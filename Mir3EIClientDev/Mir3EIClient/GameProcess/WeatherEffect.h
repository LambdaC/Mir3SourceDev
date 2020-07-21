#ifndef _CWEATHER_H
#define _CWEATHER_H

#define _MIST_STATE_START 0


class CMist
{
public:
	BOOL	m_bActive;
	BYTE	m_bMistState;	

	D3DVERTEX m_avBillboard[4];
	D3DVECTOR m_vTrans;
	D3DVECTOR m_vScale;	

private:

public:
	CMist();
	~CMist();
	BOOL Create();			// �Ȱ� ����.	
	VOID Init();			// �Ȱ� ���� �ʱ�ȭ.
	VOID Destory();			// �ؽ������ �޸�����.
	HRESULT DrawMist();
	VOID ProgressMist();	// �Ȱ� ����.(�Ȱ����۽���, �Ȱ�����, �Ȱ������������ ���� �ٸ���.)
};

/*
class CRain
{
public:
	BOOL	m_bActive;
	D3DVERTEX m_avBillboard[4];
	CParticle m_xParticles;

private:

public:
	CRain();
	~CRain();
	BOOL Create();			
	VOID Init();			
	VOID Destory();			
	HRESULT DrawRain();
	VOID ProgressRain();	
};


class CSnow
{
public:
	BOOL	m_bActive;
	D3DVERTEX m_avBillboard[4];
	CParticle m_xParticles;

private:

public:
	CSnow();
	~CSnow();
	BOOL Create();			
	VOID Init();			
	VOID Destory();			
	HRESULT DrawSnow();
	VOID ProgressSnow();	
};
*/
 
class CAirWave
{
#define _MAX_X	276
#define _MAX_Y	185
#define _CURR	0
#define _NEW	1
#define _DAMP	4
public:
	BYTE	m_bDispLut[512];

	BYTE	m_bCurr, m_bNew;

public:
	CAirWave();
	~CAirWave();
	VOID	InitAirWave();
	VOID	UpdateAirWave();
	VOID	DropAirWaveMap(INT nX, INT nY, INT nW, INT nMulFactor);
	VOID	RenderAirWave();
};

#endif // _CWEATHER_H