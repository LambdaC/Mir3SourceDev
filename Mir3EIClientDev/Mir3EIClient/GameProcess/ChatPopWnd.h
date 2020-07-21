#ifndef _CCHATPOPWND_H
#define _CCHATPOPWND_H

typedef struct tagCHATSTRING
{
	DWORD	dwFontColor;
	DWORD	dwFontBackColor;
	string	strChat;
}CHATSTRING, *LPCHATSTRING;


class CChatPopWnd : public CGameWnd
{ 
private:
protected:
	CDLList<CHATSTRING> m_xstrDividedChat;		// �������� ä�� ����Ÿ.
	
	CGameBtn		m_xChatPopBtn;
	RECT			m_rcChatPopFrame;			// ä�ÿ���.
	INT				m_nCurrStartChatLine;		// ä��ȭ������� ���� ������ ����Ű�� ä�ø���Ʈ�� ��ȣ�ε���.
	INT				m_nCanScrlCnt;

public:
	RECT			m_rcEditBoxFrame;			

public:
	CChatPopWnd();
	~CChatPopWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	BOOL	MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* szMsg = NULL);

	VOID	CreateChatPopWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowChatPopWnd();
	VOID	SetStatusBtnInit();
public:
//  �޽��� �Լ�.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();
};


#endif // _CCHATPOPWND_H
