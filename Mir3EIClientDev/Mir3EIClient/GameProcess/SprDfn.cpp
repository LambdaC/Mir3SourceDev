/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


/******************************************************************************************************************

	CSprite Class

*******************************************************************************************************************/
/******************************************************************************************************************

	�Լ��� : CSprite::CSprite()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CSprite::CSprite()
{
	InitSpriteInfo();
}



/******************************************************************************************************************

	�Լ��� : CSprite::~CSprite()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CSprite::~CSprite()
{
	DeleteSpriteInfo();
}



/******************************************************************************************************************

	�Լ��� : CSprite::InitSpriteInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::InitSpriteInfo()
{	
	ZeroMemory(m_stHeroSpr,		sizeof(SPRFRMDEF)*_MAX_HERO_MTN);
	ZeroMemory(m_stMonSpr,		sizeof(SPRFRMDEF)*_MAX_MON_MTN);
	ZeroMemory(m_stNPCSpr,		sizeof(SPRFRMDEF)*_MAX_NPC_MTN);

	ZeroMemory(m_stEffectSpr,	sizeof(EFFECTSPRINFO)*_MAX_EFFECT);
	ZeroMemory(m_stMagicSpr,	sizeof(EFFECTSPRINFO)*_MAX_MAGIC);
	ZeroMemory(m_stExplosionSpr,sizeof(EFFECTSPRINFO)*_MAX_EXPLOSION);
}



/******************************************************************************************************************

	�Լ��� : CSprite::DeleteSpriteInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::DeleteSpriteInfo()
{
	InitSpriteInfo();
}
 


/******************************************************************************************************************

	�Լ��� : CSprite::SetEffectInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPEFFECTSPRINFO pstEffect
	         DWORD dwFstFrm
	         DWORD dwEndFrm
	         WORD wDelay
	         WORD wImgIdx
	         WORD wEffectIdx
	         BYTE bSLightRadius
	         BYTE bLLightRadius
	         BYTE bSLightRColor
	         BYTE bSLightGColor
	         BYTE bSLightBColor
	         BYTE bLLightRColor
	         BYTE bLLightGColor
	         BYTE bLLightBColor
	         BYTE bBlendType
	         BYTE bOpa
	         BYTE bSwingCnt
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::SetEffectInfo(LPEFFECTSPRINFO pstEffect, DWORD dwFstFrm, DWORD dwEndFrm, WORD wDelay, WORD wImgIdx, WORD wEffectIdx,
				   BYTE bSLightRadius, BYTE bLLightRadius, 
				   BYTE bSLightRColor, BYTE bSLightGColor, BYTE bSLightBColor,
				   BYTE bLLightRColor, BYTE bLLightGColor, BYTE bLLightBColor, 
				   BYTE bMagicRColor, BYTE bMagicGColor, BYTE bMagicBColor, 
				   BYTE bBlendType, BYTE bOpa, BYTE bSwingCnt)
{
	pstEffect->dwFstFrm = dwFstFrm;
	pstEffect->dwEndFrm = dwEndFrm;
	pstEffect->wDelay	= wDelay;
	pstEffect->wImgIdx  = wImgIdx;
	pstEffect->wEffectIdx = wEffectIdx;

	pstEffect->bLightRadius[0] = bSLightRadius;
	pstEffect->bLightRadius[1] = bLLightRadius;

	pstEffect->bLightColor[0][0] = bSLightRColor;
	pstEffect->bLightColor[0][1] = bSLightGColor;
	pstEffect->bLightColor[0][2] = bSLightBColor;

	pstEffect->bLightColor[1][0] = bLLightRColor;
	pstEffect->bLightColor[1][1] = bLLightGColor;
	pstEffect->bLightColor[1][2] = bLLightBColor;

	pstEffect->bMagicColor[0] = bMagicRColor;
	pstEffect->bMagicColor[1] = bMagicGColor;
	pstEffect->bMagicColor[2] = bMagicBColor;

	pstEffect->bBlendType	= bBlendType;
	pstEffect->bOpa			= bOpa;
	pstEffect->bSwingCnt	= bSwingCnt;
}


/******************************************************************************************************************

	�Լ��� : CSprite::GetEffectInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wEffectNum
	���   : LPEFFECTSPRINFO 

	[����][������] : ��������

*******************************************************************************************************************/
LPEFFECTSPRINFO CSprite::GetEffectInfo(WORD wEffectNum)
{
	LPEFFECTSPRINFO pstEffect = NULL;

	for ( INT nCnt = 0; nCnt < _MAX_EFFECT; nCnt++ )
	{
		if ( wEffectNum == m_stEffectSpr[nCnt].wEffectIdx )
		{
			pstEffect = &m_stEffectSpr[nCnt];			
			break;
		}
	}

	return pstEffect;
}



/******************************************************************************************************************

	�Լ��� : CSprite::GetExplosionInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wEffectNum
	���   : LPEFFECTSPRINFO 

	[����][������] : ��������

*******************************************************************************************************************/
LPEFFECTSPRINFO CSprite::GetExplosionInfo(WORD wEffectNum)
{
	LPEFFECTSPRINFO pstEffect = NULL;

	for ( INT nCnt = 0; nCnt < _MAX_EXPLOSION; nCnt++ )
	{
		if ( wEffectNum == m_stExplosionSpr[nCnt].wEffectIdx )
		{
			pstEffect = &m_stExplosionSpr[nCnt];
			break;
		}
	}

	return pstEffect;
}



/******************************************************************************************************************

	�Լ��� : CSprite::GetMagicInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wEffectNum
	���   : LPEFFECTSPRINFO 

	[����][������] : ��������

*******************************************************************************************************************/
LPEFFECTSPRINFO CSprite::GetMagicInfo(WORD wEffectNum)
{
	LPEFFECTSPRINFO pstEffect = NULL;

	for ( INT nCnt = 0; nCnt < _MAX_MAGIC; nCnt++ )
	{
		if ( wEffectNum == m_stMagicSpr[nCnt].wEffectIdx )
		{
			pstEffect = &m_stMagicSpr[nCnt];		
			break;
		}
	}

	return pstEffect;
}



/******************************************************************************************************************

	�Լ��� : CSprite::SetSprDfn()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPSPRFRMDEF pstSprDfn
	         WORD wFstFrm
	         WORD wFrmCnt
	         WORD wDelay
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::SetSprDfn(LPSPRFRMDEF pstSprDfn, WORD wFstFrm, WORD wFrmCnt, WORD wDelay)
{
	pstSprDfn->wFstFrm	= wFstFrm;
	pstSprDfn->wFrmCnt	= wFrmCnt;
	pstSprDfn->wDelay	= wDelay;
}


/******************************************************************************************************************

	�Լ��� : CSprite::SetInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::SetInfo()
{
	SetWeaponOrder("weapon.ord");

	//~~~ Hero ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stHeroSpr[0],     0,  4, 200);			// _MT_STAND		
	SetSprDfn(&m_stHeroSpr[1],    80,  6, 100);			// _MT_ARROWATTACK	
	SetSprDfn(&m_stHeroSpr[2],   160,  5,  80);			// _MT_SPELL1		
	SetSprDfn(&m_stHeroSpr[3],   240,  5,  80);			// _MT_SPELL2		
	SetSprDfn(&m_stHeroSpr[4],   320,  1, 100);			// _MT_HOLD		
	SetSprDfn(&m_stHeroSpr[5],   400,  1, 100);			// _MT_PUSHBACK	
	SetSprDfn(&m_stHeroSpr[6],   480,  1, 100);			// _MT_PUSHBACKFLY	
	SetSprDfn(&m_stHeroSpr[7],   560,  3, 200);			// _MT_ATTACKMODE	
	SetSprDfn(&m_stHeroSpr[8],   640,  2, 300);			// _MT_CUT			
	SetSprDfn(&m_stHeroSpr[9],   720,  6,  85);			// _MT_ONEVSWING
	SetSprDfn(&m_stHeroSpr[10],  800,  6,  85);			// _MT_TWOVSWING	
	SetSprDfn(&m_stHeroSpr[11],  880,  6,  85);			// _MT_ONEHSWING	
	SetSprDfn(&m_stHeroSpr[12],  960,  6,  85);			// _MT_TWOHSWING	
	SetSprDfn(&m_stHeroSpr[13], 1040,  6,  85);			// _MT_SPEARVSWING	
	SetSprDfn(&m_stHeroSpr[14], 1120,  6,  85);			// _MT_SPEARHSWING	
	SetSprDfn(&m_stHeroSpr[15], 1200,  3, 100);			// _MT_HITTED		
	SetSprDfn(&m_stHeroSpr[16], 1280, 10,  70);			// _MT_WHEELWIND	
	SetSprDfn(&m_stHeroSpr[17], 1360, 10,  90);			// _MT_RANDSWING	
	SetSprDfn(&m_stHeroSpr[18], 1440, 10, 100);			// _MT_BACKDROPKICK
	SetSprDfn(&m_stHeroSpr[19], 1520, 10, 120);			// _MT_DIE			
	SetSprDfn(&m_stHeroSpr[20], 1600, 10, 100);			// _MT_SPECIALDIE	
	SetSprDfn(&m_stHeroSpr[21], 1680,  6,  90);			// _MT_WALK		
	SetSprDfn(&m_stHeroSpr[22], 1760,  6, 120);			// _MT_RUN			
	SetSprDfn(&m_stHeroSpr[23], 1840,  6, 100);			// _MT_MOODEPO		
	SetSprDfn(&m_stHeroSpr[24], 1920, 10, 100);			// _MT_ROLL		
	SetSprDfn(&m_stHeroSpr[25], 2000,  4, 180);			// _MT_FISHSTAND	
	SetSprDfn(&m_stHeroSpr[26], 2080,  3, 180);			// _MT_FISHHAND	
	SetSprDfn(&m_stHeroSpr[27], 2160,  8, 180);			// _MT_FISHTHROW	
	SetSprDfn(&m_stHeroSpr[28], 2240,  8, 180);			// _MT_FISHPULL	
	SetSprDfn(&m_stHeroSpr[29], 2320,  4, 200);			// _MT_HORSESTAND	
	SetSprDfn(&m_stHeroSpr[30], 2400,  6, 100);			// _MT_HORSEWALK	
	SetSprDfn(&m_stHeroSpr[31], 2480,  6, 100);			// _MT_HORSERUN	
	SetSprDfn(&m_stHeroSpr[32], 2560,  3, 100);			// _MT_HORSEHIT	

	//~~~ Monster ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stMonSpr[0],     0,  4, 300);			// _MT_MON_STAND.
	SetSprDfn(&m_stMonSpr[1],    80,  6, 130);			// _MT_MON_WALK.
	SetSprDfn(&m_stMonSpr[2],   160,  6, 120);			// _MT_MON_ATTACK_A.
	SetSprDfn(&m_stMonSpr[3],   240,  2, 300);			// _MT_MON_HITTED.
	SetSprDfn(&m_stMonSpr[4],   320, 10, 150);			// _MT_MON_DIE.
	SetSprDfn(&m_stMonSpr[5],   400,  6, 150);			// _MT_MON_ATTACK_B1.
	SetSprDfn(&m_stMonSpr[6],   480, 10, 150);			// _MT_MON_SPELL_A2.
	SetSprDfn(&m_stMonSpr[7],   560, 10, 150);			// _MT_MON_SPELL_B.
	SetSprDfn(&m_stMonSpr[8],   640,  6, 150);			// _MT_MON_APPEAR.
	SetSprDfn(&m_stMonSpr[9],   880,  1, 150);			// _MT_MON_SPECIAL_MTN.

	//~~~ NPC ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stNPCSpr[0],     0,  4, 300);			// _MT_NPC_STAND.
	SetSprDfn(&m_stNPCSpr[1],    30, 10, 300);			// _MT_NPC_ACT01.
	SetSprDfn(&m_stNPCSpr[2],    60,  6, 300);			// _MT_NPC_ACT02.

	//~~~ Effect Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stEffectSpr[0],   230,  236, 100, _IMAGE_MAGIC,       _SKILL_BANWOL, 3, 4, 100, 100, 100, 100, 100, 170);	// �ݿ����� 12��.
	SetEffectInfo(&m_stEffectSpr[1],    60,   70, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 100, 100, 100, 100, 160, 100, 255, 255, 255, _BLEND_NORMAL);	// �Ͽ��� ����.
	SetEffectInfo(&m_stEffectSpr[2],    90,   98, 100, _IMAGE_MAGIC,     _SKILL_FIREWIND, 3, 4, 100, 100, 100, 100, 140, 180);	// ȭ��ǳ.
	SetEffectInfo(&m_stEffectSpr[3],  1820, 1828, 100, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4, 100, 100, 100, 100, 140, 180);	// ������ ����.
	SetEffectInfo(&m_stEffectSpr[4],     0,    9, 100, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 100, 100, 100, 170, 100, 100);	// ��ȥ�ݽ���.
	SetEffectInfo(&m_stEffectSpr[5],   110,  129, 100, _IMAGE_MAGIC,    _SKILL_SPACEMOVE, 3, 4, 100, 100, 100, 170, 100, 100);	// �ư����.
	SetEffectInfo(&m_stEffectSpr[6],   130,  140, 100, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 100, 100, 100, 170, 100, 100);	// ������ȸ����.
	SetEffectInfo(&m_stEffectSpr[7],  1820, 1828, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 3, 4, 100, 100, 100, 100, 140, 180);	// ȭ����.
	SetEffectInfo(&m_stEffectSpr[8],   600,  610, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 100, 100, 100, 140, 100, 120);	// ȸ����.
	SetEffectInfo(&m_stEffectSpr[9],   630,  640, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 100, 100, 100, 170, 100, 100);	// ���.
	SetEffectInfo(&m_stEffectSpr[10],  660,  670, 100, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 3, 4, 100, 100, 100, 140, 100, 120);	// ��ȸ��.
//	SetEffectInfo(&m_stEffectSpr[11],  690,  704, 100, _IMAGE_MAGIC,  _SKILL_LIGHTFLOWER, 3, 4, 100, 100, 100, 170, 100, 100);	// �ڼ�ȭ.
	SetEffectInfo(&m_stEffectSpr[11],  690,  704, 100, _IMAGE_MAGIC,  _SKILL_LIGHTFLOWER, 3, 4, 150, 100,  50, 150, 100,  50);	// �ڼ�ȭ.	
	SetEffectInfo(&m_stEffectSpr[12], 1970, 1978,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 3, 4, 100, 100, 100, 170, 100, 100);	// ������.
	SetEffectInfo(&m_stEffectSpr[13],  740,  750, 100, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 100, 100, 100, 120, 100, 120);	// ����ȯ��.
	SetEffectInfo(&m_stEffectSpr[14],  770,  780, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 3, 4, 100, 100, 100, 170, 100, 100);	// ����ǳ.
	SetEffectInfo(&m_stEffectSpr[15],  870,  890, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4, 100, 100, 100, 100, 100, 170);	// Ž���Ŀ�.
	SetEffectInfo(&m_stEffectSpr[16],  910,  920, 100, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 3, 4, 100, 100, 100, 100, 140, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[17],  940,  950, 100, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 3, 4, 100, 100, 100, 100, 140, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[18], 1560, 1569, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 3, 4, 100, 100, 100, 100, 140, 180);	// �ݰ�ȭ����.
	SetEffectInfo(&m_stEffectSpr[19],  320,  326, 100, _IMAGE_MAGIC,        _SKILL_ERGUM, 3, 4, 100, 100, 100, 100, 100, 170);	// ��˼�.
	SetEffectInfo(&m_stEffectSpr[20], 1350, 1356, 100, _IMAGE_MAGIC,         _SKILL_YEDO, 3, 4, 100, 100, 100, 100, 100, 170);	// �����˹�.
	SetEffectInfo(&m_stEffectSpr[21], 1470, 1476, 100, _IMAGE_MAGIC,    _SKILL_FIRESWORD, 3, 4, 100, 100, 100, 100, 140, 180);	// ��ȭ��.
	SetEffectInfo(&m_stEffectSpr[22], 1430, 1445, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 3, 4, 100, 100, 100, 170, 100, 100);	// ����.
	SetEffectInfo(&m_stEffectSpr[23],  810,  820, 100, _IMAGE_MAGIC,        _SKILL_CLOAK, 3, 4, 150, 150, 150, 200, 150, 180);	// ����.
	SetEffectInfo(&m_stEffectSpr[24], 2080, 2086, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 3, 4, 150, 100,  50, 200, 150, 100);	// �׸�����.
	SetEffectInfo(&m_stEffectSpr[25], 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 3, 4, 150, 180, 200, 180, 200, 220);	// ������ȣ.
	SetEffectInfo(&m_stEffectSpr[26], 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 3, 4, 100, 150, 200, 150, 200, 250);	// �����.
	SetEffectInfo(&m_stEffectSpr[27], 2080, 2086, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 3, 4, 150, 150, 150, 200, 150, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[28], 2180, 2190, 100, _IMAGE_MAGIC,     _SKILL_JUMPSHOT, 3, 4, 150, 150, 150, 200, 150, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[29], 2270, 2280, 100, _IMAGE_MAGIC,    _SKILL_RANDSWING, 3, 4, 150, 150, 150, 200, 150, 180);	// ��������.
	SetEffectInfo(&m_stEffectSpr[30], 2080, 2086, 100, _IMAGE_MAGIC,		_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// �ż���ȯ.

	SetEffectInfo(&m_stEffectSpr[31], 1680, 1686, 100, _IMAGE_MONMAGIC, _MONMAGIC_NUMAGUMGI, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);// ������ �˱�.
	SetEffectInfo(&m_stEffectSpr[32], 830, 839, 100, _IMAGE_MAGIC, _SKILL_SHIELD, 3, 4, 100, 100, 100, 170, 100, 100);			// �ּ��Ǹ�.
	//~~~ Monster Effect Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//~~~ Magic Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stMagicSpr[0],    70,   88, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 190, 220, 190, 190, 240, 190, 255, 255, 255, _BLEND_NORMAL); // �Ͽ���.
	SetEffectInfo(&m_stMagicSpr[1],  1900, 1960,  50, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4,  70,  90, 110,  90, 120, 150);	// ������.
	SetEffectInfo(&m_stMagicSpr[2],    10,   30,  50, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 200, 100, 100, 250, 150, 150);	// ��ȥ��.
	SetEffectInfo(&m_stMagicSpr[3],   140,  159,  50, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 200, 100, 100, 100,  75,  50);	// ������ȸ.
	SetEffectInfo(&m_stMagicSpr[4],   420,  425,  20, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 100, 150, 200, 150, 200, 250);	// ȭ����.
	SetEffectInfo(&m_stMagicSpr[5],   610,  620, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 200, 140, 170, 230, 170, 200);	// ȸ����.
	SetEffectInfo(&m_stMagicSpr[6],   640,  650, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 120,  60,  60, 150,  80,  80);	// ���.
	SetEffectInfo(&m_stMagicSpr[7],   670,  680,  50, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 4, 5, 200, 140, 170, 230, 170, 200);//200, 100, 100, 250, 150, 150);	// ��ȸ��.
	SetEffectInfo(&m_stMagicSpr[8],  2050, 2056,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 2, 3, 150, 100, 100, 200, 150, 150);	// ������.
	SetEffectInfo(&m_stMagicSpr[9],   750,  760, 155, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 150, 150, 150, 200, 150, 180);	// ����ȯ��.
	SetEffectInfo(&m_stMagicSpr[10],  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 5, 6, 255, 123,   0, 255, 123,   0, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);	// ����ǳ.
//	SetEffectInfo(&m_stMagicSpr[10],  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 4, 5, 220, 150, 150, 250, 170, 170);	// ����ǳ.
	SetEffectInfo(&m_stMagicSpr[11],  840,  850, 100, _IMAGE_MAGIC,       _SKILL_SHIELD, 3, 4, 100, 100, 100, 100, 140, 180);	// �ּ��Ǹ�.
	SetEffectInfo(&m_stMagicSpr[12],  890,  900, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4,  75,  75,  75, 100,  75,  50);	// Ž���Ŀ�.
	SetEffectInfo(&m_stMagicSpr[13],  920,  930, 120, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 4, 5,  40,  60,  80,  60,  80, 100);	// ������.
	SetEffectInfo(&m_stMagicSpr[14],  980,  983, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 100, 150, 200, 150, 200, 250, 255, 255, 255, _BLEND_NORMAL, 255);	// �����.
	SetEffectInfo(&m_stMagicSpr[15],  980,  983, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 2, 3, 150, 100,  50, 200, 150, 100, 255, 255, 255, _BLEND_NORMAL, 255);	// �׸�����.
	SetEffectInfo(&m_stMagicSpr[16],  980,  983, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 2, 3, 150, 180, 200, 180, 200, 220, 255, 255, 255, _BLEND_NORMAL, 255);	// ������ȣ.
	SetEffectInfo(&m_stMagicSpr[17],  950,  970, 100, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 5, 6, 100, 150, 200, 150, 200, 250);	// ������.
	SetEffectInfo(&m_stMagicSpr[18], 1640, 1646,  20, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 100, 150, 200, 150, 200, 250);	// �ݰ�ȭ����.
//	SetEffectInfo(&m_stMagicSpr[19], 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 5, 6, 250, 150, 150, 255, 200, 200);	// ����.
	SetEffectInfo(&m_stMagicSpr[19], 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 20, 21, 255, 125, 50, 255, 255, 255);	// ����.
	SetEffectInfo(&m_stMagicSpr[20],  980,  983, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 2, 3, 150, 150, 150, 200, 150, 180);	// ������.
	SetEffectInfo(&m_stMagicSpr[21],  110,  129,  60, _IMAGE_MAGIC,   _SKILL_SPACEMOVE2, 3, 4, 100, 100, 100, 100, 100, 100);	// �ư����2.
	SetEffectInfo(&m_stMagicSpr[22],  110,  129, 100, _IMAGE_MAGIC,   _SKILL_SPACEMOVE3, 3, 4, 100, 100, 100, 100, 100, 100);	// �ư����3.

	//~~~ Monster Magic Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stMagicSpr[23],    0,    4, 100, _IMAGE_MONMAGIC,    _MONMAGIC_KEPAL, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[24],  300,  320, 100, _IMAGE_MONMAGIC,  _MONMAGIC_EXPLODE, 2, 3, 100, 100,  50, 150, 150,  75);	
	SetEffectInfo(&m_stMagicSpr[25],   20,   30, 100, _IMAGE_MONMAGIC,   _MONMAGIC_BLACK1, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[26],   40,   50, 100, _IMAGE_MONMAGIC,   _MONMAGIC_BLACK2, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[27],   80,   86, 100, _IMAGE_MONMAGIC,  _MONMAGIC_ANTHEAL, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[28],  200,  208, 100, _IMAGE_MONMAGIC, _MONMAGIC_GREATANT, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[29],  280,  289, 100, _IMAGE_MONMAGIC,	   _MONMAGIC_RED1, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[30],   40,   50, 100, _IMAGE_MONMAGIC,     _MONMAGIC_RED2, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[31],  220,  227, 100, _IMAGE_MONMAGIC,      _MONMAGIC_ANT, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[32],  240,  246, 100, _IMAGE_MONMAGIC,  _MONMAGIC_WORKANT, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[33],  440,  446, 100, _IMAGE_MONMAGIC, _MONMAGIC_COWGHOST, 2, 3, 100, 100, 100, 150, 150, 150);	// ���Ϳ�.
	SetEffectInfo(&m_stMagicSpr[34],  980,  986, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINSU, 2, 3, 100, 100, 100, 150, 150, 150);	// �ż�.
	SetEffectInfo(&m_stMagicSpr[35],  600,  606, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE, 2, 3, 100, 100, 100, 150, 150, 150);	// ����.
	SetEffectInfo(&m_stMagicSpr[36],  720,  728, 100, _IMAGE_MONMAGIC, _MONMAGIC_JUMAWANG, 2, 3, 100, 100, 100, 150, 150, 150);	// �ָ���.

	SetEffectInfo(&m_stMagicSpr[37], 1240, 1241, 100, _IMAGE_MONMAGIC,         _MONMAGIC_CHIM, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// ��ũħ.
	SetEffectInfo(&m_stMagicSpr[38], 1400, 1401, 100, _IMAGE_MONMAGIC,        _MONMAGIC_ARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// �ü����ȭ��.
	SetEffectInfo(&m_stMagicSpr[39], 1070, 1071, 100, _IMAGE_MONMAGIC,      _MONMAGIC_MAARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// ���û�ȭ��.
	SetEffectInfo(&m_stMagicSpr[40],  800,  806, 100, _IMAGE_MONMAGIC,      _MONMAGIC_DUALAXE, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// �ֵ����ذ������.
	SetEffectInfo(&m_stMagicSpr[41],  520,  527, 100, _IMAGE_MONMAGIC,     _MONMAGIC_COWFLAME, 2, 3, 100, 100, 100, 150, 150, 150);	// ȭ������.
	SetEffectInfo(&m_stMagicSpr[42],  360,  370, 100, _IMAGE_MONMAGIC,  _MONMAGIC_BIGGINE_ATT, 2, 3, 100, 100, 100, 150, 150, 150);	// �˷�� ����.
	SetEffectInfo(&m_stMagicSpr[43],  380,  400, 100, _IMAGE_MONMAGIC, _MONMAGIC_BIGGINE_CHAR, 2, 3, 100, 100, 100, 150, 150, 150);	// �˷�ſ� ���ݴ���.
	SetEffectInfo(&m_stMagicSpr[44],  320,  330,  70, _IMAGE_MONMAGIC,     _MONMAGIC_SANDFISH, 2, 3, 100, 100, 100, 150, 150, 150,  10,  10,  10, _BLEND_LIGHTINV, 0);		// ������.
	SetEffectInfo(&m_stMagicSpr[45],  260,  266, 100, _IMAGE_MONMAGIC,       _MONMAGIC_BAODIE, 2, 3, 100, 100, 100, 150, 150, 150);	// �ٺ��޵�����.
	SetEffectInfo(&m_stMagicSpr[46],  880,  886, 150, _IMAGE_MONMAGIC,        _MONMAGIC_SSEGI, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15);		// ���⳪��Ÿ��.
	SetEffectInfo(&m_stMagicSpr[47],   60,   70, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINGI_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// �����ױ�. �氩�ʱ��, ȫ��, ���Ǹ�����. // ���ⱸ���� ����.
	SetEffectInfo(&m_stMagicSpr[48],  680,  689, 100, _IMAGE_MONMAGIC,     _MONMAGIC_HUSU_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// ����ƺ��ױ�.
	SetEffectInfo(&m_stMagicSpr[49],  700,  708, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// �����ױ�.

	SetEffectInfo(&m_stMagicSpr[50],  980,  983, 10, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// �ż�.

	SetEffectInfo(&m_stMagicSpr[51],  1770,  1790, 100, _IMAGE_MONMAGIC,  _MONMAGIC_EXPLODE1, 2, 3, 100, 100,  50, 150, 150,  75);	

	//~~~ Explosion Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stExplosionSpr[0],  200,  220,  80, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 4, 5, 200, 150,  60, 255, 170, 100, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);// �׸�����.
	SetEffectInfo(&m_stExplosionSpr[1],  170,  190,  80, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 4, 5, 120, 170, 220, 160, 210, 255, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);// ������ȣ.
	SetEffectInfo(&m_stExplosionSpr[2],  580,  590, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 120, 170, 220, 160, 210, 255);	// ȭ����.
	SetEffectInfo(&m_stExplosionSpr[3], 1140, 1150, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 120, 170, 220, 160, 210, 255);	// �����.
	SetEffectInfo(&m_stExplosionSpr[4], 1800, 1810, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 120, 170, 220, 160, 210, 255);	// �ݰ�ȭ����.
	SetEffectInfo(&m_stExplosionSpr[5],  820,  830, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 4, 5, 200, 210, 190, 200, 150, 180);	// ������.
	//~~~ Monster Explosion Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stExplosionSpr[6],  100,  110, 100, _IMAGE_MONMAGIC, _MONMAGIC_ANTHEAL, 2, 3, 100, 100, 100, 150, 150, 150);	// ���ⱸ���� ����.

	SetEffectInfo(&m_stExplosionSpr[7], 2360, 2379, 100, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// �ż�.
}



VOID CSprite::SetMonFrameInfo(WORD wMonNum)
{
/*	//~~~ Monster ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stMonSpr[0],     0,  4, 300);			// _MT_MON_STAND.
	SetSprDfn(&m_stMonSpr[1],    80,  6, 130);			// _MT_MON_WALK.
	SetSprDfn(&m_stMonSpr[2],   160,  6, 120);			// _MT_MON_ATTACK_A.
	SetSprDfn(&m_stMonSpr[3],   240,  2, 300);			// _MT_MON_HITTED.
	SetSprDfn(&m_stMonSpr[4],   320, 10, 150);			// _MT_MON_DIE.
	SetSprDfn(&m_stMonSpr[5],   400,  6, 150);			// _MT_MON_ATTACK_B.
	SetSprDfn(&m_stMonSpr[6],   480, 10, 150);			// _MT_MON_SPELL_A.
	SetSprDfn(&m_stMonSpr[7],   560, 10, 150);			// _MT_MON_SPELL_B.
	SetSprDfn(&m_stMonSpr[8],   640,  6, 150);			// _MT_MON_APPEAR.
	SetSprDfn(&m_stMonSpr[9],   720,  6, 150);			// _MT_MON_SPECIAL_MTN.
*/
	// 0. Monster Mtn -> _MT_MON_STAND.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 300);		
	default:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 300);		
		break;
	}

	// 1. Monster Mtn -> _MT_MON_WALK.
	SetSprDfn(&m_stMonSpr[1],    80,  6, /*120*/150);

	// 2. Monster Mtn -> _MT_MON_ATTACK_A.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case 12: case 99:	
		SetSprDfn(&m_stMonSpr[2],  160,  6, 120);	// ����, �����, ���ȷ���, ��, �ٿ��޵�.
		break;
	case 14: case 16: case 92:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 140);	// ���밳��, �峭����, �ٰ�.
		break;
	case  3: case  5: case  6: case  7: case  8: case  9: case 15: case 19: case 93: case 96: case 97: case 98:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);	// �籫, ��������, ���ڿ�, ġ������, ���ְ���, ��, ������, ���𰡸���, ����������, ���簳��, ǳ��, ������1.
		break;
	case  4: case 10: case 11: case 13: case 17: case 18: case 94:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 170);	// ������, �����, �����1, ��������, ��������, ����, ���.
		break;
	default:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 130);	
		break;
	}

	// 3. Monster Mtn -> _MT_MON_HITTED.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[3],  240,  2, 300);	
		break;
	case  116:										// ��.horse
	case  117:										
	case  118:										
		SetSprDfn(&m_stMonSpr[3],  240, 3, 160);		

	default:
		SetSprDfn(&m_stMonSpr[3],  240,  2, 300);	
		break;
	}

	// 4. Monster Mtn -> _MT_MON_DIE.
	switch ( wMonNum )
	{
	case  94:										// ���
		SetSprDfn(&m_stMonSpr[4],  320, 10, 160);		
		break;
	case  30:										// ����.
		SetSprDfn(&m_stMonSpr[4],  320, 4, 160);		
		break;
	case  104:										// ������.
		SetSprDfn(&m_stMonSpr[4],  320, 20, 160);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 165);
		break;
	}

	// 5. Monster Mtn -> _MT_MON_ATTACK_B.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[5],  400,  6, 150);
		break;
	default:
		SetSprDfn(&m_stMonSpr[5],  400,  6, 150);		
		break;
	}

	// 6. Monster Mtn -> _MT_MON_SPELL_A.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[6],  480, 10, 150);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[6],  480, 10, 150);		
		break;
	}

	// 7. Monster Mtn -> _MT_MON_SPELL_B.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[7],  560, 10, 150);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[7],  560, 10, 150);		
		break;
	}

	// 8. Monster Mtn -> _MT_MON_APPEAR.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[8],  640,  10, 150);		
		break;
	case 83:	// �ָ�����.
		SetSprDfn(&m_stMonSpr[8],  640,  6, 150);		
		break;
	case 84:	// �ָ�ȣ��.
		SetSprDfn(&m_stMonSpr[8],  640,  6, 150);		
		break;
	case 85:	// �ָ���.
		SetSprDfn(&m_stMonSpr[8],  640,  20, 150);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[8],  640,  10, 150);		
		break;
	}

	// 9. Monster Mtn -> _MT_MON_SPECIAL_MTN.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[9],  720,  6, 150);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[9],  880,  1, 150);		
		break;
	}
}



BOOL CSprite::SetWeaponOrder(CHAR* szFileName)
{
	HANDLE	hFile;

	hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;
		ReadFile(hFile, &m_bWOrder, _MAX_HERO_REALFRAME, &dwReadLen, NULL);
		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}
