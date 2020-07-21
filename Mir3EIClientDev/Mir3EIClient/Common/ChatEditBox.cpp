/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


static CChatEdit*	g_xChatEdit = NULL;


/******************************************************************************************************************

	CChatEdit Functions

*******************************************************************************************************************/


/******************************************************************************************************************

	�Լ��� : CChatEdit::CChatEdit()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CChatEdit::CChatEdit()
{
	m_hChatEdit = NULL;
	g_xChatEdit	= this;
	m_hFontChatEdit = NULL;
	m_dwFontColor = RGB(255, 0, 255);
	ZeroMemory(m_szInputMsg, MAX_PATH);
}



/******************************************************************************************************************

	�Լ��� : CChatEdit::~CChatEdit()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CChatEdit::~CChatEdit()
{
	DestroyDialog();
}



/******************************************************************************************************************

	�Լ��� : CChatEdit::DestroyDialog()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CChatEdit::DestroyDialog()
{
	if ( m_hFontChatEdit != NULL )
	{
		DeleteObject(m_hFontChatEdit);
		m_hFontChatEdit = NULL; 
	}

	DestroyWindow(m_hChatEdit);
	return TRUE;
}



/******************************************************************************************************************

	�Լ��� : ChatEditDlgProc()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : HWND hWnd
	         UINT uMsg
	         WPARAM wParam
	         LPARAM lParam
	���   : INT_PTR CALLBACK 

	[����][������] : ��������

*******************************************************************************************************************/
INT_PTR CALLBACK ChatEditDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return g_xChatEdit->ChatEditProc(hWnd, uMsg, wParam, lParam);
}



/******************************************************************************************************************

	�Լ��� : CChatEdit::ChatEditProc()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : HWND hWnd
	         UINT nMsg
	         WPARAM wParam
	         LPARAM lParam
	���   : LRESULT CALLBACK 

	[����][������] : ��������

*******************************************************************************************************************/
LRESULT CALLBACK CChatEdit::ChatEditProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (nMsg)
	{
		case WM_KEYDOWN:
		{
			switch ( (INT)wParam )
			{
			case VK_F1:
			case VK_F2:
			case VK_F3:
			case VK_F4:
			case VK_F5:
			case VK_F6:
			case VK_F7:
			case VK_F8:
			case VK_ESCAPE:
				{
					HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
					SetFocus(m_hMainWindow);
					SendMessage(m_hMainWindow, WM_KEYDOWN, (INT)wParam, lParam);
					return 0L;
				}
			}
			break;
		}
		case WM_CHAR:
		{
			switch ( (INT)wParam )
			{
			case VK_RETURN:
				{
					GetWindowText(hWnd, m_szInputMsg, MAX_PATH);
					SetWindowText(hWnd, "");
					HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
					SetFocus(m_hMainWindow);
					ShowWindow(m_hChatEdit, SW_HIDE);

					if ( m_szInputMsg )
					{
						if ( m_szInputMsg[0] == '@' )
							SendMessage(m_hMainWindow, _WM_USER_MSG_INPUTTED, TRUE, NULL);
						else
						{
							SendMessage(m_hMainWindow, _WM_USER_MSG_INPUTTED, NULL, NULL);
						}
					}

					return 0L;
				}
			case VK_TAB:
				{
					HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
					SetFocus(m_hMainWindow);
					SendMessage(m_hMainWindow, WM_KEYDOWN, (INT)wParam, lParam);
					return 0L;
				}
			}
			break;
		}
		case WM_PAINT:
		{

			BeginPaint(m_hChatEdit, &ps);
			InvalidateRect(hWnd, NULL, FALSE);
			EndPaint(m_hChatEdit, &ps);
			break;
		}
		default:
			break;

	}
	return CallWindowProc(m_WndProcChatEdit, hWnd, nMsg, wParam, lParam);
}



/******************************************************************************************************************

	�Լ��� : CChatEdit::Create()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : HINSTANCE hInstance
	         HWND hWndParent
	         INT nX
	         INT nY
	         INT nXsize
	         INT nYSize
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CChatEdit::Create(HINSTANCE hInstance, HWND hWndParent, INT nX, INT nY, INT nXsize, INT nYSize)
{
	m_hChatEdit = CreateWindowEx(0/*WS_EX_STATICEDGE*/, _T("EDIT"), "", WS_POPUP | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
								 nX, nY, nXsize, nYSize,
								 hWndParent, NULL, hInstance, NULL);	  
	m_WndProcChatEdit = (WNDPROC)SetWindowLong(m_hChatEdit, GWL_WNDPROC, (LONG)ChatEditDlgProc);

	// �̹� ��Ʈ�� �����Ǿ� ������ ���� ����� �ֵ��� Clear
	if ( m_hFontChatEdit != NULL )
	{
		DeleteObject(m_hFontChatEdit); 
		m_hFontChatEdit = NULL; 
	}

	m_hFontChatEdit = CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 
								 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
								 DEFAULT_QUALITY, DEFAULT_PITCH, "����");

	SendMessage(m_hChatEdit, WM_SETFONT, (WPARAM)m_hFontChatEdit, MAKELPARAM(TRUE, 0));
	// �Է¿���Ʈ�������� �ִ��Է¹��� ���� ����.
	SendMessage(m_hChatEdit, EM_LIMITTEXT, (WPARAM)95, 0);
	ShowWindow(m_hChatEdit, SW_HIDE);
    UpdateWindow(m_hChatEdit);
	return TRUE;
}



BOOL CChatEdit::SetLimitText(INT nLimitText)
{
	if ( m_hChatEdit )
	{
		SendMessage(m_hChatEdit, EM_LIMITTEXT, (WPARAM)nLimitText, 0);
		return TRUE;
	}
	return FALSE;
}