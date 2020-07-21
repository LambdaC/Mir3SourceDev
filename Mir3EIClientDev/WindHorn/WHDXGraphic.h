#ifndef _WINDHORN_DXGRAPHIC
#define	_WINDHORN_DXGRAPHIC



/******************************************************************************************************************

	CWHDXGraphicWindow Class Declaration

*******************************************************************************************************************/

typedef struct tagDXG_DISPLAYINFO 
{
	WORD			wWidth;
	WORD			wHeight;
	WORD			wBPP;
}DXG_DISPLAYINFO, *LPDXG_DISPLAYINFO;

typedef struct DXG_ENUM_DEVICEINFO
{
    // 3D ����̽� ����.
    TCHAR			szDeviceDesc[256];
    GUID*			pDeviceGUID;
    D3DDEVICEDESC7	ddDeviceDesc;
    BOOL			f3DHardware;
    // ��ο� ����̹� ����.
	TCHAR			szDriverDesc[256];
    GUID*			pDriverGUID;
    DDCAPS			ddDriverCaps;
    DDCAPS			ddHELCaps;

    GUID            guidDevice;
    GUID            guidDriver;
    DDSURFACEDESC2* pddsdModes;
    DWORD           dwNumModes;
}DXG_ENUM_DEVICEINFO, *LPDXG_ENUM_DEVICEINFO;

typedef struct tagDXG_MASKINFO
{
	BYTE			bRCnt;
	BYTE			bGCnt;
	BYTE			bBCnt;
	BYTE			bRShift;
	BYTE			bGShift;
	BYTE			bBShift;
	DWORD			dwRMask;
	DWORD			dwGMask;
	DWORD			dwBMask;
}DXG_MASKINFO, *LPDXG_MASKINFO;


class CWHDXGraphicWindow : public CWHWindow
{
//1: Constuctor/Destructor
public:
	CWHDXGraphicWindow(WORD wWidth = _SCREEN_WIDTH, WORD wHeight = _SCREEN_HEIGHT, WORD wBpp = _SCREEN_BPP);
	~CWHDXGraphicWindow();

//2: Variables
protected:
	LPDIRECT3D7				m_pD3D;
    LPDIRECTDRAW7			m_pDD;
	LPDIRECT3DDEVICE7		m_pd3dDevice;
    LPDIRECTDRAWSURFACE7	m_pddsFrontBuffer;
    LPDIRECTDRAWSURFACE7	m_pddsBackBuffer;
	LPDIRECTDRAWSURFACE7	m_pddsZBuffer;
	LPDIRECTDRAWCLIPPER		m_lpcClipper;

///////<---------------------------------------------------------------------------------------------------------------------------
	HFONT					m_hDefGameFont;
///////<---------------------------------------------------------------------------------------------------------------------------

	BYTE					m_bScreenModeFlag;
    BYTE					m_bDeviceModeFlag;

public:
	DWORD					m_dwTextureTotal;	// ��ü ����Ҽ� �ִ� �޸�.
	DWORD					m_dwTextureFree;    // ���� ���� �޸�.
	DWORD					m_dwVideoTotal; 	// vram ��ü �޸�.
	DWORD					m_dwVideoFree;      // ���� ���� vram �޸� .

	BOOL					m_bIsWindowActive;
	BOOL					m_bIsWindowReady;

    RECT					m_rcWindow;
	DXG_DISPLAYINFO			m_stDisplayInfo;
	DXG_MASKINFO			m_stBitsMaskInfo;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���μ����� ���������� ��������.
	static CWHDXGraphicWindow*	m_pxDXGWnd;
	CWHDefProcess*				m_pxDefProcess;

	VOID					(*RenderProcess)(int);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//3: Methods
protected:
	BYTE	FindDriverAndDevice();
	VOID	FreeDXGEnumModeResources();

	HRESULT CreateDXG();
	HRESULT	CreatePrimarySurface();
	HRESULT CreateZBuffer(GUID* pDeviceGUID);
	HRESULT Init3DDeviceObjects();
	HRESULT DestroyDXGObjects();

public:

    __inline LPDIRECTDRAW7			GetDirectDraw()     { return m_pDD;				}
    __inline LPDIRECT3D7			GetDirect3D()		{ return m_pD3D;			}
	__inline LPDIRECT3DDEVICE7		Get3DDevice()		{ return m_pd3dDevice;		}
    __inline LPDIRECTDRAWSURFACE7	GetFrontBuffer()    { return m_pddsFrontBuffer; }
    __inline LPDIRECTDRAWSURFACE7	GetBackBuffer()     { return m_pddsBackBuffer;	}
    __inline BYTE					GetDeviceMode()     { return m_bDeviceModeFlag; }
	__inline BYTE					GetScreenMode()		{ return m_bScreenModeFlag; }

    DXG_MASKINFO			GetRGBMaskInfoIN16Bits(LPDIRECTDRAWSURFACE7 pSurface);
	virtual VOID			UpdateBoundsWnd();

	HRESULT					ResetDXG(WORD wWidth, WORD wHeight, WORD wBPP, BYTE bScreenModeFlag, BYTE bDeviceModeFlag);
	BOOL					Create(HINSTANCE hInst, LPTSTR lpCaption = NULL, CHAR *pszMenuName = NULL, CHAR* pszIconName = NULL, BYTE bScreenModeFlag = _DXG_SCREENMODE_WINDOW, BYTE bDeviceModeFlag = _DXG_DEVICEMODE_PRIMARY);

///////<---------------------------------------------------------------------------------------------------------------------------
	HFONT					CreateGameFont(LPCSTR szFontName, INT nHeight, INT nWidth = 0, INT nWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bULine = FALSE, BOOL bStrikeOut = FALSE, DWORD dwCharSet = DEFAULT_CHARSET);
	VOID					CreateDefFont();

	VOID					PutsHan(LPDIRECTDRAWSURFACE7 pSurface, INT nX, INT nY, COLORREF foreColor, COLORREF backColor, CHAR* szText, HFONT hFont = NULL);
	VOID					PutsHan(LPDIRECTDRAWSURFACE7 pSurface, RECT rc, COLORREF foreColor, COLORREF backColor, CHAR* szText, HFONT hFont = NULL);

	SIZE					GetStrLength(LPDIRECTDRAWSURFACE7 pSurface, HFONT hFont, CHAR* szFormat, ...);
///////<---------------------------------------------------------------------------------------------------------------------------

	BOOL 					StringDivide(INT nDivideWidth, INT& nDividedLine, CHAR* szSrc, CHAR* szResult);
//	BOOL					StringDivideLen(INT nDivideLen, INT& nDividedLine, CHAR* szSrc, CDLList<CHAR*>* m_pxpStr);

	VOID 					StringPlus(CHAR* szResult, CHAR* szSrc, ...);
	CHAR*					IntToStr(INT nNum);

	VOID					UsedAndFreeMemoryCheck();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WORD					ConvertColor24To16(COLORREF dwColor);
	// ������ �Լ�����.
	// 1. GDI�� �׸��� �Լ�.(��, �簢������ �鼭�ǽ��� �׸���.)
	HRESULT					DrawWithGDI(RECT rc, LPDIRECTDRAWSURFACE7 pSurface, DWORD dwColor, BYTE bKind);
	// 2. WORD�� ����Ÿ �׸��� �Լ�.(�ȼ������� �÷�Ű�� �˻��ϸ鼭 �鼭�ǽ��� �׸���.)
	BOOL					DrawWithImage(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc);
	// 3. WORD�� ����Ÿ �׸��� �Լ�.(���δ����� �÷�Ű�� ������� �ʰ� �鼭�ǽ��� Ŭ���� ���ο������� �׸���.)
	BOOL					DrawWithImagePerLineClipRgn(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight);
	// 4. Surface�� ����Ÿ �׸��� �Լ�.(�ҽ��� �÷�Ű�� ����ϸ鼭 �鼭�ǽ��� �׸���.)
	BOOL					DrawWithSurface(INT nX, INT nY, INT nXSize, INT nYSize, LPDIRECTDRAWSURFACE7 pddsSrc);

	// wChooseColor1�� ������(0xC2)�� ���ؼ�, wChooseColor2(0xC3)�� �Ӹ���(Į, ��Ÿ ���ϴ»�)�� �������� ����.
	// 5. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(�鼭�ǽ��� �׸���.)
	BOOL					DrawWithImageForComp(INT nX, INT nY, RECT rcSrc, WORD* pwSrc, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF);
	BOOL					DrawWithImageForComp(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF);
	// 6. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(�鼭�ǽ��� Ŭ���� ���ο������� �׸���.)
	BOOL					DrawWithImageForCompClipRgnBase(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF);
	__inline VOID			DrawWithImageForCompClipRgn(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF, BOOL bLighted = FALSE)
	{
		if ( bLighted )		DrawWithABlendCompDataWithLightedColor(nX, nY, nXSize, nYSize, pwSrc, wClipWidth, wClipHeight, wChooseColor1, wChooseColor2);
		else				DrawWithImageForCompClipRgnBase(nX, nY, nXSize, nYSize, pwSrc, wClipWidth, wClipHeight, wChooseColor1, wChooseColor2);
	}


	// 7. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(�ҽ��޸��� �������� ����Ʈ�����޸𸮷� �׸���.)
	BOOL					DrawWithImageForCompMemToMem(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, INT nDstXSize, INT nDstYSize, WORD* pwDst, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF);
	// 8. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(����� ����Ÿ�� �ҽ��޸��� �������� �Ϻη�Ʈ�������� ����Ʈ�����޸𸮷� �׸���.)
	BOOL					DrawWithImageForCompToMem(RECT rcWanted, WORD* pwSrc, WORD wChooseColor1, WORD wChooseColor2, WORD* pwDst);
	BOOL					DrawWithImageForCompColorToMem(RECT rcWanted, WORD* pwSrc, WORD wColor, WORD* pwDst);
	// 9. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(����� ����Ÿ�� �ҽ������� ����Ʈ������ ������Ʈ�� ���ĺ����ؼ� �鼭�ǽ����׸���.)
	BOOL					DrawWithABlendForIntersectCompData(INT nSrcX, INT nSrcY, 
															   INT nSrcXSize, INT nSrcYSize, WORD* pwSrc,
															   INT nDstX, INT nDstY,
															   INT nDstXSize, INT nDstYSize, WORD* pwDst, 
															   WORD wClipWidth, WORD wClipHeight,
															   BYTE bOpa = 50, BOOL bFocused = FALSE,
															   WORD wSrcChooseColor1 = 0XFFFF, WORD wSrcChooseColor2 = 0XFFFF,
															   WORD wDstChooseColor1 = 0XFFFF, WORD wDstChooseColor2 = 0XFFFF,
															   WORD wSrcColor = 0XFFFF, WORD wDstColor = 0XFFFF);
	// 10. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(����� ����Ÿ�� �ҽ������� �鼭�ǽ��� ���ĺ����Ѵ�.)
	BOOL					DrawWithABlendCompDataWithBackBuffer(INT nX, INT nY, 
																 INT nXSize, INT nYSize, WORD* pwSrc,
																 WORD wClipWidth, WORD wClipHeight,
																 WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF, BYTE bOpa = 50);
	// 11. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(����� ����Ÿ�� �ҽ������� ���ϴ� �÷��� ������ ���·�(���) �鼭�ǽ��� �׸���.)
	BOOL					DrawWithABlendCompDataWithLightedColor(INT nX, INT nY, 
																   INT nXSize, INT nYSize, WORD* pwSrc,
																   WORD wClipWidth, WORD wClipHeight,
																   WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF);
	// �׸��� �׸��� �Լ�.
	// 12. ����(0��)�� ������ WORD�� ����Ÿ �׸��� �Լ�.(����� ����Ÿ�� �ҽ������� �׸��ڸ� �鼭�ǽ��� ���ĺ����Ѵ�. �׸��ڴ� ���̰� �������� �پ��� ���̴� YSize��ŭ �þ�� ��￩ �鼭�ǽ��� ������.)
	BOOL					DrawWithShadowABlend(INT nX, INT nY, 
												 INT nXSize, INT nYSize, WORD* pwSrc,
												 WORD wClipWidth, WORD wClipHeight, WORD* pwShadowClrSrc,
												 BOOL bBlend = FALSE, BYTE bShadowType = 48, BYTE bOpa = 50);
	VOID					DrawWithShadowABlend(INT nX, INT nY, INT nXSize, INT nYSize, 
		                                         INT nPX, INT nPY, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight, WORD* pwShadowClrSrc,
												 BOOL bBlend = FALSE, BYTE bOpa = 50);
	// �÷�ó��.
	// 13.
	BOOL					DrawWithImageForCompClipRgnColor(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight, WORD wColor, BOOL bFocused = FALSE, BOOL bBlend = FALSE);
	BOOL					DrawWithImageForCompClipRgnColor(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight, WORD wColor, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF);
	// 14.
	BOOL					DrawWithImageForCompClipRgnGray(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc , WORD wClipWidth, WORD wClipHeight, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF);
	// ���ó��.
	// 15.
	VOID					DrawWithGrayBackBuffer();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	HRESULT					Present();
	HRESULT					RestoreSurfaces();

//4: Message Map
public:
	virtual LRESULT MainWndProcDXG(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSize(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysKeyDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);


protected:

	__inline virtual LRESULT MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{ 
		if ( m_pxDefProcess )	return m_pxDefProcess->DefMainWndProc(hWnd, uMsg, wParam, lParam);
		else					return MainWndProcDXG(hWnd, uMsg, wParam, lParam); 
	}

	virtual LRESULT	OnDestroy();
	virtual LRESULT	OnSetCursor();
};

CWHDXGraphicWindow*		GetDXGWindowPtr();

#endif //_WINDHORN_DXGRAPHIC
