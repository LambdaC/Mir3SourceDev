#include "stdafx.h"
#include ".\teammanage.h"

CTeamManage::CTeamManage(void)
{
	m_dwLastEventFilter = ID_SOCKCLIENT_EVENT_MSG_1;
}

CTeamManage::~CTeamManage(void)
{
	m_xTeamProcList.ClearAllNodes();
}


VOID CTeamManage::OnConnectToServer()
{
	//some wrong
	assert(0);
}

char* CTeamManage::OnMessageReceive(CHAR* pszPacketMsg)
{
	//some wrong
	assert(0);
	return NULL;
}

LRESULT CTeamManage::DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg )
	{
	case WM_KEYUP:
		OnKeyDown(wParam, lParam);//������˺ͼ��˺�����
		break;
	default:
		break;
	}

	LRESULT result = g_xGameProc.DefMainWndProc( hWnd, uMsg, wParam, lParam );
	
	CTeamProcess *pTeamProc = NULL;
	m_xTeamProcList.MoveCurrentToTop();
	for ( INT nCnt = 0; nCnt < m_xTeamProcList.GetCounter(); nCnt++ )
	{
		pTeamProc = m_xTeamProcList.GetCurrentData();
		if( pTeamProc )
			pTeamProc->DefMainWndProc( hWnd, uMsg, wParam, lParam );
	}
	
	
	return result;
}

LRESULT CTeamManage::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
		case 'P':
			if( GetKeyState(VK_LCONTROL) & 0x8000 )//����
			{
				CTeamProcess *pTeamProc = new CTeamProcess;
				m_xTeamProcList.AddNode( pTeamProc );
				m_dwLastEventFilter++;
				pTeamProc->Load(m_dwLastEventFilter);//���ӷ�����
			}
			break;
		case 'O':
			if( GetKeyState(VK_LCONTROL) & 0x8000 )//�Ͽ�Active hero
			{
				CTeamProcess *pTeamProc = NULL;
				m_xTeamProcList.MoveCurrentToTop();
				for ( INT nCnt = 0; nCnt < m_xTeamProcList.GetCounter(); nCnt++ )
				{
					pTeamProc = m_xTeamProcList.GetCurrentData();
					if( pTeamProc && pTeamProc->m_pMyHero->m_bActive )
					{
						m_xTeamProcList.DeleteCurrentNodeEx();
						pTeamProc->DeleteProc();//�Ͽ�����
						delete pTeamProc;//�ͷ��ڴ�
						break;
					}
					m_xTeamProcList.MoveNextNode();
				}
			}
			break;
		case VK_TAB:
			if( GetKeyState(VK_LCONTROL) & 0x8000 )
			{
				CTeamProcess *pTeamProc = NULL;
				m_xTeamProcList.MoveCurrentToTop();
				pTeamProc = m_xTeamProcList.GetCurrentData();
				if( pTeamProc == NULL )
					break;
				
				//����,hero �� socket,��һ��Ӧ������Ի�������,����ʾ�Ի���ʱ��������
				//CMyHeroʹ�����麯��,���ͷ��ʱ���,����MyHeroʱg_xGameProc.m_pMyHero������ܸı�
				DWORD Vtab1, Vtab2;
				memcpy( &Vtab1, g_xGameProc.m_pMyHero, sizeof(VOID*) );
				memcpy( &Vtab2, pTeamProc->m_pMyHero, sizeof(VOID*) );

				CMyHero* pTempHero = g_xGameProc.m_pMyHero;
				CClientSocket* pTempSocket = g_xGameProc.m_pSocket;
				
				g_xGameProc.m_pMyHero = pTeamProc->m_pMyHero;
				g_xGameProc.m_pSocket = pTeamProc->m_pSocket;
				g_xGameProc.m_pMyHero->AdjustMyPostion();

				pTeamProc->m_pMyHero = (CTeamHero*)(pTempHero);
				pTeamProc->m_pSocket = pTempSocket;
				pTeamProc->m_pMyHero->SetProc( pTeamProc );

				//��ԭ���
				memcpy( g_xGameProc.m_pMyHero, &Vtab1, sizeof(VOID*) );
				memcpy( pTeamProc->m_pMyHero, &Vtab2, sizeof(VOID*) );


				g_xGameProc.m_xInterface.MsgAdd(_CLR_RED, _CLR_BLACK, "������ɫ" );
			}
			break;
		default:
			break;
	}

	return 0;
}

VOID CTeamManage::RenderScene(INT nLoopTime)
{
	g_xGameProc.RenderScene( nLoopTime );

	CTeamProcess *pTeamProc = NULL;
	m_xTeamProcList.MoveCurrentToTop();
	for ( INT nCnt = 0; nCnt < m_xTeamProcList.GetCounter(); nCnt++ )
	{
		pTeamProc = m_xTeamProcList.GetCurrentData();
		if( pTeamProc )
			pTeamProc->RenderScene( nLoopTime );
		
		m_xTeamProcList.MoveNextNode();
	}

}
