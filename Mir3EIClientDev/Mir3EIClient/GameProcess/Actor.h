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
	LONG	nTag1;			// 때린놈 ID.(SM_STRUCK일때).
	LONG	nTag2;
}MESSAGEBODYWL, *LPMESSAGEBODYWL;
typedef struct tagMESSAGEBODYW
{
	WORD	wParam1;
	WORD	wParam2;
	WORD	wTag1;			// 때린놈 ID.(SM_STRUCK일때).
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
	CHAR				m_szName[64];					// 캐릭터나 몬스터의 이름.
	CHAR				m_szGuildName[64];

	FEATURE				m_stFeature;					// 캐릭터의 외형을 결정짓는다.
	BYTE				m_bActorImgIdx;					// 현재 Actor가 가질 이미지구조체의 번호.
	BYTE				m_bEffectImgIdx;				// 현재 Actor가 가질 이미지구조체의 번호.
	CWHWilImageData*	m_pxActorImage;					// 이미지를 얻어올 포인터들.
	RECT				m_rcActor;						// 현재 스크린상의Actor의 사각 영역.
	RECT				m_rcTargetRgn;					// 현재 Actor의 타겟영역.

	DWORD				m_dwFstFrame;					// 현재 동작의 시작 프레임.
	DWORD				m_dwEndFrame;					// 현재 동작의 마지막프레임.
	WORD				m_wDelay;						// 현재 동작에 대한 지연시간.

	BYTE				m_bCurrMtn;						// 현재 동작.
	BYTE				m_bCurrDir;						// 현재 방향.
	BYTE				m_bMoveDir;						// 현재 방향.
	DWORD				m_dwCurrFrame;					// 현재 프레임.
	WORD				m_wCurrDelay;					// 현재 지연시간.

	WORD				m_wOldPosX;						// 현재 행동이 있기전의 타일X좌표.
	WORD				m_wOldPosY;
	BYTE				m_bOldDir;						// 현재 행동이 있기전의 방향.
	WORD				m_wPosX;						// 타일 X좌표.
	WORD				m_wPosY;						// 타일 Y좌표.
	SHORT				m_shShiftPixelX;				// 현재 자신의 타일에서 X축만큼 이동한 픽셀의 거리.
	SHORT				m_shShiftPixelY;				// 현재 자신의 타일에서 Y축만큼 이동한 픽셀의 거리.
	SHORT				m_shShiftTileX;					// 현재 자신의 타일에서 X축만큼 이동한 타일의 거리.
	SHORT				m_shShiftTileY;					// 현재 자신의 타일에서 Y축만큼 이동한 타일의 거리.
	SHORT				m_shScrnPosX;					// 중심점을 고려하지 않은 화면상의 X좌표.
	SHORT				m_shScrnPosY;					// 중심점을 고려하지 않은 화면상의 Y좌표.
	BYTE				m_bMoveSpeed;					// 이동속도.

	CWHQueue			m_xPacketQueue;					// Actor가 처리해야될 메시지를 저장하고 있는 큐.
	BOOL				m_bMsgHurryCheck;				// 메시지가 2개이상 쌓여있을때는 프레임을 1프레임씩을 건너뛴다.

	BYTE				m_bBackStepFrame;
	BYTE				m_bBackStepFrameCnt;

	DWORD				m_dwCurrEffectFrame;			// 캐릭터 Effect현재 프레임.
	DWORD				m_dwFstEffectFrame;				// 캐릭터 Effect처음 프레임.
	DWORD				m_dwEndEffectFrame;				// 캐릭터 Effect마지막 프레임.
	BYTE				m_bEffectFrame;
	BYTE				m_bEffectFrameCnt;
	BYTE				m_bLightRadius[2];				// 광원 너비.
	BYTE				m_bLightColor [2][3];			// 광원 색.

	BOOL				m_bUseEffect;					// 이펙트프레임을 사용.
	BOOL				m_bUseSwordEffect;				// 검법효과 사용.

	BOOL				m_bWarMode;
	DWORD				m_dwWarModeTime;

	BYTE				m_bHPPercent;
	WORD				m_wMAXHP;
	WORD				m_wHP;
	WORD				m_wMP;
	BOOL				m_bOpenHealth;

	BYTE				m_bLightSize;					// Actor주변의 광원크기.

//	D3DVERTEX			m_avBoard[4];

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
	CHAR				m_szChatMsg[MAX_PATH];			// 채팅메시지.
	CHAR				m_szChatMsgArg[5][MAX_PATH];	// 채팅메시지를 5개의 스트링으로 구분한것.

public:
//---------------------------------------------------------------------------------------------------------------//
// 생성자 및 소멸자.
	CActor();
	~CActor();

	virtual VOID InitActor();
	virtual VOID DestroyActor();
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 생성.
	virtual BOOL Create(CImageHandler* pxImgHandler, FEATURE* pstFeature, BYTE bMtn, WORD bDir, WORD wPosX, WORD wPosY);
//---------------------------------------------------------------------------------------------------------------//

	BOOL LoadEffect(CImageHandler* pxImgHandler, WORD wEffectNum, BYTE bDir = 0);
	VOID DrawWithEffected(INT nx, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF, BOOL bFocused = FALSE, BYTE bOpa = 50, WORD wState = _STATE_NOTUSED);
//---------------------------------------------------------------------------------------------------------------//
// 프레임 설정관련.
	BOOL	CheckFeatureValidate(FEATURE stFeature);
	BOOL	ChangeFeature(FEATURE stFeature);
	virtual BOOL SetMotionFrame(BYTE bMtn, BYTE bDir);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 캐릭터 이동.
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
// 동작 진행.
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);

// 유형별 패킷상태적용.
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
//typedef struct tagFEATUREEX
//{
//	BYTE		bHorse;
//	BYTE		wHairColor;
//	BYTE		wDressColor;
//}FEATUREEX, *LPFEATUREEX;
//ydq 7-24 桿桿맣돨槻벎
typedef struct tagFEATUREEX
{
	BYTE		bHorse;
	WORD		wDressColor;
	WORD		wHairColor;
}FEATUREEX, *LPFEATUREEX;
#pragma pack(8)

class CHero : public CActor
{
private:
public:
	FEATUREEX			m_stFeatureEx;

	BYTE				m_bWeaponImgIdx;				// 현재 Actor 무기가 가질 이미지구조체의 번호.
	BYTE				m_bHairImgIdx;					// 현재 Actor 머리가 가질 이미지구조체의 번호.
	BYTE				m_bHorseImgIdx;					// 현재 Actor 말이   가질 이미지구조체의 번호.

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


/*
"ac" 렝徒제苟掘
"ac2" 렝徒제�龜�
"mac" 침렝苟掘
"mac2" 침렝�龜�
"dc" 膠잿묑샌제苟掘 
"dc2" 膠잿묑샌제�龜� 낚법죄255던瞳�爵球�샌角삔숑냥0
"mc" 침랬묑샌제苟掘
"mc2" 침랬묑샌제�龜�
"sc" 돛減苟掘
"sc2" 돛減�龜�
"needlevel" 矜狼된섬
"price" 송목


(9)膠틔角看干珂：
"ac2" 깊刻硫횅
"mac2" 깊刻츌쌥
"ac" 깊刻렝徒苟掘
"ac2" 깊刻렝徒�龜�
"mac" 깊刻침徒苟掘
"mac2" 깊刻침徒�龜�
*/







/******************************************************************************************************************

	CMyHero Class

*******************************************************************************************************************/
#pragma pack(1)
typedef struct tagACTORABILITY
{
	BYTE	bLevel;
    WORD	wAC;		//렝徒제
    WORD	wMAC;		//침렝
	WORD	wDC;		//膠잿묑샌제
    WORD	wMC;		//침랬묑샌제
    WORD	wSC;		//돛減
	WORD	wHP;
	WORD	wMP;
    WORD	wMaxHP;
    WORD	wMaxMP;
	DWORD	dwExp;
	DWORD	dwMaxExp;
	WORD	wWeight;
	WORD	wMaxWeight;
	BYTE	bWearWeight;
	BYTE	bMaxWearWeight;
    BYTE	bHandWeight;
    BYTE	bMaxHandWeight;

}ACTORABILITY, *LPACTORABILITY;

typedef struct tagACTORSUBABILITY
{
	WORD wAntiMagic;		// 마법회피.
	BYTE bHitPoint;			// 정확.
	BYTE bSpeedPoint;		// 민첩.
	BYTE bAntiPoison;		// 중독회피.
	BYTE bPoisonRecover;	// 중독회복.
	BYTE bHealthRecover;	// 체력회복.
	BYTE bSpellRecover;		// 마력회복.
}ACTORSUBABILITY, *LPACTORSUBABILITY;
#pragma pack(8)

class CMyHero : public CHero
{
public:

	//  傑땍
	DWORD			m_dwMotionLockTime;
	BOOL			m_bInputLock;				// 渴흙傑땍
	BOOL			m_bMotionLock;				// 傑땍頓땡,SetMotionState()속傑, UpdateMotionState()썩傑,冷앎角瞳侶寧뙈珂쇌코꼇捲壇柑깃句口

	CMapHandler*	m_pxMap;
	BOOL			m_bCanRun;
	BYTE			m_bAttackMode;
	ACTORABILITY    m_stAbility;
	ACTORSUBABILITY m_stSubAbility;
	BYTE		    m_bJob;
	UINT			m_nGlod;

	CWHQueue		m_xPriorPacketQueue;					// Actor가 처리해야될 메시지를 저장하고 있는 큐.

	//  땡鱗儺넨.
	DWORD			m_dwLastHitTime;						// 離쐤묑샌珂쇌
	DWORD			m_dwLastSpellTime;						// 離쐤賈痰륜麓돨珂쇌
	DWORD			m_dwLastMagicTime;						// 離쐤賈痰침랬돨珂쇌
	DWORD			m_dwLastStruckTime;						// 離쐤굳묑샌珂쇌
	DWORD			m_dwLastPKStruckTime;					// PK珂쇌,寮狼꼇횻�궐鱇考病殄쫏�
	DWORD			m_dwLastRushTime;						// 녑旒珂쇌(離쐤賈痰침랬녑旒珂쇌)
	DWORD			m_dwLastFireHitTime;					// 賈痰침랬삽헷돨珂쇌

	WORD			m_wMagicPKDelayTime;					// 침랬PK珂쇌
	WORD			m_wMagicDelayTime;						// 침랬儺넨

	BOOL			m_bActive;//角뤠捲壇痰빵句口

public:
	CMyHero();
	~CMyHero();

	virtual VOID InitActor();
	virtual VOID DestroyActor();

	VOID  SetMapHandler(CMapHandler* pxMap);
	
	//땡鱗변鑒,랙箇MyHero돨契浬,침랬츱즈 AutoTargeting(), OnLButtonDown()...딧痰
	virtual VOID  SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID = NULL, BOOL bIsDead = FALSE, LPPOINT lpptPos = NULL, SHORT shSkill = -1);
	//賈痰침랬,딧痰SetMotionState()供냥침랬땡鱗
	VOID  SetMagic(LPCLIENTMAGICRCD	pstMagic, BYTE bKeyNum, BYTE bDir, INT nTargetID, FEATURE stTargetFeature, POINT ptTargetPos);
	//藁쀼돕품寧몸榴檄, 쌈澗돕"+FAIL"契浬呵겨츱즈빈딧痰侶몸변鑒
	virtual BOOL  SetOldPosition();

	//쇱꿴MyHero角뤠瞳팁캥攣櫓,冷앎角쇱꿴角뤠矜狼盧땡뒈暠
	BOOL  CheckMyPostion();
	//盧땡뒈暠,宮뎠黨盧땡MyHero  ScrollMap()盧땡뒈暠돨튤盧좆윱盧땡뒈暠,렀鍋瞳寧몸Tile코.
	VOID  AdjustMyPostion();
	//셕炬렘蕨
	BYTE  CalcDirection(INT nTargetTileX, INT nTargetTileY);
	//쉥柑깃麟깃뻣냥뒈暠麟깃
	POINT GetPosMouseToTile(INT nXPos, INT nYPos);

	virtual BOOL Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, WORD wPosX, WORD wPosY, FEATURE* pstFeature, FEATUREEX* pstFeatureEx);
	virtual VOID OnHealthSpellChanged(LPPACKETMSG lpPacketMsg);

	//뇹잿榴檄맣긴
	virtual BOOL UpdatePacketState();
	//뫘劤頓땡榴檄,삥齡땡鱗뵨景槻,CheckMappedData()딧痰UpdateMotionState()삥齡뇜MyHero돨땡鱗,
	//RenderScene()딧痰UpdateMotionState()삥齡MyHero돨땡鱗, UpdateMotionState()딧痰UpdateMove()茄君盧땡땡鱗,뵨젯崎盧땡
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	//삥齡盧땡, 깻쇱꿴柑깃榴檄,茄君젯崎盧땡
	virtual BOOL UpdateMove(BOOL bIsMoveTime);

	virtual BOOL DrawActor(BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = FALSE, BOOL bDrawShadow = TRUE);

	//맣긴棍밖
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


	
	BOOL CanNextHit();						// 털뙤儺넨珂쇌윱털뙤角뤠옵鹿묑샌,뵨m_stAbility.bLevel冷밈뭄
	BOOL CanWalk();							//  if ( timeGetTime() - m_dwLastSpellTime < m_wMagicPKDelayTime )	return TRUE;
	BOOL CanRun();							// (timeGetTime() - m_dwLastPKStruckTime < 3000) || (timeGetTime() - m_dwLastSpellTime < m_wMagicPKDelayTime )

	
	//  柑깃句口.
	virtual BOOL OnLButtonDown(POINT ptMouse, INT nTargetID = -1, BOOL bIsDead = FALSE, POINT* lpptTargetPos = NULL);
	virtual BOOL OnRButtonDown(POINT ptMouse);
	virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);

	VOID DrawName();

	//뇹잿뜩훙慤숭警속돨변鑒뵨긴좆
	VOID	SetSocket(CClientSocket* pSocket) { m_pSocketClient = pSocket;}
	VOID	SetProc( CWHDefProcess* pProc ){ m_pGameProc = pProc; }//�阮첫蠻さ캑╂資�
protected:
	CClientSocket*	m_pSocketClient;//socket젯쌈
	CWHDefProcess*	m_pGameProc;//밑젬돨뇹잿잚
};








#endif // _CACTOR_H