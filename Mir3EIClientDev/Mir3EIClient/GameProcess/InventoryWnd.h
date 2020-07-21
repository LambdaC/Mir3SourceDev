#ifndef _INVENTORYWND_H
#define _INVENTORYWND_H


#pragma pack(1)
typedef struct tagITEMSET
{
	BOOL	bSetted;
	CItem	xItem;
}ITEMSET, *LPITEMSET;
typedef struct tagCOMMONITEMSET
{
	BOOL	bSetted;					// �������� ���õǾ������� ����.
	BOOL	bWaitResponse;				// ���� �������� �԰ų�, ����Ǿ ������ ������ ��ٸ������� ����.
	BOOL	bIsEquipItem;				// ���� �������� ����â���κ��� �Դ����� ����.
	BOOL	bIsBeltItem;				// ���� �������� ��Ʈâ���κ��� �Դ����� ����.
	BOOL	bIsHideItem;				// ���콺������ �������� �����ٰ��ΰ�?.
	CItem	xItem;						// ������.
}COMMONITEMSET, *LPCOMMONITEMSET;
#pragma pack(8)


class CInventoryWnd : public CGameWnd
{ 
protected:
	INT			m_nStartLineNum;					// item��ʾ�ӵڼ��п�ʼ
	RECT		m_rcInvenCell[_INVEN_MAX_CELL];		// Invent item rect.
	RECT		m_rcBeltCell[_BELT_MAX_CELL];		// Belt item rect


	CGameBtn	m_xInventoryBtn[_MAX_INVEN_BTN];

	CScrlBar	m_xInvenScrlBar;

public:
	ITEMSET		m_stInventoryItem[_MAX_INVEN_ITEM];
	ITEMSET		m_stBeltItem[_MAX_BELT_ITEM];

	RECT		m_rcBeltWnd;						// Belt ����
public:
	CInventoryWnd();
	~CInventoryWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateInventoryWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowInventoryWnd();
	VOID	ShowItemStatus(LPCLIENTITEMRCD pstItemInfo);
	VOID	ShowInvenItemState();
	VOID	SetInvenBtnInit();
	VOID	SetInventItemNum(INT nMakeIndex, BYTE bNum);
public:
	BOOL	CheckItemPos(CHAR* szName);
	BOOL	SaveItemPos(CHAR* szName);

	VOID	DeleteBeltItem(INT nBeltInventoryNum);
	VOID	DeleteInvenItem(INT nInventoryNum);
	VOID	DeleteInvenItem(INT nMakeIndex, CHAR* szName);
	VOID	DeleteAllBeltItem();
	VOID	DeleteAllInvenItem();

	BOOL	AddInvenItem(CItem xItem, INT nInvenNum, BOOL bUseInvenNum = TRUE);
	BOOL	AddBeltItem(CItem xItem, INT nBeltNum, BOOL bUseBeltNum = TRUE);

	INT		GetInvenNum(POINT ptMouse);
	INT		GetBeltNum(POINT ptMouse);

	BOOL	ExtractInvenItem(CItem* pxItem, INT nInventoryNum);
	BOOL	ExtractBeltItem(CItem* pxItem, INT nBeltInventoryNum);

	VOID	ChangeInvenWithCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	ChangeBeltWithCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);

	VOID	SetCommonFromInven(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetCommonFromBelt(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);

	VOID	SetInvenFromCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetBeltFromCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);

	VOID	AddNewBeltItem(LPCOMMONITEMSET pstCommonItemSet);


	BOOL	OnKeyUp(LPCOMMONITEMSET pstCommonItemSet, WPARAM wParam, LPARAM lParam);
	BOOL	OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
	VOID	OnScrollDown();
	VOID	OnScrollUp();

	VOID	SetBeltRect(INT l, INT t, INT r, INT b) { SetRect(&m_rcBeltWnd, l, t, r, b); }
};



#endif // _INVENTORYWND_H