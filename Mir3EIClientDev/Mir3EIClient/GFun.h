#ifndef _GFUN_H_
#define _GFUN_H_



// ���� Class���� ���� �ִ� �Լ��� ����ü�� �������� ��Ƴ��� �����̴�.



typedef struct tagCHAT
{
	DWORD	dwFontColor;
	DWORD	dwBackColor;
	CHAR	pszChat[MAX_PATH];
}CHAT, *LPCHAT;

typedef struct tagTEXTUREFILE
{
	WORD					wFileIdx;
	WORD					wImgIdx;
	LPDIRECTDRAWSURFACE7	lpddsTextr;
}TEXTUREFILE, *LPTEXTUREFILE;




DWORD GetChatColor(BYTE bIdx);

DWORD GetUserNameColor(BYTE bIdx);

#endif // _GFUN_H_
