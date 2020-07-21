#ifndef _MSGBOX_H_
#define _MSGBOX_H_
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// CMsgBox.h
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////

#define CLICK_NONE			0
#define CLICK_OK			1
#define CLICK_YES			2
#define CLICK_NO			4
#define CLICK_CANCLE		8
#define HAVE_EDITOBOX		128

#define MSG_BTN_OK				1
#define MSG_BTN_YESNO			2
#define MSG_BTN_YESNOCANCLE		4
#define MSG_EDITEXIST			128

#define ASK_MAKE_BIG_GUILD			1		// ������ ������ �̸��� �����ʽÿ�.
#define ASK_MAKE_SMALL_GUILD		2		// ������ ������ �̸��� �����ʽÿ�.
#define ASK_OTHERSNAME				3		// ��� ���ĸ��� �Է�������.
#define ASK_DELMEMBER_NAME			4		// �������� ������ ����� �̸��� �Է��Ͻʽÿ�.
#define ASK_ADDMEMBER_NAME			5		// �������� �߰��� ����� �̸��� �Է��Ͻʽÿ�.
#define ASK_DROP_GOLD				6		// ���� ���� �ݾ��� �Է��ϼ���.
#define ASK_DEAL_GOLD				7		// �ŷ��� �ݾ��� �Է��ϼ���.
#define ASK_GROUP_ADD_MEMBER_NAME	8		// �׷쿡 ������ ����� �̸��� �����ʽÿ�.
#define ASK_GROUP_DEL_MEMBER_NAME	9		// �׷쿡�� ���� ����� �̸��� �����ʽÿ�.
#define	ASK_GUILD_BREAK_ALLY		10		// ������ �ı� �� ������ �̸��� �Է��Ͻʽÿ�.
#define	ASK_YN_LOGOUT_GAME			11		// �α׾ƿ� �Ͻðڽ��ϱ�?
#define ASK_YN_QUIT_GAME			12		// �̸�������2�� �����Ͻðڽ��ϱ�?
#define	ASK_YN_GUILD_ALLY			13		// ������ �ϱ� ���ؼ��� ���� ���İ� [���Ͱ���] ���� �̾�� �ϸ� ��� ���ֿ� ���ְ� �־�� �մϴ�.
#define	ASK_YN_GAIN_SKILL			14		// ��(��) �����ðڽ��ϱ�?
#define	ASK_YN_USE_ITEM				15		// ��(��) ����Ͻðڽ��ϱ�?
#define ASK_WITHDRAWAL				16		// ã���� �ϴ� �ݾ��� �Է��ϼ���.
#define ASK_RECEIPT					17		// �ñ�����ϴ� �ݾ��� �Է��ϼ���.


class	CMsgBox
{
	//////////////////////////////
	// Function & Procedure
	//////////////////////////////
public:
	CMsgBox();			// Constructor
	~CMsgBox();			// Destructor
	// Function
	virtual BOOL	SetMsgBox(CHAR* szMsg,INT nType);				// Init Messages
	virtual BOOL	ShowMessageBox(VOID);							// Show Message box with Initialized
	virtual BOOL	ShowMessageBox(CHAR* szMsg,INT nType=0);		// Show	Message box with Initialization
	virtual BOOL	HideMessageBox(VOID);							// Hide Message box
	virtual BOOL	DestoryMessageBox(VOID);						// DestoryMessage box

	// Information
	BOOL	IsActive(VOID);
	BOOL	IsInited(VOID);

	// Message Process
	virtual HRESULT	OnButtonDown(LPARAM lParam, WPARAM wParam);		// Button Down
	virtual HRESULT	OnButtonUp(LPARAM lParam,WPARAM wParam);		// Button Up

	// Render Process
	virtual BOOL	RenderMessageBox(INT nLoopTIme);				// Render Function
private:
protected:
	__inline BOOL	IsInRect(int nPosX, int nPosY, RECT rc)	// ��Ȯ�ϰ� Rect ���� �ִ°��� üũ
	{	if (nPosX >= rc.left && nPosX <= rc.right && nPosY >= rc.top && nPosY <= rc.bottom)
			return TRUE;
		else 
			return FALSE;
	}
public:
	CHAR	m_szMsg[MAX_PATH];			// ����� ����
private:
protected:
	INT		m_nType;			// 0: OK(Ȯ��) ,1 : YES/NO ,2 : YES/NO/Cancle ,3 : EditBox & OK(Ȯ��) ...
	BOOL	m_bActive;			// Show or Hide ??
	BOOL	m_bInited;			// Initialized ?
	BOOL	m_bSet;				// Set ?
};

#endif  _MSGBOX_H_