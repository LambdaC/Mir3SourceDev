#ifndef _CACTOR_H
#define _CACTOR_H



/******************************************************************************************************************

	CActor Class

*******************************************************************************************************************/
#pragma pack(1)
typedef struct tagMESSAGEBODYWL
{
	LONG	lParam1;
	LONG	lParam2;
	LONG	nTag1;			// ������ ID.(SM_STRUCK�϶�).
	LONG	nTag2;
}MESSAGEBODYWL, *LPMESSAGEBODYWL;
typedef struct tagMESSAGEBODYW
{
	WORD	wParam1;
	WORD	wParam2;
	WORD	wTag1;			// ������ ID.(SM_STRUCK�϶�).
	WORD	wTag2;
}MESSAGEBODYW, *LPMESSAGEBODYW;

typedef struct tagCHARDESC
{
	LONG	nFeature;
	LONG	nStatus;
}CHARDESC, *LPCHARDESC;

typedef struct tagFEATURE
{
	BYTE	bGender; 
	BYTE	bWeapon;
	BYTE	bDress; 
	BYTE	bHair;
}FEATURE, *LPFEATURE;
#pragma pack(8)



class CActor
{
private:
public:
	DWORD				m_dwIdentity;					// ID Index From Server.
	CHAR				m_szName[64];					// ĳ���ͳ� ������ �̸�.
	CHAR				m_szGuildName[64];

	FEATURE				m_stFeature;					// ĳ������ ������ �������´�.
	BYTE				m_bActorImgIdx;					// ���� Actor�� ���� �̹�������ü�� ��ȣ.
	BYTE				m_bEffectImgIdx;				// ���� Actor�� ���� �̹�������ü�� ��ȣ.
	CWHWilImageData*	m_pxActorImage;					// �̹����� ���� �����͵�.
	RECT				m_rcActor;						// ���� ��ũ������Actor�� �簢 ����.
	RECT				m_rcTargetRgn;					// ���� Actor�� Ÿ�ٿ���.

	DWORD				m_dwFstFrame;					// ���� ������ ���� ������.
	DWORD				m_dwEndFrame;					// ���� ������ ������������.
	WORD				m_wDelay;						// ���� ���ۿ� ���� �����ð�.

	BYTE				m_bCurrMtn;						// ���� ����.
	BYTE				m_bCurrDir;						// ���� ����.
	BYTE				m_bMoveDir;						// ���� ����.
	DWORD				m_dwCurrFrame;					// ���� ������.
	WORD				m_wCurrDelay;					// ���� �����ð�.

	WORD				m_wOldPosX;						// ���� �ൿ�� �ֱ����� Ÿ��X��ǥ.
	WORD				m_wOldPosY;
	BYTE				m_bOldDir;						// ���� �ൿ�� �ֱ����� ����.
	WORD				m_wPosX;						// Ÿ�� X��ǥ.
	WORD				m_wPosY;						// Ÿ�� Y��ǥ.
	SHORT				m_shShiftPixelX;				// ���� �ڽ��� Ÿ�Ͽ��� X�ุŭ �̵��� �ȼ��� �Ÿ�.
	SHORT				m_shShiftPixelY;				// ���� �ڽ��� Ÿ�Ͽ��� Y�ุŭ �̵��� �ȼ��� �Ÿ�.
	SHORT				m_shShiftTileX;					// ���� �ڽ��� Ÿ�Ͽ��� X�ุŭ �̵��� Ÿ���� �Ÿ�.
	SHORT				m_shShiftTileY;					// ���� �ڽ��� Ÿ�Ͽ��� Y�ุŭ �̵��� Ÿ���� �Ÿ�.
	SHORT				m_shScrnPosX;					// �߽����� ������� ���� ȭ����� X��ǥ.
	SHORT				m_shScrnPosY;					// �߽����� ������� ���� ȭ����� Y��ǥ.
	BYTE				m_bMoveSpeed;					// �̵��ӵ�.

	CWHQueue			m_xPacketQueue;					// Actor�� ó���ؾߵ� �޽����� �����ϰ� �ִ� ť.
	BOOL				m_bMsgHurryCheck;				// �޽����� 2���̻� �׿��������� �������� 1�����Ӿ��� �ǳʶڴ�.

	BYTE				m_bBackStepFrame;
	BYTE				m_bBackStepFrameCnt;

	DWORD				m_dwCurrEffectFrame;			// ĳ���� Effect���� ������.
	DWORD				m_dwFstEffectFrame;				// ĳ���� Effectó�� ������.
	DWORD				m_dwEndEffectFrame;				// ĳ���� Effect������ ������.
	BYTE				m_bEffectFrame;
	BYTE				m_bEffectFrameCnt;
	BYTE				m_bLightRadius[2];				// ���� �ʺ�.
	BYTE				m_bLightColor [2][3];			// ���� ��.

	BOOL				m_bUseEffect;					// ����Ʈ�������� ���.
	BOOL				m_bUseSwordEffect;				// �˹�ȿ�� ���.

	BOOL				m_bWarMode;
	DWORD				m_dwWarModeTime;

	BYTE				m_bHPPercent;
	WORD				m_wMAXHP;
	WORD				m_wHP;
	WORD				m_wMP;
	BOOL				m_bOpenHealth;

	BYTE				m_bLightSize;					// Actor�ֺ��� ����ũ��.

	D3DVERTEX			m_avBoard[4];

	WORD				m_wABlendDelay;
	WORD				m_wABlendCurrDelay;
	BOOL				m_bABlendRev;

	BOOL				m_bReverse;

	INT					m_nState;
	WORD				m_wStateClr;

	DWORD				m_dwNameClr;

	BOOL				m_bIsDead;

	FEATURE				m_stHitter;

	BYTE				m_bAppearState;

	BYTE				m_bMoveNextFrmCnt;
	BOOL				m_bIsMoved;

	BOOL				m_bFstSoundPlayed;

	INT					m_nDividedChatLine;
	DWORD				m_wCurrChatDelay;
	CHAR				m_szChatMsg[MAX_PATH];			// ä�ø޽���.
	CHAR				m_szChatMsgArg[5][MAX_PATH];	// ä�ø޽����� 5���� ��Ʈ������ �����Ѱ�.

public:
//---------------------------------------------------------------------------------------------------------------//
// ������ �� �Ҹ���.
	CActor();
	~CActor();

	virtual VOID InitActor();
	virtual VOID DestroyActor();
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// ����.
	virtual BOOL Create(CImageHandler* pxImgHandler, FEATURE* pstFeature, BYTE bMtn, WORD bDir, WORD wPosX, WORD wPosY);
//---------------------------------------------------------------------------------------------------------------//

	BOOL LoadEffect(CImageHandler* pxImgHandler, WORD wEffectNum, BYTE bDir = 0);
	VOID DrawWithEffected(INT nx, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF, BOOL bFocused = FALSE, BYTE bOpa = 50, WORD wState = _STATE_NOTUSED);
//---------------------------------------------------------------------------------------------------------------//
// ������ ��������.
	BOOL	CheckFeatureValidate(FEATURE stFeature);
	BOOL	ChangeFeature(FEATURE stFeature);
	virtual BOOL SetMotionFrame(BYTE bMtn, BYTE bDir);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// ĳ���� �̵�.
	VOID SetMoving();
	VOID SetBackStepMoving();
	VOID SetMoved();
	WORD GetCharState();
//---------------------------------------------------------------------------------------------------------------//

	VOID ChatMsgAdd();
	VOID ShowMessage(INT nLoopTime);
	VOID StruckMsgReassign();
	
	virtual VOID PlayActSound();

//---------------------------------------------------------------------------------------------------------------//
// ���� ����.
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);

// ������ ��Ŷ��������.
	virtual VOID OnCharDescPacket(LPPACKETMSG lpPacketMsg);
	virtual VOID OnUserName(LPPACKETMSG lpPacketMsg);
	virtual VOID OnChangeNameClr(LPPACKETMSG lpPacketMsg);
	virtual VOID OnChangeLight(LPPACKETMSG lpPacketMsg);
	virtual VOID OnOpenHealth(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCloseHealth(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFeatureChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHealthSpellChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnWalk(LPPACKETMSG lpPacketMsg);
	virtual VOID OnTurn(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDigup(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDigDown(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDeath(LPPACKETMSG lpPacketMsg);
	virtual VOID OnBackStep(LPPACKETMSG lpPacketMsg);
	virtual VOID OnStruck(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFlyAxe(LPPACKETMSG lpPacketMsg);
	virtual VOID OnLighting(LPPACKETMSG lpPacketMsg);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// Rendering.
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE);
	virtual VOID DrawHPBar();
	virtual VOID DrawName();

	BOOL DrawEffect();
//---------------------------------------------------------------------------------------------------------------//
protected:
public:
};








/******************************************************************************************************************

	CNPC Class

*******************************************************************************************************************/
class CNPC : public CActor
{
private:
private:
public:
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnTurn(LPPACKETMSG lpPacketMsg);
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE);
};








/******************************************************************************************************************

	CHero Class

*******************************************************************************************************************/
#pragma pack(1)
typedef struct tagFEATUREEX
{
	BYTE		bHorse;
	BYTE		wHairColor;
	BYTE		wDressColor;
}FEATUREEX, *LPFEATUREEX;
#pragma pack(8)

class CHero : public CActor
{
private:
public:
	FEATUREEX			m_stFeatureEx;

	BYTE				m_bWeaponImgIdx;				// ���� Actor ���Ⱑ ���� �̹�������ü�� ��ȣ.
	BYTE				m_bHairImgIdx;					// ���� Actor �Ӹ��� ���� �̹�������ü�� ��ȣ.
	BYTE				m_bHorseImgIdx;					// ���� Actor ����   ���� �̹�������ü�� ��ȣ.

	BYTE				m_bYedoCnt;
	BYTE				m_bFireHitCnt;
	BOOL				m_bUseBanwol;
	BOOL				m_bUseErgum;

	RECT				m_rcHair;
	RECT				m_rcWeapon;
	RECT				m_rcHorse;

	CWHWilImageData*	m_pxHairImage;		
	CWHWilImageData*	m_pxWeaponImage;
	CWHWilImageData*	m_pxHorseImage;

	DWORD				m_dwCurrHairFrame;
	DWORD				m_dwCurrWeaponFrame;
	DWORD				m_dwCurrHorseFrame;

	BYTE				m_bShieldCurrFrm;
	WORD				m_wShieldCurrDelay;

	SHORT				m_shHitSpeed;

	BOOL				m_bIsMon;

	SHORT				m_shCurrMagicID;

protected:
public:
	CHero();
	~CHero();

	virtual VOID InitActor();
	virtual VOID DestroyActor();

	VOID ShowShield();
	VOID PlayMoveSound();

	virtual VOID PlayActSound();
	virtual BOOL ChangeFeature(FEATURE stFeature, FEATUREEX stFeatureEx);
	virtual BOOL Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, WORD wPosX, WORD wPosY, FEATURE* pstFeature, FEATUREEX* pstFeatureEx);
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);
	virtual VOID OnRun(LPPACKETMSG lpPacketMsg);
	virtual VOID OnRush(LPPACKETMSG lpPacketMsg);
	virtual VOID OnMagicFire(LPPACKETMSG lpPacketMsg);
	virtual VOID OnSpell(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCharDescPacket(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFeatureChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCharStatusChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnBackStep(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDeath(LPPACKETMSG lpPacketMsg);
	virtual VOID OnWalk(LPPACKETMSG lpPacketMsg);
	virtual VOID OnTurn(LPPACKETMSG lpPacketMsg);
	virtual VOID OnStruck(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnButch(LPPACKETMSG lpPacketMsg);
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE);
};










/******************************************************************************************************************

	CMyHero Class

*******************************************************************************************************************/
#pragma pack(1)
typedef struct tagACTORABILITY
{
    WORD	wAC;
    WORD	wMAC;
	WORD	wDC;
    WORD	wMC;
    WORD	wSC;
	WORD	wHP;
	WORD	wMP;
    WORD	wMaxHP;
    WORD	wMaxMP;
	WORD	wWeight;
 	BYTE	bExpCount;
	BYTE	bExpMaxCount;
	BYTE	bLevel;
	BYTE	bReserved1;
	BYTE	bWearWeight;
	BYTE	bMaxWearWeight;
    BYTE	bHandWeight;
    BYTE	bMaxHandWeight;

	DWORD	dwExp;
	DWORD	dwMaxExp;
	WORD	wMaxWeight;
}ACTORABILITY, *LPACTORABILITY;

typedef struct tagACTORSUBABILITY
{
	WORD wAntiMagic;		// ����ȸ��.
	BYTE bHitPoint;			// ��Ȯ.
	BYTE bSpeedPoint;		// ��ø.
	BYTE bAntiPoison;		// �ߵ�ȸ��.
	BYTE bPoisonRecover;	// �ߵ�ȸ��.
	BYTE bHealthRecover;	// ü��ȸ��.
	BYTE bSpellRecover;		// ����ȸ��.
}ACTORSUBABILITY, *LPACTORSUBABILITY;
#pragma pack(8)

class CMyHero : public CHero
{
private:
public:
//---------------------------------------------------------------------------------------------------------------//
//  ĳ���� ������ ����.
	DWORD			m_dwMotionLockTime;
	BOOL			m_bInputLock;				// ĳ���Ͱ� ���۵Ǹ� ��Էµ� ���� �ʴ´�.
	BOOL			m_bMotionLock;				// ĳ������ ������ ���õǸ� �������� ���۽����� ���������� ����۵� ���� �ʴ´�.
//---------------------------------------------------------------------------------------------------------------//

	CMapHandler*	m_pxMap;
	BOOL			m_bCanRun;
	BYTE			m_bAttackMode;
	ACTORABILITY    m_stAbility;
	ACTORSUBABILITY m_stSubAbility;
	BYTE		    m_bJob;
	UINT			m_nGlod;

	CWHQueue		m_xPriorPacketQueue;					// Actor�� ó���ؾߵ� �޽����� �����ϰ� �ִ� ť.

//---------------------------------------------------------------------------------------------------------------//
//  ĳ���� Delay���� ����.
	DWORD			m_dwLastHitTime;						// Į���� �������� ƽ ������.
	DWORD			m_dwLastSpellTime;						// ������ �������� ƽ ������.
	DWORD			m_dwLastMagicTime;						// ��ȭ�� �������� ƽ������.
	DWORD			m_dwLastStruckTime;						// �¾������� ƽ ������.
	DWORD			m_dwLastPKStruckTime;
	DWORD			m_dwLastRushTime;						// ���º� �������� ƽ������.
	DWORD			m_dwLastFireHitTime;					// ��ȭ�� �������� ƽ������.

	WORD			m_wMagicPKDelayTime;					// �������� ����� ������������ �г�ƼDelay.(�ȱ�� �ٱ⿡ ����ȴ�.)
	WORD			m_wMagicDelayTime;						// ���������� ���� ���������� ���������� Delay.
//---------------------------------------------------------------------------------------------------------------//

protected:
public:
	CMyHero();
	~CMyHero();

	virtual VOID InitActor();
	virtual VOID DestroyActor();

	VOID  SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID = NULL, BOOL bIsDead = FALSE, LPPOINT lpptPos = NULL, SHORT shSkill = -1);
	VOID  SetMapHandler(CMapHandler* pxMap);
	VOID  SetMagic(LPCLIENTMAGICRCD	pstMagic, BYTE bKeyNum, BYTE bDir, INT nTargetID, FEATURE stTargetFeature, POINT ptTargetPos);
	BOOL  SetOldPosition();
	BOOL  CheckMyPostion();
	VOID  AdjustMyPostion();
	BYTE  CalcDirection(INT nTargetTileX, INT nTargetTileY);
	POINT GetPosMouseToTile(INT nXPos, INT nYPos);

	virtual BOOL Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, WORD wPosX, WORD wPosY, FEATURE* pstFeature, FEATUREEX* pstFeatureEx);
	virtual VOID OnHealthSpellChanged(LPPACKETMSG lpPacketMsg);
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);
	virtual BOOL DrawActor(BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = FALSE, BOOL bDrawShadow = TRUE);

	__inline virtual BOOL ChangeFeature(FEATURE stFeature, FEATUREEX stFeatureEx)
	{
		if ( m_bIsMon )		
		{
			if ( CActor::ChangeFeature(stFeature) )					return TRUE;
		}
		else	
		{
			if ( CHero::ChangeFeature(stFeature, stFeatureEx) )		return TRUE;
		}

		return FALSE;
	}

//---------------------------------------------------------------------------------------------------------------//
//  ĳ���� Delay���� �Լ�.
	BOOL CanNextHit();									// ���� Į���Ҽ� �ֳ��� ����. ������ ���빫�Կ� ���� �޶�����.
	BOOL CanWalk();										// Delay�� ������� ĳ���Ͱ� �����ϼ� �ִ����� ����.
	BOOL CanRun();										// Delay�� ������� ĳ���Ͱ� �����ϼ� �ִ����� ����.
//---------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
//  ���� �Է��Լ�.
	BOOL OnLButtonDown(POINT ptMouse, INT nTargetID = -1, BOOL bIsDead = FALSE, POINT* lpptTargetPos = NULL);
	BOOL OnRButtonDown(POINT ptMouse);
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);
//---------------------------------------------------------------------------------------------------------------//
};








#endif // _CACTOR_H