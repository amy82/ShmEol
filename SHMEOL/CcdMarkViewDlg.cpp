// CcdMarkViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdMarkViewDlg.h"
#include "afxdialogex.h"


// CCcdMarkViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdMarkViewDlg, CDialogEx)

CCcdMarkViewDlg::CCcdMarkViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CCD_MARK_VIEW, pParent)
{
	m_nUnit = 0;
	m_nMarkNo = 0;
}

CCcdMarkViewDlg::~CCcdMarkViewDlg()
{
}

void CCcdMarkViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CCD_MARK_VIEW_TITLE, m_clColorStaticTitle);
	DDX_Control(pDX, IDC_STATIC_CCD_MARK_VIEW_MARK_NO, m_clColorStaticMarkNo);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_PREVIOUS, m_clColorButtonPrev);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_NEXT, m_clColorButtonNext);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_INIT, m_clColorButtonInit);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_REGIST, m_clColorButtonRegist);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_DELETE, m_clColorButtonDelete);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_ROI_SAVE, m_clColorButtonRoiSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_MASK, m_clColorButtonMarkView);
	DDX_Control(pDX, IDC_BUTTON_CCD_MARK_VIEW_FIND, m_clColorButtonMarkFind);

	DDX_Control(pDX, IDC_BUTTON_CCD_BMP_SAVE, m_clColorButtonImageSave);
	
}


BEGIN_MESSAGE_MAP(CCcdMarkViewDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_PREVIOUS, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewPrevious)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_NEXT, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewNext)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_INIT, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewInit)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_REGIST, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewRegist)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_DELETE, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewDelete)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_ROI_SAVE, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewRoiSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_MASK, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewMask)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MARK_VIEW_FIND, &CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewFind)
	ON_BN_CLICKED(IDC_BUTTON_CCD_BMP_SAVE, &CCcdMarkViewDlg::OnBnClickedButtonCcdBmpSave)
END_MESSAGE_MAP()


// CCcdMarkViewDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;

	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB_DLG_BG);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
BOOL CCcdMarkViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	this->InitMarkViewDlg();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticTitle.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTitle.SetFont(&m_clFontMid);

	m_clColorStaticMarkNo.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMarkNo.SetFont(&m_clFontMid);


	m_clMaskViewDlg.Create(IDD_DIALOG_CCD_MASK_VIEW, this);
	m_clMaskViewDlg.ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	마크뷰 초기화
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::InitMarkViewDlg()
{
#ifdef ON_LINE_MIL
	WINDOWPLACEMENT wndpl;

	GetDlgItem(IDC_STATIC_ALIGN_MARK_VIEW_IMAGE)->GetWindowPlacement(&wndpl);


	double dSizeX = 0.0;
	double dSizeY = 0.0;

	dSizeX = wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	dSizeY = wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top;

	g_clModelFinder.m_clPtSmallMarkDispSize.x = dSizeX;
	g_clModelFinder.m_clPtSmallMarkDispSize.y = dSizeY;

	//MbufAllocColor(g_clVision.m_MilSystem[0], 3, dSizeX, dSizeY, 8 + M_UNSIGNED, M_IMAGE + M_DISP + M_PROC, &g_clModelFinder.m_MilMarkImage[0]);
	MbufAllocColor(g_clVision.m_MilSystem[0], 1L, dSizeX, dSizeY, (8 + M_UNSIGNED), M_IMAGE + M_DISP + M_PROC, &g_clModelFinder.m_MilMarkImage[0]);

	if (g_clModelFinder.m_MilMarkImage[0] != M_NULL)
	{
		//MdispAlloc(g_clVision.m_MilSystem[0], M_DEFAULT, _T("M_DEFAULT"), M_DEFAULT, &g_clModelFinder.m_MilMarkDisplay[0]);

		//g_clModelFinder.m_MilMarkDisplay[0] = MdispAlloc(g_clVision.m_MilSystem[0], M_DEV0, M_DISPLAY_SETUP, M_DEFAULT, M_NULL);
		g_clModelFinder.m_MilMarkDisplay[0] = MdispAlloc(g_clVision.m_MilSystem[0], M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, M_NULL);

		MIL_INT DisplayType = MdispInquire(g_clModelFinder.m_MilMarkDisplay[0], M_DISPLAY_TYPE, M_NULL);
		//if (MdispInquire(m_MilCamDisplay[nDispIndex][i], M_DISPLAY_TYPE, M_NULL) == M_WINDOWED)
		//if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
		//if (MdispInquire(g_clModelFinder.m_MilMarkDisplay[0], M_DISPLAY_TYPE, M_NULL) != M_WINDOWED)
		if (DisplayType != M_WINDOWED)
		{
			MdispFree(g_clModelFinder.m_MilMarkDisplay[0]);
			g_clModelFinder.m_MilMarkDisplay[0] = M_NULL;
		}
	}

	g_clModelFinder.m_clPtMarkDispSize.x = wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	g_clModelFinder.m_clPtMarkDispSize.y = wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top;
	g_clModelFinder.m_clPtMarkMaxSize.x = g_clModelFinder.m_clPtMarkDispSize.x;// MAX_MARK_SIZE_X;
	g_clModelFinder.m_clPtMarkMaxSize.y = g_clModelFinder.m_clPtMarkDispSize.y;// MAX_MARK_SIZE_Y;

	if (g_clModelFinder.m_MilMarkDisplay[0] != M_NULL)
	{
		MdispSelectWindow(g_clModelFinder.m_MilMarkDisplay[0], g_clModelFinder.m_MilMarkImage[0], GetDlgItem(IDC_STATIC_ALIGN_MARK_VIEW_IMAGE)->m_hWnd);
		g_clModelFinder.EnableOverlay();
	}

	this->DisplayMarkView(m_nUnit, m_nMarkNo , m_clMaskViewDlg.m_iMarkSetSizeX, m_clMaskViewDlg.m_iMarkSetSizeY);

	this->ShowMarkNo();

#endif
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::DisplayMarkView(int nUnit, int nMarkNo, double dZoomMarkWidth, double dZoomMarkHeight)
{
#ifdef ON_LINE_MIL
	CFileFind clFinder;
	TCHAR szPath[SIZE_OF_1K];
	double dZoomX, dZoomY;
	double dSizeX, dSizeY;
	double dCenterX, dCenterY;

	m_nUnit = nUnit;

	if (nMarkNo < 0 || nMarkNo > MAX_MARK_COUNT)
		return;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MARK-%d.bmp"), BASE_DATA_PATH, nMarkNo + 1);

	MbufClear(g_clModelFinder.m_MilMarkOverlay[0], g_clModelFinder.m_lTransparentColor[0]);
	MbufClear(g_clModelFinder.m_MilMarkImage[0], 192);

	if (clFinder.FindFile(szPath) == TRUE)
	{
		MbufImport(szPath, M_BMP, M_LOAD, M_NULL, &g_clModelFinder.m_MilMarkImage[1]);

		//MmodDraw(M_DEFAULT, g_clModelFinder.m_MilModModel[m_nUnit][nMarkNo], g_clModelFinder.m_MilMarkImage[0], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

		MmodInquire(g_clModelFinder.m_MilModModel[m_nUnit][nMarkNo], M_DEFAULT, M_ALLOC_SIZE_X, &dSizeX);		//<-----여기서왜 마크 사이즈를 바꾸지?
		MmodInquire(g_clModelFinder.m_MilModModel[m_nUnit][nMarkNo], M_DEFAULT, M_ALLOC_SIZE_Y, &dSizeY);
		//dSizeX = 300;
		//dSizeY = 300;
		g_clModelFinder.m_clPtMarkSize[m_nUnit][nMarkNo].x = (LONG)dSizeX;
		g_clModelFinder.m_clPtMarkSize[m_nUnit][nMarkNo].y = (LONG)dSizeY;

		MmodInquire(g_clModelFinder.m_MilModModel[m_nUnit][nMarkNo], M_DEFAULT, M_REFERENCE_X, &dCenterX);
		MmodInquire(g_clModelFinder.m_MilModModel[m_nUnit][nMarkNo], M_DEFAULT, M_REFERENCE_Y, &dCenterY);

		g_clModelFinder.m_clPtMarkCenterPos.x = (LONG)dCenterX;
		g_clModelFinder.m_clPtMarkCenterPos.y = (LONG)dCenterY;
		 
		//g_clModelFinder.m_clPtMarkDispSize = 축소 마크 이미지 dlg 사이즈
		dZoomX = g_clModelFinder.m_clPtMarkDispSize.x / dZoomMarkWidth;// dZoomMarkWidth;// 656.0;// dSizeX - 0.36;		//0.3987 , dSizeX = 대략660 이어야된다
		dZoomY = g_clModelFinder.m_clPtMarkDispSize.y / dZoomMarkHeight;// dZoomMarkHeight;// 501.0;// dSizeY;
		

		//MdispZoom(g_clModelFinder.m_MilMarkDisplay[0], 1.0 * dZoomX, 1.0 * dZoomY);
		MimResize(g_clModelFinder.m_MilMarkImage[1], g_clModelFinder.m_MilMarkImage[0], dZoomX, dZoomY, M_DEFAULT);


		g_clModelFinder.DrawMarkOverlay(m_nUnit, nMarkNo);	//<----여기서 작은 마크에 Line Draw
	}

	m_nMarkNo = nMarkNo;

	g_clTaskWork[m_nUnit].m_ManualMarkIndex = m_nMarkNo;
	this->ShowMarkNo();
#endif
}

//-----------------------------------------------------------------------------
//
//	마크번호 표시
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::ShowMarkNo()
{
	TCHAR szTemp[SIZE_OF_1K]; 

	switch (m_nMarkNo)
	{
	case SENSOR_ALIGN_MARK:
		_stprintf_s(szTemp, SIZE_OF_1K, _T("%s"), MARK_ALIGN_NAME[SENSOR_ALIGN_MARK]);
		break;
	default:
		_stprintf_s(szTemp, SIZE_OF_1K, _T("Mark Empty"));
		break;

	}
	//_stprintf_s(szTemp, SIZE_OF_100BYTE, _T("%d / %d"), m_nMarkNo + 1, MAX_MARK_COUNT);
	m_clColorStaticMarkNo.SetWindowText(szTemp); 
}

//-----------------------------------------------------------------------------
//
//	마크 등록
//
//-----------------------------------------------------------------------------
bool CCcdMarkViewDlg::RegisterMark(double dSizeX, double dSizeY, double dCenterX, double dCenterY)
{
#ifdef ON_LINE_MIL
	TCHAR szLog[SIZE_OF_1K];
	CRect clRectMarkPos;
	int nTempNo = m_nMarkNo;// 999;
	int i = 0;

	if (dSizeX <= 5 || dSizeY <= 5)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("MARK SIZE가 최소 MARK Size보다 작습니다."));
		AddLog(szLog, 1, m_nUnit);

		return false;
	}
	if (dSizeX >= MAX_MARK_SIZE_X || dSizeY >= MAX_MARK_SIZE_Y)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("MARK SIZE가 최대 MARK Size보다 큽니다."));
		AddLog(szLog, 1, m_nUnit);

		return false;
	}

	/*for (i = 0; i < MAX_MARK_COUNT; i++)
	{
		if (g_clModelFinder.m_bMarkState[m_nUnit][i] == false)
		{
			nTempNo = i;
			break;
		}
	}

	if (nTempNo == 999)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("등록할 빈 영역이 없습니다. MARK 삭제 후 등록하세요"));
		AddLog(szLog, 1, m_nUnit);

		return false;
	}*/

	g_clModelFinder.m_clPtMarkSize[m_nUnit][m_nMarkNo].x = (LONG)dSizeX;	//마크사이즈 Drag Width
	g_clModelFinder.m_clPtMarkSize[m_nUnit][m_nMarkNo].y = (LONG)dSizeY;	//마크사이즈 Drag Height

	g_clModelFinder.m_clPtMarkCenterPos.x = (LONG)dCenterX;
	g_clModelFinder.m_clPtMarkCenterPos.y = (LONG)dCenterY;

	clRectMarkPos.left = (LONG)(dCenterX - dSizeX / 2);//실제 좌표
	clRectMarkPos.top = (LONG)(dCenterY - dSizeY / 2);

	clRectMarkPos.right = (LONG)(clRectMarkPos.left + dSizeX);
	clRectMarkPos.bottom = (LONG)(clRectMarkPos.top + dSizeY);

	g_clModelFinder.m_clPtMarkStartPos.x = clRectMarkPos.left;
	g_clModelFinder.m_clPtMarkStartPos.y = clRectMarkPos.top;

	if ((clRectMarkPos.left < 0) || (clRectMarkPos.top < 0) ||
		(clRectMarkPos.right > g_clModelData[m_nUnit].m_nWidth) || (clRectMarkPos.bottom > g_clModelData[m_nUnit].m_nHeight))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("MARK 영역 설정이 맞지 않습니다."));
		AddLog(szLog, 1, m_nUnit);

		return false;
	}

	m_nMarkNo = nTempNo;
	///this->DisplayMarkView(m_nUnit, m_nMarkNo);
	////this->ShowMarkNo();

	if (g_clModelFinder.RegistMark(m_nUnit, m_nMarkNo) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[FAIL] 마크 등록 실패"));
		AddLog(szLog, 1, m_nUnit);
		return false;
	}
	m_clMaskViewDlg.InitMaskViewDlg(m_nUnit, m_nMarkNo , g_clModelFinder.m_clPtMarkSize[m_nUnit][m_nMarkNo].x , g_clModelFinder.m_clPtMarkSize[m_nUnit][m_nMarkNo].y);
	m_clMaskViewDlg.ShowWindow(SW_SHOW);
	//this->DisplayMarkView(m_nUnit, m_nMarkNo);
	//this->ShowMarkNo();
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	버튼 : ◀◀◀
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewPrevious()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nMarkNo <= 0)
	{
		//g_ShowMsgPopup(_T("확인"), _T("첫 번째 마크입니다."), RGB_COLOR_RED);
		//return;
		m_nMarkNo = (MAX_MARK_COUNT - 1);
	}
	else
	{
		m_nMarkNo--;
	}

	
	this->DisplayMarkView(m_nUnit, m_nMarkNo, m_clMaskViewDlg.m_iMarkSetSizeX, m_clMaskViewDlg.m_iMarkSetSizeY);
}

//-----------------------------------------------------------------------------
//
//	버튼 : ▶▶▶
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nMarkNo >= (MAX_MARK_COUNT - 1))
	{
		/*g_ShowMsgPopup(_T("확인"), _T("마지막 마크입니다."), RGB_COLOR_RED);
		return;*/
		m_nMarkNo = 0;
	}
	else
	{
		m_nMarkNo++;
	}

	
	this->DisplayMarkView(m_nUnit, m_nMarkNo, m_clMaskViewDlg.m_iMarkSetSizeX, m_clMaskViewDlg.m_iMarkSetSizeY);
}

//-----------------------------------------------------------------------------
//
//	버튼 : INIT
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifdef ON_LINE_MIL
	g_clVision.ClearOverlay(m_nUnit);

	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_nDragType = MOUSE_DRAG;
	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_bDrag = true;
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : REGIST
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewRegist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
#ifdef ON_LINE_MIL
	CPoint	clPtSize;					//등록 할 Mark Size 저장변수
	CPoint	clPtCenter;			//등록 할 Mark 중심 저장변수
	CRect clRect;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	/*if (g_ShowMsgModal(_T("확인"), _T("마크를 등록 하시겠습니까?"), RGB_COLOR_RED) == false)
		return;*/

	_stprintf_s(szLog, SIZE_OF_1K, _T("[Mark] Regist Start"));
	AddLog(szLog, 0, m_nUnit);
	//-------------------
	//추가함
	//g_clModelFinder.DeleteMark(g_clSysData.m_szModelName, m_nUnit, m_nMarkNo);
	//g_clModelFinder.LoadMark(g_clSysData.m_szModelName);

	//// Mark 정렬
	//g_clModelFinder.ReSortMark(g_clSysData.m_szModelName, m_nUnit, m_nMarkNo);
	//this->DisplayMarkView(m_nUnit, m_nMarkNo);
	////

	clRect = g_pCarAABonderDlg->m_clVisionStaticCam[m_nUnit].GetRect();

	clPtSize.x = (LONG)(clRect.right - clRect.left);
	clPtSize.y = (LONG)(clRect.bottom - clRect.top);
	g_clModelFinder.m_clPtMarkSize[m_nUnit][m_nMarkNo] = clPtSize;

	clPtCenter.x =  (LONG)(clRect.left + (clPtSize.x / 2));
	clPtCenter.y = (LONG)(clRect.top + (clPtSize.y / 2));
	g_clModelFinder.m_clPtMarkCenterPos = clPtCenter;

	_stprintf_s(szLog, SIZE_OF_1K, _T("Mark Start X:%ld , Y:%ld"), clRect.left, clRect.top);
	AddLog(szLog, 0, m_nUnit);

	_stprintf_s(szLog, SIZE_OF_1K, _T("Mark Size Width:%ld , Height:%ld") , clPtSize.x , clPtSize.y);
	AddLog(szLog, 0, m_nUnit);

	if (this->RegisterMark(clPtSize.x, clPtSize.y, clPtCenter.x, clPtCenter.y) == false)
	{
		return;
	}
	//
	//g_clModelFinder.SaveMark(g_clSysData.m_szModelName, m_nUnit, m_nMarkNo);

	//g_clModelFinder.SettingFindMark(m_nUnit, m_nMarkNo);

	g_pCarAABonderDlg->m_clVisionStaticCam[m_nUnit].m_bDrag = false;
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : DELETE
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	if (g_clModelFinder.m_bMarkState[m_nUnit][m_nMarkNo] == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("등록된 마크가 존재하지 않습니다."));
		AddLog(szLog, 1, m_nUnit);

		return;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("MARK-%d번을 삭제하시겠습니까?"), m_nMarkNo + 1);
	if (g_ShowMsgModal(_T("확인"), szLog, RGB_COLOR_RED) == false)
		return;

	g_clModelFinder.DeleteMark(g_clSysData.m_szModelName, m_nUnit, m_nMarkNo);
	g_clModelFinder.LoadMark(g_clSysData.m_szModelName);

	// Mark 정렬
	g_clModelFinder.ReSortMark(g_clSysData.m_szModelName, m_nUnit, m_nMarkNo);
	this->DisplayMarkView(m_nUnit, m_nMarkNo, m_clMaskViewDlg.m_iMarkSetSizeX, m_clMaskViewDlg.m_iMarkSetSizeY);

	_stprintf_s(szLog, SIZE_OF_1K, _T("선택된 마크를 삭제하였습니다.[%s][MARK-%d]"), g_clSysData.m_szModelName, m_nMarkNo + 1);
	AddLog(szLog, 0, m_nUnit);

	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_bDrag = false;
}

//-----------------------------------------------------------------------------
//
//	버튼 : ROI SAVE
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewRoiSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPoint clPtSize;
	CPoint clPtCenter;
	CRect clRect;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	if (g_ShowMsgModal(_T("확인"), _T("FIND 마크 ROI영역을 등록하시겠습니까?"), RGB_COLOR_RED) == false)
		return;

	clRect = g_pCarAABonderDlg->m_clVisionStaticCam[m_nUnit].GetRect();
	clPtSize.x = (LONG)(clRect.right - clRect.left);
	clPtSize.y = (LONG)(clRect.bottom - clRect.top);

	//g_clModelFinder.m_clPtMarkSize = clPtSize;

	clPtCenter.x = (LONG)(clRect.left + (clPtSize.x / 2));
	clPtCenter.y = (LONG)(clRect.top + (clPtSize.y / 2));

	g_clModelFinder.m_clPtMarkCenterPos = clPtCenter;

	g_clMarkData[m_nUnit].m_clRectRoi[m_nMarkNo].left = (LONG)(clPtCenter.x - clPtSize.x / 2);
	g_clMarkData[m_nUnit].m_clRectRoi[m_nMarkNo].right = (LONG)(clPtCenter.x + clPtSize.x / 2);
	g_clMarkData[m_nUnit].m_clRectRoi[m_nMarkNo].top = (LONG)(clPtCenter.y - clPtSize.y / 2);
	g_clMarkData[m_nUnit].m_clRectRoi[m_nMarkNo].bottom = (LONG)(clPtCenter.y + clPtSize.y / 2);
	g_clMarkData[m_nUnit].SaveData(g_clSysData.m_szModelName);

	g_pCarAABonderDlg->m_clVisionStaticCam[m_nUnit].m_bDrag = false;
}

//-----------------------------------------------------------------------------
//
//	버튼 : MASK VIEW
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewMask()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}
	double dSizeX = 0.0; 
	double dSizeY = 0.0;

	MmodInquire(g_clModelFinder.m_MilModModel[m_nUnit][m_nMarkNo], M_DEFAULT, M_ALLOC_SIZE_X, &dSizeX);		//<-----여기서왜 마크 사이즈를 바꾸지?
	MmodInquire(g_clModelFinder.m_MilModModel[m_nUnit][m_nMarkNo], M_DEFAULT, M_ALLOC_SIZE_Y, &dSizeY);

	m_clMaskViewDlg.InitMaskViewDlg(m_nUnit, m_nMarkNo , (int)dSizeX, (int)dSizeY);
	m_clMaskViewDlg.ShowWindow(SW_SHOW);
}

//-----------------------------------------------------------------------------
//
//	버튼 : MARK FIND
//
//-----------------------------------------------------------------------------
void CCcdMarkViewDlg::OnBnClickedButtonCcdMarkViewFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDMotor dmAlign;
	CDMPoint dpFind;
	bool bChk = false;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

	dmAlign.x = dmAlign.y = dmAlign.t = 0.0;
	dpFind.x = dpFind.y = 0.0;

	g_clVision.CalcSingleMarkAlign(m_nUnit, m_nMarkNo, 0, dmAlign, dpFind);

	g_pCarAABonderDlg->m_clManualDlg.ShowAlignValue(); 

	TCHAR szData[SIZE_OF_100BYTE];
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), dmAlign.x);
	g_pCarAABonderDlg->m_clManualDlg.m_clColorStaticAlignXVal.SetWindowText(szData); 
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), dmAlign.y);
	g_pCarAABonderDlg->m_clManualDlg.m_clColorStaticAlignYVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), dmAlign.t);
	g_pCarAABonderDlg->m_clManualDlg.m_clColorStaticAlignTHVal.SetWindowText(szData);



	if (g_clModelData[m_nUnit].m_nDryRunMode == 1)
	{
		g_clMesCommunication[m_nUnit].m_dGrrAlignPos[0] = dmAlign.x;
		g_clMesCommunication[m_nUnit].m_dGrrAlignPos[1] = dmAlign.y;
		g_clMesCommunication[m_nUnit].m_dGrrAlignPos[2] = dmAlign.t;

		g_clMesCommunication[m_nUnit].g_Grr____Align(0);
	}

}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CCcdMarkViewDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



void CCcdMarkViewDlg::OnBnClickedButtonCcdBmpSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가합니다."), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_MIL
	CString sPath = _T("");
	CString sTemp = _T("");

	CFileDialog* pDlg = new CFileDialog(FALSE, _T("*.bmp|*.BMP|"), _T("IMAGE"), OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("Image Files (*.bmp)|*.bmp|"));
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPath = pDlg->GetPathName();
			sTemp = sPath.Right(4);
			if (sTemp.CompareNoCase(_T(".bmp")) != 0)
				sPath += _T(".bmp");

			MbufExport(sPath, M_BMP, g_clVision.m_MilGrabImage[0][0]);
		}
		delete pDlg;
	}
#endif
}
