#include "stdafx.h"
#include "Vision.h"


//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CMilDrawPixel::CMilDrawPixel()
{

}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CMilDrawPixel::~CMilDrawPixel()
{
	m_clArrayPixel.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	Pixel 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawPixel::AddList(int nPosX, int nPosY, int nWidth, COLORREF color)
{
	STRUC_MIL_PIXEL stMilPixel;

	stMilPixel.clPoint.x = nPosX;
	stMilPixel.clPoint.y = nPosY;
	stMilPixel.nWidth = nWidth;
	stMilPixel.color = color;

	m_clArrayPixel.Add(stMilPixel);
}

//-----------------------------------------------------------------------------
//
//	Pixel 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawPixel::AddList(CPoint clPoint, int nWidth, COLORREF color)
{
	STRUC_MIL_PIXEL stMilPixel;

	stMilPixel.clPoint = clPoint;
	stMilPixel.nWidth = nWidth;
	stMilPixel.color = color;

	m_clArrayPixel.Add(stMilPixel);
}

//-----------------------------------------------------------------------------
//
//	Overlay Draw
//
//-----------------------------------------------------------------------------
void CMilDrawPixel::Draw(HDC hOverlayDC, double dZoomX, double dZoomY)
{
	STRUC_MIL_PIXEL stMilPixel;
	CDC NewDC;
	CPen clPen;
	CPen* pOldPen;

	POINT pixel;
	int nCount;
	int i;

	nCount = (int)m_clArrayPixel.GetCount();

	if (hOverlayDC != M_NULL)
	{
		if (nCount > 0)
		{
			NewDC.Attach(hOverlayDC);
			NewDC.SetBkMode(TRANSPARENT);
			NewDC.SelectStockObject(NULL_BRUSH);

			for (i = 0; i < nCount; i++)
			{
				stMilPixel = m_clArrayPixel.GetAt(i);

				clPen.CreatePen(PS_SOLID, stMilPixel.nWidth, stMilPixel.color);
				pOldPen = NewDC.SelectObject(&clPen);

				pixel.x = (long)((stMilPixel.clPoint.x * dZoomX) + 0.5);
				pixel.y = (long)((stMilPixel.clPoint.y * dZoomY) + 0.5);

				NewDC.SetPixel(pixel, stMilPixel.color);
				NewDC.SelectObject(pOldPen);
				clPen.DeleteObject();

			}

			NewDC.Detach();
		}
	}
}


//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CMilDrawCross::CMilDrawCross()
{

}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CMilDrawCross::~CMilDrawCross()
{
	m_clArrayCross.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	Cross 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawCross::AddList(int nPosX, int nPosY, int nSize, int nWidth, COLORREF color)
{
	STRUC_MIL_CROSS stMilCross;

	stMilCross.clPoint.x = nPosX;
	stMilCross.clPoint.y = nPosY;
	stMilCross.nSize = nSize;
	stMilCross.nWidth = nWidth;
	stMilCross.color = color;

	m_clArrayCross.Add(stMilCross);
}

//-----------------------------------------------------------------------------
//
//	Cross 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawCross::AddList(CPoint clPoint, int nSize, int nWidth, COLORREF color)
{
	STRUC_MIL_CROSS stMilCross;

	stMilCross.clPoint = clPoint;
	stMilCross.nSize = nSize;
	stMilCross.nWidth = nWidth;
	stMilCross.color = color;

	m_clArrayCross.Add(stMilCross);
}

//-----------------------------------------------------------------------------
//
//	Overlay Draw
//
//-----------------------------------------------------------------------------
void CMilDrawCross::Draw(HDC hOverlayDC, double dZoomX, double dZoomY)
{
	STRUC_MIL_CROSS stMilCross;
	CDC NewDC;
	CPen clPen;
	CPen* pOldPen;
	int x, y, w1, w2;
	int nCount;
	int i;

	nCount = (int)m_clArrayCross.GetCount();

	if (hOverlayDC != M_NULL)
	{
		if (nCount > 0)
		{
			NewDC.Attach(hOverlayDC);
			NewDC.SetBkMode(TRANSPARENT);
			NewDC.SelectStockObject(NULL_BRUSH);

			for (i = 0; i < nCount; i++)
			{
				stMilCross = m_clArrayCross.GetAt(i);

				clPen.CreatePen(PS_SOLID, stMilCross.nWidth, stMilCross.color);
				pOldPen = NewDC.SelectObject(&clPen);

				w1 = (long)((stMilCross.nSize * dZoomX) + 0.5);
				w2 = (long)((stMilCross.nSize * dZoomY) + 0.5);
				x = (long)((stMilCross.clPoint.x * dZoomX) + 0.5);
				y = (long)((stMilCross.clPoint.y * dZoomY) + 0.5);

				NewDC.MoveTo(x - w1, y);
				NewDC.LineTo(x + w1, y);
				NewDC.MoveTo(x, y - w2);
				NewDC.LineTo(x, y + w2);

				NewDC.SelectObject(pOldPen);
				clPen.DeleteObject();
			}

			NewDC.Detach();
		}
	}
}

//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CMilDrawBox::CMilDrawBox()
{

}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CMilDrawBox::~CMilDrawBox()
{
	m_clArrayBox.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	Box 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawBox::AddList(int nLeft, int nTop, int nRight, int nBottom, int nWidth, int nStyle, COLORREF color)
{
	STRUC_MIL_BOX stMilBox;

	stMilBox.clRectBox.left = nLeft;
	stMilBox.clRectBox.top = nTop;
	stMilBox.clRectBox.right = nRight;
	stMilBox.clRectBox.bottom = nBottom;
	stMilBox.nWidth = nWidth;
	stMilBox.nStyle = nStyle;
	stMilBox.color = color;

	m_clArrayBox.Add(stMilBox);
}

//-----------------------------------------------------------------------------
//
//	Box 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawBox::AddList(CRect clRect, int nWidth, int nStyle, COLORREF color)
{
	STRUC_MIL_BOX stMilBox;

	stMilBox.clRectBox = clRect;
	stMilBox.nWidth = nWidth;
	stMilBox.nStyle = nStyle;
	stMilBox.color = color;

	m_clArrayBox.Add(stMilBox);
}

//-----------------------------------------------------------------------------
//
//	Overlay Draw
//
//-----------------------------------------------------------------------------
void CMilDrawBox::Draw(HDC hOverlayDC, double dZoomX, double dZoomY)
{
	STRUC_MIL_BOX stMilBox;		
	int x1, x2, y1, y2;
	int nCount;
	int i;

	nCount = (int)m_clArrayBox.GetCount();

	if (hOverlayDC != M_NULL)
	{
		if (nCount > 0)
		{
			CDC NewDC;
			CPen clPen;
			CPen* pOldPen;

			NewDC.Attach(hOverlayDC);
			NewDC.SetBkMode(TRANSPARENT);
			NewDC.SelectStockObject(NULL_BRUSH);

			for (i = 0; i < nCount; i++)
			{
				stMilBox = m_clArrayBox.GetAt(i);
				
				clPen.CreatePen(stMilBox.nStyle, stMilBox.nWidth, stMilBox.color);
				pOldPen = NewDC.SelectObject(&clPen);

				x1 = (long)((stMilBox.clRectBox.left * dZoomX) + 0.5);
				x2 = (long)((stMilBox.clRectBox.right * dZoomX) + 0.5);
				y1 = (long)((stMilBox.clRectBox.top * dZoomY) + 0.5);
				y2 = (long)((stMilBox.clRectBox.bottom * dZoomY) + 0.5);

				NewDC.Rectangle(x1, y1, x2, y2);

				NewDC.SelectObject(pOldPen);
				clPen.DeleteObject();
			}

			NewDC.Detach();
		}
	}
}

//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CMilDrawLine::CMilDrawLine()
{

}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CMilDrawLine::~CMilDrawLine()
{
	m_clArrayLine.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	Line 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawLine::AddList(int nStartX, int nStartY, int nEndX, int nEndY, int nWidth, int nStyle, COLORREF color)
{
	STRUC_MIL_LINE stMilLine;

	stMilLine.clPointStart.x = nStartX;
	stMilLine.clPointStart.y = nStartY;
	stMilLine.clPointEnd.x = nEndX;
	stMilLine.clPointEnd.y = nEndY;
	stMilLine.nWidth = nWidth;
	stMilLine.nStyle = nStyle;
	stMilLine.color = color;

	m_clArrayLine.Add(stMilLine);
}

//-----------------------------------------------------------------------------
//
//	Line List 추가
//
//-----------------------------------------------------------------------------
void CMilDrawLine::AddList(CPoint clPointStart, CPoint clPointEnd, int nWidth, int nStyle, COLORREF color)
{
	STRUC_MIL_LINE stMilLine;

	stMilLine.clPointStart = clPointStart;
	stMilLine.clPointEnd = clPointEnd;
	stMilLine.nWidth = nWidth;
	stMilLine.nStyle = nStyle;
	stMilLine.color = color;

	m_clArrayLine.Add(stMilLine);
}

//-----------------------------------------------------------------------------
//
//	Overlay Draw
//
//-----------------------------------------------------------------------------
void CMilDrawLine::Draw(HDC hOverlayDC, double dZoomX, double dZoomY)
{
	STRUC_MIL_LINE stMilLine;
	CDC NewDC;
	CPen clPen;
	CPen* pOldPen;
	int x1, x2, y1, y2;	
	int nCount;
	int i;


	nCount = (int)m_clArrayLine.GetCount();
	if (hOverlayDC != M_NULL)
	{
		if (nCount > 0)
		{
			NewDC.Attach(hOverlayDC);
			NewDC.SetBkMode(TRANSPARENT);
			NewDC.SelectStockObject(NULL_BRUSH);

			for (i = 0; i < nCount; i++)
			{
				stMilLine = m_clArrayLine.GetAt(i);

				clPen.CreatePen(stMilLine.nStyle, stMilLine.nWidth, stMilLine.color);
				pOldPen = NewDC.SelectObject(&clPen);

				x1 = (long)((stMilLine.clPointStart.x * dZoomX) + 0.5);
				y1 = (long)((stMilLine.clPointStart.y * dZoomY) + 0.5);
				x2 = (long)((stMilLine.clPointEnd.x * dZoomX) + 0.5);
				y2 = (long)((stMilLine.clPointEnd.y * dZoomY) + 0.5);

				NewDC.MoveTo(x1, y1);
				NewDC.LineTo(x2, y2);

				NewDC.SelectObject(pOldPen);
				clPen.DeleteObject();
			}

			NewDC.Detach();
		}
	}
}

//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CMilDrawText::CMilDrawText()
{

}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CMilDrawText::~CMilDrawText()
{
	m_clArrayText.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	Text 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawText::AddList(int nPosX, int nPosY, int nSizeX, int nSizeY, TCHAR* szText, TCHAR* szFontName, COLORREF color)
{
	STRUC_MIL_TEXT stMilText;

	stMilText.clPoint.x = nPosX;
	stMilText.clPoint.y = nPosY;
	stMilText.clPointSize.x = nSizeX;
	stMilText.clPointSize.y = nSizeY;
	_tcscpy_s(stMilText.szText, SIZE_OF_1K, szText);
	_tcscpy_s(stMilText.szFontName, SIZE_OF_100BYTE, szFontName);
	stMilText.color = color;

	m_clArrayText.Add(stMilText);
}

//-----------------------------------------------------------------------------
//
//	Text 리스트 추가
//
//-----------------------------------------------------------------------------
void CMilDrawText::AddList(CPoint clPoint, int nSizeX, int nSizeY, TCHAR* szText, TCHAR* szFontName, COLORREF color)
{
	STRUC_MIL_TEXT stMilText;

	stMilText.clPoint = clPoint;
	stMilText.clPointSize.x = nSizeX;
	stMilText.clPointSize.y = nSizeY;
	_tcscpy_s(stMilText.szText, SIZE_OF_1K, szText);
	_tcscpy_s(stMilText.szFontName, SIZE_OF_100BYTE, szFontName);
	stMilText.color = color;

	m_clArrayText.Add(stMilText);
}

//-----------------------------------------------------------------------------
//
//	Overlay Draw
//
//-----------------------------------------------------------------------------
void CMilDrawText::Draw(HDC hOverlayDC, double dZoomX, double dZoomY)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	STRUC_MIL_TEXT stMilText;
	CDC NewDC;
	CFont clFont, *pOldFont;
	int x, y;
	int nCount;
	int i;

	nCount = (int)m_clArrayText.GetCount();
	if (hOverlayDC != M_NULL)
	{
		if (nCount > 0)
		{
			NewDC.Attach(hOverlayDC);
			NewDC.SetBkMode(TRANSPARENT);

			CBrush* pOldBrush = (CBrush*)NewDC.SelectStockObject(NULL_BRUSH);

			for (i = 0; i < nCount; i++)
			{
				stMilText = m_clArrayText.GetAt(i);

				clFont.CreateFont(stMilText.clPointSize.x, stMilText.clPointSize.y, 0, 0,
					FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, stMilText.szFontName);

				pOldFont = NewDC.SelectObject(&clFont);

				oc_red = (unsigned long)GetRValue(stMilText.color);
				oc_green = (unsigned long)GetGValue(stMilText.color);
				oc_blue = (unsigned long)GetBValue(stMilText.color);

				x = (int)((stMilText.clPoint.x * dZoomX) + 0.5);
				y = (int)((stMilText.clPoint.y * dZoomY) + 0.5);

				NewDC.SetTextColor(RGB(oc_red, oc_green, oc_blue));
				NewDC.TextOut(x, y, stMilText.szText, (MIL_INT32)MosStrlen(stMilText.szText));

				NewDC.SelectObject(pOldFont);
				clFont.DeleteObject();
			}

			NewDC.Detach();
		}
	}
}



//-----------------------------------------------------------------------------
//
//	Vision 생성자
//
//-----------------------------------------------------------------------------
CVision::CVision()
{
	int i, j;
	for (i = 0; i < MAX_DIGITIZER_COUNT; i++)
	{
		m_nGrabMode[i] = GRAB_LIVE;
	}
	m_MilApplication = M_NULL;

	for (i = 0; i < MAX_SYSTEM_COUNT; i++)
	{
		m_MilSystem[i] = M_NULL;
		m_MilImage[i] = M_NULL;
		for (j = 0; j < MAX_DIGITIZER_COUNT; j++)
		{
			m_MilDigitizer[i][j] = M_NULL;
			

		}
	}

	for (i = 0; i < MAX_CCD_COUNT; i++)
	{
		m_MilProcImage[i] = M_NULL;
		m_MilChildImage[i] = M_NULL;
		m_MilSmallImage[i] = M_NULL;
	}

	for(i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_CAM_COUNT; j++)
		{
			m_MilGrabImage[i][j] = M_NULL;
			m_MilGrabImageChild[i][j] = M_NULL;
			MilCamSmallImage[i][j] = M_NULL;
			MilCamSmallImageChild[i][j] = M_NULL;
			m_MilMarkSmallImage[i][j] = M_NULL;
			m_MilCamDisplay[i][j] = M_NULL;
			m_MilCamOverlay[i][j] = M_NULL;
		}
		m_MilDisplay[i] = M_NULL;
		MilDefectImage[i] = M_NULL;
		MilDefectDisplayImage[i] = M_NULL;
		MilDefectOverlayImage[i] = M_NULL;
		m_nGrabIndex[i] = 0;
		m_nCvtColorReadyIndex[i] = 0;
		m_nCvtColorIndex[i] = 0;

		m_MilCcdGrabImage[i] = M_NULL;
		m_MilCcdProcImage[i] = M_NULL;
		m_MilWBCoefficients[i] = M_NULL;

		for(j = 0; j < MAX_BAYER_SIZE; j++)
			m_MilCcdBayerImage[i][j] = M_NULL;

		//m_pBayerInput[i] = NULL;

        MilTempImage[i] = M_NULL;
        ChartCenterPatternImage[i] = M_NULL;
        ChartCenterPatternResult[i] = M_NULL;
		for (j = 0; j < 3; j++)
		{
			m_MilCcdProcChild[i][j] = M_NULL;

			m_pCcdGrabImg[i][j] = NULL;
            m_pImgBuff[i][j] = NULL;
            
		}
        for (j = 0; j < MAX_LAST_INSP_COUNT; j++)
        {
            FieldPatternImage[i][j] = M_NULL;
            FieldPatternResult[i][j] = M_NULL;
        }
	}
}

//-----------------------------------------------------------------------------
//
//	Vision 소멸자
//
//-----------------------------------------------------------------------------
CVision::~CVision()
{
	int i, j;

	for (i = 0; i < MAX_DIGITIZER_COUNT; i++)
	{
		m_nGrabMode[i] = GRAB_LIVE;// GRAB_SNAP;
	}

	for (i = 0; i < MAX_CCD_COUNT; i++)
	{
		if (m_MilProcImage[i] != M_NULL)
			MbufFree(m_MilProcImage[i]);

		if (m_MilChildImage[i] != M_NULL)
			MbufFree(m_MilChildImage[i]);

		if (m_MilSmallImage[i] != M_NULL)
			MbufFree(m_MilSmallImage[i]);
	}
	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_CAM_COUNT; j++)
		{
			if (m_MilGrabImage[i][j] != M_NULL)
				MbufFree(m_MilGrabImage[i][j]);

			if (MilCamSmallImage[i][j] != M_NULL)
				MbufFree(MilCamSmallImage[i][j]);

			if (MilCamSmallImageChild[i][j] != M_NULL)
				MbufFree(MilCamSmallImageChild[i][j]);

			if (m_MilMarkSmallImage[i][j] != M_NULL)
				MbufFree(m_MilMarkSmallImage[i][j]);




			if (m_MilCamDisplay[i][j] != M_NULL)
				MdispFree(m_MilCamDisplay[i][j]);

			if (m_MilCamOverlay[i][j] != M_NULL)
				MdispFree(m_MilCamOverlay[i][j]);
		}
		
	}

	for(i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (m_MilCcdProcChild[i][j] != M_NULL)
				MbufFree(m_MilCcdProcChild[i][j]);
			if (m_pCcdGrabImg[i][j] != NULL)
				cvReleaseImage(&m_pCcdGrabImg[i][j]);
		}
		if (MilDefectDisplayImage[i] != M_NULL)
			MdispFree(MilDefectDisplayImage[i]);
		if (MilDefectImage[i] != M_NULL)
			MdispFree(MilDefectImage[i]);
		if (MilDefectOverlayImage[i] != M_NULL)
			MdispFree(MilDefectOverlayImage[i]);

		
		if (m_MilDisplay[i] != M_NULL)
			MdispFree(m_MilDisplay[i]);

		if (m_MilCcdProcImage[i] != M_NULL)
			MbufFree(m_MilCcdProcImage[i]);

		if (m_MilCcdGrabImage[i] != M_NULL)
			MbufFree(m_MilCcdGrabImage[i]);

		if (m_MilWBCoefficients[i] != M_NULL)
			MbufFree(m_MilWBCoefficients[i]);

		for (j = 0; j < MAX_BAYER_SIZE; j++)
			m_MilCcdBayerImage[i][j] = M_NULL;

		

	}

	if (m_MilOCDisplay != M_NULL)
		MdispFree(m_MilOCDisplay);

	if (m_MilDefectDisplay != M_NULL)
		MdispFree(m_MilDefectDisplay);

	for (i = 0; i < MAX_SYSTEM_COUNT; i++)
	{
		for (j = 0; j < MAX_DIGITIZER_COUNT; j++)
		{
			if (m_MilDigitizer[i][j] != M_NULL)
			{
				MdigFree(m_MilDigitizer[i][j]);
			}
		}
	}

	for (i = 0; i < MAX_SYSTEM_COUNT; i++)
	{
		if (m_MilSystem[i] != M_NULL)
		{
			MsysFree(m_MilSystem[i]);
		}
	}

	if (m_MilApplication != M_NULL)
	{
		MappFree(m_MilApplication);
	}

	

	



	//if (m_pDefectTempArea != NULL)
	//{
		//delete[] m_pDefectTempArea;
		//m_pDefectTempArea = NULL;
	//}
}


//-----------------------------------------------------------------------------
//
//	Mil Application 할당
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilApplication()
{
	/*
	#ifdef ON_LINE_CAM
	//MdigAlloc(MilSystem, M_DEFAULT, _T("Mil10_DCF.dcf"), M_DEFAULT, &MilDigitizer);
	//MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV0 + nSysIndex, M_COMPLETE, &m_MilSystem[nSysIndex]);
	//MsysAlloc(M_SYSTEM_VGA, M_DEV0 + nSysIndex, M_COMPLETE, &m_MilSystem[nSysIndex]);
#else
	//MsysAlloc(M_SYSTEM_VGA, M_DEV0 + nSysIndex, M_COMPLETE, &m_MilSystem[nSysIndex]);
#endif
	*/
#ifdef ON_LINE_CAM			//ON_LINE_MIL
	//MappAlloc(M_DEFAULT, &m_MilApplication);
	MappAllocDefault(M_DEFAULT, &m_MilApplication, &m_MilSystem[0], &m_MilCamDisplay[0][0], M_NULL, M_NULL);
	if (m_MilApplication != M_NULL)
	{
#ifdef _DEBUG
		MappControl(M_ERROR, M_PRINT_DISABLE);
#else
		MappControl(M_ERROR, M_PRINT_DISABLE);
#endif	
		return true;
	}

#else
	MappAlloc(M_DEFAULT, &m_MilApplication);
	MsysAlloc(M_SYSTEM_VGA, M_DEV0, M_COMPLETE, &m_MilSystem[0]);
	if (m_MilSystem[0] != M_NULL)
		return true;
#endif

	return false;
}

//-----------------------------------------------------------------------------
//
//	Mil System 할당
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilSystem(int nSysIndex)
{
	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

#ifdef ON_LINE_CAM
	//MdigAlloc(MilSystem, M_DEFAULT, _T("Mil10_DCF.dcf"), M_DEFAULT, &MilDigitizer);
	//MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV0 + nSysIndex, M_COMPLETE, &m_MilSystem[nSysIndex]);
	//MsysAlloc(M_SYSTEM_VGA, M_DEV0 + nSysIndex, M_COMPLETE, &m_MilSystem[nSysIndex]);
#else
	//MsysAlloc(M_SYSTEM_VGA, M_DEV0 + nSysIndex, M_COMPLETE, &m_MilSystem[nSysIndex]);
#endif

	//if (m_MilSystem[nSysIndex] != M_NULL)
		//return true;

	return false;
}

//-----------------------------------------------------------------------------
//
//	MIL Color Digitizer 할당
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilDigitizer(int nSysIndex, int nDigIndex)
{
	MIL_INT nMilCount;

	nMilCount = 0;

	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

	if (nDigIndex < 0 || nDigIndex > MAX_DIGITIZER_COUNT)
		return false;
	nMilCount = MsysInquire(m_MilSystem[nSysIndex], M_DIGITIZER_NUM, M_NULL);

	LONG64   Counter = 0;
	LONG64   Channel[] = { M_CH0 , M_CH1 };// , M_CH4 };
	if (nMilCount > 0)
	{
		MdigAlloc(m_MilSystem[nSysIndex], M_DEFAULT, _T("SHM.dcf"), M_DEFAULT, &m_MilDigitizer[nSysIndex][nDigIndex]);
		//MdigAlloc(m_MilSystem[nSysIndex], M_DEV0, _T("Mobis.dcf"), M_DEFAULT, &m_MilDigitizer[nSysIndex][nDigIndex]);

		
		MdigControl(m_MilDigitizer[nSysIndex][nDigIndex], M_GRAB_MODE, M_ASYNCHRONOUS); //M_SYNCHRONOUS); M_SYNCHRONOUS  M_ASYNCHRONOUS
		MdigControl(m_MilDigitizer[nSysIndex][nDigIndex], M_GRAB_TIMEOUT, 3000);

		MdigInquire(m_MilDigitizer[nSysIndex][nDigIndex], M_SIZE_X, &m_nMilSizeX[nDigIndex]);
		MdigInquire(m_MilDigitizer[nSysIndex][nDigIndex], M_SIZE_Y, &m_nMilSizeY[nDigIndex]);
		//
		m_lBuffAttribute[nDigIndex] = M_IMAGE + M_GRAB + M_PROC;
	}
	else
	{
		m_nMilSizeX[nDigIndex] = CAM_SIZE_X;
		m_nMilSizeY[nDigIndex] = CAM_SIZE_Y;
		m_lBuffAttribute[nDigIndex] = M_IMAGE + M_PROC;// +M_DISP;
		return true;
	}

	return true;
}
#if 0
//-----------------------------------------------------------------------------
//
//	MIL Color Digitizer 할당
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilDigitizer(int nSysIndex, int nDigIndex, TCHAR* szDcfFile, int nSizeX, int nSizeY)
{
	MIL_INT nMilCount;

	nMilCount = 0;

	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

	if (nDigIndex < 0 || nDigIndex > MAX_DIGITIZER_COUNT)
		return false;

	nMilCount = MsysInquire(m_MilSystem[nSysIndex], M_DIGITIZER_NUM, M_NULL);
	if (nMilCount > 0)
	{
		MdigAlloc(m_MilSystem[nSysIndex], M_DEV0 + nDigIndex, szDcfFile, M_DEFAULT, &m_MilDigitizer[nSysIndex][nDigIndex]);

		MdigInquire(m_MilDigitizer[nSysIndex][nDigIndex], M_SIZE_X, &m_nMilSizeX[nDigIndex]);
		MdigInquire(m_MilDigitizer[nSysIndex][nDigIndex], M_SIZE_Y, &m_nMilSizeY[nDigIndex]);
		MdigInquire(m_MilDigitizer[nSysIndex][nDigIndex], M_SIZE_BAND, &m_nMilBand[nDigIndex]);

		MdigControl(m_MilDigitizer[nSysIndex][nDigIndex], M_GRAB_MODE, M_ASYNCHRONOUS);
		MdigControl(m_MilDigitizer[nSysIndex][nDigIndex], M_GRAB_TIMEOUT, 100);

		m_lBuffAttribute[nDigIndex] = M_IMAGE + M_GRAB + M_PROC + M_DISP;
	}
	else
	{
		m_nMilSizeX[nDigIndex] = nSizeX;
		m_nMilSizeY[nDigIndex] = nSizeY;
		m_lBuffAttribute[nDigIndex] = M_IMAGE + M_PROC + M_DISP;
	}

	return true;
}
#endif


//-----------------------------------------------------------------------------
//
//	MIL 컬러 버퍼 할당
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilCamBuffer(int nSysIndex, int nDigIndex, int nCamIndex, int nCamCount)
{
#ifdef ON_LINE_MIL
	int i = 0;

	if (nDigIndex < 0 || nDigIndex > MAX_DIGITIZER_COUNT)
		return false;

	if (nCamCount > MAX_CCD_COUNT)
		return false;

	//MbufAllocColor(m_MilSystem, 3, CAM_SIZE_X, CAM_SIZE_Y, (8+M_UNSIGNED), m_lBuffAttribute[nDigIndex], &m_MilImage[nDigIndex]);

#ifdef ON_LINE_CAM
	for (i = 0; i < nCamCount; i++)
	{
#ifdef NORINDA_MODE
		//m_lBuffAttribute[nDigIndex] = M_IMAGE + M_PROC + M_DISP;		//---->NORINDA_MODE
		m_lBuffAttribute[nDigIndex] = M_IMAGE + M_PROC + M_DISP;
#else
		m_lBuffAttribute[nDigIndex] = M_IMAGE + M_PROC + M_GRAB + M_DISP;
#endif
		//MbufAllocColor(m_MilSystem[nSysIndex],3,  CAM_SIZE_X, CAM_SIZE_Y, (8 + M_UNSIGNED), M_IMAGE + M_GRAB + M_PROC, &m_MilGrabImage[nCamIndex][i]);
		MbufAlloc2d(m_MilSystem[nSysIndex], CAM_SIZE_X, CAM_SIZE_Y, (8 + M_UNSIGNED), M_IMAGE + M_GRAB + M_PROC, &m_MilGrabImage[nCamIndex][i]);
		//MbufAllocColor(m_MilSystem[nSysIndex], 3, nSizeX, nSizeY, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilCcdGrabImage[nIndex]);
		if (m_MilGrabImage[nCamIndex][i])
		{
			MbufClear(m_MilGrabImage[nCamIndex][i], M_COLOR_BLACK);

			MbufChild2d(m_MilGrabImage[nCamIndex][i], 0, 0, CAM_SIZE_X, CAM_SIZE_Y, &m_MilGrabImageChild[nCamIndex][i]);
			//MbufChildColor(m_MilGrabImage[nCamIndex][i], M_RED, &m_MilGrabImageChild[nCamIndex][i]);
			//MbufChildColor(m_MilCcdProcImage[nIndex], lColorBand, &m_MilCcdProcChild[nIndex][i]);
			if (m_MilGrabImageChild[nCamIndex][i])
				MbufClear(m_MilGrabImageChild[nCamIndex][i], M_COLOR_BLACK);
			else
				return false;
			//MbufAlloc2d(m_MilSystem[nSysIndex], CAM_SIZE_X, CAM_SIZE_Y, (8+M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilChildImage[nCamIndex][i]);
		}
		//
		MbufAlloc2d(m_MilSystem[nSysIndex], SMALL_CAM_SIZE_X, SMALL_CAM_SIZE_Y, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &MilCamSmallImage[nCamIndex][i]);
		if (MilCamSmallImage[nCamIndex][i])
		{
			MbufClear(MilCamSmallImage[nCamIndex][i], M_COLOR_BLACK);

			MbufChild2d(MilCamSmallImage[nCamIndex][i], 0, 0, SMALL_CAM_SIZE_X, SMALL_CAM_SIZE_Y, &MilCamSmallImageChild[nCamIndex][i]);
			if (MilCamSmallImageChild[i])
				MbufClear(MilCamSmallImageChild[nCamIndex][i], M_COLOR_BLACK);
			else
				return false;

			//if (m_MilMarkSmallImage[i])
				//MbufClear(m_MilMarkSmallImage[i], M_COLOR_BLACK);
			//else
				//return false;
			MbufAlloc2d(m_MilSystem[nSysIndex], SMALL_CAM_SIZE_X, SMALL_CAM_SIZE_Y, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilMarkSmallImage[nCamIndex][i]);
		}


		/*switch (i % 3)
		{
		case 0:		lColorBand = M_RED;		break;
		case 1:		lColorBand = M_GREEN;	break;
		case 2:		lColorBand = M_BLUE;	break;
		}*/


	}

#endif
	//MbufAllocColor(m_MilSystem[nSysIndex], 3, SMALL_CAM_SIZE_X, SMALL_CAM_SIZE_Y, (8+M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilSmallImage[nCamIndex]);
	MbufAllocColor(m_MilSystem[nSysIndex], 3, CCD1_DISP_SIZE_X, CCD1_DISP_SIZE_Y, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilSmallImage[nCamIndex]);
	MbufClear(m_MilSmallImage[nCamIndex], 0);



#endif
	return true;
}
#if 0
//-----------------------------------------------------------------------------
//
//	컬러 버퍼 생성
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilColorBuffer(int nSysIndex, int nDigIndex, int nCamIndex, int nCamCount)
{
	long lColorBand = 0;
	int i;

	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

	if (nDigIndex < 0 || nDigIndex > MAX_DIGITIZER_COUNT)
		return false;

	if (nCamIndex < 0 || nCamIndex > MAX_CCD_COUNT)
		return false;

	if (nCamCount > MAX_CCD_COUNT)
		return false;

	MbufAllocColor(m_MilSystem[nSysIndex], 3, m_nMilSizeX[nDigIndex], m_nMilSizeY[nDigIndex], 8 + M_UNSIGNED, m_lBuffAttribute[nDigIndex], &m_MilImage[nDigIndex]);
	MbufClear(m_MilImage[nDigIndex], M_COLOR_BLACK);
	
	for (i = nCamIndex; i < nCamCount; i++)
	{
		switch (i % 3)
		{
		case 0:		lColorBand = M_RED;		break;
		case 1:		lColorBand = M_GREEN;	break;
		case 2:		lColorBand = M_BLUE;	break;
		}

		MbufChildColor(m_MilImage[nDigIndex], lColorBand, &m_MilGrabImage[i]);
		MbufAlloc2d(m_MilSystem[nSysIndex], m_nMilSizeX[nDigIndex], m_nMilSizeY[nDigIndex], 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &m_MilChildImage[i]);
	}
	return true;
}
#endif
//-----------------------------------------------------------------------------
//
//	CCD용 이미지 버퍼 생성
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilDefectBuffer(int nSysIndex, int nIndex, int nSizeX, int nSizeY)
{

	int i;

	if (nIndex < 0 || nIndex >= MAX_UNIT_COUNT)
		return false;


#ifdef ON_LINE_MIL
	MdispAlloc(m_MilSystem[nSysIndex], M_DEFAULT, _T("M_DEFAULT"), M_DEFAULT, &MilDefectDisplayImage[nIndex]);

	MbufAllocColor(m_MilSystem[nSysIndex], 3L, nSizeX, nSizeY, (8 + M_UNSIGNED), M_IMAGE + M_DISP + M_PROC, &MilDefectImage[nIndex]);
	if (MilDefectImage[nIndex])
	{
		MbufClear(MilDefectImage[nIndex], 0);


		MilDefectDisplayImage[nIndex] = M_NULL;
		MilDefectOverlayImage[nIndex] = M_NULL;

		MilDefectDisplayImage[nIndex] = MdispAlloc(m_MilSystem[nSysIndex], M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, M_NULL);
	}


	
#endif
	return true;
}


//-----------------------------------------------------------------------------
//
//	CCD용 이미지 버퍼 생성
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilCcdBuffer(int nSysIndex, int nIndex, int nSizeX, int nSizeY)
{

	long lColorBand;
	int i;

	if(nIndex < 0 || nIndex >= MAX_UNIT_COUNT)
		return false;

	MbufAllocColor(m_MilSystem[nSysIndex], 3, nSizeX, nSizeY, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilCcdGrabImage[nIndex]);
	if (m_MilCcdGrabImage[nIndex] == M_NULL)
		return false;

#ifdef ON_LINE_MIL
	MbufClear(m_MilCcdGrabImage[nIndex], 0);
#endif
	MbufAllocColor(m_MilSystem[nSysIndex], 3, nSizeX, nSizeY, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilCcdProcImage[nIndex]);
	if (m_MilCcdProcImage[nIndex] == M_NULL)
		return false;

#ifdef ON_LINE_MIL
	MbufClear(m_MilCcdProcImage[nIndex], 0);
#endif
	/*MbufAllocColor(m_MilSystem[nSysIndex], 3, CCD1_DISP_SIZE_X, CCD1_DISP_SIZE_Y, (8+M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilSmallImage[nIndex]);
	MbufClear(m_MilSmallImage[nIndex], 0);*/
		

	for (i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:		lColorBand = M_RED;		break;
		case 1:		lColorBand = M_GREEN;	break;
		case 2:		lColorBand = M_BLUE;	break;
		}

		MbufChildColor(m_MilCcdProcImage[nIndex], lColorBand, &m_MilCcdProcChild[nIndex][i]);
		if (m_MilCcdProcChild[nIndex][i] == M_NULL)
			return false;

#ifdef ON_LINE_MIL
		MbufClear(m_MilCcdProcChild[nIndex][i], 0);
#endif
		m_pImgBuff[nIndex][i] = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, nSizeX * nSizeY);
		MbufInquire(m_MilCcdProcChild[nIndex][i], M_HOST_ADDRESS, &m_pImgBuff[nIndex][i]);
	}

	for (i = 0; i < MAX_BAYER_SIZE; i++)
	{
		MbufAlloc2d(m_MilSystem[nSysIndex], nSizeX, nSizeY, 8 + M_UNSIGNED, M_IMAGE + M_PROC, &m_MilCcdBayerImage[nIndex][i]);
#ifdef ON_LINE_MIL
		if (m_MilCcdBayerImage[nIndex][i] != M_NULL)
			MbufClear(m_MilCcdBayerImage[nIndex][i], 0);
#endif
		m_pCcdGrabImg[nIndex][i] = cvCreateImage(cvSize(nSizeX, nSizeY), IPL_DEPTH_8U, 1);
	}
	
	MbufAlloc1d(m_MilSystem[nSysIndex], 3, 32 + M_FLOAT, M_ARRAY, &m_MilWBCoefficients[nIndex]);
        
	MbufAllocColor(m_MilSystem[nSysIndex], 1L, CCD1_DISP_SIZE_X, CCD1_DISP_SIZE_Y, (8 + M_UNSIGNED), M_IMAGE + M_DISP + M_PROC, &MilTempImage[nIndex]);//M_IMAGE + M_DISP + M_PROC

#ifdef ON_LINE_MIL
    if (MilTempImage[nIndex])	MbufClear(MilTempImage[nIndex], 0);

#endif
    
	//// 이물검사용 버퍼 할당 
	//m_pDefectTempArea = new int[_DEF_MAX_BLOBS];
	//if (m_pDefectTempArea == NULL)
	//	return false;

	//m_pDefectInspImage = cvCreateImage(cvSize(nSizeX, nSizeY), IPL_DEPTH_8U, 1);
	//if (m_pDefectInspImage == NULL)
	//{
	//	AddLog(_T("[FAIL] 이물검사용 흑백 이미지 버퍼 할당 실패"), 1);
	//	return false;
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::CloseViion()
{
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CVision::AllocMil2DBuffer(int nSysIndex, int nDigIndex, int nCamIndex, int nCamCount)
{
	return true;
}

//-----------------------------------------------------------------------------
//
//CAM
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilCamDisplay(int nSysIndex, int nCamIndex, HWND hWnd)
{
	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

	if (nCamIndex < 0 || nCamIndex > MAX_CAM_COUNT)
		return false;
	for (int i = 0; i < MAX_CAM_COUNT; i++)
	{
		MdispAlloc(m_MilSystem[nSysIndex], M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &m_MilCamDisplay[nCamIndex][i]);
		if (m_MilCamDisplay[nCamIndex][i] != M_NULL)
		{
			MIL_INT DisplayType = MdispInquire(m_MilCamDisplay[nCamIndex][i], M_DISPLAY_TYPE, M_NULL);
			
			//if (MdispInquire(m_MilCamDisplay[nCamIndex][i], M_DISPLAY_TYPE, M_NULL) != M_WINDOWED)
			if (DisplayType != M_WINDOWED)
			{
				MdispFree(m_MilCamDisplay[nCamIndex][i]);
				m_MilCamDisplay[nCamIndex][i] = M_NULL;

				return false;
			}

			//MdispControl(m_MilCamDisplay[nCamIndex], M_WINDOW_SCROLLBAR, M_DISABLE);
			MdispSelectWindow(m_MilCamDisplay[nCamIndex][i], MilCamSmallImageChild[nCamIndex][i], hWnd);
		}
	}
	return true;
}
//
//-----------------------------------------------------------------------------
//
//CCD
//
//-----------------------------------------------------------------------------
bool CVision::AllocMilDisplay(int nSysIndex, int nCamIndex, HWND hWnd)
{
	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

	if (nCamIndex < 0 || nCamIndex > MAX_CCD_COUNT)
		return false;

	MdispAlloc(m_MilSystem[nSysIndex], M_DEFAULT, _T("M_DEFAULT"), M_DEFAULT, &m_MilDisplay[nCamIndex]);
	if (m_MilDisplay[nCamIndex] != M_NULL)
	{
		MIL_INT DisplayType = MdispInquire(m_MilDisplay[nCamIndex], M_DISPLAY_TYPE, M_NULL);
		if (DisplayType != M_WINDOWED)
		//if (MdispInquire(m_MilDisplay[nCamIndex], M_DISPLAY_TYPE, M_NULL) != M_WINDOWED)
		{
			MdispFree(m_MilDisplay[nCamIndex]);
			m_MilDisplay[nCamIndex] = M_NULL;

			return false;
		}

		//MdispControl(m_MilDisplay[nCamIndex], M_WINDOW_SCROLLBAR, M_DISABLE);
		
		//if(nCamIndex < CAM_CCD)
		//	MdispSelectWindow(m_MilDisplay[nCamIndex], m_MilGrabImage[nCamIndex], hWnd);
		//else
		//MdispSelectWindow(m_MilDisplay[nCamIndex], m_MilCcdProcImage[nCamIndex], hWnd);
		MdispSelectWindow(m_MilDisplay[nCamIndex], m_MilSmallImage[nCamIndex], hWnd);
	}

	
	
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CVision::AllocInspBuff(int nSysIndex, int nSizeX, int nSizeY)
{	
	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

	MbufAllocColor(m_MilSystem[nSysIndex], 3, nSizeX, nSizeY, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilOCImage);
	if (m_MilOCImage == M_NULL)
		return false;

	MbufAllocColor(m_MilSystem[nSysIndex], 3, nSizeX, nSizeY, (8 + M_UNSIGNED), M_IMAGE + M_PROC + M_DISP, &m_MilDefectImage);
	if (m_MilDefectImage == M_NULL)
		return false;

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CVision::AllocInspDisplay(int nSysIndex, int nType, double dZoomFac, HWND hWnd)
{
	if (nSysIndex < 0 || nSysIndex > MAX_SYSTEM_COUNT)
		return false;

	if (nType == 0)
	{
		MdispAlloc(m_MilSystem[nSysIndex], M_DEFAULT, _T("M_DEFAULT"), M_DEFAULT, &m_MilOCDisplay);
		if (m_MilOCDisplay != M_NULL)
		{
			if (MdispInquire(m_MilOCDisplay, M_DISPLAY_MODE, M_NULL) != M_WINDOWED)
			{
				MdispFree(m_MilOCDisplay);
				m_MilOCDisplay = M_NULL;

				return false;
			}

			MdispControl(m_MilOCDisplay, M_WINDOW_SCROLLBAR, M_DISABLE);
			MdispSelectWindow(m_MilOCDisplay, m_MilOCImage, hWnd);
			MdispZoom(m_MilOCDisplay, dZoomFac, dZoomFac);
		}

		if (m_MilOCDisplay != M_NULL)
		{
			if (MdispInquire(m_MilOCDisplay, M_DISPLAY_MODE, M_NULL) == M_WINDOWED)
			{
				MdispControl(m_MilOCDisplay, M_OVERLAY_SHOW, M_ENABLE);
				MdispControl(m_MilOCDisplay, M_OVERLAY, M_ENABLE);
				MdispInquire(m_MilOCDisplay, M_OVERLAY_ID, &m_MilOCOverlay);
				MdispInquire(m_MilOCDisplay, (MIL_INT)M_TRANSPARENT_COLOR, &m_nMilTransparentOC);
#ifdef ON_LINE_MIL
				MbufClear(m_MilOCOverlay, (MIL_DOUBLE)m_nMilTransparentOC);
				MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
#endif
			}
		}
	}
	else
	{
		MdispAlloc(m_MilSystem[nSysIndex], M_DEFAULT, _T("M_DEFAULT"), M_DEFAULT, &m_MilDefectDisplay);
		if (m_MilDefectDisplay != M_NULL)
		{
			if (MdispInquire(m_MilDefectDisplay, M_DISPLAY_MODE, M_NULL) != M_WINDOWED)
			{
				MdispFree(m_MilDefectDisplay);
				m_MilDefectDisplay = M_NULL;

				return false;
			}

			MdispControl(m_MilDefectDisplay, M_WINDOW_SCROLLBAR, M_DISABLE);
			MdispSelectWindow(m_MilDefectDisplay, m_MilDefectImage, hWnd);
			MdispZoom(m_MilDefectDisplay, dZoomFac, dZoomFac);
		}

		if (m_MilDefectDisplay != M_NULL)
		{
			if (MdispInquire(m_MilDefectDisplay, M_DISPLAY_MODE, M_NULL) == M_WINDOWED)
			{
				MdispControl(m_MilDefectDisplay, M_OVERLAY_SHOW, M_ENABLE);
				MdispControl(m_MilDefectDisplay, M_OVERLAY, M_ENABLE);
				MdispInquire(m_MilDefectDisplay, M_OVERLAY_ID, &m_MilDefectOverlay);
				MdispInquire(m_MilDefectDisplay, (MIL_INT)M_TRANSPARENT_COLOR, &m_nMilTransparentDefect);
#ifdef ON_LINE_MIL
				MbufClear(m_MilDefectOverlay, (MIL_DOUBLE)m_nMilTransparentDefect);
				MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
#endif
			}
		}
	}
	
	return true;
}

//-----------------------------------------------------------------------------
//
//	마크 찾기
//
//-----------------------------------------------------------------------------
bool CVision::CalcSingleMarkAlign(int m_nUnit, int nNo, int nCount, CDMotor& clDMotor, CDMPoint clDPt)
{
#ifndef ON_LINE_MIL
	return true;
#endif
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szPos[SIZE_OF_100BYTE];
	TCHAR szTemp[SIZE_OF_100BYTE];
	STRUC_MARK_POS stMarkPos;
	CDMPoint clDPtFindMark;
	CDMPoint clDPtFindPos;
	bool bFind = false;
	double dFitError = 0.0;
	bool bAreaFlag = true;

	memset(&stMarkPos, 0x00, sizeof(stMarkPos));
	clDMotor.x = clDMotor.y = clDMotor.t = 0.0;
	clDPt.x = clDPt.y = 0.0;
	g_clTaskWork[m_nUnit].m_dAADataX = 0.0;
	g_clTaskWork[m_nUnit].m_dAADataY = 0.0;
	g_clTaskWork[m_nUnit].m_dAADataTh = 0.0;

	g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);
	g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);

	//_stprintf_s(szPos, SIZE_OF_100BYTE, _T("[#%d]"), nCamIndex + 1);

	if ((g_clMarkData[m_nUnit].m_clRectRoi[nNo].top <= 0) || g_clMarkData[m_nUnit].m_clRectRoi[nNo].left <= 0)
		bAreaFlag = false;

	stMarkPos.nMarkNo = nNo;
	bFind = g_clModelFinder.FindModel(m_nUnit, nNo, bAreaFlag, clDPtFindPos, stMarkPos.dScore, stMarkPos.dAngle, dFitError, stMarkPos.clDPtMarkSize, stMarkPos.clDPtMarkCenter);
	if (bFind == true)
	{
		stMarkPos.dMarkCenterX = clDPtFindPos.x;
		stMarkPos.dMarkCenterY = clDPtFindPos.y;
		//_tcscpy_s(stMarkPos.szMode, SIZE_OF_100BYTE, _T("EDGE MATCH"));
		_tcscpy_s(stMarkPos.szMode, SIZE_OF_100BYTE, _T("MARK FIND"));
	}
	else
	{
#ifdef ON_LINE_MIL
		MgraColor(M_DEFAULT, M_COLOR_RED);
#endif
		MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 319L, g_clMarkData[m_nUnit].m_clRectRoi[nNo].left*-1);	//M_DRAW_RELATIVE_ORIGIN_X//- ROI 영역 Offset
		MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 320L, g_clMarkData[m_nUnit].m_clRectRoi[nNo].top*-1);//M_DRAW_RELATIVE_ORIGIN_Y

		MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 3203L, CAM_REDUCE_FACTOR_X);//M_DRAW_SCALE_X
		MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 3204L, CAM_REDUCE_FACTOR_Y);//M_DRAW_SCALE_Y

		MmodDraw(M_DEFAULT, g_clModelFinder.m_MilModResult[m_nUnit], m_MilCamOverlay[m_nUnit][0], M_DRAW_BOX + M_DRAW_POSITION + M_DRAW_EDGES + M_DRAW_AXIS, M_DEFAULT, M_DEFAULT);

		//return false;
	}
	_stprintf_s(szLog, SIZE_OF_1K, _T("[MarkAlign] SCore:%.01lf[Spec:%d]"), stMarkPos.dScore , g_clModelData[m_nUnit].m_nMinMatching);
	AddLog(szLog, 0, m_nUnit);
	if (bFind == true && stMarkPos.dScore < g_clModelData[m_nUnit].m_nMinMatching) {
		bFind = false;
	}
#ifdef ON_LINE_MIL
	if (true == bFind) {
		MgraColor(M_DEFAULT, M_COLOR_MAGENTA);
	}
	else {
		MgraColor(M_DEFAULT, M_COLOR_RED);
	}
#endif
	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("[ ROI ]"));
	this->DrawMOverlayText(m_nUnit, g_clMarkData[m_nUnit].m_clRectRoi[nNo].left, g_clMarkData[m_nUnit].m_clRectRoi[nNo].top - 30, szTemp, M_COLOR_MAGENTA, _T("Arial"), 15, 10, FALSE, VIDEO_CAM);

	MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 319L, g_clMarkData[m_nUnit].m_clRectRoi[nNo].left*-1);//M_DRAW_RELATIVE_ORIGIN_X	//- ROI 영역 Offset
	MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 320L, g_clMarkData[m_nUnit].m_clRectRoi[nNo].top*-1);//M_DRAW_RELATIVE_ORIGIN_Y

	MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 3203L, CAM_REDUCE_FACTOR_X);//M_DRAW_SCALE_X
	MmodControl(g_clModelFinder.m_MilModResult[m_nUnit], M_DEFAULT, 3204L, CAM_REDUCE_FACTOR_Y);//M_DRAW_SCALE_Y

	MmodDraw(M_DEFAULT, g_clModelFinder.m_MilModResult[m_nUnit], m_MilCamOverlay[m_nUnit][0], M_DRAW_BOX + M_DRAW_POSITION + M_DRAW_EDGES + M_DRAW_AXIS, M_DEFAULT, M_DEFAULT);

	this->DrawOverlayFindMark(m_nUnit, nNo, stMarkPos, bFind);

	clDPtFindMark.x = stMarkPos.dMarkCenterX;
	clDPtFindMark.y = stMarkPos.dMarkCenterY; 
	clDPt.x = stMarkPos.dMarkCenterX;
	clDPt.y = stMarkPos.dMarkCenterY;

	if (bFind == true)
	{
		g_CalcAlignData(m_nUnit, clDPtFindMark, stMarkPos.dAngle, clDMotor.x, clDMotor.y, clDMotor.t);

		g_clTaskWork[m_nUnit].m_dAADataX = clDMotor.x;
		g_clTaskWork[m_nUnit].m_dAADataY = clDMotor.y;
		g_clTaskWork[m_nUnit].m_dAADataTh = clDMotor.t;
		//_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("RETRY CNT-%d"), nCount);
		//this->DrawMOverlayText(nCamIndex, 20, 60, szTemp, M_COLOR_MAGENTA, _T("Arial"), 15, 12, FALSE);
	}
	else
	{
		_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("[ FIND FAIL!]"));
		this->DrawMOverlayText(m_nUnit, CCD1_CAM_SIZE_X / 2 - 500, CCD1_CAM_SIZE_Y / 2 - 200, szTemp, M_COLOR_RED, _T("Arial"), 100, 40, FALSE, VIDEO_CAM);
		g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);

		return false; 
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("[MarkAlign][ CAM-%d ] X:%.03lf, Y:%.03lf, T:%.03lf"), m_nUnit + 1, clDMotor.x, clDMotor.y, clDMotor.t);
	AddLog(szLog, 0, m_nUnit);

	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("[ ALIGN DATA ]"));
	this->DrawMOverlayText(m_nUnit, CCD1_CAM_SIZE_X - 520, CCD1_CAM_SIZE_Y - 90, szTemp, M_COLOR_MAGENTA, _T("Arial"), 15, 10, FALSE, VIDEO_CAM);
	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("X : %.03lf, Y : %.03f, T : %.03f"), clDMotor.x, clDMotor.y, clDMotor.t);
	this->DrawMOverlayText(m_nUnit, CCD1_CAM_SIZE_X - 520, CCD1_CAM_SIZE_Y - 55, szTemp, M_COLOR_MAGENTA, _T("Arial"), 15, 10, FALSE, VIDEO_CAM);
	this->DrawOverlayAll(m_nUnit, VIDEO_CAM);

	return true;
}

//-----------------------------------------------------------------------------
//
//	마크 오버레이 그리기
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayFindMark(int nCamIndex, int nNo, STRUC_MARK_POS stMarkPos, bool bFindOk)
{
	COLORREF drawColor;
	CPoint clPtFindOrd;
	CDMPoint clDPtCenter;
	CRect rectMark;
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szPos[SIZE_OF_100BYTE];
	TCHAR szTemp[SIZE_OF_100BYTE];

	//_stprintf_s(szPos, _T("[INSP #%d]"), nCamIndex + 1);

	//this->DrawOverlayText(nCamIndex, 20, 20, szPos, RGB(0, 255, 0), _T("Arial"), 8, 12);

	this->DrawMOverlayLine(nCamIndex, CCD1_CAM_SIZE_X / 2, 0, CCD1_CAM_SIZE_X / 2, CCD1_CAM_SIZE_Y, M_COLOR_MAGENTA, 1, FALSE, PS_DOT, VIDEO_CAM);
	this->DrawMOverlayLine(nCamIndex, 0, CCD1_CAM_SIZE_Y / 2, CCD1_CAM_SIZE_X, CCD1_CAM_SIZE_Y / 2, M_COLOR_MAGENTA, 1, FALSE, PS_DOT, VIDEO_CAM);

	this->DrawMOverlayBox(nCamIndex, nCamIndex, g_clMarkData[nCamIndex].m_clRectRoi[nNo], M_COLOR_BLUE, 2, FALSE, PS_DASH, VIDEO_CAM);

	clPtFindOrd.x = (int)(stMarkPos.dMarkCenterX - stMarkPos.clDPtMarkCenter.x);
	clPtFindOrd.y = (int)(stMarkPos.dMarkCenterY - stMarkPos.clDPtMarkCenter.y);

	this->DrawMOverlayText(nCamIndex, clPtFindOrd.x, clPtFindOrd.y - 30, stMarkPos.szMode, M_COLOR_GREEN, _T("Arial"), 15, 10, FALSE, VIDEO_CAM);	//MARK FIND 글자 표시

	if (bFindOk == true)	drawColor = RGB(0, 255, 0);
	else					drawColor = RGB(255, 32, 32);

	//-- Mark Size Box 그리기
	rectMark.left = (int)(stMarkPos.dMarkCenterX - stMarkPos.clDPtMarkCenter.x);
	rectMark.top = (int)(stMarkPos.dMarkCenterY - stMarkPos.clDPtMarkCenter.y);
	rectMark.right = (int)(stMarkPos.dMarkCenterX + (stMarkPos.clDPtMarkSize.x - stMarkPos.clDPtMarkCenter.x));
	rectMark.bottom = (int)(stMarkPos.dMarkCenterY + (stMarkPos.clDPtMarkSize.y - stMarkPos.clDPtMarkCenter.y));
	this->DrawMOverlayBox(nCamIndex, nCamIndex,rectMark, drawColor, 1, FALSE, VIDEO_CAM);
																//COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/, int nStyles/* = PS_SOLID*/, int DisplayMode)
	//this->DrawMOverlayCross(nCamIndex, nCamIndex, (int)stMarkPos.dMarkCenterX, (int)stMarkPos.dMarkCenterY, 50, drawColor, 1, TRUE, PS_SOLID, VIDEO_CAM); //마크 중심 십자가

	this->DrawOverlayCross(nCamIndex, nCamIndex, (int)stMarkPos.dMarkCenterX, (int)stMarkPos.dMarkCenterY, 50, drawColor, 1, PS_SOLID, VIDEO_CAM);
	//this->DrawMOverlayCross(nCamIndex, nCamIndex, (int)rectMark.left, (int)rectMark.top, 200, drawColor, 1, TRUE);

	clDPtCenter.x = CCD1_CAM_SIZE_X / 2;
	clDPtCenter.y = CCD1_CAM_SIZE_Y / 2;

	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("[POS]"));
	this->DrawOverlayText(nCamIndex, 20, CCD1_CAM_SIZE_Y - 110, szTemp, drawColor, _T("Arial"), 10, 14, VIDEO_CAM);

	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("CENTER X : %.2f"), stMarkPos.dMarkCenterX);
	this->DrawOverlayText(nCamIndex, 20, CCD1_CAM_SIZE_Y - 80, szTemp, drawColor, _T("Arial"), 10, 14, VIDEO_CAM);

	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("CENTER Y : %.2f"), stMarkPos.dMarkCenterY);
	this->DrawOverlayText(nCamIndex, 20, CCD1_CAM_SIZE_Y - 50, szTemp, drawColor, _T("Arial"), 10, 14, VIDEO_CAM);

	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("[Mark] %s"), MARK_ALIGN_NAME[nNo]);// , stMarkPos.nMarkNo + 1);
	this->DrawOverlayText(nCamIndex, 20, 30, szTemp, drawColor, _T("Arial"), 10, 14, VIDEO_CAM);

	_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("SCORE : [%.2f / %d]"), stMarkPos.dScore, g_clModelData[nCamIndex].m_nMinMatching);
	this->DrawOverlayText(nCamIndex, 20, 60, szTemp, drawColor, _T("Arial"), 10, 14, VIDEO_CAM);

	_stprintf_s(szLog, SIZE_OF_1K, _T("[MarkAlign]Find CENTER X:%.03lf"), stMarkPos.dMarkCenterX);
	AddLog(szLog, 0, nCamIndex);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[MarkAlign]Find CENTER Y:%.03lf"), stMarkPos.dMarkCenterY);
	AddLog(szLog, 0, nCamIndex);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::EnableOverlay(int nSysIndex, int nDispIndex)
{
	static unsigned char LutLow[18] = { 0, 0, 128,			// Index 1 = dark-blue
		0, 0, 255,			// Index 2 = light-blue
		255, 0, 0,			// Index 3 = light-red
		0, 255, 0,			// Index 4 = light-green
		128, 0, 128,		// Index 5 = magenta
		0, 128, 128 };		// Index 6 = cyon
	int nTempBand;
	MIL_ID       MilLut, MilLutChildLow, MilLutChildKey;
	PALETTEENTRY PalEntry;
	HDC          hDC;
	COLORREF     color;

	if (m_MilDisplay[nDispIndex])
	{
		MIL_INT DisplayType = MdispInquire(m_MilDisplay[nDispIndex], M_DISPLAY_TYPE, M_NULL);
		//if (MdispInquire(m_MilDisplay[nDispIndex], M_DISPLAY_TYPE, M_NULL) == M_WINDOWED)

		//if((DisplayType&(M_WINDOWED|M_EXCLUSIVE)) != M_WINDOWED)       
		//M_USER_WINDOW
		//if(DisplayType == M_WINDOWED)
		MIL_INT DisplayType222 = (M_WINDOWED | M_USER_WINDOW);
		if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
		{
			MdispControl(m_MilDisplay[nDispIndex], M_OVERLAY_SHOW, M_ENABLE);// M_WINDOW_OVR_SHOW
			MdispControl(m_MilDisplay[nDispIndex], M_OVERLAY, M_ENABLE);//M_WINDOW_OVR_WRITE
			MdispInquire(m_MilDisplay[nDispIndex], M_OVERLAY_ID, &m_MilOverlay[nDispIndex]);//M_WINDOW_OVR_BUF_ID
			MdispInquire(m_MilDisplay[nDispIndex], M_TRANSPARENT_COLOR, &m_nMilTransparent[nDispIndex]);
			/*MdispControl(m_MilDisplay[nDispIndex], M_WINDOW_OVR_SHOW, M_ENABLE);
			MdispControl(m_MilDisplay[nDispIndex], M_WINDOW_OVR_WRITE, M_ENABLE);
			MdispInquire(m_MilDisplay[nDispIndex], M_WINDOW_OVR_BUF_ID, &m_MilOverlay[nDispIndex]);
			MdispInquire(m_MilDisplay[nDispIndex], (MIL_INT)M_KEY_COLOR, &m_nMilTransparent[nDispIndex]);*/
#ifdef ON_LINE_MIL
			MbufClear(m_MilOverlay[nDispIndex], (MIL_DOUBLE)m_nMilTransparent[nDispIndex]);
			MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
#endif


		}

		nTempBand = (int)MbufInquire(m_MilOverlay[nDispIndex], M_SIZE_BAND, M_NULL);
		if (nTempBand == 1)
		{
			MbufAllocColor(m_MilSystem[nSysIndex], 3L, 256L, 1L, 8L + M_UNSIGNED, M_LUT, &MilLut);

			MbufChild2d(MilLut, 3, 0, 6, 1, &MilLutChildLow);
			MgenLutRamp(MilLut, 0, 0, 255, 255);
			MbufPutColor(MilLutChildLow, M_RGB24 + M_PACKED, M_ALL_BAND, &LutLow);

			hDC = ::GetDC(NULL);
			GetSystemPaletteEntries(hDC, (UINT)m_nMilTransparent[nDispIndex], 1, &PalEntry);
			color = RGB(PalEntry.peRed, PalEntry.peGreen, PalEntry.peBlue);

			MbufChild1d(MilLut, m_nMilTransparent[nDispIndex], 1, &MilLutChildKey);
			MbufPutColor(MilLutChildKey, (M_RGB24 | M_PACKED), M_ALL_BAND, &color);
			::ReleaseDC(NULL, hDC);

			MdispControl(m_MilDisplay[nDispIndex], M_OVERLAY_LUT, MilLut);

			MbufFree(MilLutChildKey);
			MbufFree(MilLutChildLow);
			MbufFree(MilLut);
		}
	}



	if (MilDefectDisplayImage[nDispIndex])
	{
		MIL_INT DefectDisplayType = MdispInquire(MilDefectDisplayImage[nDispIndex], M_DISPLAY_TYPE, M_NULL);

		//if (DisplayType == M_DISPLAY_MODE)//(M_WINDOWED | M_USER_WINDOW))
		//if (DisplayType == M_WINDOWED)
		if (DefectDisplayType == (M_WINDOWED | M_USER_WINDOW))
		{
			MdispControl(MilDefectDisplayImage[nDispIndex], M_OVERLAY_SHOW, M_ENABLE);// 
			MdispControl(MilDefectDisplayImage[nDispIndex], M_OVERLAY, M_ENABLE);//
			MdispInquire(MilDefectDisplayImage[nDispIndex], M_OVERLAY_ID, &MilDefectOverlayImage[nDispIndex]);//
			MdispInquire(MilDefectDisplayImage[nDispIndex], M_TRANSPARENT_COLOR, &m_nMilDefectTransparent[nDispIndex]);

			MbufClear(MilDefectOverlayImage[nDispIndex], (MIL_DOUBLE)m_nMilDefectTransparent[nDispIndex]);
			MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
		}
	}

}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::EnableCamOverlay(int nSysIndex, int nDispIndex)
{
	static unsigned char LutLow[18] = { 0, 0, 128,			// Index 1 = dark-blue
		0, 0, 255,			// Index 2 = light-blue
		255, 0, 0,			// Index 3 = light-red
		0, 255, 0,			// Index 4 = light-green
		128, 0, 128,		// Index 5 = magenta
		0, 128, 128 };		// Index 6 = cyon
	int nTempBand;
	MIL_ID       MilLut, MilLutChildLow, MilLutChildKey;
	PALETTEENTRY PalEntry;
	HDC          hDC;
	COLORREF     color;
	for (int i = 0; i < MAX_CAM_COUNT; i++)
	{
		if (m_MilCamDisplay[nDispIndex][i])
		{
			MIL_INT DisplayType = MdispInquire(m_MilCamDisplay[nDispIndex][i], M_DISPLAY_TYPE, M_NULL);
			//if (MdispInquire(m_MilCamDisplay[nDispIndex][i], M_DISPLAY_TYPE, M_NULL) == M_WINDOWED) 
			if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
			{ 
				MdispControl(m_MilCamDisplay[nDispIndex][i], M_OVERLAY_SHOW, M_ENABLE);// M_WINDOW_OVR_SHOW
				MdispControl(m_MilCamDisplay[nDispIndex][i], M_OVERLAY, M_ENABLE);//M_WINDOW_OVR_WRITE
				MdispInquire(m_MilCamDisplay[nDispIndex][i], M_OVERLAY_ID, &m_MilCamOverlay[nDispIndex][i]);//M_WINDOW_OVR_BUF_ID
				MdispInquire(m_MilCamDisplay[nDispIndex][i], M_TRANSPARENT_COLOR, &m_nMilCamTransparent[nDispIndex][i]);
#ifdef ON_LINE_MIL
				MbufClear(m_MilCamOverlay[nDispIndex][i], (MIL_DOUBLE)m_nMilCamTransparent[nDispIndex][i]);
				MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
#endif
				
			}

			nTempBand = (int)MbufInquire(m_MilCamOverlay[nDispIndex][i], M_SIZE_BAND, M_NULL);
			if (nTempBand == 1)
			{
				MbufAllocColor(m_MilSystem[nSysIndex], 3L, 256L, 1L, 8L + M_UNSIGNED, M_LUT, &MilLut);

				MbufChild2d(MilLut, 3, 0, 6, 1, &MilLutChildLow);
				MgenLutRamp(MilLut, 0, 0, 255, 255);
				MbufPutColor(MilLutChildLow, M_RGB24 + M_PACKED, M_ALL_BAND, &LutLow);

				hDC = ::GetDC(NULL);
				GetSystemPaletteEntries(hDC, (UINT)m_nMilCamTransparent[nDispIndex][i], 1, &PalEntry);
				color = RGB(PalEntry.peRed, PalEntry.peGreen, PalEntry.peBlue);

				MbufChild1d(MilLut, m_nMilCamTransparent[nDispIndex][i], 1, &MilLutChildKey);
				MbufPutColor(MilLutChildKey, (M_RGB24 | M_PACKED), M_ALL_BAND, &color);
				::ReleaseDC(NULL, hDC);

				MdispControl(m_MilCamDisplay[nDispIndex][i], M_OVERLAY_LUT, MilLut);

				MbufFree(MilLutChildKey);
				MbufFree(MilLutChildLow);
				MbufFree(MilLut);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayText(int nUnit, CPoint clPoint, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nFs_x, int nFs_y, int DisplayMode)
{
	int x, y;
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = ((double)SMALL_CAM_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)SMALL_CAM_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);
		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}
	

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);

		CBrush* pOldBrush = (CBrush*)NewDC.SelectStockObject(NULL_BRUSH);
		CFont font, *oldfont;

		font.CreateFont(nFs_y, nFs_x, 0, 0,
			FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, szFontName);

		oldfont = NewDC.SelectObject(&font);

		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		x = (long)((clPoint.x * dZoomX) + 0.5);
		y = (long)((clPoint.y * dZoomY) + 0.5);

		NewDC.SetTextColor(RGB(oc_red, oc_green, oc_blue));
		NewDC.TextOut(x, y, szText, (MIL_INT32)MosStrlen(szText));

		NewDC.SelectObject(oldfont);
		font.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}
	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayText(int nUnit, int nX, int nY, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nFs_x, int nFs_y, int DisplayMode)
{
	int x, y;
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;


	HDC hOverlayDC;

	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}
	


	

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);

		CBrush* pOldBrush = (CBrush*)NewDC.SelectStockObject(NULL_BRUSH);
		CFont font, *oldfont;

		font.CreateFont(nFs_y, nFs_x, 0, 0,
			FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, szFontName);

		oldfont = NewDC.SelectObject(&font);

		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		x = (int)((nX * dZoomX) + 0.5);
		y = (int)((nY * dZoomY) + 0.5);

		NewDC.SetTextColor(RGB(oc_red, oc_green, oc_blue));
		NewDC.TextOut(x, y, szText, (MIL_INT32)MosStrlen(szText));

		NewDC.SelectObject(oldfont);
		font.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
	
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayBox(int nUnit, int nCamIndex, CRect clRect, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);
		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int x1 = (int)((clRect.left * dZoomX) + 0.5);
		int x2 = (int)((clRect.right * dZoomX) + 0.5);
		int y1 = (int)((clRect.top * dZoomY) + 0.5);
		int y2 = (int)((clRect.bottom * dZoomY) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.Rectangle(x1, y1, x2, y2);
		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}
	if (DisplayMode == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
	
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayBox(int nUnit, int nCamIndex, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int x1 = (int)((nLeft * dZoomX) + 0.5);
		int x2 = (int)((nRight * dZoomX) + 0.5);
		int y1 = (int)((nTop * dZoomX) + 0.5);
		int y2 = (int)((nBottom * dZoomX) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.Rectangle(x1, y1, x2, y2);
		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}
	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayFillBox(int nUnit, CPoint clPointPos, COLORREF color, int nSizeX, int nSizeY, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		COLORREF color = RGB(oc_red, oc_green, oc_blue);
		HBRUSH hbrush = ::CreateSolidBrush(color);

		CRect clRect;
		clRect.left = (int)(((clPointPos.x - nSizeX) * dZoomX) + 0.5);
		clRect.right = (int)(((clPointPos.x + nSizeX) * dZoomX) + 0.5);
		clRect.top = (int)(((clPointPos.y - nSizeY) * dZoomY) + 0.5);
		clRect.bottom = (int)(((clPointPos.y + nSizeY) * dZoomY) + 0.5);

		::FillRect(NewDC, &clRect, hbrush);
		::DeleteObject(hbrush);

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayFillBox(int nUnit, int nX, int nY, COLORREF color, int nSizeX, int nSizeY, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}


	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		COLORREF color = RGB(oc_red, oc_green, oc_blue);
		HBRUSH hbrush = ::CreateSolidBrush(color);

		CRect clRect;
		clRect.left = (int)(((nX - nSizeX) * dZoomX) + 0.5);
		clRect.right = (int)(((nX + nSizeX) * dZoomX) + 0.5);
		clRect.top = (int)(((nY - nSizeY) * dZoomY) + 0.5);
		clRect.bottom = (int)(((nY + nSizeY) * dZoomY) + 0.5);

		::FillRect(NewDC, &clRect, hbrush);
		::DeleteObject(hbrush);

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
	}
	
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayCircle(int nUnit, CRect clRect, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int x1 = (int)((clRect.left * dZoomX) + 0.5);
		int x2 = (int)((clRect.right * dZoomX) + 0.5);
		int y1 = (int)((clRect.top * dZoomY) + 0.5);
		int y2 = (int)((clRect.bottom * dZoomY) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.Ellipse(x1, y1, x2, y2);
		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayCircle(int nUnit, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int x1 = (int)((nLeft * dZoomX) + 0.5);
		int x2 = (int)((nRight * dZoomX) + 0.5);
		int y1 = (int)((nTop * dZoomY) + 0.5);
		int y2 = (int)((nBottom * dZoomY) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.Ellipse(x1, y1, x2, y2);
		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}


	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayCross(int nUnit, int nCamIndex, CPoint clPointPos, int nWdt, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{ 
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}
	
	

	if ((hOverlayDC != M_NULL) && (nCamIndex < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int w = (int)((nWdt * dZoomX) + 0.5);
		int x = (int)((clPointPos.x * dZoomX) + 0.5);
		int y = (int)((clPointPos.y * dZoomY) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.MoveTo(x - w, y);
		NewDC.LineTo(x + w, y);
		NewDC.MoveTo(x, y - w);
		NewDC.LineTo(x, y + w);

		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}
	if (DisplayMode == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayCross(int nUnit, int nCamIndex, int nX, int nY, int nWdt, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);

	}

	if ((hOverlayDC != M_NULL) && (nCamIndex < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int w = (int)((nWdt * dZoomX) + 0.5);
		int x = (int)((nX * dZoomX) + 0.5);
		int y = (int)((nY * dZoomY) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.MoveTo(x - w, y);
		NewDC.LineTo(x + w, y);
		NewDC.MoveTo(x, y - w);
		NewDC.LineTo(x, y + w);

		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayLine(int nUnit, CPoint clPointStart, CPoint clPointEnd, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH	logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int ix1 = (int)((clPointStart.x * dZoomX) + 0.5);
		int iy1 = (int)((clPointStart.y * dZoomY) + 0.5);
		int ix2 = (int)((clPointEnd.x * dZoomX) + 0.5);
		int iy2 = (int)((clPointEnd.y * dZoomY) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.MoveTo(ix1, iy1);
		NewDC.LineTo(ix2, iy2);

		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayLine(int nUnit, int nX1, int nY1, int nX2, int nY2, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		LOGBRUSH	logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = color;

		m_pen.CreatePen(nStyles | PS_GEOMETRIC, nWid, &logBrush);
		//m_pen.CreatePen(PS_SOLID, wid, RGB(oc_red, oc_green, oc_blue)); 

		int ix1 = (int)((nX1 * dZoomX) + 0.5);
		int iy1 = (int)((nY1 * dZoomY) + 0.5);
		int ix2 = (int)((nX2 * dZoomX) + 0.5);
		int iy2 = (int)((nY2 * dZoomY) + 0.5);

		NewDC.SelectObject(&m_pen);
		NewDC.MoveTo(ix1, iy1);
		NewDC.LineTo(ix2, iy2);

		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayPixel(int nUnit, CPoint clPointPos, COLORREF color, int nWid, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);

		CBrush* pOldBrush = (CBrush*)NewDC.SelectStockObject(NULL_BRUSH);

		CPen		m_pen;
		CPen*		m_penOld;

		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		m_pen.CreatePen(PS_SOLID, nWid, RGB(oc_red, oc_green, oc_blue));

		int x = (int)((clPointPos.x * dZoomX) + 0.5);
		int y = (int)((clPointPos.y * dZoomY) + 0.5);

		m_penOld = NewDC.SelectObject(&m_pen);
		NewDC.SetPixel(x, y, RGB(oc_red, oc_green, oc_blue));

		NewDC.SelectObject(m_penOld);
		NewDC.SelectObject(pOldBrush);

		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayPixel(int nUnit, int nX, int nY, COLORREF color, int nWid, int DisplayMode)
{
	unsigned long	oc_red = 0L, oc_green = 150L, oc_blue = 0L;
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}

	if ((hOverlayDC != M_NULL) && (nUnit < MAX_CCD_COUNT))
	{
		// Attach the device context
		CDC NewDC;
		NewDC.Attach(hOverlayDC);
		NewDC.SetBkMode(TRANSPARENT);

		CBrush* pOldBrush = (CBrush*)NewDC.SelectStockObject(NULL_BRUSH);

		CPen		m_pen;
		CPen*		m_penOld;

		oc_red = (unsigned long)GetRValue(color);
		oc_green = (unsigned long)GetGValue(color);
		oc_blue = (unsigned long)GetBValue(color);

		m_pen.CreatePen(PS_SOLID, nWid, RGB(oc_red, oc_green, oc_blue));

		int x = (int)((nX * dZoomX) + 0.5);
		int y = (int)((nY * dZoomX) + 0.5);

		m_penOld = NewDC.SelectObject(&m_pen);
		NewDC.SetPixel(x, y, RGB(oc_red, oc_green, oc_blue));

		NewDC.SelectObject(m_penOld);
		NewDC.SelectObject(pOldBrush);

		m_pen.DeleteObject();

		NewDC.Detach();	//DC 연결 끊기
	}

	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::ClearOverlay(int nUnit, int DisplayMode)
{
	m_clMilDrawPixel[nUnit].RemoveAll();
	m_clMilDrawCross[nUnit].RemoveAll();
	m_clMilDrawBox[nUnit].RemoveAll();
	m_clMilDrawLine[nUnit].RemoveAll();
	m_clMilDrawText[nUnit].RemoveAll();

#ifdef  ON_LINE_MIL
	if (DisplayMode == VIDEO_CAM)
	{
		//MbufClear(m_MilCamOverlay[nUnit][0], (MIL_DOUBLE)m_nMilTransparent[nUnit]);      //<--기존
		MbufClear(m_MilCamOverlay[nUnit][0], (MIL_DOUBLE)m_nMilCamTransparent[nUnit][0]);   //<---변경


	}
	else
	{
		MbufClear(m_MilOverlay[nUnit], (MIL_DOUBLE)m_nMilTransparent[nUnit]);
	}
#endif //  ONLINE_MIL

}

//-----------------------------------------------------------------------------
//
//	Overlay 텍스트 추가
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayText(int nCamIndex, int nX, int nY, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nSx, int nSy, BOOL bRealDraw/* = TRUE*/, int DisplayMode)
{
	CPoint clPointPos;

	clPointPos.x = nX;
	clPointPos.y = nY;

	if (bRealDraw)
	{
		this->DrawOverlayText(nCamIndex, clPointPos, szText, color, szFontName, nSx, nSy);
	}
	else
	{
		m_clMilDrawText[nCamIndex].AddList(nX, nY, nSx, nSy, szText, szFontName, color);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayText(int nCamIndex, CPoint clPointPos, TCHAR* szText, COLORREF color, TCHAR* szFontName, int nSx, int nSy, BOOL bRealDraw/* = TRUE*/, int DisplayMode)
{
	if (bRealDraw)
	{
		this->DrawOverlayText(nCamIndex, clPointPos, szText, color, szFontName, nSx, nSy);
	}
	else
	{
		m_clMilDrawText[nCamIndex].AddList(clPointPos.x, clPointPos.y, nSx, nSy, szText, szFontName, color);
	}
}

//-----------------------------------------------------------------------------
//
//	Overlay 점 추가
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayPixel(int nCamIndex, int nX, int nY, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/)
{
	CPoint clPointPos;
	clPointPos.x = nX;
	clPointPos.y = nY;

	if (bRealDraw)
	{
		this->DrawOverlayPixel(nCamIndex, clPointPos, color, nWid);
	}
	else
	{
		m_clMilDrawPixel[nCamIndex].AddList(clPointPos, nWid, color);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayPixel(int nCamIndex, CPoint clPointPos, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/)
{
	if (bRealDraw)
	{
		this->DrawOverlayPixel(nCamIndex, clPointPos, color, nWid);
	}
	else
	{
		m_clMilDrawPixel[nCamIndex].AddList(clPointPos, nWid, color);
	}
}

//-----------------------------------------------------------------------------
//
//	Overlay 선 추가	
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayLine(int nCamIndex, int nX1, int nY1, int nX2, int nY2, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	CPoint clPointStart;
	CPoint clPointEnd;

	clPointStart.x = nX1;
	clPointStart.y = nY1;
	clPointEnd.x = nX2;
	clPointEnd.y = nY2;

	if (bRealDraw)
	{
		this->DrawOverlayLine(nCamIndex, clPointStart, clPointEnd, color, nWid, nStyles);
	}
	else
	{
		m_clMilDrawLine[nCamIndex].AddList(nX1, nY1, nX2, nY2, nWid, nStyles, color);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayLine(int nCamIndex, CPoint clPointStart, CPoint clPointEnd, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	if (bRealDraw)
	{
		this->DrawOverlayLine(nCamIndex, clPointStart, clPointEnd, color, nWid, nStyles);
	}
	else
	{
		m_clMilDrawLine[nCamIndex].AddList(clPointStart.x, clPointStart.y, clPointEnd.x, clPointEnd.y, nWid, nStyles, color);
	}
}

//-----------------------------------------------------------------------------
//
//	Overlay Cross 추가
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayCross(int nUnit, int nCamIndex, int nX, int nY, int nLength, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/, int nStyles/* = PS_SOLID*/)
{
	CPoint clPointPos;

	clPointPos.x = nX;
	clPointPos.y = nY;

	if (bRealDraw)
	{
		this->DrawOverlayCross(nUnit, nUnit, clPointPos, nLength, color, nWid, nStyles, nCamIndex);
	}
	else
	{
		m_clMilDrawCross[nCamIndex].AddList(clPointPos, nLength, nWid, color);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayCross(int nUnit, int nCamIndex, CPoint clPointPos, int nLength, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/, int nStyles/* = PS_SOLID*/)
{
	if (bRealDraw)
	{
		this->DrawOverlayCross(nCamIndex, nCamIndex, clPointPos, nLength, color, nWid, nStyles);
	}
	else
	{
		m_clMilDrawCross[nCamIndex].AddList(clPointPos, nLength, nWid, color);
	}
}

//-----------------------------------------------------------------------------
//
//	Overlay 원 추가
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayCircle(int nCamIndex, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/)
{
	CRect clRect;

	clRect.left = nLeft;
	clRect.top = nTop;
	clRect.right = nRight;
	clRect.bottom = nBottom;

	this->DrawOverlayCircle(nCamIndex, clRect, color, nWid, nStyles);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayCircle(int nCamIndex, CRect clRect, COLORREF color, int nWid, int nStyles/* = PS_SOLID*/)
{
	this->DrawOverlayCircle(nCamIndex, clRect, color, nWid, nStyles);
}

//-----------------------------------------------------------------------------
//
//	Overlay 네모 추가
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayBox(int nUnit, int nCamIndex, int nLeft, int nTop, int nRight, int nBottom, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	CRect clRect;

	clRect.left = nLeft;
	clRect.top = nTop;
	clRect.right = nRight;
	clRect.bottom = nBottom;

	if (bRealDraw)
	{
		this->DrawOverlayBox(nUnit, nCamIndex, clRect, color, nWid, nStyles);
	}
	else
	{
		m_clMilDrawBox[nCamIndex].AddList(clRect, nWid, nStyles, color);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVision::DrawMOverlayBox(int nUnit, int nCamIndex, CRect clRect, COLORREF color, int nWid, BOOL bRealDraw/* = TRUE*/, int nStyles/* = PS_SOLID*/, int DisplayMode)
{
	if (bRealDraw)
	{
		this->DrawOverlayBox(nCamIndex, nCamIndex, clRect, color, nWid, nStyles, DisplayMode);
	}
	else
	{
		m_clMilDrawBox[nCamIndex].AddList(clRect, nWid, nStyles, color);
	}
}

//-----------------------------------------------------------------------------
//
// 동시에 Draw
//
//-----------------------------------------------------------------------------
void CVision::DrawOverlayAll(int nUnit, int DisplayMode)
{
	double dZoomX = 0.0;
	double dZoomY = 0.0;

	
	HDC hOverlayDC;
	if (DisplayMode == VIDEO_CAM)
	{
		dZoomX = (double)((double)(SMALL_CAM_SIZE_X) / (double)CCD1_CAM_SIZE_X);
		dZoomY = (double)((double)(SMALL_CAM_SIZE_Y) / (double)CCD1_CAM_SIZE_Y);

		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilCamOverlay[nUnit][0], M_DC_HANDLE, M_NULL);
	}
	else
	{
		dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[nUnit].m_nWidth);
		dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[nUnit].m_nHeight);

		MbufControl(m_MilOverlay[nUnit], M_DC_ALLOC, M_DEFAULT);
		hOverlayDC = (HDC)MbufInquire(m_MilOverlay[nUnit], M_DC_HANDLE, M_NULL);
	}
	

	m_clMilDrawPixel[nUnit].Draw(hOverlayDC, dZoomX, dZoomY);
	m_clMilDrawCross[nUnit].Draw(hOverlayDC, dZoomX, dZoomY);
	m_clMilDrawBox[nUnit].Draw(hOverlayDC, dZoomX, dZoomY);
	m_clMilDrawLine[nUnit].Draw(hOverlayDC, dZoomX, dZoomY);
	m_clMilDrawText[nUnit].Draw(hOverlayDC, dZoomX, dZoomY);

	
	if (DisplayMode == VIDEO_CAM)
	{
		MbufControl(m_MilCamOverlay[nUnit][0], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilCamOverlay[nUnit][0], M_MODIFIED, M_DEFAULT);
	}
	else
	{
		MbufControl(m_MilOverlay[nUnit], M_DC_FREE, M_DEFAULT);
		MbufControl(m_MilOverlay[nUnit], M_MODIFIED, M_DEFAULT);
	}
	::ReleaseDC(NULL, hOverlayDC);
}


//-----------------------------------------------------------------------------
//
// Fov 영역 이미지 저장
//
//-----------------------------------------------------------------------------
void CVision::SaveFovImage(int nUnit, unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi)
{
	TCHAR szPos[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	MbufAlloc2d(g_clVision.m_MilSystem[0], sizeX, sizeY, 8 + M_UNSIGNED, M_IMAGE + M_PROC, &MilSfrTargetImage[nUnit]);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\FovCrop"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	_stprintf_s(szPos, SIZE_OF_1K, _T("%s\\FovCrop_%d.bmp"), szPath, index);


	int startX = rcRoi.left;
	int startY = rcRoi.top;

	if (startX < 0)
	{
		startX = 0;
	}
	if (startY < 0)
	{
		startY = 0;
	}

	MbufChild2d(g_clVision.m_MilCcdProcChild[nUnit][1], startX, startY, sizeX, sizeY, &MilSfrTargetImage[nUnit]);
	MbufSave(szPos, MilSfrTargetImage[nUnit]);


	//
	//
	//MbufFree(MilSfrTargetImage);

}



//-----------------------------------------------------------------------------
//
// sfr 영역 이미지 저장
//
//-----------------------------------------------------------------------------
void CVision::SaveSfrImage(int nUnit, unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi)
{
    TCHAR szPos[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

    MbufAlloc2d(g_clVision.m_MilSystem[0], sizeX*2, sizeY*2, 8 + M_UNSIGNED, M_IMAGE + M_PROC, &MilSfrTargetImage[nUnit]);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Crop"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	_stprintf_s(szPos, SIZE_OF_1K, _T("%s\\Crop_%d.bmp"), szPath, index);


	int startX = rcRoi.left;
	int startY = rcRoi.top;

	if (startX < 0)
	{
		startX = 0;
	} 
	if (startY < 0)
	{
		startY = 0;
	}

    MbufChild2d(g_clVision.m_MilCcdProcChild[nUnit][1], startX, startY, sizeX*2, sizeY*2, &MilSfrTargetImage[nUnit]);
    MbufSave(szPos, MilSfrTargetImage[nUnit]);


    //
    //
    //MbufFree(MilSfrTargetImage);

}

void CElemEllipse::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
{
	int i;
	int x1, x2, y1, y2;

	if (OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for (i = 0; i<iCnt; i++)
		{
			m_pen.CreatePen(iStyle[i], 1, c[i]);
			m_penOld = NewDC.SelectObject(&m_pen);

			x1 = (long)(cp1[i].x * dZoomFactorX + 0.5);
			x2 = (long)(cp2[i].x * dZoomFactorX + 0.5);
			y1 = (long)(cp1[i].y * dZoomFactorY + 0.5);
			y2 = (long)(cp2[i].y * dZoomFactorY + 0.5);


			NewDC.Ellipse(x1, y1, x2, y2);
			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemEllipse::addList(CPoint pos1, CPoint pos2, int iLineStyle, COLORREF color)
{
	if (iCnt<MAX_BOX_CNT)
	{
		cp1[iCnt].x = pos1.x;
		cp1[iCnt].y = pos1.y;
		cp2[iCnt].x = pos2.x;
		cp2[iCnt].y = pos2.y;

		iStyle[iCnt] = iLineStyle;
		c[iCnt] = color;
		iCnt++;
	}
}


//void CElemText::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
//{
//	int i;
//	int x, y;
//
//	char tmpChar[256];
//
//	if (OverlayDC != M_NULL)
//	{
//		CDC NewDC;
//
//		NewDC.Attach(OverlayDC);
//		NewDC.SetBkMode(TRANSPARENT);
//		NewDC.SelectStockObject(NULL_BRUSH);
//
//		CFont font, *oldfont;
//
//		for (i = 0; i<iCnt; i++)
//		{
//			font.CreateFont(s[i].x, s[i].y, 0, 0,
//				FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
//				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FontName[i]);
//
//			oldfont = NewDC.SelectObject(&font);
//
//			NewDC.SetTextColor(c[i]);
//
//			x = (long)(p[i].x * dZoomFactorX + 0.5);
//			y = (long)(p[i].y * dZoomFactorY + 0.5);
//
//			sprintf_s(tmpChar, str[i], 256);
//
//			NewDC.TextOut(x, y, tmpChar, MOs_strlen(tmpChar));
//
//			NewDC.SelectObject(oldfont);
//			font.DeleteObject();
//		}
//
//		NewDC.Detach();
//	}
//}

//void CElemText::addList(int iPosX, int iPosY, CString Str, COLORREF color, int iSizeX, int iSizeY, CString FontStr)
//{
//	if (iCnt<MAX_TEXT_CNT)
//	{
//		p[iCnt].x = iPosX;
//		p[iCnt].y = iPosY;
//		str[iCnt] = Str;
//		c[iCnt] = color;
//		s[iCnt].x = iSizeX;
//		s[iCnt].y = iSizeY;
//		FontName[iCnt] = FontStr;
//		iCnt++;
//	}
//}


void CElemPixel::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
{
	int i;
	POINT Pixel;

	if (OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for (i = 0; i<iCnt; i++)
		{
			m_pen.CreatePen(PS_SOLID, 1, c[i]);
			m_penOld = NewDC.SelectObject(&m_pen);

			Pixel.x = (long)(p[i].x * dZoomFactorX + 0.5);
			Pixel.y = (long)(p[i].y * dZoomFactorY + 0.5);

			NewDC.SetPixel(Pixel, c[i]);

			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemPixel::addList(int iPosX, int iPosY, COLORREF color)
{
	if (iCnt<MAX_PIXEL_CNT)
	{
		p[iCnt].x = iPosX;
		p[iCnt].y = iPosY;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemPixel::addList(CPoint Pos, COLORREF color)
{
	if (iCnt<MAX_PIXEL_CNT)
	{
		p[iCnt].x = Pos.x;
		p[iCnt].y = Pos.y;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemCross::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
{
	int i;
	int x, y, w1, w2;

	if (OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for (i = 0; i<iCnt; i++)
		{
			m_pen.CreatePen(PS_SOLID, 1, c[i]);
			m_penOld = NewDC.SelectObject(&m_pen);

			w1 = (long)(iSize[i] * dZoomFactorX + 0.5);
			w2 = (long)(iSize[i] * dZoomFactorY + 0.5);
			x = (long)(p[i].x * dZoomFactorX + 0.5);
			y = (long)(p[i].y * dZoomFactorY + 0.5);

			NewDC.MoveTo(x - w1, y);
			NewDC.LineTo(x + w1, y);
			NewDC.MoveTo(x, y - w2);
			NewDC.LineTo(x, y + w2);

			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemCross::addList(int iPosX, int iPosY, int w, COLORREF color)
{
	if (iCnt<MAX_CROSS_CNT)
	{
		p[iCnt].x = iPosX;
		p[iCnt].y = iPosY;
		iSize[iCnt] = w;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemCross::addList(CPoint Pos, int w, COLORREF color)
{
	if (iCnt<MAX_CROSS_CNT)
	{
		p[iCnt].x = Pos.x;
		p[iCnt].y = Pos.y;
		iSize[iCnt] = w;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemBox::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY, bool largeFlag)
{
	int i;
	int x1, x2, y1, y2;

	if (OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for (i = 0; i<iCnt; i++)
		{
			m_pen.CreatePen(iStyle[i], 1, c[i]);
			m_penOld = NewDC.SelectObject(&m_pen);

			if (largeFlag)
			{
				x1 = (long)(r[i].left * dZoomFactorX + 0.5) - 1;
				x2 = (long)(r[i].right * dZoomFactorX + 0.5) + 1;
				y1 = (long)(r[i].top * dZoomFactorY + 0.5) - 1;
				y2 = (long)(r[i].bottom * dZoomFactorY + 0.5) + 1;
			}
			else
			{
				x1 = (long)(r[i].left * dZoomFactorX + 0.5);
				x2 = (long)(r[i].right * dZoomFactorX + 0.5);
				y1 = (long)(r[i].top * dZoomFactorY + 0.5);
				y2 = (long)(r[i].bottom * dZoomFactorY + 0.5);
			}
			NewDC.Rectangle(x1, y1, x2, y2);
			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemBox::addList(int iLeft, int iTop, int iRight, int iBottom, int iLineStyle, COLORREF color)
{
	if (iCnt<MAX_BOX_CNT)
	{
		r[iCnt].left = iLeft;
		r[iCnt].top = iTop;
		r[iCnt].right = iRight;
		r[iCnt].bottom = iBottom;
		iStyle[iCnt] = iLineStyle;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemBox::addList(CRect rBox, int iLineStyle, COLORREF color)
{
	if (iCnt<MAX_BOX_CNT)
	{
		r[iCnt] = rBox;
		c[iCnt] = color;
		iStyle[iCnt] = iLineStyle;
		iCnt++;
	}
}