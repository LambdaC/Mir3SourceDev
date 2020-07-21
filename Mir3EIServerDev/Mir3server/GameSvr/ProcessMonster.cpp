#include "stdafx.h"

CMirMap*					GetMap(char *pszMapName);

CMonsterObject* AddCreature(CMirMap* pMap, int nX, int nY, int nMonRace, BOOL fSearch)
{
	CMonsterObject* pMonsterObject = NULL;

	switch(g_pMonRaceInfo[nMonRace].wRaceIndex)
	{
		case _ANIMAL_DEER:
			pMonsterObject = (CMonsterObject*)new CAnimalObject; break;
		case _MONSTER_STICK:		// ������
			pMonsterObject = (CMonsterObject*)new CStickObject; break;
		case _MONSTER_SANDMOB:		// ������
			pMonsterObject = (CMonsterObject*)new CSandMobObject; break;
		case _MONSTER_RON:			// ��
			pMonsterObject = (CMonsterObject*)new CRonObject; break;
		case _MONSTER_SCULTURE1:	// �ָ�����, �ָ�ȣ��
		case _MONSTER_SCULTURE2:
			pMonsterObject = (CMonsterObject*)new CScultureObject; break;
		case _MONSTER_BEEQUEEN:		// �񸷿���
			pMonsterObject = (CMonsterObject*)new CBeeQueen; break;
		case _MONSTER_SCULTUREKING: // �ָ���
			pMonsterObject = (CMonsterObject*)new CScultureKingObject; break;
		case _MONSTER_DUALAXE:		// �ֵ����ذ�
			pMonsterObject = (CMonsterObject*)new CDualAxeObject; break;
		case _MONSTER_MAGUNGSA:		// ���û�
			pMonsterObject = (CMonsterObject*)new CDualAxeObject(6); break;
		case _MONSTER_THONEDARK:	// ��ũ
			pMonsterObject = (CMonsterObject*)new CDualAxeObject(3); break;
		case _MONSTER_LIGHTZOMBI:
			pMonsterObject = (CMonsterObject*)new CLightingZombiObject; break;
		case _MONSTER_ROCKMAN:		// �籫
			pMonsterObject = (CMonsterObject*)new CRockManObject; break;
		case _MONSTER_MINORNUMA:
			pMonsterObject = (CMonsterObject*)new CMinorNumaObject; break;
		case _MONSTER_WHITESKELETON:	// ���
			pMonsterObject = (CMonsterObject*)new CWhiteSkeleton; break;
		case _MONSTER_ELFMONSTER:		// �ż� ���� �� 
			pMonsterObject = (CMonsterObject*)new CElfMonster; break;			
		case _MONSTER_ELFWARRIOR:		// �ż� ���� �� 
			pMonsterObject = (CMonsterObject*)new CElfWarriorMonster; break;
		case _MONSTER_SPITSPIDER:		// ħ�Ź�
			pMonsterObject = (CMonsterObject*)new CSpitSpiderMonster; break;
		case _MONSTER_OMA:
		case _MONSTER_OMAKNIGHT:
		case _MONSTER_OMAWARRIOR:
			pMonsterObject = (CMonsterObject*)new COmaObject; break;
		default:
			pMonsterObject = (CMonsterObject*)new CGenneralMonObject;
//			pMonsterObject = (CMonsterObject*)new CChickenObject;
			break;
	}

	if (pMonsterObject)
	{
		if (fSearch)
			pMonsterObject->GetAvailablePosition(pMap, nX, nY, 10);

		pMonsterObject->m_nCurrX			= nX;
		pMonsterObject->m_nCurrY			= nY;
		pMonsterObject->m_nDirection		= rand() % 8;
		pMonsterObject->m_pMap				= pMap;
		pMonsterObject->m_nRace				= nMonRace;

		pMonsterObject->Initialize();

		pMap->AddNewObject(nX, nY, OS_MOVINGOBJECT, pMonsterObject);

		if (!pMonsterObject->m_fHideMode)
			pMonsterObject->AddRefMsg(RM_TURN, pMonsterObject->m_nDirection, nX, nY, 0, pMonsterObject->m_szName);

		return pMonsterObject;
	}

	return NULL;
}

BOOL RegenMonster(CMonsterGenInfo* pMonGenInfo, int nCount)
{
	DWORD dwStart	= GetTickCount();

	for (int i = 0; i < nCount; i++)
	{
		int nX = pMonGenInfo->nX - pMonGenInfo->nAreaX + (rand() % (pMonGenInfo->nAreaX * 2 + 1));
		int nY = pMonGenInfo->nY - pMonGenInfo->nAreaY + (rand() % (pMonGenInfo->nAreaY * 2 + 1));

		if (CMonsterObject* pMonsterObject = AddCreature(GetMap(pMonGenInfo->szMapName), nX, nY, pMonGenInfo->nMonIndex, TRUE))
			pMonGenInfo->xMonsterObjList.AddNewNode(pMonsterObject);

		if (GetTickCount() - dwStart > 3000/*ZenLimitTime*/)
			break;
	}

	return TRUE;
}

DWORD GetZenTime(DWORD dwZenTime)
{
	if (dwZenTime < 30 * 60 * 1000)
	{
		return dwZenTime;
/*      if ztime < 30 * 60 * 1000 then begin
         r := (GetUserCount - UserFullCount) / ZenFastStep;  //�� 200���� �ö����� 10%�� ���� �� �� ��Ŵ
         if r > 0 then begin
            if r > 6 then r := 6;
            Result := ztime - Round ((ztime/10) * r);
         end else
            Result := ztime;
      end else
         Result := ztime; */
	}

	return dwZenTime;
}

UINT WINAPI ProcessMonster(LPVOID lpParameter)
{
	int		nCurrMonGen		= 0;
	DWORD	dwCurrentTick	= GetTickCount();

	while (TRUE)
	{
		if (g_fTerminated) 
		{
			return 0L;
		}

		/* Generate Monster
		if (GetTickCount() - dwLastGenTick > 200)
		{
			dwLastGenTick = GetTickCount();

			if (nCurrMonGen < g_nNumOfMonGenInfo - 1) 
				nCurrMonGen++;
			else
				nCurrMonGen = 0;

			CMonsterGenInfo* pMonGenInfo = &g_pMonGenInfo[nCurrMonGen];

			if (pMonGenInfo)
			{
				if ((pMonGenInfo->dwStartTime == 0) || ((dwLastGenTick - pMonGenInfo->dwStartTime) > GetZenTime(pMonGenInfo->dwZenTime)))
				{
					if (pMonGenInfo->nCount > (int)pMonGenInfo->xMonsterObjList.GetCount())
					{
						if (RegenMonster(pMonGenInfo, pMonGenInfo->nCount - pMonGenInfo->xMonsterObjList.GetCount()))
							pMonGenInfo->dwStartTime = GetTickCount();
					}
				}
			}
		}
		*/

		// Execute Monster A.I
		for (int i = 0; i < g_nNumOfMonGenInfo + 1; i++)
		{
			CMonsterGenInfo* pMonGenInfo = &g_pMonGenInfo[i];

			if (pMonGenInfo)
			{
				if (pMonGenInfo->xMonsterObjList.GetCount())
				{
					PLISTNODE pListNode = pMonGenInfo->xMonsterObjList.GetHead();

					while (pListNode)
					{
						CMonsterObject* pMonsterObject = pMonGenInfo->xMonsterObjList.GetData(pListNode);

						if (pMonsterObject)
						{
							dwCurrentTick = GetTickCount();

							if (!pMonsterObject->m_fIsGhost)
							{
								if (dwCurrentTick - pMonsterObject->m_dwRunTime >= pMonsterObject->m_dwRunNextTick)
								{
									pMonsterObject->m_dwRunTime = dwCurrentTick;

									if (dwCurrentTick - pMonsterObject->m_dwSearchTime >= pMonsterObject->m_dwSearchTick)
									{
										pMonsterObject->m_dwSearchTime = dwCurrentTick;
										pMonsterObject->SearchViewRange();
									}

									pMonsterObject->Operate();
								}
							}
							else
							{
								if (GetTickCount() - pMonsterObject->m_dwGhostTime > 3 * 60 * 1000)
								{
									delete pMonsterObject;
									pMonsterObject = NULL;

									pListNode = pMonGenInfo->xMonsterObjList.RemoveNode(pListNode);
									continue;
								}
							}
						}

						pListNode = pMonGenInfo->xMonsterObjList.GetNext(pListNode);
					} // while (pListNode)
				}
			} // if (pMonGenInfo)
		}

		SleepEx(1, TRUE);
	}

	return 0L;
}
