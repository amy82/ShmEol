// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdColorReproductionSpecDlg.h"
#include "afxdialogex.h"


// CCcdColorReproductionSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdColorReproductionSpecDlg, CDialogEx)

CCcdColorReproductionSpecDlg::CCcdColorReproductionSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdColorReproductionSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
	m_brCheck.CreateSolidBrush(RGB(45, 45, 45));
}

CCcdColorReproductionSpecDlg::~CCcdColorReproductionSpecDlg()
{
}

void CCcdColorReproductionSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_CCD_ROTATION, m_clColorStaticHRotation);
	DDX_Control(pDX, IDC_STATIC_CCD_ROTATION_VAL, m_clColorStaticHRotationVal);
	
	DDX_Control(pDX, IDC_STATIC_CCD_COLOR_BLACKLEVEL_VAL, m_clColorStaticColorBlackLevelVal);

	DDX_Control(pDX, IDC_CCD_COLOR_COMBO_DATAFORMAT, m_CcdColorComboDataFormat);
	DDX_Control(pDX, IDC_CCD_COLOR_COMBO_OUTMODE, m_CcdColorComboOutMode);
	DDX_Control(pDX, IDC_CCD_COLOR_COMBO_SENSORTYPE, m_CcdColorComboSensorType);
	DDX_Control(pDX, IDC_CCD_COLOR_COMBO_DEMOSAIC, m_CcdColorComboDemosaic);

	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_SPEC_CLOSE, m_clColorButtonClose);

	DDX_Control(pDX, IDC_STATIC_CCD_COLOR_DATAFORMAT,		m_clColorStaticCcdColorDataformat);
	DDX_Control(pDX, IDC_STATIC_CCD_COLOR_OUTMODE,			m_clColorStaticCcdColorOutmode);
	DDX_Control(pDX, IDC_STATIC_CCD_COLOR_SENSORTYPE,		m_clColorStaticCcdColorSensortype);
	DDX_Control(pDX, IDC_STATIC_CCD_COLOR_DEMOSAIC,			m_clColorStaticCcdColorDemosaic);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_COLOR_BLACKLEVEL,	m_clColorStaticCcdColorBlacklevel);
}

BEGIN_MESSAGE_MAP(CCcdColorReproductionSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_COLOR_REPRODUCTION_GRID_SPEC, &CCcdColorReproductionSpecDlg::OnNMDblClickedColorReproductSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_SPEC_SAVE, &CCcdColorReproductionSpecDlg::OnBnClickedButtonCcdColorReproductionSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_SPEC_CLOSE, &CCcdColorReproductionSpecDlg::OnBnClickedButtonCcdColorReproductionSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_ROTATION_VAL, &CCcdColorReproductionSpecDlg::OnStnClickedStaticCcdRotationVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_COLOR_BLACKLEVEL_VAL, &CCcdColorReproductionSpecDlg::OnStnClickedStaticCcdColorBlacklevelVal)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCcdColorReproductionSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::OnPaint()
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
BOOL CCcdColorReproductionSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
	this->InitChartGridCtrl();
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticHRotation.SetBkColor(RGB_DLG_BG);
	m_clColorStaticHRotation.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticHRotation.SetFont(&m_clFontSmall);
	
	m_clColorStaticHRotationVal.SetBkColor(RGB_COLOR_WHITE).SetFont(&m_clFontMid);

	m_clColorStaticColorBlackLevelVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticColorBlackLevelVal.SetFont(&m_clFontMid);

	m_clColorStaticCcdColorDataformat.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdColorDataformat.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdColorDataformat.SetFont(&m_clFontSmall);

	m_clColorStaticCcdColorOutmode.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdColorOutmode.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdColorOutmode.SetFont(&m_clFontSmall);

	m_clColorStaticCcdColorSensortype.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdColorSensortype.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdColorSensortype.SetFont(&m_clFontSmall);

	m_clColorStaticCcdColorDemosaic.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdColorDemosaic.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdColorDemosaic.SetFont(&m_clFontSmall);

	m_clColorStaticCcdColorBlacklevel.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdColorBlacklevel.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdColorBlacklevel.SetFont(&m_clFontSmall);

	SetWindowTheme(GetDlgItem(IDC_CHECK_CCD_COLOR_8BITUSE)->m_hWnd, L"", L"");

	m_CcdColorComboDataFormat.ResetContent();
	m_CcdColorComboOutMode.ResetContent();
	m_CcdColorComboSensorType.ResetContent();
	m_CcdColorComboDemosaic.ResetContent();
	//
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_YUV"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_8BIT"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_10BIT"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_12BIT"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_BE"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_HDR"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_DECOMP"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_24BIT"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT_BE"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT_BE"));
	m_CcdColorComboDataFormat.AddString(_T("DATAFORMAT_RGB"));		//rgb = 100
																	//
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_BGGR"));	//1
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_RGGB"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_GBRG"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_GRBG"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_BLACKWHITE"));	//1
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_YUV422_YCbYCr"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_YUV422_YCrYCb"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_YUV422_CbYCrY"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_YUV422_CrYCbY"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_RGB_BGR"));		//1
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_RGB_RGB"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_BNGR"));	//1
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_RGNB"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_NBRG"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_GRBN"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_BGGN"));	//1
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_RGGN"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_GBNG"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_GRNG"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_NGGR"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_NGGB"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_GNRG"));
	m_CcdColorComboOutMode.AddString(_T("OUTMODE_BAYER_GNBG"));
	//
	m_CcdColorComboSensorType.AddString(_T("SENSORTYPE_RGGB"));
	m_CcdColorComboSensorType.AddString(_T("SENSORTYPE_RCCC"));
	m_CcdColorComboSensorType.AddString(_T("SENSORTYPE_RCCB"));
	m_CcdColorComboSensorType.AddString(_T("SENSORTYPE_CCCC"));
	m_CcdColorComboSensorType.AddString(_T("SENSORTYPE_RBCC"));
	m_CcdColorComboSensorType.AddString(_T("SENSORTYPE_OTHER"));
	m_CcdColorComboSensorType.AddString(_T("SENSORTYPE_RGBIR2"));
	//

	m_CcdColorComboDemosaic.AddString(_T("DEMOSAIC_NONE"));
	m_CcdColorComboDemosaic.AddString(_T("GRADIENT"));
	m_CcdColorComboDemosaic.AddString(_T("BL33"));
	m_CcdColorComboDemosaic.AddString(_T("OPENCV_VNG"));
	m_CcdColorComboDemosaic.AddString(_T("VNG"));
	m_CcdColorComboDemosaic.AddString(_T("GR_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("GB_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("GBTF"));
	m_CcdColorComboDemosaic.AddString(_T("BLLC"));
	m_CcdColorComboDemosaic.AddString(_T("RESIDUAL"));
	m_CcdColorComboDemosaic.AddString(_T("BAYER_Y"));
	m_CcdColorComboDemosaic.AddString(_T("GRADIENT_RESIDUAL"));
	m_CcdColorComboDemosaic.AddString(_T("GBTF_RESIDUAL"));
	m_CcdColorComboDemosaic.AddString(_T("RESIDUAL_RESIDUAL"));
	m_CcdColorComboDemosaic.AddString(_T("BL33_RESIDUAL"));
	m_CcdColorComboDemosaic.AddString(_T("IR_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("GRADIENT_G_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("GBTF_G_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("RESIDUAL_G_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("BL33_G_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("GRADIENT_IR_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("GBTF_IR_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("RESIDUAL_IR_ONLY"));
	m_CcdColorComboDemosaic.AddString(_T("BL33_IR_ONLY"));


	m_CcdColorComboDataFormat.SetCurSel(0);
	m_CcdColorComboOutMode.SetCurSel(0);
	m_CcdColorComboSensorType.SetCurSel(0);
	m_CcdColorComboDemosaic.SetCurSel(0);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::InitChartGridCtrl()
{
	/*TCHAR* pszRow[] = { _T("") ,
		_T("dRealGapX"), _T("dRealGapY"), _T("nFiducialMarkType"),
		_T("dModuleChartDistance"), _T("nDistortionAlrotithmType") 
	};*/
	
	TCHAR* pszCol[] = { _T("Chart"), _T("spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_COLOR_REPRODUCTION_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = ColorReproductionMaxCount;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 180;
	int gridWidth2 = 110;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridColorReproductionSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridColorReproductionSpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridColorReproductionSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridColorReproductionSpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridColorReproductionSpec.SetReference_Setting();
	m_clGridColorReproductionSpec.EnableSelection(FALSE);
	m_clGridColorReproductionSpec.SetRowCount(SpecRow);
	m_clGridColorReproductionSpec.SetColumnCount(SpecCol);
	m_clGridColorReproductionSpec.SetFixedRowCount(1);
	m_clGridColorReproductionSpec.SetFixedColumnCount(1);

	m_clGridColorReproductionSpec.SetItemText(1, 0, _T("Threshold1"));
	m_clGridColorReproductionSpec.SetItemText(2, 0, _T("Threshold2"));
	m_clGridColorReproductionSpec.SetItemText(3, 0, _T("Threshold3"));
	m_clGridColorReproductionSpec.SetItemText(4, 0, _T("Threshold4"));

	m_clGridColorReproductionSpec.SetItemText(5, 0, _T("ColorLab1_L"));
	m_clGridColorReproductionSpec.SetItemText(6, 0, _T("ColorLab1_a"));
	m_clGridColorReproductionSpec.SetItemText(7, 0, _T("ColorLab1_b"));
	m_clGridColorReproductionSpec.SetItemText(8, 0, _T("ColorLab2_L"));
	m_clGridColorReproductionSpec.SetItemText(9, 0, _T("ColorLab2_a"));
	m_clGridColorReproductionSpec.SetItemText(10, 0, _T("ColorLab2_b"));
	m_clGridColorReproductionSpec.SetItemText(11, 0, _T("ColorLab3_L"));
	m_clGridColorReproductionSpec.SetItemText(12, 0, _T("ColorLab3_a"));
	m_clGridColorReproductionSpec.SetItemText(13, 0, _T("ColorLab3_b"));
	m_clGridColorReproductionSpec.SetItemText(14, 0, _T("ColorLab4_L"));
	m_clGridColorReproductionSpec.SetItemText(15, 0, _T("ColorLab4_a"));
	m_clGridColorReproductionSpec.SetItemText(16, 0, _T("ColorLab4_b"));

	m_clGridColorReproductionSpec.SetItemText(17, 0, _T("Roi1_Left"));
	m_clGridColorReproductionSpec.SetItemText(18, 0, _T("Roi1_Top"));
	m_clGridColorReproductionSpec.SetItemText(19, 0, _T("Roi1_right"));
	m_clGridColorReproductionSpec.SetItemText(20, 0, _T("Roi1_Bottom"));
	m_clGridColorReproductionSpec.SetItemText(21, 0, _T("Roi2_Left"));
	m_clGridColorReproductionSpec.SetItemText(22, 0, _T("Roi2_Top"));
	m_clGridColorReproductionSpec.SetItemText(23, 0, _T("Roi2_right"));
	m_clGridColorReproductionSpec.SetItemText(24, 0, _T("Roi2_Bottom"));
	m_clGridColorReproductionSpec.SetItemText(25, 0, _T("Roi3_Left"));
	m_clGridColorReproductionSpec.SetItemText(26, 0, _T("Roi3_Top"));
	m_clGridColorReproductionSpec.SetItemText(27, 0, _T("Roi3_right"));
	m_clGridColorReproductionSpec.SetItemText(28, 0, _T("Roi3_Bottom"));
	m_clGridColorReproductionSpec.SetItemText(29, 0, _T("Roi4_Left"));
	m_clGridColorReproductionSpec.SetItemText(30, 0, _T("Roi4_Top"));
	m_clGridColorReproductionSpec.SetItemText(31, 0, _T("Roi4_right"));
	m_clGridColorReproductionSpec.SetItemText(32, 0, _T("Roi4_Bottom"));

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridColorReproductionSpec.SetRowHeight(i, gridHeight);
       // m_clGridChartSpec.SetItemText(i, 0, pszRow[i]);
		
		//

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridColorReproductionSpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridColorReproductionSpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridColorReproductionSpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridColorReproductionSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowColorReproductionSpec();
	}
}

//-----------------------------------------------------------------------------
//
//	SATURATION SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::ShowColorReproductionSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	CButton* pButton;
	int i = 0;
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dChartRotation);
	m_clColorStaticHRotationVal.SetWindowText(szData);
	
   
	for (i = 0; i < ColorReproductionMaxCount -1; i++)
	{
		m_clGridColorReproductionSpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_ColorReproductionSpec[i],6);
	}
	
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_COLOR_8BITUSE);
	if (g_clModelData[m_nUnit].m_nColor8BitUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_dColorBlackLevel);
	m_clColorStaticColorBlackLevelVal.SetWindowText(szData);

	m_CcdColorComboDataFormat.SetCurSel(g_clModelData[m_nUnit].colorParameter[0]);
	m_CcdColorComboOutMode.SetCurSel(g_clModelData[m_nUnit].colorParameter[1]);
	m_CcdColorComboSensorType.SetCurSel(g_clModelData[m_nUnit].colorParameter[2]);
	m_CcdColorComboDemosaic.SetCurSel(g_clModelData[m_nUnit].colorParameter[3]);

	m_clGridColorReproductionSpec.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::OnBnClickedButtonCcdColorReproductionSpecSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("COLOR REPRODUCTION SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	this->GetColorReproductionSpec();

	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
    g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] COLOR REPRODUCTION SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::GetColorReproductionSpec()
{
	CString sData = _T("");
	CButton* pButton;
	int i;

	for (i = 0; i < ColorReproductionMaxCount -1; i++)
	{
		sData = m_clGridColorReproductionSpec.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_ColorReproductionSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}
	m_clColorStaticHRotationVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dChartRotation = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_COLOR_BLACKLEVEL_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dColorBlackLevel = _ttoi((TCHAR*)(LPCTSTR)sData);

	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_COLOR_8BITUSE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nColor8BitUse = 1;
	else
		g_clModelData[m_nUnit].m_nColor8BitUse = 0;

	g_clModelData[m_nUnit].colorParameter[0] = m_CcdColorComboDataFormat.GetCurSel();
	g_clModelData[m_nUnit].colorParameter[1] = m_CcdColorComboOutMode.GetCurSel();
	g_clModelData[m_nUnit].colorParameter[2] = m_CcdColorComboSensorType.GetCurSel();
	g_clModelData[m_nUnit].colorParameter[3] = m_CcdColorComboDemosaic.GetCurSel();

	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(g_clModelData[m_nUnit].colorParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(g_clModelData[m_nUnit].colorParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(g_clModelData[m_nUnit].colorParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(g_clModelData[m_nUnit].colorParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.nBlackLevel = g_clModelData[m_nUnit].m_dColorBlackLevel;

	g_clSysData.sDSave();
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::OnBnClickedButtonCcdColorReproductionSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdColorReproductionSpecDlg::OnNMDblClickedColorReproductSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridColorReproductionSpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.06lf"), pDlg->GetReturnVal());
				m_clGridColorReproductionSpec.SetItemText(nRow, nCol, sData);

				m_clGridColorReproductionSpec.Invalidate();
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
void CCcdColorReproductionSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdColorReproductionSpecDlg::PreTranslateMessage(MSG* pMsg)
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

void CCcdColorReproductionSpecDlg::OnStnClickedStaticCcdRotationVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticHRotationVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticHRotationVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}


void CCcdColorReproductionSpecDlg::OnStnClickedStaticCcdColorBlacklevelVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticColorBlackLevelVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticColorBlackLevelVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}


HBRUSH CCcdColorReproductionSpecDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	if (pWnd->GetDlgCtrlID() == IDC_CHECK_CCD_COLOR_8BITUSE
		)
	{
		pDC->SetTextColor(RGB_COLOR_WHITE);
		pDC->SetBkColor(RGB(100, 100, 100));
		pDC->SetBkMode(TRANSPARENT);

		return (HBRUSH)m_brCheck;
		//return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
