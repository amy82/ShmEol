// LightDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "LightDlg.h"
#include "afxdialogex.h"

// CLightDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLightDlg, CDialogEx)

CLightDlg::CLightDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLightDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
	oc_CHANNEL = 0;
	m_CurrentTopChartIndex = LIGHT_CHART_CH_1;

	m_CurrentLeftChartIndex = LEFT_CHART_CH_1;
	m_CurrentRightChartIndex = RIGHT_CHART_CH_1;

	//m_CurrentSideChartIndex = LIGHT_CHART_LEFT_CH1;
	m_CurrentBackduIndex = LIGHT_OC_WHITE_CH1;
	m_CurrentOcIcIndex = LIGHT_OC_IR_CH1;
	m_CurrentAlignIndex = LIGHT_DATA_ALIGN_SENSOR;


}

CLightDlg::~CLightDlg()
{
}

void CLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LIGHT_TITLE, m_clColorStaticTitle);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CHART, m_clColorStaticChart[0]);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CHART2, m_clColorStaticChart[1]);
	DDX_Control(pDX, IDC_STATIC_LIGHT_TOP_CHART_VALUE, m_clColorStaticTopChartVal);
    DDX_Control(pDX, IDC_STATIC_LIGHT_LEFT_CHART_VALUE, m_clColorStaticLeftChartVal);
    DDX_Control(pDX, IDC_STATIC_LIGHT_RIGHT_CHART_VALUE, m_clColorStaticRightChartVal);

	DDX_Control(pDX, IDC_STATIC_LIGHT_SIDE_CHART_VALUE, m_clColorStaticSideChartVal);
	DDX_Control(pDX, IDC_STATIC_LIGHT_ALIGN_VALUE, m_clColorStaticAlignVal);
	
    
	DDX_Control(pDX, IDC_STATIC_LIGHT_OC, m_clColorStaticOC[0]);
	DDX_Control(pDX, IDC_STATIC_LIGHT_OC2, m_clColorStaticOC[1]);

	DDX_Control(pDX, IDC_STATIC_LIGHT_OC_WHITE_VAL, m_clColorStaticOCWhiteVal);
	DDX_Control(pDX, IDC_STATIC_LIGHT_OC_WHITE_TIME_VAL, m_clColorStaticOCWhiteTimeVal);
	
	DDX_Control(pDX, IDC_STATIC_LIGHT_OC_IR_VAL, m_clColorStaticOCIrVal);

	DDX_Control(pDX, IDC_SLIDER_LIGHT_TOP_CHART, m_clSliderCtrlTopChart);

	DDX_Control(pDX, IDC_SLIDER_LIGHT_SIDE_CHART, m_clSliderCtrlSideChart);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_LEFT_CHART, m_clSliderCtrlLeftChart);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_RIGHT_CHART, m_clSliderCtrlRightChart);
	
	DDX_Control(pDX, IDC_SLIDER_LIGHT_ALIGN, m_clSliderCtrlAlign);
	
	DDX_Control(pDX, IDC_SLIDER_LIGHT_OC_WHITE, m_clSliderCtrlOcWhite);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_OC_IR, m_clSliderCtrlOcIr);

	DDX_Control(pDX, IDC_SLIDER_LIGHT_STAIN, m_clSliderCtrlOC[1]);
	DDX_Control(pDX, IDC_BUTTON_TOP_CHART_LIGHT_SAVE,	m_clColorButtonTopChartSave);
	DDX_Control(pDX, IDC_BUTTON_OC_WHITE_LIGHT_SAVE, m_clColorButtonOcWhiteSave);
	DDX_Control(pDX, IDC_BUTTON_LEFT_CHART_LIGHT_SAVE, m_clColorButtonLeftChartSave);
	DDX_Control(pDX, IDC_BUTTON_RIGHT_CHART_LIGHT_SAVE, m_clColorButtonRightChartSave);
	
	DDX_Control(pDX, IDC_BUTTON_IR_WHITE_LIGHT_SAVE,	m_clColorButtonIrWhiteSave);
	DDX_Control(pDX, IDC_BUTTON_ALIGN_LIGHT_SAVE,		m_clColorButtonAlignSave);



	DDX_Control(pDX, IDC_COMBO_LIGHT_DOME, m_clComboDomeChannel);
	//
	DDX_Control(pDX, IDC_BUTTON_LIGHT_TOP_CHART1, m_clColorButtonTopChart[0]);
	
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_WHITE_CH1, m_clColorButtonOcWhite[0]);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_WHITE_CH2, m_clColorButtonOcWhite[1]);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_WHITE_CH3, m_clColorButtonOcWhite[2]);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_WHITE_CH4, m_clColorButtonOcWhite[3]);

	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_WHITE_POWER_ON, m_clColorButtonOcWhitePowerOn);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_WHITE_POWER_OFF, m_clColorButtonOcWhitePowerOff);

	
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_WHITE_GET_TIME, m_clColorButtonOcWhiteTime);

	DDX_Control(pDX, IDC_BUTTON_LIGHT_SIDE_CHART_LEFT, m_clColorButtonLeftChart);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_SIDE_CHART_RIGHT, m_clColorButtonRightChart);


	
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_IR_CH1, m_clColorButtonOcIr[0]);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_OC_IR_CH2, m_clColorButtonOcIr[1]);
	
	DDX_Control(pDX, IDC_BUTTON_LIGHT_ALIGN_SENSOR_CH, m_clColorButtonAlign[0]);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_ALIGN_HOLDER_CH, m_clColorButtonAlign[1]);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_ALIGN_LENS_CH, m_clColorButtonAlign[2]);
	
	DDX_Control(pDX, IDC_BUTTON_LIGHT_LX1, m_clColorButtonLx1);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_LX2, m_clColorButtonLx2);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_LX3, m_clColorButtonLx3);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_LX4, m_clColorButtonLx4);

	DDX_Control(pDX, IDC_BUTTON_LIGHT_CH_CHANGE, m_clColorButtonChChange);
	
	DDX_Control(pDX, IDC_BUTTON_LIGHT_VALUE_UP, m_clColorButtonUp);
	DDX_Control(pDX, IDC_BUTTON_LIGHT_VALUE_DOWN, m_clColorButtonDown);
	
	
}


BEGIN_MESSAGE_MAP(CLightDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_HSCROLL()
	ON_STN_CLICKED(IDC_STATIC_LIGHT_TOP_CHART_VALUE, &CLightDlg::OnStnClickedStaticLightChartVal)
	ON_STN_CLICKED(IDC_STATIC_LIGHT_OC_WHITE_VAL, &CLightDlg::OnStnClickedStaticLightOcVal)
	ON_BN_CLICKED(IDC_BUTTON1, &CLightDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLightDlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO_LIGHT_DOME, &CLightDlg::OnCbnSelchangeComboLightDome)
	ON_STN_CLICKED(IDC_STATIC_LIGHT_LEFT_CHART_VALUE, &CLightDlg::OnStnClickedStaticLightChartVal2)
    ON_STN_CLICKED(IDC_STATIC_LIGHT_RIGHT_CHART_VALUE, &CLightDlg::OnStnClickedStaticLightRightChartValue)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_LX1, &CLightDlg::OnBnClickedButtonLightLx1)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_LX2, &CLightDlg::OnBnClickedButtonLightLx2)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_LX3, &CLightDlg::OnBnClickedButtonLightLx3)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_LX4, &CLightDlg::OnBnClickedButtonLightLx4)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_VALUE_UP, &CLightDlg::OnBnClickedButtonLightValueUp)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_VALUE_DOWN, &CLightDlg::OnBnClickedButtonLightValueDown)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_CH_CHANGE, &CLightDlg::OnBnClickedButtonLightChChange)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART1, &CLightDlg::OnBnClickedButtonLightTopChart1)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART2, &CLightDlg::OnBnClickedButtonLightTopChart2)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART3, &CLightDlg::OnBnClickedButtonLightTopChart3)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART4, &CLightDlg::OnBnClickedButtonLightTopChart4)
	ON_STN_CLICKED(IDC_STATIC_LIGHT_ALIGN_VALUE, &CLightDlg::OnStnClickedStaticLightAlignValue)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART5, &CLightDlg::OnBnClickedButtonLightTopChart5)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART6, &CLightDlg::OnBnClickedButtonLightTopChart6)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART7, &CLightDlg::OnBnClickedButtonLightTopChart7)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART8, &CLightDlg::OnBnClickedButtonLightTopChart8)
	ON_STN_CLICKED(IDC_STATIC_LIGHT_OC_IR_VAL, &CLightDlg::OnStnClickedStaticLightOcIrVal)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_WHITE_CH1, &CLightDlg::OnBnClickedButtonLightOcWhiteCh1)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_WHITE_CH2, &CLightDlg::OnBnClickedButtonLightOcWhiteCh2)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_IR_CH1, &CLightDlg::OnBnClickedButtonLightOcIrCh1)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_IR_CH2, &CLightDlg::OnBnClickedButtonLightOcIrCh2)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_ALIGN_SENSOR_CH, &CLightDlg::OnBnClickedButtonLightAlignSensorCh)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_ALIGN_HOLDER_CH, &CLightDlg::OnBnClickedButtonLightAlignHolderCh)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_ALIGN_LENS_CH, &CLightDlg::OnBnClickedButtonLightAlignLensCh)
	ON_BN_CLICKED(IDC_BUTTON_TOP_CHART_LIGHT_SAVE, &CLightDlg::OnBnClickedButtonTopChartLightSave)
	ON_BN_CLICKED(IDC_BUTTON_OC_WHITE_LIGHT_SAVE, &CLightDlg::OnBnClickedButtonOcWhiteLightSave)
	ON_BN_CLICKED(IDC_BUTTON_IR_WHITE_LIGHT_SAVE, &CLightDlg::OnBnClickedButtonIrWhiteLightSave)
	ON_BN_CLICKED(IDC_BUTTON_ALIGN_LIGHT_SAVE, &CLightDlg::OnBnClickedButtonAlignLightSave)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_SIDE_CHART_LEFT, &CLightDlg::OnBnClickedButtonLightSideChartLeft)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_SIDE_CHART_RIGHT, &CLightDlg::OnBnClickedButtonLightSideChartRight)
	ON_STN_CLICKED(IDC_STATIC_LIGHT_SIDE_CHART_VALUE, &CLightDlg::OnStnClickedStaticLightSideChartValue)
	ON_BN_CLICKED(IDC_BUTTON_LEFT_CHART_LIGHT_SAVE, &CLightDlg::OnBnClickedButtonSideChartLightSave)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART9, &CLightDlg::OnBnClickedButtonLightTopChart9)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART10, &CLightDlg::OnBnClickedButtonLightTopChart10)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART11, &CLightDlg::OnBnClickedButtonLightTopChart11)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART12, &CLightDlg::OnBnClickedButtonLightTopChart12)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_TOP_CHART13, &CLightDlg::OnBnClickedButtonLightTopChart13)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_WHITE_GET_TIME, &CLightDlg::OnBnClickedButtonLightOcWhiteGetTime)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_WHITE_CH3, &CLightDlg::OnBnClickedButtonLightOcWhiteCh3)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_WHITE_CH4, &CLightDlg::OnBnClickedButtonLightOcWhiteCh4)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_WHITE_POWER_OFF, &CLightDlg::OnBnClickedButtonLightOcWhitePowerOff)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OC_WHITE_POWER_ON, &CLightDlg::OnBnClickedButtonLightOcWhitePowerOn)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT_CHART_LIGHT_SAVE, &CLightDlg::OnBnClickedButtonRightChartLightSave)
END_MESSAGE_MAP()


// CLightDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CLightDlg::OnPaint()
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
BOOL CLightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CLightDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticTitle.SetBkColor(RGB_CTRL_BG);
	m_clColorStaticTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTitle.SetFont(&m_clFontBig);
    m_clColorStaticTitle.SetFontBold(TRUE);
    m_clColorStaticTitle.SetBorder(FALSE);
    m_clColorStaticTitle.SetFontSize(15);

	m_clColorStaticChart[0].SetBkColor(RGB_DLG_BG);
	m_clColorStaticChart[0].SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticChart[0].SetFont(&m_clFontMid);

	m_clColorStaticChart[1].SetBkColor(RGB_DLG_BG);
	m_clColorStaticChart[1].SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticChart[1].SetFont(&m_clFontMid);

	m_clColorStaticOC[0].SetBkColor(RGB_DLG_BG);
	m_clColorStaticOC[0].SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOC[0].SetFont(&m_clFontMid);

	m_clColorStaticOC[1].SetBkColor(RGB_DLG_BG);
	m_clColorStaticOC[1].SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOC[1].SetFont(&m_clFontMid);

	m_clColorStaticAlignVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignVal.SetFont(&m_clFontMid);
	

	m_clColorStaticSideChartVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSideChartVal.SetFont(&m_clFontMid);
	

	m_clColorStaticTopChartVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTopChartVal.SetFont(&m_clFontMid);

	m_clColorStaticLeftChartVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLeftChartVal.SetFont(&m_clFontMid);

	m_clColorStaticRightChartVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticRightChartVal.SetFont(&m_clFontMid);

	m_clColorStaticOCWhiteVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCWhiteVal.SetFont(&m_clFontMid);

	m_clColorStaticOCWhiteTimeVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCWhiteTimeVal.SetFont(&m_clFontMid);


	
	m_clColorStaticOCIrVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCIrVal.SetFont(&m_clFontMid);

	m_clSliderCtrlAlign.SetRange(0, 255);
	m_clSliderCtrlAlign.SetTicFreq(5);

	m_clSliderCtrlTopChart.SetRange(0, 255);
	m_clSliderCtrlTopChart.SetTicFreq(5);


	m_clSliderCtrlSideChart.SetRange(0, 255);
	m_clSliderCtrlSideChart.SetTicFreq(5);

	
   

	m_clSliderCtrlOcWhite.SetRange(0, 255);//999);
	m_clSliderCtrlOcWhite.SetTicFreq(5);

	m_clSliderCtrlOcIr.SetRange(0, 999);
	m_clSliderCtrlOcIr.SetTicFreq(5);

	m_clSliderCtrlLeftChart.SetRange(0, 255);
	m_clSliderCtrlLeftChart.SetTicFreq(5);

	m_clSliderCtrlRightChart.SetRange(0, 255);
	m_clSliderCtrlRightChart.SetTicFreq(5);

	//m_clColorButtonSave.SetCtrlFont(20, 0, _T("맑은 고딕"));

	m_clComboDomeChannel.SetFont(&m_clFontMid);
	m_clComboDomeChannel.SetCurSel(0);

	//GetDlgItem(IDC_STATIC_LEFT_CHART)->SetWindowText("OC 6500K");
	//GetDlgItem(IDC_STATIC_RIGHT_CHART)->SetWindowText("OC 5000k");
	//
	GetDlgItem(IDC_SLIDER_LIGHT_STAIN)->ShowWindow(SW_HIDE);

	m_clColorButtonChChange.state = 1;
	//GetDlgItem(IDC_COMBO_LIGHT_DOME)->ShowWindow(SW_HIDE);


}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CLightDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];

	m_nUnit = nUnit;
	_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[LIGHT]")); //, m_nUnit + 1);
	GetDlgItem(IDC_STATIC_LIGHT_TITLE)->SetWindowText(szTitle);

	this->ShowLightData();
	this->ShowOCLightData();

}

//-----------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------
void CLightDlg::OnStnClickedStaticLightChartVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	CString sPos = _T("");
	int nValue;

	m_clColorStaticTopChartVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nValue = (int)pDlg->GetReturnVal();
			if (nValue < 0 || nValue > 999)
			{
				delete pDlg;
				g_ShowMsgPopup(_T("ERROR"), _T("조명값이 잘 못되었습니다.(범위 : 0 ~ 255)"), RGB_COLOR_RED);
				return;
			}

			sPos.Format(_T("%d"), nValue);
			m_clColorStaticTopChartVal.SetWindowText(sPos);
			m_clSliderCtrlTopChart.SetPos(nValue);
#ifdef ON_LINE_LIGHT 

			TopChartControl[0].dpctrlLedVolume(m_CurrentTopChartIndex + m_nUnit, nValue);

#endif
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CLightDlg::OnStnClickedStaticLightChartVal2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");
	int nValue;

	m_clColorStaticLeftChartVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nValue = (int)pDlg->GetReturnVal();
			if (nValue < 0 || nValue > 255)
			{
				delete pDlg;
				g_ShowMsgPopup(_T("ERROR"), _T("조명값이 잘 못되었습니다.(범위 : 0 ~ 255)"), RGB_COLOR_RED);
				return;
			}

			sPos.Format(_T("%d"), nValue);
			m_clColorStaticLeftChartVal.SetWindowText(sPos);
			m_clSliderCtrlLeftChart.SetPos(nValue);
#ifdef ON_LINE_LIGHT
			LightLeftChartControl[0].dpctrlLedVolume(LEFT_CHART_CH_1, nValue);
#endif
		}
		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CLightDlg::OnStnClickedStaticLightOcVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	CString sPos = _T("");
	int nValue;

	m_clColorStaticOCWhiteVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nValue = (int)pDlg->GetReturnVal();
			if (nValue < 0 || nValue > 999)
			{
				delete pDlg;
				g_ShowMsgPopup(_T("ERROR"), _T("조명값이 잘 못되었습니다.(범위 : 0 ~ 255)"), RGB_COLOR_RED);
				return;
			}

			sPos.Format(_T("%d"), nValue);
			m_clColorStaticOCWhiteVal.SetWindowText(sPos);
			m_clSliderCtrlOcWhite.SetPos(nValue);
#ifdef ON_LINE_LIGHT
			BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_OC_CH2 + m_nUnit, nValue);
			//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(m_CurrentBackduIndex, 1, nValue);
#endif
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	조명값 저장
//
//-----------------------------------------------------------------------------
void CLightDlg::GetLightData(int ChartIndex)
{
	// CHART
	switch (ChartIndex)
	{
	case 0:
		//TOP CHART
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_TOP_CHART_1 + m_CurrentTopChartIndex + m_nUnit] = m_clSliderCtrlTopChart.GetPos();
		break;
	case 1:
		//OC WHITE
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_OC_WHITE1 + m_CurrentBackduIndex + m_nUnit] = m_clSliderCtrlOcWhite.GetPos();
		break;
	case 2:
		//OC IR
		//g_clModelData[m_nUnit].m_nLight[LIGHT_OC_IR1 + m_CurrentOcIcIndex] = m_clSliderCtrlOcIr.GetPos();
		break;
	case 3:
		//ALIGN
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_SENSOR] = m_clSliderCtrlAlign.GetPos();
		break;
	case 4:
		//LEFT CHART
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_LEFT] = m_clSliderCtrlLeftChart.GetPos();
		break;
	case 5:
		//RIGHT CHART
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_RIGHT] = m_clSliderCtrlRightChart.GetPos();
		break;
	case 999:
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_TOP_CHART_1 + m_CurrentTopChartIndex + m_nUnit] = m_clSliderCtrlTopChart.GetPos();
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_OC_WHITE1] = m_clSliderCtrlOcWhite.GetPos();
		//g_clModelData[m_nUnit].m_nLight[LIGHT_OC_IR1 + m_CurrentOcIcIndex] = m_clSliderCtrlOcIr.GetPos();
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_SENSOR] = m_clSliderCtrlAlign.GetPos();
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_LEFT] = m_clSliderCtrlLeftChart.GetPos();
		g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_RIGHT] = m_clSliderCtrlRightChart.GetPos();
		break;
	}
	
	

	//
	//CString sPos = _T("");
	//m_clColorStaticOCIrVal.GetWindowText(sPos);

	

	
	
	
	
	//oc광원 룩스
	//g_clModelData[m_nUnit].m_LxData[oc_CHANNEL] = ocLux;// m_clSliderCtrlChart[2].GetPos();
	//g_clModelData[m_nUnit].m_LxVal = ocVal;
	
	//
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CLightDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{		
		Sleep(100);
		this->ShowLightData();		
		//this->ShowOCLightData();

		

		/*TopChartControl[m_nUnit].ctrlLedVolume(LIGHT_OC_IR_CH1, g_clModelData[m_nUnit].m_nLight[LIGHT_OC_IR]); 
		Sleep(100);
		TopChartControl[m_nUnit].ctrlLedVolume(LIGHT_OC_WHITE, g_clModelData[m_nUnit].m_nLight[LIGHT_OC_5100k]);*/
		
		

	}
}

//-----------------------------------------------------------------------------
//
//	조명값 표시
//
//-----------------------------------------------------------------------------
void CLightDlg::ShowLightData()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int chVal = 0;
	int lightVal = 0;
	chVal = m_CurrentTopChartIndex + m_nUnit;
	lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_CHART_CH_1];
	TopChart_Change(chVal, lightVal);


	TopChartControl[m_nUnit].dpctrlLedVolume(LIGHT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_TOP_CHART_1]);


	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nLight[chVal]);
	m_clColorStaticTopChartVal.SetWindowText(szData);
	m_clSliderCtrlTopChart.SetPos(g_clModelData[m_nUnit].m_nLight[chVal]);

	//LEFT CHART
	chVal = m_CurrentLeftChartIndex;

	lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_LEFT + chVal];
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), lightVal);

	m_clColorStaticLeftChartVal.SetWindowText(szData);
	m_clSliderCtrlLeftChart.SetPos(lightVal);
	LeftChart_Change(chVal, lightVal);

	//RIGHT CHART
	chVal = m_CurrentRightChartIndex;

	lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_RIGHT + chVal];
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), lightVal);

	m_clColorStaticRightChartVal.SetWindowText(szData);
	m_clSliderCtrlRightChart.SetPos(lightVal);
	RightChart_Change(chVal, lightVal);


	LightLeftChartControl[m_nUnit].dpctrlLedVolume(LEFT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_LEFT]);
	LightRightChartControl[m_nUnit].dpctrlLedVolume(RIGHT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_RIGHT]);

	//OCControl[m_nUnit].Send_12CHChannel_Value(LIGHT_CHART_LEFT_CH1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_LEFT]);
	//OCControl[m_nUnit].Send_12CHChannel_Value(LIGHT_CHART_RIGHT_CH2, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_RIGHT]);
	

	//Oc White
	chVal = LIGHT_BD_OC_CH2;
	lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_OC_WHITE1];
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), lightVal);
	m_clColorStaticOCWhiteVal.SetWindowText(szData);
	m_clSliderCtrlOcWhite.SetPos(lightVal);
	OcWhite_Change(0, lightVal);

	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(chVal, 1, lightVal);
	BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_OC_CH2 + m_nUnit, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_OC_WHITE1]);

	
	//ALIGN
	chVal = LIGHT_BD_ALIGN_CH1;
	lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_SENSOR];
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), lightVal);
	m_clColorStaticAlignVal.SetWindowText(szData);
	m_clSliderCtrlAlign.SetPos(lightVal);
	Align_Change(chVal, lightVal);


	BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_ALIGN_CH1 + m_nUnit, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_SENSOR]);

}
void CLightDlg::ShowOCLightData()
{
	//TCHAR szData[SIZE_OF_100BYTE];
	ocLux = g_clModelData[m_nUnit].m_LxData[oc_CHANNEL];
	ocVal = g_clModelData[m_nUnit].m_LxVal;
	OC_LX_Change(ocLux);

}

//-----------------------------------------------------------------------------
//
//	OnHScroll
//
//-----------------------------------------------------------------------------
void CLightDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TCHAR szPos[SIZE_OF_100BYTE];
	int nPosi = 0;

	if (nSBCode == SB_ENDSCROLL)
		return;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		return;
	}
	if (pScrollBar->m_hWnd == GetDlgItem(IDC_SLIDER_LIGHT_TOP_CHART)->m_hWnd)		//TOP CHART
	{
		nPosi = m_clSliderCtrlTopChart.GetPos();

		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), nPosi);
		m_clColorStaticTopChartVal.SetWindowText(szPos);
#ifdef ON_LINE_LIGHT	
		TopChartControl[0].dpctrlLedVolume(m_CurrentTopChartIndex + m_nUnit, nPosi);
#endif
	}
	else if (pScrollBar->m_hWnd == GetDlgItem(IDC_SLIDER_LIGHT_LEFT_CHART)->m_hWnd)		//LEFT CHART
	{
		nPosi = m_clSliderCtrlLeftChart.GetPos();
		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), nPosi);
		m_clColorStaticLeftChartVal.SetWindowText(szPos);

#ifdef ON_LINE_LIGHT
		LightLeftChartControl[0].dpctrlLedVolume(m_CurrentLeftChartIndex + m_nUnit, nPosi);
#endif
	}
	else if (pScrollBar->m_hWnd == GetDlgItem(IDC_SLIDER_LIGHT_RIGHT_CHART)->m_hWnd)		//RIGHT CHART
	{
		nPosi = m_clSliderCtrlRightChart.GetPos();
		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), nPosi);
		m_clColorStaticRightChartVal.SetWindowText(szPos);
#ifdef ON_LINE_LIGHT
		LightRightChartControl[0].dpctrlLedVolume(m_CurrentRightChartIndex + m_nUnit, nPosi);
#endif

	}
	else if (pScrollBar->m_hWnd == GetDlgItem(IDC_SLIDER_LIGHT_ALIGN)->m_hWnd)		//ALIGN
	{
		nPosi = m_clSliderCtrlAlign.GetPos();

		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), nPosi);
		m_clColorStaticAlignVal.SetWindowText(szPos);
#ifdef ON_LINE_LIGHT
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_ALIGN_CH1 + m_nUnit, nPosi);

#endif
	}
	else if (pScrollBar->m_hWnd == GetDlgItem(IDC_SLIDER_LIGHT_OC_WHITE)->m_hWnd)		//이물 광원
	{
		nPosi = m_clSliderCtrlOcWhite.GetPos();

		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), nPosi);
		m_clColorStaticOCWhiteVal.SetWindowText(szPos);
#ifdef ON_LINE_LIGHT
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_OC_CH2 + m_nUnit, nPosi);
#endif
	}
	
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//-----------------------------------------------------------------------------
//
//	Combo Box : Dome 조명값
//
//-----------------------------------------------------------------------------
void CLightDlg::OnCbnSelchangeComboLightDome()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szData[SIZE_OF_100BYTE];

}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CLightDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		
	}
	else if(pMsg->message == WM_LBUTTONUP)
	{

	}
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CLightDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_pCarAABonderDlg->m_clSerialThread.SendLightSet(m_nUnit, 'C', 1, 50, false);
}


void CLightDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_pCarAABonderDlg->m_clSerialThread.SendLightOnOffSet(m_nUnit, 'H', 1, true, false);

}

void CLightDlg::OnStnClickedStaticLightRightChartValue()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString sPos = _T("");
    int nValue;

	m_clColorStaticRightChartVal.GetWindowText(sPos);
    CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
    if (pDlg != NULL)
    {
        if (pDlg->DoModal() == IDOK)
        {
            nValue = (int)pDlg->GetReturnVal();
            if (nValue < 0 || nValue > 255)
            {
                delete pDlg;
                g_ShowMsgPopup(_T("ERROR"), _T("조명값이 잘 못되었습니다.(범위 : 0 ~ 255)"), RGB_COLOR_RED);
                return;
            }

            sPos.Format(_T("%d"), nValue);
			m_clColorStaticRightChartVal.SetWindowText(sPos);
			m_clSliderCtrlRightChart.SetPos(nValue);
#ifdef ON_LINE_LIGHT
			LightRightChartControl[0].dpctrlLedVolume(RIGHT_CHART_CH_1, nValue);
#endif
        }

        delete pDlg;
    }
}

void CLightDlg::OC_LX_Change(int LxData)
{
	//
	ocLux = LxData;
	m_clColorButtonLx1.state = 0;
	m_clColorButtonLx2.state = 0;
	m_clColorButtonLx3.state = 0;
	m_clColorButtonLx4.state = 0;
	switch (ocLux)
	{
	case OC_1000_LX:
		m_clColorButtonLx1.state = 1;
		break;
	case OC_2000_LX:
		m_clColorButtonLx2.state = 1;
		break;
	case OC_3000_LX:
		m_clColorButtonLx3.state = 1;
		break;
	case OC_4000_LX:
		m_clColorButtonLx4.state = 1;
		break;
	}
	m_clColorButtonLx1.Invalidate();
	m_clColorButtonLx2.Invalidate();
	m_clColorButtonLx3.Invalidate();
	m_clColorButtonLx4.Invalidate();
}
void CLightDlg::OnBnClickedButtonLightLx1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//OCControl[m_nUnit].SendLightONOFF(true);
	/*if (g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_AUTO && g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_PAUSE)
	{
		OCControl[m_nUnit].SendLightLxStep(OC_1000_LX);
		OC_LX_Change(OC_1000_LX);
		Sleep(15);
		OCControl[m_nUnit].LxSetDataSave();
	}*/
	
}


void CLightDlg::OnBnClickedButtonLightLx2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//OCControl[m_nUnit].SendLightONOFF(false);
	/*if (g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_AUTO && g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_PAUSE)
	{
		OCControl[m_nUnit].SendLightLxStep(OC_2000_LX);
		OC_LX_Change(OC_2000_LX);
		Sleep(15);
		OCControl[m_nUnit].LxSetDataSave();
	}*/
}


void CLightDlg::OnBnClickedButtonLightLx3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*if (g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_AUTO && g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_PAUSE)
	{
		OCControl[m_nUnit].SendLightLxStep(OC_3000_LX);
		OC_LX_Change(OC_3000_LX);
		Sleep(15);
		OCControl[m_nUnit].LxSetDataSave();
	}*/
}


void CLightDlg::OnBnClickedButtonLightLx4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*if (g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_AUTO && g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_PAUSE)
	{
		OCControl[m_nUnit].SendLightLxStep(OC_4000_LX);
		OC_LX_Change(OC_4000_LX);
		Sleep(15);
		OCControl[m_nUnit].LxSetDataSave();
	}*/
}


void CLightDlg::OnBnClickedButtonLightValueUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//OCControl[m_nUnit].SendLightValue(0);//0 = up
	//Sleep(15);
	//OCControl[m_nUnit].LxSetDataSave();
}


void CLightDlg::OnBnClickedButtonLightValueDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//OCControl[m_nUnit].SendLightValue(1);//1 = down
	//Sleep(15);
	//OCControl[m_nUnit].LxSetDataSave();
}


void CLightDlg::OnBnClickedButtonLightChChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (oc_CHANNEL == LIGHT_OC_WHITE_CH1)
	{
		oc_CHANNEL = LIGHT_OC_IR_CH1;
	}
	else
	{
		oc_CHANNEL = LIGHT_OC_WHITE_CH1;
	}
	OC_CHANNEL_Change(oc_CHANNEL);
	this->ShowOCLightData();
}

void CLightDlg::OC_CHANNEL_Change(int OC_CH)
{
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO || g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		return;
	}
	if (OC_CH == LIGHT_OC_WHITE_CH1)
	{
		//5000
		m_clColorButtonChChange.SetWindowText(_T("5000K ON"));
	}
	else
	{
		//6500
		m_clColorButtonChChange.SetWindowText(_T("6500K ON"));
	}
	//OCControl[m_nUnit].SendLightChange(OC_CH);
}

void CLightDlg::TopChart_Change(int index, int nValue)
{
	m_clColorButtonTopChart[0].state = 0;

	m_clColorButtonTopChart[index].state = 1;
	CString sPos = _T("");
	sPos.Format(_T("%d"), nValue);
	m_clColorStaticTopChartVal.SetWindowText(sPos);

	m_clSliderCtrlTopChart.SetPos(nValue);
	//
	//
	m_clColorButtonTopChart[0].Invalidate();
	


	
}

void CLightDlg::LeftChart_Change(int index, int nValue)
{
	m_clColorButtonLeftChart.state = 1;
	CString sPos = _T("");
	sPos.Format(_T("%d"), nValue);
	m_clColorStaticLeftChartVal.SetWindowText(sPos);
	m_clSliderCtrlLeftChart.SetPos(nValue);
	m_clColorButtonLeftChart.Invalidate();
}

void CLightDlg::RightChart_Change(int index, int nValue)
{
	m_clColorButtonRightChart.state = 1;
	CString sPos = _T("");
	sPos.Format(_T("%d"), nValue);
	m_clColorStaticRightChartVal.SetWindowText(sPos);
	m_clSliderCtrlRightChart.SetPos(nValue);
	m_clColorButtonRightChart.Invalidate();
}
void CLightDlg::SideChart_Change(int index, int nValue)
{
	//m_clColorButtonSideChart[0].state = 0;
	//m_clColorButtonSideChart[1].state = 0;


	//m_clColorButtonSideChart[index].state = 1;
	//CString sPos = _T("");
	//sPos.Format(_T("%d"), nValue);
	//m_clColorStaticSideChartVal.SetWindowText(sPos);

	//m_clSliderCtrlSideChart.SetPos(nValue);
	////
	////
	//m_clColorButtonSideChart[0].Invalidate();
	//m_clColorButtonSideChart[1].Invalidate();
}
void CLightDlg::OcWhite_Change(int index, int nValue)
{
	m_clColorButtonOcWhite[0].state = 0;
	m_clColorButtonOcWhite[1].state = 0;
	m_clColorButtonOcWhite[2].state = 0;
	m_clColorButtonOcWhite[3].state = 0;


	m_clColorButtonOcWhite[index].state = 1;
	CString sPos = _T("");
	sPos.Format(_T("%d"), nValue);
	m_clColorStaticOCWhiteVal.SetWindowText(sPos);

	m_clSliderCtrlOcWhite.SetPos(nValue);
	//
	//
	m_clColorButtonOcWhite[0].Invalidate();
	m_clColorButtonOcWhite[1].Invalidate();
	m_clColorButtonOcWhite[2].Invalidate();
	m_clColorButtonOcWhite[3].Invalidate();
}
void CLightDlg::OcIr_Change(int index, int nValue)
{
	m_clColorButtonOcIr[0].state = 0;
	m_clColorButtonOcIr[1].state = 0;


	m_clColorButtonOcIr[index].state = 1;
	CString sPos = _T("");
	sPos.Format(_T("%d"), nValue);
	m_clColorStaticOCIrVal.SetWindowText(sPos);

	m_clSliderCtrlOcIr.SetPos(nValue);
	//
	//
	m_clColorButtonOcIr[0].Invalidate();
	m_clColorButtonOcIr[1].Invalidate();
}
void CLightDlg::Align_Change(int index, int nValue)
{
	m_clColorButtonAlign[0].state = 1;

	CString sPos = _T("");
	sPos.Format(_T("%d"), nValue);
	m_clColorStaticAlignVal.SetWindowText(sPos);

	m_clSliderCtrlAlign.SetPos(nValue);
	//
	//
	m_clColorButtonAlign[0].Invalidate();
}


void CLightDlg::OnBnClickedButtonLightTopChart1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_1 + m_nUnit;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].dpctrlLedVolume(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_2;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].ctrlLedVolume(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_3;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].ctrlLedVolume(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_4;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].ctrlLedVolume(chVal, lightVal);
}


void CLightDlg::OnStnClickedStaticLightAlignValue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");
	int nValue;

	m_clColorStaticAlignVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nValue = (int)pDlg->GetReturnVal();
			if (nValue < 0 || nValue > 255) 
			{
				delete pDlg;
				g_ShowMsgPopup(_T("ERROR"), _T("조명값이 잘 못되었습니다.(범위 : 0 ~ 255)"), RGB_COLOR_RED);
				return;
			}

			sPos.Format(_T("%d"), nValue);
			m_clColorStaticAlignVal.SetWindowText(sPos);
			m_clSliderCtrlAlign.SetPos(nValue);
#ifdef ON_LINE_LIGHT
			BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_ALIGN_CH1 + m_nUnit, nValue);
#endif
		}

		delete pDlg;
	}
}


void CLightDlg::OnBnClickedButtonLightTopChart5()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_5;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart6()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_6;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart7()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_7;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart8()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_8;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnStnClickedStaticLightOcIrVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T(""); 
	int nValue;

	m_clColorStaticOCIrVal.GetWindowText(sPos); 
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nValue = (int)pDlg->GetReturnVal();
			if (nValue < 0 || nValue > 999)
			{
				delete pDlg;
				g_ShowMsgPopup(_T("ERROR"), _T("조명값이 잘 못되었습니다.(범위 : 0 ~ 255)"), RGB_COLOR_RED);
				return;
			}

			sPos.Format(_T("%d"), nValue); 
			m_clColorStaticOCIrVal.SetWindowText(sPos);
			m_clSliderCtrlOcIr.SetPos(nValue);
#ifdef ON_LINE_LIGHT
			//IRControl[m_nUnit].Send_12CHChannel_Value(m_CurrentBackduIndex + m_nUnit, nValue);
#endif
		}

		delete pDlg;
	}
}


void CLightDlg::OnBnClickedButtonLightOcWhiteCh1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	m_CurrentBackduIndex = LIGHT_BD_OC_CH2;
	int chVal = m_CurrentBackduIndex + m_nUnit;
	int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_OC_WHITE1];
	//
	OcWhite_Change(0, lightVal);
	BackDuLightControl[m_nUnit].ctrlLedVolume(chVal, lightVal);
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(chVal, 1, lightVal);

}


void CLightDlg::OnBnClickedButtonLightOcWhiteCh2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	//m_CurrentBackduIndex = LIGHT_OC_WHITE_CH2;
	//int chVal = m_CurrentBackduIndex + m_nUnit;
	//int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_OC_WHITE2];
	//
	//OcWhite_Change(chVal, lightVal);
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(chVal, 1, lightVal);


}


void CLightDlg::OnBnClickedButtonLightOcIrCh1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	//m_CurrentOcIcIndex = LIGHT_OC_IR_CH1;
	//int chVal = m_CurrentOcIcIndex;
	//int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_OC_IR1 + m_CurrentOcIcIndex];
	//
	//OcIr_Change(chVal, lightVal);

	//IRControl[m_nUnit].Send_12CHChannel_Value(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightOcIrCh2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	//m_CurrentOcIcIndex = LIGHT_OC_IR_CH2;
	//int chVal = m_CurrentOcIcIndex;
	//int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_OC_IR1 + m_CurrentOcIcIndex];
	//
	//OcIr_Change(chVal, lightVal);

	//IRControl[m_nUnit].Send_12CHChannel_Value(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightAlignSensorCh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	int chVal = LIGHT_BD_ALIGN_CH1 + m_nUnit;
	int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_SENSOR];
	//
	Align_Change(chVal, lightVal);
	BackDuLightControl[m_nUnit].ctrlLedVolume(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightAlignHolderCh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLightDlg::OnBnClickedButtonLightAlignLensCh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLightDlg::OnBnClickedButtonTopChartLightSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("조명 값을 저장하시겠습니까?"), RGB_COLOR_RED) == false)
		return;

	this->GetLightData(0);

	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	AddLog(_T("[INFO] TOP CHART 조명값 저장"), 0, m_nUnit);
}


void CLightDlg::OnBnClickedButtonOcWhiteLightSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("조명 값을 저장하시겠습니까?"), RGB_COLOR_RED) == false)
		return;

	this->GetLightData(1);

	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	AddLog(_T("[INFO] OC 조명값 저장"), 0, m_nUnit);
}


void CLightDlg::OnBnClickedButtonIrWhiteLightSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("조명 값을 저장하시겠습니까?"), RGB_COLOR_RED) == false)
		return;

	this->GetLightData(2);

	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	AddLog(_T("[INFO] IR 조명값 저장"), 0, m_nUnit);
}


void CLightDlg::OnBnClickedButtonAlignLightSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("조명 값을 저장하시겠습니까?"), RGB_COLOR_RED) == false)
		return;

	this->GetLightData(3);

	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	AddLog(_T("[INFO] ALIGN 조명값 저장"), 0, m_nUnit);
}


void CLightDlg::OnBnClickedButtonLightSideChartLeft()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentLeftChartIndex = LEFT_CHART_CH_1;
	int chVal = m_CurrentLeftChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_LEFT];
	//
	LeftChart_Change(chVal, lightVal);
	LightLeftChartControl[0].dpctrlLedVolume(chVal, lightVal);
	///LightLeftChartControl[0].dpctrlLedVolume(LEFT_CHART_CH_1, nValue);


	//LeftChart_Change(chVal, lightVal);

	//OCControl[m_nUnit].Send_12CHChannel_Value(chVal, lightVal);

}


void CLightDlg::OnBnClickedButtonLightSideChartRight()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}


	m_CurrentRightChartIndex = RIGHT_CHART_CH_1;
	int chVal = m_CurrentRightChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_RIGHT];
	//
	RightChart_Change(chVal, lightVal);

	LightRightChartControl[0].dpctrlLedVolume(chVal, lightVal);
	//OCControl[m_nUnit].Send_12CHChannel_Value(chVal, lightVal);

}


void CLightDlg::OnStnClickedStaticLightSideChartValue()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	CString sPos = _T("");
	int nValue;

	m_clColorStaticSideChartVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nValue = (int)pDlg->GetReturnVal(); 
			if (nValue < 0 || nValue > 999)
			{
				delete pDlg;
				g_ShowMsgPopup(_T("ERROR"), _T("조명값이 잘 못되었습니다.(범위 : 0 ~ 255)"), RGB_COLOR_RED);
				return;
			}

			sPos.Format(_T("%d"), nValue);
			m_clColorStaticSideChartVal.SetWindowText(sPos);
			m_clSliderCtrlSideChart.SetPos(nValue);
#ifdef ON_LINE_LIGHT
	
			
#endif
		}

		delete pDlg;
	}
}


void CLightDlg::OnBnClickedButtonSideChartLightSave()
{
	// TODO: Add your control notification handler code here
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

	if (g_ShowMsgModal(_T("확인"), _T("조명 값을 저장하시겠습니까?"), RGB_COLOR_RED) == false)
		return;

	this->GetLightData(4);

	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	AddLog(_T("[INFO] LEFT CHART 조명값 저장"), 0, m_nUnit);
}


void CLightDlg::OnBnClickedButtonLightTopChart9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_9;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	//m_CurrentTopChartIndex = LIGHT_CHART_CH_1 + m_nUnit;
	//int chVal = m_CurrentTopChartIndex;
	//int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	////
	//TopChart_Change(chVal, lightVal);
	//TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);


	m_CurrentTopChartIndex = LIGHT_CHART_CH_10;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_11;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_12;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}


void CLightDlg::OnBnClickedButtonLightTopChart13()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	m_CurrentTopChartIndex = LIGHT_CHART_CH_13;
	int chVal = m_CurrentTopChartIndex;
	int lightVal = g_clModelData[m_nUnit].m_nLight[m_CurrentTopChartIndex];
	//
	TopChart_Change(chVal, lightVal);
	TopChartControl[0].SendDomeChartLightValue(chVal, lightVal);
}

void CLightDlg::setOcTime(int mtime)
{
	/*CString sPos;
	sPos.Format(_T("%d"), mtime);
	m_clColorStaticOCWhiteTimeVal.SetWindowText(sPos);
	sPos.Empty();*/
}
void CLightDlg::OnBnClickedButtonLightOcWhiteGetTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit); 
		return;
	}
}


void CLightDlg::OnBnClickedButtonLightOcWhiteCh3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	//m_CurrentBackduIndex = LIGHT_OC_WHITE_CH3;
	//int chVal = m_CurrentBackduIndex + m_nUnit;
	//int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_OC_WHITE3];
	//
	//OcWhite_Change(chVal, lightVal);
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(chVal, 1, lightVal);

}


void CLightDlg::OnBnClickedButtonLightOcWhiteCh4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	//m_CurrentBackduIndex = LIGHT_OC_WHITE_CH4;
	//int chVal = m_CurrentBackduIndex + m_nUnit;
	//int lightVal = g_clModelData[m_nUnit].m_nLight[LIGHT_OC_WHITE4];
	//
	//OcWhite_Change(chVal, lightVal);
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(chVal, 1, lightVal);

}


void CLightDlg::OnBnClickedButtonLightOcWhitePowerOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(LIGHT_OC_WHITE_CH1, 0, 0);	Sleep(20);
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(LIGHT_OC_WHITE_CH2, 0, 0);	Sleep(20);
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(LIGHT_OC_WHITE_CH3, 0, 0);	Sleep(20);
	//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(LIGHT_OC_WHITE_CH4, 0, 0);
	//AddLog(_T("[INFO] 이물 광원 OFF"), 0, m_nUnit);
}


void CLightDlg::OnBnClickedButtonLightOcWhitePowerOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//자동 운전때 켜기 때문에  ON삭제
}


void CLightDlg::OnBnClickedButtonRightChartLightSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: Add your control notification handler code here
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

	if (g_ShowMsgModal(_T("확인"), _T("조명 값을 저장하시겠습니까?"), RGB_COLOR_RED) == false)
		return;

	this->GetLightData(5);

	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);

	AddLog(_T("[INFO] RIGHT CHART 조명값 저장"), 0, m_nUnit);
}