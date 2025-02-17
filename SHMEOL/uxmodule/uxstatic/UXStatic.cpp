// MyClass.cpp : implementation file
//

#include "stdafx.h"
//#include "OwnerDrawButton.h"
#include "UXStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UXStatic

UXStatic::UXStatic()
{
	
}

UXStatic::~UXStatic()
{
}



/////////////////////////////////////////////////////////////////////////////
// CButtonCT message handlers
void UXStatic::setTransparent(bool ATransparent)
{
	MTransparent = ATransparent;
	Invalidate();
}

void UXStatic::SetBackgroundColor(COLORREF AColor)
{
	

	MBackgroundColor = AColor;
	MTransparent = false;
	Invalidate();
}

void UXStatic::SetTextSet(int size)
{
	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = size;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, "±¼¸²");
	fnt.CreateFontIndirect(&lf);
	this->SetFont(&fnt);
	
	fnt.Detach();
	//
	//
	this->ModifyStyle(0, SS_CENTER | SS_CENTERIMAGE);
	Invalidate();
}
void UXStatic::SetTextColor(COLORREF AColor)
{
	MTextColor = AColor;
	Invalidate();
}

BEGIN_MESSAGE_MAP(UXStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

HBRUSH UXStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	//pDC->SetTextAlign(TA_CENTER | TA_TOP);
	pDC->SetTextColor(MTextColor);
	pDC->SetBkMode(TRANSPARENT);  // we do not want to draw background when drawing text. 
								  // background color comes from drawing the control background.
	if (MTransparent)
		return nullptr;  // return nullptr to indicate that the parent object 
						 // should supply the brush. it has the appropriate background color.
	else
		return (HBRUSH)CreateSolidBrush(MBackgroundColor);  // color for the empty area of the control
}