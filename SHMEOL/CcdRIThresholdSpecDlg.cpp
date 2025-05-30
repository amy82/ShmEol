// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdRIThresholdSpecDlg.h"
#include "afxdialogex.h"


// CCcdRIThresholdSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdRIThresholdSpecDlg, CDialogEx)

CCcdRIThresholdSpecDlg::CCcdRIThresholdSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdRIThresholdSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
	mLensGridRow = 17;	//17
	mLensGridCol = 13;	//13
	mLensCurrentCol = 0; //0 ~ 12
}

CCcdRIThresholdSpecDlg::~CCcdRIThresholdSpecDlg()
{
}

void CCcdRIThresholdSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_TOP_BAR, m_clColorStaticTopBar);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT, m_clColorStaticCenterSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT, m_clColorStaticCornerSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, m_clColorStaticCornerSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT, m_clColorStaticCornerSfrDeviationLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, m_clColorStaticCornerSfrDeviationLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY, m_clColorStaticOCXY);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, m_clColorStaticOCXYVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH, m_clColorStaticOCTh);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, m_clColorStaticOCThVal);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_CLOSE, m_clColorButtonClose);


	DDX_Control(pDX, IDC_BUTTON_CCD_LENS_SHADING_PREV, m_clColorButtonLensShadingPrev);
	DDX_Control(pDX, IDC_BUTTON_CCD_LENS_SHADING_NEXT, m_clColorButtonLensShadingNext);
	

	//
	DDX_Control(pDX, IDC_STATIC_CCD_LENS_SHADING_INDEX_VAL, m_clColorStaticLensShadingIndexVal);
}


BEGIN_MESSAGE_MAP(CCcdRIThresholdSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI1_SPEC_GRID_SPEC, &CCcdRIThresholdSpecDlg::OnNMDblClickedRi1Spec)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI2_SPEC_GRID_SPEC, &CCcdRIThresholdSpecDlg::OnNMDblClickedRi2Spec)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI3_SPEC_GRID_SPEC, &CCcdRIThresholdSpecDlg::OnNMDblClickedRi3Spec)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI4_SPEC_GRID_SPEC, &CCcdRIThresholdSpecDlg::OnNMDblClickedRi4Spec)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI5_SPEC_GRID_SPEC, &CCcdRIThresholdSpecDlg::OnNMDblClickedRi5Spec)

	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_LENS_SHADING_INDEX_VAL, &CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
	ON_BN_CLICKED(IDC_BUTTON_CCD_LENS_SHADING_PREV, &CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdLensShadingPrev)
	ON_BN_CLICKED(IDC_BUTTON_CCD_LENS_SHADING_NEXT, &CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdLensShadingNext)
END_MESSAGE_MAP()


// CCcdRIThresholdSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnPaint()
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
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CCcdRIThresholdSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

    RiThresholdGridCount = 0;

	// 그리드 초기화
    this->InitRiThresholdGridCtrl1();
   /* this->InitRiThresholdGridCtrl2();
    this->InitRiThresholdGridCtrl3();
    this->InitRiThresholdGridCtrl4();
    this->InitRiThresholdGridCtrl5();*/


	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	//m_clColorStaticTopBar.SetBkColor(RGB_COLOR_BLACK);
	//m_clColorStaticTopBar.SetTextColor(RGB_COLOR_WHITE);
	
	m_clColorStaticCenterSfrLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCenterSfrLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCenterSfrLimit.SetFont(&m_clFontSmall);

	m_clColorStaticLensShadingIndexVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLensShadingIndexVal.SetFont(&m_clFontMid);

	m_clColorStaticCornerSfrLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCornerSfrLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCornerSfrLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticCornerSfrDeviationLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCornerSfrDeviationLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrDeviationLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCornerSfrDeviationLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrDeviationLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticOCXY.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOCXY.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOCXY.SetFont(&m_clFontSmall);

	m_clColorStaticOCXYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCXYVal.SetFont(&m_clFontMid);

	m_clColorStaticOCTh.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOCTh.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOCTh.SetFont(&m_clFontSmall);

	m_clColorStaticOCThVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCThVal.SetFont(&m_clFontMid);


	CString sData;
	sData.Format(_T("%d"), mLensCurrentCol + 1);
	m_clColorStaticLensShadingIndexVal.SetWindowTextA(sData);
	m_clColorStaticLensShadingIndexVal.Invalidate();
	sData.Empty();
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::InitRiThresholdGridCtrl1()
{

    TCHAR* pszCol[] = { _T("RI"), _T("LEFT"), _T("TOP"), _T("WIDTH"), _T("HEIGHT") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI1_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
	int SpecCol = RIThresholdMaxCount + 1;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 60;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec1.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec1.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec1.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec1.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec1.SetReference_Setting();
    m_clGridRIThresholdSpec1.EnableSelection(FALSE);
    m_clGridRIThresholdSpec1.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec1.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec1.SetFixedRowCount(1);
    m_clGridRIThresholdSpec1.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i +1);
        m_clGridRIThresholdSpec1.SetItemText(0, i+1, sData);
    }
   

    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec1.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec1.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec1.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec1.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec1.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}

void CCcdRIThresholdSpecDlg::InitRiThresholdGridCtrl2()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI2_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec2.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec2.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec2.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec2.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec2.SetReference_Setting();
    m_clGridRIThresholdSpec2.EnableSelection(FALSE);
    m_clGridRIThresholdSpec2.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec2.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec2.SetFixedRowCount(1);
    m_clGridRIThresholdSpec2.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i+21);
        m_clGridRIThresholdSpec2.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec2.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec2.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec2.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec2.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec2.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdRIThresholdSpecDlg::InitRiThresholdGridCtrl3()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI3_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec3.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec3.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec3.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec3.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec3.SetReference_Setting();
    m_clGridRIThresholdSpec3.EnableSelection(FALSE);
    m_clGridRIThresholdSpec3.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec3.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec3.SetFixedRowCount(1);
    m_clGridRIThresholdSpec3.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i+41);
        m_clGridRIThresholdSpec3.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec3.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec3.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec3.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec3.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec3.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdRIThresholdSpecDlg::InitRiThresholdGridCtrl4()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI4_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec4.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec4.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec4.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec4.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec4.SetReference_Setting();
    m_clGridRIThresholdSpec4.EnableSelection(FALSE);
    m_clGridRIThresholdSpec4.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec4.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec4.SetFixedRowCount(1);
    m_clGridRIThresholdSpec4.SetFixedColumnCount(1);
	//
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i + 61);
        m_clGridRIThresholdSpec4.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec4.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec4.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec4.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec4.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec4.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdRIThresholdSpecDlg::InitRiThresholdGridCtrl5()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI5_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec5.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec5.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec5.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec5.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec5.SetReference_Setting();
    m_clGridRIThresholdSpec5.EnableSelection(FALSE);
    m_clGridRIThresholdSpec5.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec5.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec5.SetFixedRowCount(1);
    m_clGridRIThresholdSpec5.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i + 81);
        m_clGridRIThresholdSpec5.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec5.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec5.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec5.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec5.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec5.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
        this->ShowRIThresholdSpec();
	}
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::ShowRIThresholdSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	CString sData;
    int i = 0;
    int j = 0;

    int _x = 0;
    int _y = 0;
    RiThresholdGridCount = 0;
	int minit = mLensGridRow * mLensCurrentCol;
	int mMax = mLensGridRow * (mLensCurrentCol + 1);
	int mindex = 0;

	for (i = 0; i < mLensGridRow; i++)
	{
		sData.Format(_T("ROI%d"), minit+i + 1);
		m_clGridRIThresholdSpec1.SetItemText(0, i + 1, sData);
	}
	sData.Empty();
	for (i = minit; i < mMax; i++)// for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        m_clGridRIThresholdSpec1.SetItemText(1, mindex + 1, g_clModelData[m_nUnit].m_LensShadingRoi[i].left);
        m_clGridRIThresholdSpec1.SetItemText(2, mindex + 1, g_clModelData[m_nUnit].m_LensShadingRoi[i].top);
        m_clGridRIThresholdSpec1.SetItemText(3, mindex + 1, g_clModelData[m_nUnit].m_LensShadingRoi[i].right);
        m_clGridRIThresholdSpec1.SetItemText(4, mindex + 1, g_clModelData[m_nUnit].m_LensShadingRoi[i].bottom);
		mindex++;
    }

	m_clGridRIThresholdSpec1.Invalidate();




}

//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::GetRIThresholdSpec()
{
	CString sData = _T("");
	int i;
    RiThresholdGridCount = 0;

	int minit = mLensGridRow * mLensCurrentCol;
	int mMax = mLensGridRow * (mLensCurrentCol + 1);
	int mindex = 0;

	for (i = minit; i < mMax; i++)// for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        sData = m_clGridRIThresholdSpec1.GetItemText(1, mindex + 1);
		g_clModelData[m_nUnit].m_LensShadingRoi[i].left = _ttoi((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec1.GetItemText(2, mindex + 1);
		g_clModelData[m_nUnit].m_LensShadingRoi[i].top = _ttoi((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec1.GetItemText(3, mindex + 1);
		g_clModelData[m_nUnit].m_LensShadingRoi[i].right =_ttoi((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec1.GetItemText(4, mindex + 1);
		g_clModelData[m_nUnit].m_LensShadingRoi[i].bottom =_ttoi((TCHAR*)(LPCTSTR)sData);
		mindex++;
    }

	sData.Empty();


}

//-----------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticLensShadingIndexVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticLensShadingIndexVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	CORNER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCornerSfrLimitVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCornerSfrLimitVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	코너부 SFR 편차 LIMIT
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCornerSfrDeviationLimitVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCornerSfrDeviationLimitVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	광축검사 XY
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticOCXYVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOCXYVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	광축검사 TH
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticOCThVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOCThVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("일시 정지 중 사용불가합니다."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_ShowMsgModal(_T("확인"), _T("RI THRESHOLD SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;


	this->GetRIThresholdSpec();

	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();

	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] RI THRESHOLD SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnNMDblClickedRi1Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridRIThresholdSpec1.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
                m_clGridRIThresholdSpec1.SetItemText(nRow, nCol, sData);

                m_clGridRIThresholdSpec1.Invalidate();
			}

			delete pDlg;
		}
	}
}
//
void CCcdRIThresholdSpecDlg::OnNMDblClickedRi2Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridRIThresholdSpec2.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
                m_clGridRIThresholdSpec2.SetItemText(nRow, nCol, sData);

                m_clGridRIThresholdSpec2.Invalidate();
            }

            delete pDlg;
        }
    }
}
//
void CCcdRIThresholdSpecDlg::OnNMDblClickedRi3Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridRIThresholdSpec3.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
                m_clGridRIThresholdSpec3.SetItemText(nRow, nCol, sData);

                m_clGridRIThresholdSpec3.Invalidate();
            }

            delete pDlg;
        }
    }
}
//
void CCcdRIThresholdSpecDlg::OnNMDblClickedRi4Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridRIThresholdSpec4.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
                m_clGridRIThresholdSpec4.SetItemText(nRow, nCol, sData);

                m_clGridRIThresholdSpec4.Invalidate();
            }

            delete pDlg;
        }
    }
}
//
void CCcdRIThresholdSpecDlg::OnNMDblClickedRi5Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridRIThresholdSpec5.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
                m_clGridRIThresholdSpec5.SetItemText(nRow, nCol, sData);

                m_clGridRIThresholdSpec5.Invalidate();
            }

            delete pDlg;
        }
    }
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdRIThresholdSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CCcdRIThresholdSpecDlg::PreTranslateMessage(MSG* pMsg)
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

void CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdLensShadingPrev()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mLensCurrentCol < 1)
	{
		mLensCurrentCol = mLensGridCol - 1;
	}
	else
	{
		mLensCurrentCol--;
	}
	CString sData;
	sData.Format(_T("%d"), mLensCurrentCol + 1);
	m_clColorStaticLensShadingIndexVal.SetWindowTextA(sData);
	m_clColorStaticLensShadingIndexVal.Invalidate();
	sData.Empty();
	this->ShowRIThresholdSpec();
}


void CCcdRIThresholdSpecDlg::OnBnClickedButtonCcdLensShadingNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mLensCurrentCol >= mLensGridCol - 1)
	{
		mLensCurrentCol = 0;
	}
	else
	{
		mLensCurrentCol++;
	}
	CString sData;
	sData.Format(_T("%d"), mLensCurrentCol + 1);
	m_clColorStaticLensShadingIndexVal.SetWindowTextA(sData);
	m_clColorStaticLensShadingIndexVal.Invalidate();
	sData.Empty();
	this->ShowRIThresholdSpec();
}
