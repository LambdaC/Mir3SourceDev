#ifndef _SPRITEDEF_H
#define _SPRITEDEF_H

// ĳ����, ����, NPC���� ��������Ʈ�� Define�Ѵ�.

#define	 _MAX_HUMAN_RACE_FRAME	  2640

// ĳ���� ���� Define.
#define	 _MAX_HUMAN_RACE			 3

#define	 _HUMAN_RACE_TYPE1			 0		// �˸� ����.
//#define	 _HUMAN_RACE_TYPE2			 1		// �˸� ����.
#define	 _HUMAN_RACE_TYPE2			 1		// �� ����.
//#define	 _HUMAN_RACE_TYPE4			 3		// �� ����.
#define	 _HUMAN_RACE_TYPE3			 2		// �氩 ����.
//#define	 _HUMAN_RACE_TYPE6			 5		// �氩 ����.
//#define	 _HUMAN_RACE_TYPE7			 6		// ������ ���� ����.
//#define	 _HUMAN_RACE_TYPE8			 7		// ������ ���� ����.
//#define	 _HUMAN_RACE_TYPE9			 8		// ������ ���� ����.
//#define	 _HUMAN_RACE_TYPE10			 9		// ������ ���� ����.
//#define	 _HUMAN_RACE_TYPE11			10		// ������ ���� ����.
//#define	 _HUMAN_RACE_TYPE12			11		// ������ ���� ����.


// ĳ���� ���� Define.
#define  _MAX_HUMAN_MTN				33

#define  _MT_HUMAN_STAND			 0
#define  _MT_HUMAN_ARROWATTACK		 1
#define  _MT_HUMAN_SPELL1			 2
#define  _MT_HUMAN_SPELL2			 3
#define  _MT_HUMAN_HOLD				 4
#define  _MT_HUMAN_PUSHBACK			 5
#define  _MT_HUMAN_PUSHBACKFLY		 6 
#define  _MT_HUMAN_ATTACKMODE		 7
#define  _MT_HUMAN_CUT				 8
#define  _MT_HUMAN_ONEVSWING		 9
#define  _MT_HUMAN_TWOVSWING		10
#define  _MT_HUMAN_ONEHSWING		11
#define  _MT_HUMAN_TWOHSWING		12
#define  _MT_HUMAN_SPEARVSWING		13
#define  _MT_HUMAN_SPEARHSWING		14
#define  _MT_HUMAN_HITTED			15
#define  _MT_HUMAN_WHEELWIND		16
#define  _MT_HUMAN_RANDSWING		17
#define  _MT_HUMAN_BACKDROPKICK		18
#define  _MT_HUMAN_PUSHBACKDEAD		19
#define  _MT_HUMAN_SPECIALDEAD		20
#define  _MT_HUMAN_WALK				21
#define  _MT_HUMAN_RUN				22
#define  _MT_HUMAN_MOODEPO			23
#define  _MT_HUMAN_ROLL				24
#define  _MT_HUMAN_FISHSTAND		25
#define  _MT_HUMAN_FISHHAND			26
#define  _MT_HUMAN_FISHTHROW		27
#define  _MT_HUMAN_FISHPULL			28
#define  _MT_HUMAN_HORSESTAND		29
#define  _MT_HUMAN_HORSEWALK		30
#define  _MT_HUMAN_HORSERUN			31
#define  _MT_HUMAN_HORSEHITT		32
/*
#define  _MT_HUMAN_WEAPON1			33
#define  _MT_HUMAN_WEAPON2			34
#define  _MT_HUMAN_WEAPON3			35
*/



// ���� ���� Define
#define	 _MAX_MON_RACE				 5

#define	 _RACE_LIZARD				 0
#define	 _RACE_NIGHTGHOST			 1
#define	 _RACE_THORN				 2
#define	 _RACE_SANDMON				 3
#define	 _RACE_GOLEM				 4


// ���� ���� Define
#define  _MAX_MON_MTN				 9	

#define  _MT_MON_STAND				 0
#define  _MT_MON_WALK				 1
#define  _MT_MON_ATTACK				 2
#define  _MT_MON_STRUCK				 3
#define  _MT_MON_DIE				 4
#define  _MT_MON_DEATH				 5
#define  _MT_MON_APPEAR				 6
#define  _MT_MON_DISAPPEAR			 7
#define  _MT_MON_CRITICAL			 8


typedef struct tagMTNFRMINFO
{
	SHORT	shStartFrm;
	BYTE	bFrmCnt;
	BYTE	bSkip;
	SHORT	shDelay;
	BOOL	bReverse;
}MTNFRMINFO, *LPMTNFRMINFO;

typedef struct tagHUMANRACEINFO
{
	SHORT	shImgIdx;
	SHORT	shRaceStartFrm;
	SHORT	shRaceEndFrm;
	MTNFRMINFO stMtn[_MAX_HUMAN_MTN];
}HUMANRACEINFO, *LPHUMANRACEINFO;

typedef struct tagMONRACEINFO
{
	SHORT	shImgIdx;
	SHORT	shRaceStartFrm;
	SHORT	shRaceEndFrm;
	MTNFRMINFO stMtn[_MAX_MON_MTN];
}MONRACEINFO, *LPMONRACEINFO;



class CSpriteInfo
{
public:
	HUMANRACEINFO	m_stHuman[_MAX_HUMAN_RACE];
	MONRACEINFO		m_stMon[_MAX_MON_RACE];
public:
	CSpriteInfo();
	~CSpriteInfo();

	Init();
	VOID SetSpriteInfo();

	VOID SetHumanSpriteInfo();
	VOID SetMonSpriteInfo();
	VOID SetHumanRaceInfo(LPHUMANRACEINFO pstHumanRaceInfo, SHORT shImgIdx, SHORT shRaceStartFrm, SHORT	shRaceEndFrm);
	VOID SetMonRaceInfo(LPMONRACEINFO pstMonRaceInfo, SHORT shImgIdx, SHORT shRaceStartFrm, SHORT shRaceEndFrm);
	VOID SetMotionInfo(LPMTNFRMINFO pstMtnFrmInfo, SHORT shStartFrm, BYTE bFrmCnt, BYTE bSkip, SHORT shDelay, BOOL bReverse);
};



#endif //_SPRITEDEF_H




// �������� ����......
/*
LPRACE

typedef struct tagRACETYPEINFO
{
	SHORT			shStartFrm;
	SHORT			shEndFrm;
	SHORT			shMaxMtn;
	SHORT			shMaxFrame;
	SHORT			shImgIdx;
	LPMTNFRMINFO	pstMtn;
}HUMANRACEINFO, *LPHUMANRACEINFO;

typedef struct tagMTNINFO
{
	BYTE	bMtnFrmOffset;				// ���� ���ۿ� ���� �ִ� ������.
	WORD	wDir;						// ������ �ִº�Ʈ�� 1�� ���õȴ�.
	BYTE	bStartFrm;					// ���� ������.
	BYTE	bFrmCnt;					// �������� ����.
	SHORT	shDelay;					// ���� ������ Delay.
	BOOL	bReverse;					// ������ �Ųٷ� ������������ ����.
}MTNFRMINFO, *LPMTNFRMINFO;
*/































