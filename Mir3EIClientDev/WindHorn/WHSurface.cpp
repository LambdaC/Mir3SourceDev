/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/



#include "stdafx.h"
#include "WHEngine.h"



/******************************************************************************************************************

	�Լ��� : CWHSurface::ReleaseSurface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHSurface::ReleaseSurface()
{
	if ( m_pDDS )
	{
		m_pDDS->Release();
		m_pDDS = NULL;

		return TRUE;
	}

	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CWHSurface::CreateOffScreenSurface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPDIRECTDRAW7 pDD
	         DWORD dwXSize
	         DWORD dwYSize
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHSurface::CreateOffScreenSurface(LPDIRECTDRAW7 pDD, DWORD dwXSize, DWORD dwYSize) 
{
	HRESULT					hr;
	DDSURFACEDESC2			ddsd;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize			= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth		= dwXSize;
	ddsd.dwHeight		= dwYSize;

	hr = pDD->CreateSurface(&ddsd, &m_pDDS, NULL);

	if ( hr != DD_OK )	return FALSE;

	return TRUE;
}



/******************************************************************************************************************

	�Լ��� : CWHSurface::CopyImageToSurface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : DWORD dwSrcWidth
	         DWORD dwSrcHeight
	         WORD* pwSrc
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHSurface::CopyImageToSurface(DWORD dwSrcWidth, DWORD dwSrcHeight, WORD* pwSrc)
{
	DDSURFACEDESC2			ddsd;
	WORD*					pwdDst = NULL;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize	= sizeof(DDSURFACEDESC2);

	if (m_pDDS->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) == DD_OK)
	{
		pwdDst = (WORD*)ddsd.lpSurface;

		CopyMemory(pwdDst, pwSrc, dwSrcWidth * dwSrcHeight * sizeof(WORD));

		m_pDDS->Unlock(NULL);

		DDCOLORKEY              ddck;
		ddck.dwColorSpaceLowValue =  RGB( 0,  0,  0);
		ddck.dwColorSpaceHighValue = RGB(10, 10, 10);
		m_pDDS->SetColorKey(DDCKEY_SRCBLT, &ddck);

		return TRUE;
	}

	return FALSE;
}
