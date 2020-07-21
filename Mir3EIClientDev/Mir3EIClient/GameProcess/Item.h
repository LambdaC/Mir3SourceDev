#ifndef _CITEM_H
#define	_CITEM_H


#pragma pack(1)
//typedef struct tagSTANDARDITEM
//{
//	CHAR			szName[20];
//
//	DWORD			dwUnknown1;
//	DWORD			dwUnknown2;
//	SHORT			sUnknown3;//30
//
//	BYTE			bStdMode; //(pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3)
//							  //���ǿ��Է���belt�ϵ���Ʒ,Ҳ�ǿ���"��"����Ʒ,ħ��ˮ,�سǾ��
//	BYTE			bShape;            
//	BYTE			bWeight;           
//	BYTE			bAniCount;//34
//	
//	BYTE			sSpecialPower;           
//
//	BYTE			bNeedIdentify;
//
//	WORD			wLooks;            
//	WORD			wDuraMax;//�־� 40
//
//	WORD			wAC;			
//	WORD			wMAC;	//44		
//
//	WORD			wDC;			
//	WORD			wMC;//48			
//
//	WORD			wSC;			
//	BYTE			bNeed;             
//	BYTE			bNeedLevel; //52       
//
//	int				nUnkown4;
//	WORD			wUnkown5;
//	int				nUnkown6;
//	WORD			wUnkown7;
//
//	int				nPrice;//56
//}STANDARDITEM, *LPSTANDARDITEM;

//8/8 �������ݿ�
typedef struct tagSTANDARDITEM
{
	char		szName[20];			// ������ �̸� (õ�����ϰ�)
	char		szPrefixName[10];
	BYTE		bStdMode;          //
	BYTE		bShape;            // ���º� �̸� (ö��)
	BYTE		bWeight;           // ����
	BYTE		bAniCount;         // 1���� ũ�� �ִϸ��̼� �Ǵ� ������
	BYTE		bSource;           // ���� (0�� �⺻, 1���� ũ�� �� �ܴ���)
	BYTE		bNeedIdentify;     // $01 (���̴�Ƽ���� �� �� ��)
	WORD		wLooks;             // �׸� ��ȣ
	WORD		wDuraMax;

	WORD		wAC;				// ����
	WORD		wMAC;				// ���׷�
	WORD		wDC;				// ������
	WORD		wMC;				// ������ ���� �Ŀ�
	WORD		wSC;				// ������ ���ŷ�
	WORD		wUnkown1;
	WORD		wUnkown2;

	BYTE		bNeed;             // 0:Level, 1:DC, 2:MC, 3:SC
	BYTE		bNeedLevel;        // 1..60 level value...
	UINT		nPrice;
	WORD		wStock;
}STANDARDITEM, *LPSTANDARDITEM;

typedef struct tagCLIENTITEMRCD
{
	STANDARDITEM	stStdItem;
	int				nMakeIndex;
	WORD			nDura;
	WORD			nDuraMax;//����
	BYTE			bDrugNum;//ydq ����
	BYTE			bDrugNum2;

	BYTE			b1;
	BYTE			b2;
	BYTE			b3;
	BYTE			b4;
	BYTE			b5;
	BYTE			b6;
	BYTE			b7;
	BYTE			b8;

}CLIENTITEMRCD, *LPCLIENTITEMRCD;

typedef struct tagGROUNDITEM
{
	INT				nRecog;
	SHORT			shTileX;
	SHORT			shTileY;
	WORD			wLooks;
	CHAR			szItemName[40];
}GROUNDITEM, *LPGROUNDITEM;
#pragma pack(8)


class CItem
{ 
public:
	CItem();
	~CItem();

private:
public:
	BYTE			m_bAttr;
	SHORT			m_shCellNum;//��Ԫ��λ��
	CLIENTITEMRCD	m_stItemInfo;

protected:
public:
	BOOL		SetItem(CLIENTITEMRCD stItemInfo, SHORT shInventoryNum);
	BOOL		DrawItem(INT nX, INT nY, BYTE bItemType = _ITEM_TYPE_INVENTORY);
	VOID		ShowItemStatus(INT nX, INT nY);
public:
};



#endif //_CITEM_H