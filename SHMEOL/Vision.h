#pragma once

#define MAX_SYSTEM_COUNT			1
#define MAX_DIGITIZER_COUNT			1

#define MAX_HOOK_BUFF_SIZE			10

#define MAX_BAYER_SIZE				3


#define MAX_CCD_COUNT				2
#define MAX_PIXEL_CNT	50000
#define MAX_BOX_CNT		20000
#define MAX_CROSS_CNT	10000	
#define MAX_TEXT_CNT	10000
#define MAX_BOX_CNT		20000

//long MFTYPE ProcessingFunction(long lHookType, MIL_ID MilHookId, void MPTYPE* pHookData);

typedef struct STRUC_HOOK_DATA
{
	int nLiveMode;
	MIL_ID MilGrabImage;
	MIL_ID MilSmallImage;
} STRUC_HOOK_DATA;

typedef struct STRUC_MIL_PIXEL
{
	int nWidth;
	CPoint clPoint;
	COLORREF color;
} STRUC_MIL_PIXEL;

typedef struct STRUC_MIL_CROSS
{
	int nWidth;
	int nSize;
	CPoint clPoint;
	COLORREF color;
} STRUC_MIL_CROSS;

typedef struct STRUC_MIL_BOX
{
	int nWidth;
	int nStyle;
	CRect clRectBox;
	COLORREF color;
} STRUC_MIL_BOX;

typedef struct STRUC_MIL_LINE
{
	int nWidth;
	int nStyle;
	CPoint clPointStart;
	CPoint clPointEnd;
	COLORREF color;
} STRUC_MIL_LINE;

typedef struct STRUC_MIL_TEXT
{
	TCHAR szFontName[SIZE_OF_100BYTE];
	TCHAR szText[SIZE_OF_1K];
	CPoint clPoint;
	CPoint clPointSize;
	COLORREF color;
} STRUC_MIL_TEXT;

class CMilDrawPixel
{
public:
	CMilDrawPixel();
	~CMilDrawPixel();

public:
	void AddList(int nPosX, int nPosY, int nWidth, COLORREF color);
	void AddList(CPoint clPoint, int nWidth, COLORREF color);
	void Draw(HDC hOverlayDC, double dZoomX, double dZoomY);
	void RemoveAll() { m_clArrayPixel.RemoveAll(); };

private:
	CArray<STRUC_MIL_PIXEL, STRUC_MIL_PIXEL&> m_clArrayPixel;
};


class CMilDrawCross
{
public:
	CMilDrawCross();
	~CMilDrawCross();

public:
	void AddList(int nPosX, int nPosY, int nSize, int nWidth, COLORREF color);
	void AddList(CPoint clPoint, int nSize, int nWidth, COLORREF color);
	void Draw(HDC hOverlayDC, double dZoomX, double dZoomY);
	void RemoveAll() { m_clArrayCross.RemoveAll(); };

private:
	CArray<STRUC_MIL_CROSS, STRUC_MIL_CROSS&> m_clArrayCross;
};

class CMilDrawBox
{
public:
	CMilDrawBox();
	~CMilDrawBox();

public:
	void AddList(int nLeft, int nTop, int nRight, int nBottom, int nWidth, int nStyle, COLORREF color);
	void AddList(CRect clRect, int nWidth, int nStyle, COLORREF color);
	void Draw(HDC hOverlayDC, double dZoomX, double dZoomY);
	void RemoveAll() { m_clArrayBox.RemoveAll(); };

private:
	CArray<STRUC_MIL_BOX, STRUC_MIL_BOX&> m_clArrayBox;
};

class CMilDrawLine
{
public:
	CMilDrawLine();
	~CMilDrawLine();

public:
	void AddList(int nStartX, int nStartY, int nEndX, int nEndY, int nWidth, int nStyle, COLORREF color);
	void AddList(CPoint clPointStart, CPoint clPointEnd, int nWidth, int nStyle, COLORREF color);
	void Draw(HDC hOverlayDC, double dZoomX, double dZoomY);
	void RemoveAll() { m_clArrayLine.RemoveAll(); };

private:
	CArray<STRUC_MIL_LINE, STRUC_MIL_LINE&> m_clArrayLine;
};

class CMilDrawText
{
public:
	CMilDrawText();
	~CMilDrawText();

public:
	void AddList(int nPosX, int nPosY, int nSizeX, int nSizeY, TCHAR* szText, TCHAR* szFontName, COLORREF color);
	void AddList(CPoint clPoint, int nSizeX, int nSizeY, TCHAR* szText, TCHAR* szFontName, COLORREF color);
	void Draw(HDC hOverlayDC, double dZoomX, double dZoomY);
	void RemoveAll() { m_clArrayText.RemoveAll(); };

private:
	CArray<STRUC_MIL_TEXT, STRUC_MIL_TEXT&> m_clArrayText;
};

//class CElemText
//{
//public:
//	int iCnt;
//	CPoint p[MAX_TEXT_CNT];
//	CPoint s[MAX_TEXT_CNT];
//	CString str[MAX_TEXT_CNT];
//	CString FontName[MAX_TEXT_CNT];
//	COLORREF c[MAX_TEXT_CNT];
//
//	CElemText() { iCnt = 0; }
//	~CElemText() {}
//
//	void addList(int iPosX, int iPosY, CString Str, COLORREF color, int iSizeX, int iSizeY, CString FontStr);
//	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
//};

class CElemEllipse
{
public:
	int iCnt;
	int iStyle[MAX_BOX_CNT];
	CPoint cp1[MAX_BOX_CNT];
	CPoint cp2[MAX_BOX_CNT];
	COLORREF c[MAX_BOX_CNT];

	CElemEllipse() { iCnt = 0; }
	~CElemEllipse() {}

	void addList(CPoint pos1, CPoint pos2, int iLineStyle, COLORREF c);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};

class CElemPixel
{
public:
	int iCnt;
	CPoint p[MAX_PIXEL_CNT];
	COLORREF c[MAX_PIXEL_CNT];


	CElemPixel() { iCnt = 0; }
	~CElemPixel() {}

	void addList(int iPosX, int iPosY, COLORREF color);
	void addList(CPoint Pos, COLORREF color);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};

class CElemCross
{
public:
	int iCnt;
	int iSize[MAX_CROSS_CNT];
	CPoint p[MAX_CROSS_CNT];
	COLORREF c[MAX_CROSS_CNT];


	CElemCross() { iCnt = 0; }
	~CElemCross() {}

	void addList(int iPosX, int iPosY, int w, COLORREF color);
	void addList(CPoint Pos, int w, COLORREF color);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};

class CElemBox
{
public:
	int iCnt;
	int iStyle[MAX_BOX_CNT];
	CRect r[MAX_BOX_CNT];
	COLORREF c[MAX_BOX_CNT];

	CElemBox() { iCnt = 0; }
	~CElemBox() {}

	void addList(int iLeft, int iTop, int iRight, int iBottom, int iLineStyle, COLORREF color);
	void addList(CRect rBox, int iLineStyle, COLORREF c);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY, bool largeFlag);
};

class CVision
{
public:
	CVision();
	~CVision();

public:
	bool AllocMilApplication();
	bool AllocMilSystem(int nSysIndex);
	//bool AllocMilDigitizer(int nSysIndex, int nDigIndex, TCHAR* szDcfFile, int nSizeX, int nSizeY);
	bool AllocMilDigitizer(int nSysIndex, int nDigIndex);
	void CloseViion();

	bool AllocMilCamBuffer(int nSysIndex, int nDigIndex, int nCamIndex, int nCamCount);
	//bool AllocMilColorBuffer(int nSysIndex, int nDigIndex, int nCamIndex, int nCamCount);
	bool AllocMilCcdBuffer(int nSysIndex, int nIndex, int nSizeX, int nSizeY);
	bool AllocMilDefectBuffer(int nSysIndex, int nIndex, int nSizeX, int nSizeY);
	bool AllocMil2DBuffer(int nSysIndex, int nDigIndex, int nCamIndex, int nCamCount);

	bool AllocMilDisplay(int nSysIndex, int nCamIndex, HWND hWnd);
	bool AllocMilCamDisplay(int nSysIndex, int nCamIndex, HWND hWnd);
	
	bool AllocInspBuff(int nSysIndex, int nSizeX, int nSizeY);
	bool AllocInspDisplay(int nSysIndex, int nType, double dZoomFac, HWND hWnd);
	void DrawOverlayOCResult();
	void DrawOverlayDefectResult();

	bool CalcSingleMarkAlign(int nCamIndex, int nNo, int nCount, CDMotor& clDMotor, CDMPoint clDPt);
	void DrawOverlayFindMark(int nCamIndex, int nNo, STRUC_MARK_POS stMarkPos, bool bFindOk);

	void EnableOverlay(int nSysIndex, int nDispIndex);
	void EnableCamOverlay(int nSysIndex, int nDispIndex);
	void ClearOverlay(int nUnit , int DisplayMode = VIDEO_CCD);
	void DrawOverlayAll(int nUnit, int DisplayMode = VIDEO_CCD);
	//
	void DrawOverlayBox(int nUnit, int nCamIndex, CRect clRect, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	void DrawOverlayBox(int nUnit, int nCamIndex, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	void DrawMOverlayBox(int nUnit, int nCamIndex, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, BOOL bRealDraw = TRUE, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);	//! Overlay 네모 추가
	void DrawMOverlayBox(int nUnit, int nCamIndex, CRect clRect, COLORREF color, int nWid, BOOL bRealDraw = TRUE, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);

	void DrawOverlayCross(int nUnit, int nCamIndex, CPoint clPointPos, int nWdt, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	void DrawOverlayCross(int nUnit, int nCamIndex, int nX, int nY,    int nWdt, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);

	void DrawMOverlayCross(int nUnit, int nCamIndex, int nX, int nY,    int nLength, COLORREF color, int nWid, BOOL bRealDraw = TRUE, int nStyles = PS_SOLID);					//! Overlay Cross 추가
	void DrawMOverlayCross(int nUnit, int nCamIndex, CPoint clPointPos, int nLength, COLORREF color, int nWid, BOOL bRealDraw = TRUE, int nStyles = PS_SOLID);
	//

	void DrawOverlayText(int nCamIndex, CPoint clPoint, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nFs_x, int nFs_y, int DisplayMode = VIDEO_CCD);
	void DrawOverlayText(int nCamIndex, int nX, int nY, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nFs_x, int nFs_y, int DisplayMode = VIDEO_CCD);


	void DrawOverlayFillBox(int nCamIndex, CPoint clPointPos, COLORREF color, int nSizeX, int nSizeY, int DisplayMode = VIDEO_CCD);
	void DrawOverlayFillBox(int nCamIndex, int nX, int nY, COLORREF color, int nSizeX, int nSizeY, int DisplayMode = VIDEO_CCD);
	void DrawOverlayCircle(int nCamIndex, CRect clRect, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	void DrawOverlayCircle(int nCamIndex, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	
	void DrawOverlayLine(int nCamIndex, CPoint clPointStart, CPoint clPointEnd, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	void DrawOverlayLine(int nCamIndex, int nX1, int nY1, int nX2, int nY2, COLORREF color, int nWid, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	void DrawOverlayPixel(int nCamIndex, CPoint clPointPos, COLORREF color, int nWid, int DisplayMode = VIDEO_CCD);
	void DrawOverlayPixel(int nCamIndex, int nX, int nY, COLORREF color, int nWid, int DisplayMode = VIDEO_CCD);

	void DrawMOverlayText(int nCamIndex, int nX, int nY, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nSx, int nSy, BOOL bRealDraw = TRUE, int DisplayMode = VIDEO_CCD);				//! Overlay 텍스트 추가
	void DrawMOverlayText(int nCamIndex, CPoint clPointPos, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nSx, int nSy, BOOL bRealDraw = TRUE, int DisplayMode = VIDEO_CCD);

	void DrawMOverlayPixel(int nCamIndex, int nX, int nY, COLORREF color, int nWid, BOOL bRealDraw = TRUE);														//! Overlay 점 추가
	void DrawMOverlayPixel(int nCamIndex, CPoint clPointPos, COLORREF color, int nWid, BOOL bRealDraw = TRUE);
	void DrawMOverlayLine(int nCamIndex, int nX1, int nY1, int nX2, int nY2, COLORREF color, int nWid, BOOL bRealDraw = TRUE, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);			//! Overlay 선 추가	
	void DrawMOverlayLine(int nCamIndex, CPoint clPointStart, CPoint clPointEnd, COLORREF color, int nWid, BOOL bRealDraw = TRUE, int nStyles = PS_SOLID, int DisplayMode = VIDEO_CCD);
	
	void DrawMOverlayCircle(int nCamIndex, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, int nStyles = PS_SOLID);						//! Overlay 원 추가
	void DrawMOverlayCircle(int nCamIndex, CRect clRect, COLORREF color, int nWid, int nStyles = PS_SOLID);
	
	void SaveSfrImage(int nUnit, unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi);
	void SaveFovImage(int nUnit, unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi);
    
public:
	MIL_ID m_MilApplication;
	MIL_ID m_MilSystem[MAX_SYSTEM_COUNT];
	//MIL_ID m_MilDigitizer[MAX_SYSTEM_COUNT][MAX_DIGITIZER_COUNT];
	MIL_ID m_MilDigitizer[MAX_UNIT_COUNT][MAX_DIGITIZER_COUNT];
	int m_nGrabMode[MAX_DIGITIZER_COUNT];



	MIL_ID m_MilImage[MAX_DIGITIZER_COUNT];

	

	MIL_ID m_MilProcImage[MAX_CCD_COUNT];
	MIL_ID m_MilChildImage[MAX_CCD_COUNT];
	MIL_ID m_MilSmallImage[MAX_CCD_COUNT];


	//Align Camera
	MIL_ID m_MilGrabImage[MAX_UNIT_COUNT][MAX_CAM_COUNT];
	MIL_ID m_MilGrabImageChild[MAX_UNIT_COUNT][MAX_CAM_COUNT];
	MIL_ID MilCamSmallImage[MAX_UNIT_COUNT][MAX_CAM_COUNT];
	MIL_ID MilCamSmallImageChild[MAX_UNIT_COUNT][MAX_CAM_COUNT];
	MIL_ID m_MilMarkSmallImage[MAX_UNIT_COUNT][MAX_CAM_COUNT];
	MIL_ID m_MilCamDisplay[MAX_UNIT_COUNT][MAX_CAM_COUNT];
	MIL_ID m_MilCamOverlay[MAX_UNIT_COUNT][MAX_CAM_COUNT];


	MIL_INT m_nMilCamTransparent[MAX_CCD_COUNT][MAX_CAM_COUNT];
	MIL_INT m_nMilTransparent[MAX_CCD_COUNT];
	MIL_INT m_nMilDefectTransparent[MAX_CCD_COUNT];
	MIL_INT m_nMilSizeX[MAX_DIGITIZER_COUNT];
	MIL_INT m_nMilSizeY[MAX_DIGITIZER_COUNT];
	MIL_INT m_nMilBand[MAX_DIGITIZER_COUNT];
	
	

	MIL_ID m_MilCcdGrabImage[MAX_UNIT_COUNT];
	MIL_ID m_MilCcdProcImage[MAX_UNIT_COUNT];
	MIL_ID m_MilCcdProcChild[MAX_UNIT_COUNT][3];
	MIL_ID m_MilCcdBayerImage[MAX_UNIT_COUNT][MAX_BAYER_SIZE];
	MIL_ID m_MilWBCoefficients[MAX_UNIT_COUNT];


	IplImage* m_pCcdGrabImg[MAX_UNIT_COUNT][MAX_BAYER_SIZE];
	long m_lBuffAttribute[MAX_DIGITIZER_COUNT];
	double m_dZoomFac[MAX_CCD_COUNT];
	unsigned char* m_pImgBuff[MAX_UNIT_COUNT][3];
	int m_nGrabIndex[MAX_UNIT_COUNT];
	int m_nCvtColorReadyIndex[MAX_UNIT_COUNT];
	int m_nCvtColorIndex[MAX_UNIT_COUNT];

	MIL_ID m_MilDisplay[MAX_UNIT_COUNT];
	MIL_ID m_MilOverlay[MAX_UNIT_COUNT];

	MIL_ID MilDefectDisplayImage[MAX_UNIT_COUNT];
	MIL_ID	MilDefectImage[MAX_UNIT_COUNT];
	MIL_ID	MilDefectOverlayImage[MAX_UNIT_COUNT];
	

	MIL_ID m_MilOCImage;
	MIL_ID m_MilOCDisplay;
	MIL_ID m_MilOCOverlay;
	MIL_INT m_nMilTransparentOC;

	MIL_ID m_MilDefectImage;
	MIL_ID m_MilDefectDisplay;
	MIL_ID m_MilDefectOverlay;
	MIL_INT m_nMilTransparentDefect;

	MIL_ID MilOptImage;
	
    MIL_ID MilSfrTargetImage[MAX_UNIT_COUNT];

    MIL_ID      MilTempImage[MAX_UNIT_COUNT];
    MIL_ID		ChartCenterPatternImage[MAX_UNIT_COUNT];			        /* 중심점 확인용 패턴매칭 마크 모델 */
    MIL_ID		ChartCenterPatternResult[MAX_UNIT_COUNT];			        /* 중심점 확인용 패턴매칭 결과 */

    MIL_ID		FieldPatternImage[MAX_UNIT_COUNT][MAX_LAST_INSP_COUNT];		/* 필드 ROI용 패턴매칭 마크 모델 */
    MIL_ID		FieldPatternResult[MAX_UNIT_COUNT][MAX_LAST_INSP_COUNT];	/* 필드 ROI용 패턴매칭 결과 */

	//IplImage* m_pDefectInspImage;
	//int* m_pDefectTempArea;

	CElemPixel  pixellist[MAX_UNIT_COUNT];
	CElemBox	boxlist[MAX_UNIT_COUNT];
	CElemCross	crosslist[MAX_UNIT_COUNT];
	//CElemText	textlist[MAX_UNIT_COUNT];
	CElemEllipse ellipselist[MAX_UNIT_COUNT];
	//STRUC_HOOK_DATA m_stHookData[MAX_CAM_COUNT];

	CMilDrawPixel m_clMilDrawPixel[MAX_CCD_COUNT];
	CMilDrawCross m_clMilDrawCross[MAX_CCD_COUNT];
	CMilDrawBox m_clMilDrawBox[MAX_CCD_COUNT];
	CMilDrawLine m_clMilDrawLine[MAX_CCD_COUNT];
	CMilDrawText m_clMilDrawText[MAX_CCD_COUNT];
};

