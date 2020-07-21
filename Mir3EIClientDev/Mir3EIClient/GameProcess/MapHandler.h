/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/


#ifndef _MAPHANDLER_
#define	_MAPHANDLER_


#pragma pack(1)
typedef struct tagLIGHTINFO
{
	BOOL	bIsLight;
	CHAR	cLightSizeType;
	CHAR	cLightColorType;
}LIGHTINFO, *LPLIGHTINFO;

// ������ �ε����� ��������.
// ���� �ִ� ������ ��ü �ʿ� ���õ� ������ �����Ѵ�.
typedef struct tagMAPFILEHEADER
{
	CHAR	szDesc[20];
	WORD	wAttr;
	SHORT	shWidth;
	SHORT	shHeight;
	CHAR	cEventFileIdx;
	CHAR	cFogColor;
}MAPFILEHEADER, *LPMAPFILEHEADER;

typedef struct tagTILEINFO
{
	BYTE	bFileIdx;
	WORD	wTileIdx;
}TILEINFO, *LPTILEINFO;

typedef struct tagCELLINFO
{
	BYTE	bFlag;
	BYTE	bObj1Ani;
	BYTE	bObj2Ani;
	WORD	wFileIdx;//BYTE
	WORD	wObj1;
	WORD	wObj2;
	WORD	bDoorIdx;//BYTE,����Ҫ�ĵĵط�����һ��
	BYTE	bDoorOffset;
	WORD	wLigntNEvent;
}CELLINFO, *LPCELLINFO;
/*
typedef struct tagCELLINFO
{
BYTE	bFlag;
BYTE	bObj1Ani;
BYTE	bObj2Ani;
BYTE	bFileIdx;
WORD	wObj1;
WORD	wObj2;
BYTE	bDoorIdx;
BYTE	bDoorOffset;
WORD	wLigntNEvent;
}CELLINFO, *LPCELLINFO;
*/
/*
typedef struct tagDOORIMAGEINFO
{
	WORD	wPosX;
	WORD	wPosY;
	WORD	wImageNum;
}DOORIMAGEINFO, *LPDOORIMAGEINFO;

typedef struct tagDOORINFO
{
	BYTE			bDoorIdx;
	BYTE			bDoorImgCnt;
	LPDOORIMAGEINFO	pstDoorImgInfo;
}DOORINFO, *LPDOORINFO;
*/
#pragma pack(8)


class CMapHandler
{
private:
protected:
public:
	LPTILEINFO		m_pstTileInfo;
	LPCELLINFO		m_pstCellInfo;

	MAPFILEHEADER	m_stMapFileHeader;				// �ε��� �������� ���.

	// ĳ������ �̵��� ���õȴ�.
	SHORT			m_shStartViewTileX;				// �俵���� ���� X Tile ��ǥ.(���� ��ũ�� ���� Ÿ�� ��ǥ���� ���� �� ū �������̴�.)
	SHORT			m_shStartViewTileY;				// �俵���� ���� ��ũ�� �������� ����, ���� 1Ÿ�Ͼ��� �������� �д�.
	SHORT			m_shViewOffsetX;				// ��ũ���� X���� ����.(ĳ������ �ȱ⵿���� ������.)
	SHORT			m_shViewOffsetY;				

	RECT			m_rcView;						// �ʱ⺻Ÿ���� �׷��� ����.(ȭ��Ŭ������ ���ؼ�)

	POINT			m_ptMovePixelArray[6];			// �̵��� ���� �ȼ����� ��������Ÿ.

	WORD			m_wSavedMapBuffer[_VIEW_CELL_X_COUNT * _CELL_WIDTH * _VIEW_CELL_Y_COUNT * _CELL_HEIGHT];				// �⺻Ÿ�ϰ� SMŸ���� ����� ����. �ڱ� ĳ���Ͱ� �̵��ϱ����� ���ŵ��� �ʴ´�.


	DWORD			m_dwAniSaveTime[8];
	BYTE			m_bAniTileFrame[8][16];

	CWHWilImageData*	m_pxTileImg[_MAX_TILE_FILE];
	CImageHandler*		m_pImageHander;
/*
	BYTE			m_bDoorCount;
	LPDOORINFO		m_pstDoorInfo;
	BYTE*			m_pbCellIDoorIdx;
*/

public:
	CMapHandler();
	~CMapHandler();
	VOID			InitMapHandler();				// Ŭ���� ���� �ʱ�ȭ.
	VOID			LoadMapHandler(CHAR* szMapFile, CImageHandler* pxImgHandler, INT nX, INT nY);// �̹����� ���� �ʿ뵥��Ÿ �ε�.
	VOID			DestroyMapHandler();			// Ŭ���� ���� �ʱ�ȭ�� �޸� ����.

	BOOL			LoadMapData(CHAR* szMapFile);	// ����Ǵ� ���� ����Ÿ�� �ε�.(���� �ٲ𶧸��� �ҷ�����.)
	VOID			LoadMapImage(CImageHandler* pxImgHandler);					// �ʿ� ���õ� �̹��� ����Ÿ �ε�(�޸𸮸ʻ��).
	VOID			LoadNewMapBuffer();				// ���� ó�� �ε��Ǿ����� Ÿ��, SMŸ�� ��Ϲ��ۿ� ������ ������ �����Ѵ�.

	VOID			FreeMapData();					// ����Ǵ� ���� ����Ÿ�� ����.(���� �ٲ𶧸��� �ҷ�����.)

	VOID			DrawBaseTile(INT nX, INT nY);	// �⺻Ÿ���� �׸���.
//	VOID			DrawOpenDoor(INT nX, INT nY);
//	VOID			SetDoorIndex();

	VOID			ScrollMap(INT nCharDir, INT nCharFrame, INT nSpeed);		// ĳ���� �̵��� ���� Scroll���� ������ ����.
	VOID			ScrollMap(INT nCharDir, WORD wCurrDelay, WORD wMoveDelay, INT nSpeed);
	VOID			SetMovedTileBuffer(SHORT shMovedTileX, SHORT shMovedTileY);	// ĳ���� �̵��� ���� ���ŵǴ� �⺻ �̹���(Ÿ��, SMŸ��)�� ����.
	VOID			SetStartViewTile(INT nX, INT nY);							// �׸��� �俵���� �ʱ�ġ����.

	BOOL			GetNextTileCanMove(INT nXPos, INT nYPos, BYTE bDir, INT nGap, POINT* lpptTarget);

/////////////////////////////////////////////////////////////////////////////////////////////////////
	VOID			GetScrnPosFromTilePos(SHORT shTileX, SHORT shTileY, SHORT& shScrnX, SHORT& shScrnY);
	VOID			GetTilePosFromScrnPos(SHORT shScrnX, SHORT shScrnY, SHORT& shTileX, SHORT& shTileY);

	BYTE			CalcDirection16(WORD wFireTileX, WORD wFireTileY, WORD wDestTileX, WORD wDestTileY);
	BYTE			CalcDirection8(WORD wFireTileX, WORD wFireTileY, WORD wDestTileX, WORD wDestTileY);


//  ���� Ÿ�Ͽ� ���� �ʼӼ� ��� �Լ���.
	BYTE			GetTileAttribute(INT nX, INT nY);
	BYTE			GetEventNum(INT nX, INT nY);
//	BOOL			GetDoorState(INT nX, INT nY);

	INT				GetDoor(INT nX, INT nY);
	VOID			OpenDoor(INT nX, INT nY, INT nIdx);
	VOID			CloseDoor(INT nX, INT nY, INT nIdx);
	INT				GetDoorImgIdx(INT nX, INT nY);
	BOOL			IsDoorOpen(INT nX, INT nY);

	LIGHTINFO		GetTileLightInfo(INT nX, INT nY);
//	VOID			SetDoorState(BYTE bIndex, BOOL bDoorOpen);
	VOID			SetAniTileFrame(INT nLoopTime);
};


#endif //_MAPHANDLER_
























//	VOID			DrawOneCellObjTile(INT nX, INT nY);
//	BOOL			DrawOneCellOverObjTile(INT nX, INT nY);

