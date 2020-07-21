/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/



#ifndef _CMAGIC_H
#define _CMAGIC_H



/******************************************************************************************************************

	CMagic Class
	

*******************************************************************************************************************/
class CMagic
{
private:
protected:
public:
	BYTE			m_bActiveState;							// ���� Ȱ��ȭ����.(�����Ҹ�ÿ� ���ȴ�.)
	BOOL			m_bRepeat;								// �ִϸ��̼��� �ݺ�����.
	BOOL			m_bFixed;								// ������ �̵�����.
	BYTE			m_bMagicNum;							// ������ȣ.

	CActor*			m_pxOwner;								// �����߻���ü.
	CActor*			m_pxTarget;								// �����߻簴ü.
	CMapHandler*	m_pxMap;								// ������������.

	// ��ǥ����.
	SHORT	m_shScrnX, m_shScrnY;							// ������ũ����ǥ.
	FLOAT	m_fFloatScrnX, m_fFloatScrnY;					// ������ũ����ǥ.
	SHORT	m_shTileX, m_shTileY;							// ����Ÿ����ǥ.

	SHORT	m_shFireScrnX, m_shFireScrnY;					// ����������ũ����ǥ.	
	SHORT	m_shFireTileX, m_shFireTileY;					// ��������Ÿ����ǥ.

	SHORT	m_shTargetScrnX, m_shTargetScrnY;				// ��ǥ���� ��ũ����ǥ.
	SHORT	m_shTargetTileX, m_shTargetTileY;				// ��ǥ���� Ÿ����ǥ.(��ȭ�ɼ��ִ�.)

	// ����������.
	WORD	m_wCurrDelay;									// �����ð����尪.
	WORD	m_wCurrLightDelay;
	WORD	m_wFrmDelay;									// �������� �ѱ�� ���� �����ð���.
	WORD	m_wMagicLife;									// ������ ����ǰ� �ִ� �ð�.(ms����)


	BYTE	m_bLightRadius[2];								// ���� �ʺ�.
	BYTE	m_bLightColor[2][3];							// ���� ��.
	BYTE	m_bMagicColor[3];								// ��.

	DWORD	m_dwFstFrame;									// ���� ������ ����������.
	DWORD	m_dwEndFrame;									// ���� ������ ������������.
	DWORD	m_dwCurrFrame;									// ���������尪.

	BYTE	m_bBlendType;									// ������ ����·� �׸����ΰ��� ����.
	BYTE	m_bOpacity;										// 0 - 255�ܰ�. 0�� ���� ����(����Ʈ����), 255�� ������.
	BYTE	m_bSwingCnt;									// ������ ��鸲 ������ �ش�.

	FLOAT	m_fGradient;
	INT		m_nShiftX;
	INT		m_nShiftY;
	INT		m_nDistanceX;
	INT		m_nDistanceY;
	INT		m_nPrevDistanceX;
	INT		m_nPrevDistanceY;

	BYTE	m_bDir16;
	BYTE	m_bCurrSwing;

	BOOL	m_bShowLight;

	D3DVERTEX			m_avMagic[4];
	CWHWilImageData*	m_pxMagicImg;

	INT		m_nDuplicateNum; 

	LPDIRECTDRAWSURFACE7 m_lpddsMagicTextr[60];

public:
	CMagic();
	~CMagic();

	virtual BOOL CreateMagic(BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
		                     SHORT shTargetTileX, SHORT shTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0);


	virtual VOID DestoryMagic();
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
	virtual BOOL DrawLight(CLightFog* xLightFog, INT nLoopTime);
};


// _SKILL_FIRE, _SKILL_SHOOTLIGHTEN ����.
class CMagicStream : public CMagic
{
private:
	WORD	m_wMagicStart;
	POINT	m_ptTileGap;
public:
	BOOL CreateMagic(BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
		             SHORT shTargetTileX, SHORT shTargetTileY, CActor* pxOwner, INT nTarget, WORD wStartMagicTime, POINT ptTileGap);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};


class CElecMagic : public CMagic
{
private:
	SHORT	m_shEPosX, m_shEPosY;
	BOOL	m_bArrived;

	CElec m_xElec;

public:
	virtual BOOL CreateMagic(BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
		                     SHORT shTargetTileX, SHORT shTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0);
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
};



// _SKILL_HOLYSHIELD, _SKILL_EARTHFIRE ����.
class CRepeatMagic : public CMagic
{
private:
public:
	DWORD	m_dwMagiLifeTotal;
	INT		m_nEventID;					// �̺�Ʈ�ΰ����ȴ�.

	_inline CRepeatMagic()
	{
		m_nEventID		  = 0;
		m_dwMagiLifeTotal = 0;
	}

	BOOL CreateMagic(INT nEventID, BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
	                 SHORT shTargetTileX, SHORT shTargetTileY, DWORD dwMagicLifeTotal, CActor* pxOwner = NULL, INT nTarget = 0);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};


#endif // _CMAGIC_H
