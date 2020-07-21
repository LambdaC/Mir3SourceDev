#include "stdafx.h"

BYTE g_SpitMap[8][5][5] = {
							{	{0, 0, 1, 0, 0},     //DR_UP
								{0, 0, 1, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0} },

							{	{0, 0, 0, 0, 1},     //DR_UPRIGHT
								{0, 0, 0, 1, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0} },

							{	{0, 0, 0, 0, 0},     //DR_RIGHT
								{0, 0, 0, 0, 0},
								{0, 0, 0, 1, 1},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0} },

							{	{0, 0, 0, 0, 0},     //DR_DOWNRIGHT
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 1, 0},
								{0, 0, 0, 0, 1} },

							{	{0, 0, 0, 0, 0},     //DR_DOWN
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 1, 0, 0},
								{0, 0, 1, 0, 0} },

							{	{0, 0, 0, 0, 0},     //DR_DOWNLEFT
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 1, 0, 0, 0},
								{1, 0, 0, 0, 0} },

							{	{0, 0, 0, 0, 0},     //DR_LEFT
								{0, 0, 0, 0, 0},
								{1, 1, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0} },

							{	{1, 0, 0, 0, 0},     //DR_UPLEFT
								{0, 1, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0} }
};

CMonsterObject::CMonsterObject()
{
	m_dwRunNextTick		= 250;
	m_dwSearchTick		= 3000 + rand() % 2000;

	m_nDirection		= 4;

	m_pTargetObject		= NULL;
	m_btTargetDir		= 0;
	m_pExpHitterObject	= NULL;

	m_dwHitTime			= 0;

	m_fIsDead			= FALSE;
	m_fHideMode			= FALSE;

	m_btLight			= 0;
	
	m_fDupMode			= FALSE;
	m_fRunAwayMode		= FALSE;
	m_fNoAttackMode		= FALSE;
	m_fHasMission		= FALSE;
	m_fBoHolySeize		= FALSE;

	m_dwSearchEnemyTime	= GetTickCount();
	m_dwThinkTime		= GetTickCount();

	m_wObjectType		= _OBJECT_MONSTER;

	m_btAntiMagic		= 0;

	m_dwGold			= 0;
}

void CMonsterObject::KickException()
{
	m_fIsDead		= TRUE;
	m_dwDeathTime	= GetTickCount();

	MakeGhost();
}
/*procedure  TCreature.KickException;
var
   hum: TUserHuman;
begin
   if RaceServer = RC_USERHUMAN then begin
      MapName := HomeMap;
      CX := HomeX;
      CY := HomeY;
      hum := TUserHuman(self);
      hum.EmergencyClose := TRUE;
   end else begin  //
      Death := TRUE;
      DeathTime := GetTickCount;
      MakeGhost;
   end;
end; */

CMonsterObject* CMonsterObject::MakeClone(int nMonRace)
{
	CMonRaceInfo* pMonRaceInfo = &g_pMonRaceInfo[nMonRace];

	if (pMonRaceInfo)
	{
		CMonsterObject* pMonsterObject = (CMonsterObject*)AddCreatureSysop(m_nCurrX, m_nCurrY, pMonRaceInfo, FALSE);

		if (pMonsterObject)
		{
			pMonsterObject->m_pMasterObject = m_pMasterObject;
//      mon.MasterRoyaltyTime := src.MasterRoyaltyTime;
//      mon.SlaveMakeLevel := src.SlaveMakeLevel;
//      mon.SlaveExpLevel := src.SlaveExpLevel;
//      mon.RecalcAbilitys; //ApplySlaveLevelAbilitys;
//      mon.ChangeNameColor;
			if (m_pMasterObject)
			{
				CPlayerObject* pPlayerObject = dynamic_cast<CPlayerObject*>(m_pMasterObject);

				if (pPlayerObject)
					pPlayerObject->m_xSlaveObjList.AddNewNode(pMonsterObject);
			}

			pMonsterObject->m_WAbility			= m_WAbility;
			memcpy(pMonsterObject->m_wStatusArr, m_wStatusArr, sizeof(m_wStatusArr));
			pMonsterObject->m_pTargetObject		= m_pTargetObject;
			pMonsterObject->m_dwTargetFocusTime	= m_dwTargetFocusTime;
			pMonsterObject->m_pLastHitterObject	= m_pLastHitterObject;
			pMonsterObject->m_dwLastHitTime		= m_dwLastHitTime;
			pMonsterObject->m_nDirection		= m_nDirection;

			return pMonsterObject;
		}
	}

	return NULL;
}

BOOL CMonsterObject::IsProperTarget(CCharObject* pTargetObject)
{
	BOOL fFlag = FALSE;

	if (pTargetObject == this || !pTargetObject) return fFlag;

	if (pTargetObject->m_wObjectType & _OBJECT_HUMAN)
	{
		CPlayerObject *pPlayerObject = dynamic_cast<CPlayerObject*>(pTargetObject);

		if (pPlayerObject)
		{
			if (pPlayerObject->IsEmpty())
				return fFlag;
		}
	}

//	if (pTargetMonsterObject)
//	{
	if (m_pMasterObject)
	{
		if (m_pMasterObject->m_pTargetObject == pTargetObject)
			fFlag = TRUE;

		if (pTargetObject->m_pTargetObject)
		{
			if ((pTargetObject->m_pTargetObject == m_pMasterObject) || 
				(pTargetObject->m_pTargetObject->m_pMasterObject == m_pMasterObject))
				fFlag = TRUE;
		}
/*			if (
         //������ �ִ� ��
         //if (target.RaceServer >= RC_ANIMAL) and (target.Master = nil) then
         //   Result := TRUE;
         if (Master.LastHiter = target) or (Master.ExpHiter = target) or (Master.TargetCret = target) then
            Result := TRUE;
         if target.TargetCret <> nil then begin
            if (target.TargetCret = Master) or  //������ ����
               (target.TargetCret.Master = Master) and (target.RaceServer <> 0) //���Ḧ ����, ����ΰ�� ����
            then
               Result := TRUE;
         end; */
		if (pTargetObject->m_pTargetObject == this)
			fFlag = TRUE;
/*         if (target.TargetCret = self) and (target.RaceServer >= RC_ANIMAL) then  //���̸鼭 �ڽ��� �����ϴ� ��
            Result := TRUE;
         if target.Master <> nil then begin  //��밡 ��ȯ��
            if (target.Master = Master.LastHiter) or (target.Master = Master.TargetCret) then
               Result := TRUE;
         end;
         if target.Master = Master then Result := FALSE;  //������ ������ ���ݾ���
         if target.BoHolySeize then Result := FALSE;  //��迡 �ɷ� ������ ���ݾ���
         if Master.BoSlaveRelax then Result := FALSE;
         if target.RaceServer = RC_USERHUMAN then begin  //��밡 ����� ���
            if (Master.InSafeZone) or (target.InSafeZone) then begin  //������ �������뿡 �ְų�, ��밡 �������뿡 �ִ� ���
               Result := FALSE;
            end;
         end;
         BreakCrazyMode;  //�����ִ� ��.. */
	}
	else
	{
		if (pTargetObject->m_wObjectType & _OBJECT_HUMAN)
			fFlag = TRUE;
		
		if (pTargetObject->m_pMasterObject)
			fFlag = TRUE;

/*         if target.RaceServer = RC_USERHUMAN then
            Result := TRUE;
         if (RaceServer > RC_PEACENPC) and (RaceServer < RC_ANIMAL) then begin //���ݷ��� ���� NPC�� �ƹ��� �����Ѵ�.
            Result := TRUE;
         end;
         if target.Master <> nil then
            Result := TRUE; */

//		if BoCrazyMode then  //��ħ, �ƹ��� ����, �� �Ȱ���... (��ȯ�����Ե� ���Ѵ�.)
  //       Result := TRUE;
	}

	return fFlag;
}

void CMonsterObject::GetCharName(char *pszCharName)
{
	strcpy(pszCharName, m_szName);

	if (m_pMasterObject)
	{
		char szMasterName[32];

		m_pMasterObject->GetCharName(szMasterName);

		strcat(pszCharName, " (");
		strcat(pszCharName, szMasterName);
		strcat(pszCharName, ")");
	}
}

void CMonsterObject::MakeHolySeize(DWORD dwHTime)
{
	m_fBoHolySeize		= TRUE;
	m_dwHolySeizeStart	= GetTickCount();
	m_dwHolySeizeTime	= dwHTime;
	
	AddRefMsg(RM_CHANGENAMECOLOR, 0, 0, 0, 0, NULL);
}

void CMonsterObject::BreakHolySeize()
{
	if (m_fBoHolySeize)
	{
		m_fBoHolySeize		= FALSE;
		AddRefMsg(RM_CHANGENAMECOLOR, 0, 0, 0, 0, NULL);
	}
}

BOOL CMonsterObject::WalkTo(int nDir)
{
	int nX, nY;

	if (m_fBoHolySeize)
		return FALSE;

	WalkNextPos(nDir, nX, nY);

	if (m_wEscape)
	{
		if (!m_pMap->CanSafeWalk(nX, nY))
			return FALSE;
	}

	return WalkXY(nX, nY, nDir);
}

void CMonsterObject::Die()
{
	CPlayerObject*	pPlayerObject = NULL;
	CMonsterObject* pMonsterObject = NULL;

	if (m_pExpHitterObject)
	{
		pPlayerObject = dynamic_cast<CPlayerObject*>(m_pExpHitterObject);

		if (pPlayerObject)
		{
			int nExp = pPlayerObject->CalcGetExp(m_Ability.Level, m_nFightExp);
			pPlayerObject->GainExp(nExp);
		}
		else
		{
			pMonsterObject = dynamic_cast<CMonsterObject*>(m_pExpHitterObject);

			if (pMonsterObject)
			{
				if (pMonsterObject->m_pMasterObject)
				{
					pPlayerObject = dynamic_cast<CPlayerObject*>(pMonsterObject->m_pMasterObject);

					int nExp = pPlayerObject->CalcGetExp(m_Ability.Level, m_nFightExp);
					pPlayerObject->GainExp(nExp);
				}
			}
		}
	}

//	MonGetRandomItems();
	ScatterBagItems();
	
	m_pMasterObject = NULL;

	CCharObject::Die();
/*   try
      //���� ���� ���.  ����ġ�� ��´�.
      if (RaceServer <> RC_USERHUMAN) and (LastHiter <> nil) then begin
         //������ �����ڰ� ����̾�� ��.
         if ExpHiter <> nil then begin //����ġ�� �Դ� ���.. ���� ������ ������ ���
            if ExpHiter.RaceServer = RC_USERHUMAN then begin
               //�ִ� ü�� ��ŭ, ����� ������ ����ؼ� ����ġ�� ��´�.
               exp := ExpHiter.CalcGetExp (self.Abil.Level, self.FightExp);
               if not BoVentureServer then begin
                  ExpHiter.GainExp (exp);
               end else begin
                  //���輭�������� ������ �ö󰣴�.
               end;
            end else begin
               if ExpHiter.Master <> nil then begin //�������� ��ȯ��
                  //���ϵ� ����ġ�� ����
                  ExpHiter.GainSlaveExp (self.Abil.Level);  //����� ������ŭ ������ ����
                  //������ ����ġ�� �Դ´�.
                  exp := ExpHiter.Master.CalcGetExp (self.Abil.Level, self.FightExp);
                  if not BoVentureServer then begin
                     ExpHiter.Master.GainExp (exp); //��ȯ���� �θ��� ����� �Դ´�.
                  end else begin
                     //���輭�������� ������ �ö󰣴�.
                  end;
               end;
            end;
         end else
            if LastHiter.RaceServer = RC_USERHUMAN then begin
               //�ִ� ü�� ��ŭ, ����� ������ ����ؼ� ����ġ�� ��´�.
               exp := LastHiter.CalcGetExp (self.Abil.Level, self.FightExp);
               if not BoVentureServer then begin
                  LastHiter.GainExp (exp);
               end else begin
                  //
               end;
            end;
      end;
      Master := nil;
   except
      MainOutMessage ('[Exception] TCreature.Die 1');
   end;	  */
}

void CMonsterObject::ScatterBagItems()
{
	_LPTUSERITEMRCD lptUserItemRcd = NULL;

	if (m_xTItemRcd.GetCount())
	{
		PLISTNODE pListNode = m_xTItemRcd.GetHead();

		while (pListNode)
		{
			lptUserItemRcd = m_xTItemRcd.GetData(pListNode);

			if (lptUserItemRcd)
				DropItemDown(lptUserItemRcd, 3, FALSE);

			pListNode = m_xTItemRcd.RemoveNode(pListNode);
		}
	}
}
/*
procedure TCreature.ScatterBagItems;    //�׾ ���濡 �������� �긲.. ���� �기��.
var
   i, dropwide: integer;
   pu: PTUserItem;
   dellist: TStringList;
   boDropall: Boolean;
begin
   dellist := nil;

   boDropall := TRUE;
   if RaceServer = RC_USERHUMAN then begin
      dropwide := 2;
      if PKLevel < 2 then boDropall := FALSE; //����� 1/3Ȯ���� ������.
      //�����̴� �� ������.
   end else
      dropwide := 3;

   try
      for i:=ItemList.Count-1 downto 0 do begin
         if (Random(3) = 0) or boDropall then begin
            if DropItemDown (PTUserItem(ItemList[i])^, dropwide, TRUE) then begin
               pu := PTUserItem(ItemList[i]);
               if RaceServer = RC_USERHUMAN then begin
                  if dellist = nil then dellist := TStringList.Create;
                  //����߸� �������� Ŭ���̾�Ʈ�� �˸�.
                  dellist.AddObject(UserEngine.GetStdItemName (pu.Index), TObject(pu.MakeIndex));
               end;
               Dispose(PTUserItem(ItemList[i]));
               ItemList.Delete (i);
            end;
         end;
      end;
      if dellist <> nil then begin
         SendMsg (self, RM_DELITEMS, 0, integer(dellist), 0, 0, '');
         //dellist�� rm_delitem���� free ���Ѿ� �Ѵ�.
      end;
   except
      MainOutMessage ('[Exception] TCreature.ScatterBagItems');
   end;
end;
*/
void CMonsterObject::Initialize()
{
	memcpy(m_szName, g_pMonRaceInfo[g_pMonRaceInfo[m_nRace].wRaceIndex].szMonName, memlen(g_pMonRaceInfo[g_pMonRaceInfo[m_nRace].wRaceIndex].szMonName));

	MonGetRandomItems();

//	cret.RaceImage := pm.RaceImg;
//	cret.Appearance := pm.Appr;
//	cret.LifeAttrib := pm.LifeAttrib;
	m_btLifeAttrib		= g_pMonRaceInfo[m_nRace].btUndead;

	m_Ability.Level		= g_pMonRaceInfo[m_nRace].Level;
	m_Ability.HP		= g_pMonRaceInfo[m_nRace].HP;
	m_Ability.MaxHP		= g_pMonRaceInfo[m_nRace].HP;
	m_Ability.MP		= g_pMonRaceInfo[m_nRace].MP;
	m_Ability.MaxMP		= g_pMonRaceInfo[m_nRace].MP;
	m_Ability.AC		= g_pMonRaceInfo[m_nRace].AC;
	m_Ability.MAC		= g_pMonRaceInfo[m_nRace].MAC;
	m_Ability.DC		= g_pMonRaceInfo[m_nRace].DC;
	m_Ability.MC		= 0;
	m_Ability.SC		= 0;
	m_Ability.m_wWater	= g_pMonRaceInfo[m_nRace].m_wWater;
	m_Ability.m_wFire	= g_pMonRaceInfo[m_nRace].m_wFire;
	m_Ability.m_wWind	= g_pMonRaceInfo[m_nRace].m_wWind;
	m_Ability.m_wLight	= g_pMonRaceInfo[m_nRace].m_wLight;
	m_Ability.m_wEarth	= g_pMonRaceInfo[m_nRace].m_wEarth;

	m_nFightExp			= g_pMonRaceInfo[m_nRace].Exp;

	m_WAbility			= m_Ability;

	m_btSpeedPoint		= (BYTE)g_pMonRaceInfo[m_nRace].Speed;
	m_btHitPoint		= (BYTE)g_pMonRaceInfo[m_nRace].Hit;

	m_dwNextWalkTime	= g_pMonRaceInfo[m_nRace].dwWalkSpeed;
	m_dwNextHitTime		= g_pMonRaceInfo[m_nRace].dwAttackSpeed;

	m_wEscape			= g_pMonRaceInfo[m_nRace].wEscape;

	m_nViewRange		= (4 * g_pMonRaceInfo[m_nRace].ViewRange) * (g_pMonRaceInfo[m_nRace].ViewRange + 1); 

	m_tFeature.btGender	= 3;
	m_tFeature.btWear	= g_pMonRaceInfo[m_nRace].nAppear;
	m_tFeature.btHair	= 0;
	m_tFeature.btWeapon	= 0;
}

void CMonsterObject::MakeGenItem(_LPTGENERALITEMRCD lptGenItemRcd)
{
	_TGENITEMRCD		GenItemRcd;

	sprintf(GenItemRcd.szItem, "G%03d%04d%04d", lptGenItemRcd->nStdIndex, lptGenItemRcd->nDura, lptGenItemRcd->nDuraMax);

	memcpy(lptGenItemRcd->szMakeIndex, GenItemRcd.szItem, 12);

	m_xTGenItemRcd.AddNewNode(lptGenItemRcd);
}

void CMonsterObject::MonGetRandomItems()
{
	CMonItem*			pMonItem = NULL;
	CMonRaceInfo*		pMonRaceInfo = &g_pMonRaceInfo[m_nRace];

//	_TMAKEITEMRCD		MakeItemRcd;

	if (pMonRaceInfo)
	{
		if (pMonRaceInfo->m_xMonItemList.GetCount())
		{
			PLISTNODE pListNode = pMonRaceInfo->m_xMonItemList.GetHead();

			while (pListNode)
			{
				pMonItem = pMonRaceInfo->m_xMonItemList.GetData(pListNode);

				if (pMonItem)
				{
//					if (1 >= rand() % pMonItem->m_nPoint)
//					{
						_LPTUSERITEMRCD lpTItemRcd = new _TUSERITEMRCD;

						switch (pMonItem->m_btItemType)
						{
							case _ITEM_GOLD:
								m_dwGold = (pMonItem->m_wCount / 2) + (rand() % pMonItem->m_wCount);
								break;
							case _ITEM_WEAPON:
							case _ITEM_ARMOR:
							case _ITEM_ACCESSORY:
							{
								ZeroMemory(lpTItemRcd->szPrefixName, sizeof(lpTItemRcd->szPrefixName));
								ZeroMemory(lpTItemRcd->btValue, sizeof(lpTItemRcd->btValue));

								lpTItemRcd->nStdIndex = pMonItem->m_wItemIndex;
								
								switch (pMonItem->m_btItemType)
								{
									case 0:
										memcpy(lpTItemRcd->szMakeIndex, "A00000000000", 12);
										break;
									case 1:
										memcpy(lpTItemRcd->szMakeIndex, "B00000000000", 12);
										break;
									case 2:
										memcpy(lpTItemRcd->szMakeIndex, "C00000000000", 12);
										break;
								}

								lpTItemRcd->nDura		= g_pStdItemSpecial[pMonItem->m_wItemIndex].wDuraMax;
								lpTItemRcd->nDuraMax	= g_pStdItemSpecial[pMonItem->m_wItemIndex].wDuraMax;

								if (rand() % 10 == 0)
									g_pStdItemSpecial[pMonItem->m_wItemIndex].UpgradeRandomItem(lpTItemRcd->btValue, lpTItemRcd->nDura, lpTItemRcd->nDuraMax);

								m_xTItemRcd.AddNewNode(lpTItemRcd);
//								MakeItemToDB(&MakeItemRcd);

								break;
							}
							case _ITEM_ETC:
							{
								_LPTGENERALITEMRCD	lptGenItemRcd = new _TGENERALITEMRCD;

								if (lptGenItemRcd)
								{
									lptGenItemRcd->nStdIndex	= pMonItem->m_wItemIndex;
									lptGenItemRcd->nDura		= g_pStdItemEtc[pMonItem->m_wItemIndex].wDuraMax;
									lptGenItemRcd->nDuraMax		= g_pStdItemEtc[pMonItem->m_wItemIndex].dwRSource;

									MakeGenItem(lptGenItemRcd);
								}

								break;
							}
						}
//					}
				}

				pListNode = pMonRaceInfo->m_xMonItemList.GetNext(pListNode);
			}
		}
	}
}
/*
function  TUserEngine.MonGetRandomItems (mon: TCreature): integer;
var
   i, numb: integer;
   list: TList;
   iname: string;
   pmi: PTMonItemInfo;
   pu: PTUserItem;
   pstd: PTStdItem;
begin
   list := nil;
   for i:=0 to MonDefList.Count-1 do begin
      if CompareText (PTMonsterInfo(MonDefList[i]).Name, mon.UserName) = 0 then begin
         list := PTMonsterInfo(MonDefList[i]).Itemlist;
         break;
      end;
   end;
   if list <> nil then begin
      for i:=0 to list.Count-1 do begin
         pmi := PTMonItemInfo(list[i]);
         if pmi.SelPoint >= Random(pmi.MaxPoint) then begin
            if CompareText(pmi.ItemName, '��') = 0 then begin
               mon.Gold := (pmi.Count div 2) + Random(pmi.Count);
            end else begin
               //����ũ ������ �̺�Ʈ....
               iname := '';
               ////if (BoUniqueItemEvent) and (not mon.BoAnimal) then begin
               ////   if GetUniqueEvnetItemName (iname, numb) then begin
                     //numb; //iname
               ////   end;
               ////end;
               if iname = '' then
                  iname := pmi.ItemName;

               new (pu);
               if CopyToUserItemFromName (iname, pu^) then begin
                  //�������� ����Ǿ� ����..
                  pu.Dura := Round ((pu.DuraMax / 100) * (20+Random(80)));

                  pstd := GetStdItem (pu.Index);
                  ////if pstd <> nil then
                  ////   if pstd.StdMode = 50 then begin  //��ǰ��
                  ////      pu.Dura := numb;
                  ////   end;

                  //���� Ȯ����
                  //�������� ���׷��̵�� ���� ����
                  if Random(10) = 0 then
                     RandomUpgradeItem (pu);

                  mon.ItemList.Add (pu)
               end else
                  Dispose (pu);
            end;
         end;
      end;
   end;
   Result := 1;
end;
*/
void CMonsterObject::SearchViewRange()
{
	int				nX, nY;
	PLISTNODE		pListNode;
	CMapCellInfo*	pMapCellInfo;
	_LPTOSOBJECT	pOSObject;
	CVisibleObject* pVisibleObject;

	// Clear VisibleObjectList
	if (m_xVisibleObjectList.GetCount())
	{
		PLISTNODE pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
				pVisibleObject->nVisibleFlag = 0;

			pListNode = m_xVisibleObjectList.GetNext(pListNode);
		}
	}

	// Search VisibleObjectList
	for (int i = 0; i < m_nViewRange; i++)
	{
		nX = m_nCurrX + g_SearchTable[i].x;
		nY = m_nCurrY + g_SearchTable[i].y;

		pMapCellInfo = m_pMap->GetMapCellInfo(nX, nY);

		if (pMapCellInfo)
		{
			if (pMapCellInfo->m_xpObjectList)
			{
				if (pMapCellInfo->m_xpObjectList->GetCount())
				{
					pListNode = pMapCellInfo->m_xpObjectList->GetHead();

					while (pListNode)
					{
						pOSObject = pMapCellInfo->m_xpObjectList->GetData(pListNode);

						if (pOSObject)
						{
							if (pOSObject->btType == OS_MOVINGOBJECT)
							{
								CCharObject* pCharObject = (CCharObject*)pOSObject->pObject;
								UpdateVisibleObject(pCharObject);
							}
						}
					
						pListNode = pMapCellInfo->m_xpObjectList->GetNext(pListNode);
					} // while (pListNode)
				} // if (pMapCellInfo->m_pObjectList.GetCount())
			}
		} // if (pMapCellInfo)
	}

	if (m_xVisibleObjectList.GetCount())
	{
		PLISTNODE pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
			{
				if (pVisibleObject->nVisibleFlag == 0)
				{
					delete pVisibleObject;		
					pVisibleObject = NULL;

					pListNode = m_xVisibleObjectList.RemoveNode(pListNode);
					continue;
				}
			} // if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
			
			pListNode = m_xVisibleObjectList.GetNext(pListNode);
		} // while (pListNode)
	}
}

BOOL CMonsterObject::IsFrontObject(CCharObject* pCharObject)
{
	for (int i = 0; i < 8; i++)
	{
		if (pCharObject->m_nCurrX == m_nCurrX + g_SearchTable[i].x && pCharObject->m_nCurrY == m_nCurrY + g_SearchTable[i].y)
			return TRUE;
	}

	return FALSE;
}

void CMonsterObject::SetLastHiter(CCharObject* pHitter)
{
	DWORD dwHitTick = GetTickCount();

	m_pLastHitterObject = pHitter;
	m_dwLastHitTime		= dwHitTick;

	if (!m_pExpHitterObject)
	{
		m_pExpHitterObject	= pHitter;
		m_dwExpHitTime		= dwHitTick;
	}
	else
	{
		if (m_pExpHitterObject == pHitter)
			m_dwExpHitTime	= dwHitTick;	
	}
}

void CMonsterObject::Wondering()
{
	if ((rand() % 20) == 0)
	{
		if ((rand() % 4) == 1)
			TurnTo(rand() % 8);
		else
			WalkTo(m_nDirection);
	}
}

void CMonsterObject::GotoTargetXY()
{
	int nDir;

	if ((m_nCurrX != m_nTargetX) || (m_nCurrY != m_nTargetY))
	{
		if (m_xVisibleObjectList.GetCount())
		{
			PLISTNODE pListNode = m_xVisibleObjectList.GetHead();

			CVisibleObject* pVisibleObject = m_xVisibleObjectList.GetData(pListNode);

			if (pVisibleObject)
			{
				if ((!pVisibleObject->pObject->m_fIsDead) && IsProperTarget(pVisibleObject->pObject) && (!pVisibleObject->pObject->m_fInspector))
				{
					if (abs(m_nCurrX - pVisibleObject->pObject->m_nCurrX) + abs(m_nCurrY - pVisibleObject->pObject->m_nCurrY) <
						abs(m_nCurrX - m_nTargetX) + abs(m_nCurrY - m_nTargetY))
					{
						SelectTarget(pVisibleObject->pObject);
						m_nTargetX = pVisibleObject->pObject->m_nCurrX;
						m_nTargetY = pVisibleObject->pObject->m_nCurrY;

						return;
					}
				}
			}
		}

		int nX = m_nTargetX;
		int nY = m_nTargetY;

		m_nFindPathTime = GetTickCount();

		while (TRUE)
		{
			if (nX > m_nCurrX)
			{
				nDir = DR_RIGHT;

				if (nY > m_nCurrY)
					nDir = DR_DOWNRIGHT;
				else if (nY < m_nCurrY)
					nDir = DR_UPRIGHT;

				break;
			}
			
			if (nX < m_nCurrX)
			{
				nDir = DR_LEFT;

				if (nY > m_nCurrY)
					nDir = DR_DOWNLEFT;
				else if (nY < m_nCurrY)
					nDir = DR_UPLEFT;

				break;
			}

			if (nY > m_nCurrY)
			{
				nDir = DR_DOWN;
				break;
			}
			
			if (nY < m_nCurrY)
			{
				nDir = DR_UP;
				break;
			}

			break;
		}

//		char szTemp[64];
//		sprintf(szTemp, "�� �� %s �� �ű� ���Ŷ�... ������", m_pTargetObject->m_szName);
//		AddRefMsg(RM_MONSTERSAY, 0, 0, 0, 0, szTemp);

		int nOldX = m_nCurrX;
		int nOldY = m_nCurrY;

		WalkTo(nDir);

		for (int i = 0; i < 7; i++)
		{
			if (nOldX == m_nCurrX && nOldY == m_nCurrY)
			{
				if (rand() % 3) nDir++;
				else if (nDir > 0) nDir--;
				else
					nDir = 7;

				if (nDir > 7) nDir = 0;
				
				WalkTo(nDir);
			}
			else
				break;
		}
	}
}

void CMonsterObject::Struck(CCharObject* pHitter)
{
	if (pHitter)
	{
		if (IsProperTarget(pHitter))
			SelectTarget(pHitter);
	}

	if (m_Ability.Level < 50)
		m_dwHitTime = m_dwHitTime + (150 - _MIN(130, m_Ability.Level * 4));

/*procedure TAnimal.Struck (hiter: TCreature);
begin
   StruckTime := GetTickCount;
   if hiter <> nil then begin
      if IsProperTarget (hiter) then
         SelectTarget (hiter);
   end;
   if BoAnimal then begin
      MeatQuality := MeatQuality - Random (300);  //������ ������ ���� ���� ��� ǰ���� ������
      if MeatQuality < 0 then MeatQuality := 0;
   end;
   if Abil.Level < 50 then
      HitTime  := HitTime + (150 - _MIN(130, Abil.Level * 4)); //�ѹ濡 ms�� �ʰ� ������.
   //WalkTime := WalkTime + (300 - _MIN(200, (Abil.Level div 5) * 20));
end;
*/
}

WORD CMonsterObject::GetThisCharColor()
{
	if (m_fBoHolySeize)
		return _CHAT_COLOR4;

	return _CHAT_COLOR3;
}

void CMonsterObject::Operate()
{
	int nCount = m_DelayProcessQ.GetCount();

	_LPTPROCESSMSG lpProcessMsg;

	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			lpProcessMsg = (_LPTPROCESSMSG)m_DelayProcessQ.PopQ();

			if (lpProcessMsg)
			{
				if (GetTickCount() < lpProcessMsg->dwDeliveryTime)
				{
					m_DelayProcessQ.PushQ((BYTE *)lpProcessMsg);
					continue;
				}

				switch (lpProcessMsg->wIdent)
				{
					case RM_DOOPENHEALTH:
					{
						MakeOpenHealth();
						break;
					}
					case RM_STRUCK:
					{
						if (lpProcessMsg->pCharObject->m_wObjectType & _OBJECT_HUMAN)
							lpProcessMsg->pCharObject->AddRefMsg(RM_STRUCK, lpProcessMsg->wParam, lpProcessMsg->lParam1, 
																			lpProcessMsg->lParam2, lpProcessMsg->lParam3, NULL);

						break;
					}
					case RM_MAGSTRUCK:
					{
						AddProcess(lpProcessMsg->pCharObject, lpProcessMsg->wIdent, lpProcessMsg->wParam, lpProcessMsg->lParam1, 
										lpProcessMsg->lParam2, lpProcessMsg->lParam3, NULL);
						break;
					}
				}

				delete lpProcessMsg;
				lpProcessMsg = NULL;
			}
		}
	}

	nCount = m_ProcessQ.GetCount();

	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			lpProcessMsg = (_LPTPROCESSMSG)m_ProcessQ.PopQ();

			switch (lpProcessMsg->wIdent)
			{
				case RM_STRUCK:
				{
					if (lpProcessMsg->pCharObject == this && lpProcessMsg->lParam3)
					{
						SetLastHiter((CCharObject*)lpProcessMsg->lParam3);
						Struck((CCharObject*)lpProcessMsg->lParam3);

						m_dwHealthTick	= 0;
						m_dwSpellTick	= 0;
						m_btPerHealth--;
						m_btPerSpell--;

						BreakHolySeize();
					}

					break;
				}
				case RM_MAGSTRUCK:
				case RM_MAGSTRUCK_MINE:
				{
					if (lpProcessMsg->wIdent == RM_MAGSTRUCK)
					{
						if (m_Ability.Level < 50)
							m_dwWalkTime += 800 + (rand() % 1000);
					}

					int nVal = GetMagStruckDamage(lpProcessMsg->lParam1);

					if (nVal > 0)
					{
						StruckDamage(nVal);
						HealthSpellChanged();
						AddRefMsg(RM_STRUCK_MAG, nVal, m_WAbility.HP, m_WAbility.MP, (int)lpProcessMsg->pCharObject, NULL);
						
//                  if BoAnimal then begin //��Ⱑ ������ ������ ���..
 //                   MeatQuality := MeatQuality - v1 * 1000;  //������ ������ ������� ġ�������� ��������.
//                  end;
						SetLastHiter(lpProcessMsg->pCharObject);
//						Struck(lpProcessMsg->pCharObject);

						m_dwHealthTick	= 0;
						m_dwSpellTick	= 0;

						BreakHolySeize();
					}

					break;
				}
			}

			delete lpProcessMsg;
			lpProcessMsg = NULL;
		}
	}

	Run();
}

void CMonsterObject::MonsterNormalAttack()
{
	if (m_xVisibleObjectList.GetCount())
	{
		PLISTNODE pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			CVisibleObject* pVisibleObject = m_xVisibleObjectList.GetData(pListNode);

			if (pVisibleObject)
			{
				if ((!pVisibleObject->pObject->m_fIsDead) && IsProperTarget(pVisibleObject->pObject) 
					&& (!pVisibleObject->pObject->m_fInspector) && (!pVisibleObject->pObject->m_fHumHideMode))
				{
					if (abs(m_nCurrX - pVisibleObject->pObject->m_nCurrX) + abs(m_nCurrY - pVisibleObject->pObject->m_nCurrY) < 999)
					{
						SelectTarget(pVisibleObject->pObject);
						return;
					}
				}
			}

			pListNode = m_xVisibleObjectList.GetNext(pListNode);
		}
	}
}

BOOL CMonsterObject::TargetInAttackRange()
{
	if (m_pTargetObject)
	{
		if ((m_pTargetObject->m_nCurrX >= m_nCurrX - 1) && (m_pTargetObject->m_nCurrX <= m_nCurrX + 1) &&
			(m_pTargetObject->m_nCurrY >= m_nCurrY - 1) && (m_pTargetObject->m_nCurrY <= m_nCurrY + 1) && 
			!((m_pTargetObject->m_nCurrX == m_nCurrX) && (m_pTargetObject->m_nCurrY == m_nCurrY))) 
		{
			if ((m_pTargetObject->m_nCurrX == m_nCurrX - 1) && (m_pTargetObject->m_nCurrY == m_nCurrY))
			{
				m_btTargetDir = DR_LEFT;
				return TRUE;
			}

			if ((m_pTargetObject->m_nCurrX == m_nCurrX + 1) && (m_pTargetObject->m_nCurrY == m_nCurrY))
			{
				m_btTargetDir = DR_RIGHT;
				return TRUE;
			}

			if ((m_pTargetObject->m_nCurrX == m_nCurrX) && (m_pTargetObject->m_nCurrY == m_nCurrY - 1))
			{
				m_btTargetDir = DR_UP;
				return TRUE;
			}

			if ((m_pTargetObject->m_nCurrX == m_nCurrX) && (m_pTargetObject->m_nCurrY == m_nCurrY + 1))
			{
				m_btTargetDir = DR_DOWN;
				return TRUE;
			}

			if ((m_pTargetObject->m_nCurrX == m_nCurrX - 1) && (m_pTargetObject->m_nCurrY == m_nCurrY - 1))
			{
				m_btTargetDir = DR_UPLEFT;
				return TRUE;
			}

			if ((m_pTargetObject->m_nCurrX == m_nCurrX + 1) && (m_pTargetObject->m_nCurrY == m_nCurrY - 1))
			{
				m_btTargetDir = DR_UPRIGHT;
				return TRUE;
			}

			if ((m_pTargetObject->m_nCurrX == m_nCurrX - 1) && (m_pTargetObject->m_nCurrY == m_nCurrY + 1))
			{
				m_btTargetDir = DR_DOWNLEFT;
				return TRUE;
			}

			if ((m_pTargetObject->m_nCurrX == m_nCurrX + 1) && (m_pTargetObject->m_nCurrY == m_nCurrY + 1))
			{
				m_btTargetDir = DR_DOWNRIGHT;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CMonsterObject::TargetInSpitRange(int& nTargetDir)
{
	int nX = 0, nY = 0;

	if ((abs(m_pTargetObject->m_nCurrX - m_nCurrX) <= 2) && (abs(m_pTargetObject->m_nCurrY - m_nCurrY) <= 2))
	{
		nX = m_pTargetObject->m_nCurrX - m_nCurrX;
		nY = m_pTargetObject->m_nCurrY - m_nCurrY;

		if ((abs(nX) <= 1) && (abs(nY) <= 1))
		{
			TargetInAttackRange();
			return TRUE;
		}
		else
		{
			nX += 2;
			nY += 2;

			if ((nX >= 0 && nX <= 4) && (nY >= 0 && nY <= 4))
			{
				nTargetDir = GetNextDirection(m_pTargetObject->m_nCurrX, m_pTargetObject->m_nCurrY);

				if (g_SpitMap[nTargetDir][nX][nY] == 1)
					return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CMonsterObject::Attack()
{
	m_nDirection = (int)m_btTargetDir;

	_Attack(CM_HIT, m_pTargetObject);

	AddRefMsg(RM_HIT, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

	return TRUE;
}

BOOL CMonsterObject::AttackTarget()
{
	if (m_pTargetObject)
	{
		if (TargetInAttackRange())
		{
			if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
			{
				m_dwHitTime	= m_dwTargetFocusTime = GetTickCount();
					
				Attack();
				BreakHolySeize();
			}

			return TRUE;
		}
		else
		{
			if (m_pTargetObject->m_pMap == m_pMap)
			{
				m_nTargetX = m_pTargetObject->m_nCurrX;
				m_nTargetY = m_pTargetObject->m_nCurrY;
			}
			else
			{
				m_pTargetObject = NULL;

				m_nTargetX = -1;
				m_nTargetY = -1;
			}
		}
	}

	return FALSE;
}

BOOL CMonsterObject::Think()
{
	if (GetTickCount() - m_dwThinkTime > 3000)
	{
		m_dwThinkTime = GetTickCount();

		if (m_pMap->GetDupCount(m_nCurrX, m_nCurrY) >= 2)
			m_fDupMode = TRUE;

		if (m_pTargetObject)
		{
			if (!IsProperTarget(m_pTargetObject))
				m_pTargetObject = NULL;
		}
	}

	if (m_fDupMode)
	{
		int nOldX = m_nCurrX;
		int nOldY = m_nCurrY;

		WalkTo(rand() % 8);

		if (nOldX != m_nCurrX || nOldX != m_nCurrX)
		{
			m_fDupMode = FALSE;
			return TRUE;
		}
	}

	return FALSE;
}

void CMonsterObject::InheritedRun()
{
	if (RestoreHealSpell())
		Die();

	CCharObject::Run();
}

void CMonsterObject::Run()
{
	if (!m_fIsDead && !m_fHideMode && !m_fIsGhost && !m_fStoneMode && m_wStatusArr[POISON_STONE] == 0)
	{
		if (m_pTargetObject)
		{
			if ((GetTickCount() - m_dwTargetFocusTime > 30000) || m_pTargetObject->m_fIsDead || m_pTargetObject->m_fIsGhost ||
				(abs(m_pTargetObject->m_nCurrX - m_nCurrX) > 15) || (abs(m_pTargetObject->m_nCurrY - m_nCurrY) > 15))
				m_pTargetObject = NULL;
		}
/*      if LastHiter <> nil then begin
         if (GetTickCount - LastHitTime > 30 * 1000) or
            (LastHiter.Death) or
            (LastHiter.BoGhost) then
             LastHiter := nil;
      end;
      if ExpHiter <> nil then begin
         if (GetTickCount - ExpHitTime > 6 * 1000) or
            (ExpHiter.Death) or
            (ExpHiter.BoGhost) then
             ExpHiter := nil;
      end;
      if Master <> nil then begin
         BoNoItem := TRUE;
         if (Master.Death and (GetTickCount - Master.DeathTime > 1000)) or
            (Master.BoGhost and (GetTickCount - Master.GhostTime > 1000)) then begin
            WAbil.HP := 0; //Die;
            //Master := nil;
         end;
      end;
*/
		if (m_fBoHolySeize)
		{
			if (GetTickCount() - m_dwHolySeizeStart > m_dwHolySeizeTime)
				BreakHolySeize();
		}

		if (Think())
		{
			InheritedRun();
			return;
		}

		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			m_dwWalkTime = GetTickCount();

			if (!m_fRunAwayMode)
			{
				if (!m_fNoAttackMode)
				{
					if (m_pTargetObject)
					{
						if (AttackTarget())
						{
							InheritedRun();
							return;
						}
					}
					else
					{
						m_nTargetX = -1;
						
						if (m_fHasMission)
						{
							m_nTargetX = m_nMissionX;
							m_nTargetY = m_nMissionY;
						}
					}
				}

				if (m_pMasterObject)
				{
					if (!m_pTargetObject)
					{
						int nX, nY;

						m_pMasterObject->GetBackPosition(nX, nY);

						if ((abs(m_nTargetX - nX) > 1) || (abs(m_nTargetY - nY) > 1))
						{
							m_nTargetX = nX;
							m_nTargetY = nY;
							
							if ((abs(m_nCurrX - nX) <= 2) || (abs(m_nCurrY - nY) <= 2))
							{
								if (m_pMap->GetObject(nX, nY))
								{
									m_nTargetX = m_nCurrX;
									m_nTargetY = m_nCurrY;
								}
							}
						}
					}

/*               //���ΰ� �ʹ� ������ ������...
               if (not Master.BoSlaveRelax) and
                  ((PEnvir <> Master.PEnvir) or
                   (abs(CX-Master.CX) > 20) or
                   (abs(CY-Master.CY) > 20)
                  )
               then begin
                  SpaceMove (Master.PEnvir.MapName, TargetX, TargetY, 1);
               end;
            end; */
					if ((abs(m_nCurrX - m_pMasterObject->m_nCurrX) > 20) || (abs(m_nCurrY - m_pMasterObject->m_nCurrY) > 20))
						SpaceMove(m_nTargetX, m_nTargetY, m_pMasterObject->m_pMap);
				}

			}
			else
			{
				if (m_dwRunAwayTime > 0)
				{
					if (GetTickCount() - m_dwRunAwayStart > m_dwRunAwayTime)
					{
						m_fRunAwayMode	= FALSE;
						m_dwRunAwayTime	= 0;
					}
				}
			}

/*         if Master <> nil then begin
            if Master.BoSlaveRelax then begin
               //������ �޽��϶�� ��...
               inherited Run;
               exit;
            end;
         end;
*/
			if (m_nTargetX != -1 )
				GotoTargetXY();
			else
			{
				if (!m_pTargetObject)
					Wondering();
			}
		}
	}

	InheritedRun();
}

void CMonsterObject::ComeOut()
{
	m_fHideMode = FALSE;
	AddRefMsg(RM_DIGUP, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
}

void CMonsterObject::ComeDown()
{
	AddRefMsg(RM_DIGDOWN, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

	CVisibleObject* pVisibleObject;

	if (m_xVisibleObjectList.GetCount())
	{
		PLISTNODE pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
			{
				delete pVisibleObject;
				pVisibleObject = NULL;
			}

			pListNode = m_xVisibleObjectList.RemoveNode(pListNode);
		} // while (pListNode)
	}

	m_fHideMode = TRUE;
}

BOOL CMonsterObject::CheckComeOut(int nValue)
{
	if (m_xVisibleObjectList.GetCount())
	{
		PLISTNODE pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			CVisibleObject* pVisibleObject = m_xVisibleObjectList.GetData(pListNode);

			if (pVisibleObject)
			{
				if ((!pVisibleObject->pObject->m_fIsDead) && IsProperTarget(pVisibleObject->pObject) && (!pVisibleObject->pObject->m_fInspector))
				{
					if (abs(m_nCurrX - pVisibleObject->pObject->m_nCurrX) <= nValue && abs(m_nCurrY - pVisibleObject->pObject->m_nCurrY) <= nValue)
						return TRUE;
				}
			}

			pListNode = m_xVisibleObjectList.GetNext(pListNode);
		}
	}

	return FALSE;
}

/* **************************************************************************************

		�Ϲ� ����

   ************************************************************************************** */

void CGenneralMonObject::Run() 
{ 
	if (!m_fIsDead && !m_fIsGhost)
	{
		if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
		{
			m_dwSearchEnemyTime = GetTickCount();
			MonsterNormalAttack();
		}
	}

	CMonsterObject::Run();	
}

/* **************************************************************************************

		��

   ************************************************************************************** */

CChickenObject::CChickenObject()
{
	m_nMeatQuality		= 3000 + rand() % 2000;
	m_nBodyLeathery		= 50;
}

void CChickenObject::Run()
{
}

/* **************************************************************************************

		�ָ�ȣ��, �ָ�����

   ************************************************************************************** */

CScultureObject::CScultureObject()
{
	m_dwSearchTick	= 1500 + rand() % 1500;

	m_fStoneMode	= TRUE;
	m_nCharStatusEx = STATE_STONE_MODE;
	m_nCharStatus	= GetCharStatus();
}

void CScultureObject::MeltStone()
{
	m_nCharStatusEx	= 0;
	m_nCharStatus	= GetCharStatus();

	AddRefMsg(RM_DIGUP, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

	m_fStoneMode	= FALSE;
}

void CScultureObject::MeltStoneAll()
{
	CWHList<CCharObject*>	ObjectList;

	MeltStone();

	m_pMap->GetMapObject(m_nCurrX, m_nCurrY, 7, &ObjectList);

	if (ObjectList.GetCount())
	{
		PLISTNODE		pListNode = ObjectList.GetHead();
		CMonsterObject*	pTargetObject;

		while (pListNode)
		{
			if (pTargetObject = (CMonsterObject*)ObjectList.GetData(pListNode))
			{
				if (pTargetObject->m_fStoneMode)
				{
					if (pTargetObject->m_wObjectType & _OBJECT_MONSTER)
					{
						switch (pTargetObject->m_nRace)
						{
							case 145:
							case 148:
								((CScultureObject*)pTargetObject)->MeltStone();
								break;
						}
					}
				}
			}
		
			pListNode = ObjectList.RemoveNode(pListNode);
		}
	}
}

void CScultureObject::Run()
{
	if (!m_fIsDead && !m_fIsGhost && m_wStatusArr[POISON_STONE] == 0)
	{
		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			if (m_fStoneMode)
			{
				if (CheckComeOut(2))
				{
					MeltStoneAll();
					m_dwWalkTime = GetTickCount() + 2000;
				}
			}
			else
			{
				if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
				{
					m_dwSearchEnemyTime = GetTickCount();
					MonsterNormalAttack();
				}
			}
		}
	}

	CMonsterObject::Run();	
}

/* **************************************************************************************

		�ָ���

   ************************************************************************************** */

CScultureKingObject::CScultureKingObject()
{
	m_dwSearchTick	= 1500 + rand() % 1500;

	m_nDangerLevel	= 5;

	m_fStoneMode	= TRUE;
	m_nCharStatusEx = STATE_STONE_MODE;
	m_nCharStatus	= GetCharStatus();

	m_nDirection	= 5;
}

void CScultureKingObject::CallSlave()
{
	static const int MaxSlaveList = 4;
	static int SlaveList[MaxSlaveList] = { 143/*���û�*/, 145/*�ָ�����*/, 148/* �ָ�ȣ�� */, 126/*���⳪��*/ };

	int				nCount = 6 + (rand() % 6);
	int				nMonRace;
	int				nX, nY;
	CMonsterObject* pMonObject;

	for (int i = 0; i < nCount; i++)
	{
		if (m_SlaveObjectList.GetCount() < 30)
		{
			nMonRace = SlaveList[rand() % MaxSlaveList];	

			GetFrontPosition(nX, nY);

			pMonObject = (CMonsterObject*)AddCreatureSysop(nX, nY, &g_pMonRaceInfo[nMonRace], FALSE);

			if (pMonObject)
				m_SlaveObjectList.AddNewNode(pMonObject);
		}
	}
}

void CScultureKingObject::MeltStone()
{
	m_nCharStatusEx	= 0;
	m_nCharStatus	= GetCharStatus();

	AddRefMsg(RM_DIGUP, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

	m_fStoneMode	= FALSE;

//   event := TEvent.Create (PEnvir, CX, CY, ET_SCULPEICE, 5 * 60 * 1000, TRUE);
//   EventMan.AddEvent (event);
}

void CScultureKingObject::Run()
{
	if (!m_fIsDead && !m_fIsGhost && m_wStatusArr[POISON_STONE] == 0)
	{
		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			if (m_fStoneMode)
			{
				if (CheckComeOut(2))
				{
					MeltStone();
					m_dwWalkTime = GetTickCount() + 2000;
				}
			}
			else
			{
				if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
				{
					m_dwSearchEnemyTime = GetTickCount();
					MonsterNormalAttack();
				}
			
				if (((m_WAbility.HP / m_WAbility.MaxHP * 5) < m_nDangerLevel) && (m_nDangerLevel > 0))
				{
					m_nDangerLevel--;
					CallSlave();
				}

				if (m_WAbility.HP == m_WAbility.MaxHP) 
					m_nDangerLevel = 5;
			}
		}

		if (m_SlaveObjectList.GetCount())
		{
			PLISTNODE		pListNode = NULL;
			CMonsterObject* pMonsterObject = NULL;

			pListNode = m_SlaveObjectList.GetHead();

			while (pListNode)
			{
				pMonsterObject = m_SlaveObjectList.GetData(pListNode);

				if (pMonsterObject->m_fIsDead || pMonsterObject->m_fIsGhost)
					pListNode = m_SlaveObjectList.RemoveNode(pListNode);
				else
					pListNode = m_SlaveObjectList.GetNext(pListNode);
			}
		}
	}

	CMonsterObject::Run();	
}

/* **************************************************************************************

		�񸷿���

   ************************************************************************************** */

CBeeQueen::CBeeQueen()
{
	m_dwSearchTick	= 2500 + rand() % 1500;

	m_fStickMode = TRUE;
}

void CBeeQueen::MakeChildBee()
{
	if (m_SlaveObjectList.GetCount() < 15)
	{
		AddRefMsg(RM_HIT, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
		AddDelayProcess(this, RM_ZEN_BEE, 0, 0, 0, 0, NULL, 500);
	}
}

void CBeeQueen::Operate()
{
	int nCount = m_DelayProcessQ.GetCount();

	_LPTPROCESSMSG lpProcessMsg;

	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			lpProcessMsg = (_LPTPROCESSMSG)m_DelayProcessQ.PopQ();

			if (lpProcessMsg)
			{
				if (GetTickCount() < lpProcessMsg->dwDeliveryTime)
				{
					m_DelayProcessQ.PushQ((BYTE *)lpProcessMsg);
					continue;
				}

				switch (lpProcessMsg->wIdent)
				{
					case RM_ZEN_BEE:
					{
						CMonsterObject *pMonObject = (CMonsterObject *)AddCreatureSysop(m_nCurrX, m_nCurrY, &g_pMonRaceInfo[_MONSTER_BEE], FALSE);

						if (pMonObject)
						{
							m_SlaveObjectList.AddNewNode(pMonObject);
							pMonObject->SelectTarget(m_pTargetObject);
						}

						break;
					}
				}

				delete lpProcessMsg;
				lpProcessMsg = NULL;
			}
		}
	}

	CMonsterObject::Operate();
}

void CBeeQueen::Run()
{
	if (!m_fIsDead && !m_fIsGhost && m_wStatusArr[POISON_STONE] == 0)
	{
		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			m_dwWalkTime = GetTickCount();

			if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
			{
				m_dwHitTime = GetTickCount();
				MonsterNormalAttack();

				if (m_pTargetObject)
					MakeChildBee();
			}
		}

		if (m_SlaveObjectList.GetCount())
		{
			PLISTNODE		pListNode = NULL;
			CMonsterObject* pMonsterObject = NULL;

			pListNode = m_SlaveObjectList.GetHead();

			while (pListNode)
			{
				pMonsterObject = m_SlaveObjectList.GetData(pListNode);

				if (pMonsterObject->m_fIsDead || pMonsterObject->m_fIsGhost)
					pListNode = m_SlaveObjectList.RemoveNode(pListNode);
				else
					pListNode = m_SlaveObjectList.GetNext(pListNode);
			}
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		�ֵ��� �ذ�, ���û�

   ************************************************************************************** */

CDualAxeObject::CDualAxeObject(int nChainShotCount)
{
   m_nChainShot			= 0;
   m_nChainShotCount	= nChainShotCount;
}

void CDualAxeObject::FlyAxeAttack(CCharObject* pTargetObject)
{
//   if PEnvir.CanFly (CX, CY, targ.CX, targ.CY) then begin //������ ���ư��� �ִ���.
	int nDamage;
	int nDir	= GetNextDirection(pTargetObject->m_nCurrX, pTargetObject->m_nCurrY);

	if ((HIBYTE(m_WAbility.DC) - LOBYTE(m_WAbility.DC) + 1) > 0)
		nDamage = LOBYTE(m_WAbility.DC) + rand() % (HIBYTE(m_WAbility.DC) - LOBYTE(m_WAbility.DC) + 1);
	else
		nDamage = LOBYTE(m_WAbility.DC);

	if (nDamage > 0)
		nDamage = pTargetObject->GetHitStruckDamage(nDamage);

	if (nDamage > 0)
	{
		pTargetObject->StruckDamage(nDamage);
		pTargetObject->AddDelayProcess(pTargetObject, RM_STRUCK, nDamage, pTargetObject->m_WAbility.HP, pTargetObject->m_WAbility.MaxHP, 
										(int)this /*Hitter*/, NULL, 600 + _MAX(abs(m_nCurrX - pTargetObject->m_nCurrX), abs(m_nCurrY - pTargetObject->m_nCurrY) * 50));
	}

	AddRefMsg(RM_FLYAXE, nDir, m_nCurrX, m_nCurrY, (int)pTargetObject, NULL);
}

BOOL CDualAxeObject::AttackTarget()
{
	if (m_pTargetObject)
	{
		if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
		{
			m_dwHitTime = GetTickCount();

			if ((abs(m_nCurrX - m_pTargetObject->m_nCurrX) <= 7) && (abs(m_nCurrY - m_pTargetObject->m_nCurrY) <= 7))
			{
				if (m_nChainShot < m_nChainShotCount - 1)
				{
					m_nChainShot++;
					m_dwTargetFocusTime = GetTickCount();
					FlyAxeAttack(m_pTargetObject);
				}
				else
				{
					if ((rand() % 5) == 0)
						m_nChainShot = 0;
				}

				return TRUE;
			}
			else
			{
				if (m_pTargetObject->m_pMap == m_pMap)
				{
					m_nTargetX = m_pTargetObject->m_nCurrX;
					m_nTargetY = m_pTargetObject->m_nCurrY;
				}
				else
				{
					m_pTargetObject = NULL;

					m_nTargetX = -1;
					m_nTargetY = -1;
				}
			}
		}
	}

	return FALSE;
}

void CDualAxeObject::Run()
{
	if (!m_fIsDead && !m_fIsGhost)
	{
		if ((GetTickCount() - m_dwSearchEnemyTime > 5000))
		{
			m_dwSearchEnemyTime = GetTickCount();
			MonsterNormalAttack();
		}

		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			// �������� �ڵ� �߰�
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		����Ʈ�� ����

   ************************************************************************************** */

void CLightingZombiObject::LightingAttack(int nDir)
{
	int nSX, nSY, nTX, nTY;
	int nPwr;

	m_nDirection = nDir;

	AddRefMsg(RM_LIGHTING, 1, m_nCurrX, m_nCurrY, (int)m_pTargetObject, NULL);

	if (GetNextPosition(nDir, 1, nSX, nSY))
	{
		GetNextPosition(nDir, 1, nTX, nTY);
		nPwr = LOBYTE(m_WAbility.DC) + rand() % HIBYTE(m_WAbility.DC) - LOBYTE(m_WAbility.DC) + 1;
		MagPassThroughMagic(nSX, nSY, nTX, nTY, nDir, nPwr, TRUE);

		BreakHolySeize();
	}
}

void CLightingZombiObject::Run()
{
	if (!m_fIsDead && !m_fIsGhost && m_wStatusArr[POISON_STONE] == 0)
	{
		if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
		{
			m_dwSearchEnemyTime = GetTickCount();
			MonsterNormalAttack();
		}

		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			if (m_pTargetObject)
			{
				if ((abs(m_nCurrX - m_pTargetObject->m_nCurrX) <= 4) && (abs(m_nCurrY - m_pTargetObject->m_nCurrY) <= 4))
				{
					if ((abs(m_nCurrX - m_pTargetObject->m_nCurrX) <= 2) && (abs(m_nCurrY - m_pTargetObject->m_nCurrY) <= 2))
					{
						if (rand() % 3 != 0)
						{
							CMonsterObject::Run();
							return;
						}
					}

					GetBackPosition(m_nTargetX, m_nTargetY);
				}
			}
		}

		if (m_pTargetObject)
		{
			if ((abs(m_nCurrX - m_pTargetObject->m_nCurrX) < 6) && (abs(m_nCurrY - m_pTargetObject->m_nCurrY) < 6))
			{
				if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
				{
					m_dwHitTime = GetTickCount();
					LightingAttack(GetNextDirection(m_pTargetObject->m_nCurrX, m_pTargetObject->m_nCurrY));
				}
			}
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		��

   ************************************************************************************** */

void CRonObject::AroundAttack()
{
	CWHList<CCharObject*>	xTargetList;

	m_nDirection = (int)m_btTargetDir;

	m_pMap->GetMapObject(m_nCurrX, m_nCurrY, 1, &xTargetList);

	if (xTargetList.GetCount())
	{
		PLISTNODE		pListNode = xTargetList.GetHead();
		CCharObject*	pTargetObject;

		while (pListNode)
		{
			if (pTargetObject = xTargetList.GetData(pListNode))
				_Attack(CM_HIT, pTargetObject);
		
			pListNode = xTargetList.RemoveNode(pListNode);
		}
	}

	AddRefMsg(RM_HIT, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
}

void CRonObject::Run()
{	 
	if (!m_fIsDead && !m_fIsGhost && m_wStatusArr[POISON_STONE] == 0)
	{
		if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
		{
			m_dwSearchEnemyTime = GetTickCount();
			MonsterNormalAttack();
		}

		if (m_pTargetObject)
		{
			if ((abs(m_nCurrX - m_pTargetObject->m_nCurrX) < 6) && (abs(m_nCurrY - m_pTargetObject->m_nCurrY) < 6))
			{
				if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
				{
					m_dwHitTime = GetTickCount();
					AroundAttack();
				}
			}
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		�ϱ� ����

   ************************************************************************************** */

void CMinorNumaObject::Run()
{	 
	if (!m_fIsDead)
	{
		if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
		{
			m_dwSearchEnemyTime = GetTickCount();
			MonsterNormalAttack();
		}
	}

	CMonsterObject::Run();	
}

/* **************************************************************************************

		���� �ø��� 

   ************************************************************************************** */

void COmaObject::Run()
{	 
	if (!m_fIsDead && !m_fIsGhost)
	{
		if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
		{
			m_dwSearchEnemyTime = GetTickCount();
			MonsterNormalAttack();
		}
	}

	CMonsterObject::Run();	
}

/* **************************************************************************************

		��(������)

   ************************************************************************************** */

CRockManObject::CRockManObject()
{
//	m_dwSearchTick = 2500 + rand() % 1500;
//	m_dwSearchTime = GetTickCount();

	m_fHideMode = TRUE;
}

void CRockManObject::Run()
{	 
	if (!m_fIsDead && !m_fIsGhost)
	{
		if (m_fHideMode)
		{
			if (CheckComeOut(8))
				ComeOut();

			m_dwWalkTime = GetTickCount() + 1000;
		}
		else
		{
			if ((GetTickCount() - m_dwSearchEnemyTime > 8000) || ((GetTickCount() - m_dwSearchEnemyTime > 1000) && !m_pTargetObject))
			{
				m_dwSearchEnemyTime = GetTickCount();
				MonsterNormalAttack();

				if (!m_pTargetObject)
					ComeDown();
			}
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		������

   ************************************************************************************** */

CStickObject::CStickObject()
{
	m_dwSearchTick	= 2500 + rand() % 1500;

	m_fHideMode = TRUE;
}

void CStickObject::Run()
{	 
	if (!m_fIsDead && !m_fIsGhost)
	{
		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			m_dwWalkTime = GetTickCount();

			if (m_fHideMode)
			{
				if (CheckComeOut(4))
					ComeOut();
			}
			else
			{
				if (m_pTargetObject)
				{
					if (abs(m_nCurrX - m_pTargetObject->m_nCurrX) > 4 &&  abs(m_nCurrY - m_pTargetObject->m_nCurrY) > 4)
					{
						ComeDown();
						return;
					}
				}
				
				if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
					MonsterNormalAttack();
				
				if (!m_fHideMode)
				{
					if (AttackTarget())
						CMonsterObject::Run();
				}
			}
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		�� ����(���)

   ************************************************************************************** */

CSandMobObject::CSandMobObject()
{
	m_fHideMode = TRUE;
}

void CSandMobObject::Run()
{	 
	if (!m_fIsDead && !m_fIsGhost)
	{
		if (GetTickCount() - m_dwWalkTime > m_dwNextWalkTime)
		{
			m_dwWalkTime = GetTickCount();

			if (m_fHideMode)
			{
				if ((m_WAbility.HP > (m_WAbility.MaxHP / 20) && CheckComeOut(8)))
					m_dwAppearStart = GetTickCount();
			}
			else
			{
				if ((m_WAbility.HP > 0) && (m_WAbility.HP < (m_WAbility.MaxHP / 20)) && (GetTickCount() - m_dwAppearStart > 3000))
					ComeDown();
				else if (m_pTargetObject)
				{
					if (abs(m_nCurrX - m_pTargetObject->m_nCurrX) > 15 &&  abs(m_nCurrY - m_pTargetObject->m_nCurrY) > 15)
					{
						ComeDown();
						return;
					}
				}
				
				if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
					MonsterNormalAttack();
				
				if (!m_fHideMode)
				{
					if (AttackTarget())
					{
						CMonsterObject::Run();
					}
				}
			}
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		���

   ************************************************************************************** */

CWhiteSkeleton::CWhiteSkeleton()
{
//	m_dwSearchTick = 2500 + rand() % 1500;
//	m_dwSearchTime = GetTickCount();
	m_fIsFirst	= TRUE;
	m_fHideMode = TRUE;
}

void CWhiteSkeleton::ResetSkeleton()
{
//   NextHitTime := 3000 - (SlaveMakeLevel * 600);
//   NextWalkTime := 1200 - (SlaveMakeLevel * 250);
	m_dwWalkTime = GetTickCount() + 2000;	
}

void CWhiteSkeleton::Run()
{	 
	if (m_fIsFirst)
	{
		m_fIsFirst		= FALSE;
		m_nDirection	= 5;
		m_fHideMode		= FALSE;
		AddRefMsg(RM_DIGUP, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
		ResetSkeleton();
	}

	CGenneralMonObject::Run();
}

/* **************************************************************************************

		�ż� (������)

   ************************************************************************************** */

CElfMonster::CElfMonster()
{
	m_fNoAttackMode = TRUE;
	m_fIsFirst		= TRUE;
	m_fHideMode		= TRUE;
}

void CElfMonster::ResetElfMon()
{
//   NextHitTime := 3000 - (SlaveMakeLevel * 600);
//   NextWalkTime := 1200 - (SlaveMakeLevel * 250);
	m_dwWalkTime = GetTickCount() + 2000;	
}

void CElfMonster::AppearNow()
{
	m_fIsFirst		= FALSE;
	m_fHideMode		= FALSE;

	m_dwWalkTime = GetTickCount() + 800;
/*procedure TElfMonster.AppearNow;
begin
   bofirst := FALSE;
   HideMode := FALSE;
   //SendRefMsg (RM_TURN, Dir, CX, CY, 0, '');
   //Appear;
   //ResetElfMon;
   RecalcAbilitys;
   WalkTime := WalkTime + 800; //������ �ణ ������ ����
end;
*/
}

void CElfMonster::Run()
{	 
	if (m_fIsFirst)
	{
		m_fIsFirst		= FALSE;
		m_fHideMode		= FALSE;
		AddRefMsg(RM_DIGUP, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
		ResetElfMon();
	}

	if (m_fIsDead)
	{
		if (GetTickCount() - m_dwDeathTime > 2 * 1000)
			MakeGhost();
	}
	else
	{
		BOOL fChangeFace = FALSE;

		if (m_pTargetObject)
			fChangeFace = TRUE;

		if (m_pMasterObject)
		{
			if (m_pMasterObject->m_pTargetObject)// || m_pMasterObject->m_pLastHiter)
				fChangeFace = TRUE;
		}

		if (fChangeFace)
		{
			CElfWarriorMonster* pElfWarriorMon = dynamic_cast<CElfWarriorMonster*>(MakeClone(_MONSTER_ELFWARRIOR));

			if (pElfWarriorMon)
				pElfWarriorMon->AppearNow();

			m_pMasterObject = NULL;
			KickException();

			return;
		}
	}

	CMonsterObject::Run();
}

/* **************************************************************************************

		�ż� (������)

   ************************************************************************************** */

CElfWarriorMonster::CElfWarriorMonster()
{
	m_fIsFirst		= TRUE;
}

void CElfWarriorMonster::ResetElfMon()
{
//   NextHitTime := 3000 - (SlaveMakeLevel * 600);
//   NextWalkTime := 1200 - (SlaveMakeLevel * 250);
	m_dwWalkTime = GetTickCount() + 2000;	
}

void CElfWarriorMonster::AppearNow()
{
	m_fIsFirst		= FALSE;
	m_fHideMode		= FALSE;

	AddRefMsg(RM_DIGUP, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

	m_dwWalkTime = GetTickCount() + 800;
/*procedure TElfMonster.AppearNow;
begin
   bofirst := FALSE;
   HideMode := FALSE;
   //SendRefMsg (RM_TURN, Dir, CX, CY, 0, '');
   //Appear;
   //ResetElfMon;
   RecalcAbilitys;
   WalkTime := WalkTime + 800; //������ �ణ ������ ����
end;
*/
}

void CElfWarriorMonster::Run()
{	 
	if (m_fIsFirst)
	{
		m_fIsFirst		= FALSE;
		m_fHideMode		= FALSE;
		AddRefMsg(RM_DIGUP, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
		ResetElfMon();
	}

	if (m_fIsDead)
	{
		if (GetTickCount() - m_dwDeathTime > 2 * 1000)
			MakeGhost();
	}
	else
	{
		BOOL fChangeFace = TRUE;

		if (m_pTargetObject)
			fChangeFace = FALSE;

		if (m_pMasterObject)
		{
			if (m_pMasterObject->m_pTargetObject)// || m_pMasterObject->m_pLastHiter)
				fChangeFace = FALSE;
		}

		if (fChangeFace)
		{
			CElfMonster* pElfMon = dynamic_cast<CElfMonster*>(MakeClone(_MONSTER_ELFMONSTER));

			if (pElfMon)
			{
				AddRefMsg(RM_DIGDOWN, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
				AddRefMsg(RM_CHANGEFACE, 0, (int)this, (int)pElfMon, 0, NULL);
			
				pElfMon->AppearNow();
			}

			m_pMasterObject = NULL;
			KickException();
		}
	}

	CGenneralMonObject::Run();
}

/* **************************************************************************************

		ħ�Ź�

   ************************************************************************************** */

CSpitSpiderMonster::CSpitSpiderMonster()
{
}

void CSpitSpiderMonster::SpitAttack(int nDir)
{
	int nDamage;
	int nX, nY;

	m_nDirection = nDir;

	if (HIBYTE(m_WAbility.DC) - LOBYTE(m_WAbility.DC) + 1)
		nDamage = LOBYTE(m_WAbility.DC) + rand() % (HIBYTE(m_WAbility.DC) - LOBYTE(m_WAbility.DC) + 1);
	else
		nDamage = LOBYTE(m_WAbility.DC);

	if (nDamage <= 0) return;

	AddRefMsg(RM_HIT, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (g_SpitMap[nDir][i][k] == 1)
			{
				nX = m_nCurrX - 2 + k;
				nY = m_nCurrY - 2 + i;

				CCharObject* pCharObject = m_pMap->GetObject(nX, nY);

				if (pCharObject && pCharObject != this)
				{
					if (IsProperTarget(pCharObject))
					{
						if (pCharObject->m_btSpeedPoint)
						{
							if (rand() % pCharObject->m_btSpeedPoint < m_btHitPoint)
							{
								nDamage = GetMagStruckDamage(nDamage);

								if (nDamage > 0)
								{
									pCharObject->StruckDamage(nDamage);
									pCharObject->AddDelayProcess(pCharObject, RM_STRUCK, nDamage, pCharObject->m_WAbility.HP, 
																	pCharObject->m_WAbility.MaxHP, (int)this, NULL, 300);

/*                        if BoUsePoison then begin
                           //ü���� �����ϴ� ���� �ߵ� �ȴ�.
                           if Random(20 + cret.AntiPoison) = 0 then
                              cret.MakePoison (POISON_DECHEALTH, 30, 1);   //ü���� ����
                           //if Random(2) = 0 then
                           //   cret.MakePoison (POISON_STONE, 5);   //����
                        end; */

								}
							}
						}
					}
				}
			}
		}
	}
}

BOOL CSpitSpiderMonster::AttackTarget()
{
	int nTargetDir;

	if (m_pTargetObject)
	{
		if (TargetInSpitRange(nTargetDir))
		{
			if (GetTickCount() - m_dwHitTime > m_dwNextHitTime)
			{
				m_dwHitTime			= GetTickCount();
				m_dwTargetFocusTime = GetTickCount();
				SpitAttack(nTargetDir);
				BreakHolySeize();
			}

			return TRUE;
		}
		else
		{
			if (m_pTargetObject->m_pMap != m_pMap)
			{
				m_nTargetX = m_pTargetObject->m_nCurrX;
				m_nTargetY = m_pTargetObject->m_nCurrY;
			}
			else
			{
				m_pTargetObject = NULL;

				m_nTargetX = -1;
				m_nTargetY = -1;
			}
		}
	}

	return FALSE;
}
