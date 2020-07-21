#pragma once

class CTeamManage : public CWHDefProcess
{
public:
	CTeamManage(void);
	~CTeamManage(void);

public:
	LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);

	VOID	RenderScene(INT nLoopTime);

	//����ʵ�ֵ��麯��
	virtual LRESULT DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual	char*	OnMessageReceive(CHAR* pszPacketMsg);
	virtual VOID	OnConnectToServer();
private:
	DWORD	m_dwLastEventFilter;//socket�¼�

	CPDLList<CTeamProcess> m_xTeamProcList;
};
