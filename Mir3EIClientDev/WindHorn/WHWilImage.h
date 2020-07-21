/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/



#ifndef _WILIMAGEHANDLER_
#define	_WILIMAGEHANDLER_



/******************************************************************************************************************

	CWilImageData Class Declaration

   ���̹����� �޸𸮿� �ε��ϰų� ���� �޸𸮸����·� ���ϴ� ��ġ�� �����Ѵ�.

*******************************************************************************************************************/


#pragma pack(1)

typedef struct tagWILFILEHEADER
{
	CHAR	szTmp[40];
	INT		nImageCount;
}WILFILEHEADER, *LPWILFILEHEADER;

typedef struct tagWILFILEIMAGEINFO
{
	SHORT	shWidth;
	SHORT	shHeight;
	SHORT	shPX;
	SHORT	shPY;
	DWORD	dwImageLength;
}WILIMAGEINFO, *LPWILIMAGEINFO;

typedef struct tagWIXFILEIMAGEINFO
{
	CHAR	szTmp[40];
	INT		nIndexCount;
	INT*	pnPosition;
}WIXIMAGEINFO, *LPWIXIMAGEINFO;


typedef struct tagNEWWILFILEHEADER
{
	SHORT	shComp;
	CHAR	szTitle[20];
	SHORT	shVer;
	INT		nImageCount;
}NEWWILFILEHEADER, *LPNEWWILFILEHEADER;

typedef struct tagNEWWILFILEIMAGEINFO
{
	SHORT	shWidth;
	SHORT	shHeight;
	SHORT	shPX;
	SHORT	shPY;
	CHAR	bShadow;					
	SHORT	shShadowPX;
	SHORT	shShadowPY;
	DWORD	dwImageLength;
}NEWWILIMAGEINFO, *LPNEWWILIMAGEINFO;
typedef struct tagNEWWIXFILEIMAGEINFO
{
	CHAR	szTitle[20];
	INT		nIndexCount;
	INT*	pnPosition;
}NEWWIXIMAGEINFO, *LPNEWWIXIMAGEINFO;

#pragma pack(8)


class CWHWilImageData
{
private:
protected:
	BOOL				m_bIsMemMapped;				// �޸𸮸ʻ�뿩��.
	BOOL				m_bIsCompressed;			// ���࿩��.

	LPBYTE				m_pbStartData;				// ����Ÿ�� �����ּ�.(��ü ����Ÿ������ ����ũ��� ����.)

	INT					m_nCurrImageIdx;			// ���� ����Ű�� �ִ� �ε���.


public:
	NEWWIXIMAGEINFO		m_stNewWixImgaeInfo;		//wix�ļ�ͷ

	LPWILIMAGEINFO		m_lpstCurrWilImageInfo;		// ���� �������� ������ ����Ű�� ������.
	LPNEWWILIMAGEINFO	m_lpstNewCurrWilImageInfo;	

	BYTE*				m_pbCurrImage;				// ���� �������� �̹����� ����Ű�� ������.
	TCHAR				m_szWilFileName[MAX_PATH];

	CWHWilImageData();
	~CWHWilImageData();

	BOOL NewLoad(CHAR* szWilFile, BOOL bComp = TRUE);
	BOOL NewSetIndex(DWORD dwIndex);				// �ܺο��� ���޹��� �ε����� ������ �����̹����� ������ ����Ű�� �ּҸ� Setting�Ѵ�.


	BOOL Load(CHAR* szWilFile, BOOL bIsMemMapped = TRUE, BOOL bComp = TRUE);
	VOID Init();
	VOID Destroy();
	VOID SetIndex(INT nIndex);						// �ܺο��� ���޹��� �ε����� ������ �����̹����� ������ ����Ű�� �ּҸ� Setting�Ѵ�.
};


#endif //_WILIMAGEHANDLER_
