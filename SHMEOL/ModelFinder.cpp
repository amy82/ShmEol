#include "StdAfx.h"
#include "ModelFinder.h"


CModelFinder::CModelFinder(void)
{
	int i, j;

	//m_MilMarkSystem = M_NULL;
	m_MilMarkDisplay[0] = m_MilMarkDisplay[1] = M_NULL;
	m_MilMarkImage[0] = m_MilMarkImage[1] = M_NULL;
	m_MilMarkOverlay[0] = m_MilMarkOverlay[1] = M_NULL;

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_MARK_COUNT; j++)
		{
			m_MilModModel[i][j] = M_NULL;
			m_bMarkState[i][j] = false;
			m_bMarkState[i][j] = false;
			m_clPtMarkSize[i][j].x = 0.0;
			m_clPtMarkSize[i][j].y = 0.0;

			m_clPtMarkSize[i][j].x = 0.0;
			m_clPtMarkSize[i][j].y = 0.0;
		}

		m_MilModResult[i] = M_NULL;
	}
	MilMarkTempImage = M_NULL;

	m_clPtMarkMaxSize.x = m_clPtMarkMaxSize.y = 0;
	m_clPtMarkDispSize.x = m_clPtMarkDispSize.y = 0;

	m_clPtMarkCenterPos.x = m_clPtMarkCenterPos.y = 0;
	m_clPtMarkStartPos.x = m_clPtMarkStartPos.y = 0;
	m_bInitMarkOverlay = false;
	m_bEnableMarkOverlay = false;
}


CModelFinder::~CModelFinder(void)
{
}


//-----------------------------------------------------------------------------
//
//	마크 초기화
//
//-----------------------------------------------------------------------------
void CModelFinder::InitMark()
{
	int i;

	//MsysAlloc(M_SYSTEM_VGA, M_DEV1, M_COMPLETE, &m_MilMarkSystem);

	//WINDOWPLACEMENT wndpl;
	//double dSizeX = 0.0;
	//double dSizeY = 0.0;

	//m_clMarkViewDlg
	//g_pCarAABonderDlg->m_clCcdDlg.m_clMarkViewDlg.GetDlgItem(IDC_STATIC_ALIGN_MARK_VIEW_IMAGE)->GetWindowPlacement(&wndpl);

	//dSizeX = 261.0;// wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	//dSizeY = 175.0;//wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top;

	//MbufAllocColor(g_clVision.m_MilSystem[0], 3, dSizeX, dSizeY, 8 + M_UNSIGNED, M_IMAGE + M_DISP + M_PROC, &m_MilMarkImage[0]);
	//MbufAllocColor(m_MilMarkSystem, 1L, MAX_MARK_SIZE_X, MAX_MARK_SIZE_Y, 8 + M_UNSIGNED, M_IMAGE + M_DISP + M_PROC, &m_MilMarkImage[1]);

	for (i = 0; i < 2; i++)
	{
		// Mark Buffer
		//if (i == 0)
			//MbufAlloc2d(m_MilMarkSystem, MAX_MARK_SIZE_X, MAX_MARK_SIZE_Y, 8 + M_UNSIGNED, M_IMAGE + M_DISP + M_PROC, &m_MilMarkImage[i]);
			//MbufAllocColor(m_MilMarkSystem, 3, MAX_MARK_SIZE_X, MAX_MARK_SIZE_Y, 8 + M_UNSIGNED, M_IMAGE + M_DISP + M_PROC, &m_MilMarkImage[i]);
		// Mask Buffer
		//else
			//MbufAllocColor(m_MilMarkSystem, 1L, MAX_MARK_SIZE_X, MAX_MARK_SIZE_Y, 8 + M_UNSIGNED, M_IMAGE + M_DISP + M_PROC, &m_MilMarkImage[i]);

		/*if (m_MilMarkImage[i] != M_NULL)
		{
			MdispAlloc(g_clVision.m_MilSystem[0], M_DEFAULT, _T("M_DEFAULT"), M_DEFAULT, &m_MilMarkDisplay[i]);
			if (MdispInquire(m_MilMarkDisplay[i], M_DISPLAY_MODE, M_NULL) != M_WINDOWED)
			{
				MdispFree(m_MilMarkDisplay[i]);
				m_MilMarkDisplay[i] = M_NULL;
			}
		}*/
	}

	MbufAllocColor(g_clVision.m_MilSystem[0], 1L, CAM_SIZE_X, CAM_SIZE_Y, (8 + M_UNSIGNED), M_IMAGE + M_DISP + M_PROC, &MilMarkTempImage);
#ifdef ON_LINE_MIL
	if (MilMarkTempImage)	MbufClear(MilMarkTempImage, 0);
#endif
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CModelFinder::CloseModelFind()
{
	int i, j;

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_MARK_COUNT; j++)
		{
			if (m_MilModModel[i][j] != M_NULL)
				MmodFree(m_MilModModel[i][j]);
		}

		if (m_MilModResult[i] != M_NULL)
			MmodFree(m_MilModResult[i]);
	}

	for (i = 0; i < 2; i++)
	{
		if (m_MilMarkDisplay[i] != M_NULL)
		{
			//MdispDeselect(m_MilMarkDisplay[i], m_MilMarkImage[i]);
			MdispFree(m_MilMarkDisplay[i]);

			m_MilMarkDisplay[i] = M_NULL;
		}

		if (m_MilMarkImage[i])
		{
			if (m_MilMarkImage[i] != M_NULL)
				MbufFree(m_MilMarkImage[i]);

			m_MilMarkImage[i] = M_NULL;
		}
	}

	if (MilMarkTempImage)
	{
		if (MilMarkTempImage != M_NULL)
			MbufFree(MilMarkTempImage);

		MilMarkTempImage = M_NULL;
	}
	
	//if (m_MilMarkSystem != M_NULL)
	//	MsysFree(m_MilMarkSystem);

	//m_MilMarkSystem = M_NULL;
}

//-----------------------------------------------------------------------------
//
//	오버레이 Enable
//
//-----------------------------------------------------------------------------
void CModelFinder::EnableOverlay()
{
#ifdef ON_LINE_MIL
	if (m_bInitMarkOverlay == false && m_MilMarkDisplay[0] != M_NULL)
	{
		MIL_INT DisplayType = MdispInquire(m_MilMarkDisplay[0], M_DISPLAY_TYPE, M_NULL);
		if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
		//if (MdispInquire(m_MilMarkDisplay[0], M_DISPLAY_TYPE, M_NULL) == M_WINDOWED)
		{
			/*
			MdispControl(m_MilDisplay[nDispIndex], M_OVERLAY_SHOW, M_ENABLE);// M_WINDOW_OVR_SHOW
			MdispControl(m_MilDisplay[nDispIndex], M_OVERLAY, M_ENABLE);//M_WINDOW_OVR_WRITE
			MdispInquire(m_MilDisplay[nDispIndex], M_OVERLAY_ID, &m_MilOverlay[nDispIndex]);//M_WINDOW_OVR_BUF_ID
			MdispInquire(m_MilDisplay[nDispIndex], M_TRANSPARENT_COLOR, &m_nMilTransparent[nDispIndex]);
			*/

			MdispControl(m_MilMarkDisplay[0], M_WINDOW_SHOW, M_ENABLE);
			MdispControl(m_MilMarkDisplay[0], M_OVERLAY, M_ENABLE);
			MdispInquire(m_MilMarkDisplay[0], M_OVERLAY_ID, &m_MilMarkOverlay[0]);//[1]);
			MdispControl(m_MilMarkDisplay[0], M_OVERLAY_SHOW, M_DISABLE);//M_WINDOW_OVR_SHOW, M_DISABLE);

			m_lTransparentColor[0] = (long)MdispInquire(m_MilMarkDisplay[0], M_TRANSPARENT_COLOR, M_NULL);

			MbufClear(m_MilMarkOverlay[0], m_lTransparentColor[0]);
			MdispControl(m_MilMarkDisplay[0], M_OVERLAY_CLEAR, M_DEFAULT);
			MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);

			m_bInitMarkOverlay = true; 
		}

		if (m_bInitMarkOverlay)
		{
			if (m_bEnableMarkOverlay == false)
			{
				MdispControl(m_MilMarkDisplay[0], M_OVERLAY_SHOW, M_ENABLE);
			}
			else
			{
				MdispControl(m_MilMarkDisplay[0], M_OVERLAY_SHOW, M_DISABLE);
				m_bEnableMarkOverlay = FALSE;
			}

			m_bInitMarkOverlay = FALSE;
		}
	}
#endif
}

//-----------------------------------------------------------------------------
//
//	마크 속성 세팅
//
//-----------------------------------------------------------------------------
void CModelFinder::SettingFindMark(int nUnit, int nNo)
{
	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return;

	if (nNo < 0 || nNo >= MAX_MARK_COUNT)
		return;

	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SEARCH_POSITION_RANGE, M_ENABLE);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SEARCH_ANGLE_RANGE, M_ENABLE);//M_ENABLE);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SEARCH_SCALE_RANGE, M_ENABLE);// M_ENABLE);

	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_NUMBER, 1);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SPEED, M_MEDIUM/*M_HIGH*/);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_ACCURACY, M_MEDIUM);

	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SHARED_EDGES, M_DISABLE);
	//MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_ASPECT_RATIO, M_DEFAULT);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_ASPECT_RATIO, 1.0);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SAVE_TARGET_EDGES, M_DISABLE);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_TARGET_CACHING, M_DISABLE);

	//if( iCh == 0 )	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SMOOTHNESS, 30);
	//else			MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SMOOTHNESS, 70);

	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SMOOTHNESS, g_clMarkData[nUnit].m_nSmooth[nNo]);// 70/*MarkData.iSmooth[nCh][nNo]*/);

	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_DETAIL_LEVEL, M_MEDIUM);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_FILTER_MODE, M_RECURSIVE);

	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ANGLE, 1);

	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ANGLE_DELTA_NEG, 0.9);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ANGLE_DELTA_POS, 1.1);

	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_SCALE, 1.0);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_SCALE_MIN_FACTOR, 0.99);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_SCALE_MAX_FACTOR, 1.01);
	//MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_SCALE_MAX_FACTOR, 1.2);

	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ACCEPTANCE, 90);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ACCEPTANCE_TARGET, 60);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_CERTAINTY, 90);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_CERTAINTY_TARGET, 60);


	MmodPreprocess(m_MilModModel[nUnit][nNo], M_DEFAULT);
}

//-----------------------------------------------------------------------------
//
//	마크 등록
//
//-----------------------------------------------------------------------------
bool CModelFinder::RegistMark(int nUnit, int nNo)
{
	//g_clVision.ClearOverlay(nUnit);

	//MbufClear(m_MilMarkImage[0], 192);
#ifdef ON_LINE_MIL
	MbufClear(MilMarkTempImage, 0);
#endif
	long startX = (long)m_clPtMarkStartPos.x;	// (long)(m_clPtMarkCenterPos.x - (long)(m_clPtMarkSize.x / 2));		//여기서 값이 다 0이다 210702
	long startY = (long)m_clPtMarkStartPos.y;	//(long)(m_clPtMarkCenterPos.y - (long)(m_clPtMarkSize.y / 2));
	long endX = (long)(startX + m_clPtMarkSize[nUnit][nNo].x);
	long endY = (long)(startY + m_clPtMarkSize[nUnit][nNo].y);


	//### MODEL FIND
	//MbufClear(m_MilMarkImage[0], 192);
	if (m_MilModModel[nUnit][nNo])
	{
		if (m_MilModModel[nUnit][nNo] != M_NULL)
		{
			MmodFree(m_MilModModel[nUnit][nNo]);
			m_MilModModel[nUnit][nNo] = M_NULL;
		} 
	}


	MmodAlloc(g_clVision.m_MilSystem[0], M_GEOMETRIC, M_DEFAULT, &m_MilModModel[nUnit][nNo]);
	MmodDefine(m_MilModModel[nUnit][nNo], M_IMAGE, g_clVision.m_MilGrabImageChild[nUnit][0], startX, startY, m_clPtMarkSize[nUnit][nNo].x, m_clPtMarkSize[nUnit][nNo].y);
	//MmodDraw(M_DEFAULT, m_MilModModel[nUnit][nNo], m_MilMarkImage[0], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);	//기존 210705
	MmodDraw(M_DEFAULT, m_MilModModel[nUnit][nNo], MilMarkTempImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_REFERENCE_X, m_clPtMarkSize[nUnit][nNo].x / 2);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, M_REFERENCE_Y, m_clPtMarkSize[nUnit][nNo].y / 2);
	return TRUE;
}

//-----------------------------------------------------------------------------
//
//	마크 전체 로드
//
//-----------------------------------------------------------------------------
void CModelFinder::LoadMark(CString sModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;
	int i, j;
	double dSizeX = 0.0;
	double dSizeY = 0.0;

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		if (m_MilModResult[i] != M_NULL)
		{
			MmodFree(m_MilModResult[i]);
			m_MilModResult[i] = M_NULL;
		}

		MmodAllocResult(g_clVision.m_MilSystem[0], M_DEFAULT, &m_MilModResult[i]);

		for (j = 0; j < MAX_MARK_COUNT; j++)
		{
			if (m_MilModModel[i][j] != M_NULL)
			{
				MmodFree(m_MilModModel[i][j]);
				m_MilModModel[i][j] = M_NULL;
			}

			_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MARK-%d.mod"), BASE_DATA_PATH, j + 1);
			if (clFinder.FindFile(szPath) == TRUE)
			{
				MmodRestore(szPath, g_clVision.m_MilSystem[0], M_DEFAULT, &m_MilModModel[i][j]);
				m_bMarkState[i][j] = true;
			}
			else
			{
				m_bMarkState[i][j] = false;
			}

			MmodInquire(g_clModelFinder.m_MilModModel[i][j], M_DEFAULT, M_ALLOC_SIZE_X, &dSizeX);
			MmodInquire(g_clModelFinder.m_MilModModel[i][j], M_DEFAULT, M_ALLOC_SIZE_Y, &dSizeY);

			g_clModelFinder.m_clPtMarkSize[i][j].x = (LONG)dSizeX;
			g_clModelFinder.m_clPtMarkSize[i][j].y = (LONG)dSizeY;
		}


		//230411
		
		

		
		//
	}
}

//-----------------------------------------------------------------------------
//
//	마크 로드
//
//-----------------------------------------------------------------------------
void CModelFinder::LoadMark(CString sModelName, int nUnit, int nNo)
{
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return;

	if (nNo < 0 || nNo >= MAX_MARK_COUNT)
		return;


	if (m_MilModResult[nUnit] != M_NULL)
	{
		MmodFree(m_MilModResult[nUnit]);
		m_MilModResult[nUnit] = M_NULL;
	}

	MmodAllocResult(g_clVision.m_MilSystem[0], M_DEFAULT, &m_MilModResult[nUnit]);

	if (m_MilModModel[nUnit][nNo] != M_NULL)
	{
		MmodFree(m_MilModModel[nUnit][nNo]);
		m_MilModModel[nUnit][nNo] = M_NULL;
	}

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MARK-%d.mod"), BASE_DATA_PATH,  nNo + 1);
	if (clFinder.FindFile(szPath) == TRUE)
	{
		MmodRestore(szPath, g_clVision.m_MilSystem[0], M_DEFAULT, &m_MilModModel[nUnit][nNo]);
		m_bMarkState[nUnit][nNo] = true;
	}
	else
	{
		m_bMarkState[nUnit][nNo] = false;
	}
}

//-----------------------------------------------------------------------------
//
//	마크 저장
//
//-----------------------------------------------------------------------------
bool CModelFinder::SaveMark(CString sModelName, int nUnit, int nNo)
{
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return false;

	if (nNo < 0 || nNo >= MAX_MARK_COUNT)
		return false;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_DATA_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MARK-%d.mod"), BASE_DATA_PATH, nNo + 1);
	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SMOOTHNESS, g_clMarkData[nUnit].m_nSmooth[nNo]);// 70);
	m_bMarkState[nUnit][nNo] = true;

	MmodSave(szPath, m_MilModModel[nUnit][nNo], M_DEFAULT);

	// BMP 
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MARK-%d.bmp"), BASE_DATA_PATH,nNo + 1);
	//MbufExport(szPath, M_BMP, m_MilMarkImage[0]);
	MbufExport(szPath, M_BMP, m_MilMarkImage[1]);

	return true;
}

//-----------------------------------------------------------------------------
//
//	마크 삭제
//
//-----------------------------------------------------------------------------
void CModelFinder::DeleteMark(CString sModelName, int nUnit, int nNo)
{
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return;

	if (nNo < 0 || nNo >= MAX_MARK_COUNT)
		return;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MARK-%d.mod"), BASE_DATA_PATH, nNo + 1);
	if (clFinder.FindFile(szPath) == TRUE)
		DeleteFile(szPath);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MARK-%d.bmp"), BASE_DATA_PATH, nNo + 1);
	if (clFinder.FindFile(szPath) == TRUE)
		DeleteFile(szPath);

	m_bMarkState[nUnit][nNo] = false;
}

//-----------------------------------------------------------------------------
//
//	마크 재정렬(삭제후)
//
//-----------------------------------------------------------------------------
void CModelFinder::ReSortMark(CString sModelName, int nUnit, int nNo)
{
	int i, j;

	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return;

	if (nNo < 0 || nNo >= MAX_MARK_COUNT)
		return;

	for (i = 0; i < MAX_MARK_COUNT; i++)
	{
		if (m_bMarkState[nUnit][i] == true)
		{
			for (j = nNo; j >= 0; j--)
			{
				if (m_bMarkState[nUnit][j] == false)
				{
					this->ReNumberMark(sModelName, nUnit, i, j);
					m_bMarkState[nUnit][i] = false;
					m_bMarkState[nUnit][j] = true;
					break;
				}
			}
		}
	}

	this->LoadMark(g_clSysData.m_szModelName);
}

//-----------------------------------------------------------------------------
//
//	마크 재 넘버링
//
//-----------------------------------------------------------------------------
void CModelFinder::ReNumberMark(CString sModelName, int nUnit, int nOldNo, int nNewNo)
{
	TCHAR szOldPath[SIZE_OF_1K];
	TCHAR szNewPath[SIZE_OF_1K];
	CFileFind clFinder;

	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return;

	if (nOldNo < 0 || nOldNo >= MAX_MARK_COUNT)
		return;

	if (nNewNo < 0 || nNewNo >= MAX_MARK_COUNT)
		return;

	if (m_bMarkState[nUnit][nOldNo] == true)
	{
		_stprintf_s(szOldPath, SIZE_OF_1K, _T("%s\\MARK-%d.mod"), BASE_DATA_PATH, nOldNo + 1);
		_stprintf_s(szNewPath, SIZE_OF_1K, _T("%s\\MARK-%d.mod"), BASE_DATA_PATH, nNewNo + 1);
		if (clFinder.FindFile(szOldPath) == TRUE)
		{
			CopyFile(szOldPath, szNewPath, TRUE);
			DeleteFile(szOldPath);
		}

		_stprintf_s(szOldPath, SIZE_OF_1K, _T("%s\\MARK-%d.bmp"), BASE_DATA_PATH, nOldNo + 1);
		_stprintf_s(szNewPath, SIZE_OF_1K, _T("%s\\MARK-%d.bmp"), BASE_DATA_PATH, nNewNo + 1);
		if (clFinder.FindFile(szOldPath) == TRUE)
		{
			CopyFile(szOldPath, szNewPath, TRUE);
			DeleteFile(szOldPath);
		}
	}
}

//-----------------------------------------------------------------------------
//
//	마크 오버레이 그리기
//
//-----------------------------------------------------------------------------
void CModelFinder::DrawMarkOverlay(int nUnit, int nNo)
{
	double dSizeX, dSizeY;
	CDMPoint clDptCenter;

	dSizeX = dSizeY = 0.0;

	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return;

	if (nNo < 0 || nNo >= MAX_MARK_COUNT)
		return;

	double m_dZoomX = 0.0;
	double m_dZoomY = 0.0;
	
#ifdef ON_LINE_MIL
	MbufClear(m_MilMarkOverlay[0], m_lTransparentColor[0]);

	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ALLOC_SIZE_X, &dSizeX);
	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ALLOC_SIZE_Y, &dSizeY);

	m_dZoomX = (double)g_clModelFinder.m_clPtSmallMarkDispSize.x / (double)dSizeX;		//마크 이미지 축소 OR 확대
	m_dZoomY = (double)g_clModelFinder.m_clPtSmallMarkDispSize.y / (double)dSizeY;

	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, 3203L, m_dZoomX);	//M_DRAW_SCALE_X
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, 3204L, m_dZoomY);	//M_DRAW_SCALE_Y

	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_REFERENCE_X, &clDptCenter.x);  
	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_REFERENCE_Y, &clDptCenter.y);
	
	MgraColor(M_DEFAULT, M_COLOR_GREEN);
	MmodDraw(M_DEFAULT, m_MilModModel[nUnit][nNo], m_MilMarkOverlay[0], M_DRAW_DONT_CARE, M_DEFAULT, M_DEFAULT);//<---노란 마스크 영역


	MgraColor(M_DEFAULT, M_COLOR_MAGENTA);
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, 3203L, m_dZoomX);   //M_DRAW_SCALE_X
	MmodControl(m_MilModModel[nUnit][nNo], M_DEFAULT, 3204L, m_dZoomY);   //M_DRAW_SCALE_Y

	MmodControl(m_MilModModel[nUnit][nNo], M_CONTEXT, M_SMOOTHNESS, g_clMarkData[nUnit].m_nSmooth[nNo]);
	MmodDraw(M_DEFAULT, m_MilModModel[nUnit][nNo], m_MilMarkOverlay[0], M_DRAW_EDGES, M_DEFAULT, M_DEFAULT);//<-----EDGE 영역

	MgraColor(M_DEFAULT, M_COLOR_RED);
	 

//	m_dZoomX = (double)g_clModelFinder.m_clPtSmallMarkDispSize.x / (double)g_clModelFinder.m_clPtZoomMarkDispSize.x;		//마크 이미지 축소 OR 확대
	//m_dZoomY = (double)g_clModelFinder.m_clPtSmallMarkDispSize.y / (double)g_clModelFinder.m_clPtZoomMarkDispSize.y;
	int dCenterX = clDptCenter.x * m_dZoomX;
	int dCenterY = clDptCenter.y * m_dZoomY;
	MgraLine(M_DEFAULT, m_MilMarkOverlay[0], dCenterX, 0, dCenterX, dSizeY);	//<-----Center Cross x축
	MgraLine(M_DEFAULT, m_MilMarkOverlay[0], 0, dCenterY, dSizeX, dCenterY);	//<-----Center Cross y축
#endif
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CModelFinder::FindModel(int nUnit, int nNo, bool bAreaFlag, CDMPoint& clFindPos, double& dScore, double& dAngle, double& dFitError, CDMPoint& clMarkSize, CDMPoint& clMarkCenter)
{
	int nMinMatch = 50;								//Mark 매칭율 저장 변수

	dScore = 0.0;
	dFitError = 0.0;
	clFindPos.x = 0.0;
	clFindPos.y = 0.0;

	if (nUnit < 0 || nUnit >= MAX_UNIT_COUNT)
		return false;

	if (nNo < 0 || nNo >= MAX_MARK_COUNT)
		return false;

	if (m_bMarkState[nUnit][nNo] == false)
		return false;

	if (m_MilModModel[nUnit][nNo] == M_NULL)
		return false;


	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ALLOC_SIZE_X, &clMarkSize.x);
	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_ALLOC_SIZE_Y, &clMarkSize.y);
	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_REFERENCE_X, &clMarkCenter.x);
	MmodInquire(m_MilModModel[nUnit][nNo], M_DEFAULT, M_REFERENCE_Y, &clMarkCenter.y);
	// 
	if (m_MilModResult[nUnit] != M_NULL)
	{
		MmodFree(m_MilModResult[nUnit]);
		m_MilModResult[nUnit] = M_NULL;

		MmodAllocResult(g_clVision.m_MilSystem[0], M_DEFAULT, &m_MilModResult[nUnit]);
	}

	MmodPreprocess(m_MilModModel[nUnit][nNo], M_DEFAULT);
	if (bAreaFlag == true)
	{
		MIL_ID MilChildLow = M_NULL;

		//MbufChild2d(g_clVision.m_MilGrabImage[nUnit]/*m_MilGrabImage[nCh]*/,
		//
		//MbufChild2d(g_clVision.m_MilCcdProcChild[nUnit][1],

		MbufChild2d(g_clVision.m_MilGrabImage[nUnit][0],
			g_clMarkData[nUnit].m_clRectRoi[nNo].left, g_clMarkData[nUnit].m_clRectRoi[nNo].top,
			g_clMarkData[nUnit].m_clRectRoi[nNo].right - g_clMarkData[nUnit].m_clRectRoi[nNo].left,
			g_clMarkData[nUnit].m_clRectRoi[nNo].bottom - g_clMarkData[nUnit].m_clRectRoi[nNo].top,
			&MilChildLow);

		/*else
		{
		MbufChild2d(Vision.GrapImg[nCh],
		MarkData.rcFindROI[nCh][nNo].left,
		MarkData.rcFindROI[nCh][nNo].top,
		MarkData.rcFindROI[nCh][nNo].right - MarkData.rcFindROI[iCh][nNo].left,
		MarkData.rcFindROI[nCh][nNo].bottom - MarkData.rcFindROI[iCh][nNo].top,
		&MilChildLow);
		}*/

		MmodFind(m_MilModModel[nUnit][nNo], MilChildLow, m_MilModResult[nUnit]);

		if (MilChildLow != M_NULL)
			MbufFree(MilChildLow);
	}
	else
	{
		/*if (Vision.iGrabMode[iCh] == (int)GRAB_MODE_RGRG)		MmodFind(ModModel[nUnit][iPatNo], Vision.ImageChild[nUnit], ModResult[nUnit]);
		else													MmodFind(ModModel[nUnit][iPatNo], Vision.GrapImg[nUnit], ModResult[nUnit]);*/
		//MmodFind(m_MilModModel[nUnit][nNo], g_clVision.m_MilCcdProcImage[nUnit], m_MilModResult[nUnit]);
		//MmodFind(m_MilModModel[nUnit][nNo], g_clVision.m_MilCcdProcChild[nUnit][1], m_MilModResult[nUnit]);


		MmodFind(m_MilModModel[nUnit][nNo], g_clVision.m_MilGrabImage[nUnit][0], m_MilModResult[nUnit]);
	}

	long lObbjNo = 0;
	MmodGetResult(m_MilModResult[nUnit], M_DEFAULT, M_NUMBER + M_TYPE_LONG, &lObbjNo);
	if (lObbjNo < 1)
	{
		return false;		//Mark 인식 실패
	}

	double	Find_x[5];
	double	Find_y[5];
	double	Find_angle[5];
	double	Find_Score[5];
	double	Find_ScoreTarget[5];
	double	Find_FitError[5];

	int	   maxObjNum = 0;
	double oldtmpRate = 0;
	if (lObbjNo > 0 && lObbjNo < 5)
	{
		MmodGetResult(m_MilModResult[nUnit], M_DEFAULT, M_POSITION_X, Find_x);
		MmodGetResult(m_MilModResult[nUnit], M_DEFAULT, M_POSITION_Y, Find_y);
		MmodGetResult(m_MilModResult[nUnit], M_DEFAULT, M_ANGLE, Find_angle);
		MmodGetResult(m_MilModResult[nUnit], M_DEFAULT, M_SCORE, Find_Score);
		MmodGetResult(m_MilModResult[nUnit], M_DEFAULT, M_SCORE_TARGET, Find_ScoreTarget);
		MmodGetResult(m_MilModResult[nUnit], M_DEFAULT, M_FIT_ERROR, Find_FitError);

		oldtmpRate = 0;
		for (int i = 0; i< lObbjNo; i++)
		{
			if (Find_Score[i] + Find_ScoreTarget[i] >= oldtmpRate)
			{
				maxObjNum = i;
				oldtmpRate = Find_Score[i] + Find_ScoreTarget[i];
			}
		}
	}
	else
	{
		return false;
	}

	double	Val[2];
	Val[0] = Val[1] = 0.0;

	if (bAreaFlag)
	{
		clFindPos.x = Find_x[maxObjNum] +g_clMarkData[nUnit].m_clRectRoi[nNo].left;
		clFindPos.y = Find_y[maxObjNum] +g_clMarkData[nUnit].m_clRectRoi[nNo].top;
	}
	else
	{
		clFindPos.x = Find_x[maxObjNum];
		clFindPos.y = Find_y[maxObjNum];
	}

	dScore = Find_Score[maxObjNum];
	dAngle = Find_angle[maxObjNum];
	dFitError = Find_FitError[maxObjNum];

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CModelFinder::FindBestModel(int nUnit, bool bAreaFlag, int& nFindNo, double& dCenterX, double& dCenterY, double& dAngle, double& dScore, CDMPoint& clMarkSize, CDMPoint& clMarkCenter)
{
	STRUC_MARK_POS stMarkPos[MAX_MARK_COUNT];
	CDMPoint clMarkCenterResult;
	CDMPoint clMarkSizeResult;
	CDMPoint clCenterResult;
	double dScoreResult;
	double dAngleResult;
	double dFitErrResult;
	double dTempScore;
	int nBestFindIndex;
	int nFindCount;
	bool bFindMark;
	int i;

	dScoreResult = dAngleResult = dFitErrResult = dTempScore = 0.0;
	nBestFindIndex = -1;
	nFindCount = 0;
	bFindMark = false;

	for (i = 0; i < MAX_MARK_COUNT; i++)
	{
		if (m_bMarkState[nUnit][i] == true)
		{
			if (this->FindModel(nUnit, i, bAreaFlag, clCenterResult, dScoreResult, dAngleResult, dFitErrResult, clMarkSizeResult, clMarkCenterResult))
			{
				// 90이상 찾았으면 바로 리턴
				if (dScoreResult >= 90.0)
				{
					dScore = dScoreResult;
					nFindNo = i;
					dCenterX = clCenterResult.x;
					dCenterY = clCenterResult.y;
					dAngle = dAngleResult;
					clMarkSize = clMarkSizeResult;
					clMarkCenter = clMarkCenterResult;

					return true;
				}
				else
				{
					stMarkPos[i].dMarkCenterX = clCenterResult.x;
					stMarkPos[i].dMarkCenterY = clCenterResult.y;
					stMarkPos[i].dScore = dScoreResult;
					stMarkPos[i].dAngle = dAngleResult;
					stMarkPos[i].clDPtMarkSize = clMarkSizeResult;
					stMarkPos[i].clDPtMarkCenter = clMarkCenterResult;
				}
			}
		}
	}

	// Max Score 찾기
	for (i = 0; i < MAX_MARK_COUNT; i++)
	{
		if (m_bMarkState[nUnit][i] == true)
		{
			if (stMarkPos[i].dScore > dTempScore)
			{
				dTempScore = stMarkPos[i].dScore;
				nBestFindIndex = i;
				bFindMark = true;
			}
		}
	}

	// Max Score 찾았으면
	if (bFindMark == true)
	{
		// 최소 매칭율보다 작으면
		if (stMarkPos[nBestFindIndex].dScore < g_clModelData[nUnit].m_nMinMatching)
			return false;

		dScore = stMarkPos[nBestFindIndex].dScore;
		nFindNo = nBestFindIndex;
		dCenterX = stMarkPos[nBestFindIndex].dMarkCenterX;
		dCenterY = stMarkPos[nBestFindIndex].dMarkCenterY;
		dAngle = stMarkPos[nBestFindIndex].dAngle;
		clMarkSize = stMarkPos[nBestFindIndex].clDPtMarkSize;
		clMarkCenter = stMarkPos[nBestFindIndex].clDPtMarkCenter;
		return true;

	}

	return false;
}