#ifndef _TYPEDEF_TEXT_H
#define _TYPEDEF_TEXT_H

typedef struct tag_CMTxtBtn
{
	COLORREF nColor;			// ���� ���¿����� ��
	COLORREF cColor;			// Click �Ǿ������� ��
	CHAR	Txt[70];			// Main���� ���̴� Txt
	CHAR	sTxt[70];			// Sub�� ���̴� Txt
	RECT	xRect;				// Top �� �׻� 0���� �ؾ���
	INT		nLinePos;			// Top �� �����Ѵ�.  Top�� �ٰ� ������ �����ӿ� ���ϼ� �׻� ��������
	CHAR	Param[70];
	BOOL	bIsClicked;
	INT		nImgID;				//itemͼƬ����
	INT		nSubMenu;
} CMTxtBtn;

typedef struct tag_CMText
{
	COLORREF	fColor;				// Text Color
	BOOL		bDrawCenter;		// DrawCenter
	INT			nPosx;				// Draw Position x
	INT			nLine;				// Draw Line indicater	:Zerobase
	CHAR*		pText;				// Text
} CMText;

#endif _TYPEDEF_TEXT_H