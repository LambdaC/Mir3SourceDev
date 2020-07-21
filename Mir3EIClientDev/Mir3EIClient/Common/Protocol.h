
#ifndef _LEGENDOFMIR2_PROTCOL
#define _LEGENDOFMIR2_PROTCOL

#define DEFBLOCKSIZE			16

// For Game Gate
#define GM_OPEN					1
#define GM_CLOSE				2
#define	GM_CHECKSERVER			3			// Send check signal to Server
#define GM_CHECKCLIENT			4			// Send check signal to Client
#define GM_DATA					5
#define GM_SERVERUSERINDEX		6
#define GM_RECEIVE_OK			7
#define GM_TEST					20

#define	SM_VERSION_AVAILABLE	500			//
#define	SM_CERTIFICATION_FAIL	501			//  Fail
#define SM_ID_NOTFOUND			502			//	ID ����
#define	SM_PASSWD_FAIL			503			//	�н����� Ʋ��
#define	SM_NEWID_SUCCESS		504			//	�����̵� �� ����� ����
#define	SM_NEWID_FAIL			505			//	�����̵� ����� ����
#define	SM_CHGPASSWD_SUCCESS	506			//	�н����� �ٲٱ� ����
#define	SM_CHGPASSWD_FAIL		507			//	�н����� �ٲٱ� ����
#define	SM_QUERYCHR				520			//	ĳ������Ʈ
#define	SM_NEWCHR_SUCCESS		521			//	�ɸ��� ���� ����
#define	SM_NEWCHR_FAIL			522			//	�ɸ��� ���� ����
#define	SM_DELCHR_SUCCESS		523			//	�ɸ��� ���� ����
#define	SM_DELCHR_FAIL			524			//	�ɸ��� ���� ����
#define	SM_STARTPLAY			525			//	���ӽ���
#define	SM_STARTFAIL			526			//	���ӽ��� ����
#define	SM_QUERYCHR_FAIL		527			//	�ɸ��� ���� �о���� ����
#define	SM_OUTOFCONNECTION		528			//	���� ������
#define	SM_PASSOK_SELECTSERVER	529			//	Password�� �����Ƿ�  ���� Selection���� �Ѿ(���� List�� �ֱ� ���Ӽ��� �ڷ�)
#define	SM_SELECTSERVER_OK		530			//	�������� (���� ���� IP���� ������ ��)
#define	SM_NEEDUPDATE_ACCOUNT	531			//	������ ������ �ٽ� �Է��ϱ� �ٶ� â..
#define	SM_UPDATEID_SUCCESS		532			//	�������� ���� ����
#define	SM_UPDATEID_FAIL		533			//	�������� ���� ����


// For login process
#define CM_PROTOCOL				2000
#define CM_IDPASSWORD			2001
#define CM_ADDNEWUSER			2002
#define CM_CHANGEPASSWORD		2003
#define CM_UPDATEUSER			2004

#define CM_QUERYCHR				100
#define CM_NEWCHR				101
#define CM_DELCHR				102
#define CM_SELCHR				103
#define CM_SELECTSERVER			104


#define LGM_NONE				0
#define LGM_INPUT_ID			1			// Login Input ID
#define LGM_INPUT_PASSWORD		2			// Login Input Password
#define LGM_INPUT_USER_ID		10			// Account Input ID
#define LGM_INPUT_USER_PASSWORD	11			// Account Input Password
#define LGM_INPUT_REPASS		12			// Account Input RePass
#define LGM_INPUT_USER_NAME		13			// Account Input User Name	
#define	LGM_INPUT_SSNO			14			// Account Input SSNO.
#define LGM_INPUT_BIRTH			15			// Account Input Birthday
#define LGM_INPUT_ZIP_1			16			// Account Input First Zip code
#define LGM_INPUT_ZIP_2			17			// Account Input Second Zip code
#define LGM_INPUT_ADDRESS_1		18			// Account Input Address #1
#define LGM_INPUT_ADDRESS_2		19			// Account Input Address #2
#define LGM_INPUT_TELNUM		20			// Account Input Telephone Number
#define LGM_INPUT_MOBILE		21			// Account Input Mobile Phone Number
#define LGM_INPUT_EMAIL			22			// Account Input E-Mail
#define LGM_INPUT_QUIZ_1		23			// Account Input Quiz1
#define LGM_INPUT_ANSWER_1		24			// Account Input Answer1
#define LGM_INPUT_QUIZ_2		25			// Account Input QUiz2
#define LGM_INPUT_ANSWER_2		26			// Account Input Answer2

#define CONNECT_FAIL				0
#define CONNECT_SUCCESS				1
#define CONNECT_CLOSE				2

typedef struct tagTUserEntryInfo
{
	char		szLoginID[10];
	char		szPassword[10];
	char		szUserName[20];
	char		szSSNo[15];
	char		szPhone[14];
	char		szQuiz[20];
	char		szAnswer[12];
	char		szEmail[40];
} TUserEntryInfo, *LPTUserEntryInfo;

typedef struct tagTUserEntryAddInfo
{
	char		szQuiz2[20];
	char		szAnswer2[12];
	char		szBirthDay[11];
	char		szMobilePhone[15];
} TUserEntryAddInfo, *LPTUserEntryAddInfo;

typedef struct _Rect
{
	int x;
	int y;
	int Width;
	int Height;
}	Rect;

////////////////////////////////////////////
typedef struct tagUnCompressedFileNode
{
	char		szFileName[128];
	char		szTargetFileName[128];
	long		lDirectory;
	long		lFileSize;
	long		Position;
	long		ActionMode;
	long		lCount;
} UnCompressedFileNode;

////////////////////////////////////////////
typedef struct	tagFTPFILE
{
	char		Name[66];	// File Name
	char		Type;		// 
	int			Size;		// Each File Size
}FTPFILE;

////////////////////////////////////////////
typedef	struct	tagFileListHeader
{
	int		Count;			// File Count
	long	Amount;			// File Amount
	char	VersionDate[8];	// Version for Update ex) 2001.12.20 -> 20011220
}FileListHeader;

////////////////////////////////////////////
#define WM_BUTTONCLICK				WM_USER + 500	// Button Class�� Click Event �� �޾��� ���
#define WM_MOUSEON					WM_USER + 501	// Button Class�� mouse on Event �� �޾��� ���

#endif
