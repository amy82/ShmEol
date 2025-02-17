// VisitionStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionStatic.h"


// CVisionStatic

IMPLEMENT_DYNAMIC(CVisionStatic, CStatic)

CVisionStatic::CVisionStatic()
{	
	m_nUnit = UNIT_AA1;
}

CVisionStatic::~CVisionStatic()
{
}


BEGIN_MESSAGE_MAP(CVisionStatic, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()	
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()



// CVisitionStatic 메시지 처리기입니다.


//-----------------------------------------------------------------------------
//
//	초기화
//
//-----------------------------------------------------------------------------
void CVisionStatic::SetInit(int nUnit, double dZoomFac, CPoint clPtSize)
{
	int i = 0;
	m_nUnit = nUnit;
	m_nCamNo = nUnit;
	m_dZoomFac = dZoomFac;
	m_clCamSize = clPtSize;

	//TRACE("CamNo:%d, ZoomFac:%lf, Size:%ld,%ld", nCamNo, dZoomFac, clPtSize.x, clPtSize.y);

	m_clDisplaySize.x = (LONG)(m_clCamSize.x * m_dZoomFac);
	m_clDisplaySize.y = (LONG)(m_clCamSize.y * m_dZoomFac);
	m_clScrollPos = 0;
	m_clClickPoint = 0;

	m_nDragType = 0;
	m_bDrag = false;
	m_bRButtonUp = false;

	m_nMeasureStep = MEASURE_START;
	m_bClick = false;
	m_bDrawLine = false;
	m_nDragDistType = 0;
	m_nBoxDrawType = 0;

	m_nCursorType = 0;
	m_clClickPoint = 0;

	m_clMeasure[0].x = (m_clCamSize.x / 2) - 30;
	m_clMeasure[0].y = (m_clCamSize.y / 2) - 30;
	m_clMeasure[1].x = (m_clCamSize.x / 2) + 30;
	m_clMeasure[1].y = (m_clCamSize.y / 2) + 30;

	m_bLock = false;
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		m_nSfrSizeX[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeX[i];
		m_nSfrSizeY[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeY[i];
	}

	for (i = 0; i < MAX_FOV_COUNT; i++)
	{
		m_nFovSizeX[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeX[i];
		m_nFovSizeY[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeY[i];
	}
	m_nCenterSfrSizeX = 150;
	m_nCenterSfrSizeY = 150;


	
		
    m_FovSetMode = false;
    m_SnrSetMode = false;
	::ShowScrollBar(this->GetSafeHwnd(), SB_HORZ, FALSE);
	::ShowScrollBar(this->GetSafeHwnd(), SB_VERT, FALSE);

#ifdef ON_LINE_MIL
	/*if (g_clVision.m_MilDisplay[m_nCamNo])
	{
		MdispZoom(g_clVision.m_MilDisplay[m_nCamNo], m_dZoomFac, m_dZoomFac);
		this->ImageScroll();
	}*/

	

	m_nCenterSfrSizeX = g_clModelData[m_nUnit].m_clSfrInfo.m_nCenSizeX;
	m_nCenterSfrSizeY = g_clModelData[m_nUnit].m_clSfrInfo.m_nCenSizeY;

	this->ClearMeasure();
#endif
	this->LoadStandardCursor();

    this->SetSfrRoi();
    this->SetFovRoi();
    this->SetSnrRoi();
}

//-----------------------------------------------------------------------------
//
//	Display Zoom
//
//-----------------------------------------------------------------------------
void CVisionStatic::DisplayZoom()
{
#ifndef ON_LINE_MIL
	return;
#endif
	double dMaxZoomFac = 0.0;
	
	dMaxZoomFac = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
	
	if (g_clVision.m_MilDisplay[m_nUnit])
	{
		if (m_dZoomFac <= dMaxZoomFac)
		{
			m_clScrollPos.x = m_clScrollPos.y = 0;
		}

		this->InitScroll();
		MdispZoom(g_clVision.m_MilDisplay[m_nUnit], m_dZoomFac, m_dZoomFac);

		this->ImageScroll();
		Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//	커서 로드
//
//-----------------------------------------------------------------------------
void CVisionStatic::LoadStandardCursor()
{
	m_hCursorStd = NULL;
	m_hCursorWidth = NULL;
	m_hCursorHeight = NULL;
	m_hCursorMove = NULL;
	m_hCursorNWSE = NULL;
	m_hCursorNESW = NULL;

	m_hCursorStd = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hCursorWidth = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_hCursorHeight = AfxGetApp()->LoadStandardCursor(IDC_SIZENS);
	m_hCursorMove = AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
	m_hCursorNWSE = AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE);
	m_hCursorNESW = AfxGetApp()->LoadStandardCursor(IDC_SIZENESW);
}

//-----------------------------------------------------------------------------
//
//	커서 변경
//
//-----------------------------------------------------------------------------
void CVisionStatic::ChangeCursor(int nType)
{
	switch (nType)
	{
	case STANDARD:		::SetCursor(m_hCursorStd);		break;
	case CENTER:		::SetCursor(m_hCursorMove);		break;
	case LEFT:			::SetCursor(m_hCursorWidth);	break;
	case LEFTTOP:		::SetCursor(m_hCursorNWSE);		break;
	case LEFTBOTTOM:	::SetCursor(m_hCursorNESW);		break;
	case RIGHT:			::SetCursor(m_hCursorWidth);	break;
	case RIGHTTOP:		::SetCursor(m_hCursorNESW);		break;
	case RIGHTBOTTOM:	::SetCursor(m_hCursorNWSE);		break;
	case TOP:			::SetCursor(m_hCursorHeight);	break;
	case BOTTOM:		::SetCursor(m_hCursorHeight);	break;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CVisionStatic::ChangeCursorMeasureMode(CPoint clPoint)
{
#ifndef ON_LINE_MIL
	return 0;
#endif

	double dZoomX, dZoomY;
	CPoint clDrawOffset;
	CPoint cpDraw;
	CPoint p;
	int nRetVal;
	int nGap;

	nRetVal = -1;
	nGap = 20;
	dZoomX = dZoomY = 0.0;

	if (m_dZoomFac >= 1)
		dZoomX = dZoomY = (double)(1.0 * m_dZoomFac);
	else
		dZoomX = dZoomY = (double)(1.0 / m_dZoomFac);

	clDrawOffset.x = (int)(m_clScrollPos.x / m_dZoomFac);
	clDrawOffset.y = (int)(m_clScrollPos.y / m_dZoomFac);

	if (m_dZoomFac >= 1)
	{
		p.x = (int)(clPoint.x / dZoomX + 0.5) + clDrawOffset.x;
		p.y = (int)(clPoint.y / dZoomY + 0.5) + clDrawOffset.y;
	}
	else
	{
		p.x = (int)(clPoint.x * dZoomX + 0.5) + clDrawOffset.x;
		p.y = (int)(clPoint.y * dZoomY + 0.5) + clDrawOffset.y;
	}
	

	TRACE("m_clMeasure[0].x(%d) - nGap(%d) < p.x(%d)", m_clMeasure[0].x, nGap, p.x);

	if (m_clMeasure[0].x - nGap < p.x && m_clMeasure[0].x + nGap > p.x)
	{
		::SetCursor(m_hCursorWidth);
		nRetVal = 1;
	}
	else if (m_clMeasure[0].y - nGap < p.y && m_clMeasure[0].y + nGap > p.y)
	{
		::SetCursor(m_hCursorHeight);
		nRetVal = 2;
	}
	else if (m_clMeasure[1].x - nGap < p.x && m_clMeasure[1].x + nGap > p.x)
	{
		::SetCursor(m_hCursorWidth);
		nRetVal = 3;
	}
	else if (m_clMeasure[1].y - nGap < p.y && m_clMeasure[1].y + nGap > p.y)
	{
		::SetCursor(m_hCursorHeight);
		nRetVal = 4;
	}

	return nRetVal;
}

//-----------------------------------------------------------------------------
//
//FOV 박스 이동
//
//-----------------------------------------------------------------------------
void CVisionStatic::SetDrawMoveFov(int nRefIndex, CPoint clPoint)
{
	int		i = 0;
	int		nMoveValue = 0;
	double dDispFacX = 0.0;
	double dDispFacY = 0.0;

	dDispFacX = ((double)g_clModelData[m_nUnit].m_nWidth / (double)CCD1_DISP_SIZE_X);
	dDispFacY = ((double)g_clModelData[m_nUnit].m_nHeight / (double)CCD1_DISP_SIZE_Y);

	switch (m_nCursorType)
	{
	case CENTER:
		m_clPtFovOffset[nRefIndex].x = (int)(clPoint.x * dDispFacX) - (m_nFovSizeX[nRefIndex] / 2);
		m_clPtFovOffset[nRefIndex].y = (int)(clPoint.y * dDispFacY) - (m_nFovSizeY[nRefIndex] / 2);
		break;

	case LEFT:// LEFT 라인을 움직이면 좌표는 이동량만큼 '-' , 사이즈는 이동량만큼 '+'
		nMoveValue = m_clPtFovOffset[nRefIndex].x - (int)(clPoint.x * dDispFacX);
		m_nFovSizeX[nRefIndex] += nMoveValue;
		m_clPtFovOffset[nRefIndex].x -= nMoveValue;
		break;

	case RIGHT:// RIGHT 라인을 움직이면 좌표는 안움직이고 , 사이즈는 이동량만큼 '-'
		nMoveValue = (m_clPtFovOffset[nRefIndex].x + m_nFovSizeX[nRefIndex]) - (int)(clPoint.x * dDispFacX);
		m_nFovSizeX[nRefIndex] -= nMoveValue;
		break;

	case TOP:// TOP 라인을 움직이면 좌표는 이동량만큼 '-' , 사이즈는 이동량만큼 '+'
		nMoveValue = m_clPtFovOffset[nRefIndex].y - (int)(clPoint.y * dDispFacY);
		m_nFovSizeY[nRefIndex] += nMoveValue;
		m_clPtFovOffset[nRefIndex].y -= nMoveValue;
		break;

	case BOTTOM:// BOTTOM 라인을 움직이면 좌표 는 안움직이고 , 사이즈는 이동량만큼 '-'
		nMoveValue = (m_clPtFovOffset[nRefIndex].y + m_nFovSizeY[nRefIndex]) - (int)(clPoint.y * dDispFacY);
		m_nFovSizeY[nRefIndex] -= nMoveValue;
		break;

	default:
		return;
	}
}



//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::SetDrawMoveSfr(int nRefIndex, CPoint clPoint)
{
	int		i = 0;
	int		nMoveValue = 0;
	double dDispFacX = 0.0;
	double dDispFacY = 0.0;
	
	//if(g_clModelData[m_nCamNo].m_nDomeChartUse != 1)
	//	return;

	dDispFacX = ((double)g_clModelData[m_nUnit].m_nWidth / (double)CCD1_DISP_SIZE_X);
	dDispFacY = ((double)g_clModelData[m_nUnit].m_nHeight / (double)CCD1_DISP_SIZE_Y);

	switch (m_nCursorType)
	{
	case CENTER:
		m_clPtSfrOffset[nRefIndex].x = (int)(clPoint.x * dDispFacX) - (m_nSfrSizeX[nRefIndex] / 2);
		m_clPtSfrOffset[nRefIndex].y = (int)(clPoint.y * dDispFacY) - (m_nSfrSizeY[nRefIndex] / 2);
		break;
	case LEFT:// LEFT 라인을 움직이면 좌표는 이동량만큼 '-' , 사이즈는 이동량만큼 '+'
		nMoveValue = m_clPtSfrOffset[nRefIndex].x - (int)(clPoint.x * dDispFacX);
		m_nSfrSizeX[nRefIndex] += nMoveValue;
		
		m_clPtSfrOffset[nRefIndex].x -= nMoveValue;
		
		break;
	case RIGHT:// RIGHT 라인을 움직이면 좌표는 안움직이고 , 사이즈는 이동량만큼 '-'
		
		nMoveValue = (m_clPtSfrOffset[nRefIndex].x + m_nSfrSizeX[nRefIndex]) - (int)(clPoint.x * dDispFacX);
		m_nSfrSizeX[nRefIndex] -= nMoveValue;

		break;
	case TOP:// TOP 라인을 움직이면 좌표는 이동량만큼 '-' , 사이즈는 이동량만큼 '+'
		nMoveValue = m_clPtSfrOffset[nRefIndex].y - (int)(clPoint.y * dDispFacY);
		m_nSfrSizeY[nRefIndex] += nMoveValue;
		
		m_clPtSfrOffset[nRefIndex].y -= nMoveValue;

		break;
	case BOTTOM:// BOTTOM 라인을 움직이면 좌표 는 안움직이고 , 사이즈는 이동량만큼 '-'
		
		nMoveValue = (m_clPtSfrOffset[nRefIndex].y + m_nSfrSizeY[nRefIndex]) - (int)(clPoint.y * dDispFacY);
		m_nSfrSizeY[nRefIndex] -= nMoveValue;
		break;
	default:
		return;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::SetDrawMoveCircle(int nRefIndex, CPoint clPoint)
{
	int		nMoveValue = 0;
	int		nSx = 0, nSy = 0;
	double	dDispFacX = 0, dDispFacY = 0;
	CRect	clRectROI;

    dDispFacX = (double)g_clModelData[m_nCamNo].m_nWidth / (double)CCD2_DISP_SIZE_X;
    dDispFacY = (double)g_clModelData[m_nCamNo].m_nHeight / (double)CCD2_DISP_SIZE_Y;
	
	//clRectROI = m_clRectCircle[nRefIng_pAABonderDlg->m_pCcdDlg->m_pCcdSfrDlg->GetRectCircle(nRefIndex);

	switch (m_nCursorType)
	{
	case CENTER:
		nSx = m_clRectCircle[nRefIndex].right - m_clRectCircle[nRefIndex].left;
		nSy = m_clRectCircle[nRefIndex].bottom - m_clRectCircle[nRefIndex].top;

		m_clRectCircle[nRefIndex].left = (long)(clPoint.x * dDispFacX) - nSx / 2;
		m_clRectCircle[nRefIndex].top = (long)(clPoint.y * dDispFacY) - nSy / 2;
		m_clRectCircle[nRefIndex].right = (long)(clPoint.x * dDispFacX) + nSx / 2;
		m_clRectCircle[nRefIndex].bottom = (long)(clPoint.y * dDispFacY) + nSy / 2;		
		break;
	case LEFT:
		nMoveValue = m_clRectCircle[nRefIndex].left - (int)(clPoint.x * dDispFacX);
		m_clRectCircle[nRefIndex].left -= nMoveValue;		
		break;
	case RIGHT:
		nMoveValue = m_clRectCircle[nRefIndex].right - (int)(clPoint.x * dDispFacX);
		m_clRectCircle[nRefIndex].right -= nMoveValue;		
		break;
	case TOP:
		nMoveValue = m_clRectCircle[nRefIndex].top - (int)(clPoint.y * dDispFacY);
		m_clRectCircle[nRefIndex].top -= nMoveValue;		
		break;
	case BOTTOM:
		nMoveValue = m_clRectCircle[nRefIndex].bottom - (int)(clPoint.y * dDispFacY);
		m_clRectCircle[nRefIndex].bottom -= nMoveValue;		
		break;

	default:
		return;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::DestroyCursor()
{
	if (m_hCursorStd != NULL)
		::DestroyCursor(m_hCursorStd);

	if (m_hCursorWidth != NULL)
		::DestroyCursor(m_hCursorWidth);

	if (m_hCursorHeight != NULL)
		::DestroyCursor(m_hCursorHeight);

	if (m_hCursorMove != NULL)
		::DestroyCursor(m_hCursorMove);

	if (m_hCursorNWSE != NULL)
		::DestroyCursor(m_hCursorNWSE);

	if (m_hCursorNESW != NULL)
		::DestroyCursor(m_hCursorNESW);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CVisionStatic::GetLineType()
{
#ifndef ON_LINE_MIL
	return 0;
#endif

	int nType;

	nType = 0;

	if ((m_clClickPoint.x > (m_clDrawBox.centerX - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.x < (m_clDrawBox.centerX + MOUSE_DRAG_SIZE_X)) &&
		(m_clClickPoint.y >(m_clDrawBox.centerY - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.y < (m_clDrawBox.centerY + MOUSE_DRAG_SIZE_X)))
	{
		nType = CENTER;
	}
	else if ((m_clClickPoint.x >(m_clDrawBox.left - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.x < (m_clDrawBox.left + MOUSE_DRAG_SIZE_X)) &&
		(m_clClickPoint.y >(m_clDrawBox.top + MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.bottom - MOUSE_DRAG_SIZE_Y)))
	{
		nType = LEFT;
	}
	else if ((m_clClickPoint.x >(m_clDrawBox.left - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.x < (m_clDrawBox.left + MOUSE_DRAG_SIZE_X)) &&
		(m_clClickPoint.y >(m_clDrawBox.top - MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.top + MOUSE_DRAG_SIZE_Y)))
	{
		nType = LEFTTOP;
	}
	else if ((m_clClickPoint.x >(m_clDrawBox.left - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.x < (m_clDrawBox.left + MOUSE_DRAG_SIZE_X)) &&
		(m_clClickPoint.y >(m_clDrawBox.bottom - MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.bottom + MOUSE_DRAG_SIZE_Y)))
	{
		nType = LEFTBOTTOM;
	}
	else if ((m_clClickPoint.x >(m_clDrawBox.right - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.x <(m_clDrawBox.right + MOUSE_DRAG_SIZE_X)) &&
		(m_clClickPoint.y >(m_clDrawBox.top + MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.bottom - MOUSE_DRAG_SIZE_Y)))
	{
		nType = RIGHT;
	}
	else if ((m_clClickPoint.x >(m_clDrawBox.right - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.x < (m_clDrawBox.right + MOUSE_DRAG_SIZE_X)) &&
		(m_clClickPoint.y >(m_clDrawBox.top - MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.top + MOUSE_DRAG_SIZE_Y)))
	{
		nType = RIGHTTOP;
	}
	else if ((m_clClickPoint.x >(m_clDrawBox.right - MOUSE_DRAG_SIZE_X)) && (m_clClickPoint.x < (m_clDrawBox.right + MOUSE_DRAG_SIZE_X)) &&
		(m_clClickPoint.y >(m_clDrawBox.bottom - MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.bottom + MOUSE_DRAG_SIZE_Y)))
	{
		nType = RIGHTBOTTOM;
	}
	else if ((m_clClickPoint.x > m_clDrawBox.left) && (m_clClickPoint.x < m_clDrawBox.right) &&
		(m_clClickPoint.y >(m_clDrawBox.top - MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.top + MOUSE_DRAG_SIZE_Y)))
	{
		nType = TOP;
	}
	else if ((m_clClickPoint.x > m_clDrawBox.left) && (m_clClickPoint.x < m_clDrawBox.right) &&
		(m_clClickPoint.y >(m_clDrawBox.bottom - MOUSE_DRAG_SIZE_Y)) && (m_clClickPoint.y < (m_clDrawBox.bottom + MOUSE_DRAG_SIZE_Y)))
	{
		nType = BOTTOM;
	}
	else
	{
		nType = STANDARD;
	}

	return nType;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::InitScroll()
{
#ifndef ON_LINE_MIL
	return;
#endif

	double dZoomDispSize;
	SCROLLINFO si;
	double dMaxZoomFac;
	
	dMaxZoomFac = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);

	//### H-Scroll Settine(X축)
	dZoomDispSize = (double)(m_clCamSize.x * m_dZoomFac);

	if (m_dZoomFac == dMaxZoomFac)
	{
		::ShowScrollBar(this->GetSafeHwnd(), SB_HORZ, FALSE);
	}
	else
	{
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		si.nPage = (UINT)(dZoomDispSize / 10);
		si.nMax = (UINT)(dZoomDispSize - m_clDisplaySize.x + si.nPage + 17);		//전체 Size - Display되는 Size + 한페이지크기 + Scroll 크기
		si.nMin = 0;
		si.nPos = (UINT)(m_clScrollPos.x / m_dZoomFac);
		si.nTrackPos = 0;
		::ShowScrollBar(this->GetSafeHwnd(), SB_HORZ, TRUE);
		this->SetScrollInfo(SB_HORZ, &si);
	}

	//### V-Scroll Settine(Y축)	
	dZoomDispSize = (double)(m_clCamSize.y * m_dZoomFac);

	if (m_dZoomFac == dMaxZoomFac)
	{
		::ShowScrollBar(this->GetSafeHwnd(), SB_VERT, FALSE);
	}
	else
	{
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		si.nPage = (UINT)(dZoomDispSize / 10);
		si.nMax = (UINT)(dZoomDispSize - m_clDisplaySize.y + si.nPage + 17);		//전체 Size - Display되는 Size + 한페이지크기 + Scroll 크기
		si.nMin = 0;
		si.nPos = (UINT)(m_clScrollPos.y / m_dZoomFac);							//처음 기본값
		si.nTrackPos = 0;

		::ShowScrollBar(this->GetSafeHwnd(), SB_VERT, TRUE);
		this->SetScrollInfo(SB_VERT, &si);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::PlusZoom()
{
#ifndef ON_LINE_MIL
	return;
#endif

	if (m_dZoomFac <= 3)
		m_dZoomFac *= 1.2;

	this->DisplayZoom();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::MinusZoom()
{
#ifndef ON_LINE_MIL
	return;
#endif

	if (m_dZoomFac <= 3)
		m_dZoomFac /= 1.2;

	this->DisplayZoom();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::ImageScroll()
{
#ifndef ON_LINE_MIL
	return;
#endif

	if (g_clVision.m_MilDisplay[m_nUnit])
	{
		MdispPan(g_clVision.m_MilDisplay[m_nUnit], (MIL_DOUBLE)((double)m_clScrollPos.x / m_dZoomFac),
			(MIL_DOUBLE)((double)m_clScrollPos.y / m_dZoomFac));
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::DrawRect(CPoint clPoint, CPoint clPtSize)
{
#ifndef ON_LINE_MIL
	return;
#endif

	//## 실 Size로 변환(현재는 Zoom기능을 쓰고 있는 상태)
	//추가해야함	converter
	int sx, sy, ex, ey, cx, cy;
	
	double dZoomX;
	double dZoomY;

	dZoomX = dZoomY = 0.0;
	sx = sy = ex = ey = cx = cy = 0;

	if (m_dZoomFac >= 1)
		dZoomX = dZoomY = (double)(1.0 * m_dZoomFac);
	else
		dZoomX = dZoomY = (double)(1.0 / m_dZoomFac);
	
	if (g_pCarAABonderDlg->m_bCamState[m_nUnit] == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		int nSx, nSy, nEx, nEy, nCx, nCy;
		CPoint clPtDrawOffset;
		CPoint clPtDrawCenter;


		if (m_dZoomFac >= 1)
		{
			nSx = (int)(clPoint.x / dZoomX);
			nSy = (int)(clPoint.y / dZoomY);
			nEx = (int)((clPoint.x + clPtSize.x) / dZoomX);
			nEy = (int)((clPoint.y + clPtSize.y) / dZoomY);

			nCx = (int)(nSx + (clPtSize.x >> 1) / m_dZoomFac);
			nCy = (int)(nSy + (clPtSize.y >> 1) / m_dZoomFac);

		}
		else
		{
			nSx = (int)(clPoint.x * dZoomX);
			nSy = (int)(clPoint.y * dZoomY);
			nEx = (int)((clPoint.x + clPtSize.x) * dZoomX);
			nEy = (int)((clPoint.y + clPtSize.y) * dZoomY);

			nCx = (int)(nSx + ((clPtSize.x >> 1) / m_dZoomFac));
			nCy = (int)(nSy + ((clPtSize.y >> 1) / m_dZoomFac));
		}

		clPtDrawOffset.x = (int)(m_clScrollPos.x / m_dZoomFac);
		clPtDrawOffset.y = (int)(m_clScrollPos.y / m_dZoomFac);

		m_clRect.left = (int)(nSx + clPtDrawOffset.x);
		m_clRect.top = (int)(nSy + clPtDrawOffset.y);
		m_clRect.right = (int)(nEx + clPtDrawOffset.x);
		m_clRect.bottom = (int)(nEy + clPtDrawOffset.y);

		m_clRectRoi = m_clRect;

		g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);

		clPtDrawCenter.x = nCx + clPtDrawOffset.x;
		clPtDrawCenter.y = nCy + clPtDrawOffset.y;

		if (m_dZoomFac >= 1) 
		{
			g_clVision.DrawMOverlayBox(m_nUnit, m_nCamNo, m_clRect, RGB_COLOR_BLUE, 1, 1, 0, VIDEO_CAM);
			g_clVision.DrawMOverlayCross(m_nUnit, m_nCamNo, clPtDrawCenter, 20, RGB_COLOR_BLUE, 1,1,9);
		}
		else
		{
			g_clVision.DrawMOverlayBox(m_nUnit, m_nCamNo, m_clRect, RGB_COLOR_BLUE, 1, 1, 0, VIDEO_CAM);
			g_clVision.DrawMOverlayCross(m_nUnit, m_nCamNo, clPtDrawCenter, 20, RGB_COLOR_BLUE, 1, 1, 9);// (int)ceil(dZoomX));
		}
	}
	else
	{


		if (m_dZoomFac >= 1)
		{
			sx = (int)(clPoint.x / dZoomX);
			sy = (int)(clPoint.y / dZoomY);
			ex = (int)((clPoint.x + clPtSize.x) / dZoomX);
			ey = (int)((clPoint.y + clPtSize.y) / dZoomY);

			cx = (int)(sx + (clPtSize.x >> 1) / m_dZoomFac);
			cy = (int)(sy + (clPtSize.y >> 1) / m_dZoomFac);

		}
		else
		{
			sx = (int)(clPoint.x * dZoomX);
			sy = (int)(clPoint.y * dZoomY);
			ex = (int)((clPoint.x + clPtSize.x) * dZoomX);
			ey = (int)((clPoint.y + clPtSize.y) * dZoomY);

			cx = (int)(sx + ((clPtSize.x >> 1) / m_dZoomFac));
			cy = (int)(sy + ((clPtSize.y >> 1) / m_dZoomFac));
		}

		CPoint clDrawOffset;
		clDrawOffset.x = (int)(m_clScrollPos.x / m_dZoomFac);
		clDrawOffset.y = (int)(m_clScrollPos.y / m_dZoomFac);

		m_clRect.left = (int)(clDrawOffset.x + sx);
		m_clRect.top = (int)(clDrawOffset.y + sy);
		m_clRect.right = (int)(clDrawOffset.x + ex);
		m_clRect.bottom = (int)(clDrawOffset.y + ey);

		g_clVision.ClearOverlay(m_nUnit);

		CPoint clDrawCenter;
		clDrawCenter.x = clDrawOffset.x + cx;
		clDrawCenter.y = clDrawOffset.y + cy;

		g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRect, RGB(0, 0, 255), 1);
		g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, clDrawCenter, 11, RGB(0, 0, 255), 1);
	}
	
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::DrawMeasure(CPoint clPoint)
{
#ifndef ON_LINE_MIL
	return;
#endif

	double dZoomX;
	double dZoomY;
	CPoint clDrawOffset;
	CPoint clDrawPt;

	dZoomX = dZoomY = 0.0;

	if (m_dZoomFac >= 1)
		dZoomX = dZoomY = (double)(1.0 * m_dZoomFac);
	else
		dZoomX = dZoomY = (double)(1.0 / m_dZoomFac);
	

	clDrawOffset.x = (int)(m_clScrollPos.x / m_dZoomFac);
	clDrawOffset.y = (int)(m_clScrollPos.y / m_dZoomFac);


	if (m_dZoomFac >= 1) {
		clDrawPt.x = (int)(clPoint.x / dZoomX) + clDrawOffset.x;
		clDrawPt.y = (int)(clPoint.y / dZoomY) + clDrawOffset.y;
	}
	else
	{
		clDrawPt.x = (int)(clPoint.x * dZoomX) + clDrawOffset.x;
		clDrawPt.y = (int)(clPoint.y * dZoomY) + clDrawOffset.y;
	}

	g_clVision.ClearOverlay(m_nUnit);

	if (m_nMeasureStep == (int)MEASURE_START)
	{
		m_clMeasure[0] = clDrawPt;
		g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, m_clMeasure[0], 20, RGB(255, 0, 0), 1);
		g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, m_clMeasure[1], 20, RGB(255, 0, 0), 2);
	}
	else if (m_nMeasureStep == (int)MEASURE_END)
	{
		m_clMeasure[1] = clDrawPt;
		g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, m_clMeasure[0], 20, RGB(0, 255, 0), 1);
		g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, m_clMeasure[1], 20, RGB(255, 0, 0), 1);

	}
	else if (m_nMeasureStep == (int)MEASURE_COMPLETE)
	{
		g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, m_clMeasure[0], 20, RGB(0, 255, 0), 1);
		g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, m_clMeasure[1], 20, RGB(0, 255, 0), 1);
		g_clVision.DrawOverlayLine(m_nUnit, m_clMeasure[0], m_clMeasure[1], RGB(0, 255, 0), 1);
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CVisionStatic::ClearMeasure()
{
	m_nMeasureStep = MEASURE_START;
	m_clMeasure[0].x = m_clCamSize.x / 2 - 30;
	m_clMeasure[0].y = m_clCamSize.y / 2 - 30;
	m_clMeasure[1].x = m_clCamSize.x / 2 + 30;
	m_clMeasure[1].y = m_clCamSize.y / 2 + 30;
}

//-----------------------------------------------------------------------------
//
//	거리측정 오버레이 그린다.(AA는 비전 카메라가 없기 때문에 분해능 없음)
//
//-----------------------------------------------------------------------------
void CVisionStatic::DrawDistance()
{
	//TCHAR szMsg[SIZE_OF_100BYTE];

	//g_clVision.ClearOverlay(m_nCamNo);

	//// 원Image 크기보다 크게 보려고 할 경우
	//if (m_dZoomFac >= 1)
	//{
	//	g_clVision.DrawOverlayLine(m_nCamNo, m_clMeasure[0].x, 0, m_clMeasure[0].x, m_clCamSize.y, M_COLOR_RED, 1);
	//	g_clVision.DrawOverlayLine(m_nCamNo, 0, m_clMeasure[0].y, m_clCamSize.x, m_clMeasure[0].y, M_COLOR_MAGENTA, 1);

	//	g_clVision.DrawOverlayLine(m_nCamNo, m_clMeasure[1].x, 0, m_clMeasure[1].x, m_clCamSize.y, M_COLOR_RED, 1);
	//	g_clVision.DrawOverlayLine(m_nCamNo, 0, m_clMeasure[1].y, m_clCamSize.x, m_clMeasure[1].y, M_COLOR_MAGENTA, 1);
	//}
	//else
	//{
	//	g_clVision.DrawOverlayLine(m_nCamNo, m_clMeasure[0].x, 0, m_clMeasure[0].x, m_clCamSize.y, M_COLOR_RED, (int)(1.0 / m_dZoomFac + 0.5));
	//	g_clVision.DrawOverlayLine(m_nCamNo, 0, m_clMeasure[0].y, m_clCamSize.x, m_clMeasure[0].y, M_COLOR_MAGENTA, (int)(1.0 / m_dZoomFac + 0.5));

	//	g_clVision.DrawOverlayLine(m_nCamNo, m_clMeasure[1].x, 0, m_clMeasure[1].x, m_clCamSize.y, M_COLOR_RED, (int)(1.0 / m_dZoomFac + 0.5));
	//	g_clVision.DrawOverlayLine(m_nCamNo, 0, m_clMeasure[1].y, m_clCamSize.x, m_clMeasure[1].y, M_COLOR_MAGENTA, (int)(1.0 / m_dZoomFac + 0.5));
	//}

	//_stprintf_s(szMsg, SIZE_OF_100BYTE, _T("GAP-X : %.04lf"), abs(m_clMeasure[0].x - m_clMeasure[1].x) * g_clSysData.m_clCamResol[m_nCamNo].x);
	//g_clVision.DrawOverlayText(m_nCamNo, 5, m_clCamSize.y - 120, szMsg, M_COLOR_GREEN, _T("Arial"), 18, 26);

	//_stprintf_s(szMsg, SIZE_OF_100BYTE, _T("GAP-Y : %.04lf"), abs(m_clMeasure[0].y - m_clMeasure[1].y) * g_clSysData.m_clCamResol[m_nCamNo].y);
	//g_clVision.DrawOverlayText(m_nCamNo, 5, m_clCamSize.y - 60, szMsg, M_COLOR_GREEN, _T("Arial"), 18, 26);
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CVisionStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect clRect;
	CRect clRectCenter;
	CPoint clPtDragStart;
	CPoint clPtDragSize;

	CPoint clPtCamDragStart;
	CPoint clPtCamDragSize;

	//int nIndex;

	if (m_bLock == true)
		return;

	//if (m_nCamNo == 0 || m_nCamNo == 1)
	if (g_pCarAABonderDlg->m_bCamState[m_nUnit] == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		if (m_bDragUse == false)
			return;
		switch (m_nDragFlag)
		{
		case MOUSE_DRAG:
			m_bClickFlag = true;
			m_clClickPoint = point;

			// 기존 박스를 편집할때
			if (m_nCursorType > 0)
				m_nType = SQUARE_RESIZE;

			// 박스를 이동 할때
			if (m_nType != SQUARE_RESIZE)
			{
				clRect.left = (LONG)(m_clDRect.centerX - MOUSE_DRAG_SIZE_X);
				clRect.right = (LONG)(m_clDRect.centerX + MOUSE_DRAG_SIZE_X);
				clRect.top = (LONG)(m_clDRect.centerY - MOUSE_DRAG_SIZE_Y);
				clRect.bottom = (LONG)(m_clDRect.centerY + MOUSE_DRAG_SIZE_Y);

				// 선택한 좌표가 박스의 중심 위치면 박스 이동
				if (m_clClickPoint.x > clRect.left && m_clClickPoint.x < clRect.right &&
					m_clClickPoint.y > clRect.top && m_clClickPoint.y < clRect.bottom)
				{
					m_nType = SQUARE_MOVE;
				}
			}

			// 새로운 박스를 생성할때
			if (m_nType != SQUARE_RESIZE && m_nType != SQUARE_MOVE)
			{
				if (m_clClickPoint.x > m_clDRect.left && m_clClickPoint.x < m_clDRect.right &&
					m_clClickPoint.y > m_clDRect.top && m_clClickPoint.y < m_clDRect.bottom)
					return;

				if (m_clDRect.cnt > 0)
					m_clDRect.cnt--;

				m_nType = SQUARE_CREATE;

				m_clDRect.left = m_clClickPoint.x;
				m_clDRect.top = m_clClickPoint.y;
				m_clDRect.right = m_clClickPoint.x;
				m_clDRect.bottom = m_clClickPoint.y;

				clPtCamDragStart.x = (m_clDRect.left < m_clDRect.right) ? (LONG)m_clDRect.left : (LONG)m_clDRect.right;
				clPtCamDragStart.y = (m_clDRect.top < m_clDRect.bottom) ? (LONG)m_clDRect.top : (LONG)m_clDRect.bottom;

				clPtCamDragSize.x = (LONG)(abs(m_clDRect.left - m_clDRect.right));
				clPtCamDragSize.y = (LONG)(abs(m_clDRect.top - m_clDRect.bottom));

				this->DrawRect(clPtCamDragStart, clPtCamDragSize);
			}
			SetCapture();

			break;
		case DIST_CHECK:
			m_clClickDist = point;
			m_bDrawLine = true;
			SetCapture();
			break;
		case DISP_MOVE:
			m_bClickFlag = true;
			m_clClickPoint = point;
			break;
		case MEASURE:
			m_bRButtonUp = true;
			m_bClickFlag = true;
			this->DrawMeasure(point);
			break;
		}

	}//여기까지 Cam
	else if (g_pCarAABonderDlg->m_bCamState[m_nUnit] == VIDEO_CCD)	//VIDEO_CAM , VIDEO_CCD
	{
		if (m_bDrag == false)
		{
			if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
			{
				m_nSelectIndexFOV = this->GetSelectedFovNo(point);
				if (m_nSelectIndexFOV != -1)
				{
					this->DrawRectFov(m_nSelectIndexFOV);

					m_bClick = true;
					m_nCursorType = this->GetSelectedCursor(point);
					//
					this->ChangeCursor(m_nCursorType);
				}
				return;
			}
			else
			{
				m_nSelectIndexCCD = this->GetSelectedSfrNo(point);

				if (m_nSelectIndexCCD != -1)
				{
					this->DrawRectSfr(m_nSelectIndexCCD);

					//! ROI를 선택 하였을 경우
					if (m_nSelectIndexCCD >= 0 && m_nSelectIndexCCD < MAX_LAST_INSP_COUNT + 4)
					{
						m_bClick = true;
						m_nCursorType = this->GetSelectedCursor(point);
						//
						this->ChangeCursor(m_nCursorType);
					}
				}
			}
			if (m_bClick == false)	//240614
			{
				//이미지 밝기 보이게
				g_clVision.ClearOverlay(m_nUnit);

				CPoint _Mp;
				TCHAR szTemp[SIZE_OF_100BYTE];
				int pos = 0;
				int width = 0;
				int textTempx = 10;
				int textTempy = 10;
				width = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, NULL);

				_Mp.x = point.x * g_clModelData[m_nUnit].m_nWidth / CCD1_DISP_SIZE_X;
				_Mp.y = point.y * g_clModelData[m_nUnit].m_nHeight / CCD1_DISP_SIZE_Y;


				g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, _Mp, 30, RGB(255, 0, 0), 1);
				if (_Mp.x > g_clModelData[m_nUnit].m_nWidth - (g_clModelData[m_nUnit].m_nWidth / 2))
				{
					textTempx = -900;
				}
				if (_Mp.y > (g_clModelData[m_nUnit].m_nHeight / 2))
				{
					textTempy = -200;
				}
				pos = _Mp.y * width + _Mp.x;
				_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("(X:%d,Y:%d)RGB %d,%d,%d"), _Mp.x, _Mp.y, g_clVision.m_pImgBuff[m_nUnit][0][pos], g_clVision.m_pImgBuff[m_nUnit][1][pos], g_clVision.m_pImgBuff[m_nUnit][2][pos]);
				g_clVision.DrawMOverlayText(m_nUnit, _Mp.x + textTempx, _Mp.y + textTempy, szTemp, M_COLOR_MAGENTA, _T("맑은 고딕"), 20, 10, FALSE);
				g_clVision.DrawOverlayAll(m_nUnit);
			}
		}
		else
		{
			switch (m_nDragType)
			{
			case MOUSE_DRAG:
				m_bClick = true;
				m_clClickPoint = point;

				// 기존 박스를 편집할 때
				if (m_nCursorType > 0)
					m_nBoxDrawType = SQUARE_RESIZE;

				// 박스를 이동시킬때
				if (m_nBoxDrawType != SQUARE_RESIZE)
				{
					clRectCenter.left = (LONG)(m_clDrawBox.centerX - MOUSE_DRAG_SIZE_X);
					clRectCenter.right = (LONG)(m_clDrawBox.centerX + MOUSE_DRAG_SIZE_X);
					clRectCenter.top = (LONG)(m_clDrawBox.centerY - MOUSE_DRAG_SIZE_Y);
					clRectCenter.bottom = (LONG)(m_clDrawBox.centerY + MOUSE_DRAG_SIZE_Y);

					// 선택한 좌표가 박스이 중심이라면 박스 이동
					if (m_clClickPoint.x > clRectCenter.left && m_clClickPoint.x < clRectCenter.right &&
						m_clClickPoint.y > clRectCenter.top && m_clClickPoint.y < clRectCenter.bottom)
					{
						m_nBoxDrawType = SQUARE_MOVE;
					}
				}

				// 새로운 박스를 생성할때
				if (m_nBoxDrawType != SQUARE_RESIZE && m_nBoxDrawType != SQUARE_MOVE)
				{
					if (m_clClickPoint.x > m_clDrawBox.left && m_clClickPoint.x < m_clDrawBox.right &&
						m_clClickPoint.y > m_clDrawBox.top && m_clClickPoint.y < m_clDrawBox.bottom)
					{
						return;
					}

					if (m_clDrawBox.cnt > 0)
						m_clDrawBox.cnt--;

					m_nBoxDrawType = SQUARE_CREATE;

					m_clDrawBox.left = m_clClickPoint.x;
					m_clDrawBox.top = m_clClickPoint.y;
					m_clDrawBox.right = m_clClickPoint.x;
					m_clDrawBox.bottom = m_clClickPoint.y;

					clPtDragStart.x = m_clDrawBox.left < m_clDrawBox.right ? (LONG)m_clDrawBox.left : (LONG)m_clDrawBox.right;
					clPtDragStart.y = m_clDrawBox.top < m_clDrawBox.bottom ? (LONG)m_clDrawBox.top : (LONG)m_clDrawBox.bottom;
					clPtDragSize.x = (LONG)(abs(m_clDrawBox.left - m_clDrawBox.right));
					clPtDragSize.y = (LONG)(abs(m_clDrawBox.top - m_clDrawBox.bottom));

					this->DrawRect(clPtDragStart, clPtDragSize);
				}

				SetCapture();
				break;
			case DIST_CHECK:
				m_clClickDist = point;
				m_bDrawLine = true;
				SetCapture();
				break;
			case DISP_MOVE:
				m_bClick = true;
				m_clClickPoint = point;
				break;
			case MEASURE:
				m_bRButtonUp = true;
				m_bClick = true;
				this->DrawMeasure(point);

				break;
			default:
				break;
			}
		}
	}
	CStatic::OnLButtonDown(nFlags, point);
}


//-----------------------------------------------------------------------------
//
//	선택된 SNR ROI 영역 인덱스 반환
//
//-----------------------------------------------------------------------------
int CVisionStatic::GetSelectedSNRNo(CPoint point)
{
    CRect clRect;
    CPoint clPtPos;
    int nSelectNo;
    int i;

    clPtPos.x = (int)((point.x * ((double)g_clModelData[m_nUnit].m_nWidth / (double)CCD1_DISP_SIZE_X)) + 0.5);
    clPtPos.y = (int)((point.y * ((double)g_clModelData[m_nUnit].m_nHeight / (double)CCD1_DISP_SIZE_Y)) + 0.5);
    //
    for (i = 0; i < MAX_SNR_COUNT; i++)
    {
        if (PtInRect(m_clRectDrawSnr[i], clPtPos) == TRUE)
        {
            nSelectNo = i;
            return nSelectNo;
        }
    }
    return -1;
}
//-----------------------------------------------------------------------------
//
//	선택된 FOV ROI 영역 인덱스 반환
//
//-----------------------------------------------------------------------------
int CVisionStatic::GetSelectedFovNo(CPoint point)
{
    CRect clRect;
    CPoint clPtPos;
    int nSelectNo;
    int i;

    clPtPos.x = (int)((point.x * ((double)g_clModelData[m_nUnit].m_nWidth / (double)CCD1_DISP_SIZE_X)) + 0.5);
    clPtPos.y = (int)((point.y * ((double)g_clModelData[m_nUnit].m_nHeight / (double)CCD1_DISP_SIZE_Y)) + 0.5);
    //
    for (i = 0; i < MAX_FOV_COUNT; i++)
    {
		clRect.left = m_clPtFovOffset[i].x;
		clRect.top = m_clPtFovOffset[i].y;
		clRect.right = clRect.left + m_nFovSizeX[i];
		clRect.bottom = clRect.top + m_nFovSizeY[i];

		if (PtInRect(clRect, clPtPos) == TRUE)
		{
			nSelectNo = i;
			return nSelectNo;
		}


    }

    return -1;
}
//-----------------------------------------------------------------------------
//
//	선택된 SFR ROI 영역 인덱스 반환
//
//-----------------------------------------------------------------------------
int CVisionStatic::GetSelectedSfrNo(CPoint point)
{
	CRect clRect;
	CPoint clPtPos;
	int nSelectNo;
	int i;

    clPtPos.x = (int)((point.x * ((double)g_clModelData[m_nUnit].m_nWidth / (double)CCD1_DISP_SIZE_X)) + 0.5);
    clPtPos.y = (int)((point.y * ((double)g_clModelData[m_nUnit].m_nHeight / (double)CCD1_DISP_SIZE_Y)) + 0.5);
    for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
    {
        clRect.left = m_clPtSfrOffset[i].x;
        clRect.top = m_clPtSfrOffset[i].y;
		clRect.right = clRect.left + m_nSfrSizeX[i];
		clRect.bottom = clRect.top + m_nSfrSizeY[i];

        if (PtInRect(clRect, clPtPos) == TRUE)
        {
            nSelectNo = i;
            return nSelectNo;
        }
    }

	for (i = 0; i < 4; i++)
	{
		if (PtInRect(m_clRectCircle[i], clPtPos) == TRUE)
		{
            nSelectNo = MAX_LAST_INSP_COUNT + i;
			return nSelectNo;
		}
	}

	return -1;
}

//-----------------------------------------------------------------------------
//
//	좌표로 선택 커서 타입 반환
//
//-----------------------------------------------------------------------------
int CVisionStatic::GetSelectedCursor(CPoint point)
{
	CDrawBox clRectBox;
	CPoint clPtPos;
	int nCount;
	int nMaxCount;
	int i;
	int nCursor = -1;



	int nSquareSelectSizeX = 0;// = m_nSfrSizeX / 2 - 12;
	int nSquareSelectSizeY = 0;// = m_nSfrSizeY / 2 - 12;

	int	iGap;

    clPtPos.x = (int)(point.x * (((double)g_clModelData[m_nUnit].m_nWidth / (double)CCD1_DISP_SIZE_X)) + 0.5);
    clPtPos.y = (int)(point.y * (((double)g_clModelData[m_nUnit].m_nHeight / (double)CCD1_DISP_SIZE_Y)) + 0.5);
	
	//clPtPos.x -= m_rectCamDispPos1.left;
	//clPtPos.y -= m_rectCamDispPos1.top;
    nCount = MAX_LAST_INSP_COUNT + 4;
    nMaxCount = MAX_LAST_INSP_COUNT;

	iGap = int((double)g_clModelData[m_nUnit].m_nWidth / (double)CCD1_DISP_SIZE_X * 6);// 5);


	if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
	{
		for (i = 0; i < MAX_FOV_COUNT; i++)
		{
			clRectBox.left = m_clPtFovOffset[i].x;
			clRectBox.top = m_clPtFovOffset[i].y;
			clRectBox.right = clRectBox.left + m_nFovSizeX[i];
			clRectBox.bottom = clRectBox.top + m_nFovSizeY[i];

			clRectBox.centerX = (clRectBox.left + clRectBox.right) / 2;
			clRectBox.centerY = (clRectBox.top + clRectBox.bottom) / 2;

			if ((clPtPos.x >(clRectBox.left + iGap)) &&
				(clPtPos.x < (clRectBox.right - iGap)) &&
				(clPtPos.y >(clRectBox.top + iGap)) &&
				(clPtPos.y < (clRectBox.bottom - iGap)))
			{
				return CENTER;
			}
			else if ((clPtPos.x >(clRectBox.left - iGap)) &&
				(clPtPos.x < (clRectBox.left + iGap)) &&
				(clPtPos.y >(clRectBox.top)) &&
				(clPtPos.y < (clRectBox.bottom)))
			{
				return LEFT;
			}
			else if ((clPtPos.x >(clRectBox.right - iGap)) &&
				(clPtPos.x < (clRectBox.right + iGap)) &&
				(clPtPos.y >(clRectBox.top)) &&
				(clPtPos.y < (clRectBox.bottom)))
			{
				return RIGHT;
			}
			else if ((clPtPos.x > clRectBox.left) &&
				(clPtPos.x < clRectBox.right) &&
				(clPtPos.y >(clRectBox.top - iGap)) &&
				(clPtPos.y < (clRectBox.top + iGap)))
			{
				return TOP;
			}
			else if ((clPtPos.x > clRectBox.left) &&
				(clPtPos.x < clRectBox.right) &&
				(clPtPos.y >(clRectBox.bottom - iGap)) &&//SQUARE_RESET_SIZE_X
				(clPtPos.y < (clRectBox.bottom + iGap)))
			{
				return BOTTOM;
			}
			else
			{
				nCursor = STANDARD;
			}
		}

		return nCursor;
	}
	for (i = 0; i < nCount; i++)
	{
		if (i < nMaxCount)	//! SFR 영역
		{
			clRectBox.left = m_clPtSfrOffset[i].x;
			clRectBox.top = m_clPtSfrOffset[i].y;
			clRectBox.right = clRectBox.left + m_nSfrSizeX[i];
			clRectBox.bottom = clRectBox.top + m_nSfrSizeY[i];

			clRectBox.centerX = (clRectBox.left + clRectBox.right) / 2;
			clRectBox.centerY = (clRectBox.top + clRectBox.bottom) / 2;
		}
		else  //! 원형마크 영역
		{
            
			clRectBox.left = m_clRectCircle[i - nMaxCount].left;
			clRectBox.top = m_clRectCircle[i - nMaxCount].top;
			clRectBox.right = m_clRectCircle[i - nMaxCount].right;
			clRectBox.bottom = m_clRectCircle[i - nMaxCount].bottom;
			//
			clRectBox.centerX = (clRectBox.left + clRectBox.right) / 2;
			clRectBox.centerY = (clRectBox.top + clRectBox.bottom) / 2;
			 
            nSquareSelectSizeX = (clRectBox.right - clRectBox.left)/2 - 20;
            nSquareSelectSizeY = (clRectBox.bottom - clRectBox.top)/2 - 20;

		}

		if ((clPtPos.x > (clRectBox.left + iGap)) &&
			(clPtPos.x < (clRectBox.right - iGap)) &&
			(clPtPos.y >(clRectBox.top + iGap)) &&
			(clPtPos.y < (clRectBox.bottom - iGap)))
		{
			return CENTER;
		}
		else if ((clPtPos.x >(clRectBox.left - iGap)) &&
			(clPtPos.x < (clRectBox.left + iGap)) &&
			(clPtPos.y >(clRectBox.top)) &&
			(clPtPos.y < (clRectBox.bottom)))
		{
			return LEFT;
		}
		else if ((clPtPos.x >(clRectBox.right - iGap)) &&
			(clPtPos.x < (clRectBox.right + iGap)) &&
			(clPtPos.y >(clRectBox.top)) &&
			(clPtPos.y < (clRectBox.bottom)))
		{
			return RIGHT;
		}
		else if ((clPtPos.x > clRectBox.left) &&
			(clPtPos.x < clRectBox.right) &&
			(clPtPos.y >(clRectBox.top - iGap)) &&
			(clPtPos.y < (clRectBox.top + iGap)))
		{
			return TOP;
		}
		else if ((clPtPos.x > clRectBox.left) &&
			(clPtPos.x < clRectBox.right) &&
			(clPtPos.y >(clRectBox.bottom - iGap)) &&//SQUARE_RESET_SIZE_X
			(clPtPos.y < (clRectBox.bottom + iGap)))
		{
			return BOTTOM;
		}
		else
		{
			nCursor = STANDARD;
		}
	}

	return nCursor;
}

//-----------------------------------------------------------------------------
//
//	OnLButtonUp
//
//-----------------------------------------------------------------------------
void CVisionStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint clPoint;
	CPoint clPtDragStart;
	CPoint clPtDragSize;
	SCROLLINFO stScrollVert;
	SCROLLINFO stScrollHoz;

	SCROLLINFO stScrVert;
	SCROLLINFO stScrHorz;
	CPoint clPt;
	if (g_pCarAABonderDlg->m_bCamState[m_nUnit] == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{

		double dTemp = 0.0;
		ReleaseCapture();
		m_bDrawLine = false;

		// 화면 이동일 경우
		if ((m_bClickFlag == true) && (m_nDragFlag == DISP_MOVE))
		{
			this->GetScrollInfo(SB_VERT, &stScrVert);
			this->GetScrollInfo(SB_HORZ, &stScrHorz);

			clPt.x = point.x - m_clClickPoint.x;
			clPt.y = point.y - m_clClickPoint.y;

			m_clScrollPos.x -= clPt.x;
			m_clScrollPos.y -= clPt.y;

			if (m_clScrollPos.x < 0)		m_clScrollPos.x = 0;
			if (m_clScrollPos.y < 0)		m_clScrollPos.y = 0;

			stScrHorz.nPos = m_clScrollPos.x;
			stScrVert.nPos = m_clScrollPos.y;

			this->SetScrollInfo(SB_VERT, &stScrVert, TRUE);
			this->SetScrollInfo(SB_HORZ, &stScrHorz, TRUE);

			//this->ScrollImage();
		}
		else if ((m_bClickFlag == true) && (m_nDragFlag == MOUSE_DRAG))
		{
			switch (m_nType)
			{
			case SQUARE_RESIZE:
				//-->Left > Right || Top > Bottom 일 경우 스왑
				if (m_clDRect.left > m_clDRect.right)
				{
					dTemp = m_clDRect.left;
					m_clDRect.left = m_clDRect.right;
					m_clDRect.right = dTemp;
				}

				if (m_clDRect.top > m_clDRect.bottom)
				{
					dTemp = m_clDRect.top;
					m_clDRect.top = m_clDRect.bottom;
					m_clDRect.bottom = dTemp;
				}

				break;
			case SQUARE_CREATE:
				if (m_clDRect.left > m_clDRect.right)
				{
					dTemp = m_clDRect.left;
					m_clDRect.left = m_clDRect.right;
					m_clDRect.right = dTemp;
				}

				if (m_clDRect.top > m_clDRect.bottom)
				{
					dTemp = m_clDRect.top;
					m_clDRect.top = m_clDRect.bottom;
					m_clDRect.bottom = dTemp;
				}

				if ((m_clDRect.right - m_clDRect.left) < 20 || (m_clDRect.bottom - m_clDRect.top) < 20)
				{
					m_clDRect.left = m_clDRect.right = 0.0;
					m_clDRect.top = m_clDRect.bottom = 0.0;
					m_clDRect.centerX = m_clDRect.centerY = 0.0;
					m_clDRect.cnt--;
				}

				clPtDragStart.x = (m_clDRect.left < m_clDRect.right) ? (LONG)m_clDRect.left : (LONG)m_clDRect.right;
				clPtDragStart.y = (m_clDRect.top < m_clDRect.bottom) ? (LONG)m_clDRect.top : (LONG)m_clDRect.bottom;

				clPtDragSize.x = (LONG)(abs(m_clDRect.left - m_clDRect.right));
				clPtDragSize.y = (LONG)(abs(m_clDRect.top - m_clDRect.bottom));

				this->DrawRect(clPtDragStart, clPtDragSize);

				break;
			}

			m_nType = SQUARE_RESET;
		}

		m_bClickFlag = false;
	}
	else
	{
		double dDrawLeft;
		double dDrawRight;
		double dDrawTop;
		double dDrawBottom;

		dDrawLeft = dDrawRight = dDrawTop = dDrawBottom = 0.0;

		if (m_bLock == true)
			return;

		ReleaseCapture();
		m_bDrawLine = false;

		if (m_bClick == true)
		{
			switch (m_nDragType)
			{
				// 마우스 드래그
			case MOUSE_DRAG:
				switch (m_nBoxDrawType)
				{
				case SQUARE_RESIZE:
					if (m_clDrawBox.left > m_clDrawBox.right)
					{
						dDrawLeft = m_clDrawBox.right;
						dDrawRight = m_clDrawBox.left;
						m_clDrawBox.left = dDrawLeft;
						m_clDrawBox.right = dDrawRight;
					}

					if (m_clDrawBox.top > m_clDrawBox.bottom)
					{
						dDrawTop = m_clDrawBox.bottom;
						dDrawBottom = m_clDrawBox.top;
						m_clDrawBox.top = dDrawTop;
						m_clDrawBox.bottom = dDrawBottom;
					}
					break;
				case SQUARE_CREATE:
					if (m_clDrawBox.left > m_clDrawBox.right)
					{
						dDrawLeft = m_clDrawBox.right;
						dDrawRight = m_clDrawBox.left;
						m_clDrawBox.left = dDrawLeft;
						m_clDrawBox.right = dDrawRight;
					}

					if (m_clDrawBox.top > m_clDrawBox.bottom)
					{
						dDrawTop = m_clDrawBox.bottom;
						dDrawBottom = m_clDrawBox.top;
						m_clDrawBox.top = dDrawTop;
						m_clDrawBox.bottom = dDrawBottom;
					}

					if (m_clDrawBox.right - m_clDrawBox.left < 20 || m_clDrawBox.bottom - m_clDrawBox.top < 20)
					{
						m_clDrawBox.left = m_clDrawBox.right = m_clDrawBox.top = m_clDrawBox.bottom = 0;
						m_clDrawBox.centerX = m_clDrawBox.centerY = 0;
						m_clDrawBox.cnt--;
					}

					clPtDragStart.x = m_clDrawBox.left < m_clDrawBox.right ? (LONG)m_clDrawBox.left : (LONG)m_clDrawBox.right;
					clPtDragStart.y = m_clDrawBox.top < m_clDrawBox.bottom ? (LONG)m_clDrawBox.top : (LONG)m_clDrawBox.bottom;
					clPtDragSize.x = (LONG)(abs(m_clDrawBox.left - m_clDrawBox.right));
					clPtDragSize.y = (LONG)(abs(m_clDrawBox.top - m_clDrawBox.bottom));

					this->DrawRect(clPtDragStart, clPtDragSize);

					break;
				}

				m_nBoxDrawType = SQUARE_RESET;
				break;
				// 화면 이동
			case DISP_MOVE:
				this->GetScrollInfo(SB_VERT, &stScrollVert);
				this->GetScrollInfo(SB_HORZ, &stScrollHoz);

				clPoint.x = point.x - m_clClickPoint.x;
				clPoint.y = point.y - m_clClickPoint.y;

				m_clScrollPos.x -= clPoint.x;
				m_clScrollPos.y -= clPoint.y;

				if (m_clScrollPos.x < 0) m_clScrollPos.x = 0;
				if (m_clScrollPos.y < 0) m_clScrollPos.y = 0;

				stScrollHoz.nPos = m_clScrollPos.x;
				stScrollVert.nPos = m_clScrollPos.y;

				this->SetScrollInfo(SB_VERT, &stScrollVert, TRUE);
				this->SetScrollInfo(SB_HORZ, &stScrollHoz, TRUE);

				this->ImageScroll();
				break;
			}
		}

		m_bClick = false;

	}
	CStatic::OnLButtonUp(nFlags, point);
}

//-----------------------------------------------------------------------------
//
//	OnMouseMove
//
//-----------------------------------------------------------------------------
void CVisionStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bLock == true)		return;

	CPoint clPoint;
	CPoint clPtDragStart;
	CPoint clPtDragSize;
	CPoint clPtCamDragStart;
	CPoint clPtCamDragSize;
	double dDrawX, dDrawY;
	double dZoomX, dZoomY;
	CPoint clPtDrawOfs;
	CPoint clPtDraw;
	int nMoveX, nMoveY;
	int nMaxCount;

	dDrawX = dDrawY = 0.0;
	dZoomX = dZoomY = 0.0;
	nMoveX = nMoveY = 0;

	

	m_clClickPoint = point;
	if (g_pCarAABonderDlg->m_bCamState[m_nUnit] == VIDEO_CAM)	//VIDEO_CAM , VIDEO_CCD
	{
		CPoint clPtDrawOffSet;
		clPtDrawOffSet.x = clPtDrawOffSet.y = 0;

		if ((m_bClickFlag == true) && (m_nDragFlag == MOUSE_DRAG))
		{
			// 박스 리사이즈
			if (m_nType == SQUARE_RESIZE && m_bClickFlag == true)
			{
				switch (m_nCursorType)
				{
				case LEFT:			m_clDRect.left = m_clClickPoint.x;											break;
				case LEFTTOP:		m_clDRect.left = m_clClickPoint.x;	m_clDRect.top = m_clClickPoint.y;		break;
				case LEFTBOTTOM:	m_clDRect.left = m_clClickPoint.x;	m_clDRect.bottom = m_clClickPoint.y;	break;
				case RIGHT:			m_clDRect.right = m_clClickPoint.x;											break;
				case RIGHTTOP:		m_clDRect.right = m_clClickPoint.x;	m_clDRect.top = m_clClickPoint.y;		break;
				case RIGHTBOTTOM:	m_clDRect.right = m_clClickPoint.x;	m_clDRect.bottom = m_clClickPoint.y;	break;
				case TOP:			m_clDRect.top = m_clClickPoint.y;											break;
				case BOTTOM:		m_clDRect.bottom = m_clClickPoint.y;										break; 
				}

				// 박스 사이즈가 너무 작은 경우
				if ((m_clDRect.right - m_clDRect.left) < 20 || (m_clDRect.bottom - m_clDRect.top) < 20)
				{
					m_bClickFlag = false;

					// 20 * 20 이하기 됐을 경우 클릭하기 편하도록 10 PIXEL 증가
					switch (m_nCursorType)
					{
					case LEFT:
						m_clDRect.left = m_clClickPoint.x - RESET_SIZE_X;
						break;
					case LEFTTOP:
						m_clDRect.left = m_clClickPoint.x - RESET_SIZE_X;
						m_clDRect.top = m_clClickPoint.y - RESET_SIZE_Y;
						break;
					case LEFTBOTTOM:
						m_clDRect.left = m_clClickPoint.x - RESET_SIZE_X;
						m_clDRect.bottom = m_clClickPoint.y + RESET_SIZE_Y;
						break;
					case RIGHT:
						m_clDRect.right = m_clClickPoint.x + RESET_SIZE_X;
						break;
					case RIGHTTOP:
						m_clDRect.right = m_clClickPoint.x + RESET_SIZE_X;
						m_clDRect.top = m_clClickPoint.y - RESET_SIZE_Y;
						break;
					case RIGHTBOTTOM:
						m_clDRect.right = m_clClickPoint.x + RESET_SIZE_X;
						m_clDRect.bottom = m_clClickPoint.y + RESET_SIZE_Y;
						break;
					case TOP:
						m_clDRect.top = m_clClickPoint.y - RESET_SIZE_X;
						break;
					case BOTTOM:
						m_clDRect.bottom = m_clClickPoint.y + RESET_SIZE_Y;
						break;
					}

					m_nType = SQUARE_RESET;
				}

				m_clDRect.centerX = m_clDRect.left + ((m_clDRect.right - m_clDRect.left) / 2);
				m_clDRect.centerY = m_clDRect.top + ((m_clDRect.bottom - m_clDRect.top) / 2);

				this->ChangeCursor(m_nCursorType);
			}
			// 박스 생성
			else if (m_nType == SQUARE_CREATE)
			{
				m_clDRect.right = m_clClickPoint.x;
				m_clDRect.bottom = m_clClickPoint.y;
				m_clDRect.centerX = m_clDRect.left + ((m_clDRect.right - m_clDRect.left) / 2);
				m_clDRect.centerY = m_clDRect.top + ((m_clDRect.bottom - m_clDRect.top) / 2);
			}
			// 박스 이동
			else if (m_nType == SQUARE_MOVE)
			{
				m_clDRect.left = m_clDRect.left - (m_clDRect.centerX - m_clClickPoint.x);
				m_clDRect.right = m_clDRect.right - (m_clDRect.centerX - m_clClickPoint.x);
				m_clDRect.top = m_clDRect.top - (m_clDRect.centerY - m_clClickPoint.y);
				m_clDRect.bottom = m_clDRect.bottom - (m_clDRect.centerY - m_clClickPoint.y);

				m_clDRect.centerX = m_clClickPoint.x;
				m_clDRect.centerY = m_clClickPoint.y;

				this->ChangeCursor(m_nCursorType);
			}

			clPtCamDragStart.x = (m_clDRect.left < m_clDRect.right) ? (LONG)m_clDRect.left : (LONG)m_clDRect.right;
			clPtCamDragStart.y = (m_clDRect.top < m_clDRect.bottom) ? (LONG)m_clDRect.top : (LONG)m_clDRect.bottom;

			clPtCamDragSize.x = (LONG)(abs(m_clDRect.left - m_clDRect.right));
			clPtCamDragSize.y = (LONG)(abs(m_clDRect.top - m_clDRect.bottom));

			this->DrawRect(clPtCamDragStart, clPtCamDragSize);
		}
	}
	else      //CCD 창
	{
		if (m_bDrag == false)
		{
			

			if (m_bClick == true)
			{
				if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
				{
					if (m_nSelectIndexFOV != -1)
					{
						this->SetDrawMoveFov(m_nSelectIndexFOV, point);
					}
					this->DrawRectFov(m_nSelectIndexFOV);
					return;
				}
				else
				{
					nMaxCount = MAX_LAST_INSP_COUNT;
					if (m_nSelectIndexCCD != -1)
					{
						if (m_nSelectIndexCCD >= 0 && m_nSelectIndexCCD < nMaxCount)
						{
							this->SetDrawMoveSfr(m_nSelectIndexCCD, point);
						}
						else
						{
							this->SetDrawMoveCircle(m_nSelectIndexCCD - nMaxCount, point);
						}

						this->DrawRectSfr(m_nSelectIndexCCD);

						return;
					}
				}
			}
			/*if (m_bClick == true && m_nSelectIndexCCD != -1)
			{
				if (m_nSelectIndexCCD >= 0 && m_nSelectIndexCCD < nMaxCount)
				{
					this->SetDrawMoveSfr(m_nSelectIndexCCD, point);
				}
				else
				{
					this->SetDrawMoveCircle(m_nSelectIndexCCD - nMaxCount, point);
				}

				this->DrawRectSfr(m_nSelectIndexCCD);

				return;
			}*/
		}
		else
		{
			if (m_bClick == true && m_nDragType == MOUSE_DRAG) 
			{
				switch (m_nBoxDrawType)
				{
				case SQUARE_RESIZE:
					switch (m_nCursorType)
					{
					case LEFT:
						m_clDrawBox.left = m_clClickPoint.x;
						break;
					case LEFTTOP:
						m_clDrawBox.left = m_clClickPoint.x;
						m_clDrawBox.top = m_clClickPoint.y;
						break;
					case LEFTBOTTOM:
						m_clDrawBox.left = m_clClickPoint.x;
						m_clDrawBox.bottom = m_clClickPoint.y;
						break;
					case RIGHT:
						m_clDrawBox.right = m_clClickPoint.x;
						break;
					case RIGHTTOP:
						m_clDrawBox.right = m_clClickPoint.x;
						m_clDrawBox.top = m_clClickPoint.y;
						break;
					case RIGHTBOTTOM:
						m_clDrawBox.right = m_clClickPoint.x;
						m_clDrawBox.bottom = m_clClickPoint.y;
						break;
					case TOP:
						m_clDrawBox.top = m_clClickPoint.y;
						break;
					case BOTTOM:
						m_clDrawBox.bottom = m_clClickPoint.y;
						break;
					}

					// 박스 사이즈가 너무 작은 경우
					if (m_clDrawBox.right - m_clDrawBox.left < 20 || m_clDrawBox.bottom - m_clDrawBox.top < 20)
					{
						m_bClick = false;

						// 20 Pixel 이하가 됐을 경우 클릭하기 편하도록 10Pixel씩 증가
						switch (m_nCursorType)
						{
						case LEFT:
							m_clDrawBox.left = m_clDrawBox.left - SQUARE_RESET_SIZE_X;
							break;
						case LEFTTOP:
							m_clDrawBox.left = m_clDrawBox.left - SQUARE_RESET_SIZE_X;
							m_clDrawBox.top = m_clDrawBox.top - SQUARE_RESET_SIZE_Y;
							break;
						case LEFTBOTTOM:
							m_clDrawBox.left = m_clDrawBox.left - SQUARE_RESET_SIZE_X;
							m_clDrawBox.bottom = m_clDrawBox.bottom + SQUARE_RESET_SIZE_Y;
							break;
						case RIGHT:
							m_clDrawBox.right = m_clDrawBox.right + SQUARE_RESET_SIZE_X;
							break;
						case RIGHTTOP:
							m_clDrawBox.right = m_clDrawBox.right + SQUARE_RESET_SIZE_X;
							m_clDrawBox.top = m_clDrawBox.top - SQUARE_RESET_SIZE_Y;
							break;
						case RIGHTBOTTOM:
							m_clDrawBox.right = m_clDrawBox.right + SQUARE_RESET_SIZE_X;
							m_clDrawBox.bottom = m_clDrawBox.bottom + SQUARE_RESET_SIZE_Y;
							break;
						case TOP:
							m_clDrawBox.top = m_clDrawBox.top - SQUARE_RESET_SIZE_Y;
							break;
						case BOTTOM:
							m_clDrawBox.bottom = m_clDrawBox.bottom + SQUARE_RESET_SIZE_Y;
							break;
						}

						m_nBoxDrawType = SQUARE_RESET;
					}

					m_clDrawBox.centerX = m_clDrawBox.left + ((m_clDrawBox.right - m_clDrawBox.left) / 2);
					m_clDrawBox.centerY = m_clDrawBox.top + ((m_clDrawBox.bottom - m_clDrawBox.top) / 2);

					this->ChangeCursor(m_nCursorType);

					break;
				case SQUARE_CREATE:
					m_clDrawBox.right = m_clClickPoint.x;
					m_clDrawBox.bottom = m_clClickPoint.y;
					m_clDrawBox.centerX = m_clDrawBox.left + ((m_clDrawBox.right - m_clDrawBox.left) / 2);
					m_clDrawBox.centerY = m_clDrawBox.top + ((m_clDrawBox.bottom - m_clDrawBox.top) / 2);

					break;
				case SQUARE_MOVE:
					dDrawX = m_clDrawBox.centerX - m_clClickPoint.x;
					dDrawY = m_clDrawBox.centerY - m_clClickPoint.y;

					m_clDrawBox.left = m_clDrawBox.left - dDrawX;
					m_clDrawBox.right = m_clDrawBox.right - dDrawX;
					m_clDrawBox.top = m_clDrawBox.top - dDrawY;
					m_clDrawBox.bottom = m_clDrawBox.bottom - dDrawY;

					m_clDrawBox.centerX = m_clClickPoint.x;
					m_clDrawBox.centerY = m_clClickPoint.y;

					this->ChangeCursor(m_nCursorType);
					break;
				}

				clPtDragStart.x = m_clDrawBox.left < m_clDrawBox.right ? (LONG)m_clDrawBox.left : (LONG)m_clDrawBox.right;
				clPtDragStart.y = m_clDrawBox.top < m_clDrawBox.bottom ? (LONG)m_clDrawBox.top : (LONG)m_clDrawBox.bottom;
				clPtDragSize.x = (LONG)(abs(m_clDrawBox.left - m_clDrawBox.right));
				clPtDragSize.y = (LONG)(abs(m_clDrawBox.top - m_clDrawBox.bottom));

				this->DrawRect(clPtDragStart, clPtDragSize);
			}
			else if (m_nDragType == DIST_CHECK)
			{
				if (m_bDrawLine == false)
				{
					m_nDragDistType = this->ChangeCursorMeasureMode(point);
				}

				if (m_bDrawLine == true)
				{
					if (m_dZoomFac >= 1)
						dZoomX = dZoomY = (double)(1.0 * m_dZoomFac);
					else
						dZoomX = dZoomY = (double)(1.0 / m_dZoomFac);


					clPtDrawOfs.x = (int)(m_clScrollPos.x / m_dZoomFac);
					clPtDrawOfs.y = (int)(m_clScrollPos.y / m_dZoomFac);

					if (m_dZoomFac >= 1)
					{
						nMoveX = (int)((point.x / dZoomX + 0.5) + clPtDrawOfs.x) - (int)((m_clClickDist.x / dZoomX + 0.5) + clPtDrawOfs.x);
						nMoveY = (int)((point.y / dZoomY + 0.5) + clPtDrawOfs.y) - (int)((m_clClickDist.y / dZoomY + 0.5) + clPtDrawOfs.y);
					}
					else
					{
						nMoveX = (int)(point.x * dZoomX + 0.5) - (int)(m_clClickDist.x * dZoomX + 0.5);
						nMoveY = (int)(point.y * dZoomY + 0.5) - (int)(m_clClickDist.y * dZoomY + 0.5);
					}

					m_clClickDist = point;

					switch (m_nDragDistType)
					{
					case 1:		m_clMeasure[0].x += nMoveX;		break;
					case 2:		m_clMeasure[0].y += nMoveY;		break;
					case 3:		m_clMeasure[1].x += nMoveX;		break;
					case 4:		m_clMeasure[1].y += nMoveY;		break;
					}

					this->DrawDistance();
					SetCapture();
				}
				else
				{
					m_nDragDistType = this->ChangeCursorMeasureMode(point);
				}
			}
			else if (m_bClick == true && m_nDragType == MEASURE)
			{
				clPoint = point;
				this->DrawMeasure(clPoint);
			}
			else if (m_bClick == false && m_nDragType == MOUSE_DRAG)
			{
				m_nCursorType = this->GetLineType();
				this->ChangeCursor(m_nCursorType);
			}
		}
	}

	CStatic::OnMouseMove(nFlags, point);
}

//-----------------------------------------------------------------------------
//
//	OnRButtonUp
//
//-----------------------------------------------------------------------------
void CVisionStatic::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint clPoint;

	if (m_bLock == true)
		return;

	if ((m_nMeasureStep < MEASURE_COMPLETE) && (m_nDragType == MEASURE) && (m_bRButtonUp == true))
	{
		m_bRButtonUp = false;
		m_nMeasureStep++;

		clPoint.x = 10;
		clPoint.y = 10;

		this->DrawMeasure(clPoint);
	}

	if ((m_nMeasureStep >= MEASURE_COMPLETE) && (m_nDragType == MEASURE))
	{
		m_bDrag = false;
	}

	CStatic::OnRButtonUp(nFlags, point);
}

//-----------------------------------------------------------------------------
//
//	OnHScroll
//
//-----------------------------------------------------------------------------
void CVisionStatic::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SCROLLINFO sif;
	this->GetScrollInfo(SB_HORZ, &sif);

	if (nSBCode == SB_ENDSCROLL)
		return;

	switch (nSBCode)
	{
	case SB_LINELEFT:
	case SB_PAGELEFT:
		sif.nPos -= sif.nPage;
		if (sif.nPos < 0)
			sif.nPos = 0;

		m_clScrollPos.x = sif.nPos;
		this->ImageScroll();
		break;
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		sif.nPos += sif.nPage;
		if (sif.nPos >= (int)(sif.nMax - sif.nPage))
			sif.nPos = sif.nMax - sif.nPage;

		m_clScrollPos.x = sif.nPos;
		this->ImageScroll();
		break;
	case SB_THUMBTRACK:
		sif.nPos = nPos;

		m_clScrollPos.x = nPos;
		this->ImageScroll();
		break;
	case SB_ENDSCROLL:
		break;
	}

	this->SetScrollInfo(SB_HORZ, &sif, TRUE);
	Invalidate(FALSE);

	CStatic::OnHScroll(nSBCode, nPos, pScrollBar);
}

//-----------------------------------------------------------------------------
//
//	OnVScroll
//
//-----------------------------------------------------------------------------
void CVisionStatic::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SCROLLINFO sif;
	this->GetScrollInfo(SB_VERT, &sif);

	switch (nSBCode)
	{
	case SB_LINELEFT:
	case SB_PAGELEFT:
		sif.nPos -= sif.nMax / 10;
		if (sif.nPos < 0)
			sif.nPos = 0;

		m_clScrollPos.y = sif.nPos;
		this->ImageScroll();
		break;
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		sif.nPos += sif.nPage;
		if (sif.nPos >= (int)(sif.nMax - sif.nPage))
			sif.nPos = sif.nMax - sif.nPage;

		m_clScrollPos.y = sif.nPos;
		this->ImageScroll();
		break;
	case SB_THUMBTRACK:
		sif.nPos = nPos;

		m_clScrollPos.y = nPos;
		this->ImageScroll();
		break;
	case SB_ENDSCROLL:
		break;
	}

	this->SetScrollInfo(SB_VERT, &sif, TRUE);
	Invalidate(FALSE);

	CStatic::OnVScroll(nSBCode, nPos, pScrollBar);
}
//-----------------------------------------------------------------------------
//
//	모델 데이터의 Snr 영역을 내부에 저장
//
//-----------------------------------------------------------------------------
void CVisionStatic::SetSnrRoi()
{
    int i;
    for (i = 0; i < MAX_SNR_COUNT; i++)
    {
		m_clRectDrawSnr[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_clRectSnr[i];
    }
}
//-----------------------------------------------------------------------------
//
//	모델 데이터의 fov 영역을 내부에 저장
//
//-----------------------------------------------------------------------------
void CVisionStatic::SetFovRoi()
{
    int i;
    for (i = 0; i < MAX_FOV_COUNT; i++)
    {
        m_clRectFov[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_clRectFov[i];
    }
}
//-----------------------------------------------------------------------------
//
//	모델 데이터의 ROI 영역을 내부에 저장
//
//-----------------------------------------------------------------------------
void CVisionStatic::SetSfrRoi()
{
	int i = 0;
	

	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		m_clPtSfrOffset[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i];
	}

	for (i = 0; i < 4; i++)
	{
		m_clRectCircle[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle[i];
	}


	for (i = 0; i < MAX_FOV_COUNT; i++)
	{
		m_clPtFovOffset[i] = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[i];
	}
}

//-----------------------------------------------------------------------------
//
//	FOV ROI 영역 초기화
//
//-----------------------------------------------------------------------------
void CVisionStatic::InitFovRoi()
{
	int i;
	double dOffsetX, dOffsetY;
	int nCount = 0;
	nCount = MAX_FOV_COUNT;
	for (i = 0; i < nCount; i++)
	{
		m_clPtFovOffset[i].x = m_clPtFovOffset[i].y = 0;
#if (____MACHINE_NAME == MODEL_FRONT_100)
		if (i < 4)
		{
			m_nFovSizeX[i] = 270;
			m_nFovSizeY[i] = 230;
		}
		else if (i < 8)
		{
			m_nFovSizeX[i] = 170;
			m_nFovSizeY[i] = 175;
		}
		else
		{
			m_nFovSizeX[i] = 80;
			m_nFovSizeY[i] = 130;
		}
		switch (i)
		{
		case 0:		dOffsetX = 2.98;	dOffsetY = 9.1;		break;	//LT
		case 1:		dOffsetX = 1.51;	dOffsetY = 9.1;		break;	//R T
		case 2:		dOffsetX = 2.98;	dOffsetY = 1.125;	break;	//B L
		case 3:		dOffsetX = 1.51;	dOffsetY = 1.125;	break;	//B R
																	
		case 4:		dOffsetX = 6.7;		dOffsetY = 9.5;		break;
		case 5:		dOffsetX = 1.17;	dOffsetY = 9.5;		break;
		case 6:		dOffsetX = 6.7;		dOffsetY = 1.12;	break;
		case 7:		dOffsetX = 1.17;	dOffsetY = 1.12;	break;//
		/*case 4:		dOffsetX = 7.15;	dOffsetY = 9.5;		break;
		case 5:		dOffsetX = 1.17;	dOffsetY = 9.5;		break;
		case 6:		dOffsetX = 7.15;	dOffsetY = 1.12;	break;
		case 7:		dOffsetX = 1.17;	dOffsetY = 1.12;	break;*/
			//
		case 8:		dOffsetX = 40.5;	dOffsetY = 15.5;		break;
		case 9:		dOffsetX = 1.024;	dOffsetY = 15.5;		break;
		case 10:	dOffsetX = 40.5;	dOffsetY = 1.07;	break;
		case 11:	dOffsetX = 1.024;	dOffsetY = 1.07;	break;
		}

#else
#ifdef KUMI_TEST_MODE


		if (i < 4)
		{
			m_nFovSizeX[i] = 130;// 115;
			m_nFovSizeY[i] = 140;// 125;
		}
		else
		{
			m_nFovSizeX[i] = 160;// 145;
			m_nFovSizeY[i] = 190;// 175;
		}

		switch (i)
		{
		case 0:		dOffsetX = 3.88;	dOffsetY = 4.25;		break;	//LT
		case 1:		dOffsetX = 1.35;	dOffsetY = 4.25;		break;	//R T
		case 2:		dOffsetX = 3.88;	dOffsetY = 1.31;		break;	//B L
		case 3:		dOffsetX = 1.35;	dOffsetY = 1.31;		break;	//B R
		//
		case 4:		dOffsetX = 7.0;		dOffsetY = 6.3;			break;
		case 5:		dOffsetX = 1.175;	dOffsetY = 6.3;			break;
		case 6:		dOffsetX = 7.0;		dOffsetY = 1.2;			break;
		case 7:		dOffsetX = 1.175;	dOffsetY = 1.2;			break;
		//
		case 8:		dOffsetX = 7.4;		dOffsetY = 1.99;		break;
		case 9:		dOffsetX = 1.158;	dOffsetY = 1.99;		break;
		}
#else
		if (i < 4)
		{
			m_nFovSizeX[i] = 140;
			m_nFovSizeY[i] = 140;
		}
		else if (i < 8)
		{
			m_nFovSizeX[i] = 200;
			m_nFovSizeY[i] = 210;
		}
		else
		{
			m_nFovSizeX[i] = 210;
			m_nFovSizeY[i] = 200;
		}

		switch (i)
		{
		case 0:		dOffsetX = 3.78;	dOffsetY = 4.25;		break;	//LT
		case 1:		dOffsetX = 1.363;	dOffsetY = 4.25;		break;	//R T
		case 2:		dOffsetX = 3.78;	dOffsetY = 1.31;		break;	//B L
		case 3:		dOffsetX = 1.363;	dOffsetY = 1.31;		break;	//B R
																		//
		case 4:		dOffsetX = 8.0;		dOffsetY = 7.7;			break;
		case 5:		dOffsetX = 1.14;	dOffsetY = 7.7;			break;
		case 6:		dOffsetX = 8.0;		dOffsetY = 1.135;			break;
		case 7:		dOffsetX = 1.14;	dOffsetY = 1.135;			break;
		/*case 4:		dOffsetX = 8.3;		dOffsetY = 8.44;			break;
		case 5:		dOffsetX = 1.141;	dOffsetY = 8.44;			break;
		case 6:		dOffsetX = 8.3;		dOffsetY = 1.135;			break;
		case 7:		dOffsetX = 1.141;	dOffsetY = 1.135;			break;*/
			//
		case 8:		dOffsetX = 8.0;		dOffsetY = 1.99;		break;
		case 9:		dOffsetX = 1.147;	dOffsetY = 1.99;		break;
		}
#endif
#endif

		m_clPtFovOffset[i].x = (LONG)((double)g_clModelData[m_nUnit].m_nWidth / dOffsetX) - (m_nFovSizeX[i] / 2);
		m_clPtFovOffset[i].y = (LONG)((double)g_clModelData[m_nUnit].m_nHeight / dOffsetY) - (m_nFovSizeY[i] / 2);

		m_clRectFov[i].left = m_clPtFovOffset[i].x;
		m_clRectFov[i].top = m_clPtFovOffset[i].y;
		m_clRectFov[i].right = m_clRectFov[i].left + m_nFovSizeX[i];
		m_clRectFov[i].bottom = m_clRectFov[i].top + m_nFovSizeY[i];
	}

	



	this->DrawRectFov(999);
}


//-----------------------------------------------------------------------------
//
//	SFR ROI 영역 초기화
//
//-----------------------------------------------------------------------------
void CVisionStatic::InitSfrRoi()
{
	int i;
	double dOffsetX, dOffsetY;
	int nCount;
    nCount = MAX_LAST_INSP_COUNT;
	m_nCenterSfrSizeX = 150;
	m_nCenterSfrSizeY = 150;
	for (i = 0; i < nCount; i++)
	{
#if (____MACHINE_NAME == MODEL_FRONT_100)
		if (i == 0)
		{
			m_nSfrSizeX[i] = 390;
			m_nSfrSizeY[i] = 360;
		}
		else if (i < 5)
		{
			m_nSfrSizeX[i] = 160;
			m_nSfrSizeY[i] = 160;
		}
		else
		{
			m_nSfrSizeX[i] = 160;
			m_nSfrSizeY[i] = 160;
		}
#else
		if (i == 0)
		{
			m_nSfrSizeX[i] = 270;
			m_nSfrSizeY[i] = 270;
		}
		else if (i < 5)
		{
			m_nSfrSizeX[i] = 190;
			m_nSfrSizeY[i] = 190;
		}
		else
		{
			m_nSfrSizeX[i] = 150;
			m_nSfrSizeY[i] = 170;
		}
#endif
	}


	
	for (i = 0; i < nCount; i++)
	{
		m_clPtSfrOffset[i].x = m_clPtSfrOffset[i].y = 0;
#if (____MACHINE_NAME == MODEL_FRONT_100)
		switch (i)
		{
		case 0:		dOffsetX = 2.0;		dOffsetY = 2.0;		break;
		//
		case 1:		dOffsetX = 2.8;		dOffsetY = 1.17;		break;	//LT
		case 2:		dOffsetX = 1.57;	dOffsetY = 1.17;		break;	//R T
		case 3:		dOffsetX = 2.8;		dOffsetY = 7.3;	break;	//B L
		case 4:		dOffsetX = 1.57;	dOffsetY = 7.3;	break;	//B R
		//
		case 5:		dOffsetX = 7.0;		dOffsetY = 1.12;		break;
		case 6:		dOffsetX = 1.175;	dOffsetY = 1.12;		break;
		case 7:		dOffsetX = 7.0;		dOffsetY = 8.8;	break;
		case 8:		dOffsetX = 1.175;	dOffsetY = 8.8;	break;
		}
#else
		switch (i)
		{
		case 0:		dOffsetX = 2.0;		dOffsetY = 2.0;		break;
			//
		case 1:		dOffsetX = 2.6;		dOffsetY = 4.5;		break;
		case 2:		dOffsetX = 1.63;	dOffsetY = 4.5;		break;
		case 3:		dOffsetX = 2.6;		dOffsetY = 1.27;	break;
		case 4:		dOffsetX = 1.63;	dOffsetY = 1.27;	break;
			//
		case 5:		dOffsetX = 7.0;		dOffsetY = 6.5;		break;
		case 6:		dOffsetX = 1.17;	dOffsetY = 6.5;		break;
		case 7:		dOffsetX = 7.0;		dOffsetY = 1.19;	break;
		case 8:		dOffsetX = 1.17;	dOffsetY = 1.19;	break;
		}
#endif

		m_clPtSfrOffset[i].x = (LONG)((double)g_clModelData[m_nUnit].m_nWidth / dOffsetX) - (m_nSfrSizeX[i] / 2);
		m_clPtSfrOffset[i].y = (LONG)((double)g_clModelData[m_nUnit].m_nHeight / dOffsetY) - (m_nSfrSizeY[i] / 2);

		m_clRectROI[i].left = m_clPtSfrOffset[i].x;
		m_clRectROI[i].top = m_clPtSfrOffset[i].y;
		m_clRectROI[i].right = m_clRectROI[i].left + m_nSfrSizeX[i];
		m_clRectROI[i].bottom = m_clRectROI[i].top + m_nSfrSizeY[i];


	}
	
    //
	
    //
    //
#if (____MACHINE_NAME == MODEL_FRONT_100)
	int dCircleSizeX = 170;
	int dCircleSizeY = 140;
	m_clRectCircle[0].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.37);
	m_clRectCircle[0].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.19);
	m_clRectCircle[0].right = (LONG)((double)m_clRectCircle[0].left + dCircleSizeX);
	m_clRectCircle[0].bottom = (LONG)((double)m_clRectCircle[0].top + dCircleSizeY);

	m_clRectCircle[1].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.54);
	m_clRectCircle[1].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.19);
	m_clRectCircle[1].right = (LONG)((double)m_clRectCircle[1].left + dCircleSizeX);
	m_clRectCircle[1].bottom = (LONG)((double)m_clRectCircle[1].top + dCircleSizeY);

	m_clRectCircle[2].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.37);
	m_clRectCircle[2].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.68);
	m_clRectCircle[2].right = (LONG)((double)m_clRectCircle[2].left + dCircleSizeX);
	m_clRectCircle[2].bottom = (LONG)((double)m_clRectCircle[2].top + dCircleSizeY);

	m_clRectCircle[3].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.54);
	m_clRectCircle[3].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.68);
	m_clRectCircle[3].right = (LONG)((double)m_clRectCircle[3].left + dCircleSizeX);
	m_clRectCircle[3].bottom = (LONG)((double)m_clRectCircle[3].top + dCircleSizeY);																																											//LT_FOV_PIONT = 0, RT_FOV_PIONT, BL_FOV_PIONT, BR_FOV_PIONT, CIRCLE_FOV_PIONT,
#else
	int dCircleSizeX = 130;
	int dCircleSizeY = 110;
	m_clRectCircle[0].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.41);
	m_clRectCircle[0].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.29);
	m_clRectCircle[0].right = (LONG)((double)m_clRectCircle[0].left + dCircleSizeX);
	m_clRectCircle[0].bottom = (LONG)((double)m_clRectCircle[0].top + dCircleSizeY);

	m_clRectCircle[1].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.52);
	m_clRectCircle[1].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.29);
	m_clRectCircle[1].right = (LONG)((double)m_clRectCircle[1].left + dCircleSizeX);
	m_clRectCircle[1].bottom = (LONG)((double)m_clRectCircle[1].top + dCircleSizeY);

	m_clRectCircle[2].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.41);
	m_clRectCircle[2].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.62);
	m_clRectCircle[2].right = (LONG)((double)m_clRectCircle[2].left + dCircleSizeX);
	m_clRectCircle[2].bottom = (LONG)((double)m_clRectCircle[2].top + dCircleSizeY);

	m_clRectCircle[3].left = (LONG)((double)g_clModelData[m_nUnit].m_nWidth * 0.52);
	m_clRectCircle[3].top = (LONG)((double)(g_clModelData[m_nUnit].m_nHeight) * 0.62);
	m_clRectCircle[3].right = (LONG)((double)m_clRectCircle[3].left + dCircleSizeX);
	m_clRectCircle[3].bottom = (LONG)((double)m_clRectCircle[3].top + dCircleSizeY);
#endif

    this->DrawRectSfr(999);
    
}
//-----------------------------------------------------------------------------
//
//	초기 Align ROI 그린다.
//
//-----------------------------------------------------------------------------
void CVisionStatic::DrawCamAlign(int nIndex)
{

#ifndef ON_LINE_MIL
	return;
#endif
	TCHAR szPos[SIZE_OF_100BYTE];
	int nCount = 0;
	int nGapX = 40;
	int nGapY = 40;
	int i = 0;

	g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);

	g_clVision.DrawMOverlayCross(m_nUnit, VIDEO_CAM, CCD1_CAM_SIZE_X / 2, CCD1_CAM_SIZE_Y / 2, 400, M_COLOR_BLUE, 1, FALSE, PS_SOLID);

	g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);
	
}
//-----------------------------------------------------------------------------
//
//	Snr ROI 영역 그리기
//
//-----------------------------------------------------------------------------
void CVisionStatic::DrawRectSnr(int nIndex)
{
#ifndef ON_LINE_MIL
    return;
#endif
    TCHAR szPos[SIZE_OF_100BYTE];
    int nGapX = 40;
    int nGapY = 40;
    int i;
    int ntxtNum = 0;
    g_clVision.ClearOverlay(m_nUnit);

    // Snr 영역
    for (i = 0; i < MAX_SNR_COUNT; i++)
    {
        g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectDrawSnr[i], M_COLOR_BLUE, 1, FALSE, PS_DOT);
        //g_clVision.DrawMOverlayCross(m_nUnit, (m_clRectSnr[i].right - m_clRectSnr[i].left) / 2 + m_clRectSnr[i].left, (m_clRectSnr[i].bottom - m_clRectSnr[i].top) / 2 + m_clRectSnr[i].top, 15, M_COLOR_GREEN, 1, FALSE, PS_SOLID);
        _stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), (i+1));
        g_clVision.DrawMOverlayText(m_nUnit, m_clRectDrawSnr[i].left + 10, m_clRectDrawSnr[i].top + 10, szPos, M_COLOR_WHITE, _T("Arial"), 15, 15);
    }
    //}
    g_clVision.DrawOverlayAll(m_nUnit);
}
//-----------------------------------------------------------------------------
//
//	Fov ROI 영역 그리기
//
//-----------------------------------------------------------------------------
void CVisionStatic::DrawRectFov(int nIndex)
{
#ifndef ON_LINE_MIL
    return;
#endif
    TCHAR szPos[SIZE_OF_100BYTE];
    int nCount;
    int nGapX = 40;
    int nGapY = 40;
    int i;

    g_clVision.ClearOverlay(m_nUnit);

	for (i = 0; i < MAX_FOV_COUNT; i++)
	{
		m_clRectFov[i].left = m_clPtFovOffset[i].x;
		m_clRectFov[i].top = m_clPtFovOffset[i].y;
		m_clRectFov[i].right = m_clRectFov[i].left + m_nFovSizeX[i];
		m_clRectFov[i].bottom = m_clRectFov[i].top + m_nFovSizeY[i];
	}
    for (i = 0; i < MAX_FOV_COUNT; i++)
    {
		if (nIndex == i) 
		{
			g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectFov[i], M_COLOR_MAGENTA, 1, FALSE, PS_DASH);// PS_DOT);
		}
		else
		{
			g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectFov[i], M_COLOR_CYAN, 1, FALSE, PS_DASH);// PS_DOT);
		}

        g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, (m_clRectFov[i].right - m_clRectFov[i].left) / 2 + m_clRectFov[i].left, (m_clRectFov[i].bottom - m_clRectFov[i].top) / 2 + m_clRectFov[i].top, 15, M_COLOR_GREEN, 1, FALSE, PS_SOLID);
		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), i);
        g_clVision.DrawMOverlayText(m_nUnit, m_clRectFov[i].left + 10, m_clRectFov[i].top + 10, szPos, M_COLOR_WHITE, _T("Arial"), 15, 15);
        
    }
    //}

	_stprintf_s(szPos, SIZE_OF_100BYTE, _T("FovRoi"));
	g_clVision.DrawMOverlayText(m_nUnit, 10, 150, szPos, M_COLOR_WHITE, _T("Arial"), 12, 20);

    g_clVision.DrawOverlayAll(m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	SFR ROI 영역을 오버레이로 그린다.
//
//-----------------------------------------------------------------------------
void CVisionStatic::DrawRectSfr(int nIndex)
{
#ifndef ON_LINE_MIL
	return;
#endif

	TCHAR szPos[SIZE_OF_100BYTE];
	int nCount = 0;
	int nGapX = 40;
	int nGapY = 40;
	int i = 0;

	g_clVision.ClearOverlay(m_nUnit);

    nCount = MAX_LAST_INSP_COUNT; 

	
	// 검사영역
	for (i = 0; i < nCount; i++)
	{
		m_clRectROI[i].left = m_clPtSfrOffset[i].x;
		m_clRectROI[i].top = m_clPtSfrOffset[i].y;
		m_clRectROI[i].right = m_clRectROI[i].left + m_nSfrSizeX[i];
		m_clRectROI[i].bottom = m_clRectROI[i].top + m_nSfrSizeY[i];


		if (nIndex == i) {
			g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectROI[i], M_COLOR_MAGENTA, 1, FALSE);
		}
		else {
			g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectROI[i], M_COLOR_BLUE, 1, FALSE);
		}
		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), i);
		g_clVision.DrawMOverlayText(m_nUnit, m_clRectROI[i].left + 10, m_clRectROI[i].top + 10, szPos, M_COLOR_RED, _T("Arial"), 15, 15);
	}

	// 원형마크 영역 
	for (i = 0; i < 4; i++)
	{
		g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectCircle[i], M_COLOR_DARK_MAGENTA, 1, FALSE, PS_DOT);	//M_COLOR_GREEN
		g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit,
			(m_clRectCircle[i].right - m_clRectCircle[i].left) / 2 + m_clRectCircle[i].left, 
			(m_clRectCircle[i].bottom - m_clRectCircle[i].top) / 2 + m_clRectCircle[i].top, 15, M_COLOR_LIGHT_BLUE, 1, FALSE, PS_SOLID);	//M_COLOR_GREEN
		//
		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), i);
		g_clVision.DrawMOverlayText(m_nUnit, m_clRectCircle[i].left + 10, m_clRectCircle[i].top + 10, szPos, M_COLOR_DARK_GREEN, _T("Arial"), 13, 13);	//M_COLOR_YELLOW
	}
	CPoint _ccdMp;
	_ccdMp.x =  g_clModelData[m_nUnit].m_nWidth / 2;
	_ccdMp.y =  g_clModelData[m_nUnit].m_nHeight / 2;
	g_clVision.DrawOverlayCross(m_nUnit, m_nUnit, _ccdMp, 1000, RGB(255, 0, 0), 1); 

	g_clVision.DrawOverlayAll(m_nUnit);
}

//
//-----------------------------------------------------------------------------
//
//	SNR 영역 사이즈 조절 및 이동
//
//-----------------------------------------------------------------------------
void CVisionStatic::MoveRectSnr(int nMoveType, int nType, int nMoveSize)
{
    int nCount;
    int nIndex;

    if (m_nSelectIndexSNR < 0)
        return;

    nCount = MAX_SNR_COUNT;

    switch (nType)
    {
    case MOVE_UP:
        if (nMoveType == MOVE_POS)
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[nIndex].top -= nMoveSize;
			m_clRectDrawSnr[nIndex].bottom -= nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[0].bottom -= nMoveSize;
			m_clRectDrawSnr[1].bottom -= nMoveSize;
			m_clRectDrawSnr[2].bottom -= nMoveSize;

        }
        break;
    case MOVE_DOWN:
        if (nMoveType == MOVE_POS)
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[nIndex].top += nMoveSize;
			m_clRectDrawSnr[nIndex].bottom += nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[0].bottom += nMoveSize;
			m_clRectDrawSnr[1].bottom += nMoveSize;
			m_clRectDrawSnr[2].bottom += nMoveSize;
        }
        break;
    case MOVE_LEFT:
        if (nMoveType == MOVE_POS)
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[nIndex].left -= nMoveSize;
			m_clRectDrawSnr[nIndex].right -= nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[0].right -= nMoveSize;
			m_clRectDrawSnr[1].right -= nMoveSize;
			m_clRectDrawSnr[2].right -= nMoveSize;
        }
        break;
    case MOVE_RIGHT:
        if (nMoveType == MOVE_POS)
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[nIndex].left += nMoveSize;
			m_clRectDrawSnr[nIndex].right += nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexSNR;
			m_clRectDrawSnr[0].right += nMoveSize;
			m_clRectDrawSnr[1].right += nMoveSize;
			m_clRectDrawSnr[2].right += nMoveSize;
        }
        break;
    }

    this->DrawRectSnr(m_nSelectIndexSNR);
}
//
//-----------------------------------------------------------------------------
//
//	FOV 영역 사이즈 조절 및 이동
//
//-----------------------------------------------------------------------------
void CVisionStatic::MoveRectFov(int nMoveType, int nType, int nMoveSize)
{
    int nCount;
    int nIndex;

    if (m_nSelectIndexFOV < 0)
        return;

    nCount = MAX_FOV_COUNT;

    switch (nType)
    {
    case MOVE_UP:
        if (nMoveType == MOVE_POS)
        {
            /*nIndex = m_nSelectIndexFOV;
            m_clRectFov[nIndex].top -= nMoveSize;
            m_clRectFov[nIndex].bottom -= nMoveSize;*/

			m_clPtFovOffset[m_nSelectIndexFOV].y -= nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexFOV;
           // m_clRectFov[nIndex].bottom -= nMoveSize;


			m_nFovSizeY[nIndex] -= nMoveSize;
            
        }
        break;
    case MOVE_DOWN:
        if (nMoveType == MOVE_POS)
        {
            /*nIndex = m_nSelectIndexFOV;
            m_clRectFov[nIndex].top += nMoveSize;
            m_clRectFov[nIndex].bottom += nMoveSize;*/

			m_clPtFovOffset[m_nSelectIndexFOV].y += nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexFOV;
            //m_clRectFov[nIndex].bottom += nMoveSize;

			m_nFovSizeY[nIndex] += nMoveSize;
        }
        break;
    case MOVE_LEFT:
        if (nMoveType == MOVE_POS)
        {
            /*nIndex = m_nSelectIndexFOV;
            m_clRectFov[nIndex].left -= nMoveSize;
            m_clRectFov[nIndex].right -= nMoveSize;*/

			m_clPtFovOffset[m_nSelectIndexFOV].x -= nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexFOV;
            //m_clRectFov[nIndex].right -= nMoveSize;

			m_nFovSizeX[nIndex] -= nMoveSize;
        }
        break;
    case MOVE_RIGHT:
        if (nMoveType == MOVE_POS)
        {
            /*nIndex = m_nSelectIndexFOV;
            m_clRectFov[nIndex].left += nMoveSize;
            m_clRectFov[nIndex].right += nMoveSize;*/

			m_clPtFovOffset[m_nSelectIndexCCD].x += nMoveSize;
        }
        else
        {
            nIndex = m_nSelectIndexFOV;
            //m_clRectFov[nIndex].right += nMoveSize;

			m_nFovSizeX[nIndex] += nMoveSize;
        }
        break;
    }

    this->DrawRectFov(m_nSelectIndexFOV);
}

//-----------------------------------------------------------------------------
//
//	ROI 영역 사이즈 조절 및 이동
//
//-----------------------------------------------------------------------------
void CVisionStatic::MoveRectSfr(int nMoveType, int nType, int nMoveSize)
{
	int nCount;
	int nIndex = 0;

	if(m_nSelectIndexCCD < 0)
		return;

    nCount = MAX_LAST_INSP_COUNT;

	switch(nType)
	{
	case MOVE_UP:
		if(nMoveType == MOVE_POS)
		{
			// 검사 영역
			if(m_nSelectIndexCCD < nCount)
			{
				m_clPtSfrOffset[m_nSelectIndexCCD].y -= nMoveSize;
			}
			// 원형마크 영역
			else
			{
				nIndex = m_nSelectIndexCCD - nCount;
				m_clRectCircle[nIndex].top -= nMoveSize;
				m_clRectCircle[nIndex].bottom -= nMoveSize;
			}
		}
		else
		{
			// 검사 영역
			if (m_nSelectIndexCCD < nCount)
			{
				if (m_nSelectIndexCCD == 0)
				{
					m_nCenterSfrSizeY -= nMoveSize;
				}
				else
				{
					m_nSfrSizeY[nIndex] -= nMoveSize;
				}
			}
			else
			{
				nIndex = m_nSelectIndexCCD - nCount;
				m_clRectCircle[nIndex].top -= nMoveSize;
			}
		}
		break;
	case MOVE_DOWN:
		if(nMoveType == MOVE_POS)
		{
			// 검사 영역
			if(m_nSelectIndexCCD < nCount)
			{
				m_clPtSfrOffset[m_nSelectIndexCCD].y += nMoveSize;
			}
			// 원형마크 영역
			else
			{
				nIndex = m_nSelectIndexCCD - nCount;
				m_clRectCircle[nIndex].top += nMoveSize;
				m_clRectCircle[nIndex].bottom += nMoveSize;
			}
		}
		else
		{
			// 검사 영역
			if (m_nSelectIndexCCD < nCount)
			{
				if (m_nSelectIndexCCD == 0)
				{
					m_nCenterSfrSizeY += nMoveSize;
				}
				else
				{
					m_nSfrSizeY[nIndex] += nMoveSize;
				}
				
			}
			else
			{
				nIndex = m_nSelectIndexCCD - nCount;
				m_clRectCircle[nIndex].top += nMoveSize;
			}
		}
		break;
	case MOVE_LEFT:
		if(nMoveType == MOVE_POS)
		{
			// 검사 영역
			if(m_nSelectIndexCCD < nCount)
			{
				m_clPtSfrOffset[m_nSelectIndexCCD].x -= nMoveSize;
			}
			// 원형마크 영역
			else
			{
				nIndex = m_nSelectIndexCCD - nCount;
				m_clRectCircle[nIndex].left -= nMoveSize;
				m_clRectCircle[nIndex].right -= nMoveSize;
			}
		}
		else
		{
			// 검사 영역
			if (m_nSelectIndexCCD < nCount)
			{
				if (m_nSelectIndexCCD == 0)
				{
					m_nCenterSfrSizeX -= nMoveSize;
				}
				else
				{
					m_nSfrSizeX[nIndex] -= nMoveSize;
				}
				
			}
			else
			{
				nIndex = m_nSelectIndexCCD - nCount; 
				m_clRectCircle[nIndex].right -= nMoveSize;
			}
		}
		break;
	case MOVE_RIGHT:
		if(nMoveType == MOVE_POS)
		{
			// 검사 영역
			if(m_nSelectIndexCCD < nCount)
			{
				m_clPtSfrOffset[m_nSelectIndexCCD].x += nMoveSize;
			}
			// 원형마크 영역
			else
			{
				nIndex = m_nSelectIndexCCD - nCount;
				m_clRectCircle[nIndex].left += nMoveSize;
				m_clRectCircle[nIndex].right += nMoveSize;
			}
		}
		else
		{
			// 검사 영역
			if (m_nSelectIndexCCD < nCount)
			{
				if (m_nSelectIndexCCD == 0)
				{
					m_nCenterSfrSizeX += nMoveSize;
				}
				else
				{
					m_nSfrSizeX[nIndex] += nMoveSize;
				}
				
			}
			else
			{
				nIndex = m_nSelectIndexCCD - nCount;
				m_clRectCircle[nIndex].right += nMoveSize;
			}
		}
		break;
	}
	TCHAR szPos[SIZE_OF_100BYTE];
	if (m_nSelectIndexCCD < nCount)
	{
		
	}
	else
	{

		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("circle[%d] x:%lu, y: %lu / sizeX: %lu, sizeY: %lu"), nIndex,
			m_clRectCircle[nIndex].left, m_clRectCircle[nIndex].top,
			(m_clRectCircle[nIndex].right - m_clRectCircle[nIndex].left),
			(m_clRectCircle[nIndex].bottom , m_clRectCircle[nIndex].top)
		);
		AddLog(szPos, 0, m_nUnit);
	}
	this->DrawRectSfr(m_nSelectIndexCCD);
}

//-----------------------------------------------------------------------------
//
//	SNR 마크 저장
//
//-----------------------------------------------------------------------------
void CVisionStatic::RegistSnrMark()
{
    TCHAR szPos[SIZE_OF_100BYTE];
    int nPitch, nSizeX, nSizeY;
    int i;

	nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, M_NULL);
	nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_X, M_NULL);
	nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_Y, M_NULL);

	if (g_FindCirclePos(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][1],  g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)	//RegistSnrMark
	{
		g_ShowMsgPopup(_T("ERROR"), _T("원형 마크 찾기 실패"), RGB_COLOR_RED);
		return;
	}

	//g_CalcImageAlign(m_nUnit);	//RegistSnrMark

	//g_clModelData[m_nUnit].m_clSfrInfo.m_dSnrOcX[g_clModelType.m_nModelIndex] = g_clTaskWork[m_nUnit].m_dOcResultX;
	//g_clModelData[m_nUnit].m_clSfrInfo.m_dSnrOcY[g_clModelType.m_nModelIndex] = g_clTaskWork[m_nUnit].m_dOcResultY;

 //   for (i = 0; i < MAX_SNR_COUNT; i++)
 //   {
 //       g_clModelData[m_nUnit].m_clSfrInfo.m_clPtSnr[i] = g_clTaskWork[m_nUnit].m_clPtSnr[i];
 //       g_clModelData[m_nUnit].m_clSfrInfo.m_clRectSnr[i] = m_clRectDrawSnr[i];
 //   }

 //   g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

 //   g_clVision.ClearOverlay(m_nUnit);
 //   for (i = 0; i < MAX_SNR_COUNT; i++)
 //   {
 //       g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectDrawSnr[i], M_COLOR_YELLOW, 1, FALSE, PS_DOT);

 //       _stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), i);
 //       g_clVision.DrawMOverlayText(m_nUnit, m_clRectDrawSnr[i].left + 10, m_clRectDrawSnr[i].top + 10, szPos, M_COLOR_BLUE, _T("Arial"), 15, 15);
 //   }

 //   g_clVision.DrawOverlayAll(m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	FOV DISTORTION ROTATION 마크 저장
//
//-----------------------------------------------------------------------------
void CVisionStatic::RegistFovMark()
{
    int nPitch, nSizeX, nSizeY;
    int i;

	int iWidth = 0;
	int iHeight = 0;

    nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, M_NULL);
    nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_X, M_NULL);
    nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_Y, M_NULL);


    for (i = 0; i < MAX_FOV_COUNT; i++)
    {
		if (m_clPtFovOffset[i].x < 1)
		{
			m_clPtFovOffset[i].x = 0;
			m_clRectFov[i].left = 0;
			m_clRectFov[i].right = m_nFovSizeX[i];
		}

		if (m_clPtFovOffset[i].y < 1)
		{ 
			m_clRectFov[i].top = 0;
			m_clPtFovOffset[i].y = 0;
			m_clRectFov[i].bottom = m_nFovSizeY[i];
		}
		//m_nFovSizeY
		if (m_clPtFovOffset[i].x + m_nFovSizeX[i] > g_clModelData[m_nUnit].m_nWidth - 1)
		{
			m_clPtFovOffset[i].x = g_clModelData[m_nUnit].m_nWidth - 1 - m_nFovSizeX[i];
			m_clRectFov[i].left = m_clPtFovOffset[i].x;
			m_clRectFov[i].right = m_clRectFov[i].left + m_nFovSizeX[i];
		}

		if (m_clPtFovOffset[i].y + m_nFovSizeY[i] > g_clModelData[m_nUnit].m_nHeight - 1)
		{
			m_clPtFovOffset[i].y = g_clModelData[m_nUnit].m_nHeight - 1 - m_nFovSizeY[i];
			m_clRectFov[i].top = m_clPtFovOffset[i].y;
			m_clRectFov[i].bottom = m_clRectFov[i].top + m_nFovSizeY[i];
		}
		//m_clRectFov[i].right = m_clRectFov[i].left + m_nFovSizeX[i];
		if (m_clRectFov[i].right > g_clModelData[m_nUnit].m_nWidth - 1)
		{
			m_clRectFov[i].right = g_clModelData[m_nUnit].m_nWidth - 1;
		}
		if (m_clRectFov[i].bottom > g_clModelData[m_nUnit].m_nHeight - 1)
		{
			m_clRectFov[i].bottom = g_clModelData[m_nUnit].m_nHeight - 1;
		}
		//g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight
		g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[i].x = m_clRectFov[i].left;
		g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[i].y = m_clRectFov[i].top;

		g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeX[i] = m_clRectFov[i].right - m_clRectFov[i].left;
		g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeY[i] = m_clRectFov[i].bottom - m_clRectFov[i].top;
    }

	TCHAR szPos[SIZE_OF_100BYTE];

	g_CalcImageAlign(m_nUnit);//RegistFovMark

	//g_clModelData[m_nUnit].m_clSfrInfo.m_dFovOcX = g_clTaskWork[m_nUnit].m_dOcResultX;
	//g_clModelData[m_nUnit].m_clSfrInfo.m_dFovOcY = g_clTaskWork[m_nUnit].m_dOcResultY;

    g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

    g_clVision.ClearOverlay(m_nUnit);



    for (i = 0; i < MAX_FOV_COUNT; i++)
    {
		iWidth = m_nFovSizeX[i];
		iHeight = m_nFovSizeY[i];

        g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectFov[i], M_COLOR_BLUE, 2, FALSE, PS_DOT);
		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), i);
		g_clVision.DrawMOverlayText(m_nUnit, m_clRectFov[i].left + 10, m_clRectFov[i].top + 10, szPos, M_COLOR_WHITE, _T("Arial"), 15, 15);

		if (g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_AUTO)
		{
			g_clVision.SaveFovImage(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][1], nPitch, iWidth, iHeight, i, m_clRectFov[i]);
		}
    } 

	_stprintf_s(szPos, SIZE_OF_100BYTE, _T("Fov Roi"));
	g_clVision.DrawMOverlayText(m_nUnit, 20, 20, szPos, M_COLOR_WHITE, _T("Arial"), 15, 30);
    g_clVision.DrawOverlayAll(m_nUnit);

	
}

//-----------------------------------------------------------------------------
//
//	원형마크 저장
//
//-----------------------------------------------------------------------------
void CVisionStatic::RegistCircleMark()
{
	int nPitch, nSizeX, nSizeY;
	int i;

	g_clVision.ClearOverlay(m_nUnit);
	
	for (i = 0; i < 4; i++)
	{		
		g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, m_clRectCircle[i], M_COLOR_GREEN, 2, FALSE, PS_DOT);
	}

	nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, M_NULL);
	nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_X, M_NULL);
	nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_Y, M_NULL);

	if (g_FindCirclePos(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][2], m_clRectCircle) == false)	//RegistCircleMark
	{
		g_ShowMsgPopup(_T("ERROR"), _T("원형 마크 찾기 실패"), RGB_COLOR_RED);
		return;
	}

	for (i = 0; i < 4; i++)
	{
		g_clModelData[m_nUnit].m_clSfrInfo.m_clPtCircle[i] = g_clTaskWork[m_nUnit].m_clPtCircle[i];
		g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle[i] = m_clRectCircle[i];
	}


	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	g_clVision.DrawOverlayAll(m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	ROI 영역 모델 데이터에 저장
//
//-----------------------------------------------------------------------------
void CVisionStatic::SaveSfrRoi()
{
	TCHAR szPos[SIZE_OF_100BYTE];
	int i;

	int nPitch, nSizeX, nSizeY;

	nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, M_NULL);
	nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_X, M_NULL);
	nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_Y, M_NULL);

	g_clVision.ClearOverlay(m_nUnit);
	

	//
	//sfr 영역 저장
	//
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].x = m_clRectROI[i].left;
		g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].y = m_clRectROI[i].top;

		g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeX[i] = m_clRectROI[i].right - m_clRectROI[i].left;
		g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeY[i] = m_clRectROI[i].bottom - m_clRectROI[i].top;

		g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].x, g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].y,
			g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].x + g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeX[i],
			g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].y + g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeY[i], M_COLOR_BLUE, 1, FALSE);


		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), i);
		g_clVision.DrawMOverlayText(m_nUnit, g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].x + 10, g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].y + 10, szPos, M_COLOR_GREEN, _T("Arial"), 15, 15);
	}

	//
	//원형마크 영역 저장
	//
	for (i = 0; i < 4; i++)
	{
		g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle[i] = m_clRectCircle[i];

		g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle[i], M_COLOR_GREEN, 2, FALSE, PS_DOT);

		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), i);
		g_clVision.DrawMOverlayText(m_nUnit, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle[i].left + 10, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle[i].top + 10,
			szPos, M_COLOR_GREEN, _T("Arial"), 30, 25);
	}


	//if (g_FindCirclePos(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][1], g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)	//SaveSfrRoi
	//if (g_OpencvFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle , false) == false)

	if (g_MilFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)		//SaveSfrRoi
	{
		g_ShowMsgPopup(_T("ERROR"), _T("원형 마크 찾기 실패"), RGB_COLOR_RED);
		return;
	}

	g_CalcImageAlign(m_nUnit);//SaveSfrRoi


	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	g_clVision.DrawOverlayAll(m_nUnit);
}