/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/


#include "StdAfx.h"


CItem::CItem()
{
	m_shCellNum	= 0;
	m_bAttr		= 0;
	ZeroMemory(&m_stItemInfo, sizeof(CLIENTITEMRCD));
}


CItem::~CItem()
{
}


BOOL CItem::SetItem(CLIENTITEMRCD stItemInfo, SHORT shInventoryNum)
{
	m_stItemInfo = stItemInfo;
	m_shCellNum = shInventoryNum;
/*
a:����
b:��
c:���� ���� �����
g:��Ÿ
*/
/*
#define _U_DRESS					0
#define _U_WEAPON					1
#define _U_RIGHTHAND				2
#define _U_NECKLACE					3
#define _U_HELMET					4
#define _U_ARMRINGL					5
#define _U_ARMRINGR					6            
#define _U_RINGL					7 
#define _U_RINGR					8 
#define _U_CHARM					9
#define _U_UNEQUIP					100
*/

	switch ( m_stItemInfo.stStdItem.bStdMode )
	{
	// ����.
	case 5:		
	case 6:		
		m_bAttr = _U_WEAPON;
		break;
	// ��.
	case 10:
	case 11:
		m_bAttr = _U_DRESS;
		break;
	case 15:
		m_bAttr = _U_HELMET;
		break;
	case 19:
	case 20:
	case 21:
		m_bAttr = _U_NECKLACE;
		break;
	case 22:
	case 23:
		m_bAttr = _U_RINGL;
		break;
	case 24:
	case 26:
		m_bAttr = _U_ARMRINGL;
		break;
	// ����.
	case 30:
		m_bAttr = _U_RIGHTHAND;
		break;
	// ������, ����.
	case 25:
		m_bAttr = _U_ARMRINGL;
		break;
	case 53:
		m_bAttr = _U_SHOES;
		break;
	}

	return TRUE;
}


BOOL CItem::DrawItem(INT nX, INT nY, BYTE bItemType)
{
	CWHWilImageData*	pxItemImg;	
	BOOL bDrawItem = FALSE;
	INT x=nX; INT y=nY;
	switch ( bItemType )
	{
	case _ITEM_TYPE_INVENTORY:// ���
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX = nX+_INVENTORY_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			nY = nY+_INVENTORY_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;
		}
		break;
	case _ITEM_TYPE_EQUIP://װ��
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX += g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP].m_lpstNewCurrWilImageInfo->shPX;
			nY += g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP].m_lpstNewCurrWilImageInfo->shPY;
		}
		break;
	}
		
	if ( bDrawItem )
	{
 		g_xMainWnd.DrawWithImageForCompClipRgn(
						nX,
						nY,
						pxItemImg->m_lpstNewCurrWilImageInfo->shWidth,
						pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, 600);

		if( bItemType == _ITEM_TYPE_INVENTORY )//��ʾ����
		{
			if( m_stItemInfo.stStdItem.bStdMode == 0 || 
				m_stItemInfo.stStdItem.bStdMode == 3 )
			{
				CHAR szNum[16];
				sprintf( szNum, "%3d", m_stItemInfo.bDrugNum );
				g_xMainWnd.PutsHan(NULL, x+_INVENTORY_CELL_WIDTH/2, y+26, RGB(255, 0, 0), RGB(0, 0, 0), szNum, NULL);
			}
		}
	}
	return TRUE;
}


VOID CItem::ShowItemStatus(INT nX, INT nY)
{
	CHAR	szLineBuf[3][MAX_PATH];
	CHAR	szName[MAX_PATH];
	SIZE	sizeLen;
	BOOL	bUseAble = TRUE;
	const INT nLineGap = 14;

	ZeroMemory(szName, MAX_PATH);
	ZeroMemory(szLineBuf, 3*MAX_PATH);

	if ( m_stItemInfo.stStdItem.szName )
	{
		switch ( m_stItemInfo.stStdItem.bStdMode )
		{
		// ���ڿ�, ���ڿ�.
		case 10:
		case 11:
			{
				bUseAble = FALSE;

				// ù°��.
				if ( m_stItemInfo.stStdItem.szName[20] )
					g_xMainWnd.StringPlus(szName, &m_stItemInfo.stStdItem.szName[20], " ", &m_stItemInfo.stStdItem.szName[0], "");
				else
					strcpy(szName, m_stItemInfo.stStdItem.szName);
				g_xMainWnd.PutsHan(NULL, nX, nY, RGB(250, 250, 0), RGB(0, 0, 0), szName);
				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, szName);

				sprintf(szLineBuf[0], " ����%d ����%d/%d", (m_stItemInfo.stStdItem.bWeight), (m_stItemInfo.nDura/1000), (m_stItemInfo.nDuraMax)/1000);

				g_xMainWnd.PutsHan(NULL, nX+sizeLen.cx, nY, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[0]);
				

				// ��°��.
				if ( m_stItemInfo.stStdItem.wAC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "���%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC));

				if ( m_stItemInfo.stStdItem.wMAC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC));

				if ( m_stItemInfo.stStdItem.wDC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "�ı�%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC));

				if ( m_stItemInfo.stStdItem.wMC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC));

				if ( m_stItemInfo.stStdItem.wSC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wSC), HIBYTE(m_stItemInfo.stStdItem.wSC));

				g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);

				// ��°��.
				switch ( m_stItemInfo.stStdItem.bNeed )
				{
				case 0:
					{
						if ( g_xGameProc.m_pMyHero->m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ䷹��%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 1:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wDC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ��ı���%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 2:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wMC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ丶����%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 3:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wSC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ䵵��%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				}

				if ( bUseAble )
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[2]);
				else
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 0, 0), RGB(0, 0, 0), szLineBuf[2]);
			}
			break;
		// ����.
		case 5:
		case 6:
			{
				bUseAble = FALSE;

				// ù°��.
				if ( (m_stItemInfo.stStdItem.bNeedIdentify & 0X01) != 0 )			
				{
					if ( m_stItemInfo.stStdItem.szName[20] )
						g_xMainWnd.StringPlus(szName, "(*)", &m_stItemInfo.stStdItem.szName[20], " ", &m_stItemInfo.stStdItem.szName[0], "");
					else
						strcpy(szName, m_stItemInfo.stStdItem.szName);
				}
				else																
				{
					if ( m_stItemInfo.stStdItem.szName[20] )
						g_xMainWnd.StringPlus(szName, &m_stItemInfo.stStdItem.szName[20], " ", &m_stItemInfo.stStdItem.szName[0], "");
					else
						strcpy(szName, m_stItemInfo.stStdItem.szName);
				}

				g_xMainWnd.PutsHan(NULL, nX, nY, RGB(250, 250, 0), RGB(0, 0, 0), szName);
				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, szName);

				sprintf(szLineBuf[0], " ����%d ����%d/%d", (m_stItemInfo.stStdItem.bWeight), (m_stItemInfo.nDura/1000), (m_stItemInfo.nDuraMax)/1000);
				g_xMainWnd.PutsHan(NULL, nX+sizeLen.cx, nY, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[0]);

				// ��°��.
				if ( m_stItemInfo.stStdItem.wDC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "�ı�%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC));

				if ( m_stItemInfo.stStdItem.wMC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC));

				if ( m_stItemInfo.stStdItem.wSC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wSC), HIBYTE(m_stItemInfo.stStdItem.wSC));

				if ( m_stItemInfo.stStdItem.bSource/*sSpecialPower*/ > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d ", m_stItemInfo.stStdItem.bSource/*sSpecialPower*/);

				g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);

				// ��°��.
				if ( HIBYTE(m_stItemInfo.stStdItem.wAC) > 0 )
					sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "��Ȯ+%d ", HIBYTE(m_stItemInfo.stStdItem.wAC));

				if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
				{
					if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) > 10 )
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "���ݼӵ�+%d ", HIBYTE(m_stItemInfo.stStdItem.wMAC)-10);
					else
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "���ݼӵ�-%d ", HIBYTE(m_stItemInfo.stStdItem.wMAC));
				}

				if ( LOBYTE(m_stItemInfo.stStdItem.wAC) > 0 )
					sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "���+%d ", LOBYTE(m_stItemInfo.stStdItem.wAC));

				if ( LOBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
					sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "����+%d ", LOBYTE(m_stItemInfo.stStdItem.wMAC));

				switch ( m_stItemInfo.stStdItem.bNeed )
				{
				case 0:
					{
						if ( g_xGameProc.m_pMyHero->m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ䷹��%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 1:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wDC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ��ı���%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 2:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wMC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ丶����%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 3:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wSC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ䵵��%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				}

				if ( bUseAble )
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[2]);
				else
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 0, 0), RGB(0, 0, 0), szLineBuf[2]);

			}
			break;			
        case 15:	//����,����
        case 19:	//�����
		case 20:
		case 21:  
        case 22:	//����
		case 23:  
        case 24:	//����
		case 26:  
			{
				bUseAble = FALSE;

				// ù°��.
				if ( m_stItemInfo.stStdItem.szName[20] )
					g_xMainWnd.StringPlus(szName, &m_stItemInfo.stStdItem.szName[20], " ", &m_stItemInfo.stStdItem.szName[0], "");
				else
					strcpy(szName, m_stItemInfo.stStdItem.szName);
				g_xMainWnd.PutsHan(NULL, nX, nY, RGB(250, 250, 0), RGB(0, 0, 0), szName);
				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, szName);

				sprintf(szLineBuf[0], " ����%d ����%d/%d", (m_stItemInfo.stStdItem.bWeight), (m_stItemInfo.nDura/1000), (m_stItemInfo.nDuraMax)/1000);

				g_xMainWnd.PutsHan(NULL, nX+sizeLen.cx, nY, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[0]);

				// �ι�°��.
				// �����.
				if ( m_stItemInfo.stStdItem.bStdMode == 19 && m_stItemInfo.stStdItem.bStdMode == 20 )
				{
					if ( m_stItemInfo.stStdItem.wAC > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����ȸ��+%d ", HIBYTE(m_stItemInfo.stStdItem.wAC));

					if ( LOBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����+%d ", LOBYTE(m_stItemInfo.stStdItem.wMAC));

					if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "���+%d ", HIBYTE(m_stItemInfo.stStdItem.wMAC));		
				}				
				// ����.
				if ( m_stItemInfo.stStdItem.bStdMode == 22 && m_stItemInfo.stStdItem.bStdMode == 23 )
				{
					if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "�ߵ�ȸ��+%d ", HIBYTE(m_stItemInfo.stStdItem.wMAC));

					if ( LOBYTE(m_stItemInfo.stStdItem.wAC) > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "���ݼӵ�+%d ", LOBYTE(m_stItemInfo.stStdItem.wAC));
					
					if ( LOBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "���ݼӵ�-%d ", LOBYTE(m_stItemInfo.stStdItem.wMAC));
				}
				// ����.
				else if ( m_stItemInfo.stStdItem.bStdMode == 24 && m_stItemInfo.stStdItem.bStdMode == 26 )
				{
					if ( m_stItemInfo.stStdItem.wAC > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "��Ȯ+%d ", HIBYTE(m_stItemInfo.stStdItem.wAC));
			
					if ( m_stItemInfo.stStdItem.wMAC > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "��ø+%d ", HIBYTE(m_stItemInfo.stStdItem.wMAC));
				}
				else
				{

					if ( m_stItemInfo.stStdItem.wAC > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "���%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC));
					
					if ( m_stItemInfo.stStdItem.wMAC > 0 )
						sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC));
				}

				if ( m_stItemInfo.stStdItem.wDC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "�ı�%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC));

				if ( m_stItemInfo.stStdItem.wMC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC));

				if ( m_stItemInfo.stStdItem.wSC > 0 )
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], "����%d-%d ", LOBYTE(m_stItemInfo.stStdItem.wSC), HIBYTE(m_stItemInfo.stStdItem.wSC));

				g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);

				// ����°��.
				switch ( m_stItemInfo.stStdItem.bNeed )
				{
				case 0:
					{
						if ( g_xGameProc.m_pMyHero->m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ䷹��%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 1:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wDC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ��ı���%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 2:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wMC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ丶����%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				case 3:
					{
						if ( HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wSC) >= m_stItemInfo.stStdItem.bNeedLevel )
						   bUseAble = TRUE;
						sprintf(&szLineBuf[2][strlen(szLineBuf[2])], "�ʿ䵵��%d ", m_stItemInfo.stStdItem.bNeedLevel);
					}
					break;
				}

				if ( bUseAble )
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[2]);
				else
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 0, 0), RGB(0, 0, 0), szLineBuf[2]);
			}
			break;

/*		case 25:	//�Ѹ��� ������
		case 30:	//��,Ƚ��
		case 40:	//��ⵢ�
		case 42:
		case 43:
*/		default:
			{
				bUseAble = FALSE;

				// ù��°��.
				g_xMainWnd.PutsHan(NULL, nX, nY, RGB(250, 250, 0), RGB(0, 0, 0), m_stItemInfo.stStdItem.szName);
				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_stItemInfo.stStdItem.szName);

				switch ( m_stItemInfo.stStdItem.bStdMode )
				{
				case 0:			// ����.
					if ( m_stItemInfo.stStdItem.wAC > 0 )
						sprintf(&szLineBuf[0][strlen(szLineBuf[0])], " +%dHP ", m_stItemInfo.stStdItem.wAC);

					if ( m_stItemInfo.stStdItem.wMAC > 0 )
						sprintf(&szLineBuf[0][strlen(szLineBuf[0])], " +%dMP ", m_stItemInfo.stStdItem.wMAC);

					sprintf(&szLineBuf[0][strlen(szLineBuf[0])], " ����%d ", m_stItemInfo.stStdItem.bWeight);

					g_xMainWnd.PutsHan(NULL, nX+sizeLen.cx, nY, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[0]);

					break;
				case 1:			// �������.
				case 2:			// �ָԹ�.
					break;
				case 3:			// Ư���ѹ��� OR ����������.
					sprintf(&szLineBuf[0][strlen(szLineBuf[0])], " ����%d ", m_stItemInfo.stStdItem.bWeight);
					g_xMainWnd.PutsHan(NULL, nX+sizeLen.cx, nY, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[0]);
					break;
				case 4:			// ����å��.
					sprintf(&szLineBuf[0][strlen(szLineBuf[0])], " ����%d ", m_stItemInfo.stStdItem.bWeight);
					g_xMainWnd.PutsHan(NULL, nX+sizeLen.cx, nY, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[0]);

					switch ( m_stItemInfo.stStdItem.bShape )
					{
					case 0:
						{
							// ��°��.
							sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ���繫����� ");
							g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);

							sprintf(&szLineBuf[2][strlen(szLineBuf[2])], " �ʿ䷹��%d ", m_stItemInfo.stStdItem.wDuraMax);

							if ( (g_xGameProc.m_pMyHero->m_bJob == _JOB_JUNSA) && (g_xGameProc.m_pMyHero->m_stAbility.bLevel >= m_stItemInfo.stStdItem.wDuraMax) )
							   bUseAble = TRUE;
							if ( bUseAble )
								g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[2]);
							else
								g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 0, 0), RGB(0, 0, 0), szLineBuf[2]);
						}
						break;
					case 1:
						{
							// ��°��.
							sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " �ּ��縶��å ");
							g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);

							sprintf(&szLineBuf[2][strlen(szLineBuf[2])], " �ʿ䷹��%d ", m_stItemInfo.stStdItem.wDuraMax);

							if ( (g_xGameProc.m_pMyHero->m_bJob == _JOB_SULSA) && (g_xGameProc.m_pMyHero->m_stAbility.bLevel >= m_stItemInfo.stStdItem.wDuraMax) )
							   bUseAble = TRUE;

							if ( bUseAble )
								g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[2]);
							else
								g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 0, 0), RGB(0, 0, 0), szLineBuf[2]);
						}
						break;
					case 2:
						{
							sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ���繫����� ");
							g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);

							sprintf(&szLineBuf[2][strlen(szLineBuf[2])], " �ʿ䷹��%d ", m_stItemInfo.stStdItem.wDuraMax);

							if ( (g_xGameProc.m_pMyHero->m_bJob == _JOB_DOSA) && (g_xGameProc.m_pMyHero->m_stAbility.bLevel >= m_stItemInfo.stStdItem.wDuraMax) )
							   bUseAble = TRUE;

							if ( bUseAble )
								g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[2]);
							else
								g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 0, 0), RGB(0, 0, 0), szLineBuf[2]);
						}
						break;
					}
					break;						
				case 25:			// ���� ������.
					// ù��°��.
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ����%d ", m_stItemInfo.stStdItem.bWeight);
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);

					// �ι�°��.
					sprintf(&szLineBuf[2][strlen(szLineBuf[2])], " ���%d/%d ", m_stItemInfo.nDura, m_stItemInfo.nDuraMax);
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap*2, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[2]);
					break;
				case 30:			// ȶ�Ұ� ��.
					// �ι�°��.
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ����%d ����%d/%d ", m_stItemInfo.stStdItem.bWeight, m_stItemInfo.nDura/1000, m_stItemInfo.nDuraMax/1000);
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);
					break;
				case 31:			// ���������ø���.
					// ù��°��.
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ����%d ", m_stItemInfo.stStdItem.bWeight);
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);
					break;
				case 40:		// ��������(��ⵢ�)
					// �ι�°��.
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ����%d ǰ��%d/%d ", m_stItemInfo.stStdItem.bWeight, m_stItemInfo.nDura/1000, m_stItemInfo.nDuraMax/1000);
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);
					break;
				case 42:			// ���������.
					// �ι�°��.
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ����%d ���� ", m_stItemInfo.stStdItem.bWeight);
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);
					break;
				case 43:		// ����������.
					// �ι�°��.
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ����%d �־�%d ", m_stItemInfo.stStdItem.bWeight, m_stItemInfo.nDura/1000);//����-����,����-�־�
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);
					break;
				case 44:		// �������� ���� Ư�� ������.
					break;
				case 45:		// ���� �������� �ٲ�� ��ɼ� ������.
					break;
				case 46:		// ����� ���� �ܼ�������.
				default:
					// �ι�°��.
					sprintf(&szLineBuf[1][strlen(szLineBuf[1])], " ����%d ", m_stItemInfo.stStdItem.bWeight);
					g_xMainWnd.PutsHan(NULL, nX, nY+nLineGap, RGB(250, 250, 250), RGB(0, 0, 0), szLineBuf[1]);
					break;
				}
			}
			break;
		}				
	}
}

