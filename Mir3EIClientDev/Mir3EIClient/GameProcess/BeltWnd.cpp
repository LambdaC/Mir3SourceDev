/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



/******************************************************************************************************************

	CInventoryWnd Class

*******************************************************************************************************************/
/******************************************************************************************************************

	�Լ��� : CInventoryWnd::CInventoryWnd()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CInventoryWnd::CInventoryWnd()
{
	Init();
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::~CInventoryWnd()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CInventoryWnd::~CInventoryWnd()
{
	Destroy();
}


VOID CInventoryWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();
	m_nStartLineNum	= 0;
	ZeroMemory(m_rcInvenCell, sizeof(RECT) *_INVEN_MAX_CELL);
	ZeroMemory(m_rcBeltCell,  sizeof(RECT) *_BELT_MAX_CELL );
	ZeroMemory(m_stInventoryItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);
	ZeroMemory(m_stBeltItem,	  sizeof(ITEMSET)*_MAX_BELT_ITEM );

	m_xInvenScrlBar.Init();

	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].Init();
	}
}


VOID CInventoryWnd::Destroy()
{
	INT nCnt;
	CGameWnd::Destroy();
	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].Destroy();
	}
	Init();
}


/******************************************************************************************************************

	�Լ��� : CInventoryWnd::CreateInventoryWnd()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : INT nID
	         CWHWilImageData* pxWndImage
	         INT nFrameImgIdx
	         INT nStartX
	         INT nStartY
	         INT nWidth
	         INT nHeight
	         BOOL bCanMove
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::CreateInventoryWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	// ������ ����.
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, -114, -24);

	// ��ư����.m_rcWnd.left+236, m_rcWnd.top+420
	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+242, nStartY+ 421);
	
	m_xInvenScrlBar.CreateScrlBar(pxWndImage, 270, _INVEN_MAX_CELL_YCNT, 10, 218, 10);

	// �κ��丮 �������� Set.
	for ( INT nYCnt = 0; nYCnt < _INVEN_CELL_YCNT; nYCnt++ )
	{
		for ( INT nXCnt = 0; nXCnt < _INVEN_CELL_XCNT; nXCnt++ )
		{
			SetRect(&m_rcInvenCell[nXCnt+nYCnt*_INVEN_CELL_XCNT], 
					_INVEN_CELL_XSTART+(nXCnt*_INVENTORY_CELL_WIDTH), 
					_INVEN_CELL_YSTART+(nYCnt*_INVENTORY_CELL_HEIGHT),
					_INVEN_CELL_XSTART+(nXCnt*_INVENTORY_CELL_WIDTH) +_INVENTORY_CELL_WIDTH, 
					_INVEN_CELL_YSTART+(nYCnt*_INVENTORY_CELL_HEIGHT)+_INVENTORY_CELL_HEIGHT);
		}
	}

	// ��Ʈ �������� Set.
	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		SetRect(&m_rcBeltCell[nCnt], 
				_BELT_CELL_XSTART+(nCnt*_BELT_CELL_XGAP), 
				_BELT_CELL_YSTART,
				_BELT_CELL_XSTART+(nCnt*_BELT_CELL_XGAP)+_INVENTORY_CELL_WIDTH, 
				_BELT_CELL_YSTART+_INVENTORY_CELL_HEIGHT);
	}
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::SetInvenBtnInit()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetInvenBtnInit()
{
	for( INT nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}


/******************************************************************************************************************

	�Լ��� : CInventoryWnd::ShowInventoryWnd()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ShowInventoryWnd()
{
	INT nCnt;

	//����
	ShowGameWnd();
//	if ( m_bActive )
//	{
//		if ( m_pxWndImage->NewSetIndex(m_nFrameImgIdx) )
//		{
//			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcWnd.left-115, m_rcWnd.top, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight,
//				(WORD*)m_pxWndImage->m_pbCurrImage, _CLIP_WIDTH, 600);
//		}
//	}



	//����
	RECT rcTitle = {m_rcWnd.left+50, m_rcWnd.top+18, m_rcWnd.left+110, m_rcWnd.top+58};

	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(200, 200, 255), RGB(0, 0, 0), "[����]", g_xMainWnd.CreateGameFont("����", 12, 0, FW_BOLD));
	
	// ��Ǯ
	CHAR szMoney[16];
	RECT rcMoney = {m_rcWnd.left+80, m_rcWnd.top+406, m_rcWnd.left+120, m_rcWnd.top+446};
	sprintf( szMoney, "%d", g_xGameProc.m_xMyHero.m_nGlod );
	g_xMainWnd.PutsHan(NULL, rcMoney, RGB(200, 200, 255), RGB(0, 0, 0), szMoney, g_xMainWnd.CreateGameFont("����", 10, 0, FW_BOLD));

	// ������.
	m_xInvenScrlBar.ShowScrlBar(m_rcWnd.left+254, m_rcWnd.top+165, m_nStartLineNum, 12);
	
	// Item.
	for ( nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			INT nStartX, nStartY;

			if ( nCnt >= m_nStartLineNum*_INVEN_CELL_XCNT && nCnt < (m_nStartLineNum+_INVEN_CELL_YCNT)*_INVEN_CELL_XCNT ) 
			{
				nStartX = m_rcWnd.left+m_rcInvenCell[nCnt-(m_nStartLineNum*_INVEN_CELL_XCNT)].left;
				nStartY = m_rcWnd.top +m_rcInvenCell[nCnt-(m_nStartLineNum*_INVEN_CELL_XCNT)].top;

				m_stInventoryItem[nCnt].xItem.DrawItem(nStartX, nStartY);

				RECT rc = {nStartX, nStartY, nStartX+_INVENTORY_CELL_WIDTH, nStartY+_INVENTORY_CELL_HEIGHT};
				g_xMainWnd.DrawWithGDI(rc, NULL, RGB(255, 0, 255), 1);
			}
		}
	}

	// С�����
	for ( nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
//		if ( m_stBeltItem[nCnt].bSetted )
		{
			INT nStartX, nStartY;

			nStartX = m_rcBeltWnd.left + m_rcBeltCell[nCnt].left;
			nStartY = m_rcBeltWnd.top + m_rcBeltCell[nCnt].top;

			m_stBeltItem[nCnt].xItem.DrawItem(nStartX, nStartY);
		
			RECT rc = {nStartX, nStartY, nStartX+_INVENTORY_CELL_WIDTH, nStartY+_INVENTORY_CELL_HEIGHT};
			g_xMainWnd.DrawWithGDI(rc, NULL, RGB(255, 0, 255), 1);

		}
	}

	// ��ť.
	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].ShowGameBtn();
//for debug
		RECT rc = m_xInventoryBtn[nCnt].m_rcBtn;
		g_xMainWnd.DrawWithGDI(rc, NULL, RGB(255, 0, 0), 1);

	}

	// ����µ���Ʒ��ϸ��, 
	ShowInvenItemState();	
}




/******************************************************************************************************************

	�Լ��� : CInventoryWnd::ShowInvenItemState()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ShowInvenItemState()
{
/*	INT nInventoryNum = GetInvenNum(g_xGameProc.m_ptMousePos);
	if ( nInventoryNum != -1 )
	{
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			m_stInventoryItem[nInventoryNum].xItem.ShowItemStatus(m_rcWnd.left+95, m_rcWnd.top+250);
		}
	}
*/
	INT nInventoryNum = GetInvenNum(g_xGameProc.m_ptMousePos);
	if ( nInventoryNum != -1 )
	{
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			INT nStartX, nStartY;

			if ( nInventoryNum >= m_nStartLineNum*_INVEN_CELL_XCNT && nInventoryNum < (m_nStartLineNum+_INVEN_CELL_YCNT)*_INVEN_CELL_XCNT ) 
			{
				nStartX = m_rcWnd.left+m_rcInvenCell[nInventoryNum-(m_nStartLineNum*_INVEN_CELL_XCNT)].left;
				nStartY = m_rcWnd.top +m_rcInvenCell[nInventoryNum-(m_nStartLineNum*_INVEN_CELL_XCNT)].top;

				m_stInventoryItem[nInventoryNum].xItem.ShowItemStatus(nStartX+15, nStartY+15);
			}
		}
	}

	INT nBeltInventoryNum = GetBeltNum(g_xGameProc.m_ptMousePos);
	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			m_stBeltItem[nBeltInventoryNum].xItem.ShowItemStatus(m_rcWnd.left+95, m_rcWnd.top+250);
		}		
	}
}














/******************************************************************************************************************

	������ �ְ��� ����, �κ��丮��ġ �������� ���̺�� �ε�.(�κ��丮 �� ��Ʈ)

*******************************************************************************************************************/
/******************************************************************************************************************

	�Լ��� : CInventoryWnd::CheckItemPos()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : CHAR* szName
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::CheckItemPos(CHAR* szName)
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];
	INT		nCnt1, nCnt2;
	ITEMSET	stInvenItem[_MAX_INVEN_ITEM];						// �ӽõ���Ÿ �ε�뺯��.
	ITEMSET	stBeltItem[_MAX_BELT_ITEM];							
	ITEMSET	stCheckedInvenItem[_MAX_INVEN_ITEM];				// �˻�� ����Ÿ �����뺯��.
	ITEMSET	stCehckedBeltItem[_MAX_BELT_ITEM];

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", szName, ".itm", "");

	hFile = CreateFile(szItemFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(stInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);
	ZeroMemory(stCheckedInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);
	ZeroMemory(stBeltItem , sizeof(ITEMSET)*_MAX_BELT_ITEM );
	ZeroMemory(stCehckedBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		ReadFile(hFile, &stInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM, &dwReadLen, NULL);
		ReadFile(hFile, &stBeltItem , sizeof(ITEMSET)*_MAX_BELT_ITEM , &dwReadLen, NULL);

		// �������� ���� �κ��丮����Ÿ�� Ŭ���̾�Ʈ���� �������� �����Ų ��Ʈâ����Ÿ�� ���ϸ鼭 �´� ��ġ�� ������Ų��.
		for ( nCnt1 = 0; nCnt1 < _MAX_BELT_ITEM; nCnt1++ )
		{
			if ( stBeltItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_stInventoryItem[nCnt2].bSetted )
					{
						// ���������������� �̾Ƴ���.
						if ( stBeltItem[nCnt1].xItem.m_stItemInfo.nMakeIndex  != m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex &&
							 !strcmp(stBeltItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) &&
							 (stBeltItem[nCnt1].xItem.m_stItemInfo.nDura    == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDura   ) &&
							 (stBeltItem[nCnt1].xItem.m_stItemInfo.nDuraMax == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDuraMax) )
						{
							stCehckedBeltItem[nCnt1] = m_stInventoryItem[nCnt2];
							ZeroMemory(&stBeltItem[nCnt1], sizeof(ITEMSET));
							DeleteInvenItem(nCnt2);
							break;
						}						   
					}
				}
			}
		} 

		memcpy(m_stBeltItem, stCehckedBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM);

		// �κ��丮.
		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( stInvenItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_stInventoryItem[nCnt2].bSetted )
					{
						// ���������������� �̾Ƴ���.
						if ( stInvenItem[nCnt1].xItem.m_stItemInfo.nMakeIndex != m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex &&
							 !strcmp(stInvenItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) &&
							 (stInvenItem[nCnt1].xItem.m_stItemInfo.nDura	 == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDura    ) &&
							 (stInvenItem[nCnt1].xItem.m_stItemInfo.nDuraMax == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDuraMax ) )
						{
							stCheckedInvenItem[nCnt1] = m_stInventoryItem[nCnt2];
							ZeroMemory(&stInvenItem[nCnt1], sizeof(ITEMSET));
							DeleteInvenItem(nCnt2);
							break;
						}						
					}
				}
			}
		}

		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( m_stInventoryItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( !stCheckedInvenItem[nCnt2].bSetted )
					{
						stCheckedInvenItem[nCnt2] = m_stInventoryItem[nCnt1];
						break;
					}
				}
			}
		}
		memcpy(m_stInventoryItem, stCheckedInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);

		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::SaveItemPos()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : CHAR* szName
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::SaveItemPos(CHAR* szName)
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", szName, ".itm", "");
	hFile = CreateFile(szItemFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwWriteLen;

		WriteFile(hFile, m_stInventoryItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM, &dwWriteLen, NULL);
		WriteFile(hFile, m_stBeltItem,		sizeof(ITEMSET)*_MAX_BELT_ITEM , &dwWriteLen, NULL);

		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}


/******************************************************************************************************************

	�Լ��� : CInventoryWnd::GetInvenNum()

	�ۼ��� : 
	�ۼ��� : 

	����   : ���콺 ��ġ���� ���� �κ��丮�� ����ȣ�� ���´�.
	�Է�   : POINT ptMouse
	���   : INT 

	[����][������] : ��������

*******************************************************************************************************************/
INT CInventoryWnd::GetInvenNum(POINT ptMouse)
{
	RECT	rc;
	for ( INT nCnt = 0; nCnt < _INVEN_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcInvenCell[nCnt].left, m_rcWnd.top+m_rcInvenCell[nCnt].top, 
			    m_rcWnd.left+m_rcInvenCell[nCnt].left+_INVENTORY_CELL_WIDTH, m_rcWnd.top+m_rcInvenCell[nCnt].top+_INVENTORY_CELL_HEIGHT);
		if ( PtInRect(&rc, ptMouse) )
		{
			return (nCnt+m_nStartLineNum*_INVEN_CELL_XCNT);
		}
	}

	return -1;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::GetBeltNum()

	�ۼ��� : 
	�ۼ��� : 

	����   : ���콺 ��ġ���� ���� ��Ʈ�� ����ȣ�� ���´�.
	�Է�   : POINT ptMouse
	���   : INT 

	[����][������] : ��������

*******************************************************************************************************************/
INT CInventoryWnd::GetBeltNum(POINT ptMouse)
{
	RECT	rc;
	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		SetRect(&rc, m_rcBeltWnd.left+m_rcBeltCell[nCnt].left, m_rcBeltWnd.top+m_rcBeltCell[nCnt].top, 
			    m_rcBeltWnd.left+m_rcBeltCell[nCnt].left+_INVENTORY_CELL_WIDTH, m_rcBeltWnd.top+m_rcBeltCell[nCnt].top+_INVENTORY_CELL_HEIGHT);
		if ( PtInRect(&rc, ptMouse) )
		{
			return (nCnt);
		}
	}

	return -1;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::DeleteInventoryCurrItem()

	�ۼ��� : 
	�ۼ��� : 

	����   : �κ��丮�� �ش缿 �������� �����.
	�Է�   : INT nInventoryNum
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteInvenItem(INT nInventoryNum)
{
	ZeroMemory(&m_stInventoryItem[nInventoryNum], sizeof(ITEMSET));
}



VOID CInventoryWnd::DeleteInvenItem(INT nMakeIndex, CHAR* szName)
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			if ( m_stInventoryItem[nCnt].xItem.m_stItemInfo.nMakeIndex == nMakeIndex )
			{
				if ( !strcmp(m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, szName) )
				{
					DeleteInvenItem(nCnt);
					break;
				}
			}
		}		
	}
}


/******************************************************************************************************************

	�Լ��� : CInventoryWnd::DeleteInventoryAllItem()

	�ۼ��� : 
	�ۼ��� : 

	����   : �κ��丮�� ��� �������� �����.
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteAllInvenItem()
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		ZeroMemory(&m_stInventoryItem[nCnt], sizeof(ITEMSET));
	}
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::DeleteCurrBeltItemList()

	�ۼ��� : 
	�ۼ��� : 

	����   : ��Ʈ�� �ش缿 �������� �����.
	�Է�   : INT nBeltInventoryNum
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteBeltItem(INT nBeltInventoryNum)
{
	ZeroMemory(&m_stBeltItem[nBeltInventoryNum], sizeof(ITEMSET));
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::DeleteAllBeltItemList()

	�ۼ��� : 
	�ۼ��� : 

	����   : ��Ʈ�� ��� �������� �����.
	�Է�   : INT nBeltInventoryNum
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteAllBeltItem()
{
	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		ZeroMemory(&m_stBeltItem[nCnt], sizeof(ITEMSET));
	}
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::AddInvenItem()

	�ۼ��� : 
	�ۼ��� : 

	����   : �κ��丮�� �������� �ִ´�.
	�Է�   : CItem xItem
	         INT nInvenNum
	         BOOL bUseInvenNum
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::AddInvenItem(CItem xItem, INT nInvenNum, BOOL bUseInvenNum)
{
	if ( bUseInvenNum )
	{
		if ( !m_stInventoryItem[nInvenNum].bSetted )
		{
			m_stInventoryItem[nInvenNum].bSetted = TRUE;
			m_stInventoryItem[nInvenNum].xItem = xItem;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( !m_stInventoryItem[nCnt].bSetted )
		{
			m_stInventoryItem[nCnt].bSetted = TRUE;
			m_stInventoryItem[nCnt].xItem = xItem;

			return TRUE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::AddBeltItem()

	�ۼ��� : 
	�ۼ��� : 

	����   : ��Ʈ�� �������� �ִ´�.
	�Է�   : CItem xItem
	         INT nBeltNum
	         BOOL bUseBeltNum
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::AddBeltItem(CItem xItem, INT nBeltNum, BOOL bUseBeltNum)
{
	if ( bUseBeltNum )
	{
		if ( !m_stBeltItem[nBeltNum].bSetted )
		{
			m_stBeltItem[nBeltNum].bSetted = TRUE;
			m_stBeltItem[nBeltNum].xItem = xItem;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		if ( !m_stBeltItem[nCnt].bSetted )
		{
			m_stBeltItem[nCnt].bSetted = TRUE;
			m_stBeltItem[nCnt].xItem = xItem;

			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::ExtractInvenItem()

	�ۼ��� : 
	�ۼ��� : 

	����   : �κ��丮���� ���� ��ȣ�� �������� �̾ƿ´�.
	�Է�   : CItem* pxItem
	         INT nInventoryNum
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::ExtractInvenItem(CItem* pxItem, INT nInventoryNum)
{
	if ( m_stInventoryItem[nInventoryNum].bSetted )
	{
		memcpy(pxItem, &m_stInventoryItem[nInventoryNum].xItem, sizeof(CItem));
		DeleteInvenItem(nInventoryNum);
				
		return TRUE;
	}
	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::ExtractBeltItem()

	�ۼ��� : 
	�ۼ��� : 

	����   : ����â���� ���� ��ȣ�� �������� �̾ƿ´�.
	�Է�   : CItem* pxItem
	         INT nBeltInventoryNum
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::ExtractBeltItem(CItem* pxItem, INT nBeltInventoryNum)
{
	if ( m_stBeltItem[nBeltInventoryNum].bSetted )
	{
		memcpy(pxItem, &m_stBeltItem[nBeltInventoryNum].xItem, sizeof(CItem));
		DeleteBeltItem(nBeltInventoryNum);
				
		return TRUE;
	}
	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::ChangeInvenWithCommon()

	�ۼ��� : 
	�ۼ��� : 

	����   : �κ��丮�� �����۰� ����(���콺)�������� �ٲ۴�.
	�Է�   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ChangeInvenWithCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xInvenItem;
		if ( ExtractInvenItem(&xInvenItem, nInventoryNum) )
		{
			AddInvenItem(pstCommonItemSet->xItem, nInventoryNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xInvenItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= FALSE;
			pstCommonItemSet->xItem.m_shCellNum = nInventoryNum; 
		}
	}
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::ChangeBeltWithCommon()

	�ۼ��� : 
	�ۼ��� : 

	����   : ��Ʈ�� �����۰� ����(���콺)�������� �ٲ۴�.
	�Է�   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ChangeBeltWithCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xBeltItem;
		if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xBeltItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= TRUE;
			pstCommonItemSet->xItem.m_shCellNum = nBeltInventoryNum; 
		}
	}
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::SetCommonFromInven()

	�ۼ��� : 
	�ۼ��� : 

	����   : �κ��丮�� �ش��ȣ �������� ����(���콺)���������� �����Ѵ�.
	�Է�   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetCommonFromInven(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xInvenItem;
	if ( ExtractInvenItem(&xInvenItem, nInventoryNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xInvenItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= FALSE;
		pstCommonItemSet->xItem.m_shCellNum = nInventoryNum; 
	}
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::SetCommonFromBelt()

	�ۼ��� : 
	�ۼ��� : 

	����   : ��Ʈâ�� �ش��ȣ �������� ����(���콺)���������� �����Ѵ�.
	�Է�   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetCommonFromBelt(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xBeltItem;
	if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xBeltItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= TRUE;
		pstCommonItemSet->xItem.m_shCellNum = nBeltInventoryNum; 
	}
}	



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::SetInvenFromCommon()

	�ۼ��� : 
	�ۼ��� : 

	����   : ����(���콺)�������� �κ��丮�� �ش��ȣ�� �����Ѵ�.
	�Է�   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetInvenFromCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		pstCommonItemSet->xItem.m_shCellNum = nInventoryNum;
		AddInvenItem(pstCommonItemSet->xItem, nInventoryNum, TRUE);

		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::SetBeltFromCommon()

	�ۼ��� : 
	�ۼ��� : 

	����   : ����(���콺)�������� ��Ʈâ�� �ش��ȣ�� �����Ѵ�.
	�Է�   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetBeltFromCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		pstCommonItemSet->xItem.m_shCellNum = nBeltInventoryNum;
		AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);

		ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
	}
}


VOID CInventoryWnd::AddNewBeltItem(LPCOMMONITEMSET pstCommonItemSet)
{
	INT nCnt;
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bIsBeltItem )
	{
		if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */ 
			 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
		{
			for ( nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
			{
				if ( m_stInventoryItem[nCnt].bSetted && 
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode == pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode &&
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.bShape == pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bShape && 
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.nDura == pstCommonItemSet->xItem.m_stItemInfo.nDura && 
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.nDuraMax == pstCommonItemSet->xItem.m_stItemInfo.nDuraMax )
					 
				{
					if ( !m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].bSetted )
					{
						m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].xItem = m_stInventoryItem[nCnt].xItem;
						m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].bSetted = TRUE;
						m_stInventoryItem[nCnt].xItem.m_stItemInfo.bDrugNum--;
						if( m_stInventoryItem[nCnt].xItem.m_stItemInfo.bDrugNum == 0 )
							DeleteInvenItem(nCnt);//����ط�Ӧ�ø�һ��
					}
					break;
				}
			}
		}			 
	}
}












/******************************************************************************************************************

	Message Function.(���콺�Է�)

*******************************************************************************************************************/
BOOL CInventoryWnd::OnKeyUp(LPCOMMONITEMSET pstCommonItemSet, WPARAM wParam, LPARAM lParam)
{
	INT nBeltInventoryNum;

	nBeltInventoryNum = -1;
	
	switch ( wParam )
	{
	case '1': 	nBeltInventoryNum = 0;		break;
	case '2': 	nBeltInventoryNum = 1;		break;
	case '3': 	nBeltInventoryNum = 2;		break;
	case '4': 	nBeltInventoryNum = 3;		break;
	case '5': 	nBeltInventoryNum = 4;		break;
	case '6': 	nBeltInventoryNum = 5;		break;
	}

	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			if ( !pstCommonItemSet->bSetted )
			{				  
				SetCommonFromBelt(nBeltInventoryNum, pstCommonItemSet);
			}
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{		
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					ChangeBeltWithCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}
		else
		{
			if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					 SetBeltFromCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}

		if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
		{			
			pstCommonItemSet->bWaitResponse = TRUE;
			pstCommonItemSet->bIsHideItem	= TRUE;
			g_xClientSocket.SendItemIndex(CM_EAT, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName);
			return TRUE;
		}
	}

	return FALSE;
}


/******************************************************************************************************************

	�Լ��� : CInventoryWnd::OnLButtonDown()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : POINT ptMouse
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nCnt, nInventoryNum, nBeltInventoryNum;

	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].ChangeRect(m_rcWnd.left+242, m_rcWnd.top+ 421);


	if ( m_xInvenScrlBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= m_xInvenScrlBar.GetScrlRate();
		m_nStartLineNum = 11*fScrlRate;

		return FALSE;
	}


	for( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		if ( m_xInventoryBtn[nCnt].OnLButtonDown(ptMouse) )		
			return TRUE;
	}

	nInventoryNum	  = GetInvenNum(ptMouse);
	nBeltInventoryNum = GetBeltNum(ptMouse);

	if ( (nInventoryNum == -1 && nBeltInventoryNum == -1) )		m_bCanMove = TRUE;
	else													
	{
		if ( nInventoryNum != -1 )
		{
			if ( m_stInventoryItem[nInventoryNum].bSetted )		m_bCanMove = FALSE;
			else												m_bCanMove = TRUE;				
		}
		else if ( nBeltInventoryNum != -1 )
		{
			if ( m_stBeltItem[nInventoryNum].bSetted )			m_bCanMove = FALSE;
			else												m_bCanMove = TRUE;				
		}
	}
	
	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::OnLButtonUp()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nInventoryNum, nBeltInventoryNum;

	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].ChangeRect(m_rcWnd.left+242, m_rcWnd.top+ 421);

	if ( m_xInvenScrlBar.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	// �κ��丮 �����츦 �ٴ´�.
	if ( m_xInventoryBtn[_BTN_ID_INVENCLOSE].OnLButtonUp(ptMouse) )
		return TRUE;

	nInventoryNum	  = GetInvenNum(ptMouse);
	nBeltInventoryNum = GetBeltNum(ptMouse);

	// ����(���콺)�����ۿ� ����â���� �� �������� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴ϶��, ������ ������ Off��Ų��.
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bWaitResponse )
	{
		nInventoryNum = GetInvenNum(ptMouse);
		if ( nInventoryNum != -1 )
		{
			g_xClientSocket.SendTakeOnOffItem(CM_TAKEOFFITEM, pstCommonItemSet->xItem.m_shCellNum, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex);
			pstCommonItemSet->bWaitResponse	= TRUE;
			return FALSE;
		}
	}

	// �κ��丮 ���������� Ŭ���Ѱ��.
	if ( nInventoryNum != -1 )
	{
		// Ŭ�����κ��丮�� �������� �������.
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			// ����(���콺)�����ۼ��� ���������,
			if ( !pstCommonItemSet->bSetted )
			{				  
				// ���콺�� �������� ���δ�.
				SetCommonFromInven(nInventoryNum, pstCommonItemSet);
			}
			// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�, ������������ �ƴҶ���.
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				ChangeInvenWithCommon(nInventoryNum, pstCommonItemSet);
			}
		}
		// Ŭ���� �κ��丮�� �������� �������.
		else
		{
			// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�,
			if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				SetInvenFromCommon(nInventoryNum, pstCommonItemSet);
			}
		}
	}

	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			if ( !pstCommonItemSet->bSetted )
			{				  
				SetCommonFromBelt(nBeltInventoryNum, pstCommonItemSet);
			}
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{		
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					ChangeBeltWithCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}
		else
		{
			if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					 SetBeltFromCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::OnLButtonDoubleClick()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	���   : BOOL 

	[����][������] : ʹ�õ���

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{	
	INT nInventoryNum	  = GetInvenNum(ptMouse);
	INT nBeltInventoryNum = GetBeltNum(ptMouse);

	if ( nInventoryNum != -1 )
	{
		// Ŭ�����κ��丮�� �������� �������.
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			// ����(���콺)�����ۼ��� ���������,
			if ( !pstCommonItemSet->bSetted )
			{				  
				// ���콺�� �������� ���δ�.
				SetCommonFromInven(nInventoryNum, pstCommonItemSet);
			}
			// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�,
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				ChangeInvenWithCommon(nInventoryNum, pstCommonItemSet);
			}
		}
	}

	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			if ( !pstCommonItemSet->bSetted )
			{				  
				SetCommonFromBelt(nBeltInventoryNum, pstCommonItemSet);
			}
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				ChangeBeltWithCommon(nBeltInventoryNum, pstCommonItemSet);
			} 
		}
	}

	//pstCommonItemSet��ǰ��ѡ��ITEM
	if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
	{			
		pstCommonItemSet->bWaitResponse = TRUE;
		g_xClientSocket.SendItemIndex(CM_EAT, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName);
	}

	return TRUE;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::OnMouseMove()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : POINT ptMouse
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::OnMouseMove(POINT ptMouse)
{
	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].ChangeRect(m_rcWnd.left+242, m_rcWnd.top+ 421);

	for( INT nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
		m_xInventoryBtn[nCnt].OnMouseMove(ptMouse);
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::OnScrollDown()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::OnScrollDown()
{
	if ( m_nStartLineNum > 0 )												m_nStartLineNum--;
}



/******************************************************************************************************************

	�Լ��� : CInventoryWnd::OnScrollUp()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::OnScrollUp()
{
//	if ( m_nStartLineNum < _INVEN_MAX_CELL_YCNT - _INVEN_CELL_YCNT )		m_nStartLineNum++;
	if ( m_nStartLineNum < (_INVEN_MAX_CELL_YCNT-1) )
	{
		m_nStartLineNum++;
	}
}
