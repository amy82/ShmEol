#pragma once

class UXStatic : public CStatic
{
protected:
	DECLARE_MESSAGE_MAP()

public:
	UXStatic();
	virtual ~UXStatic();
	// make the background transparent (or if ATransparent == true, restore the previous background color)
	void setTransparent(bool ATransparent = true);
	// set background color and make the background opaque
	void SetBackgroundColor(COLORREF);
	void SetTextColor(COLORREF);

protected:
	HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

private:
	bool MTransparent = true;
	COLORREF MBackgroundColor = RGB(100, 100, 100);  // default is white (in case someone sets opaque without setting a color)
	COLORREF MTextColor = RGB(10, 10, 10);  // default is black. it would be more clean 
										 // to not use the color before set with SetTextColor(..), but whatever...
public:
	void SetTextSet(int size);
};