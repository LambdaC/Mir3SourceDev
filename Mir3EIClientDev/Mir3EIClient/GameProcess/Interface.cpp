/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

#define BELT_POS_X	0
#define BELT_POS_Y	457
#define BELT_WND_WIDTH	512
#define BELT_WND_HEIGHT 48

/******************************************************************************************************************

	�Լ��� : CInterface::CInterface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CInterface::CInterface()
{
	Init();
}



/******************************************************************************************************************

	�Լ��� : CInterface::~CInterface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CInterface::~CInterface()
{
	Destroy();
}



/******************************************************************************************************************

	�Լ��� : CInterface::Init()

	�ۼ��� : 
	�ۼ��� : 

	����   : �������̽����� ������, ��ü�ʱ�ȭ.
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::Init()
{
	m_nIdxMsgBox		= 0;
	m_nFstLine			= 0;
	m_shBeltHeight		= 0;
	m_bShowKey			= FALSE;
	m_bMoveFocusedWnd	= FALSE;
	m_bBeltState		= _BELT_STATE_STAY;

	SetRect(&m_rcMain,  0, 0, 0, 0);
	SetRect(&m_rcChat,  0, 0, 0, 0);

	ZeroMemory(&m_stCommonItem, sizeof(ITEMSET));

	m_xClientSysMsg.Init();

	m_pxInterImg = NULL;
//YDQ	m_xInterImgEx.Init();

	m_xStatusWnd.Init();
	m_xStoreWnd.Init();
	m_xGuildWnd.Init();
	m_xGroupWnd.Init();
	m_xChatPopWnd.Init();
	m_xExchangeWnd.Init();
	m_xGroupPopWnd.Init();
	m_xInventoryWnd.Init();
	m_xGuildMasterWnd.Init();

	for ( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		m_xInterBtn[nCnt].Init();
	}

	m_xScrlBar.Init();

	m_xChat.ClearAllNodes();
	m_xWndOrderList.ClearAllNodes();
}



/******************************************************************************************************************

	�Լ��� : CInterface::Destroy()

	�ۼ��� : 
	�ۼ��� : 

	����   : �������̽����� ����, ��ü�� �Ҹ��, �ʱ�ȭ.
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::Destroy()
{
	m_xClientSysMsg.Destroy();

//	m_xInterImgEx.Destroy();
	m_pxInterImg = NULL;

	m_xInventoryWnd.Destroy();
	m_xStoreWnd.Destroy();
	m_xStatusWnd.Destroy();
	m_xGuildWnd.Destroy();
	m_xGroupWnd.Destroy();
	m_xExchangeWnd.Destroy();
	m_xGuildMasterWnd.Destroy();
	m_xGroupPopWnd.Destroy();
	m_xChatPopWnd.Destroy();

	for ( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		m_xInterBtn[nCnt].Destroy();
	}

	m_xChat.ClearAllNodes();
	m_xWndOrderList.ClearAllNodes();

	Init();
}


VOID CInterface::CreateInterface(CImageHandler* pxImgHandler)
{
	m_pxInterImg = &(pxImgHandler->m_xImageList[_IMAGE_INTER]);

	//------------------------------------------------------------------------------------------------------------
	// ä�ÿ���Ʈ ������ ��ġ����.
	MoveWindow(g_xChatEditBox.GetSafehWnd(), 
			   g_xMainWnd.m_rcWindow.left+_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_INPUT_EDITWND_YPOS,
			   _INPUT_EDITWND_WIDTH, _INPUT_EDITWND_HEIGHT, TRUE);

	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_MAIN) )
	{
		SetRect(&m_rcMain, 
				0, (600-m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight), 
				m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, 600);
	}
	//------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------------------
	// ��������.
	SetRect(&m_rcChat, 188, 490, 532, 560);

	//------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------------------
	// ����.
	m_xInventoryWnd.CreateInventoryWnd(_WND_ID_INVENTORY, m_pxInterImg, _WNDIMGIDX_INVENTORY, 0, 0, 280, 464, TRUE);
	//״̬
	m_xStatusWnd.CreateStatusWnd(_WND_ID_STATUS, m_pxInterImg, _WNDIMGIDX_ITEMSET, 510, 0, 330, 468, TRUE);
	//�洢
	m_xStoreWnd.CreateStoreWnd(_WND_ID_STORE, m_pxInterImg, _WNDIMGIDX_STORE, 0, 0, 290, 224, TRUE);
	//����
	m_xExchangeWnd.CreateExchangeWnd(_WND_ID_EXCHANGE, m_pxInterImg, _WNDIMGIDX_EXCHANGE, 0, 0, 0, 0, TRUE);
	//�л�
	m_xGuildMasterWnd.CreateGuildMasterWnd(_WND_ID_GUILDMASTER, m_pxInterImg, _WNDIMGIDX_GUILDMASTER, 0, 0, 0, 0, TRUE);
//	m_xGuildWnd.CreateGuildWnd(_WND_ID_GUILD, &m_xInterImgEx, _WNDIMGIDX_GUILD, 0, 0, 540, 442, TRUE);

	//��
	m_xGroupWnd.CreateGroupWnd(_WND_ID_GROUP, m_pxInterImg, _WNDIMGIDX_GROUP, 0, 0, 260, 245, TRUE);
	//YDQ	m_xGroupPopWnd.CreateGroupPopWnd(_WND_ID_GROUPPOP, &m_xInterImgEx, _WNDIMGIDX_GROUPPOP, 0, 0, 260, 114, TRUE);
	//����
	m_xChatPopWnd.CreateChatPopWnd(_WND_ID_CHATPOP, m_pxInterImg, _WNDIMGIDX_CHATPOP, 0, 0, 0, 0, TRUE);

	//����
	m_xOptionWnd.CreateOptionWnd(_WND_ID_OPTION, m_pxInterImg, _WNDIMGIDX_OPTION, 0, 0, 0, 0, TRUE);
	
	m_xQuestWnd.CreateQuestWnd(_WND_ID_QUEST, m_pxInterImg, _WNDIMGIDX_QUEST, 0, 0, 0, 0, TRUE);
	//��
	m_xHorseWnd.CreateHorseWnd(_WND_ID_HORSE, m_pxInterImg, _WNDIMGIDX_HORSE, 0, 0, 0, 0, TRUE);

	//NPC
	m_xNPCWnd.CreateNPCChatWnd(_WND_ID_NPCCHAT, m_pxInterImg, _WNDIMGIDX_NPCCHAT, 0, 0, 388, 204, TRUE);				// ���

	// ��ʼ����ť
	m_xInterBtn[ _BTN_ID_CHANGE	].CreateGameBtn(m_pxInterImg, 1170, 1170, m_rcMain.left+638, m_rcMain.top+7);//����
	m_xInterBtn[ _BTN_ID_MINIMAP].CreateGameBtn(m_pxInterImg, 1172, 1172, m_rcMain.left+638, m_rcMain.top+41);//С��ͼ
	m_xInterBtn[ _BTN_ID_MUGONG	].CreateGameBtn(m_pxInterImg, 1174, 1174, m_rcMain.left+638, m_rcMain.top+76);//Unknown

	m_xInterBtn[ _BTN_ID_EXIT	].CreateGameBtn(m_pxInterImg, 1176, 1176, m_rcMain.left+8, m_rcMain.top+72);//�˳���ť
	m_xInterBtn[ _BTN_ID_LOGOUT	].CreateGameBtn(m_pxInterImg, 1178, 1178, m_rcMain.left+109, m_rcMain.top+72);//logout
	m_xInterBtn[ _BTN_ID_GROUP	].CreateGameBtn(m_pxInterImg, 1180, 1181, m_rcMain.left+706, m_rcMain.top+8);	// ��
	m_xInterBtn[ _BTN_ID_GUILD	].CreateGameBtn(m_pxInterImg, 1182, 1183, m_rcMain.left+674, m_rcMain.top+11);	// �л�

	m_xInterBtn[ _BTN_ID_BELT	].CreateGameBtn(m_pxInterImg, 1205, 1205, m_rcMain.left+148, m_rcMain.top+2);	// BELT �����

	m_xInterBtn[ _BTN_ID_MAGIC	].CreateGameBtn(m_pxInterImg,1184, 1184, m_rcMain.left+739, m_rcMain.top+33);	// ħ��
	m_xInterBtn[ _BTN_ID_POPUP	].CreateGameBtn(m_pxInterImg,1168, 1168, m_rcMain.left+619, m_rcMain.top+6);	// ����������
	m_xInterBtn[ _BTN_ID_QUEST	].CreateGameBtn(m_pxInterImg,1186, 1187, m_rcMain.left+742, m_rcMain.top+11);	// ����.
	m_xInterBtn[ _BTN_ID_OPTION	].CreateGameBtn(m_pxInterImg,1188, 1189, m_rcMain.left+706, m_rcMain.top+72);	// ����
	m_xInterBtn[ _BTN_ID_HELP	].CreateGameBtn(m_pxInterImg,1190, 1191, m_rcMain.left+742, m_rcMain.top+61);	// help
	m_xInterBtn[ _BTN_ID_HORSE	].CreateGameBtn(m_pxInterImg,1192, 1193, m_rcMain.left+674, m_rcMain.top+61);	// horse
	m_xInterBtn[ _BTN_ID_BAG	].CreateGameBtn(m_pxInterImg,1194, 1195, m_rcMain.left+682, m_rcMain.top+33);	// .
	m_xInterBtn[ _BTN_ID_CHAR	].CreateGameBtn(m_pxInterImg,1196, 1197, m_rcMain.left+711, m_rcMain.top+31);	// ��ɫ��ť

	//������
	m_xScrlBar.CreateScrlBar(m_pxInterImg, 1207, _MAX_CHATLINE, 12, 56, 12);

	m_xMsgBox.Load(m_pxInterImg);	// ���
}



/******************************************************************************************************************

	�Լ��� : CInterface::MsgAdd()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : DWORD dwFontColor
	         DWORD dwFontBackColor
	         CHAR* pszMsg
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* pszMsg)
{
	if ( pszMsg )
	{	
		if ( pszMsg[0] != NULL )
		{
			INT  nCnt;
			CHAT stChat;
			INT	 nLineCnt;
			CHAR pszDivied[MAX_PATH*2];
			CHAR pszArg[5][MAX_PATH];

			m_xChatPopWnd.MsgAdd(dwFontColor, dwFontBackColor, pszMsg);

			ZeroMemory(pszDivied, MAX_PATH*2);
			ZeroMemory(pszArg,	  MAX_PATH*5);

			g_xMainWnd.StringDivide(m_rcChat.right-m_rcChat.left, nLineCnt, pszMsg, pszDivied);

			sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4]);

			if ( nLineCnt > 5 )		
			{
				nLineCnt = 5;
			}

			// ���ڿ� ����.
			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				// ĭ�� �������� ������.
				if ( m_xChat.GetCounter() - m_nFstLine == _MAX_CHATLINE )
				{
					m_nFstLine++;
				}

				stChat.dwFontColor = dwFontColor;
				stChat.dwBackColor = dwFontBackColor;
				strcpy(stChat.pszChat, pszArg[nCnt]);

				m_xChat.AddNode(stChat);
			}

			// �ִ�������� �˻��ؼ� ���̻��̸� �����Ѵ�.
			while ( m_xChat.GetCounter() >= 50 )
			{
				m_xChat.MoveCurrentToTop();
				m_xChat.DeleteCurrentNode();

				if ( m_nFstLine > 0 )
					m_nFstLine--;
			}
		}
	}
}



/******************************************************************************************************************

	�Լ��� : CInterface::ShowWndList()

	�ۼ��� : 
	�ۼ��� : 

	����   : Active�Ǿ��ִ� �������� ����Ʈ�� �����ش�.
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::ShowWndList()
{	
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		m_xWndOrderList.MoveCurrentToTop();

		INT* pnCurrID;

		for ( INT nCnt = 0; nCnt < m_xWndOrderList.GetCounter(); nCnt++ )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				m_xInventoryWnd.ShowInventoryWnd();
				break;
			case _WND_ID_STATUS:
				m_xStatusWnd.ShowStatusWnd();
				break;
			case _WND_ID_STORE:
				m_xStoreWnd.ShowStoreWnd();
				break;
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.ShowExchangeWnd();
				break;
			case _WND_ID_GUILDMASTER:
				m_xGuildMasterWnd.ShowGuildMasterWnd();
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.ShowGuildWnd();
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.ShowGroupWnd();
				break;
			case _WND_ID_GROUPPOP:
				m_xGroupPopWnd.ShowGroupPopWnd();
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.ShowChatPopWnd();
				break;
			case _WND_ID_NPCCHAT:					// ���
				m_xNPCWnd.ShowNPCChatWnd();
				break;

			case _WND_ID_QUEST:
				m_xQuestWnd.ShowQuestWnd();
				break;
			case _WND_ID_OPTION:
				m_xOptionWnd.ShowOptionWnd();
				break;
			case _WND_ID_HORSE:
				m_xHorseWnd.ShowHorseWnd();
				break;
			}			

			m_xWndOrderList.MoveNextNode();
		}
	}	
}



/******************************************************************************************************************

	�Լ��� : CInterface::ShowChatList()

	�ۼ��� : 
	�ۼ��� : 

	����   : ä�� ����Ʈ�� �����ش�.
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::ShowChatList()
{
	if ( !m_xChat.CheckEmpty() )
	{
		INT		nCnt, nShowLine;
		LPCHAT	pstChat;

		m_xChat.MoveCurrentToTop();
		m_xChat.MoveNode(m_nFstLine);

		nShowLine = ((m_xChat.GetCounter() - m_nFstLine ) >= _MAX_CHATLINE) ?  _MAX_CHATLINE : m_xChat.GetCounter() - m_nFstLine;
		
		for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
		{
			pstChat = m_xChat.GetCurrentData();

			g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
							   m_rcChat.left, m_rcChat.top+nCnt*15,
							   pstChat->dwBackColor, pstChat->dwFontColor, pstChat->pszChat);

			m_xChat.MoveNextNode();
		}
	}
}



/******************************************************************************************************************

	�Լ��� : CInterface::RenderInterface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : INT nLoopTime
	         POINT ptMousePos
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::RenderInterface(INT nLoopTime, POINT ptMousePos)
{
	INT nX, nY, nCnt;

	ShowBeltItem();

	ShowWndList();

	//����µ���Ʒ
	if ( m_stCommonItem.bSetted && !m_stCommonItem.bIsHideItem )
	{
		nX = ptMousePos.x - _INVENTORY_CELL_WIDTH /2;
		nY = ptMousePos.y - _INVENTORY_CELL_HEIGHT/2;
		m_stCommonItem.xItem.DrawItem(nX, nY);
	}


	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_MAIN) )
	{
 		g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left, m_rcMain.top,	m_rcMain.right-m_rcMain.left, m_rcMain.bottom-m_rcMain.top,
											   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}
	//ydq��ʱ��ӵ�
	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_CHATPOP-1) )
	{
		g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+178, m_rcMain.top-18,
			m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
			(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}

	//������Ϣ
	ShowChatList();
	ShowGameStatus();


	for ( nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++)
	{
		m_xInterBtn[nCnt].ShowGameBtn();
	}

	// ��ũ�ѹ�.
	m_xScrlBar.ShowScrlBar(m_rcMain.left+620, m_rcMain.top+40, m_nFstLine, m_xChat.GetCounter());

	// Ŭ���̾�Ʈ�޽���(���ʻ��).
	m_xClientSysMsg.ShowSysMsg(nLoopTime, 30, 30);

	// ���
	m_xMsgBox.RenderMessageBox(0);

	ShowMagicKey();

}



/******************************************************************************************************************

	�Լ��� : CInterface::ShowBeltItem()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::ShowBeltItem()
{
	INT nX, nY;

	if ( m_bBeltState == _BELT_STATE_UP )
	{
		m_shBeltHeight += 10;

		if ( m_shBeltHeight >= 46 )	
		{
			m_shBeltHeight = 46;
		}
	}
	else if ( m_bBeltState == _BELT_STATE_DOWN )
	{
		m_shBeltHeight -= 10;
		if ( m_shBeltHeight <= 0 )
		{
			m_shBeltHeight = 0;
			m_bBeltState   = _BELT_STATE_STAY;
		}
	}

	if ( m_bBeltState != _BELT_STATE_STAY )
	{
		if ( m_pxInterImg->NewSetIndex(_IMGIDX_BELT) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(BELT_POS_X - 115, BELT_POS_Y-m_shBeltHeight,
												   m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
												   m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
			m_xInventoryWnd.SetBeltRect(BELT_POS_X, BELT_POS_Y-m_shBeltHeight, BELT_POS_X+BELT_WND_WIDTH, BELT_POS_Y-m_shBeltHeight+BELT_WND_HEIGHT);

			// ��Ʈ ������ �׸���.
			for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
			{
				if ( m_xInventoryWnd.m_stBeltItem[nCnt].bSetted )
				{
					nX = BELT_POS_X + 8 + nCnt*40;
					nY = BELT_POS_X - 6  - m_shBeltHeight;

					m_xInventoryWnd.m_stBeltItem[nCnt].xItem.DrawItem(nX, nY);
				}
			}
		}

	}
}



/******************************************************************************************************************

	�Լ��� : CInterface::ShowGameStatus()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::ShowGameStatus()
{
	FLOAT	fMyHPRate;
	FLOAT	fMyMPRate;				
	FLOAT	fMyWetRate;				
	FLOAT	fMyExpRate;
	WORD	wJobIcon;
	WORD	wImgNum;
	CHAR	pszBuff[MAX_PATH];
	RECT	rcStats;
	DWORD	dwFntClr;

	BYTE	bMyJob  = g_xGameProc.m_pMyHero->m_bJob;
	BYTE	bMyLevel= g_xGameProc.m_pMyHero->m_stAbility.bLevel;
	WORD	wMyAC   = g_xGameProc.m_pMyHero->m_stAbility.wAC;
	WORD	wMyDC   = g_xGameProc.m_pMyHero->m_stAbility.wDC;
	WORD	wMyMC   = g_xGameProc.m_pMyHero->m_stAbility.wMC;
	WORD	wMySC   = g_xGameProc.m_pMyHero->m_stAbility.wSC;
	BYTE	bDay	= g_xGameProc.m_bDayState;

	WORD	wHP		= g_xGameProc.m_pMyHero->m_stAbility.wHP;
	WORD	wMP		= g_xGameProc.m_pMyHero->m_stAbility.wMP;
	WORD	wWet	= g_xGameProc.m_pMyHero->m_stAbility.wWeight;
	DWORD	dwExp	= g_xGameProc.m_pMyHero->m_stAbility.dwExp;

	BYTE	bJob	= g_xGameProc.m_pMyHero->m_bJob;
	
	// �Ϸ��� ����ġ(��, ��, ����, ����)
	switch ( bDay )
	{
	case _DAYSTATE_DAY:
//		wImgNum = 130;
		wImgNum = 1200;
		break;
	case _DAYSTATE_DUSK:
//		wImgNum = 131;
		wImgNum = 1201;
		break;
	case _DAYSTATE_NIGHT:
//		wImgNum = 132;
		wImgNum = 1202;
		break;
	case _DAYSTATE_DAWN:
//		wImgNum = 133;
		wImgNum = 1204;
		break;
	}
	if ( m_pxInterImg->NewSetIndex(wImgNum) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+384/*684*/, m_rcMain.top-9/*+70*/,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}

	// HP, MP���.
	// �����˻�.
	if ( wHP )	
	{
		fMyHPRate = (FLOAT)((FLOAT)wHP/(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.wMaxHP);

		if ( fMyHPRate > 1.0f ) 
		{
			fMyHPRate = 1.0f;
		}
	}
	else			
	{
		fMyHPRate = 0;
	}

	if ( wMP )		
	{
		fMyMPRate = (FLOAT)((FLOAT)wMP/(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.wMaxMP);

		if ( fMyMPRate > 1.0f ) 
		{
			fMyMPRate = 1.0f;
		}
	}
	else			
	{
		fMyMPRate = 0;
	}

	if ( dwExp )	
	{
		fMyExpRate = (FLOAT)((FLOAT)dwExp/(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.dwMaxExp);

		if ( fMyExpRate > 1.0f ) 
		{
			fMyExpRate = 1.0f;
		}
	}
	else			
	{
		fMyExpRate = 0;
	}

	if ( wWet )		
	{
		fMyWetRate = (FLOAT)((FLOAT)wWet /(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.wMaxWeight);

		if ( fMyWetRate > 1.0f ) 
		{
			fMyWetRate = 1.0f;
		}
	}
	else			
	{
		fMyWetRate = 0;
	}

	if ( m_pxInterImg->NewSetIndex(1163) )
	{
		RECT rcHP = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyHPRate), 
					  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+33, m_rcMain.top+8, rcHP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	if ( m_pxInterImg->NewSetIndex(1164) )
	{
		RECT rcMP = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyMPRate), 
					  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+73, m_rcMain.top+8, rcMP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	// EXP, WET 
	if ( m_pxInterImg->NewSetIndex(1166) )
	{
		RECT rcEXP = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyExpRate), 
					   m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+152, m_rcMain.top+27, rcEXP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	if ( m_pxInterImg->NewSetIndex(1167) )
	{
		RECT rcWET = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyWetRate), 
					  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+166, m_rcMain.top+27, rcWET, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	dwFntClr = RGB(225, 225, 0);
	// ������6��.
	//��Ҫ���������仯���ı�
	sprintf(pszBuff, "%d", g_xGameProc.m_pMyHero->m_stAbility.bLevel);
	SetRect(&rcStats, m_rcMain.left+394, m_rcMain.top+2, m_rcMain.left+408, m_rcMain.top+16);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff, g_xMainWnd.CreateGameFont("�ü�ü", 10, 0, FW_BOLD));

	dwFntClr = RGB(255, 255, 200);
	sprintf(pszBuff, "%s : [%d,%d]", g_xGameProc.m_szMapName, g_xGameProc.m_pMyHero->m_wPosX, g_xGameProc.m_pMyHero->m_wPosY);
	SetRect(&rcStats, 9, 579, 139, 592);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);

	//FIXME ������ʲô��˼
	dwFntClr = RGB(255, 200, 50);
	// ������ �����ܹ� Ư��ġ ���.
	sprintf(pszBuff, "%d-%d", LOBYTE(wMyAC), HIBYTE(wMyAC));
	SetRect(&rcStats, 662, 577, 703, 590);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);

	SetRect(&rcStats, 750, 577, 791, 590);
	switch ( bJob )
	{
	case _JOB_DOSA:		
		{
			wJobIcon = 66;
			wImgNum	 = 123;
			sprintf(pszBuff, "%d-%d", LOBYTE(wMySC), HIBYTE(wMySC));
			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	case _JOB_SULSA:	
		{
			wJobIcon = 65;	
			wImgNum	 = 124;
			sprintf(pszBuff, "%d-%d", LOBYTE(wMyMC), HIBYTE(wMyMC));
			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	case _JOB_JUNSA:	
		{
			wJobIcon = 64;
			wImgNum	 = 122;
			sprintf(pszBuff, "%d-%d", LOBYTE(wMyDC), HIBYTE(wMyDC));
			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	}
	if ( m_pxInterImg->NewSetIndex(wJobIcon) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+82, m_rcMain.top+71,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
	// AC���.
	if ( m_pxInterImg->NewSetIndex(120) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+391, m_rcMain.top+136,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
	// DC, MC, SC
	if ( m_pxInterImg->NewSetIndex(wImgNum) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+487, m_rcMain.top+136,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
}


VOID CInterface::ShowMagicKey()
{
	if ( m_bShowKey )
	{
		INT nCnt;

		for ( nCnt = 0; nCnt < 12; nCnt++ )
		{
			if ( m_pxInterImg->NewSetIndex(1450+nCnt) )
			{
 				g_xMainWnd.DrawWithABlendCompDataWithBackBuffer(nCnt*m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, 0,
																m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
																m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
																(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);

			}
		}
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ �����κ�/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************

	�Լ��� : CInterface::GetWindowInMousePos()

	�ۼ��� : 
	�ۼ��� : 

	����   : ���콺 �����͸� �����ȿ� ������ �ִ� �����츮��Ʈ�� ��ó�� �������� ID�� �����Ѵ�.
	�Է�   : POINT ptMouse
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
INT	CInterface::GetWindowInMousePos(POINT ptMouse)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		RECT rcWnd;
		INT* pnCurrID;
		m_xWndOrderList.MoveCurrentToTail();

		for ( INT nCnt = m_xWndOrderList.GetCounter()-1; nCnt >= 0 ; nCnt-- )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				rcWnd = m_xInventoryWnd.GetGameWndRect();
				break;
			case _WND_ID_STATUS:
				rcWnd = m_xStatusWnd.GetGameWndRect();
				break;
			case _WND_ID_STORE:
				rcWnd = m_xStoreWnd.GetGameWndRect();
				break;
			case _WND_ID_EXCHANGE:
				rcWnd = m_xExchangeWnd.GetGameWndRect();
				break;
			case _WND_ID_GUILDMASTER:
				rcWnd = m_xGuildMasterWnd.GetGameWndRect();
				break;
			case _WND_ID_GUILD:
				rcWnd = m_xGuildWnd.GetGameWndRect();
				break;
			case _WND_ID_GROUP:
				if( m_xGroupWnd.m_xSelectCharWnd.m_bActive)
					rcWnd = m_xGroupWnd.m_xSelectCharWnd.GetGameWndRect();
				else
					rcWnd = m_xGroupWnd.GetGameWndRect();
				break;
			case _WND_ID_GROUPPOP:
				rcWnd = m_xGroupPopWnd.GetGameWndRect();
				break;
			case _WND_ID_CHATPOP:
				rcWnd = m_xChatPopWnd.GetGameWndRect();
				break;
			case _WND_ID_NPCCHAT:	// ���
				rcWnd = m_xNPCWnd.GetGameWndRect();
				break;

			case _WND_ID_QUEST:
				rcWnd = m_xQuestWnd.GetGameWndRect();
				break;
			case _WND_ID_OPTION:
				rcWnd = m_xOptionWnd.GetGameWndRect();
				break;
			case _WND_ID_HORSE:
				rcWnd = m_xHorseWnd.GetGameWndRect();
				break;

			}

			if ( PtInRect(&rcWnd, ptMouse) )
			{
				return *pnCurrID;
			}

			m_xWndOrderList.MovePreviousNode();
		}
	}
	return -1;
}


/******************************************************************************************************************

	�Լ��� : CInterface::AddWindowToList()

	�ۼ��� : 
	�ۼ��� : 

	����   : �����츮��Ʈ�� �� �������� ���� �Է¹��� ���̵� nID�� �����츦 �߰��Ѵ�.
	�Է�   : INT nID
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::AddWindowToList(INT nID)
{
	m_xWndOrderList.AddNode(nID);
}


/******************************************************************************************************************

	�Լ��� : CInterface::DeleteWindowToList()

	�ۼ��� : 
	�ۼ��� : 

	����   : nID�� ���̵� ���� �����츦 ����Ʈ�󿡼� �����Ѵ�.
	�Է�   : INT nID
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::DeleteWindowToList(INT nID)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		m_xWndOrderList.MoveCurrentToTop();

		INT* pnCurrID;
		for ( INT nCnt = 0; nCnt < m_xWndOrderList.GetCounter(); nCnt++ )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			if ( *pnCurrID == nID )
			{
				m_xWndOrderList.DeleteCurrentNode();
				break;
			}

			m_xWndOrderList.MoveNextNode();
		}
	}	
}


/******************************************************************************************************************

	�Լ��� : CInterface::WindowActivate()

	�ۼ��� : 
	�ۼ��� : 

	����   : nID�� �����츦 �����츮��Ʈ�� �߰���Ű�ų� ������Ű��, �߰��� ���, �������� ���¸� �ֻ��� ���·� �����Ѵ�.
			 �����찡 Ű�Է��� �޾Ƽ� ȭ�鿡 ���ö� ȣ���ϴ� �Լ��̴�.
	�Է�   : INT nID
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInterface::WindowActivate(INT nID)
{
	// ���ο� �����쿡 ��Ŀ���� �ֱ����ؼ� ��� �������� ��Ŀ���� FALSE�����ش�.
	BOOL bRet = FALSE;

	AllWindowsFocusOff();

	switch ( nID )
	{
	case _WND_ID_INVENTORY:
		{
			if ( m_xInventoryWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_INVENTORY);
				m_xInventoryWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_INVENTORY);
				m_xInventoryWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_STATUS:
		{
			if ( m_xStatusWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_STATUS);
				m_xStatusWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_STATUS);
				m_xStatusWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_STORE:
		{
			if ( m_xStoreWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_STORE);
				m_xStoreWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_STORE);
				m_xStoreWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_EXCHANGE:
		{
			if ( m_xExchangeWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_EXCHANGE);
				m_xExchangeWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_EXCHANGE);
				m_xExchangeWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_QUEST:
		{
			if ( m_xQuestWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_QUEST);
				m_xQuestWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_QUEST);
				m_xQuestWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_OPTION:
		{
			if ( m_xOptionWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_OPTION);
				m_xOptionWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_OPTION);
				m_xOptionWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_HORSE:
		{
			if ( m_xHorseWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_HORSE);
				m_xHorseWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_HORSE);
				m_xHorseWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;

	case _WND_ID_GUILDMASTER:
		{
			if ( m_xGuildMasterWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GUILDMASTER);
				m_xGuildMasterWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_GUILDMASTER);
				m_xGuildMasterWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_GUILD:
		{
			if ( m_xGuildWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GUILD);
				m_xGuildWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_GUILD);
				m_xGuildWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_GROUP:
		{
			if ( m_xGroupWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GROUP);
				m_xGroupWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_GROUP);
				m_xGroupWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_GROUPPOP:
		{
			if ( m_xGroupPopWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GROUPPOP);
				m_xGroupPopWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_GROUPPOP);
				m_xGroupPopWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_CHATPOP:
		{
			if ( m_xChatPopWnd.GetGameWndActive() )
			{
				MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+_INPUT_EDITWND_XPOS, 
	 					   g_xMainWnd.m_rcWindow.top+_INPUT_EDITWND_YPOS, _INPUT_EDITWND_WIDTH, _INPUT_EDITWND_HEIGHT, TRUE);

				DeleteWindowToList(_WND_ID_CHATPOP);
				m_xChatPopWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left + m_xChatPopWnd.m_rcWnd.left + m_xChatPopWnd.m_rcEditBoxFrame.left, 
	 					   g_xMainWnd.m_rcWindow.top + m_xChatPopWnd.m_rcWnd.top + m_xChatPopWnd.m_rcEditBoxFrame.top, 
						   m_xChatPopWnd.m_rcEditBoxFrame.right - m_xChatPopWnd.m_rcEditBoxFrame.left, 
						   m_xChatPopWnd.m_rcEditBoxFrame.bottom - m_xChatPopWnd.m_rcEditBoxFrame.top, TRUE);

				SetFocus(g_xChatEditBox.GetSafehWnd());
				AddWindowToList(_WND_ID_CHATPOP);
				m_xChatPopWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_NPCCHAT:		// ���
		{
			if ( m_xNPCWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_NPCCHAT);
//				m_xNPCWnd.CloseWnd();
				m_xNPCWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				// �ӽ�
				AddWindowToList(_WND_ID_NPCCHAT);
//				m_xNPCWnd.SetNPCStr("�ϴ��� �췯�� ���� �β��� ���⸦ �ټ����̴� �ٶ����� ���� ���ο� �ߴ� <��/@STAR>�� �뷡�ϴ� �������� ��� �׾� ���°��� <���/@LOVE>�ؾ��� �׸��� �� ������ �ֿ� ������ �ɾ� ���� �ڴ�. ���� �㿡�� ���� �ٶ��� ��ġ���. ���ع��� ��λ��� ������ ����� �ϴ����� �����ϻ� �츮���� ���� ����ȭ ��õ�� ȭ������ ���ѻ�� �������� ���� �����ϼ�. �ø� �ʴ� �ƴ��� ��� ������ �ܴ� �Ҹ���  �ø� �ʴ� �ƴ��� �ܴ� ������ ������ �Ҹ��� �ʹ����� �Ƹ��ٿ� �׼Ҹ��� ���� �ʴ� �𸣴� ���̳�\n <���ĸ� �����غ���?/@@buildguildnow>  \n <����/@end>",0);
				m_xNPCWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	}

	return bRet;
}


/******************************************************************************************************************

	�Լ��� : CInterface::MoveTopWindow()

	�ۼ��� : 
	�ۼ��� : 

	����   : ������ �����츦 ���콺 ��ǥ�� �̵���Ų��.
	�Է�   : POINT ptMouse
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::MoveTopWindow(POINT ptMouse)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		INT* pnCurrID;
		m_xWndOrderList.MoveCurrentToTail();
		pnCurrID = m_xWndOrderList.GetCurrentData();
		if ( m_bMoveFocusedWnd )
		{
			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				m_xInventoryWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_STATUS:
				m_xStatusWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_STORE:
				m_xStoreWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GUILDMASTER:
				m_xGuildMasterWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GROUPPOP:
				m_xGroupPopWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.MoveGameWnd(ptMouse);
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
				break;
			case _WND_ID_NPCCHAT:		// ���
				m_xNPCWnd.MoveGameWnd(ptMouse);
				break;

			case _WND_ID_QUEST:
				m_xQuestWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_OPTION:
				m_xOptionWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_HORSE:
				m_xHorseWnd.MoveGameWnd(ptMouse);
				break;

			}
		}
	}
}



/******************************************************************************************************************

	�Լ��� : CInterface::WindowFocusChanged()

	�ۼ��� : 
	�ۼ��� : 

	����   : ������ �������� ���콺 Ŭ���� �Ǹ� ���� Top �����츦 ���콺 Ŭ�� ������� �ٲ��ְ� ��������� ��Ŀ���� �����ش�.
	�Է�   : INT nID
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInterface::WindowFocusChangedAndSetReadyMove(INT nID, POINT ptMouse)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		AllWindowsFocusOff();

		DeleteWindowToList(nID);
		AddWindowToList(nID);
		// ���콺 Ŭ���� �Ȼ����̸� �̵���ų �غ� �Ȼ����̴�.
		m_bMoveFocusedWnd = TRUE;

		switch ( nID )
		{
		case _WND_ID_INVENTORY:
			m_xInventoryWnd.SetGameWndFocused(TRUE);
			m_xInventoryWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_STATUS:
			m_xStatusWnd.SetGameWndFocused(TRUE);
			m_xStatusWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_STORE:
			m_xStoreWnd.SetGameWndFocused(TRUE);
			m_xStoreWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.SetGameWndFocused(TRUE);
			m_xExchangeWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GUILDMASTER:
			m_xGuildMasterWnd.SetGameWndFocused(TRUE);
			m_xGuildMasterWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.SetGameWndFocused(TRUE);
			m_xGuildWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GROUP:
			if( m_xGroupWnd.m_xSelectCharWnd.m_bActive )
			{
				m_xGroupWnd.m_xSelectCharWnd.SetGameWndFocused(TRUE);
				m_xGroupWnd.m_xSelectCharWnd.SetReadyMove(ptMouse);
			}
			else
			{
				m_xGroupWnd.SetGameWndFocused(TRUE);
				m_xGroupWnd.SetReadyMove(ptMouse);
			}
			break;
		case _WND_ID_GROUPPOP:
			m_xGroupPopWnd.SetGameWndFocused(TRUE);
			m_xGroupPopWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_CHATPOP:
			m_xChatPopWnd.SetGameWndFocused(TRUE);
			m_xChatPopWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_NPCCHAT:		// ���
			m_xNPCWnd.SetGameWndFocused(TRUE);
			m_xNPCWnd.SetReadyMove(ptMouse);
			break;

		case _WND_ID_QUEST:
			m_xQuestWnd.SetGameWndFocused(TRUE);
			m_xQuestWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_OPTION:
			m_xOptionWnd.SetGameWndFocused(TRUE);
			m_xOptionWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_HORSE:
			m_xHorseWnd.SetGameWndFocused(TRUE);
			m_xHorseWnd.SetReadyMove(ptMouse);
			break;

		}
	}	
}


VOID CInterface::AllWindowsFocusOff()
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		m_xWndOrderList.MoveCurrentToTop();

		INT* pnCurrID;
		for ( INT nCnt = 0; nCnt < m_xWndOrderList.GetCounter(); nCnt++ )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				m_xInventoryWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_STATUS:
				m_xStatusWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_STORE:
				m_xStoreWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GUILDMASTER:
				m_xGuildMasterWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GROUPPOP:
				m_xGroupPopWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_NPCCHAT:		// ���
				m_xNPCWnd.SetGameWndFocused(FALSE);
				break;

			case _WND_ID_QUEST:
				m_xQuestWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_OPTION:
				m_xOptionWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_HORSE:
				m_xHorseWnd.SetGameWndFocused(FALSE);
				break;

			}
			m_xWndOrderList.MoveNextNode();
		}
	}
}

BOOL CInterface::IsTopWindow(INT nID)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		INT* pnCurrID;
		m_xWndOrderList.MoveCurrentToTail();
		pnCurrID = m_xWndOrderList.GetCurrentData();

		if ( nID == *pnCurrID )
			return TRUE;
	}
	return FALSE;
}








///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �޽��� �Է°��úκ�/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************

	�Լ��� : CInterface::OnLButtonDown()

 	�ۼ��� : 
	�ۼ��� : 

	����   : Mouse LButtonDown�� �Ͼ���� �������̽����� ������ �����Ѵ�.
	�Է�   : POINT ptMouse
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInterface::OnLButtonDown(POINT ptMouse)
{
	if(m_xMsgBox.IsActive())	// ���
	{
		m_xMsgBox.OnButtonDown(ptMouse);
		return TRUE;
	}
	else
	{
		if ( m_xScrlBar.OnLButtonDown(ptMouse) )
		{
			FLOAT	fScrlRate;

			fScrlRate = m_xScrlBar.GetScrlRate();
			m_nFstLine  = (m_xChat.GetCounter()-1)*fScrlRate;

			return TRUE;
		}

		for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
		{
			if ( m_xInterBtn[nCnt].OnLButtonDown(ptMouse) )
				return TRUE;
		}

		//BeltWnd
		if( PtInRect(&m_xInventoryWnd.m_rcBeltWnd, ptMouse))
		{
			m_xInventoryWnd.OnLButtonDown(&m_stCommonItem, ptMouse);
			return TRUE;
		}

		INT nInterfaceWndInRect;
		nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

		if ( nInterfaceWndInRect != -1 )
		{
			switch ( nInterfaceWndInRect )
			{
			case _WND_ID_INVENTORY:
				if ( !m_xInventoryWnd.OnLButtonDown(&m_stCommonItem, ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_STATUS:
				if ( !m_xStatusWnd.OnLButtonDown(&m_stCommonItem, ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_STORE:
				if ( !m_xStoreWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_EXCHANGE:
				if ( !m_xExchangeWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_GUILDMASTER:
				if ( !m_xGuildMasterWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_GUILD:
				if ( !m_xGuildWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_GROUP:
				if ( !m_xGroupWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_GROUPPOP:
				if ( !m_xGroupPopWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_CHATPOP:
				if ( !m_xChatPopWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_NPCCHAT:	// ���
				if ( !m_xNPCWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;


			case _WND_ID_QUEST:
				if ( !m_xQuestWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_OPTION:
				if ( !m_xOptionWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_HORSE:
				if ( !m_xHorseWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;

			}
			return TRUE;
		}
		else
			AllWindowsFocusOff();
	}
	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInterface::OnLButtonUp()

	�ۼ��� : 
	�ۼ��� : 

	����   : Mouse LButtonUp�� �Ͼ���� �������̽����� ������ �����Ѵ�.
	�Է�   : POINT ptMouse
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInterface::OnLButtonUp(POINT ptMouse)
{
	m_bMoveFocusedWnd = FALSE;

	if ( m_xMsgBox.IsActive() )	// ���
	{
		HRESULT hResult;
		hResult = m_xMsgBox.OnButtonUp(ptMouse);
		if ( hResult != 0 )
		{
			switch ( m_nIdxMsgBox )
			{
			case 12:
				{
					switch ( hResult )	// ����Ʈ �ڽ��� ����.
					{
					case 2:
						{
						   DWORD dwCurrTick = timeGetTime();
						   if ( (dwCurrTick - g_xGameProc.m_pMyHero->m_dwLastPKStruckTime> 10000) &&
								(dwCurrTick - g_xGameProc.m_pMyHero->m_dwLastMagicTime   > 10000) &&
								(dwCurrTick - g_xGameProc.m_pMyHero->m_dwLastHitTime		> 10000) || 
								(g_xGameProc.m_pMyHero->m_bCurrMtn					== _MT_DIE ) )
								SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
						   else
						   {
							   DWORD dwFont, dwBack;

							   dwFont = GetChatColor(3);
							   dwBack = GetChatColor(2);

							   MsgAdd(dwFont, dwBack, "ʱ�䲻��,������?");
						   }
						}
						break;
					case 4:
						m_xMsgBox.HideMessageBox();
						break;
					}
				}
				break;
			}
		}
	}
	else
	{
		if ( m_xScrlBar.OnLButtonUp(ptMouse) )
		{
			return TRUE;
		}

		//BeltWnd
		if( PtInRect(&m_xInventoryWnd.m_rcBeltWnd, ptMouse))
		{
			m_xInventoryWnd.OnLButtonUp(&m_stCommonItem, ptMouse);
			return TRUE;
		}

		for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
		{
			if ( m_xInterBtn[nCnt].OnLButtonUp(ptMouse) )
			{
				switch ( nCnt )
				{
				case _BTN_ID_QUEST:		WindowActivate(_WND_ID_QUEST);					break;
				case _BTN_ID_OPTION:	WindowActivate(_WND_ID_OPTION);					break;
				case _BTN_ID_HORSE:		WindowActivate(_WND_ID_HORSE);					break;

				case _BTN_ID_CHANGE:	WindowActivate(_WND_ID_EXCHANGE);				break;
				case _BTN_ID_GUILD:		
					g_xGameProc.m_pSocket->SendGuildHome();
					break;
				case _BTN_ID_GROUP:		WindowActivate(_WND_ID_GROUP);					break;
				case _BTN_ID_POPUP:		WindowActivate(_WND_ID_CHATPOP);				break;
				case _BTN_ID_BAG:		WindowActivate(_WND_ID_INVENTORY);				break;
				case _BTN_ID_MUGONG:	m_bShowKey = !m_bShowKey;						break;
				case _BTN_ID_BELT:
					{
						if ( m_shBeltHeight >= 46 )	
						{
							m_shBeltHeight = 46;
						}
						else if ( m_shBeltHeight <= 0 )		
						{
							m_shBeltHeight = 0;
						}

						if ( m_shBeltHeight == 46 )
						{
							m_bBeltState = _BELT_STATE_DOWN;
						}
						else if ( m_shBeltHeight == 0 )
						{
							m_bBeltState = _BELT_STATE_UP;
						}
					}
					break;
				case _BTN_ID_EXIT:
					{
						CHAR	  szMsg[MAX_PATH];
						m_nIdxMsgBox = 12;

						strcpy( szMsg, "����Ҫ�˳�������?" );
						m_xMsgBox.ShowMessageBox(szMsg, 2);					// YES/No ?
					}
					break;
				case _BTN_ID_MAGIC:
					if ( m_xStatusWnd.GetStatusWndType() != _TYPE_SETMAGIC )
					{
						if ( !WindowActivate(_WND_ID_STATUS) )		WindowActivate(_WND_ID_STATUS);
					}
					else
						WindowActivate(_WND_ID_STATUS);
					m_xStatusWnd.SetStatusWndType(_TYPE_SETMAGIC);
					break;
				case _BTN_ID_CHAR:
//					if ( m_xStatusWnd.GetStatusWndType() != _TYPE_EQUIP )
//					{
//						if ( !WindowActivate(_WND_ID_STATUS) )		WindowActivate(_WND_ID_STATUS);
//					}
//					else
//						WindowActivate(_WND_ID_STATUS);
//					m_xStatusWnd.SetStatusWndType(_TYPE_EQUIP);
//					m_xStatusWnd.SetStatusWndType(_WND_ID_STATUS);

					m_xStatusWnd.SetStatusWndType(_TYPE_STATUS);
					WindowActivate(_WND_ID_STATUS);
					break;
				case _BTN_ID_MINIMAP:	WindowActivate(_BTN_ID_MINIMAP);				break;
				case _BTN_ID_LOGOUT:
					{
						//TEST���µ�½
						g_xGameProc.ReLoad();
					}
				}
			}
		}

		INT nInterfaceWndInRect;
		nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

		// �� �������� OnLButtonUp�� ���ϰ��� TRUE�̸� ��������� Close�ȴ�.
		if ( nInterfaceWndInRect != -1 )
		{
			switch ( nInterfaceWndInRect )
			{
			case _WND_ID_INVENTORY:		if ( m_xInventoryWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )	WindowActivate(_WND_ID_INVENTORY);		break;
			case _WND_ID_STATUS:		if ( m_xStatusWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )		WindowActivate(_WND_ID_STATUS);			break;
			case _WND_ID_STORE:			if ( m_xStoreWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_STORE);			break;
			case _WND_ID_EXCHANGE:		if ( m_xExchangeWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_EXCHANGE);		break;
			case _WND_ID_GUILDMASTER:
			{
				if ( m_xGuildMasterWnd.OnLButtonUp(ptMouse) )
					WindowActivate(_WND_ID_EXCHANGE);
				break;
			}
			case _WND_ID_GUILD:			if ( m_xGuildWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_GUILD);			break;
			case _WND_ID_GROUP:			if ( m_xGroupWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_GROUP);			break;
			case _WND_ID_GROUPPOP:		if ( m_xGroupPopWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_GROUPPOP);		break;
			case _WND_ID_CHATPOP:		if ( m_xChatPopWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_CHATPOP);		break;

			case _WND_ID_QUEST:			if ( m_xQuestWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_QUEST);			break;
			case _WND_ID_OPTION:		if ( m_xOptionWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_OPTION);			break;
			case _WND_ID_HORSE:			if ( m_xHorseWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_HORSE);			break;

			case _WND_ID_NPCCHAT:		if ( m_xNPCWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_NPCCHAT);		break; // ���
			}
			return TRUE;
		}
	}
	return FALSE;
}


/******************************************************************************************************************

	�Լ��� : CInterface::OnMouseMove()

	�ۼ��� : 
	�ۼ��� : 

	����   : Mouse Move�� �Ͼ���� �������̽����� ������ �����Ѵ�.
	�Է�   : POINT ptMouse
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInterface::OnMouseMove(POINT ptMouse)
{
	MoveTopWindow(ptMouse);

	if ( m_xScrlBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate = m_xScrlBar.GetScrlRate();
		m_nFstLine  = (m_xChat.GetCounter()-1)*fScrlRate;
		return TRUE;
	}

	for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
		m_xInterBtn[nCnt].OnMouseMove(ptMouse);

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
		case _WND_ID_INVENTORY:
			m_xInventoryWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_STATUS:
			m_xStatusWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_STORE:
			m_xStoreWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GUILDMASTER:
			m_xGuildMasterWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GROUP:
			m_xGroupWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GROUPPOP:
			m_xGroupPopWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_CHATPOP:
			m_xChatPopWnd.OnMouseMove(ptMouse);
			break;

		case _WND_ID_QUEST:
			m_xQuestWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_OPTION:
			m_xOptionWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_HORSE:
			m_xHorseWnd.OnMouseMove(ptMouse);
			break;

		case _WND_ID_NPCCHAT:		// ���
			m_xNPCWnd.OnMouseMove(ptMouse);
			break;
		}
		return TRUE;
	}
	else
	{
		m_xStatusWnd.SetStatusBtnInit();
		m_xInventoryWnd.SetInvenBtnInit();
		m_xChatPopWnd.SetStatusBtnInit();
		m_xGuildMasterWnd.SetStatusBtnInit();
		m_xOptionWnd.SetStatusBtnInit();
		m_xQuestWnd.SetStatusBtnInit();
		m_xHorseWnd.SetStatusBtnInit();
		m_xExchangeWnd.SetStatusBtnInit();
	}

	return FALSE;
}


BOOL CInterface::OnScrollDown()
{
	if ( IsTopWindow(m_xInventoryWnd.m_nID) )
	{
		m_xInventoryWnd.OnScrollDown();
	}
	else if ( IsTopWindow(m_xStatusWnd.m_nID) )
	{
		m_xStatusWnd.OnScrollDown();
	}
	else if (IsTopWindow(m_xNPCWnd.m_nID))		// ���
	{
		m_xNPCWnd.OnScrollDown();
	}
	else if(IsTopWindow(m_xStoreWnd.m_nID))
	{
		m_xStoreWnd.OnScrollDown();
	}
	else
	{
		if ( !m_xChatPopWnd.m_bActive )
		{
			if ( m_nFstLine > 0 )	
			{
				m_nFstLine--;
			}
		}
		else
		{
			m_xChatPopWnd.OnScrollDown();
		}
	}
	return TRUE;
}


BOOL CInterface::OnScrollUp()
{
	if ( IsTopWindow(m_xInventoryWnd.m_nID) )
	{
		m_xInventoryWnd.OnScrollUp();
	}
	else if ( IsTopWindow(m_xStatusWnd.m_nID) )
	{
		m_xStatusWnd.OnScrollUp();
	}
	else if (IsTopWindow(m_xNPCWnd.m_nID))		// ���
	{
		m_xNPCWnd.OnScrollUp();
	}
	else if(IsTopWindow(m_xStoreWnd.m_nID))
	{
		m_xStoreWnd.OnScrollUp();
	}
	else
	{
		if ( !m_xChatPopWnd.m_bActive )
		{
			if ( m_nFstLine < (m_xChat.GetCounter()-1) )
			{
				m_nFstLine++;
			}
		}
		else
		{
			m_xChatPopWnd.OnScrollUp();
		}
	}
	return TRUE;
}

BOOL CInterface::OnLButtonDoubleClick(POINT ptMouse)
{
	if ( IsTopWindow(m_xInventoryWnd.m_nID) )
		m_xInventoryWnd.OnLButtonDoubleClick(&m_stCommonItem, ptMouse);
	return TRUE;
}


BOOL CInterface::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	if ( m_xInventoryWnd.OnKeyUp(&m_stCommonItem, wParam, lParam) )
	{
		return TRUE;
	}
	return FALSE;
}


BOOL CInterface::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
	case VK_RETURN:	
		break;
	case VK_F9:	
		WindowActivate(_WND_ID_INVENTORY);			
		break;
	case VK_F11:
		if ( m_xStatusWnd.GetStatusWndType() != _TYPE_SETMAGIC )
		{
			if ( !WindowActivate(_WND_ID_STATUS) )
				WindowActivate(_WND_ID_STATUS);
		}
		else
			WindowActivate(_WND_ID_STATUS);

		m_xStatusWnd.SetStatusWndType(_TYPE_SETMAGIC);
		break;
	}

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(g_xGameProc.m_ptMousePos);

	if ( nInterfaceWndInRect != -1 )
	{
		if ( nInterfaceWndInRect == _WND_ID_STATUS )
		{
			if ( m_xStatusWnd.OnKeyDown(wParam, lParam, g_xGameProc.m_ptMousePos) )
				return TRUE;
		}
	}
		
	return FALSE;
}


VOID CInterface::OnSysKeyDown()
{
	// F10 Key ��������.
	if ( m_xStatusWnd.GetStatusWndType() != _TYPE_EQUIP )
	{
		if ( !WindowActivate(_WND_ID_STATUS) )
			WindowActivate(_WND_ID_STATUS);
	}
	else
		WindowActivate(_WND_ID_STATUS);

	m_xStatusWnd.SetStatusWndType(_TYPE_EQUIP);
}


LRESULT	CInterface::OnMsgInputted(WPARAM wParam, LPARAM lParam)
{
	if ( m_xNPCWnd.OnMsgInputted() )
		return TRUE;

	return 0L;
}