#ifndef _MAGIC_HANDLER
#define _MAGIC_HANDLER

#define _SKILL_BANWOL				0			// 반월.			半月弯刀
#define _SKILL_AMYOUNSUL			1			// 암연술.		施毒术 
#define _SKILL_FIREWIND				2			// 화염풍.		抗拒火环
#define _SKILL_HANGMAJINBUB			3			// 항마진법.		幽灵盾
#define _SKILL_DEJIWONHO			4			// 대지원호.		神圣战甲术
#define _SKILL_FIRE					5			// 염사장.		地狱火
#define _SKILL_MOOTEBO				6			// 무태보.		野蛮冲撞

#define _SKILL_TAMMING				7			// 뢰혼격.		诱惑之光
#define _SKILL_SPACEMOVE			8			// 아공행법.		瞬息移动
#define _SKILL_KILLUNDEAD			9			// 사자윤회.		圣言术

#define _SKILL_FIREBALL				10			// 화염장.		火球术
#define _SKILL_HEALLING				11			// 회복술.		治愈术
#define _SKILL_HOLYSHIELD			12			// 결계.			困魔咒
#define _SKILL_BIGHEALLING			13			// 대회복.		群体治疗术
#define _SKILL_LIGHTFLOWER			14			// 뢰설화.		地狱雷光
#define _SKILL_SHOOTLIGHTEN			15			// 뢰인장.		疾光电影
#define _SKILL_SKELLETON			16			// 백골소환술.	召唤骷髅
#define _SKILL_SNOWWIND				17			// 빙설풍.		冰咆哮
#define _SKILL_BIGCLOAK				18			// 대은신.		集体隐身术
#define _SKILL_SHIELD				19			// 주술의막.		魔法盾
#define _SKILL_SHOWHP				20			// 탐기파연.		心灵启示
#define _SKILL_EATTHFIRE			21			// 지염술.		火墙
#define _SKILL_FIRECHARM			22			// 폭살계.		灵魂火符
#define _SKILL_FIREBOOM				23			// 폭열파.		爆裂火焰
#define _SKILL_FIREBALL2			24			// 금강화염장.	大火球
#define _SKILL_YEDO					25			// 예도.			攻杀剑术
#define _SKILL_ERGUM				26			// 어검술.		刺杀剑术
#define _SKILL_LIGHTENING			27			// 강격.			雷电术
#define _SKILL_FIRESWORD			28			// 염화결.		烈火剑法
#define _SKILL_CLOAK				29			// 은신.			隐身术
#define _SKILL_SINSU				30			// 신수소환.		召唤神兽
#define _SKILL_ILKWANG				31			// 일광검법.		精神力战法
#define _SKILL_ONESWORD				32			// 외수검법.		基本剑术

class CMagicInfo
{
	/*
	* FLD_XXX 对应数据库表的属性
	*/
public:
	int		nIndex;			// FLD_INDEX
	char	szName[13];		// FLD_NAME
	
	short	sEffectType;	// FLD_EFFECTTYPE
	short	sEffect;		// FLD_EFFECT
	short	sSpell;			// FLD_SPELL
	short	sPower;			// FLD_POWER
	short	sMaxPower;		// FLD_MAXPOWER
	short	sDefSpell;		// FLD_DEFSPELL
	short	sDefPower;		// FLD_DEFPOWER
	short	sDefMaxPower;	// FLD_DEFMAXPOWER
	
	short	sJob;			// FLD_JOB

	short	sNeed[3];		// FLD_NEEDL1 FLD_NEEDL2 FLD_NEEDL3
	int		nTrain[3];		// FLD_L1TRAIN FLD_L2TRAIN FLD_L3TRAIN
	
	short	sDelay;			// FLD_DELAY

public:
	int		GetPower13(int nPwr, int nLevel);
	BOOL	CheckMagicLevelup(CCharObject* pCharObject, _LPTHUMANMAGICRCD lptMagicRcd);

	__inline int MPow() 
		{ if ((sDefMaxPower - sDefPower) > 0) return sDefPower + (rand() % (sDefMaxPower - sDefPower)); 
			else return sDefPower; }
	// 获取需要消耗的MP
	__inline int GetSpellPoint(int nLevel)
		{ return ROUND(sSpell / (3/*MaxTrainLevel*/ + 1) * (nLevel + 1)) + sDefSpell; }
	__inline int GetPower(int nPwr, int nLevel)
		{ if ((sDefMaxPower - sDefPower) > 0) return ROUND(nPwr / (3/*MaxTrainLevel*/ + 1) * (nLevel + 1)) + (sDefPower + (rand() % (sDefMaxPower - sDefPower))); 
			else return ROUND(nPwr / (3/*MaxTrainLevel*/ + 1) * (nLevel + 1)) + sDefPower; }	
};

#endif
