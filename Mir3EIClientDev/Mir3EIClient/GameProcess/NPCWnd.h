#ifndef _CNPCWnd_H
#define _CNPCWnd_H

/*using namespace std;

*/
class CNPCWnd : public CGameWnd
{ 
public:
	INT						m_nNpcId;

protected:
	CWHWilImageData			m_xNPCImage;
	int						m_nStartLine;
	int						m_nMaxLine;

	CGameBtn				m_xBtnClose;
public:
	CNPCWnd();
	~CNPCWnd();
	VOID	CreateNPCChatWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowNPCChatWnd();

	__inline void	SetNPC(int nNPCID) { m_nNpcId = nNPCID; }
	void	ResetDialog();

public:
	VOID SetNpcEditBoxPos(VOID);
	VOID SetWndRectReduce(VOID);
	VOID SetWndRectExtend(VOID);
//  �޽��� �Լ�.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
	BOOL	OnMsgInputted(VOID);

	VOID	OnScrollDown();
	VOID	OnScrollUp();
	VOID	OnEnterKeyDown(VOID);

private:
	// Command Click ó��
	BOOL	ClickCommandProcess(CMTxtBtn* ClickedBtn);		// �Ʒ� �� �ִ� �͵� ����
	BOOL	SendCommandToSrv(CHAR* szMsg);
	VOID	ShowNPCWnd();

	INT		m_nNpcMsgState;
	CMTxtBtn* m_pClickedTxtBtn;
	CMirMsgBox	m_xMsgBox;
/*	ClickPepairCommand(VOID);		// ��ġ��(@REPAIR)
	ClickSellCommand(VOID);			// �ȴ�(@SELL)
	ClickBuyCommand(VOID);			// ���(@BUY)
	ClickBuildGuildCommand(VOID);	// ���ļ���(@@BUILDGUILDNOW)
	ClickSpecialRepairCommand(VOID);// Ư������(@SPECIALREPAIR)
	ClickMakeCommand(VOID);			// �����(@MAKE)
*/
};

#endif // _CNPCWnd_H