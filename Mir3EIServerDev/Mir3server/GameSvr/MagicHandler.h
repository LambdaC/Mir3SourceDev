#ifndef _MAGIC_HANDLER
#define _MAGIC_HANDLER

#define _SKILL_BANWOL				0			// �ݿ�.
#define _SKILL_AMYOUNSUL			1			// �Ͽ���.
#define _SKILL_FIREWIND				2			// ȭ��ǳ.
#define _SKILL_HANGMAJINBUB			3			// �׸�����.
#define _SKILL_DEJIWONHO			4			// ������ȣ.
#define _SKILL_FIRE					5			// ������.
#define _SKILL_MOOTEBO				6			// ���º�.

#define _SKILL_TAMMING				7			// ��ȥ��.
#define _SKILL_SPACEMOVE			8			// �ư����.
#define _SKILL_KILLUNDEAD			9			// ������ȸ.

#define _SKILL_FIREBALL				10			// ȭ����.
#define _SKILL_HEALLING				11			// ȸ����.
#define _SKILL_HOLYSHIELD			12			// ���.
#define _SKILL_BIGHEALLING			13			// ��ȸ��.
#define _SKILL_LIGHTFLOWER			14			// �ڼ�ȭ.
#define _SKILL_SHOOTLIGHTEN			15			// ������.
#define _SKILL_SKELLETON			16			// ����ȯ��.
#define _SKILL_SNOWWIND				17			// ����ǳ.
#define _SKILL_BIGCLOAK				18			// ������.
#define _SKILL_SHIELD				19			// �ּ��Ǹ�.
#define _SKILL_SHOWHP				20			// Ž���Ŀ�.
#define _SKILL_EATTHFIRE			21			// ������.
#define _SKILL_FIRECHARM			22			// �����.
#define _SKILL_FIREBOOM				23			// ������.
#define _SKILL_FIREBALL2			24			// �ݰ�ȭ����.
#define _SKILL_YEDO					25			// ����.
#define _SKILL_ERGUM				26			// ��˼�.
#define _SKILL_LIGHTENING			27			// ����.
#define _SKILL_FIRESWORD			28			// ��ȭ��.
#define _SKILL_CLOAK				29			// ����.
#define _SKILL_SINSU				30			// �ż���ȯ.
#define _SKILL_ILKWANG				31			// �ϱ��˹�.
#define _SKILL_ONESWORD				32			// �ܼ��˹�.

class CMagicInfo
{
public:
	int		nIndex;
	char	szName[13];
	
	short	sEffectType;
	short	sEffect;
	short	sSpell;
	short	sPower;
	short	sMaxPower;
	short	sDefSpell;
	short	sDefPower;
	short	sDefMaxPower;
	
	short	sJob;

	short	sNeed[3];
	int		nTrain[3];
	
	short	sDelay;

public:
	int		GetPower13(int nPwr, int nLevel);
	BOOL	CheckMagicLevelup(CCharObject* pCharObject, _LPTHUMANMAGICRCD lptMagicRcd);

	__inline int MPow() 
		{ if ((sDefMaxPower - sDefPower) > 0) return sDefPower + (rand() % (sDefMaxPower - sDefPower)); 
			else return sDefPower; }
	__inline int GetSpellPoint(int nLevel)
		{ return ROUND(sSpell / (3/*MaxTrainLevel*/ + 1) * (nLevel + 1)) + sDefSpell; }
	__inline int GetPower(int nPwr, int nLevel)
		{ if ((sDefMaxPower - sDefPower) > 0) return ROUND(nPwr / (3/*MaxTrainLevel*/ + 1) * (nLevel + 1)) + (sDefPower + (rand() % (sDefMaxPower - sDefPower))); 
			else return ROUND(nPwr / (3/*MaxTrainLevel*/ + 1) * (nLevel + 1)) + sDefPower; }	
};

#endif
