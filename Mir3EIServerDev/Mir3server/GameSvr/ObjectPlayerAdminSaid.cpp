#include "stdafx.h"

#define _MAX_ADMINCOMMAND_LIST	(IDS_COMMAND_HAIRSTYLE - IDS_COMMAND_MONGEN + 1)

void InitAdminCommandList()
{
	TCHAR	szCommand[64];
	int		nLen;

	HINSTANCE hInstance = LoadLibrary(_T("AdminCmd.DLL"));

	if (hInstance)
	{
		int i;
		for (i = 0; i < _MAX_ADMINCOMMAND_LIST; i++)
		{
			LoadString(hInstance, IDS_COMMAND_MONGEN + i, szCommand, sizeof(szCommand)/sizeof(TCHAR));

			nLen = lstrlen(szCommand) * sizeof(TCHAR) + 1;

			char *pszAdminCommand = new char[nLen];

			if (pszAdminCommand)
			{
				WideCharToMultiByte(CP_ACP, 0, szCommand, -1, pszAdminCommand, nLen, NULL, NULL);
				g_xAdminCommandList.AddNewNode(pszAdminCommand);
			}
		}

		InsertLogMsgParam(IDS_LOAD_ADMINCOMMAND, &i, LOGPARAM_INT);

		FreeLibrary(hInstance);
	}
}

void UnInitAdminCommandList()
{
	PLISTNODE pListNode = g_xAdminCommandList.GetHead();

	while (pListNode)
	{
		delete [] g_xAdminCommandList.GetData(pListNode);

		pListNode = g_xAdminCommandList.RemoveNode(pListNode);
	}
}

BOOL CPlayerObject::ProcessForAdminSaid(char *pszMsg)
{
	if (pszMsg[0] == '@')
	{
		PLISTNODE	pListNode	= g_xAdminCommandList.GetHead();
		int			nCommand	= 0;

		char		*pszParam1 = NULL, *pszParam2 = NULL, *pszParam3 = NULL, *pszParam4 = NULL;

		if ((pszParam1 = strchr(&pszMsg[1], ' ')))
		{
			*pszParam1 = '\0';
			pszParam1++;
		}

		char *pszData;

		while (pListNode)
		{
			pszData = (char *)g_xAdminCommandList.GetData(pListNode);

			if (memcmp(&pszMsg[1], pszData, memlen(pszData)) == 0)
				break;

			nCommand++;

			pListNode = g_xAdminCommandList.GetNext(pListNode);
		}

		if (nCommand >= _MAX_ADMINCOMMAND_LIST) return FALSE;

		if (pszParam1)
		{
			if (pszParam2 = strchr(pszParam1, ' '))
			{
				*pszParam2 = '\0';
				pszParam2++;

				if (pszParam3 = strchr(pszParam2, ' '))
				{
					*pszParam3 = '\0';
					pszParam3++;

					if (pszParam4 = strchr(pszParam3, ' '))
					{
						*pszParam4 = '\0';
						pszParam4++;
					}
				}
			}
		}

		switch (IDS_COMMAND_MONGEN + nCommand)
		{
			case IDS_COMMAND_MONGEN:						//"����"
				if (pszParam1 && pszParam2)
					CmdCallMakeMonster(pszParam1, pszParam2);
				break;
			case IDS_COMMAND_INSPECTOR:						//"������"
			{
				TCHAR	wszMsg[64];
				char	szMsg[64];

				m_fInspector = ~m_fInspector;

				if (m_fInspector)
					LoadString(g_hInst, IDS_INSPECTOR_ON, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));
				else
					LoadString(g_hInst, IDS_INSPECTOR_OFF, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));

				WideCharToMultiByte(CP_ACP, 0, wszMsg, -1, szMsg, sizeof(szMsg), NULL, NULL);
				SysMsg(szMsg, 1);

				break;
			}
			case IDS_COMMAND_ADMIN:							//"���"
				break;
			case IDS_COMMAND_INVINCIBILITY:					//"����"
			{
				TCHAR	wszMsg[64];
				char	szMsg[64];

				m_fIsNeverDie = ~m_fIsNeverDie;

				if (m_fIsNeverDie)
					LoadString(g_hInst, IDS_NEVERDIE_ON, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));
				else
					LoadString(g_hInst, IDS_NEVERDIE_OFF, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));

				WideCharToMultiByte(CP_ACP, 0, wszMsg, -1, szMsg, sizeof(szMsg), NULL, NULL);
				SysMsg(szMsg, 1);

				break;
			}
			case IDS_COMMAND_ATTACK:						//"����"
				break;
			case IDS_COMMAND_MOVE:							//"�̵�"
				if (pszParam1)
					CmdRandomSpaceMove(pszParam1);
				break;
			case IDS_COMMAND_CHANGELEVEL:					//"��������"
			{
				if (pszParam1)
				{
					m_Ability.Level = m_pUserInfo->m_THumanRcd.szLevel = _MIN(40, AnsiStrToVal(pszParam1));				
					HasLevelUp(1);
				}
				break;
			}
			case IDS_COMMAND_MOVEFREESTYLE:					//"�����̵�"
				if (pszParam1 && pszParam2 && pszParam3)
					CmdFreeSpaceMove(pszParam1, pszParam2, pszParam3);
				break;
			case IDS_COMMAND_MAP:							//"��"
			{
				char szMsg[64];

				memcpy(szMsg, "MAP : ", 6);
				memcpy(&szMsg[6], m_pMap->m_szMapTextName, memlen(m_pMap->m_szMapTextName));

				SysMsg(szMsg, 0);
				
				break;
			}
			case IDS_COMMAND_LEVEL:							//"��"
				break;
			case IDS_COMMAND_MONLEVEL:						//"����"
				CmdSendMonsterLevelInfos();
				break;
			case IDS_COMMAND_RECALL:						//"��ȯ"
				break;
			case IDS_COMMAND_NUMOFMON:						//"����"
				break;
			case IDS_COMMAND_NUMOFHUMAN:					//"�����"
				break;
			case IDS_COMMAND_SABUKMONEY:					//"��ϼ���"
				break;
			case IDS_COMMAND_KICK:							//"Kick"
				break;
			case IDS_COMMAND_KICK2:							//"ű"
				break;
			case IDS_COMMAND_TING:							//"��"
				break;
			case IDS_COMMAND_KINGTING:						//"����"
				break;
			case IDS_COMMAND_LUCKYVALUE:					//"��"
				break;
			case IDS_COMMANT_SHUTUP:						//"ä��"
				break;
			case IDS_COMMAND_TALK:							//"ä������"
				break;
			case IDS_COMMAND_SHUTUPMAN:						//"ä����"
				break;
			case IDS_COMMAND_RELOADADMIN:					//"ReloadAdmin"
				break;
			case IDS_COMMAND_RELOADABUSIVE:					//"�弳�����б�"
				break;
			case IDS_COMMAND_MOOTAEBO:						//"���º�"
				break;
			case IDS_COMMAND_BACKWALK:						//"�ް���"
				break;
			case IDS_COMMAND_GAIN:							//"����"
				if (pszParam1 && pszParam2)
					CmdMakeItem(pszParam1, pszParam2);
				break;
			case IDS_COMMAND_DELGOLD:						//"������"
				break;
			case IDS_COMMAND_ADDGOLD:						//"���߰�"
				break;
			case IDS_COMMAND_GOOD:							//"����"
				break;
			case IDS_COMMAND_OTHERDELGOLD:					//"Ÿ�ε�����"
				break;
			case IDS_COMMAND_OTHERADDGOLD:					//"Ÿ�ε��߰�"
				break;
			case IDS_COMMAND_OTHERLEVELUP:					//"Ÿ�η�������"
				break;
			case IDS_COMMAND_OTHEREXPUP:					//"Ÿ�ΰ���ġ����"
				break;
			case IDS_COMMAND_WEAPONDUR:						//"���⳻������"
				break;
			case IDS_COMMAND_PARDON:						//"����"
				break;
			case IDS_COMMAND_PKPOINT:						//"����������"
				break;
			case IDS_COMMAND_PKPOINTUP:						//"��������������"
				break;
			case IDS_COMMAND_CHANGELUCKY:					//"����"
				break;
			case IDS_COMMAND_SKILLUP:						//"��������"
				if (pszParam1 && pszParam2)
					CmdMakeFullSkill(pszParam1, pszParam2);
				break;
			case IDS_COMMAND_OTHERSKILLUP:					//"Ÿ�ι�������"
				break;
			case IDS_COMMAND_DELSKILL:						//"���������ϱ�"
				break;
			case IDS_COMMAND_OTHERDELSKILL:					//"Ÿ�ι��������ϱ�"
				break;
			case IDS_COMMAND_CHGJOB:						//"����"
			{
				if (pszParam1)
				{
					if (CmdChangeJob(pszParam1))
						HasLevelUp(1);
				}
			
				break;
			}
			case IDS_COMMAND_CHGGENDER:						//"Ʈ��������"
			{
				if (m_pUserInfo->m_THumanRcd.btGender == 0) m_pUserInfo->m_THumanRcd.btGender = m_tFeature.btGender = 1;
				else m_pUserInfo->m_THumanRcd.btGender = m_tFeature.btGender = 0;

				SysMsg(pszData, 1);

				break;
			}
			case IDS_COMMAND_COLOR:							//"��"
				break;
			case IDS_COMMAND_MONRECALL:						//"����ȯ"
			{
				if (pszParam1 && pszParam2)
					CmdCallMakeSlaveMonster(pszParam1, pszParam2);

				break;
			}
			case IDS_COMMAND_MISSION:						//"�̼�"
				break;
			case IDS_COMMAND_GENPOS:						//"����"
			{
				if (pszParam1 && pszParam2 && pszParam3 && pszParam4)
					CmdCallMakeMonsterXY(pszParam1, pszParam2, pszParam3, pszParam4);
				break;
			}
			case IDS_COMMAND_TRANSPARENCY:					//"����"
				break;
			case IDS_COMMAND_CIVILWAR:						//"����������"
				break;
			case IDS_COMMAND_DYEINGHAIR:
				if (pszParam1)
					CmdDyeingHair(pszParam1);
				break;
			case IDS_COMMAND_DYEINGWEAR:
				if (pszParam1)
					CmdDyeingWear(pszParam1);
				break;
			case IDS_COMMAND_HAIRSTYLE:
				if (pszParam1)
					CmdHairStyle(pszParam1);
				break;
			case IDS_COMMAND_RESERVED3:						// �������̸�
				if (pszParam1 && pszParam2)
					CmdChangeItemPrefix(pszParam1, pszParam2);
				break;
			case IDS_COMMAND_RESERVED4:						// ������
			{
				TCHAR	wszMsg[64];
				char	szMsg[64];

				m_fIsCapture = ~m_fIsCapture;

				if (m_fIsCapture)
				{
					LoadString(g_hInst, IDS_CAPTURE_ON, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));

					m_hCaptureFile = fopen("capture.txt", "w+");
				}
				else
				{
					LoadString(g_hInst, IDS_CAPTURE_OFF, wszMsg, sizeof(wszMsg)/sizeof(TCHAR));
				
					fclose(m_hCaptureFile);
				}

				WideCharToMultiByte(CP_ACP, 0, wszMsg, -1, szMsg, sizeof(szMsg), NULL, NULL);
				SysMsg(szMsg, 1);

				break;
			}
			case IDS_COMMAND_RESERVED5:
			{
				int nX, nY;
				CScripterObject* pScripter = new CScripterObject;

				if (pScripter)
				{
					GetFrontPosition(nX, nY);

					pScripter->Create(nX, nY, m_pMap);

					g_xScripterList.AddNewNode(pScripter);
				}

				break;
			}
		}
	}

	return FALSE;
}
