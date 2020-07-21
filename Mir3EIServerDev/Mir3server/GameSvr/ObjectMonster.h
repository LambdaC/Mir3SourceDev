
#define _MONSTER_SANDMOB		3		// ������
#define _MONSTER_ROCKMAN		4		// �籫
#define _MONSTER_RON			9		// ��
#define _MONSTER_MINORNUMA		18		// ����
#define _ANIMAL_DEER			21		// �罿
#define _MONSTER_OMA			23		// ����
#define _MONSTER_OMAKNIGHT		25		// ��������
#define _MONSTER_OMAWARRIOR		27		// �������
#define _MONSTER_SPITSPIDER		30		// ħ�Ź�
#define _MONSTER_STICK			39		// ������
#define _MONSTER_DUALAXE		42		// �ֵ����ذ�
#define _MONSTER_THONEDARK		74		// ��ũ
#define _MONSTER_LIGHTZOMBI		78		// ����Ʈ�� ����
#define _MONSTER_WHITESKELETON	94		// ���
#define _MONSTER_BEEQUEEN		124		// �񸷿���
#define _MONSTER_BEE			125		// ����
#define _MONSTER_MAGUNGSA		143		// ���û�
#define _MONSTER_SCULTURE1		145		// �ָ�����
#define _MONSTER_SCULTURE2		148		// �ָ�����
#define _MONSTER_SCULTUREKING	152		// �ָ���
#define _MONSTER_ELFMONSTER		161		// �ż�
#define _MONSTER_ELFWARRIOR		162		// �ż� ������

#define LA_UNDEAD				1

class CHolySeizeInfo
{
public:
	CEvent*					Event[8];
	CWHList<CCharObject*>	SeizeList;
	DWORD					dwOpenTime;
	DWORD					dwSeizeTime;
};

class CMonsterObject : public CNPCObject
{
public:
	int								m_nRace;

	DWORD							m_dwNextWalkTime;

	DWORD							m_dwHitTime;
	DWORD							m_dwNextHitTime;
	DWORD							m_dwThinkTime;
	DWORD							m_dwSearchEnemyTime;
	
	int								m_nTargetX;
	int								m_nTargetY;
	BYTE							m_btTargetDir;

	DWORD							m_dwRunAwayTime;
	DWORD							m_dwRunAwayStart;

	DWORD							m_dwExpHitTime;
	DWORD							m_dwLastHitTime;

	DWORD							m_nFindPathTime;

	BOOL							m_fDupMode;
	BOOL							m_fRunAwayMode;
	BOOL							m_fNoAttackMode;
	BOOL							m_fHasMission;

	int								m_nMissionX;
	int								m_nMissionY;

	int								m_nFightExp;

	WORD							m_wEscape;

	BYTE							m_btLifeAttrib;

	BOOL							m_fBoHolySeize;
	DWORD							m_dwHolySeizeStart;
	DWORD							m_dwHolySeizeTime;

	DWORD							m_dwGold;
	CWHList<_LPTGENERALITEMRCD>		m_xTGenItemRcd;
	CWHList<_LPTUSERITEMRCD>		m_xTItemRcd;
			
public:
	CMonsterObject();

	BOOL	Think();
	BOOL	Attack();
	BOOL	IsFrontObject(CCharObject* pCharObject);
	void	Struck(CCharObject* pHitter);
	void	SetLastHiter(CCharObject* pHitter);
	void	GotoTargetXY();

	BOOL	TargetInAttackRange();
	BOOL	TargetInSpitRange(int& nTargetDir);
	
	void	Wondering();
	void	MonsterNormalAttack();

	CMonsterObject*	MakeClone(int nMonRace);

	void	MakeHolySeize(DWORD dwHTime);
	void	BreakHolySeize();

	void	ComeOut();
	void	ComeDown();
	BOOL	CheckComeOut(int nValue);

	void	Initialize();

	void	InheritedRun();

	void	KickException();
	void	Die();

	void	ScatterBagItems();

	void	MakeGenItem(_LPTGENERALITEMRCD lptGenItemRcd);
	void	MonGetRandomItems();

	virtual BOOL	IsProperTarget(CCharObject* pCharObject);

	virtual void	Operate();
	virtual BOOL	AttackTarget();
	virtual BOOL	WalkTo(int nDir);
	virtual void	SearchViewRange();
	virtual void	Run();
	virtual WORD	GetThisCharColor();
	virtual void	GetCharName(char *pszCharName);
};

class CGenneralMonObject : public CMonsterObject
{
public:
	virtual void	Run();
};

class CAnimalObject : public CMonsterObject
{
public:
	BOOL			m_fSkeleton;

	int				m_nMeatQuality;
	int				m_nBodyLeathery;
};

// ��
class CChickenObject : public CAnimalObject
{
public:
	CChickenObject();

	virtual void	Run();
};

// �ָ�����, �ָ�ȣ��
class CScultureObject : public CMonsterObject
{
public:
	CScultureObject();

	void			MeltStone();
	void			MeltStoneAll();

	virtual void	Run();
};

// �ָ���
class CScultureKingObject : public CMonsterObject
{
protected:
	CWHList<CMonsterObject*>	m_SlaveObjectList;
	int							m_nDangerLevel;

public:
	CScultureKingObject();

	void			MeltStone();
	void			CallSlave();

	virtual void	Run();
};

// �񸷿���
class CBeeQueen : public CMonsterObject
{
protected:
	CWHList<CMonsterObject*>	m_SlaveObjectList;

public:
	CBeeQueen();

	void			CallSlave();
	void			MakeChildBee();

	virtual void	Operate();
	virtual void	Run();
};

// �ֵ����ذ�, ���û�
class CDualAxeObject : public CMonsterObject
{
protected:
	int m_nChainShot;
	int m_nChainShotCount;
	
public:
	CDualAxeObject(int nChainShotCount = 2);

	void			FlyAxeAttack(CCharObject* pTargetObject);

	virtual BOOL	AttackTarget();
	virtual void	Run();
};

// ����Ʈ�� ����
class CLightingZombiObject : public CMonsterObject
{	   	
public:
	CLightingZombiObject()
	{
		m_dwSearchTick	= 1500 + rand() % 1500;
	}

	void			LightingAttack(int nDir);

	virtual void	Run();
};

// ��
class CRonObject : public CGenneralMonObject
{
public:
	void			AroundAttack();

	virtual void	Run();
};

// �ϱ� ����
class CMinorNumaObject : public CMonsterObject
{
public:
	virtual void	Run();
};

// ���� �ø���
class COmaObject : public CMonsterObject
{
public:
	virtual void	Run();
};

// ������
class CStickObject : public CMonsterObject
{
public:
	CStickObject();

	virtual void	Run();
};


// �� ���� (�籫)
class CSandMobObject : public CMonsterObject
{
public:
	DWORD	m_dwAppearStart;

	CSandMobObject();

	virtual void	Run();
};

// ������
class CRockManObject : public CMonsterObject
{
public:
	CRockManObject();

	virtual void	Run();
};

// ���
class CWhiteSkeleton : public CGenneralMonObject
{
protected:
	BOOL			m_fIsFirst;

public:
	CWhiteSkeleton();

	void	ResetSkeleton();

	virtual void	Run();
};

// ħ�Ź�
class CSpitSpiderMonster : public CGenneralMonObject
{
public:
	CSpitSpiderMonster();

	void	SpitAttack(int nDir);

	virtual BOOL AttackTarget();
};

// �ż� ������
class CElfMonster : public CMonsterObject
{
protected:
	BOOL			m_fIsFirst;

public:
	CElfMonster();

	void	AppearNow();
	void	ResetElfMon();

	virtual void	Run();
};

// �ż� ������
class CElfWarriorMonster : public CSpitSpiderMonster
{
protected:
	BOOL			m_fIsFirst;

public:
	CElfWarriorMonster();

	void	AppearNow();
	void	ResetElfMon();

	virtual void	Run();
};
