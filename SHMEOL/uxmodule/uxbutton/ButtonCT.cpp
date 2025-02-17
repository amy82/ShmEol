// MyClass.cpp : implementation file
//

#include "stdafx.h"
//#include "OwnerDrawButton.h"
#include "ButtonCT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonCT

CButtonCT::CButtonCT()
{
	_selected = false;
	_grident = true;// false;
	FontSize = 16;
	state = 0;
	FontBold = FW_NORMAL;
	m_Font.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
}

CButtonCT::~CButtonCT()
{
}


BEGIN_MESSAGE_MAP(CButtonCT, CButton)
	//{{AFX_MSG_MAP(CButtonCT)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonCT message handlers
void CButtonCT::btStateChange(int _state)
{
	state = _state;
	Invalidate();
}
void CButtonCT::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);		//Get device context object
	CRect rt;
	rt = lpDrawItemStruct->rcItem;		//Get button rect
    //------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------
	//dc.FillSolidRect(rt, RGB(255, 255, 255));		//버튼 테두리 배경
	if (_grident)
	{
		DrawGradientRect(&dc, rt);
	}else
	{
		DrawColorRect(&dc, rt);
	}
	FontSet(&dc, rt);
	//------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------
	UINT state = lpDrawItemStruct->itemState;	//Get state of the button
	if ( (state & ODS_SELECTED) )		// If it is pressed
	{
		dc.DrawEdge(rt,EDGE_SUNKEN,BF_RECT);    // Draw a sunken face
	}
	else
	{
		dc.DrawEdge(rt,EDGE_RAISED,BF_RECT);	// Draw a raised face
	}
	if ( (state & ODS_FOCUS ) )       // If the button is focused
	{
		// Draw a focus rect which indicates the user 
		// that the button is focused
		int iChange = 1;
		rt.top += iChange;
		rt.left += iChange;
		rt.right -= iChange;
		rt.bottom -= iChange;
		dc.DrawFocusRect(rt);
	}
	dc.Detach();
}
void CButtonCT::FontSet(CDC *pDC, CRect rt)
{
	pDC->SetBkMode(TRANSPARENT);//글자색 배경 투명
	if (state == 3)
	{
		pDC->SetTextColor(RGB(20, 20, 20));		// Set the color of the caption to be yellow
	}
	else
	{
		pDC->SetTextColor(RGB(255, 255, 150));		// Set the color of the caption to be yellow
	}
	

	CString strTemp="";

	GetWindowText(strTemp);		// Get the caption which have been set
	CFont Font;
	CFont* pOldFont;
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = FontSize;			//폰트 사이즈
	lf.lfWeight = FontBold;//(일반 : 400 FW_NORMAL, BOLD : 700 FW_BOLD 정도)
	Font.CreateFontIndirectA(&lf);

	pOldFont = pDC->SelectObject(&Font);
	pDC->DrawText(strTemp, rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		// Draw out the caption

	//m_Font.CreateFont(FontSize, FontSize, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, strTemp);
	Font.DeleteObject();
}
void CButtonCT::DrawColorRect(CDC *pDC, CRect rt)
{
	COLORREF _BtnColor;
	switch (state)
	{
	case 0:		//기본상태
		_BtnColor = RGB(0, 0, 0);
		break;
	case 1:		//선택상태
		_BtnColor = RGB(30, 30, 90);
		break;
	case 2:

		break;
	case 3:
		//ver view
		_BtnColor = RGB(50, 150, 50);
		break;
	case 100:
		//_BtnColor = MESSAGE_BTN_COLOR;// RGB(178, 34, 34);//메세지창 버튼색
		break;
	default:
		_BtnColor = RGB(0, 0, 0);
		break;
	}
	CRect oldRt;
	oldRt = rt;
	
	/*int Gap = 3;
	rt.left = rt.left + Gap;
	rt.right = rt.right - Gap;
	rt.top = rt.top + Gap;
	rt.bottom = rt.bottom - Gap;*/

	pDC->FillSolidRect(rt, _BtnColor);		//Fill button with blue color
											////dc.Draw3dRect(&rt, RGB(0, 250, 0), RGB(200, 0, 0));
	rt = oldRt;
}
void CButtonCT::DrawGradientRect(CDC *pDC , CRect rt)
{
	/*COLORREF cRight;
	RGBTRIPLE aaa;
	aaa.rgbtBlue = 111;
	TRIVERTEX data[2];
	GRADIENT_RECT draw_rect;
	data[0].x = rt.left;
	data[0].y = rt.top;

	data[0].Red = 150 << 8;//255를 16진수로 변경하면 oxFF , 그레서 0xff00으로넣어줌
	data[0].Green = 0 << 8;
	data[0].Blue = 150 << 8;
	data[0].Alpha = 0x0000;

	data[1].x = rt.right;
	data[1].y = rt.bottom;

	data[1].Red = 5 << 8;
	data[1].Green = 0 << 8;
	data[1].Blue = 50 << 8;
	data[1].Alpha = 0x0000;
	draw_rect.UpperLeft = 0;
	draw_rect.LowerRight = 1;

	
	COLORREF dwTemp;
	COLOR16 kkk;
	BYTE KKK = 0xaa;
	COLORREF c1 = RGB(240, 248, 255); // AliceBlue

	*/
	TRIVERTEX data[2];
	int r = 0, g = 0, b = 0;
	switch (state)
	{
	case 0:		//기본상태
		r = 59, g = 151, b = 154;
		break;
	case 1:		//선택상태
		r = 254, g = 132, b = 125;
		
		break;
	case 2:
		r = 170, g = 230, b = 170;
		break;
	case 3:
		//_BtnColor = RGB(50, 150, 50);
		r = 150, g = 250, b = 150;
		break;
	case 10:	//양품,불량 배출 버튼 기본
		r = 150, g = 100, b = 150;
		break;
	case 11:	//양품,불량 배출 버튼 ON
		r = 255, g = 196, b = 50;
		break;
	case 100://팝업 메뉴 버튼
		r = 100, g = 50, b = 50;
		break;
	case 150:	//방향키 버튼
		r = 163, g = 158, b = 196;
		break;
	case 200:		//기본상태
		r = 100, g = 100, b = 100;
		break;
	case 201:		//선택상태
		r = 108, g = 154, b = 205;
		break;
	case 202:		//선택상태
		r = 200, g = 150, b = 150;
	case 300:		//Key Pad 버튼
		r = 66, g = 146, b = 176;
		break;
	}
	data[0] = { rt.left,    rt.top,   RGB_Rtn(r , true),  RGB_Rtn(g , true),    RGB_Rtn(b , true),    0x0000 };
	data[1] = { rt.right,  rt.bottom, RGB_Rtn(r , false), RGB_Rtn(g , false),   RGB_Rtn(b , false),   0x0000 };
	//data[0] = { rt.left,     rt.top,     51 << 8,  102 << 8,   51 << 8,   0x0000 };
	//data[1] = { rt.right,    rt.bottom,  255 << 8,  255 << 8,   0 << 8,   0x0000 };
	//{ rt.right,    rt.bottom,   0x2000,   0x0200,   0x0200,   0x0000 },
	GRADIENT_RECT draw_rect;
	draw_rect.UpperLeft = 0;
	draw_rect.LowerRight = 1;
	pDC->GradientFill(data, 2, &draw_rect, 1, GRADIENT_FILL_RECT_V);
}
//void CEMCHotButton::DrawGradientRect (CDC *pDC, CRect r, COLORREF cLeft, COLORREF cRight, BOOL bVertical)
COLOR16 CButtonCT::RGB_Rtn(int value , bool before)
{
	COLOR16 temp;
	int valueTemp = value;
	if (!before)
	{
		valueTemp -= 50;
	}
	
	temp = (COLOR16(COLOR16(GetRValue(valueTemp)) << 8));
	return temp;
}