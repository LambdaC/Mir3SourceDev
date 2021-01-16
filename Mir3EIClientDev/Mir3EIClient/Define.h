#ifndef _DEFINE_H
#define _DEFINE_H




/******************************************************************************************************************
	#1. File Names
*******************************************************************************************************************/
#define MESSAGE_DLL_1				".\\Mirmg.dll"
#define MIR2_PATCH_FILE_NAME		".\\Mir2Patch.exe"




/******************************************************************************************************************
	#1. Procedeure Define
*******************************************************************************************************************/
#define _LOGIN_PROC					0
#define _SVR_SEL_PROC				1
#define _CHAR_SEL_PROC				2
#define _GAME_PROC					3





/******************************************************************************************************************
	#1. Mouse Wheel Define
*******************************************************************************************************************/
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL				WM_MOUSELAST+1 
#endif





/******************************************************************************************************************
	#1. User Define Message
*******************************************************************************************************************/
#define _WM_USER_MSG_INPUTTED		WM_USER + 1005				// 에디트박스 입력메시지. 메시지가 커맨드일경우 wParam값은 TRUE로 세팅된다.
#define ID_SOCKCLIENT_EVENT_MSG		WM_USER + 1100				// SOCKET事件
#define ID_SOCKCLIENT_EVENT_MSG_1	ID_SOCKCLIENT_EVENT_MSG + 1	


/******************************************************************************************************************
	#1. Image Define Message
*******************************************************************************************************************/
#define _IMAGE_TILES				0
#define _IMAGE_TILES30				1
#define _IMAGE_TILES5				2
#define _IMAGE_SMTILES				3
#define _IMAGE_HOUSES				4
#define _IMAGE_CLIFFS				5
#define _IMAGE_DUNGEONS				6
#define _IMAGE_INNERS				7
#define _IMAGE_FUNITURES			8
#define _IMAGE_WALLS				9
#define _IMAGE_SMOBJECTS			10
#define _IMAGE_ANIMATIONS			11
#define _IMAGE_OBJECT1				12
#define _IMAGE_OBJECT2				13

#define _IMAGE_INTER				70
#define _IMAGE_M_HUMAN				71
#define _IMAGE_M_WEAPON1			72
#define _IMAGE_M_WEAPON2			73
#define _IMAGE_M_WEAPON3			74
#define _IMAGE_M_WEAPON4			75
#define _IMAGE_M_WEAPON5			76
#define _IMAGE_WM_HUMAN				77
#define _IMAGE_WM_WEAPON1			78
#define _IMAGE_WM_WEAPON2			79
#define _IMAGE_WM_WEAPON3			80
#define _IMAGE_WM_WEAPON4			81
#define _IMAGE_WM_WEAPON5			82

#define _IMAGE_M_HAIR				133
#define _IMAGE_M_HELMET1			134
#define _IMAGE_WM_HAIR				135
#define _IMAGE_WM_HELMET1			136
#define _IMAGE_M_HELMET2			146
#define _IMAGE_WM_HELMET2			147

#define _IMAGE_MAGIC				83
#define _IMAGE_ITEM_INVENTORY		84
#define _IMAGE_ITEM_EQUIP			85
#define _IMAGE_ITEM_GROUND			86
#define _IMAGE_MICON				87
#define _IMAGE_PROGUSE				88
#define _IMAGE_HORSE				89

#define _IMAGE_MONSTER1				90
#define _IMAGE_MONSTER2				91
#define _IMAGE_MONSTER3				92
#define _IMAGE_MONSTER4				93
#define _IMAGE_MONSTER5				94
#define _IMAGE_MONSTER6				95
#define _IMAGE_MONSTER7				96
#define _IMAGE_MONSTER8				97
#define _IMAGE_MONSTER9				98
#define _IMAGE_MONSTER10			99
#define _IMAGE_MONSTER11			100
#define _IMAGE_MONSTER12			101
#define _IMAGE_MONSTER13			102
#define _IMAGE_MONSTER14			103
#define _IMAGE_MONSTER15			104
#define _IMAGE_MONSTER16			105
#define _IMAGE_MONSTER17			106
#define _IMAGE_MONSTER18			107
#define _IMAGE_MONSTER19			108
#define _IMAGE_MONSTER20			109

#define _IMAGE_SMONSTER1			110
#define _IMAGE_SMONSTER2			111
#define _IMAGE_SMONSTER3			112
#define _IMAGE_SMONSTER4			113
#define _IMAGE_SMONSTER5			114
#define _IMAGE_SMONSTER6			115
#define _IMAGE_SMONSTER7			116	
#define _IMAGE_SMONSTER8			117
#define _IMAGE_SMONSTER9			118
#define _IMAGE_SMONSTER10			119	
#define _IMAGE_SMONSTER11			120
#define _IMAGE_SMONSTER12			121
#define _IMAGE_SMONSTER13			122
#define _IMAGE_SMONSTER14			123	
#define _IMAGE_SMONSTER15			124
#define _IMAGE_SMONSTER16			125
#define _IMAGE_SMONSTER17			126
#define _IMAGE_SMONSTER18			127	
#define _IMAGE_SMONSTER19			128
#define _IMAGE_SMONSTER20			129

#define _IMAGE_NPC					130
#define _IMAGE_MONMAGIC				131
#define _MAX_MONSTER_IMAGE			132

//死亡的怪物?
#define _IMAGE_D_MONSTER1			137
#define _IMAGE_D_SMONSTER1			138
#define _IMAGE_MAGICEX				139
#define _IMAGE_MONMAGICEX			140
#define _IMAGE_STOREITEM			141
#define _IMAGE_MONMAGICEX2			142
#define _IMAGE_MONSTER54			143
#define _IMAGE_FLAG					144
#define _IMAGE_MONMAGICEX3			145
#define _IMAGE_MonMagicEx4			148
#define _IMAGE_MAGICEX2				149




#define _IMAGE_INTEREX				70	//已经没有这个文件了，用gameinter代替


#define _MAX_IMAGE					150

#define _TEXTR_FILE_MAGIC			0
#define _TEXTR_FILE_MONMAGIC		1
#define _TEXTR_FILE_MAP				2
#define _TEXTR_FILE_INTER			3

#define _MAX_TEXTR_FILE				4




/******************************************************************************************************************
	#1. Item Define
*******************************************************************************************************************/
#define _ITEM_TYPE_INVENTORY		0
#define _ITEM_TYPE_EQUIP			1
#define _ITEM_TYPE_GROUND			2

#define _INVENTORY_CELL_WIDTH		38
#define _INVENTORY_CELL_HEIGHT		38

#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // 투과색.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // 검정색.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // 흰색.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // 빨강.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // 녹색.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // 푸른색
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // 노랑색.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // 주황색

#define _USER_NAMECLR1				255	//RGB(255, 255, 255); 흰색
#define _USER_NAMECLR2				251	//RGB(255, 255,   0); 노란색
#define _USER_NAMECLR3				249	//RGB(255,   0,   0); 빨간색
#define _USER_NAMECLR4				125	//RGB(255,   0,   0); ??색(결계안 몬스터색)
#define _USER_NAMECLR5				47	//RGB(165,  99,  57); 갈색
#define _USER_NAMECLR6				180	//RGB(  0,   0, 255); 푸른색
#define _USER_NAMECLR7				69	//RGB(239, 107,   0); 주황색
#define _USER_NAMECLR8				221	//RGB(  0, 148,   0); 녹색
#define _USER_NAMECLR9				254	//RGB(  0, 255, 255); 색
#define _USER_NAMECLR10				147	//RGB(140, 214, 239); 색
#define _USER_NAMECLR11				154	//RGB( 57, 181, 239); 색
#define _USER_NAMECLR12				229	//RGB(119, 136, 255); 색
#define _USER_NAMECLR13				168	//RGB(  0, 123, 222); 색
#define _USER_NAMECLR14				252	//RGB(  0,   0, 255); 색

#define _CLR_RED					RGB(255, 0, 0)
#define _CLR_BLACK					RGB(0, 0, 0)


/******************************************************************************************************************
	#1. Actor Define
*******************************************************************************************************************/
#define _GENDER_MAN					0
#define _GENDER_WOMAN				1
#define _GENDER_NPC					5
#define _GENDER_MON					3
#define _MAX_GENDER					4

#define _TARGETRGN_GAPX				10
#define _TARGETRGN_GAPY				8

#define _MAX_HERO_KIND				10
#define _MAX_MON_KIND				255
#define _MAX_NPC_KIND				29

#define _MAX_DIRECTION				8
#define _DIRECTION_LIST_1			0
#define _DIRECTION_LIST_2			1
#define _DIRECTION_LIST_3			2
#define _DIRECTION_LIST_4			3
#define _DIRECTION_LIST_5			4
#define _DIRECTION_LIST_6			5	 
#define _DIRECTION_LIST_7			6
#define _DIRECTION_LIST_8			7	

#define _DEFAULT_SPELLFRAME			10
#define _DEFAULT_DELAYTIME			300

#define _HAIR_NONE					0
#define _MAX_HAIR					30

#define _WEAPON_NONE				0		
#define _MAX_WEAPON					32		

#define _HORSE_NONE					0
#define _MAX_HORSE					4

#define	_MAX_WEAPON_MTN				25
#define	_MAX_WEAPON_FRAME			3000

#define	_START_HORSE_FRAME			2320
#define	_START_HORSE_MTN			29
#define	_MAX_HORSE_FRAME			400

#define _MY_CENTER_XPOS				400
#define _MY_CENTER_YPOS	    		243

#define _MAX_CHAT_LINE				5
#define _CHAT_WIDTH					250
//#define _GAPX_TILE_CHAR_MAP		11
//#define _GAPY_TILE_CHAR_MAP		11 
#define _GAPX_TILE_CHAR_MAP			12
#define _GAPY_TILE_CHAR_MAP			12 
#define _CHAR_CENTER_XPOS			400
#define _CHAR_CENTER_YPOS	    	243

#define _SPEED_WALK					1
#define _SPEED_RUN					2
#define _SPEED_HORSERUN				3

#define _MOTION_LOCKTIME			8000
#define _WARMODE_TIME				5000

#define _JOB_DOSA					2
#define _JOB_SULSA					1
#define _JOB_JUNSA					0

#define _STATE_RED					64690
#define _STATE_GREEN				2016
#define _STATE_BLUE					38079//31
#define _STATE_YELLOW				65504
#define _STATE_FUCHSIA				64511
#define _STATE_GRAY					0
#define _STATE_ABLEND				1
#define _STATE_SHIELDUSE			2
#define _STATE_NOTUSED				0XFFFF

#define _RUN_MINHEALTH				10

#define _DIG_NORMAL					0
#define _DIG_UP						1
#define _DIG_DOWN					2
#define _DIG_DOWNDEL				3


/******************************************************************************************************************
	#1. Sprite Define
*******************************************************************************************************************/
// Hero의 동작 정의.(게임내의 모든 동작을 정의한다.)

#define _MAX_HERO_MTN				33			// 최대 동작갯수.
#define _MAX_HERO_FRAME				3000		// 다음 Hero로 넘어가는 최대 프레임 갯수.
#define	_MAX_HERO_REALFRAME			2640

#define _MT_STAND					0			// 유휴동작.
#define _MT_ARROWATTACK				1			// 활공격.
#define _MT_SPELL1					2			// 마법 시전1.
#define _MT_SPELL2					3			// 마법 공격 시전2.
#define _MT_HOLD					4			// 견디기.
#define _MT_PUSHBACK				5			// 뒤로 밀려나기.
#define _MT_PUSHBACKFLY				6			// 뒤로 날라서 밀려나기.
#define _MT_ATTACKMODE				7			// 전투모드.
#define _MT_CUT						8			// 고기 썰기.
#define _MT_ONEVSWING				9			// 한손 종베기.(동작 9번부터 14번까지에서 무기의 종류에 따라 동작이 정해진다.)
#define _MT_TWOVSWING				10			// 두손 종베기.
#define _MT_ONEHSWING				11			// 한손 횡베기.
#define _MT_TWOHSWING				12			// 두손 횡베기.	
#define _MT_SPEARVSWING				13			// 창 종베기.
#define _MT_SPEARHSWING				14			// 창 횡베기.
#define _MT_HITTED					15			// 맞기.
#define _MT_WHEELWIND				16			// 돌면서 베기.
#define _MT_RANDSWING				17			// 마구 베기.
#define _MT_BACKDROPKICK			18			// 뒤돌아 차기.
#define _MT_DIE						19			// 죽기.
#define _MT_SPECIALDIE				20			// 튀어올라 죽기.
#define _MT_WALK					21			// 걷기.
#define _MT_RUN						22			// 달리기.
#define _MT_MOODEPO					23			// 무태보 뛰기.
#define _MT_ROLL					24			// 구르기.
#define _MT_FISHSTAND				25			// 낚시모드 유휴.
#define _MT_FISHHAND				26			// 낚시모드.
#define _MT_FISHTHROW				27			// 낚시줄 던지기.
#define _MT_FISHPULL				28			// 낚시줄 당기기.
#define _MT_HORSESTAND				29			// 승마모드 유휴.
#define _MT_HORSEWALK				30			// 승마모드 걷기.
#define _MT_HORSERUN				31			// 승마모드 달리기.
#define _MT_HORSEHIT				32			// 승마모드 맞기.

// Monster의 동작 정의.(게임내의 모든 동작을 정의한다.)
#define _MAX_MON_MTN				10			// 최대 동작갯수.
#define _MAX_MON_FRAME				1000		// 다음 Mon로 넘어가는 최대 프레임 갯수.

#define _MT_MON_STAND				0			// 유휴동작.
#define _MT_MON_WALK				1			// 걷기동작.
#define _MT_MON_ATTACK_A			2			// 일반공격동작1.
#define _MT_MON_HITTED				3			// 맞기동작.
#define _MT_MON_DIE					4			// 죽기동작.
#define _MT_MON_ATTACK_B			5			// 일반공격동작2.
#define _MT_MON_SPELL_A				6			// 마법공격동작1.
#define _MT_MON_SPELL_B				7			// 마법공격동작2.
#define _MT_MON_APPEAR				8			// 나타나기동작.
#define _MT_MON_SPECIAL_MTN			9			// 특수동작1.


// NPC의 동작 정의.(게임내의 모든 동작을 정의한다.)
// NPC 관련정의.
#define _MAX_NPC_MTN				3			// 최대 동작갯수.
#define _MAX_NPC_FRAME				100			// 다음 NPC로 넘어가는 최대 프레임 갯수.

#define _MT_NPC_STAND				0			// 유휴동작.
#define _MT_NPC_ACT01				1			// 특수동작1.
#define _MT_NPC_ACT02				2			// 특수동작2.

// 기도.							0			
// 무기대장장이.					1			
// 방어구대장장이.					2			
// 여관종업원.						3			
// 카운터.							4			
// 경매안내자.						5			
// 고급사서.						6			
// 도서관경비.						7			
// 사서.							8			
// 접수처.							9			
// 약초할아버지.					10			
// 의류상.							11			
// 주점NPC.							12			
// 사막전사.						13			
// 대장간종업원.					14			
// 도박장책임자.					15			
// 옛날대장장이.					16			
// 옛날약방노인.					17			
// 옛날책방노인.					18			
// 잡상인.							19			
// 잡화상.							20			
// 잡화상.							21			
// 잡화상.							22			
// 점쟁이.							23			
// 포목상.							24			
// 여관아줌마.						25
// 음식점할배.						26
// 정육점주인.						27			
// 행정관.							28			





// 마법효과관련정의.
#define _MAX_EFFECT					33
#define _MAX_MAGIC					52
#define _MAX_EXPLOSION				8





/******************************************************************************************************************
	#1. Chat Popup Wnd
*******************************************************************************************************************/
#define _MAX_CHATLINE_POPUP			19





/******************************************************************************************************************
	#1. Button Wnd
*******************************************************************************************************************/
#define _BTN_STATE_NORMAL			0
#define _BTN_STATE_FOCUS			1
#define _BTN_STATE_CLICK			2

#define _BTN_TYPE_NOFOCUS			0
#define _BTN_TYPE_FOCUS				1





/******************************************************************************************************************
	#1. Game Procedure
*******************************************************************************************************************/
#define _CLIP_WIDTH					800
#define _CLIP_HEIGHT				492
#define _TIMER_ID					1

#define _ET_DIGOUTZOMBI				1  //좀비가 땅파고 나온 흔적
#define _ET_MINE					2  //광석이 매장되어 있음
#define _ET_PILESTONES				3  //돌무더기
#define _ET_HOLYCURTAIN				4  //결계
#define _ET_FIRE					5
#define _ET_SCULPEICE				6  //주마왕의 돌깨진 조각

#define _MAX_CELL_OBJ				10

// Day Bright.
#define _DAYSTATE_DUSK				0  // 새벽.
#define _DAYSTATE_DAY				1  // 낮.
#define _DAYSTATE_DAWN				2  // 저녁.
#define _DAYSTATE_NIGHT				3  // 밤.

// Fog Bright.
#define _FOGSTATE_DAY				0  // 낮.
#define _FOGSTATE_NIGHT				1  // 밤.
#define _FOGSTATE_DAWN				2  // 새벽, 저녁.





/******************************************************************************************************************
	#1. Interface
*******************************************************************************************************************/
#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // 투과색.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // 검정색.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // 흰색.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // 빨강.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // 녹색.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // 푸른색
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // 노랑색.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // 주황색

#define _INPUT_EDITWND_XPOS			184
#define _INPUT_EDITWND_YPOS			575
#define _INPUT_EDITWND_WIDTH		345
#define _INPUT_EDITWND_HEIGHT		17

// 메인인터페이스에서 쓰일 윈도우 아이디.
#define _WND_ID_INVENTORY			0			//가방윈도우.
#define _WND_ID_STATUS				1			//캐릭터 정보 보기윈도우(3개).
#define _WND_ID_STORE				2			//상점윈도우.
#define _WND_ID_EXCHANGE			3			//교환윈도우.
#define _WND_ID_GUILD				4			//문원윈도우.
#define _WND_ID_GUILDMASTER			5			//문주윈도우.
#define _WND_ID_GROUP				6			//그룹윈도우.
#define _WND_ID_GROUPPOP			7			//
#define _WND_ID_CHATPOP				8			//
#define _WND_ID_NPCCHAT				9		
#define _WND_ID_MESSAGEBOX			10			// MessageBox
#define _WND_ID_QUEST				11			// 
#define _WND_ID_OPTION				12			// 
#define _WND_ID_HORSE				13			// 

// 메인 인터페이스에서 쓰일 윈도우의 이미지 인덱스.
#define _WNDIMGIDX_MAIN				1160		//50		寮썹충
#define _WNDIMGIDX_INVENTORY	    1220		//관범눗왯
#define _WNDIMGIDX_ITEMSET		    1280		//榴檄（실�ィ㈃걀�
#define _WNDIMGIDX_SKILLSET			1620		//skill
#define _WNDIMGIDX_STATUS			1280		//Status
#define _WNDIMGIDX_CHARINFO			1288		//character info,실�バ턴∀П朝�
#define _WNDIMGIDX_STORE			1260			//store
#define _WNDIMGIDX_EXCHANGE			1390		//슥弄
#define _WNDIMGIDX_GUILDMASTER		600			//契삔庫커？.
#define _WNDIMGIDX_GUILD			169			//契삔.
#define _WNDIMGIDX_GROUP			1360			//Group.
#define _WNDIMGIDX_GROUPPOP			145			//그룹입력창.
#define _WNDIMGIDX_CHATPOP			1162			//좔莖눗왯
#define _WNDIMGINDX_MSGBOX1			254
#define _WNDIMGINDX_MSGBOX2			255
#define _WNDIMGIDX_NPCCHAT			1350		//NPC뚤뺐눗왯
#define _WNDIMGIDX_QUEST			700			//퀘스트창.
#define _WNDIMGIDX_OPTION			750			//옵션창.
#define _WNDIMGIDX_HORSE			1400			//쯩.
#define _IDX_IMG_NOTICEBOX			1250			//무獨눗왯 ydq

#define _IDX_IMG_BLANK				1490		//왕겜

#define _IMGIDX_BELT				1210		//belt

// 메인인터페이스에서 쓰일 버튼 아이디.
#define _BTN_ID_CHANGE				0
#define _BTN_ID_MINIMAP				1
#define _BTN_ID_MUGONG				2
#define _BTN_ID_EXIT				3
#define _BTN_ID_LOGOUT				4
#define _BTN_ID_GROUP				5
#define _BTN_ID_GUILD				6
#define _BTN_ID_BELT				7
#define _BTN_ID_MAGIC				8
#define _BTN_ID_POPUP				9
#define _BTN_ID_QUEST				10
#define _BTN_ID_OPTION				11
#define _BTN_ID_HELP				12
#define _BTN_ID_HORSE				13
#define _BTN_ID_BAG					14
#define _BTN_ID_CHAR				15

#define _MAX_INTER_BTN				16
#define _MAX_CHATLINE				5

#define _MAX_SAVECHATLINE			50

#define _BELT_STATE_STAY			0
#define _BELT_STATE_UP				1
#define _BELT_STATE_DOWN			2











/******************************************************************************************************************
	#1. Inventory Window
*******************************************************************************************************************/
#define _INVEN_MAX_CELL				65
#define _BELT_MAX_CELL				6
#define _INVEN_CELL_XCNT			6
#define _INVEN_CELL_YCNT			8
#define _INVEN_MAX_CELL_YCNT		12
#define _INVEN_CELL_XSTART			19
#define _INVEN_CELL_YSTART			60

#define _BELT_CELL_XGAP				42
#define _BELT_CELL_XSTART			18
#define _BELT_CELL_YSTART			14

#define _MAX_INVEN_BTN				1		//2
#define _MAX_INVEN_ITEM				60		//2E
#define _MAX_BELT_ITEM				6

#define _BTN_ID_INVENCLOSE			0
#define _BTN_ID_INVENSCRLUP			1
#define _BTN_ID_INVENSCRLDOWN		2





/******************************************************************************************************************
	#1. Light fog
*******************************************************************************************************************/
#define NUM_CNTX_LIGHTTILE			17
#define NUM_CNTY_LIGHTTILE			21
#define TILE_START_XPOS				-8
#define TILE_START_YPOS				-29

#define TILE_WIDTH					48
#define TILE_HEIGHT					32

#define NUM_LIGHTTILE_INDICES		(NUM_CNTX_LIGHTTILE)*(NUM_CNTY_LIGHTTILE)*3*2
#define NUM_LIGHTTILE_VERTICES		(NUM_CNTX_LIGHTTILE+1)*(NUM_CNTY_LIGHTTILE+1)



/******************************************************************************************************************
	#1. Magic
*******************************************************************************************************************/
#define _MAGIC_ACTIVE				0			// 마법활성상태.
#define _LIGHT_ACTIVE				1			// 마법광원활성상태.
#define _MAGIC_FINISH				2			// 마법소멸.

#define _SKILL_FIREBALL				1			// 화염장.
#define _SKILL_HEALLING				2			// 회복술.
#define _SKILL_ONESWORD				3			// 외수.
#define _SKILL_ILKWANG				4			// 일광.
#define _SKILL_FIREBALL2			5			// 금강화염장.
#define _SKILL_AMYOUNSUL			6			// 암연술.
#define _SKILL_YEDO					7			// 예도.
#define _SKILL_FIREWIND				8			// 화염풍.
#define _SKILL_FIRE					9			// 염사장.
#define _SKILL_SHOOTLIGHTEN			10			// 뢰인장.
#define _SKILL_LIGHTENING			11			// 강격.
#define _SKILL_ERGUM				12			// 어검술.
#define _SKILL_FIRECHARM			13			// 폭살계.
#define _SKILL_HANGMAJINBUB			14			// 항마진법.
#define _SKILL_DEJIWONHO			15			// 대지원호.
#define _SKILL_HOLYSHIELD			16			// 결계.
#define _SKILL_SKELLETON			17			// 백골소환술.
#define _SKILL_CLOAK				18			// 은신.
#define _SKILL_BIGCLOAK				19			// 대은신.
#define _SKILL_TAMMING				20			// 뢰혼격.
#define _SKILL_SPACEMOVE			21			// 아공행법.
#define _SKILL_EARTHFIRE			22			// 지염술.
#define _SKILL_FIREBOOM				23			// 폭열파.
#define _SKILL_LIGHTFLOWER			24			// 뢰설화.
#define _SKILL_BANWOL				25			// 반월.
#define _SKILL_FIRESWORD			26			// 염화결.
#define _SKILL_MOOTEBO				27			// 무태보.
#define _SKILL_SHOWHP				28			// 탐기파연.
#define _SKILL_BIGHEALLING			29			// 대회복.
#define _SKILL_SINSU				30			// 신수소환.
#define _SKILL_SHIELD				31			// 주술의막.
#define _SKILL_KILLUNDEAD			32			// 사자윤회.
#define _SKILL_SNOWWIND				33			// 빙설풍.

#define _SKILL_JUMPSHOT				33			// 점프해서치기 검기.
#define _SKILL_RANDSWING			34			// 마구 휘두르기.
#define _SKILL_SPACEMOVE2			35			// 아공행법2.
#define _SKILL_SPACEMOVE3			36			// 아공행법3.

#define _MONMAGIC_KEPAL				100			// 전격공격.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_EXPLODE			101			// 폭발마법.(돌골렘죽을때, 론공격시)
#define _MONMAGIC_BLACK1			102			// 흑마법사. (마법(시전))
#define _MONMAGIC_BLACK2			103			// 흑마법사. (마법(마법))
#define _MONMAGIC_DIE				104			// 흑마법사, 경갑옷기사, 홍마법사, 신기선보스변신전 죽음.(효과)
#define _MONMAGIC_ANTHEAL			105			// 치유개미힐링(발사마법, 폭발효과.)
#define _MONMAGIC_GREATANT			106			// 거대개미.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_MAGENUMA			108			// 결계.
#define _MONMAGIC_ANT				109			// 병정개미공격.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_WORKANT			110			// 일개미공격.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_RED1				111			// 홍마법사. (마법(시전))
#define _MONMAGIC_RED2				112			// 홍마법사. (마법(마법))
#define _MONMAGIC_COWGHOST			113			// 우면귀. (마법)
#define _MONMAGIC_SINSU				114			// 신수. (마법)
#define _MONMAGIC_ZOMBIE			115			// 좀비. (마법)
#define _MONMAGIC_JUMAWANG			116			// 주마왕. (마법)
#define _MONMAGIC_CHIM				117
#define _MONMAGIC_ARROW				118
#define _MONMAGIC_MAARROW			119
#define _MONMAGIC_DUALAXE			120
#define _MONMAGIC_COWFLAME			121
#define _MONMAGIC_BIGGINE_ATT		122
#define _MONMAGIC_BIGGINE_CHAR		123
#define _MONMAGIC_SANDFISH			124
#define _MONMAGIC_BAODIE			125
#define _MONMAGIC_SINGI_DIE			126
#define _MONMAGIC_HUSU_DIE			127
#define _MONMAGIC_ZOMBIE_DIE		128
#define _MONMAGIC_SSEGI				129
#define _MONMAGIC_NUMAGUMGI			130
#define _MONMAGIC_EXPLODE1			131

#define _BLEND_NORMAL				0			// 일반적인그리기.(알파값이 적용될수있다.)
#define _BLEND_LIGHT				1			// 섬광효과형태의 블렌딩.
#define _BLEND_LIGHTINV				2	
#define _BLEND_INVNORMAL			3
#define _BLEND_INVLIGHT				4
#define _BLEND_INVLIGHTINV			5




/******************************************************************************************************************
	#1. Map Handler
*******************************************************************************************************************/

#define _BASETILE_WIDTH				96				// 기본타일 넓이.
#define _BASETILE_HEIGHT			64
	
#define _CELL_WIDTH					48				// 기본셀 넓이, 기본타일은 4개의 셀로 이루어지고 정보는 셀단위로 저장된다.
#define _CELL_HEIGHT				32

#define _VIEW_CELL_X_COUNT			24				// 뷰영역에 필요한 X축의 셀단위 개수.((짜투리 타일제외)좌와위로 3셀, 우와아래로 2셀씩의 여유를 둔다.)
#define _VIEW_CELL_Y_COUNT			24			
#define _VIEW_CELL_Y_COUNT_FOR_OBJ	44

#define _VIEW_CELL_X_START			-200			// 뷰영역을 그리기 위한 시작 셀 X좌표.
#define _VIEW_CELL_Y_START			-157
#define _MAX_TILE_FILE				69

// 포그색 관련 속성.
#define _FOG_COLOR_TYPE0			RGB(0, 0, 0);
#define _FOG_COLOR_TYPE1			RGB(100, 10, 10);
#define _FOG_COLOR_TYPE2			RGB(10, 255, 10);
#define _FOG_COLOR_TYPE3			RGB(10, 10, 255);

// 속성 관련 정의.
#define _CAN_WALK					0
#define _CAN_NOTWALK	 			1
#define _CAN_FLY					0
#define _CAN_NOTFLY					1

// 라이트 크기 관련 정의.
#define _LIGHT_SIZE_TYPE0			3
#define _LIGHT_SIZE_TYPE1			4
#define _LIGHT_SIZE_TYPE2			5
#define _LIGHT_SIZE_TYPE3			6

// 라이트 색 관련 정의.
#define _LIGHT_COLOR_TYPE0			RGB(255, 0, 0);
#define _LIGHT_COLOR_TYPE1			RGB(0, 255, 0);
#define _LIGHT_COLOR_TYPE2			RGB(0, 0, 255);
#define _LIGHT_COLOR_TYPE3			RGB(255, 0, 255);

// 문관련 정의.
#define _DOOR_ISCLOSED				0
#define _DOOR_ISOPEN				1

#define _TILE_ANI_DELAY_1			150
#define _TILE_ANI_DELAY_2			200
#define _TILE_ANI_DELAY_3			250
#define _TILE_ANI_DELAY_4			300
#define _TILE_ANI_DELAY_5			350
#define _TILE_ANI_DELAY_6			400
#define _TILE_ANI_DELAY_7			420
#define _TILE_ANI_DELAY_8			450






/******************************************************************************************************************
	#1. Status Window
*******************************************************************************************************************/
#define _TYPE_EQUIP					0
#define _TYPE_STATUS				1
#define _TYPE_SETMAGIC				2

#define _EQUIP_MAX_CELL				11
#define _MAGIC_MAX_CELL				5
#define _MAGIC_MAX_KEY				8

#define _MAX_TYPE_WND				3

#define _MAX_STAUTS_BTN				3

#define _BTN_ID_STATUSCLOSE			0
#define _BTN_ID_STATUS				1
#define _BTN_ID_STATUSMAGIC			2

#define _BTN_ID_STATUS_X			187
#define _BTN_ID_STATUS_Y			266
#define _BTN_ID_STATUSMAGIC_X		224
#define _BTN_ID_STATUSMAGIC_Y		98

#define _EQUIP_CHAR_X				100
#define _EQUIP_CHAR_Y				200

#define _U_DRESS					0 
#define _U_WEAPON					1 
#define _U_RIGHTHAND				2 
#define _U_NECKLACE					3 
#define _U_HELMET					4 
#define _U_ARMRINGL					5 
#define _U_ARMRINGR					6                
#define _U_RINGL					7 
#define _U_RINGR					8 
#define _U_CHARM					9
#define _U_SHOES					10
#define _U_UNEQUIP					100

#define _MAX_MAGIC_SKILL			32




/******************************************************************************************************************
	#1. Store Window
*******************************************************************************************************************/
#define _STORE_STATE_SELL			0
#define _STORE_STATE_BUY			1






/******************************************************************************************************************
	#1. Client To Server Message
*******************************************************************************************************************/
#define CM_QUERYUSERNAME			80
#define CM_QUERYBAGITEMS			81
#define CM_DROPITEM					1001
#define CM_PICKUP					1000	//밟繫,숄膠
//#define CM_DROPITEM					1000
//#define CM_PICKUP					1001

#define CM_TAKEONITEM				1003
#define CM_TAKEOFFITEM				1004
#define CM_EAT						1006
#define CM_MAGICKEYCHANGE			1008
#define CM_LOGINNOTICEOK			1018
#define CM_GROUPMODE				1019	// 莉츱즈
#define CM_CREATEGROUP				1020	// 莉츱즈
#define CM_ADDGROUPMEMBER			1021	// 莉츱즈
#define CM_DELGROUPMEMBER			1022	// 莉츱즈
#define CM_TRUN						3010	//瘻��
#define CM_WALK						3011	//浬
#define CM_RUN						3013	//텝
#define CM_HIT						3014	//묑샌
#define CM_FORCEHIT					3015	//퓻제묑샌
#define CM_LONGHIT					3019
#define CM_POWERHIT					3018
#define CM_SPELL					3017	//賈痰침麓 침랬
#define CM_WIDEHIT					3024
#define CM_FIREHIT					3025
#define CM_SAY						3030
#define CM_RIDE						3031

#define CM_BUTCH					1007
#define CM_SITDOWN					3012
#define	CM_CLICKNPC					1010
#define	CM_OPENDOOR					1002


// 공통
#define	CM_CLICKNPC					1010	// 이 메시지를 서버로 보내어 해당 MPC의 정보를 받는다.
#define	CM_MERCHANTDLGSELECT		1011	// 사용자가 NPC대화중 Tag가 존재하는 부분을 Click했을경우 보내어진다.
// 팔기
#define	CM_MERCHANTQUERYSELLPRICE	1012	// 팔기 물건을 올려 놓을 경우 가격을 얻는다.  
											// 변경할 필요가 있음 (과거: 팔물건의 가격만 표시, 현재: 팔리는 물건의 각겨 모두표시)
#define CM_USERSELLITEM				1013	// 팔기 버튼을 눌렸을 경우 (과기: 팔물건만 하나만 보냄, 현재: 팔물건 모두 보냄

// 사기
#define CM_USERBUYITEM				1014	// 사기 버튼을 눌렸을 경우
#define CM_USERGETDETAILITEM		1015	// 상점 목록중에 Sub Menu가 있는 것을 클릭했을 경우

// 수리
#define	CM_USERREPAIRITEM			1023	// 수리하다 버튼을 눌렀을 경우
#define	CM_MERCHANTQUERYREPAIRCOST	1024	// 수리할아이템을 올려 놓을 경우 가격을 얻는다.

// 약방
#define CM_USERMAKEDRUGITEM			1034	// 


// 여관
#define	CM_USERSTORAGEITEM			1031	// 사용자가 맏긴다 버튼(텍스트 버튼 아님)을 눌렀을 경우 보내어진다.
#define	CM_USERTAKEBACKSTORAGEITEM	1032	// 사용자가 찾는다 버튼(텍스트 버튼 아님)을 눌렀을 경우 보내어진다.

// 문파
#define	CM_OPENGUILDDLG				1035	// 사용자가 문파창을 열고자 했을 경우 보내어진다.
#define CM_GUILDHOME				1036	// 사용자가 문파창중 HOME 버튼을 눌렀을 경우 보내어진다.
#define	CM_GUILDMEMBERLIST			1037	// 사용자가 문파창중 문원LIST를 보고자 햇을 경우
#define CM_GUILDADDMEMBER			1038	// 사용자가 문원추가를 했을 경우
#define	CM_GUILDDELMEMBER			1039	// 사용자가 문원삭제를 했을 경우
#define	CM_GUILDUPDATENOTICE		1040	// 사용자가 문파공지를 수정 했을 경우
#define	CM_GUILDUPDATERANKINFO		1041	// 사용자가 문원직위를 수정했을 경우
#define CM_GUILDMAKEALLY			1044	// 사용자가 문파동맹을 했을 경우
#define CM_GUILDBREAKALLY			1045	// 사용자가 문파동맹파기를 했을경우

//鬼뒈暠
#define CM_MINIMAP					1033	//헝헹鬼뒈暠


/******************************************************************************************************************
	#1. Server To Client Message
*******************************************************************************************************************/
//谿꼍땡鱗 UpdatePacketState()
#define SM_RUSH						6		//녑旒.
#define SM_FIREHIT					8		//삽헷댔샌
#define SM_POWERHIT					18		//퓻제댔샌
#define SM_BACKSTEP					9		//빈藁
#define SM_TURN						10		//瘻��
#define SM_WALK						11		//浬
#define SM_RUN						13		//텝
#define SM_HIT						14		//댔샌
#define SM_SPELL					17		//痰륜댔샌
#define SM_LONGHIT					19		//낀약댔샌
#define SM_DIGUP					20		//穀(蕨��)
#define SM_DIGDOWN					21		//穀(蕨苟)
#define SM_FLYAXE					22		//령릊庫(太胎쉥엊돨땡鱗)
#define SM_LIGHTING					23		//�졔�
#define SM_WIDEHIT					24		//댕렀鍋댔샌
#define SM_DISAPPEAR				30		//句呵  ProcessDefaultPacket()
#define SM_STRUCK					31		//굳묑샌
#define SM_DEATH					32		//价空
#define SM_NOWDEATH					34		//价空
#define SM_FEATURECHANGED			41		//棍챵맣긴
#define SM_USERNAME					42		//실�ッ�

#define SM_MAGICFIRE				638		// 침랬삽헷?
#define SM_CHANGELIGHT				654		//밟窟맣긴

//OnSocketMessageRecieve()
#define SM_WINEXP					44		//삿돤쒔駱令
#define SM_LEVELUP					45		//�薨뗍�
#define SM_DAYCHANGING				46		//莖좋/붚
#define SM_LOGON					50		//綠쒔되쩍
#define SM_NEWMAP					51		//劤뒈暠(뒤寧류뒈暠)
#define SM_ABILITY					52		//세콘(된섬,쏜풀,沂,침랬,렝徒...)
#define SM_HEALTHSPELLCHANGED		53		//沂/침랬맣긴 UpdatePacketState()
#define SM_MAPDESCRIPTION			54		//뒈暠츰

#define SM_HEAR						40		//좔莖斤口
#define SM_MONSTERSAY				1501	//밍膠
#define SM_SYSMESSAGE				100		//溝固句口
#define SM_GROUPMESSAGE				101		//莉句口
#define SM_CRY						102		//句口
#define SM_WHISPER					103		//쵱
#define SM_GUILDMESSAGE				104		//契삔句口

#define SM_ADDITEM					200		//警속寧숭膠틔돕관범
#define SM_BAGITEMS					201		//관범
#define SM_ADDMAGIC					210		//劤藤침랬세콘,괏닸瞳m_xInterface.m_xStatusWnd.m_pstMyMagic,壇맡뵨뚤뺐움롸잼
#define SM_SENDMYMAGIC				211		//침랬(홍꼬)

#define SM_DROPITEM_SCCESS			600		//휀땜鮫냥묘
#define SM_DROPITEM_FAIL			601		//휀땜鮫呵겨
#define SM_ITEMSHOW					610		//膠틔놔君,矜狼쇱꿴item list櫓角뤠닸瞳
#define SM_ITEMHIDE 				611		//膠틔茶꾜,닒list櫓�쓱�
#define SM_TAKEON_OK				615		//누덖냥묘
#define SM_TAKEON_FAIL				616		//누덖呵겨
#define SM_DOOROPEN					612		//역쳔
#define SM_TAKEOFF_OK				619		//菌苟냥묘
#define SM_TAKEOFF_FAIL				620		//菌苟呵겨
#define SM_SENDUSEITEMS				621		//鞫刻깎훙돨陋구
#define SM_WEIGHTCHANGED			622		//路좆맣긴
#define SM_CHANGEMAP				634		//뫘뻣뒈暠
#define SM_CLEAROBJECT				633		//훙膠,밍膠句呵
#define SM_EAT_OK					635		//뵌浪
#define SM_EAT_FAIL					636		//뵌浪呵겨
#define SM_MAGIC_LVEXP				640		//침랬�薨�(鬼삽헷->댕삽헷)
#define SM_DURACHANGE				642		//Item넣씹맣긴
#define SM_GOLDCHANGE				653		//Gold맣긴

#define SM_CHANGENAMECOLOR			656		//츰俚奈�ジ캇�
#define SM_CHARSTATUSCHANGE			657		//榴檄맣긴 UpdatePacketState()
#define SM_SENDNOTICE				658		//되쩍珂돨Notice

#define SM_CREATEGROUP_OK			660		//눼쉔莉냥묘
#define SM_CREATEGROUP_FAIL			661		//눼쉔莉呵겨
#define SM_GROUPCANCEL				666		//혤句莉
#define SM_GROUPMEMBERS				667		//莉逃

#define SM_CHANGEGUILDNAME			750		//契삔츰맣긴
#define SM_SUBABILITY				752		//세콘2

#define SM_SHOWEVENT				804
#define SM_HIDEEVENT				805

#define SM_DELITEM					202
#define SM_DELITEMS					203

#define SM_CLOSEHEALTH				1101
#define SM_OPENHEALTH				1100
#define SM_SITDOWN					12
#define SM_BUTCH					637
#define SM_SKELETON					33		// SM_DEATH와 동일.
#define SM_CHANGEFACE				1104;

#define SM_OPENDOOR_OK				612
#define SM_OPENDOOR_LOCK			613
#define SM_CLOSEDOOR				614

#define SM_MERCHANTSAY				643		//merchant-�京� NPC뚤뺐
#define	SM_MERCHANTDLGCLOSE			644		//밑균NPC뚤뺐
#define SM_SENDGOODSLIST			645
#define SM_SENDUSERSELL				646
#define	SM_SENDBUYPRICE				647		//send buy price
#define SM_USERSELLITEM_OK			648		//놔簡냥묘
#define SM_USERSELLITEM_FAIL		649		//놔簡呵겨
#define	SM_BUYITEM_SUCCESS			650		//찜냥묘
#define SM_BUYITEM_FAIL				651		//찜呵겨
#define SM_SENDDETAILGOODSLIST		652		//圈玖goods list
#define	SM_GOLDCHANGED				653		//쏜귑맣긴
#define	SM_OPENGUILDDLG				753		//댔역契삔뚤뺐움
#define	SM_OPENGUILDDLG_FAIL		754		//댔역契삔뚤뺐움-呵겨
#define	SM_SENDGUILDHOME			755		//
#define	SM_SENDGUILDMEMBERLIST		756		//鞫刻契삔냥逃
#define	SM_GUILDADDMEMBER_OK		757		//警속契삔냥逃
#define	SM_GUILDADDMEMBER_FAIL		758		//警속契삔
#define	SM_GUILDDELMEMBER_OK		759		//�쓱虧剋小�逃
#define	SM_GUILDDELMEMBER_FAIL		760
#define	SM_GUILDRANKUPDATE_FAIL		761
#define	SM_BUILDGUILD_OK			762
#define	SM_BUILDGUILD_FAIL			763
#define	SM_GUILDMAKEALLY_OK			768
#define	SM_GUILDMAKEALLY_FAIL		769
#define	SM_GUILDBREAKALLY_OK		770
#define	SM_GUILDBREAKALLY_FAIL		771
#define	SM_DLGMSG					772


#define	SM_AREASTATE				708
#define	SM_RIDEHORSE				1300

#define SM_DECODEKEY				1330	//썩쵱돨쵱篤

//灌땍屢돨句口
#define SM_INVENTITEM				1313	//膠틔맣긴,寧븐/읊/踞샙얩된냥웽돨膠틔 ,藤속,숑�帽속饉狐�
#define SM_639						639
#define SM_709						709		//价빈돨句口
#define SM_803						803		//관벵麟깃斤口
#define SM_801						801		//
#define SM_807						807		//
#define SM_1104						1104	//
#define SM_1318						1318
#define SM_1323						1323
#define SM_1401						1401


/******************************************************************************************************************
	Resource Dll string index
*******************************************************************************************************************/
#define PUNISHMENT_ID_USING             1
#define PUNISHMENT_ID_THEFT             2
#define PUNISHMENT_DISTURB_GAME         3
#define PUNISHMENT_BBS_CURSES           4
#define PUNISHMENT_CONFIRMED_CURSES     5
#define PUNISHMENT_USAGE_BUG            6
#define PUNISHMENT_ASSUMED_GAMEMASTER   7
#define PUNISHMENT_SPREAD_FALLACY       8
#define NEW_ACCOUNT_HELP_ID             9
#define NEW_ACCOUNT_HELP_PWD            10
#define NEW_ACCOUNT_HELP_REPWD          11
#define NEW_ACCOUNT_HELP_NAME           12
#define NEW_ACCOUNT_HELP_SSNO           13
#define NEW_ACCOUNT_HELP_BIRTH          14
#define NEW_ACCOUNT_HELP_ZIPCODE        15
#define NEW_ACCOUNT_HELP_ADDRESS        16
#define NEW_ACCOUNT_HELP_PHONE          17
#define NEW_ACCOUNT_HELP_MOBILEPHONE    18
#define NEW_ACCOUNT_HELP_EMAIL          19
#define NEW_ACCOUNT_HELP_Q              20
#define NEW_ACCOUNT_HELP_A              21
#define NEW_ACCOUNT_WELL_DONE           22
#define ERROR_STR_LOGIN_1               23
#define ERROR_STR_LOGIN_2               24
#define ERROR_STR_LOGIN_3               25
#define ERROR_STR_LOGIN_4               26
#define ERROR_STR_NEW_ACCOUNT_1         27
#define ERROR_STR_NEW_ACCOUNT_2         28
#define ERROR_STR_NEW_ACCOUNT_3         29
#define ERROR_STR_NEW_ACCOUNT_4         30
#define ERROR_STR_NEW_ACCOUNT_5         31
#define ERROR_STR_NEW_ACCOUNT_6         32
#define ERROR_STR_NEW_ACCOUNT_7         33
#define ALRAM_CHARGE                    34
#define ALRAM_CHARGE_IP                 35
#define ALRAM_CHARGE_1                  36
#define ALRAM_CHARGE_2                  37
#define ALRAM_CHARGE_3                  38
#define CHANGE_PASSWORD                 39
#define CHANGE_PASSWORD_1               40
#define CHANGE_PASSWORD_2               41
#define CHANGE_PASSWORD_3               42
#define CHANGE_PASSWORD_4               43
#define ERROR_STR_SELECT_SERVER_1       44
#define ERROR_STR_SELECT_SERVER_2       45
#define ERROR_STR_NEWCHR_1              200
#define ERROR_STR_NEWCHR_2              201
#define ERROR_STR_NEWCHR_3              202
#define DELETE_CHARACTER_1              203
#define DELETE_CHARACTER_2              204
#define VERSION_NOT_MATCHED             205
#define ERROR_STR_START_GAME_1          206
#define ERROR_STR_DELCHR                207
#define ERROR_STR_PATCH_1               300
#define ERROR_STR_PATCH_2               301
#define ERROR_STR_SERVER_CONNECTION     302
#define NOTICE_NOT_EXIST_INDEX          400
#define NOTICE_LAST_PAGE                401
#define FATAL_ERROR_STR                 9999
#define SERVER_SELECT_TEST              10000
//////////////////////////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************************************
		Login Procedure
*******************************************************************************************************/
#define _LOGIN_SCREEN_WIDTH		640
#define _LOGIN_SCREEN_HEIGHT	480


/******************************************************************************************************************
	#1. Progress States
*******************************************************************************************************************/
#define PRG_CONNECT					 -1
#define PRG_INTRO					 0
#define PRG_LOGIN					 1
#define PRG_NEW_ACCOUNT				 3
#define PRG_PATCH					 4
#define PRG_CHANGE_PASS				 5
#define	PRG_SERVER_SELE				 6
#define PRG_TO_SELECT_CHR			 7
#define	PRG_CHAR_SELE				 8
#define	PRG_CREATE_CHAR				 9
#define PRG_PLAY_GAME				10

#define PRG_SEL_TO_CREA				30
#define PRG_CREA_TO_SEL				31
#define PRG_SEL_TO_GAME				32

#define PRG_PATCH_FILES				77
#define PRG_NEED_ACCOUNT_CHANGE		88
#define PRG_QUIT					99



#endif // _DEFINE_H


