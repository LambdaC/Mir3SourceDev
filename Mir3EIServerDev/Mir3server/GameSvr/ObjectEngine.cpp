#include "stdafx.h"

#define _RANGE_X			12
#define _RANGE_Y			12

#define _CACHE_TICK			500

#define HEALTHFILLTICK		1500
#define SPELLFILLTICK		800

CMagicInfo*		GetMagicInfo(int nMagicID);
CMirMap*		GetMap(char *pszMapName);

CMonsterObject* AddCreature(CMirMap* pMap, int nX, int nY, int nMonRace, BOOL fSearch);

CCharObject::CCharObject(CUserInfo*	pUserInfo)
{ 
//	InitializeCriticalSection(&m_cs);

	m_pUserInfo					= pUserInfo;

	m_nCurrX					= 0;
	m_nCurrY					= 0;

	ZeroMemory(m_szName, sizeof(m_szName));

	m_dwHealthTick				= 0;
	m_dwSpellTick				= 0;
	m_dwTickSec					= 0;

	m_fOpenHealth				= FALSE;

	m_nCharStatusEx				= 0;
	m_nCharStatus				= 0;

	m_IncHealing				= 0;
	m_IncHealth					= 0;
	m_IncSpell					= 0;

	m_btPerHealing				= 5;
	m_btPerHealth				= 5;
	m_btPerSpell				= 5;

	m_dwIncHealthSpellTime		= 0;

	m_dwTickSec					= GetTickCount();

	m_nEvent					= -1; // No Event

	ZeroMemory(m_wStatusArr, sizeof(m_wStatusArr));
	ZeroMemory(m_szName, sizeof(m_szName));

	m_sHitSpeed					= 0;

	m_fAbilMagBubbleDefence		= FALSE;
	m_btMagBubbleDefenceLevel	= 0;

	m_fInspector				= FALSE;
	m_fFastTrain				= FALSE;

	m_IncHealth					= 0;
	m_IncSpell					= 0;

	m_fIsGhost					= FALSE;
	m_fIsNeverDie				= FALSE;

	m_btSpeedPoint				= DEFSPEED;

	m_fHumHideMode				= FALSE;
	m_fFixedHideMode			= FALSE;

	m_fStoneMode				= FALSE;
	m_fStickMode				= FALSE;

	m_pMasterObject				= NULL;
	m_pTargetObject				= NULL;
}

CCharObject::~CCharObject()
{
	PLISTNODE		pListNode = m_xVisibleObjectList.GetHead();

	while (pListNode)
	{
		CVisibleObject* pVisibleObject = m_xVisibleObjectList.GetData(pListNode);

		if (pVisibleObject) 
		{
			delete pVisibleObject;
			pVisibleObject = NULL;
		}

		pListNode = m_xVisibleObjectList.RemoveNode(pListNode);
	} // while (pListNode)

//	DeleteCriticalSection(&m_cs);
}

void CCharObject::SelectTarget(CCharObject* pTargetObject)
{
	m_pTargetObject			= pTargetObject;
	m_dwTargetFocusTime		= GetTickCount();
}

void CCharObject::GetFrontPosition(int &nX, int &nY)
{
	int nHeight = m_pMap->m_stMapFH.shHeight;
	int nWidth	= m_pMap->m_stMapFH.shWidth;

	nX = m_nCurrX;
	nY = m_nCurrY;

	switch (m_nDirection)
	{
		case DR_UP:
			if (nY > 0) nY--;
			break;
		case DR_DOWN:
			if (nY < nHeight - 1) nY++;
			break;
		case DR_LEFT:
			if (nX > 0) nX--;
			break;
		case DR_RIGHT:
			if (nX < nWidth - 1) nX++;
			break;
		case DR_UPLEFT:
		{
            if (nX > 0 && nY > 0)
			{
               nX--;
               nY--;
            }

			break;
		}
		case DR_UPRIGHT:
		{
            if (nX > 0 && nY < nHeight - 1)
			{
               nX++;
               nY--;
			}

			break;
		}
		case DR_DOWNLEFT:
		{
            if (nX < nWidth - 1 && nY > 0)
			{
               nX--;
               nY++;
            }

			break;
		}
		case DR_DOWNRIGHT:
		{
            if (nX < nWidth - 1 && nY < nHeight - 1)
			{
               nX++;
               nY++;
            }

			break;
		}
	}
}

int CCharObject::GetBack(int nDirection)
{
	switch (nDirection)
	{
		case DR_UP:
			return DR_DOWN;
		case DR_DOWN:
			return DR_UP;
		case DR_LEFT:
			return DR_RIGHT;
		case DR_RIGHT:
			return DR_LEFT;
		case DR_UPLEFT:
			return DR_DOWNRIGHT;
		case DR_UPRIGHT:
			return DR_DOWNLEFT;
		case DR_DOWNLEFT:
			return DR_UPRIGHT;
		case DR_DOWNRIGHT:
			return DR_UPLEFT;
	}

	return nDirection;
}

BOOL CCharObject::GetBackPosition(int &nX, int &nY)
{
	int nHeight = m_pMap->m_stMapFH.shHeight;
	int nWidth	= m_pMap->m_stMapFH.shWidth;

	nX = m_nCurrX;
	nY = m_nCurrY;

	switch (m_nDirection)
	{
		case DR_UP:
			if (nY < nHeight - 1) nY++;
			break;
		case DR_DOWN:
			if (nY > 0) nY--;
			break;
		case DR_LEFT:
			if (nX < nWidth - 1) nX++;
			break;
		case DR_RIGHT:
			if (nX > 0) nX--;
			break;
		case DR_UPLEFT:
			if ((nX < nWidth - 1) && (nY < nHeight - 1))
			{
				nX++;
				nY++;
			}

			break;
		case DR_UPRIGHT:
			if ((nX < nWidth - 1) && (nY > 0))
			{
				nX--;
				nY++;
			}

			break;
		case DR_DOWNLEFT:
			if ((nX > 0) && (nY < nHeight - 1))
			{
				nX++;
				nY--;
			}

			break;
		case DR_DOWNRIGHT:
			if ((nX > 0) && (nY > 0))
			{
				nX--;
				nY--;
			}

			break;
	}

	return TRUE;
}

BOOL CCharObject::IsProperTarget(CCharObject* pTargetObject)
{
//	if target.BoSysopMode or target.BoStoneMode then  //���...
//       Result := FALSE;

	return TRUE;
}

BOOL CCharObject::IsFriend(CCharObject* pCharObject)
{
	if (pCharObject->m_wObjectType & _OBJECT_HUMAN)
	{
		if (pCharObject->m_pUserInfo)
		{
			switch (pCharObject->m_pUserInfo->GetAttackMode())
			{
				case HAM_ALL:
					return TRUE;
				case HAM_PEACE:
					return TRUE;
			}
		}
	}
/*   function IsFriend (cret: TCreature): Boolean;
   begin
      Result := FALSE;
      if cret.RaceServer = RC_USERHUMAN then begin  //����� ����� ��츸
         //�������� ������ ���� �ٸ�
         case HumAttackMode of
            HAM_ALL:  Result := TRUE;
            HAM_PEACE: Result := TRUE;
            HAM_GROUP:
               begin
                  if cret = self then
                     Result := TRUE;
                  if IsGroupMember (cret) then
                     Result := TRUE;
               end;
            HAM_GUILD:
               begin
                  if cret = self then
                     Result := TRUE;
                  if MyGuild <> nil then begin
                     if TGuild(MyGuild).IsMember(cret.UserName) then
                        Result := TRUE;
                     if BoGuildWarArea and (cret.MyGuild <> nil) then begin  //������,������ ������ ����
                        if TGuild(MyGuild).IsAllyGuild(TGuild(cret.MyGuild)) then
                           Result := TRUE;
                     end;
                  end;
               end;
            HAM_PKATTACK:
               begin
                  if cret = self then Result := TRUE;
                  if PKLevel >= 2 then begin //���� ������
                     if cret.PKLevel < 2 then Result := TRUE;
                  end else begin  //���� �����
                     if cret.PKLevel >= 2 then Result := TRUE;
                  end;
               end;
         end;
      end;
   end;
*/
	return FALSE;
}

BOOL CCharObject::IsProperFriend(CCharObject* pCharObject)
{
	BOOL fFlag = FALSE;

	if (pCharObject)
	{
		if (m_wObjectType & _OBJECT_ANIMAL)
		{
			if (pCharObject->m_wObjectType & _OBJECT_ANIMAL)
				fFlag = TRUE;

			if (pCharObject->m_pMasterObject)
				fFlag = FALSE;
		}
		else
		{
			if (m_wObjectType & _OBJECT_HUMAN)
			{
				fFlag = IsFriend(pCharObject);

				if (pCharObject->m_wObjectType & _OBJECT_ANIMAL)
				{
					if (pCharObject->m_pMasterObject == this)
						fFlag = TRUE;
					else if (pCharObject->m_pMasterObject)
						fFlag = IsFriend(pCharObject->m_pMasterObject);

				}
			}
			else
				fFlag = TRUE;
		}
	}

	return fFlag;
}

UINT CCharObject::GetCharStatus()
{
	UINT s = 0;

	for (int i = 0; i < MAX_STATUS_ATTRIBUTE; i++)
	{
		if (m_wStatusArr[i] > 0)
			s |= (0x80000000 >> i);
	}

	return (s | (m_nCharStatusEx & 0x000FFFFF));
}

BOOL CCharObject::RestoreHealSpell()
{
	if (m_fIsNeverDie)
	{
		m_WAbility.HP = m_WAbility.MaxHP;
		m_WAbility.MP = m_WAbility.MaxMP;
	}

	int n = (GetTickCount() - m_dwTickSec) / 20;  //�ʴ� 50
	
	m_dwTickSec = GetTickCount();

	m_dwHealthTick += n;
	m_dwSpellTick  += n;

	if (!m_fIsDead)
	{
		int		nPlus = 0;
		BOOL 	fHealthSpellChanged = FALSE;

		if (m_WAbility.HP < m_WAbility.MaxHP)
		{
            if (m_dwHealthTick >= HEALTHFILLTICK)
			{
               nPlus = m_WAbility.MaxHP / 15 + 1;
               
				if (m_WAbility.HP + nPlus < m_WAbility.MaxHP)
					m_WAbility.HP = m_WAbility.HP + nPlus;
				else 
					m_WAbility.HP = m_WAbility.MaxHP;

				fHealthSpellChanged = TRUE;
            }
		}

		if (m_WAbility.MP < m_WAbility.MaxMP)
		{
            if (m_dwSpellTick >= SPELLFILLTICK)
			{
               nPlus = m_WAbility.MaxMP / 18 + 1;
               
				if (m_WAbility.MP + nPlus < m_WAbility.MaxMP)
					m_WAbility.MP = m_WAbility.MP + nPlus;
				else 
					m_WAbility.MP = m_WAbility.MaxMP;

				fHealthSpellChanged = TRUE;
            }
		}
	
		if (m_WAbility.HP == 0)
		{
			return TRUE;
		}
/*        if WAbil.HP = 0 then begin
            if BoAbilRevival then begin //��� �ɷ��� �ִ�.
               if GetTickCount - LatestRevivalTime > 60 * 1000 then begin
                  LatestRevivalTime := GetTickCount;
                  //������ ��� �Ѵ�.
                  ItemDamageRevivalRing;
                  WAbil.HP := WAbil.MaxHP;
                  HealthSpellChanged;
                  SysMsg ('������ ������ ���� ����Ǿ����ϴ�.', 1);
               end;
            end;
            if WAbil.HP = 0 then
               Die;
         end;	*/

		if (fHealthSpellChanged)
			HealthSpellChanged();

		if (m_dwHealthTick >= HEALTHFILLTICK)
			m_dwHealthTick = 0;
		if (m_dwSpellTick >= SPELLFILLTICK)
			m_dwSpellTick = 0;
	}
	else
	{
		if (GetTickCount() - m_dwDeathTime > 3 * 60 * 1000)
			MakeGhost();

		return FALSE;
	}

	if ((!m_fIsDead) && (m_IncSpell > 0) || (m_IncHealth > 0) || (m_IncHealing > 0))
	{
		int		nHP = 0, nMP = 0;

		DWORD	inchstime = 600 - _MIN(400, m_Ability.Level * 10);

		if (GetTickCount() - m_dwIncHealthSpellTime >= inchstime)
		{
			n = _MIN(200, (GetTickCount() - m_dwIncHealthSpellTime) - inchstime);

			m_dwIncHealthSpellTime = GetTickCount() + n;

			if ((m_IncSpell > 0) || (m_IncHealth > 0) || (m_IncHealing > 0))
			{
				if (m_btPerHealing <= 0) m_btPerHealing = 1;
				if (m_btPerSpell <= 0) m_btPerSpell = 1;
				if (m_btPerHealth <= 0) m_btPerHealth = 1;

				if (m_IncHealth < m_btPerHealth)
				{
					nHP += m_IncHealth;
					m_IncHealth = 0;
				}
				else
				{
					nHP += m_btPerHealth;
					m_IncHealth = m_IncHealth - m_btPerHealth;
				}		

				if (m_IncSpell < m_btPerSpell)
				{
					nMP += m_IncSpell;
					m_IncSpell = 0;
				}
				else
				{
					nHP += m_btPerSpell;
					m_IncSpell = m_IncSpell - m_btPerSpell;
				}		

				if (m_IncHealing < m_btPerHealing)
				{
					nHP += m_IncHealing;
					m_IncHealing = 0;
				}
				else
				{
					nHP += m_btPerHealing;
					m_IncHealing = m_IncHealing - m_btPerHealing;
				}		
			}

			m_btPerHealing	= 5;
			m_btPerHealth	= 5 + (m_Ability.Level / 10);
			m_btPerSpell	= 5 + (m_Ability.Level / 10);

			IncHealthSpell(nHP, nMP);

			if (m_WAbility.HP == m_WAbility.MaxHP)
			{
				m_IncHealth		= 0;
				m_IncHealing	= 0;
			}

			if (m_WAbility.MP == m_WAbility.MaxMP)
				m_IncSpell		= 0;
		}
	}
	else
		m_dwIncHealthSpellTime = GetTickCount();

	if	((int)m_dwHealthTick < -HEALTHFILLTICK)
	{
		if (m_WAbility.HP > 1)
		{
			m_WAbility.HP--;
			m_dwHealthTick += HEALTHFILLTICK;

			HealthSpellChanged();
		}
	}

	return FALSE;
}

/*
procedure TCreature.ScatterGolds;
const
   ONEDROP = 10000;
var
   i, ngold: integer;
begin
   if Gold > 0 then begin
      for i:=0 to 8 do begin
         if Gold > ONEDROP then begin
            ngold := ONEDROP;
            Gold := Gold - ONEDROP;
         end else begin
            ngold := Gold;
            Gold := 0;
         end;
         if ngold > 0 then begin
            if not DropGoldDown (ngold, TRUE) then begin
               Gold := Gold + ngold;
               break;
            end;
         end else break;
      end;
      GoldChanged;
   end;
end;
*/
BOOL CCharObject::DropItemDown(_LPTUSERITEMRCD lpTItemRcd, int nRange, BOOL fIsGenItem)
{
	CMapItem* xpMapItem = new CMapItem;

	xpMapItem->nCount = 1;

	if (fIsGenItem)
	{
		_LPTGENERALITEMRCD lpTGenItemRcd = NULL;
		
		lpTGenItemRcd = (_LPTGENERALITEMRCD)lpTItemRcd;

		xpMapItem->wLooks		= (WORD)g_pStdItemEtc[lpTGenItemRcd->nStdIndex].dwLooks;
		xpMapItem->btAniCount	= (BYTE)0;
		
		xpMapItem->pItem		= (LONG)lpTGenItemRcd;
		memmove(xpMapItem->szName, g_pStdItemEtc[lpTGenItemRcd->nStdIndex].szName, memlen(g_pStdItemEtc[lpTGenItemRcd->nStdIndex].szName));
	}
	else
	{
		xpMapItem->wLooks		= (WORD)g_pStdItemSpecial[lpTItemRcd->nStdIndex].dwLooks;
		xpMapItem->btAniCount	= (BYTE)g_pStdItemSpecial[lpTItemRcd->nStdIndex].wAniCount;
		
		xpMapItem->pItem		= (LONG)lpTItemRcd;
		
		if (strlen(lpTItemRcd->szPrefixName))
		{
			strcpy(xpMapItem->szName, lpTItemRcd->szPrefixName);
			strcat(xpMapItem->szName, " ");
			strcat(xpMapItem->szName, g_pStdItemSpecial[lpTItemRcd->nStdIndex].szName);
		}
		else
			strcpy(xpMapItem->szName, g_pStdItemSpecial[lpTItemRcd->nStdIndex].szName);
	}

	int nX, nY;

	m_pMap->GetDropPosition(m_nCurrX, m_nCurrY, nRange, nX, nY);
	m_pMap->AddNewObject(nX, nY, OS_ITEMOBJECT, (VOID *)xpMapItem);

	AddRefMsg(RM_ITEMSHOW, xpMapItem->wLooks, (int)xpMapItem, nX, nY, xpMapItem->szName);

	return TRUE;
}
/*
function  TCreature.DropItemDown (ui: TUserItem; scatterrange: integer; diedrop: Boolean): Boolean;
var
   dx, dy, idura: integer;
   pmi, pr: PTMapItem;
   ps: PTStdItem;
   logcap: string;
begin
   Result := FALSE;
   ps := UserEngine.GetStdItem (ui.Index);
   if ps <> nil then begin

      if ps.StdMode = 40 then begin //��⸦ ���� ����߸� ��� ��� ǰ���� ��������.
         idura := ui.Dura; //word�̹Ƿ�.
         idura := idura - 2000; //��� ǰ���� ��������.
         if idura < 0 then idura := 0;
         ui.Dura := idura;
      end;

      new (pmi);
      pmi.UserItem := ui;
      pmi.Name := ps.Name;
      pmi.Looks := ps.Looks;
      if ps.StdMode = 45 then begin  //�ֻ���, ����
         pmi.Looks := GetRandomLook (pmi.Looks, ps.Shape);
      end;
      pmi.AniCount := ps.AniCount;
      pmi.Reserved := 0;
      pmi.Count := 1;
      GetDropPosition (CX, CY, scatterrange, dx, dy);
      pr := Penvir.AddToMap (dx, dy, OS_ITEMOBJECT, TObject (pmi));  //�Ѽ��� 5�� �̻��� �������� ������ �����Ѵ�.
      if pr = pmi then begin
         //�������� �߰� �ƴϸ� ����..
         SendRefMsg (RM_ITEMSHOW, pmi.Looks, integer(pmi), dx, dy, pmi.Name);
         //����߸�
         if diedrop then logcap := '����_'
         else logcap := '����_';
         if not IsCheapStuff (ps.StdMode) then
            AddUserLog (logcap +
                        MapName + '_' +
                        IntToStr(CX) + '_' +
                        IntToStr(CY) + '_' +
                        BoolToStr(RaceServer = RC_USERHUMAN) + '_' +
                        UserName + '_' +
                        UserEngine.GetStdItemName (ui.Index) + '_' +
                        IntToStr(ui.MakeIndex));
         Result := TRUE;
      end else begin
         //�����ΰ��
         Dispose (pmi);
      end;
   end;
end;
}
*/

void CCharObject::Run()
{
	if (m_fOpenHealth)
	{
		if (GetTickCount() - m_dwOpenHealthStart > m_dwOpenHealthTime)
			BreakOpenHealth();
	}

	BOOL fChg = FALSE;
	BOOL fNeedRecalc = FALSE;

	for (int i = 0; i < MAX_STATUS_ATTRIBUTE; i++)
	{
		if (m_wStatusArr[i] > 0 && m_wStatusArr[i] < 60000)
		{
			if (GetTickCount() - m_dwStatusTime[i] > 1000)
			{
				m_wStatusArr[i]		-= 1;
				m_dwStatusTime[i]	+= 1000;

				if (m_wStatusArr[i] == 0)
				{
					fChg = TRUE;

					switch (i)
					{
						case STATE_DEFENCEUP:
							fNeedRecalc = TRUE;
							SysMsg("���� ��� ����", 1);
							break;
                        case STATE_MAGDEFENCEUP:
							fNeedRecalc = TRUE;
							SysMsg("���׷� ��� ����", 1);
							break;
/*                        case STATE_TRANSPARENT:
                           begin
                              BoHumHideMode := FALSE;
                           end; */
                        case STATE_BUBBLEDEFENCEUP:
							m_fAbilMagBubbleDefence = FALSE;
							break;
					}
				}
			}
		}
	}

	if (fChg)
	{
		m_nCharStatus = GetCharStatus();
		AddRefMsg(RM_CHARSTATUSCHANGED, m_sHitSpeed/*wparam*/, m_nCharStatus, 0, 0, NULL);
	}

	if (fNeedRecalc)
	{
		((CPlayerObject*)this)->RecalcAbilitys();
		AddProcess(this, RM_ABILITY, 0, 0, 0, 0, NULL);
	}
}

void CCharObject::Die()
{
	if (m_fIsNeverDie) return;

	m_IncHealing	= 0;
	m_IncHealth		= 0;
	m_IncSpell		= 0;

	m_dwDeathTime	= GetTickCount();

	if (m_wObjectType & (_OBJECT_ANIMAL | _OBJECT_HUMAN))
		AddRefMsg(RM_DEATH, m_nDirection, m_nCurrX, m_nCurrY, 1, NULL);

	m_fIsDead		= TRUE;
/*
   try
      boPK := FALSE;
      if (not BoVentureServer) and (not PEnvir.FightZone) and (not PEnvir.Fight3Zone) then begin
         //PK���� ������ ���
         if (RaceServer = RC_USERHUMAN) and (LastHiter <> nil) and (PKLevel < 2) then begin
            //�����ڰ� ���, ������ ����, �����ڰ� PK�ƴ�
            if LastHiter.RaceServer = RC_USERHUMAN then
               boPK := TRUE;
            if LastHiter.Master <> nil then
               if LastHiter.Master.RaceServer = RC_USERHUMAN then begin
                  LastHiter := LastHiter.Master; //������ ���� ������ ����
                  boPK := TRUE;
               end;
         end;
      end;

      if boPK and (LastHiter <> nil) then begin
         //����� ���� ���, ���輭�������� �ش�ȵ�
         //����� ������ ����� ����.

         //���������� ����
         guildwarkill := FALSE;
         if (MyGuild <> nil) and (LastHiter.MyGuild <> nil) then begin
            //�Ѵ� ���Ŀ� ���Ե� ���¿���
            if GetGuildRelation (self, LastHiter) = 2 then  //������ ����
               guildwarkill := TRUE;  //���������� ����, ������ �ȵ�
         end;

         //���������� ����
         if UserCastle.BoCastleUnderAttack then
            if (BoInFreePKArea) or (UserCastle.IsCastleWarArea (PEnvir, CX, CY)) then
               guildwarkill := TRUE;

         if not guildwarkill then begin //���������� ����
            if not LastHiter.IsGoodKilling(self) then begin
               LastHiter.IncPkPoint (100); //
               LastHiter.SysMsg ('����� ������ �Ͽ����ϴ�.', 0);
               //������ ��� ��� ����
               LastHiter.AddBodyLuck (-500);
               if PkLevel < 1 then //���� ����� ���� ���
                  if Random(5) = 0 then //������ �ϸ� ���Ⱑ ���ָ� �޴´�.
                     LastHiter.MakeWeaponUnlock;
            end else
               LastHiter.SysMsg ('[������ ��Ģ�� ���� ��ȣ��]', 1);
         end;

      end;
   except
      MainOutMessage ('[Exception] TCreature.Die 2');
   end;

   try
      if (not PEnvir.FightZone) and
         (not PEnvir.Fight3Zone) and
         (not BoAnimal) then begin //�����̸� ���� ��Ⱑ ���´�.
         DropUseItems;
         if (Master = nil) and (not BoNoItem) then
            ScatterBagItems;  //�����ִ� ���� ������ �긮�� ����
         if (RaceServer >= RC_ANIMAL) and (Master = nil) and (not BoNoItem) then
            ScatterGolds;
         //���� ��� ���ġ ����
         AddBodyLuck ( - (50 - (50 - Abil.Level * 5)));
      end;

      //���� ���� ��
      if PEnvir.Fight3Zone then begin
         //3�� �׾ �Ǵ� ����� ���
         Inc (FightZoneDieCount);
         if MyGuild <> nil then begin
            TGuild(MyGuild).TeamFightWhoDead (UserName);
         end;

         //���� ���
         if (LastHiter <> nil) then begin
            if (LastHiter.MyGuild <> nil) and (MyGuild <> nil) then begin
               TGuild(LastHiter.MyGuild).TeamFightWhoWinPoint (LastHiter.UserName, 100);  //matchpoint ����, ���μ��� ���
               str := TGuild(LastHiter.MyGuild).GuildName + ':' +
                      IntToStr(TGuild(LastHiter.MyGuild).MatchPoint) + '  ' +
                      TGuild(MyGuild).GuildName + ':' +
                      IntToStr(TGuild(MyGuild).MatchPoint);
               UserEngine.CryCry (RM_CRY, PEnvir, CX, CY, 10000, '- ' + str);  //���� ��ü���� �˸���.
            end;
         end;
      end;

      //�α׸� �����.
      if RaceServer = RC_USERHUMAN then begin
         if LastHiter <> nil then begin
            if LastHiter.RaceServer = RC_USERHUMAN then str := LastHiter.UserName
            else str := '#' + LastHiter.UserName;
         end else str := '####';
         AddUserLog ('����_' +
                     MapName + '_' +
                     IntToStr(CX) + '_' +
                     IntToStr(CY) + '_' +
                     UserName + '_' +
                     str + '_' +
                     'FZ-' + BoolToStr(PEnvir.FightZone) + '_' +
                     'F3-' + BoolToStr(PEnvir.Fight3Zone));
      end;

      SendRefMsg (RM_DEATH, Dir, CX, CY, 1, '');
   except
      MainOutMessage ('[Exception] TCreature.Die 3');
   end;
end;
*/
}

BOOL CCharObject::GetAvailablePosition(CMirMap* pMap, int &nX, int &nY, int nRange)
{
	if (pMap->CanMove(nX, nY))
		return TRUE;

	int nOrgX		= nX;
	int nOrgY		= nY;
	int nLoonCnt	= (4 * nRange) * (nRange + 1);

	for (int i = 0; i < nLoonCnt; i++)
	{
		nX = nOrgX + g_SearchTable[i].x;
		nY = nOrgY + g_SearchTable[i].y;

		if (pMap->CanMove(nX, nY))
			return TRUE;
	}
	
	nX = nOrgX;
	nY = nOrgY;

	return FALSE;
}

BOOL CCharObject::GetNextPosition(int nSX, int nSY, int nDir, int nDistance, int& nX, int& nY)
{
	nX = nSX;
	nY = nSY;

	switch (nDir)
	{
		case DR_UP:
			if (nY > (nDistance - 1)) nY -= nDistance;
			break;
		case DR_DOWN:
			if (nY < m_pMap->m_stMapFH.shHeight - nDistance) nY += nDistance;
			break;
		case DR_LEFT:
			if (nX > (nDistance - 1)) nX -= nDistance;
			break;
		case DR_RIGHT:
			if (nX < m_pMap->m_stMapFH.shWidth - nDistance) nX += nDistance;
			break;
		case DR_UPLEFT:
		{
			if ((nX > nDistance - 1) && (nY > nDistance - 1))
			{
				nX -= nDistance;
				nY -= nDistance;
			}

			break;
		}
		case DR_UPRIGHT:
		{
			if ((nX > nDistance - 1) && (nY < m_pMap->m_stMapFH.shHeight - nDistance))
			{
				nX += nDistance;
				nY -= nDistance;
			}

			break;
		}
		case DR_DOWNLEFT:
		{
			if ((nX < m_pMap->m_stMapFH.shWidth - nDistance) && (nY > nDistance - 1))
			{
				nX -= nDistance;
				nY += nDistance;
			}

			break;
		}
		case DR_DOWNRIGHT:
		{
			if ((nX < m_pMap->m_stMapFH.shWidth - nDistance) && (nY < m_pMap->m_stMapFH.shHeight - nDistance))
			{
				nX += nDistance;
				nY += nDistance;
			}

			break;
		}
	}

	if ((m_nCurrX == nX) && (m_nCurrY == nY))
		return FALSE;

	return TRUE;
}

int	CCharObject::GetNextDirection(int nStartX, int nStartY, int nTargetX, int nTargetY)
{
	int nFlagX, nFlagY;

	if (nStartX < nTargetX) nFlagX = 1;
	else if (nStartX == nTargetX) nFlagX = 0;
	else
		nFlagX = -1;

	if (abs(nStartY - nTargetY) > 2)
	{
		if ((nStartY >= nTargetY - 1) && (nStartY <= nTargetY + 1))
			nFlagX = 0;
	}

	if (nStartY < nTargetY) nFlagY = 1;
	else if (nStartY == nTargetY) nFlagY = 0;
	else
		nFlagY = -1;

	if (abs(nStartX - nTargetX) > 2)
	{
		if ((nStartX >= nTargetX - 1) && (nStartX <= nTargetX + 1))
			nFlagY = 0;
	}

	if ((nFlagX == 0) && (nFlagY == -1)) return DR_UP;
	else if ((nFlagX == 1) && (nFlagY == -1)) return DR_UPRIGHT;
	else if ((nFlagX == 1) && (nFlagY == 0)) return DR_RIGHT;
	else if ((nFlagX == 1) && (nFlagY == 1)) return DR_DOWNRIGHT;
	else if ((nFlagX == 0) && (nFlagY == 1)) return DR_DOWN;
	else if ((nFlagX == -1) && (nFlagY == 1)) return DR_DOWNLEFT;
	else if ((nFlagX == -1) && (nFlagY == 0)) return DR_LEFT;
	else if ((nFlagX == -1) && (nFlagY == -1)) return DR_UPLEFT;

	return DR_DOWN;
}

CCharObject* CCharObject::GetFrontObject()
{
	int nX, nY;

	GetFrontPosition(nX, nY);

	CCharObject* pCharObject = m_pMap->GetObject(nX, nY);

	if (pCharObject)
		return pCharObject;

	return NULL;
}

void CCharObject::UpdateDelayProcessCheckParam1(CCharObject* pCharObject, WORD wIdent, WORD wParam, DWORD lParam1, DWORD lParam2, DWORD lParam3, char *pszData, int nDelay)
{
	_LPTPROCESSMSG	lpProcessMsg;

	int nCount = m_DelayProcessQ.GetCount();

	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			lpProcessMsg = (_LPTPROCESSMSG)m_DelayProcessQ.PopQ();

			if (lpProcessMsg)
			{
				if (lpProcessMsg->wIdent == wIdent && lpProcessMsg->lParam1 == lParam1)
				{
					if (lpProcessMsg->pszData)
					{
						delete [] lpProcessMsg->pszData;
						lpProcessMsg->pszData = NULL;
					}
					
					delete lpProcessMsg;
					lpProcessMsg = NULL;
				}
				else
					m_DelayProcessQ.PushQ((BYTE *)lpProcessMsg);
			}
		}
	}

	AddDelayProcess(pCharObject, wIdent, wParam, lParam1, lParam2, lParam3, pszData, nDelay);
}

void CCharObject::UpdateProcess(CCharObject* pCharObject, WORD wIdent, WORD wParam, DWORD lParam1, DWORD lParam2, DWORD lParam3, char *pszData)
{
	_LPTPROCESSMSG	lpProcessMsg;

//	EnterCriticalSection(&m_cs);

	int nCount = m_ProcessQ.GetCount();

	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			lpProcessMsg = (_LPTPROCESSMSG)m_ProcessQ.PopQ();

			if (lpProcessMsg)
			{
				if (lpProcessMsg->wIdent == wIdent)
				{
					if (lpProcessMsg->pszData)
					{
						delete [] lpProcessMsg->pszData;
						lpProcessMsg->pszData = NULL;
					}
					
					delete lpProcessMsg;
					lpProcessMsg = NULL;
				}
				else
					m_ProcessQ.PushQ((BYTE *)lpProcessMsg);
			}
		}
	}

//	LeaveCriticalSection(&m_cs);

	AddProcess(pCharObject, wIdent, wParam, lParam1, lParam2, lParam3, pszData);
}

void CCharObject::AddProcess(CCharObject* pCharObject, WORD wIdent, WORD wParam, DWORD lParam1, DWORD lParam2, DWORD lParam3, char *pszData)
{
//	EnterCriticalSection(&m_cs);

	_LPTPROCESSMSG lpProcessMsg = new _TPROCESSMSG;

	if (!m_fIsGhost)
	{
		if (lpProcessMsg)
		{
			lpProcessMsg->wIdent			= wIdent;
			lpProcessMsg->wParam			= wParam;
			lpProcessMsg->lParam1			= lParam1;
			lpProcessMsg->lParam2			= lParam2;
			lpProcessMsg->lParam3			= lParam3;

			lpProcessMsg->dwDeliveryTime	= 0;

			lpProcessMsg->pCharObject		= pCharObject;

			if (pszData)
			{
				int nLen = memlen(pszData);

				lpProcessMsg->pszData = new char[nLen];
				memmove(lpProcessMsg->pszData, pszData, nLen);
			}
			else
				lpProcessMsg->pszData		= NULL;

			m_ProcessQ.PushQ((BYTE *)lpProcessMsg);
		}
	}

//	LeaveCriticalSection(&m_cs);
}

void CCharObject::AddDelayProcess(CCharObject* pCharObject, WORD wIdent, WORD wParam, DWORD lParam1, DWORD lParam2, DWORD lParam3, char *pszData, int nDelay)
{
//	EnterCriticalSection(&m_cs);

	_LPTPROCESSMSG lpProcessMsg = new _TPROCESSMSG;

	if (lpProcessMsg)
	{
		lpProcessMsg->wIdent			= wIdent;
		lpProcessMsg->wParam			= wParam;
		lpProcessMsg->lParam1			= lParam1;
		lpProcessMsg->lParam2			= lParam2;
		lpProcessMsg->lParam3			= lParam3;

		lpProcessMsg->dwDeliveryTime	= GetTickCount() + nDelay;

		lpProcessMsg->pCharObject		= pCharObject;

		if (pszData)
		{
			int nLen = memlen(pszData);

			lpProcessMsg->pszData = new char[nLen];
			memmove(lpProcessMsg->pszData, pszData, nLen);
		}
		else
			lpProcessMsg->pszData		= NULL;

		m_DelayProcessQ.PushQ((BYTE *)lpProcessMsg);
	}

//	LeaveCriticalSection(&m_cs);
}

void CCharObject::AddRefMsg(WORD wIdent, WORD wParam, DWORD lParam1, DWORD lParam2, DWORD lParam3, char *pszData)
{
	CMapCellInfo*	pMapCellInfo	= NULL;
	CCharObject*	pCharObject		= NULL;

	int nStartX = m_nCurrX - _RANGE_X;
	int nEndX	= m_nCurrX + _RANGE_X;
	int nStartY = m_nCurrY - _RANGE_Y;
	int nEndY	= m_nCurrY + _RANGE_Y;

	if (m_fInspector) return;

	if (GetTickCount() - m_dwCacheTick > _CACHE_TICK || m_xCacheObjectList.GetCount() == 0)
	{
		m_xCacheObjectList.Clear();

		for (int x = nStartX; x <= nEndX; x++)
		{
			for (int y = nStartY; y <= nEndY; y++)
			{
				if (pMapCellInfo = m_pMap->GetMapCellInfo(x, y))
				{
					if (pMapCellInfo->m_xpObjectList)
					{
						if (pMapCellInfo->m_xpObjectList->GetCount())
						{
							PLISTNODE pListNode = pMapCellInfo->m_xpObjectList->GetHead();

							while (pListNode)
							{
								_LPTOSOBJECT pOSObject = pMapCellInfo->m_xpObjectList->GetData(pListNode);

								if (pOSObject->btType == OS_MOVINGOBJECT)
								{
									pCharObject = (CCharObject*)pOSObject->pObject;

									if (!pCharObject->m_fIsGhost)
									{
										if (pCharObject->m_wObjectType & _OBJECT_HUMAN)
										{	
											pCharObject->AddProcess(this, wIdent, wParam, lParam1, lParam2, lParam3, pszData);					
											m_xCacheObjectList.AddNewNode(pCharObject);
										}
									}
								}
								
								pListNode = pMapCellInfo->m_xpObjectList->GetNext(pListNode);
							} // while (pListNode)
						} // if (pMapCellInfo->m_pObjectList.GetCount())
					}
				} // if (pMapCellInfo)
			}// for (y)
		} // for (x)

		m_dwCacheTick = GetTickCount();
	}
	else
	{
		PLISTNODE pListNode = m_xCacheObjectList.GetHead();

		while (pListNode)
		{
			CCharObject* pCharObject = m_xCacheObjectList.GetData(pListNode);

			if (!pCharObject->m_fIsGhost)
			{
				if ((pCharObject->m_pMap = m_pMap) && (abs(pCharObject->m_nCurrX - m_nCurrX) <= 11) && 
					(abs(pCharObject->m_nCurrY - m_nCurrY) <= 11))
				{
					if (pCharObject->m_wObjectType & _OBJECT_HUMAN)
						pCharObject->AddProcess(this, wIdent, wParam, lParam1, lParam2, lParam3, pszData);
//                     end else begin
//                      if cret.WantRefMsg and ((msg = RM_STRUCK) or (msg = RM_HEAR) or (msg = RM_DEATH)) then
//                       cret.SendMsg (self, msg, wparam, lparam1, lparam2, lparam3, str);
				}
			}
			
			pListNode = m_xCacheObjectList.GetNext(pListNode);
		} // while (pListNode)
	}
}

void CCharObject::SpaceMove(int nX, int nY, CMirMap* pMirMap)
{
	CVisibleObject* pVisibleObject;

	if (m_pMap->RemoveObject(m_nCurrX, m_nCurrY, OS_MOVINGOBJECT, this))
	{
		PLISTNODE pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			pVisibleObject = m_xVisibleObjectList.GetData(pListNode);

			if (pVisibleObject)
			{
				delete pVisibleObject;
				pVisibleObject = NULL;
			}
			
			pListNode = m_xVisibleObjectList.RemoveNode(pListNode);
		} // while (pListNode)

		m_pMap = pMirMap;

		m_nCurrX = nX;
		m_nCurrY = nY;

		if (m_pMap->AddNewObject(m_nCurrX, m_nCurrY, OS_MOVINGOBJECT, this))
		{
			AddProcess(this, RM_CLEAROBJECTS, 0, 0, 0, 0, NULL);
			AddProcess(this, RM_CHANGEMAP, 0, 0, 0, 0, NULL);

			AddRefMsg(RM_SPACEMOVE_SHOW, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);
		}
	}
}

void CCharObject::UpdateVisibleObject(CCharObject* pCharObject)
{
	CVisibleObject* pVisibleObject;

	PLISTNODE		pListNode = m_xVisibleObjectList.GetHead();

	while (pListNode)
	{
		pVisibleObject = m_xVisibleObjectList.GetData(pListNode);

		if (pVisibleObject->pObject == pCharObject)
		{
			pVisibleObject->nVisibleFlag = 1;
			return;
		}
		
		pListNode = m_xVisibleObjectList.GetNext(pListNode);
	} // while (pListNode)

	CVisibleObject* pNewVisibleObject = new CVisibleObject;

	pNewVisibleObject->nVisibleFlag	= 2;
	pNewVisibleObject->pObject		= pCharObject;

	m_xVisibleObjectList.AddNewNode(pNewVisibleObject);
}

void CCharObject::UpdateVisibleItem(int nX, int nY, CMapItem* pMapItem)
{
	CVisibleMapItem* pVisibleItem;

	PLISTNODE		pListNode = m_xVisibleItemList.GetHead();

	while (pListNode)
	{
		pVisibleItem = m_xVisibleItemList.GetData(pListNode);

		if (pVisibleItem->pMapItem == pMapItem)
		{
			pVisibleItem->nVisibleFlag = 1;
			return;
		}
		
		pListNode = m_xVisibleItemList.GetNext(pListNode);
	} // while (pListNode)

	CVisibleMapItem* pVisibleNewItem = new CVisibleMapItem;

	pVisibleNewItem->nVisibleFlag	= 2;
	pVisibleNewItem->wX				= (WORD)nX;
	pVisibleNewItem->wY				= (WORD)nY;
	pVisibleNewItem->pMapItem		= pMapItem;

	m_xVisibleItemList.AddNewNode(pVisibleNewItem);
}

void CCharObject::UpdateVisibleEvent(CEvent* pEvent)
{
	CVisibleEvent* pVisibleEvent;

	PLISTNODE		pListNode = m_xVisibleEventList.GetHead();

	while (pListNode)
	{
		pVisibleEvent = m_xVisibleEventList.GetData(pListNode);

		if (pVisibleEvent->pEvent == pEvent)
		{
			pVisibleEvent->nVisibleFlag = 1;
			return;
		}
		
		pListNode = m_xVisibleEventList.GetNext(pListNode);
	} // while (pListNode)

	CVisibleEvent* pVisibleNewEvent = new CVisibleEvent;

	pVisibleNewEvent->nVisibleFlag	= 2;
	pVisibleNewEvent->pEvent		= pEvent;

	m_xVisibleEventList.AddNewNode(pVisibleNewEvent);
}

void CCharObject::SearchViewRange()
{
	int nStartX = m_nCurrX - m_nViewRange;
	int nEndX	= m_nCurrX + m_nViewRange;
	int nStartY = m_nCurrY - m_nViewRange;
	int nEndY	= m_nCurrY + m_nViewRange;

	CMapCellInfo*		pMapCellInfo;
	_LPTOSOBJECT		pOSObject;	
	CCharObject*		pCharObject;
	CEvent*				pEvent;
	PLISTNODE			pListNode;
	CVisibleObject*		pVisibleObject;
	CVisibleMapItem*	pVisibleItem;
	CVisibleEvent*		pVisibleEvent;

	// Clear VisibleObjectList
	if (m_xVisibleObjectList.GetCount())
	{
		pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
				pVisibleObject->nVisibleFlag = 0;

			pListNode = m_xVisibleObjectList.GetNext(pListNode);
		}
	}

	// Clear VisibleMapItem
	if (m_xVisibleItemList.GetCount())
	{
		pListNode = m_xVisibleItemList.GetHead();

		while (pListNode)
		{
			if (pVisibleItem = m_xVisibleItemList.GetData(pListNode))
				pVisibleItem->nVisibleFlag = 0;

			pListNode = m_xVisibleItemList.GetNext(pListNode);
		}
	}

	// Clear VisibleEvent
	if (m_xVisibleEventList.GetCount())
	{
		pListNode = m_xVisibleEventList.GetHead();

		while (pListNode)
		{
			if (pVisibleEvent = m_xVisibleEventList.GetData(pListNode))
				pVisibleEvent->nVisibleFlag = 0;

			pListNode = m_xVisibleEventList.GetNext(pListNode);
		}
	}

	// Search VisibleAllObjectList
	for (int x = nStartX; x <= nEndX; x++)
	{
		for (int y = nStartY; y <= nEndY; y++)
		{
			pMapCellInfo = m_pMap->GetMapCellInfo(x, y);

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
									pCharObject = (CCharObject*)pOSObject->pObject;
									
									if (!pCharObject->m_fInspector && !pCharObject->m_fIsGhost && !pCharObject->m_fHideMode)
										UpdateVisibleObject(pCharObject);
								}
								else if (pOSObject->btType == OS_ITEMOBJECT)
								{
									if (GetTickCount() - pOSObject->dwAddTime > 60 * 60 * 1000)
									{
										delete pOSObject;
										pOSObject = NULL;

										pListNode = pMapCellInfo->m_xpObjectList->RemoveNode(pListNode);
										continue;
									}
									else
										UpdateVisibleItem(x, y, (CMapItem*)pOSObject->pObject);
								}
								else if (pOSObject->btType == OS_EVENTOBJECT)
								{
									pEvent = (CEvent*)pOSObject->pObject;

									if (pEvent->m_fVisible)
										UpdateVisibleEvent(pEvent);
								}
							}
							
							pListNode = pMapCellInfo->m_xpObjectList->GetNext(pListNode);
						} // while (pListNode)
					} // if (pMapCellInfo->m_pObjectList.GetCount())
				}
			} // if (pMapCellInfo)
		}// for (y)
	} // for (x)

	if (m_xVisibleObjectList.GetCount())
	{
		pListNode = m_xVisibleObjectList.GetHead();

		while (pListNode)
		{
			if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
			{
				if (pVisibleObject->nVisibleFlag == 0)
				{
					if (!pVisibleObject->pObject->m_fHideMode)
						AddProcess(pVisibleObject->pObject, RM_DISAPPEAR, 0, 0, 0, 0, NULL);

					delete pVisibleObject;
					pVisibleObject = NULL;
					
					pListNode = m_xVisibleObjectList.RemoveNode(pListNode);

					continue;
				}
				else
				{
					if (m_wObjectType & _OBJECT_HUMAN)
					{
						if (pVisibleObject->nVisibleFlag == 2)	// 2:New Object
						{
							if (pVisibleObject->pObject != this)
							{
								if (pVisibleObject->pObject->m_fIsDead)
								{
									AddProcess(pVisibleObject->pObject, RM_DEATH, pVisibleObject->pObject->m_nDirection, 
																		pVisibleObject->pObject->m_nCurrX, pVisibleObject->pObject->m_nCurrY, 0, NULL);
								}
								else
									AddProcess(pVisibleObject->pObject, RM_TURN, pVisibleObject->pObject->m_nDirection, 
																		pVisibleObject->pObject->m_nCurrX, pVisibleObject->pObject->m_nCurrY, 
																		0, pVisibleObject->pObject->m_szName);
							}
						}
					}
				} // if (pVisibleObject->nVisibleFlag == 0)
			} // if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
			
			pListNode = m_xVisibleObjectList.GetNext(pListNode);
		} // while (pListNode)
	}

	// Update Map Item
	if (m_xVisibleItemList.GetCount())
	{
		pListNode = m_xVisibleItemList.GetHead();

		while (pListNode)
		{
			if (pVisibleItem = m_xVisibleItemList.GetData(pListNode))
			{
				if (pVisibleItem->nVisibleFlag == 0)
				{
					AddProcess(this, RM_ITEMHIDE, 0, (LPARAM)pVisibleItem->pMapItem, pVisibleItem->wX, pVisibleItem->wY, NULL);
					
					delete pVisibleItem;
					pVisibleItem = NULL;
					
					pListNode = m_xVisibleItemList.RemoveNode(pListNode);

					continue;
				}
				else
				{
					if (pVisibleItem->nVisibleFlag == 2)	// 2:New Item
						AddProcess(this, RM_ITEMSHOW, pVisibleItem->pMapItem->wLooks, (LPARAM)pVisibleItem->pMapItem, 
										pVisibleItem->wX, pVisibleItem->wY, pVisibleItem->pMapItem->szName);	
				} // if (pVisibleObject->nVisibleFlag == 0)
			} // if (pVisibleObject = m_xVisibleItemList.GetData(pListNode))
			
			pListNode = m_xVisibleItemList.GetNext(pListNode);
		} // while (pListNode)
	}

	// Update Event Item
	if (m_xVisibleEventList.GetCount())
	{
		pListNode = m_xVisibleEventList.GetHead();

		while (pListNode)
		{
			if (pVisibleEvent = m_xVisibleEventList.GetData(pListNode))
			{
				if (pVisibleEvent->nVisibleFlag == 0)
				{
					AddProcess(this, RM_HIDEEVENT, 0, (LPARAM)pVisibleEvent->pEvent, pVisibleEvent->pEvent->m_nX, pVisibleEvent->pEvent->m_nY);
					
					pListNode = m_xVisibleEventList.RemoveNode(pListNode);

					delete pVisibleEvent;
					pVisibleEvent = NULL;

					continue;
				}
				else if (pVisibleEvent->nVisibleFlag == 2) 
				{
					AddProcess(this, RM_SHOWEVENT, pVisibleEvent->pEvent->m_nEventType, (LPARAM)pVisibleEvent->pEvent, 
									MAKELONG(pVisibleEvent->pEvent->m_nX, pVisibleEvent->pEvent->m_nEventParam), pVisibleEvent->pEvent->m_nY);	
				}
			}
			
			pListNode = m_xVisibleEventList.GetNext(pListNode);
		} // while (pListNode)
	}
}

void CCharObject::Disappear()
{
	if (m_pMap)
	{
		m_pMap->RemoveObject(m_nCurrX, m_nCurrY, OS_MOVINGOBJECT, this);
		AddRefMsg(RM_DISAPPEAR, 0, 0, 0, 0, NULL);
	}
}

void CCharObject::MakeGhost()
{
	m_fIsGhost		= TRUE;
	m_dwGhostTime	= GetTickCount();
   
	Disappear();
}

void CCharObject::TurnTo(int nDir)
{
	AddRefMsg(RM_TURN, nDir, m_nCurrX, m_nCurrY, 0, m_szName);

	m_nDirection = nDir;
}

BOOL CCharObject::TurnXY(int nX, int nY, int nDir)
{
	if (m_nCurrX == nX && m_nCurrY == nY)
	{
		AddRefMsg(RM_TURN, nDir, m_nCurrX, m_nCurrY, 0, m_szName);

		m_nDirection = nDir;

		return TRUE;
	}

	return FALSE;
}

void CCharObject::WalkNextPos(int nDir, int& nX, int& nY)
{
	switch (nDir)
	{
		case DR_UP:
			nX = m_nCurrX;
			nY = m_nCurrY - 1;
			break;
		case DR_UPRIGHT:
			nX = m_nCurrX + 1;
			nY = m_nCurrY - 1;
			break;
		case DR_RIGHT:
			nX = m_nCurrX + 1;
			nY = m_nCurrY;
			break;
		case DR_DOWNRIGHT:
			nX = m_nCurrX + 1;
			nY = m_nCurrY + 1;
			break;
		case DR_DOWN:
			nX = m_nCurrX;
			nY = m_nCurrY + 1;
			break;
		case DR_DOWNLEFT:
			nX = m_nCurrX - 1;
			nY = m_nCurrY + 1;
			break;
		case DR_LEFT:
			nX = m_nCurrX - 1;
			nY = m_nCurrY;
			break;
		case DR_UPLEFT:
			nX = m_nCurrX - 1;
			nY = m_nCurrY - 1;
			break;
	}
}

BOOL CCharObject::WalkTo(int nDir)
{
	int nX, nY;

	WalkNextPos(nDir, nX, nY);

	BOOL fResult = WalkXY(nX, nY, nDir);

	if (fResult)
	{
		if (m_fFixedHideMode)
		{
           if (m_fHumHideMode)
              m_wStatusArr[STATE_TRANSPARENT] = 1;
		}
	}

	return fResult;
}

BOOL CCharObject::RunTo(int nDir)
{
	int nX = m_nCurrX, nY = m_nCurrY;
	int nWalk = 2;

	if (m_tFeatureEx.btHorse)
		nWalk = 3;

	for (int i = 0; i < nWalk; i++)
	{
		switch (nDir)
		{
			case DR_UP:
				nY--;
				break;
			case DR_UPRIGHT:
				nX++;
				nY--;
				break;
			case DR_RIGHT:
				nX++;
				break;
			case DR_DOWNRIGHT:
				nX++;
				nY++;
				break;
			case DR_DOWN:
				nY++;
				break;
			case DR_DOWNLEFT:
				nX--;
				nY++;
				break;
			case DR_LEFT:
				nX--;
				break;
			case DR_UPLEFT:
				nX--;
				nY--;
				break;
		}
		
		if (m_pMap->CanMove(nX, nY) == FALSE)
			return FALSE;
	}

	return RunXY(nX, nY, nDir); 
}

BOOL CCharObject::WalkXY(int nX, int nY, int nDir)
{
	int nFlag = m_pMap->CheckDoorEvent(nX, nY, m_nEvent);

	if (nFlag)
	{
		if (nFlag == _DOOR_OPEN)
			AddRefMsg(RM_DOOROPEN, 1, m_nEvent, 0, 0, NULL);
	}

	if (m_pMap->CanMove(nX, nY))
	{
		if (m_pMap->MoveToMovingObject(m_nCurrX, m_nCurrY, nX, nY, this))
		{
//#ifdef _DEBUG
//	_RPT4(_CRT_WARN, "WALK:%d, %d -> %d, %d", m_nCurrX, m_nCurrY, nX, nY);
//	_RPT1(_CRT_WARN, " [%d]\n", nDir); 
//#endif
			AddRefMsg(RM_WALK, nDir, m_nCurrX, m_nCurrY, 0, NULL);

			m_nCurrX		= nX;
			m_nCurrY		= nY;

			m_nDirection	= nDir;

			m_dwHealthTick	-= 20;

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CCharObject::RunXY(int nX, int nY, int nDir)
{
	if (m_pMap->MoveToMovingObject(m_nCurrX, m_nCurrY, nX, nY, this))
	{
//#ifdef _DEBUG
//	_RPT4(_CRT_WARN, "RUN:%d, %d -> %d, %d", m_nCurrX, m_nCurrY, nX, nY);
//	_RPT1(_CRT_WARN, " [%d]\n", nDir); 
//#endif
		AddRefMsg(RM_RUN, nDir, m_nCurrX, m_nCurrY, 0, NULL);

		m_nCurrX		= nX;
		m_nCurrY		= nY;
		m_nDirection	= nDir;

		m_dwHealthTick	-= 150;
		m_dwSpellTick	-= 10;
		m_dwSpellTick	= _MAX(0, m_dwSpellTick);
		m_btPerHealth--;
		m_btPerSpell--;

		return TRUE;
	}

	return FALSE;
}

void CCharObject::IncHealthSpell(int nHP, int nMP)
{
	if (nHP >= 0)
	{
		if (m_WAbility.HP + nHP < m_WAbility.MaxHP)
			m_WAbility.HP += nHP;
		else 
			m_WAbility.HP = m_WAbility.MaxHP;
	}

	if (nMP >= 0)
	{
		if (m_WAbility.MP + nMP < m_WAbility.MaxMP)
			m_WAbility.MP += nMP;
		else 
			m_WAbility.MP = m_WAbility.MaxMP;
	}

	HealthSpellChanged();
}

//val : (+) dec spell
//      (-) inc spell
void CCharObject::DamageSpell(int nVal)
{
	if (nVal > 0)
	{
		if (m_WAbility.MP - nVal > 0)
			m_WAbility.MP = m_WAbility.MP - nVal;
		else
			m_WAbility.MP = 0;
	}
	else
	{
		if (m_WAbility.MP - nVal < m_WAbility.MaxMP)
			m_WAbility.MP = m_WAbility.MP - nVal;
		else
			m_WAbility.MP = m_WAbility.MaxMP;
	}
}

//nDamage : if (+) damage health
//			if (-) healing health
void CCharObject::DamageHealth(int nDamage)
{
/*  ��ȣ�ǹ��� 
	if BoMagicShield and (damage > 0) and (WAbil.MP > 0) then begin
      spdam := Round (damage * 1.5);
      if integer(WAbil.MP) >= spdam then begin
         WAbil.MP := WAbil.MP - spdam;
         spdam := 0;
      end else begin
         spdam := spdam - WAbil.MP;
         WAbil.MP := 0;
      end;
      damage := Round (spdam / 1.5);
      HealthSpellChanged;
   end; */
	if (nDamage > 0)
	{
		if (m_WAbility.HP - nDamage > 0)
			m_WAbility.HP = m_WAbility.HP - nDamage;
		else
			m_WAbility.HP = 0;
	}
	else
	{
		if (m_WAbility.HP - nDamage < m_WAbility.MaxHP)
			m_WAbility.HP = m_WAbility.HP - nDamage;
		else
			m_WAbility.HP = m_WAbility.MaxHP;
	}
}

int CCharObject::GetMagStruckDamage(int nDamage)
{
	int nArmor = 0;

	if ((HIBYTE(m_WAbility.MAC) - LOBYTE(m_WAbility.MAC) + 1) > 0)
		nArmor = LOBYTE(m_WAbility.MAC) + (rand() % (HIBYTE(m_WAbility.MAC) - LOBYTE(m_WAbility.MAC) + 1));
	else
		nArmor = LOBYTE(m_WAbility.MAC);

	nDamage	= _MAX(0, nDamage - nArmor);

	if (nDamage > 0)
	{
		if (m_fAbilMagBubbleDefence) // �ּ��Ǹ�
		{
			nDamage = ROUND(nDamage / 100 * (m_btMagBubbleDefenceLevel + 2) * 8);
			DamageBubbleDefence();
		}
	}										  

	return nDamage;
}

void CCharObject::StruckDamage(int nDamage)
{
	if (nDamage > 0)
	{
		BOOL	fReCalc = FALSE;
		int		wDam = (rand() % 10) + 5;

		if (m_wStatusArr[POISON_DAMAGEARMOR] > 0)
		{
			wDam	= ROUND(wDam * 1.2);
			nDamage	= ROUND(nDamage * 1.2);
		}

		if (m_pUserInfo)
		{
			_LPTUSERITEMRCD	lptDress = m_pUserInfo->GetDress();

			if (lptDress)
			{
				int nDura		= lptDress->nDura;
				int nOldDura	= ROUND(nDura / 1000);
				
				nDura	-= wDam;

				if (nDura <= 0)	// ��� ������
				{
					lptDress->nDura = nDura = 0;

//               hum.SendDelItem (UseItems[U_DRESS]); //Ŭ���̾�Ʈ�� �������� ����
					m_pUserInfo->SetEmptyDress();

					AddProcess(this, RM_DURACHANGE, U_DRESS, nDura, lptDress->nDuraMax, 0); 
					AddProcess(this, RM_FEATURECHANGED, 0, GetFeatureToLong(), 0, 0);
					
					fReCalc = TRUE;
				}
				else
					lptDress->nDura = nDura;

				if (nOldDura != ROUND(nDura / 1000))
					AddProcess(this, RM_DURACHANGE, U_DRESS, lptDress->nDura, lptDress->nDuraMax, 0); 
			}

			_LPTUSERITEMRCD	lptUseItem;

			for (int i = 0; i < 8; i++)
			{
				lptUseItem = m_pUserInfo->GetUseItem(i);

				if (lptUseItem && (rand() % 8) == 0)
				{
					int nDura		= lptUseItem->nDura;
					int nOldDura	= ROUND(nDura / 1000);
					
					nDura	-= wDam;

					if (nDura <= 0)	// ��� ������
					{
						lptUseItem->nDura = nDura = 0;

	//               hum.SendDelItem (UseItems[U_DRESS]); //Ŭ���̾�Ʈ�� �������� ����
						m_pUserInfo->SetEmptyUseItem(i);

						AddProcess(this, RM_DURACHANGE, i, nDura, lptUseItem->nDuraMax, 0); 
						AddProcess(this, RM_FEATURECHANGED, 0, GetFeatureToLong(), 0, 0);

						fReCalc = TRUE;
					}
					else
						lptUseItem->nDura = nDura;

					if (nOldDura != ROUND(nDura / 1000))
						AddProcess(this, RM_DURACHANGE, i, lptUseItem->nDura, lptUseItem->nDuraMax, 0); 
				}
			}
		}

		if (fReCalc && m_pUserInfo)
			((CPlayerObject*)this)->RecalcAbilitys();

		DamageHealth(nDamage);
	}
}

int CCharObject::GetHitStruckDamage(int nDamage)
{
	int nArmor;
	int nRnd = ((HIBYTE(m_WAbility.AC) - LOBYTE(m_WAbility.AC)) + 1);

	if (nRnd > 0)
		nArmor = LOBYTE(m_WAbility.AC) + (rand() % nRnd);
	else
		nArmor = LOBYTE(m_WAbility.AC);

	nDamage = _MAX(0, nDamage - nArmor);

	if (nDamage > 0)
	{
		if (m_fAbilMagBubbleDefence) // �ּ��Ǹ�
		{
			nDamage = ROUND(nDamage / 100 * (m_btMagBubbleDefenceLevel + 2) * 8);
			DamageBubbleDefence();
		}
	}										  

	return nDamage;
}

int CCharObject::GetAttackPower(int nDamage, int nVal)
{
	int nPower = 0;

	if (nVal < 0) nVal = 0;

//	if (Lucky > 0)
//	{
//	}
//	else
//	{
		nPower = nDamage + (rand() % (nVal + 1));
//	}

	return nPower;
/*var
   v1, v2: integer;
begin
   if val < 0 then val := 0;
   if Luck > 0 then begin
      if Random(10 - _MIN(9,Luck)) = 0 then Result := damage + val //����ΰ��
      else Result := damage + Random(val + 1);
   end else begin
      Result := damage + Random(val + 1);
      if Luck < 0 then begin
         if Random(10 - _MAX(0,-Luck)) = 0 then Result := damage;  //�ҿ��ΰ��
      end;
   end; */
}

void CCharObject::DoDamageWeapon(int nDamage)
{
	if (m_pUserInfo)
	{
		_LPTUSERITEMRCD	lptWeapon = m_pUserInfo->GetWeapon();

		if (lptWeapon)
		{
			int nDura		= lptWeapon->nDura;
			int nOldDura	= ROUND(nDura / 1000);
			
			nDura	-= nDamage;

			if (nDura <= 0)	// ��� ������
			{
				lptWeapon->nDura = nDura = 0;
//               hum.SendDelItem (UseItems[U_DRESS]); //Ŭ���̾�Ʈ�� �������� ����

				((CPlayerObject*)this)->RecalcAbilitys();

				m_pUserInfo->SetEmptyWeapon();

				AddProcess(this, RM_DURACHANGE, U_WEAPON, nDura, lptWeapon->nDuraMax, 0); 
			}
			else
				lptWeapon->nDura = nDura;

			if (nOldDura != ROUND(nDura / 1000))
				AddProcess(this, RM_DURACHANGE, U_WEAPON, lptWeapon->nDura, lptWeapon->nDuraMax, 0); 
		}
	}
}

BOOL CCharObject::_Attack(WORD wHitMode, CCharObject* pObject)
{
	int nPower	= GetAttackPower(LOBYTE(m_WAbility.DC), (HIBYTE(m_WAbility.DC) - LOBYTE(m_WAbility.DC)));
	int nSecPwr	= 0;
	int nWeaponDamage;

	if (pObject)
	{
		if (wHitMode == CM_POWERHIT && m_pUserInfo->m_fPowerHitSkill)
		{
			m_pUserInfo->m_fPowerHitSkill = FALSE;
			nPower += m_btHitPlus;
		}

		if (wHitMode == CM_FIREHIT && m_pUserInfo->m_fFireHitSkill)
		{
			m_pUserInfo->m_fFireHitSkill = FALSE;
			
			nPower += ROUND(nPower / 100 * (m_nHitDouble * 10));
		}
	}
	else
	{
		if (wHitMode == CM_POWERHIT && m_pUserInfo->m_fPowerHitSkill)
		{
			m_pUserInfo->m_fPowerHitSkill = FALSE;
			nPower += m_btHitPlus;
		}
	}

	if (wHitMode == CM_LONGHIT)
	{
		nSecPwr	= 0;

		if (m_pUserInfo->m_lpTMagicErgumSkill)
			nSecPwr = ROUND(nPower / (3/*MaxTrainLevel*/ + 2) * (m_pUserInfo->m_lpTMagicErgumSkill->btLevel + 2));
		else
			nSecPwr = nPower;

		if (nSecPwr > 0)
			SwordLongAttack(nSecPwr);
	}

	if (wHitMode == CM_WIDEHIT)
	{
		nSecPwr	= 0;

		if (m_pUserInfo->m_lpTMagicBanwolSkill)
			nSecPwr = ROUND(nPower / (3/*MaxTrainLevel*/ + 10) * (m_pUserInfo->m_lpTMagicBanwolSkill->btLevel + 2));
		else
			nSecPwr = nPower;

		if (nSecPwr > 0)
			SwordWideAttack(nSecPwr);
	}

	if (pObject)
	{
		if (IsProperTarget(pObject))
		{
			if (pObject->m_btHitPoint > 0)
			{
				if (m_btHitPoint < rand() % pObject->m_btSpeedPoint)
					nPower = 0;
			}
		}
		else
			nPower = 0;
	}	

	if (nPower > 0)
	{
		nPower			= pObject->GetHitStruckDamage(nPower);
		nWeaponDamage	= (rand() % 5) + 2 - m_AddAbility.WeaponStrong;
	
/*		if (m_wObjectType & _OBJECT_HUMAN)
		{
				case CM_FIREHIT:
				{
					if (m_pUserInfo->m_lpTMagicFireSwordSkill)
						nSecPwr = _ROUND(nPwr / (3 + 2) * (m_pUserInfo->m_lpTMagicFireSwordSkill->btLevel + 2));
					else
						nSecPwr = nPower;

					break;
				}		  
		}
*/
		if (nWeaponDamage > 0)
		{
			if (m_pUserInfo->GetWeapon()) 
				DoDamageWeapon(nWeaponDamage);
		}

		if (nPower > 0)
		{
			pObject->StruckDamage(nPower);

			// Debug Code
#ifdef _DEBUG
			char szMsg[64];

			if (m_wObjectType & _OBJECT_HUMAN)
			{
				sprintf(szMsg, "%s ���� - PW:%d HP:%d, ���⳻������:%d", pObject->m_szName, nPower, pObject->m_WAbility.HP, nWeaponDamage);
				SysMsg(szMsg, 0);
			}
			else if (pObject->m_wObjectType & _OBJECT_HUMAN)
			{
				sprintf(szMsg, "%s ���� - PW:%d HP:%d", pObject->m_szName, nPower, pObject->m_WAbility.HP);
				pObject->SysMsg(szMsg, 0);
			}
			// Debug Code
#endif

			AddDelayProcess(pObject, RM_STRUCK, nPower, pObject->m_WAbility.HP, pObject->m_WAbility.MaxHP, (LONG)this, NULL, 550);

			if (!(pObject->m_wObjectType & _OBJECT_HUMAN))
				pObject->AddProcess(pObject, RM_STRUCK, nPower, pObject->m_WAbility.HP, pObject->m_WAbility.MaxHP, (LONG)this, NULL);

			return TRUE;
		}
	}

	return FALSE;
}									   

BOOL CCharObject::HitXY(WORD wIdent, int nX, int nY, int nDir, int nHitStyle)
{
	if ((GetTickCount() - m_dwLatestHitTime) < 600)
		m_nHitTimeOverCount++;
	else
		m_nHitTimeOverCount = 0;

	if (m_nHitTimeOverCount < 2)
	{
		if (m_nCurrX == nX && m_nCurrY == nY)
		{
			if (wIdent == CM_WIDEHIT && m_pUserInfo->m_lpTMagicBanwolSkill)
			{
				if (m_WAbility.MP > 0)
				{
					int nLevel		= m_pUserInfo->GetMagicRcdByID(_SKILL_BANWOL)->btLevel;
					int nSpellPoint = GetMagicInfo(_SKILL_BANWOL)->GetSpellPoint(nLevel);
					DamageSpell(nSpellPoint);
					HealthSpellChanged();
				}
				else
					wIdent = CM_HIT;
			}

			m_nDirection		= nDir;
			m_dwLatestHitTime	= GetTickCount();

			CCharObject* pObject = GetFrontObject();

			if (pObject)
			{
				if (_Attack(wIdent, pObject))
				{
					SelectTarget(pObject);

					m_dwHealthTick	-= 100;
					m_dwSpellTick	-= 100;
					m_dwSpellTick	= _MAX(0, m_dwSpellTick);
					m_btPerHealth	-= 2;
					m_btPerSpell	-= 2;
				}
			}

			if (m_wObjectType & _OBJECT_HUMAN)
			{
				switch (wIdent)
				{
					case CM_HIT:
						AddRefMsg(RM_HIT, nDir, m_nCurrX, m_nCurrY, nHitStyle, NULL);
						break;
					case CM_WIDEHIT:
						AddRefMsg(RM_WIDEHIT, nDir, m_nCurrX, m_nCurrY, nHitStyle, NULL);
						break;
					case CM_LONGHIT:
						AddRefMsg(RM_LONGHIT, nDir, m_nCurrX, m_nCurrY, nHitStyle, NULL);
						break;
					case CM_FIREHIT:
						AddRefMsg(RM_FIREHIT, nDir, m_nCurrX, m_nCurrY, nHitStyle, NULL);
						break;
					case CM_POWERHIT:
						AddRefMsg(RM_POWERHIT, nDir, m_nCurrX, m_nCurrY, nHitStyle, NULL);
						break;
				}
			}

			if (m_pUserInfo->m_lpTMagicPowerHitSkill)		// ���� �˹�
			{
				m_pUserInfo->m_btAttackSkillCount--;

				if (m_pUserInfo->m_btAttackSkillCount == m_pUserInfo->m_btAttackSkillPointCount)
				{
					m_pUserInfo->m_fPowerHitSkill = TRUE;
					SendSocket(NULL, "+PWR");
				}

				if (m_pUserInfo->m_btAttackSkillCount <= 0)
				{
					m_pUserInfo->m_btAttackSkillCount		= 7 - m_pUserInfo->m_lpTMagicPowerHitSkill->btLevel;
					m_pUserInfo->m_btAttackSkillPointCount	= rand() % m_pUserInfo->m_btAttackSkillCount;
				}
			}

			return TRUE;
		}
	}

	return FALSE;
}

void CCharObject::DoPushed(int nDirection)
{
	int nFrontX, nFrontY;

	m_nDirection = nDirection;

	GetFrontPosition(nFrontX, nFrontY);

	if (m_pMap->MoveToMovingObject(m_nCurrX, m_nCurrY, nFrontX, nFrontY, this))
	{
		AddRefMsg(RM_PUSH, GetBack(nDirection), m_nCurrX, m_nCurrY, 0, NULL);

		m_nCurrX = nFrontX;
		m_nCurrY = nFrontY;
	}
}

void CCharObject::GoldChanged()
{
	if (m_wObjectType & _OBJECT_HUMAN)
		UpdateProcess(this, RM_GOLDCHANGED, 0, 0, 0, 0, NULL);
}

void CCharObject::HealthSpellChanged()
{
	if (m_wObjectType & _OBJECT_HUMAN)
		UpdateProcess(this, RM_HEALTHSPELLCHANGED, 0, 0, 0, 0, NULL);

	if (m_fOpenHealth)
		AddRefMsg(RM_HEALTHSPELLCHANGED, 0, 0, 0, 0, NULL);
}

CCharObject* CCharObject::AddCreatureSysop(int nX, int nY, CMonRaceInfo* pMonRaceInfo, BOOL fSearch)
{
	CMonsterObject* pMonObject = AddCreature(m_pMap, nX, nY, pMonRaceInfo->nIndex, fSearch);

	if (pMonObject)
	{
		if (g_pMonGenInfo)
			g_pMonGenInfo[g_nNumOfMonGenInfo].xMonsterObjList.AddNewNode(pMonObject);
	}

	return (CCharObject*)pMonObject;
}

void CCharObject::DoMotaebo()
{
	int nFrontX, nFrontY;

	CCharObject* pCharObject = GetFrontObject();

	if (pCharObject)
	{
		for (int i = 0; i < 5; i++)
		{
			pCharObject->DoPushed(m_nDirection);

			GetFrontPosition(nFrontX, nFrontY);
			
			if (m_pMap->MoveToMovingObject(m_nCurrX, m_nCurrY, nFrontX, nFrontY, this))
			{
				AddRefMsg(RM_RUSH, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

				m_nCurrX		= nFrontX;
				m_nCurrY		= nFrontY;

				if (!(pCharObject = GetFrontObject()))
					break;
			}
			else 
				break;
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			GetFrontPosition(nFrontX, nFrontY);
			
			if (m_pMap->MoveToMovingObject(m_nCurrX, m_nCurrY, nFrontX, nFrontY, this))
			{
				AddRefMsg(RM_RUSH, m_nDirection, m_nCurrX, m_nCurrY, 0, NULL);

				m_nCurrX		= nFrontX;
				m_nCurrY		= nFrontY;
			}
			else
				break;
		}
	}
}

/* **************************************************************************************

										Ž���Ŀ�

   ************************************************************************************** */

BOOL CCharObject::DoShowHP(CCharObject* pObject, CMagicInfo* pMagicInfo, int nLevel)
{
	if (pObject)
	{
		if (!pObject->m_fOpenHealth)
		{
			if ((rand() % 6) <= (3 + m_Ability.Level))
			{
				pObject->m_dwOpenHealthStart	= GetTickCount();
				pObject->m_dwOpenHealthTime		= pMagicInfo->GetPower13(30 + GetRPow(m_WAbility.SC) * 2, nLevel) * 1000;
				
				pObject->AddDelayProcess(pObject, RM_DOOPENHEALTH, 0, 0, 0, 0, NULL, 3000);

				return TRUE;
			}
		}
	}

	return FALSE;
}

void CCharObject::MakeOpenHealth()
{
	m_fOpenHealth		= TRUE;
   
	m_nCharStatusEx		|= STATE_OPENHEATH;
	m_nCharStatus		= GetCharStatus();
   
	AddRefMsg(RM_OPENHEALTH, 0, m_WAbility.HP/*lparam1*/, m_WAbility.MaxHP/*lparam2*/, 0, NULL);
}

void CCharObject::BreakOpenHealth()
{
	m_fOpenHealth		= FALSE;
   
	m_nCharStatusEx		^= STATE_OPENHEATH;
	m_nCharStatus		= GetCharStatus();
   
	AddRefMsg(RM_CLOSEHEALTH, 0, 0, 0, 0, NULL);
}

/* **************************************************************************************

										���º�

   ************************************************************************************** */

int CCharObject::CharPushed(int nDir, int nPushCount)
{
	int nFrontX, nFrontY;
	int nResult = 0;

	for (int i = 0; i < nPushCount; i++)
	{
		GetFrontPosition(nFrontX, nFrontY);

		if (m_pMap->CanMove(nFrontX, nFrontY, FALSE))
		{
			if (m_pMap->MoveToMovingObject(m_nCurrX, m_nCurrY, nFrontX, nFrontY, this))
			{
				m_nCurrX = nFrontX;
				m_nCurrY = nFrontY;

				AddRefMsg(RM_PUSH, GetBack(nDir), m_nCurrX, m_nCurrY, 0, NULL);

				nResult++;
			}
		}
	}

	m_nDirection = GetBack(nDir);

	return nResult;

/*function  TCreature.CharPushed (ndir, pushcount: integer): integer;  //� ���� ���ؼ� �з�����.
var
   i, nx, ny, olddir, oldx, oldy: integer;
begin
   Result := 0;
   olddir := Dir;
   oldx := CX;
   oldy := CY;
   Dir := ndir;
   for i:=0 to pushcount-1 do begin
      GetFrontPosition (self, nx, ny);
      if PEnvir.CanWalk (nx, ny, FALSE{��ħ������}) then begin
         if PEnvir.MoveToMovingObject (CX, CY, self, nx, ny, FALSE) > 0 then begin
            CX := nx;
            CY := ny;
            SendRefMsg (RM_PUSH, GetBack(ndir), CX, CY, 0, '');
            Inc (Result);
            if RaceServer >= RC_ANIMAL then
               WalkTime := WalkTime + 800; //�и��鼭 �ʰ� ������.
         end else
            break;
      end else
         break;
   end;
   Dir := GetBack(ndir); //olddir;
end;
*/
}

/* **************************************************************************************

										ȭ��ǳ

   ************************************************************************************** */

int CCharObject::MagPushArround(int nPushLevel)
{
	int nLevelGap, nPush,nDir;
	int nResult = 0;

	if (m_xVisibleObjectList.GetCount())
	{
		PLISTNODE		pListNode = m_xVisibleObjectList.GetHead();
		CVisibleObject*	pVisibleObject;

		while (pListNode)
		{
			if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
			{
				if (abs(m_nCurrX - pVisibleObject->pObject->m_nCurrX) <= 1 && abs(m_nCurrY - pVisibleObject->pObject->m_nCurrY) <= 1)
				{
					if (!pVisibleObject->pObject->m_fIsDead && pVisibleObject->pObject != this)
					{
						if (m_Ability.Level > pVisibleObject->pObject->m_Ability.Level)
						{
							nLevelGap = m_Ability.Level - pVisibleObject->pObject->m_Ability.Level;
							
							if ((rand() % 20) < 6 + nPushLevel * 3 + nLevelGap)
							{
								if (IsProperTarget(pVisibleObject->pObject))
								{
									nPush	= 1 + _MAX(0, nPushLevel - 1) + rand() % 2;
									nDir	= GetNextDirection (pVisibleObject->pObject->m_nCurrX, pVisibleObject->pObject->m_nCurrY);
									pVisibleObject->pObject->CharPushed(nDir, nPush);
									nResult++;
								}
							}
						}
					}
				}
			} // if (pVisibleObject = m_xVisibleObjectList.GetData(pListNode))
			
			pListNode = m_xVisibleObjectList.GetNext(pListNode);
		} // while (pListNode)
	}

	return nResult;

/*function  TMagicManager.MagPushArround (user: TCreature; pushlevel: integer): integer;
var
   i, ndir, levelgap, push: integer;
   cret: TCreature;
begin
   Result := 0;
   for i:=0 to user.VisibleActors.Count-1 do begin
      cret := TCreature (PTVisibleActor(user.VisibleActors[i]).cret);
      if (abs(user.CX-cret.CX) <= 1) and (abs(user.CY-cret.CY) <= 1) then begin
         if (not cret.Death) and (cret <> user) then begin
            if (user.Abil.Level > cret.Abil.Level) and (not cret.StickMode) then begin
               levelgap := user.Abil.Level - cret.Abil.Level;
               if (Random(20) < 6+pushlevel*3+levelgap) then begin  //���������� ����
                  if user.IsProperTarget(cret) then begin
                     push := 1 + _MAX(0,pushlevel-1) + Random(2);
                     ndir := GetNextDirection (user.CX, user.CY, cret.CX, cret.CY);
                     cret.CharPushed (ndir, push);
                     Inc (Result);
                  end;
               end;
            end;
         end;
      end;
   end;
end;
*/
}

/* **************************************************************************************

										������, ������

   ************************************************************************************** */

int CCharObject::MagPassThroughMagic(int nStartX, int nStartY, int nTargetX, int nTargetY, int nDir, int nPwr, BOOL fUndeadAttack)
{
	int				nResult = 0;
	CCharObject*	pObject;

	for (int i = 0; i < 12; i++)
	{
		pObject = m_pMap->GetObject(nStartX, nStartY);

		if (pObject)
		{
			if (IsProperTarget(pObject))
			{
				if (pObject->m_btAntiMagic <= rand() % 10)
				{
					if (fUndeadAttack)
						nPwr = ROUND(nPwr * 1.5);

					pObject->AddDelayProcess(this, RM_MAGSTRUCK, 0, nPwr, 0, 0, NULL, 600);

					nResult++;
				}
			}
		}

		if (!((abs(nStartX - nTargetX) <= 0) && (abs(nStartY - nTargetY) <= 0)))
		{
			nDir = GetNextDirection(nStartX, nStartY, nTargetX, nTargetY);

			if (!(GetNextPosition(nStartX, nStartY, nDir, 1, nStartX, nStartY)))
				break;
		}
		else
			break;
	}

	return nResult;
/*
function  TCreature.MagPassThroughMagic (sx, sy, tx, ty, ndir, magpwr: integer; undeadattack: Boolean): integer;
var
   i, tcount, acpwr: integer;
   cret: TCreature;
begin
   tcount := 0;
   for i:=0 to 12 do begin
      cret := TCreature (PEnvir.GetCreature (sx, sy, TRUE));
      if cret <> nil then begin
         //if (RaceServer = RC_USERHUMAN) and (cret.RaceServer = RC_USERHUMAN) and ((cret.InSafeZone) or (InSafeZone)) then
         //   continue;  //��������
         if IsProperTarget (cret) then begin
            if cret.AntiMagic <= Random(10) then begin  //���� ȸ�ǰ� ����
               if undeadattack then  //�𵥵� ���Ϳ��� ���ݷ� ��ȭ�� ���
                  acpwr := Round (magpwr * 1.5)
               else
                  acpwr := magpwr;
               cret.SendDelayMsg (self, RM_MAGSTRUCK, 0, acpwr, 0, 0, '', 600);
               Inc (tcount);
            end;
         end;
      end;
      if not ((abs(sx-tx) <= 0) and (abs(sy-ty) <= 0)) then begin
         ndir := GetNextDirection (sx, sy, tx, ty);
         if not GetNextPosition (PEnvir, sx, sy, ndir, 1, sx, sy) then
            break;
      end else
         break;
   end;
   Result := tcount;
end; */
}

/* **************************************************************************************

										�ּ��Ǹ�

   ************************************************************************************** */

BOOL CCharObject::MagBubbleDefenceUp(int nLevel, int nSec)
{
	if (m_wStatusArr[STATE_BUBBLEDEFENCEUP] == 0)
	{
		UINT nOldStatus = m_nCharStatus;

		m_wStatusArr[STATE_BUBBLEDEFENCEUP]		= (WORD)nSec; 
		m_dwStatusTime[STATE_BUBBLEDEFENCEUP]	= GetTickCount();

		m_nCharStatus = GetCharStatus();

		if (nOldStatus != m_nCharStatus)
			AddRefMsg(RM_CHARSTATUSCHANGED, m_sHitSpeed/*wparam*/, m_nCharStatus, 0, 0, NULL);

		m_fAbilMagBubbleDefence		= TRUE;
		m_btMagBubbleDefenceLevel	= nLevel;

		return TRUE;
	}

	return FALSE;
}

void CCharObject::DamageBubbleDefence()
{
	if (m_wStatusArr[STATE_BUBBLEDEFENCEUP] > 0)
	{
		if (m_wStatusArr[STATE_BUBBLEDEFENCEUP] > 3)
			m_wStatusArr[STATE_BUBBLEDEFENCEUP] -= 3;
		else
			m_wStatusArr[STATE_BUBBLEDEFENCEUP] = 1;
	}
}

/* **************************************************************************************

										������

   ************************************************************************************** */

int CCharObject::MagMakeFireCross(int nDamage, int nHTime, int nX, int nY)
{
   if (!(m_pMap->GetEvent(nX, nY - 1)))
   {
	   CEvent *pEvent = (CEvent*)new CFireBurnEvent(nX, nY - 1, nHTime * 100, this, nDamage);
	   g_xEventList.AddNewNode(pEvent);
   }
   
   if (!(m_pMap->GetEvent(nX - 1, nY)))
   {
	   CEvent *pEvent = (CEvent*)new CFireBurnEvent(nX - 1, nY, nHTime * 100, this, nDamage);
	   g_xEventList.AddNewNode(pEvent);
   }
   
   if (!(m_pMap->GetEvent(nX, nY)))
   {
	   CEvent *pEvent = (CEvent*)new CFireBurnEvent(nX, nY, nHTime * 100, this, nDamage);
	   g_xEventList.AddNewNode(pEvent);
   }

   if (!(m_pMap->GetEvent(nX + 1, nY)))
   {
	   CEvent *pEvent = (CEvent*)new CFireBurnEvent(nX + 1, nY, nHTime * 100, this, nDamage);
	   g_xEventList.AddNewNode(pEvent);
   }

   if (!(m_pMap->GetEvent(nX, nY + 1)))
   {
	   CEvent *pEvent = (CEvent*)new CFireBurnEvent(nX, nY + 1, nHTime * 100, this, nDamage);
	   g_xEventList.AddNewNode(pEvent);
   }

   return 1;
}

/* **************************************************************************************

										���

   ************************************************************************************** */

int CCharObject::MagMakeHolyCurtain(int nHTime, int nX, int nY)
{
	int						nResult = 0;
	CWHList<CCharObject*>	ObjectList;
	CHolySeizeInfo*			pHolySeizeInfo = NULL;

	if (m_pMap->CanMove(nX, nY, TRUE))
	{
		m_pMap->GetMapObject(nX, nY, 1, &ObjectList);

		if (ObjectList.GetCount())
		{
			PLISTNODE		pListNode = ObjectList.GetHead();
			CMonsterObject*	pTargetObject;

			while (pListNode)
			{
				if (pTargetObject = (CMonsterObject*)ObjectList.GetData(pListNode))
				{
					if ((pTargetObject->m_wObjectType & _OBJECT_ANIMAL) && (pTargetObject->m_Ability.Level < m_Ability.Level - 1 + rand() % 4) &&
						 (pTargetObject->m_Ability.Level < 50) && (pTargetObject->m_pMasterObject == NULL))
					{
						pTargetObject->MakeHolySeize(nHTime * 1000);

						if (!pHolySeizeInfo)
						{
							pHolySeizeInfo = new CHolySeizeInfo;

							for (int i = 0; i < 7; i++)
								pHolySeizeInfo->Event[0] = NULL;

							pHolySeizeInfo->dwOpenTime	= GetTickCount();
							pHolySeizeInfo->dwSeizeTime = nHTime * 1000;

						}

						pHolySeizeInfo->SeizeList.AddNewNode(pTargetObject);
												
						nResult++;					
					}
				}
			
				pListNode = ObjectList.RemoveNode(pListNode);
			}
		}

		if (nResult > 0 && pHolySeizeInfo)
		{
		   CEvent *pEvent = (CEvent*)new CHolyCurtainEvent(nX - 1, nY - 2, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[0] = pEvent;
		   pEvent = (CEvent*)new CHolyCurtainEvent(nX + 1, nY - 2, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[1] = pEvent;
		   pEvent = (CEvent*)new CHolyCurtainEvent(nX - 2, nY - 1, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[2] = pEvent;
		   pEvent = (CEvent*)new CHolyCurtainEvent(nX + 2, nY - 1, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[3] = pEvent;
		   pEvent = (CEvent*)new CHolyCurtainEvent(nX - 2, nY + 1, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[4] = pEvent;
		   pEvent = (CEvent*)new CHolyCurtainEvent(nX + 2, nY + 1, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[5] = pEvent;
		   pEvent = (CEvent*)new CHolyCurtainEvent(nX - 1, nY + 2, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[6] = pEvent;
		   pEvent = (CEvent*)new CHolyCurtainEvent(nX + 1, nY + 2, nHTime * 1000, this);
		   g_xEventList.AddNewNode(pEvent);
		   pHolySeizeInfo->Event[7] = pEvent;

		   g_xHolySeizeList.AddNewNode(pHolySeizeInfo);
		}
	}

	return nResult;					
}

/* **************************************************************************************

										��˼�

   ************************************************************************************** */

BOOL CCharObject::DirectAttack(CCharObject* pTargetObject, int nDamage)
{
	if (pTargetObject->m_wObjectType & _OBJECT_HUMAN)
		return FALSE;

	if (IsProperTarget(pTargetObject))
	{
		if (rand() % pTargetObject->m_btSpeedPoint < m_btHitPoint)
		{
			pTargetObject->StruckDamage(nDamage);
			pTargetObject->AddDelayProcess(pTargetObject, RM_STRUCK, nDamage, pTargetObject->m_WAbility.HP, pTargetObject->m_WAbility.MaxHP, (LONG)this, NULL, 550);

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CCharObject::SwordLongAttack(int nDamage)
{
	int nX = 0, nY = 0;

	if (GetNextPosition(m_nDirection, 2, nX, nY))
	{
		CCharObject* pTargetObject = m_pMap->GetObject(nX, nY);

		if (pTargetObject && (nDamage > 0))
		{
			if (IsProperTarget(pTargetObject))
			{
				DirectAttack(pTargetObject, nDamage);
				SelectTarget(pTargetObject);

					// Debug Code
#ifdef _DEBUG
					char szMsg[64];

					sprintf(szMsg, "%s ��� ���� - PW:%d HP:%d", pTargetObject->m_szName, nDamage, pTargetObject->m_WAbility.HP);
					SysMsg(szMsg, 0);
					// Debug Code
#endif
				return TRUE;
			}
		}
	}

	return FALSE;
}

/* **************************************************************************************

										�ݿ��˹�

   ************************************************************************************** */

BOOL CCharObject::SwordWideAttack(int nDamage)
{
	static int WideSearchPos[8] = { 6, 7, 0, 1, 2, 3, 4, 5 };
	static int WideAttack[3] = { 6, 7, 1 };

	int nDir;
	int nX, nY;

	for (int i = 0; i < 3; i++)
	{
		nDir = (m_nDirection + WideAttack[i]) % 8;

		if (GetNextPosition(nDir, 1, nX, nY))
		{
			CCharObject* pTargetObject = m_pMap->GetObject(nX, nY);

			if (pTargetObject && (nDamage > 0))
			{
				if (IsProperTarget(pTargetObject))
				{
					DirectAttack(pTargetObject, nDamage);
					SelectTarget(pTargetObject);

					// Debug Code
#ifdef _DEBUG
					char szMsg[64];

					sprintf(szMsg, "%s �ݿ� ���� - PW:%d HP:%d", pTargetObject->m_szName, nDamage, pTargetObject->m_WAbility.HP);
					SysMsg(szMsg, 0);
					// Debug Code
#endif
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

/* **************************************************************************************

										�ڼ�ȭ

   ************************************************************************************** */

BOOL CCharObject::MagElecBlizzard(int nPower)
{
	BOOL					fFlag = FALSE;
	CWHList<CCharObject*>	ObjectList;

	m_pMap->GetMapObject(m_nCurrX, m_nCurrY, 2, &ObjectList);

	if (ObjectList.GetCount())
	{
		PLISTNODE		pListNode = ObjectList.GetHead();
		CCharObject*	pTargetObject;

		while (pListNode)
		{
			if (pTargetObject = ObjectList.GetData(pListNode))
			{
				if (pTargetObject->m_wObjectType & _OBJECT_ANIMAL)
				{
					if (((CMonsterObject*)pTargetObject)->m_btLifeAttrib)
						pTargetObject->AddProcess(this, RM_MAGSTRUCK, 0, nPower, 0, 0);
					else
						pTargetObject->AddProcess(this, RM_MAGSTRUCK, 0, nPower / 10, 0, 0);

					fFlag = TRUE;
				}
			}
		
			pListNode = ObjectList.RemoveNode(pListNode);
		}
	}

	return fFlag;
}

/* **************************************************************************************

									����ǳ, ������

   ************************************************************************************** */

BOOL CCharObject::MagBigExplosion(int nPower, int nX, int nY, int nWide)
{
	BOOL					fFlag = FALSE;
	CWHList<CCharObject*>	ObjectList;

	m_pMap->GetMapObject(nX, nY, nWide, &ObjectList);

	if (ObjectList.GetCount())
	{
		PLISTNODE		pListNode = ObjectList.GetHead();
		CCharObject*	pTargetObject;

		while (pListNode)
		{
			if (pTargetObject = ObjectList.GetData(pListNode))
			{
				if (IsProperTarget(pTargetObject))
				{
					SelectTarget(pTargetObject);
					pTargetObject->AddProcess(this, RM_MAGSTRUCK, 0, nPower, 0, 0);
					fFlag = TRUE;
				}
			}
		
			pListNode = ObjectList.RemoveNode(pListNode);
		}
	}

	return fFlag;
}

/* **************************************************************************************

										��ȸ����

   ************************************************************************************** */

BOOL CCharObject::MagBigHealing(int nPower, int nX, int nY)
{
	BOOL					fFlag = FALSE;
	CWHList<CCharObject*>	ObjectList;

	m_pMap->GetMapObject(nX, nY, 1, &ObjectList);

	if (ObjectList.GetCount())
	{
		PLISTNODE		pListNode = ObjectList.GetHead();
		CCharObject*	pTargetObject;

		while (pListNode)
		{
			if (pTargetObject = ObjectList.GetData(pListNode))
			{
				if (IsProperFriend(pTargetObject))
				{
					if (pTargetObject->m_WAbility.HP < pTargetObject->m_WAbility.MaxHP)
					{
						pTargetObject->AddDelayProcess(this, RM_MAGHEALING, 0, nPower, 0, 0, NULL, 800);
						fFlag = TRUE;
					}
				}
			}
		
			pListNode = ObjectList.RemoveNode(pListNode);
		}
	}

	return fFlag;

/*function  TMagicManager.MagBigHealing (user: TCreature; pwr, x, y: integer): Boolean;
var
   i: integer;
   rlist: TList;
   cret: TCreature;
begin
   Result := FALSE;
   rlist := TList.Create;
   user.GetMapCreatures (user.PEnvir, x, y, 1, rlist);
   for i:=0 to rlist.Count-1 do begin
      cret := TCreature (rlist[i]);
      if user.IsProperFriend (cret) then begin
         if cret.WAbil.HP < cret.WAbil.MaxHP then begin
            cret.SendDelayMsg (user, RM_MAGHEALING, 0, pwr, 0, 0, '', 800);
            Result := TRUE;
         end;
         if user.BoAbilSeeHealGauge then begin
            user.SendMsg (cret, RM_INSTANCEHEALGUAGE, 0, 0, 0, 0, '');
         end;
      end;
   end;
   rlist.Free;
end;
*/
}

/* **************************************************************************************

										�׸�����, ������ȣ

   ************************************************************************************** */

BOOL CCharObject::MagDefenceUp(int nState, int nSec)
{
	BOOL fFlag = FALSE;

	if (m_wStatusArr[nState] > 0)
	{
		if (nSec > m_wStatusArr[nState])
		{
			m_wStatusArr[nState] = nSec;
			fFlag = TRUE;
		}
	}
	else
	{
		m_wStatusArr[nState] = nSec;
		fFlag = TRUE;
	}

	m_dwStatusTime[nState]	= GetTickCount();

	TCHAR	wszMsg[32], wszMsg2[32];
	char	szMsg[32];

	if (nState == STATE_DEFENCEUP)
		LoadString(g_hInst, IDS_DEFENCEUP, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));
	else
		LoadString(g_hInst, IDS_MAGDEFENCEUP, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));

	wsprintf(wszMsg2, wszMsg, nSec);
	WideCharToMultiByte(CP_ACP, 0, wszMsg2, -1, szMsg, sizeof(szMsg), NULL, NULL);
	SysMsg(szMsg, 1);

	if (m_wObjectType & _OBJECT_HUMAN)
		((CPlayerObject*)this)->RecalcAbilitys();

	AddProcess(this, RM_ABILITY, 0, 0, 0, 0);

	return FALSE;
}

BOOL CCharObject::MagMakeDefenceArea(int nX, int nY, int nRange, int nSec, int nState)
{
	int nStartX = nX - nRange;
	int nEndX	= nX + nRange;
	int nStartY = nY - nRange;
	int nEndY	= nY + nRange;
	int nCount	= 0;

	__try
	{
		for (int x = nStartX; x <= nEndX; x++)
		{
			for (int y = nStartY; y <= nEndY; y++)
			{
				if (CMapCellInfo* pMapCellInfo = m_pMap->GetMapCellInfo(x, y))
				{
					if (pMapCellInfo->m_xpObjectList)
					{
						if (pMapCellInfo->m_xpObjectList->GetCount())
						{
							PLISTNODE pListNode = pMapCellInfo->m_xpObjectList->GetHead();

							while (pListNode)
							{
								_LPTOSOBJECT pOSObject = pMapCellInfo->m_xpObjectList->GetData(pListNode);

								if (pOSObject)
								{
									if (pOSObject->btType == OS_MOVINGOBJECT)
									{
										CCharObject* pCharObject = (CCharObject*)pOSObject->pObject;

										if (!pCharObject->m_fIsGhost)
										{
											if (IsProperFriend(pCharObject))
											{
												pCharObject->MagDefenceUp(nState, nSec);
												nCount++;
											}
										}
									}
								}
								
								pListNode = pMapCellInfo->m_xpObjectList->GetNext(pListNode);
							} // while (pListNode)
						} // if (pMapCellInfo->m_pObjectList.GetCount())
					}
				} // if (pMapCellInfo)
			}// for (y)
		} // for (x)
	}
	__finally
	{
	}

	return nCount;
}

/* **************************************************************************************

										���ż�

   ************************************************************************************** */

BOOL CCharObject::MagMakePrivateTransparent(int nHTime)
{
	if (m_wStatusArr[STATE_TRANSPARENT] > 0)
		return FALSE;

	CWHList<CCharObject*>	ObjectList;

	m_pMap->GetMapObject(m_nCurrX, m_nCurrY, 9, &ObjectList);

	if (ObjectList.GetCount())
	{
		PLISTNODE		pListNode = ObjectList.GetHead();
		CCharObject*	pTargetObject;

		while (pListNode)
		{
			if (pTargetObject = ObjectList.GetData(pListNode))
			{
				if (pTargetObject->m_wObjectType & _OBJECT_ANIMAL)
				{
					if (pTargetObject->m_pTargetObject == this)
					{
						if ((abs(pTargetObject->m_nCurrX - m_nCurrX) > 1) || (abs(pTargetObject->m_nCurrY - m_nCurrY) > 1) || (rand() % 2) == 0)
							pTargetObject->m_pTargetObject = NULL;
					}
				}
			}
		
			pListNode = ObjectList.RemoveNode(pListNode);
		}
	}

	m_wStatusArr[STATE_TRANSPARENT] = nHTime;

	m_nCharStatus = GetCharStatus();
	AddRefMsg(RM_CHARSTATUSCHANGED, m_sHitSpeed/*wparam*/, m_nCharStatus, 0, 0, NULL);

	m_fHumHideMode		= TRUE;
	m_fFixedHideMode	= TRUE;

	return FALSE;
}

/* **************************************************************************************

										�����ż�

   ************************************************************************************** */

BOOL CCharObject::MagMakeGroupTransparent(int nX, int nY, int nHTime)
{
	BOOL					fFlag = FALSE;
	CWHList<CCharObject*>	ObjectList;

	m_pMap->GetMapObject(nX, nY, 1, &ObjectList);

	if (ObjectList.GetCount())
	{
		PLISTNODE		pListNode = ObjectList.GetHead();
		CCharObject*	pTargetObject;

		while (pListNode)
		{
			if (pTargetObject = ObjectList.GetData(pListNode))
			{
				if (IsProperFriend(pTargetObject))
				{
					if (pTargetObject->m_wStatusArr[STATE_TRANSPARENT] == 0)
					{
						AddDelayProcess(pTargetObject, RM_TRANSPARENT, 0, nHTime, 0, 0, NULL, 800);
						fFlag = TRUE;
					}
				}
			}
		
			pListNode = ObjectList.RemoveNode(pListNode);
		}
	}

	return fFlag;
}

/* **************************************************************************************

										������ȸ

   ************************************************************************************** */

BOOL CCharObject::MagTurnUndead(CCharObject* pTargetObject, int nX, int nY, int nLevel)
{
	CMonsterObject *pMonsterObject = (CMonsterObject*)pTargetObject;

	if (pMonsterObject->m_btLifeAttrib == LA_UNDEAD)
	{
		pMonsterObject->Struck(this);

//		if (pTargetObject->m_pTargetObject == NULL)
//		{
//         TAnimal(target).BoRunAwayMode := TRUE;
//         TAnimal(target).RunAwayStart := GetTickCount;
//         TAnimal(target).RunAwayTime := 10 * 1000;
//		}

		SelectTarget(pMonsterObject);

		if ((pMonsterObject->m_Ability.Level < m_Ability.Level - 1 + (rand() % 4)) && (pMonsterObject->m_Ability.Level < 50))
		{
			int nlvGap = m_Ability.Level - pMonsterObject->m_Ability.Level;

			if (rand() % 100 < (15 + nLevel * 7 + nlvGap))
			{
				pMonsterObject->SetLastHiter(this);
				pMonsterObject->m_WAbility.HP = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}

void CCharObject::SendSocket(_LPTDEFAULTMESSAGE lpDefMsg, char *pszPacket)
{
	DWORD					dwBytesSends = 0;
	_TMSGHEADER				MsgHdr;
	_LPTSENDBUFF			lpSendBuff = new _TSENDBUFF;

	MsgHdr.nCode			= 0xAA55AA55;
	MsgHdr.wIdent			= GM_DATA;
	MsgHdr.wUserGateIndex	= m_pUserInfo->m_nUserGateIndex;
	MsgHdr.wUserListIndex	= m_pUserInfo->m_nUserServerIndex;
	MsgHdr.nSocket			= m_pUserInfo->m_sock;

	if (lpDefMsg)
	{
		if (pszPacket)
		{
			int nLength = memlen(pszPacket);

			if (nLength >= 8096) 
			{
				InsertLogMsg(_TEXT("SendSocket:Packet is too long."));
				return;
			}

			MsgHdr.nLength	= sizeof(_TDEFAULTMESSAGE) + nLength;

			lpSendBuff->nLen	= sizeof(_TMSGHEADER) + MsgHdr.nLength;

			memmove(lpSendBuff->szData, (char *)&MsgHdr, sizeof(_TMSGHEADER));
			memmove(&lpSendBuff->szData[sizeof(_TMSGHEADER)], lpDefMsg, sizeof(_TDEFAULTMESSAGE));
			memmove(&lpSendBuff->szData[sizeof(_TMSGHEADER) + sizeof(_TDEFAULTMESSAGE)], pszPacket, MsgHdr.nLength - sizeof(_TDEFAULTMESSAGE));
			
			lpSendBuff->szData[lpSendBuff->nLen] = '\0';
		}
		else
		{
			MsgHdr.nLength		= sizeof(_TDEFAULTMESSAGE);

			lpSendBuff->nLen = sizeof(_TMSGHEADER) + MsgHdr.nLength;

			memmove(lpSendBuff->szData, (char *)&MsgHdr, sizeof(_TMSGHEADER));
			memmove(&lpSendBuff->szData[sizeof(_TMSGHEADER)], lpDefMsg, sizeof(_TDEFAULTMESSAGE));

			lpSendBuff->szData[lpSendBuff->nLen] = '\0';
		}
	}
	else
	{
		int nLen		= (memlen(pszPacket) - 1);
		
		MsgHdr.nLength	= -(nLen);

		lpSendBuff->nLen = sizeof(_TMSGHEADER) + nLen;

		memmove(lpSendBuff->szData, (char *)&MsgHdr, sizeof(_TMSGHEADER));
		memmove(&lpSendBuff->szData[sizeof(_TMSGHEADER)], pszPacket, nLen);
		
		lpSendBuff->szData[lpSendBuff->nLen] = '\0';
	}

	m_pUserInfo->m_pGateInfo->m_xSendBuffQ.PushQ((BYTE *)lpSendBuff);
//	m_pUserInfo->m_pGateInfo->Send(lpSendBuff);
}

void CCharObject::GetQueryUserName(CCharObject* pObject, int nX, int nY)
{
	_TDEFAULTMESSAGE	DefMsg;
	char				szEncodeMsg[32];
	char				szCharName[64];
	
	pObject->GetCharName(szCharName);

	fnMakeDefMessage(&DefMsg, SM_USERNAME, (int)pObject, pObject->GetThisCharColor(), 0, 0);

	int nPos = fnEncode6BitBufA((unsigned char *)szCharName, szEncodeMsg, memlen(szCharName) - 1, sizeof(szEncodeMsg));
	szEncodeMsg[nPos] = '\0';

	SendSocket(&DefMsg, szEncodeMsg);
/*procedure TUserHuman.GetQueryUserName (target: TCreature; x, y: integer);
var
   uname: string;
   tagcolor: integer;
begin
   if CretInNearXY (target, x, y) then begin
      tagcolor := GetThisCharColor (target);
      Def := MakeDefaultMsg (SM_USERNAME, Integer(target), tagcolor, 0, 0);
      uname := target.GetUserName;
      SendSocket (@Def, EncodeString (uname));
   end else
      SendDefMessage (SM_GHOST, integer(target), x, y, 0, '');
end; */
}
