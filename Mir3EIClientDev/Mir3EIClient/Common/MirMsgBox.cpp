#include "stdafx.h"

#define WRITESTRLENTH	50


CMirMsgBox::CMirMsgBox():CMsgBox()	// Constructor
{
	m_xBoxPos.x = 0;
	m_xBoxPos.y = 0;
	m_nImgIndex = 0;
}

BOOL CMirMsgBox::Load(CWHWilImageData* pxBtnImage=NULL)
{
	if(pxBtnImage!=NULL)
	{
		// Init Button;
		m_xMsgBtn[0].CreateGameBtn(pxBtnImage,1244,1245,0,0);	// OK
		m_xMsgBtn[1].CreateGameBtn(pxBtnImage,1242,1243,0,0);	// YES
		m_xMsgBtn[2].CreateGameBtn(pxBtnImage,1246,1247,0,0);	// NO
		m_xMsgBtn[3].CreateGameBtn(pxBtnImage,1426,1247,0,0);	// Cancle
		m_pxBtnImage = pxBtnImage;
		m_bSet = TRUE;
	}
	else
	{
		m_bSet = FALSE;
	}
	return m_bSet;
}

CMirMsgBox::~CMirMsgBox()	// Destructor
{
}

// Function
/*
#define MSG_BTN_OK				1
#define MSG_BTN_YESNO			2
#define MSG_BTN_YESNOCANCLE		4
#define MSG_EDITEXIST			128
*/

BOOL CMirMsgBox::ShowMessageBox(CHAR* szMsg,INT nType) // Show	Message box with Initialization
{
	return ShowMessageBox(szMsg,nType,1240);
}

BOOL CMirMsgBox::ShowMessageBox(CHAR* szMsg,INT nType,INT nImgIndex) // Show	Message box with Initialization
{
	INT Lenth;
	if(!m_bActive)
	{
		if(SetBoxImage(nImgIndex,nType))
		{
			if(CMsgBox::ShowMessageBox(szMsg,nType))
			{
				// m_xMsg���� String 
				m_xMsg.ClearAllNodes();
				StringDivideLen(WRITESTRLENTH,Lenth, m_szMsg,&m_xMsg);

				// Text Setting

				// Button Setting
				switch(m_nType)
				{
				case MSG_BTN_YESNO:
				case MSG_BTN_YESNO|MSG_EDITEXIST:
					{
						m_nStart=1;
						m_nEnd = 3;

						m_xMsgBtn[1].ChangeRect(m_xBoxPos.x+78,m_xBoxPos.y+189);
						m_xMsgBtn[2].ChangeRect(m_xBoxPos.x+210,m_xBoxPos.y+189);

						break;
					}
				case MSG_BTN_YESNOCANCLE:
				case MSG_BTN_YESNOCANCLE|MSG_EDITEXIST:
					{
						m_nStart=1;
						m_nEnd = 4;

						m_xMsgBtn[1].ChangeRect(m_xBoxPos.x+54,m_xBoxPos.y+194);
						m_xMsgBtn[2].ChangeRect(m_xBoxPos.x+144,m_xBoxPos.y+194);
						m_xMsgBtn[3].ChangeRect(m_xBoxPos.x+234,m_xBoxPos.y+194);
						break;
					}
				case MSG_BTN_OK:
					{
						m_nStart=0;
						m_nEnd = 1;

						m_xMsgBtn[0].ChangeRect(m_xBoxPos.x+144,m_xBoxPos.y+134);
						break;
					}
				case MSG_BTN_OK|MSG_EDITEXIST:
				default:
					{
						m_nStart=0;
						m_nEnd = 1;

						m_xMsgBtn[0].ChangeRect(m_xBoxPos.x+260,m_xBoxPos.y+134);
						break;
					}
				}
			}
			else
			{
				m_bActive = FALSE;
			}
		}
		else
		{
			m_bActive = FALSE;
			m_bInited = FALSE;
		}
	}
	return m_bActive;
}

BOOL CMirMsgBox::SetBoxImage(INT nImageIndex,INT nType)
{
	POINT xSize,xPos;
	if(m_bSet)
	{
		if((nType&MSG_EDITEXIST)==MSG_EDITEXIST)
		{
			m_pxBtnImage->NewSetIndex(nImageIndex+1);
		}
		else
		{
			m_pxBtnImage->NewSetIndex(nImageIndex);
		}
		m_wpData = (WORD*)m_pxBtnImage->m_pbCurrImage;
		m_shWidth = m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth;
		m_shHeight = m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight;
		xSize.x = g_xMainWnd.m_rcWindow.right - g_xMainWnd.m_rcWindow.left;
		xSize.y = g_xMainWnd.m_rcWindow.bottom - g_xMainWnd.m_rcWindow.top;
		xPos.x = (xSize.x - m_shWidth)/2;
		xPos.y = (xSize.y - m_shHeight*2)/2;
		m_xBoxPos = xPos;
	}
	return m_bSet;
}

BOOL CMirMsgBox::HideMessageBox(VOID)							// Hide Message box
{
	m_bActive = FALSE;
	return FALSE;
}

BOOL CMirMsgBox::DestoryMessageBox(VOID)						// DestoryMessage box
{
	m_bActive = FALSE;
	m_bInited = FALSE;
	m_bSet = FALSE;
	m_xMsg.ClearAllNodes();
	return FALSE;
}

// Message Process
HRESULT CMirMsgBox::OnButtonDown(POINT tpMouse)		// Button Down
{
	HRESULT hResult=0;
	for(int i = m_nStart; i< m_nEnd; i++)
	{
		m_xMsgBtn[i].OnLButtonDown(tpMouse);
	}
	return hResult;
}

HRESULT	CMirMsgBox::OnButtonUp(POINT tpMouse)			// Button Up
{
	HRESULT hResult=0;
	for(int i = m_nStart; i< m_nEnd; i++)
	{
		if(m_xMsgBtn[i].OnLButtonUp(tpMouse))
		{
			hResult =(HRESULT)pow((double)2,i);
		}
	}
	if(hResult!=0)
	{
		hResult = hResult | ((m_nType&MSG_EDITEXIST)==MSG_EDITEXIST ? HAVE_EDITOBOX:0);
	}
	return hResult;
}

BOOL CMirMsgBox::StringDivideLen(INT nDivideLen, INT& nDividedLine, CHAR* szSrc,CDLList<CHAR*>* m_pxpStr)
{
	CHAR szTmpCheck[MAX_PATH];
	CHAR szResult[MAX_PATH];
	
	nDividedLine = 1;

	INT nStartLen	= 0;
	INT nEndLen		= 0;
	INT nResultLen	= 0;
	INT nWordCheck	= 0;

	if ( szSrc[0] != NULL )
	{
		ZeroMemory(szResult,MAX_PATH);

		for ( INT nCnt = 0; nCnt < (INT)strlen(szSrc); nCnt++)
		{
			ZeroMemory(szTmpCheck, MAX_PATH);
			nEndLen = nCnt+1;

			// ����κб����� ���ڿ��� �д´�.
			memcpy(&szTmpCheck, &szSrc[nStartLen], nEndLen-nStartLen);
			INT nsLen;
			nsLen = strlen(szTmpCheck);

			// ������� �о�� �κ��� �����̸� �Ѿ����.
			if (nsLen > nDivideLen )
			{
				// ���� 2����Ʈ ���ڶ��. 
				if ( szSrc[nEndLen-1] < 0 )
				{
					// ���� �տ����ڰ� 2����Ʈ ���ڰ� �ƴ϶��
					if ( !(nWordCheck%2) )
					{
						nStartLen += strlen(szTmpCheck)-1;
						nCnt--;
						CHAR* pszNewLine;
						pszNewLine = new CHAR[nResultLen+1];
						memcpy(pszNewLine,szResult,nResultLen);
						pszNewLine[nResultLen]=NULL;
						m_pxpStr->AddNode(pszNewLine);
						nResultLen = 0;
						nDividedLine++;
					}
					else
					{
						nStartLen += strlen(szTmpCheck)-2;
						nCnt -= 2;
						CHAR* pszNewLine;
						pszNewLine = new CHAR[nResultLen];
						memcpy(pszNewLine,szResult,nResultLen-1);
						pszNewLine[nResultLen-1]=NULL;
						m_pxpStr->AddNode(pszNewLine);
						nResultLen = 0;
						nDividedLine++;
						nWordCheck--;
					}
				}
				// 1����Ʈ ����. 
				// ���纸�� �ѹ���Ʈ�պκб����� ������ָ� �ȴ�.
				else
				{
					nStartLen += strlen(szTmpCheck)-1;
					nCnt--;
					CHAR* pszNewLine;
					pszNewLine = new CHAR[nResultLen+1];
					memcpy(pszNewLine,szResult,nResultLen);
					pszNewLine[nResultLen]=NULL;
					m_pxpStr->AddNode(pszNewLine);
					nResultLen=0;
					nDividedLine++;
				}
			}
			else if(szSrc[nEndLen-1]=='\n')	// ��������     \n�����ϸ�  Error ????
			{
				nStartLen += strlen(szTmpCheck)-1;
				CHAR* pszNewLine;
				pszNewLine = new CHAR[nResultLen+1];
				memcpy(pszNewLine,szResult,nResultLen);
				pszNewLine[nResultLen]=NULL;
				m_pxpStr->AddNode(pszNewLine);
				nResultLen=0;
				nDividedLine++;
			}
			else
			{
				if ( szSrc[nEndLen-1] < 0 )
					nWordCheck++;

				szResult[nResultLen] = szSrc[nEndLen-1];
				nResultLen++;
			}
		}
		if(nResultLen!=0)
		{
			CHAR* pszNewLine;
			pszNewLine = new CHAR[nResultLen+1];
			memcpy(pszNewLine,szResult,nResultLen);
			pszNewLine[nResultLen]=NULL;
			m_pxpStr->AddNode(pszNewLine);
			nDividedLine++;
			nResultLen=0;
		}
		return TRUE;
	}
	return FALSE;
}

// Render Process
BOOL CMirMsgBox::RenderMessageBox(INT nLoopTIme)							// Render Function
{
	INT	nCount;
//	POINT	xPos;
//	POINT	xSize;

	if(m_bActive&&m_bInited&&m_bSet)
	{	// ��¥ ���� �Ҷ��� ������
		// ���� �̹��� ���� Ȯ��
		g_xMainWnd.DrawWithImageForCompClipRgn(m_xBoxPos.x,m_xBoxPos.y,m_shWidth,m_shHeight,m_wpData,800,600);

		POINT	xTxtPos;
		nCount = m_xMsg.GetCounter();
		m_xMsg.MoveCurrentToTop();

		xTxtPos.x = m_xBoxPos.x +24;//�ı�����ʼ��ַ�� x
		switch(nCount)
		{
		case 1:	// ���� ���� 1�� ���϶�
			{
				xTxtPos.y = 106;//�ı�����ʼ��ַ�� y
				INT n = strlen(m_szMsg);
				if(n<WRITESTRLENTH)
				{
					xTxtPos.x= xTxtPos.x + (WRITESTRLENTH-n)*2;
				}
				break;
			}
		case 2:	// ���� ���� 2�� �϶�
			{
				xTxtPos.y = 61;
				break;
			}
		case 3:	// ���� ���� 2�� �϶�
			{
				xTxtPos.y = 54;
				break;
			}
		case 4:	// ���� ���� 2�� �϶�
			{
				xTxtPos.y = 47;
				break;
			}
		case 5:	// ���� ���� 2�� �϶�
			{
				xTxtPos.y = 40;
				break;
			}
		case 6:	// ���� ���� 2�� �϶�
			{
				xTxtPos.y = 33;
				break;
			}
		default: // ���� ���� 3�� �̻��� ���
			{
				xTxtPos.y = 26;
				break;
			}
		}
		int i;
		for(i = 0 ; i < nCount ; i++)
		{
			g_xMainWnd.PutsHan(NULL,xTxtPos.x,m_xBoxPos.y+xTxtPos.y,RGB(255,255,255),RGB(0,0,0),*m_xMsg.GetCurrentData());
			xTxtPos.y = xTxtPos.y + 16;
			m_xMsg.MoveNextNode();
		}
		// Draw Button

		for(i = m_nStart; i< m_nEnd; i++)
		{
			m_xMsgBtn[i].ShowGameBtn();
		}
		return FALSE;
	}
	return TRUE;
}
/*
#define MSG_BTN_OK				1
#define MSG_BTN_YESNO			2
#define MSG_BTN_YESNOCANCLE		4
#define MSG_EDITEXIST			128
*/