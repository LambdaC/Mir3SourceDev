#pragma once
class CTeamProcess;

class CTeamHero : public CMyHero
{
public:
	CTeamHero(void);
	~CTeamHero(void);

public:
	//��������,����MyHero������,ħ������ AutoTargeting(), OnLButtonDown()...����
	virtual VOID  SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID = NULL, BOOL bIsDead = FALSE, LPPOINT lpptPos = NULL, SHORT shSkill = -1);

	//����״̬�ı�
	virtual BOOL UpdatePacketState();

	//�����˶�״̬,���ƶ�������Ч,
	/*virtual*/ VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	/*virtual*/ BOOL UpdateMove(BOOL bIsMoveTime);
	//�˻ص�ǰһ��״̬, ���յ�"+FAIL"����ʧ�����������������
	/*virtual*/ BOOL  SetOldPosition();

	//  �����Ϣ.
	/*virtual*/ BOOL OnLButtonDown(POINT ptMouse, INT nTargetID = -1, BOOL bIsDead = FALSE, POINT* lpptTargetPos = NULL);
//	virtual BOOL OnRButtonDown(POINT ptMouse);
//	virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);


};
