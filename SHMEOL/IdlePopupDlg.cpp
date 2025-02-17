// IdlePopupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IdlePopupDlg.h"
#include "afxdialogex.h"


// CIdlePopupDlg dialog

IMPLEMENT_DYNAMIC(CIdlePopupDlg, CDialogEx)

CIdlePopupDlg::CIdlePopupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IDLE_POPUP, pParent)
{
	m_nUnit = UNIT_AA1;
	m_brCheck.CreateSolidBrush(RGB(45, 45, 45));
}

CIdlePopupDlg::~CIdlePopupDlg()
{
}

void CIdlePopupDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_IDLE_TITLE, m_clColorStaticIdleIdleTitle);

	//DDX_Control(pDX, IDC_STATIC_IDLE_OP_ID, m_clColorStaticIdleOpId);
	//DDX_Control(pDX, IDC_STATIC_IDLE_OP_ID_VAL, m_clColorStaticIdleOpIdVal);

	//DDX_Control(pDX, IDC_STATIC_IDLE_GROUP, m_clColorStaticIdleGroup);
	//DDX_Control(pDX, IDC_COMBO_IDLE_GROUP, m_clComBoxIdleGroup);
	//DDX_Control(pDX, IDC_STATIC_IDLE_GROUP_VAL, m_clColorStaticIdleGroupVal);
	
	DDX_Control(pDX, IDC_STATIC_IDLE_REASON, m_clColorStaticIdleReason);
	DDX_Control(pDX, IDC_COMBO_IDLE_REASON, m_clComBoxIdleReason);

	DDX_Control(pDX, IDC_STATIC_IDLE_NOTE, m_clColorStaticIdleNote);
	DDX_Control(pDX, IDC_EDIT_IDLE_NOTE_VAL, m_clCeditIdleNoteVal);
	
	//DDX_Control(pDX, IDC_STATIC_IDLE_NOTE_VAL, m_clColorStaticIdleNoteVal);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIdlePopupDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CIdlePopupDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC_IDLE_OP_ID_VAL, &CIdlePopupDlg::OnStnClickedStaticIdleOpIdVal)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CIdlePopupDlg message handlers


//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CIdlePopupDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

BOOL CIdlePopupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	// 다이얼로그를 최상위 창으로 설정
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	// 컨트롤 초기화
	this->InitCtrl();

	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CIdlePopupDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	//m_clColorStaticTopBar.SetBkColor(RGB_COLOR_BLACK);
	//m_clColorStaticTopBar.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticIdleIdleTitle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticIdleIdleTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticIdleIdleTitle.SetFont(&m_clFontSmall);
	
	//m_clColorStaticIdleOpId.SetBkColor(RGB_DLG_BG);
	//m_clColorStaticIdleOpId.SetTextColor(RGB_COLOR_WHITE);
	//m_clColorStaticIdleOpId.SetFont(&m_clFontSmall);

	//m_clColorStaticIdleOpIdVal.SetBkColor(RGB_COLOR_WHITE);
	//m_clColorStaticIdleOpIdVal.SetFont(&m_clFontMid);



	//m_clColorStaticIdleGroup.SetBkColor(RGB_DLG_BG);
	//m_clColorStaticIdleGroup.SetTextColor(RGB_COLOR_WHITE);
	//m_clColorStaticIdleGroup.SetFont(&m_clFontSmall);


	m_clColorStaticIdleReason.SetBkColor(RGB_DLG_BG);
	m_clColorStaticIdleReason.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticIdleReason.SetFont(&m_clFontSmall);

	//CLabel ;
	//CComboBox m_clComBoxIdleGroup;

	//CLabel ;
	//CComboBox m_clComBoxIdleReason;

	m_clColorStaticIdleNote.SetBkColor(RGB_DLG_BG);
	m_clColorStaticIdleNote.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticIdleNote.SetFont(&m_clFontSmall);




	//m_clComBoxIdleGroup.ResetContent();
	m_clComBoxIdleReason.ResetContent();


	//m_clComBoxIdleGroup.AddString(_T("0"));
	m_clComBoxIdleReason.AddString(_T("blank"));

	//m_clComBoxIdleGroup.SetCurSel(0);
	m_clComBoxIdleReason.SetCurSel(0);
}

BOOL CIdlePopupDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_LBUTTONDOWN)
	{
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{

	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
		{
			if (GetFocus() == GetDlgItem(IDC_EDIT_IDLE_NOTE_VAL))
			{
				m_clCeditIdleNoteVal.ReplaceSel("\r\n");
				return TRUE;
			}
			return TRUE;
		}

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CIdlePopupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_CHECK_CCD_BLEMISH_8BITUSE
		)
	{
		pDC->SetTextColor(RGB_COLOR_WHITE);
		pDC->SetBkColor(RGB(100, 100, 100));
		pDC->SetBkMode(TRANSPARENT);

		return (HBRUSH)m_brCheck;
		//return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CIdlePopupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, RGB_DLG_BG);
}


void CIdlePopupDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	//S6F11 Idle Reason Report Send
	CString reportData = _T("");
	int nIndex = 0;
	CString sData = _T("");


	//Idle reason
	nIndex = m_clComBoxIdleReason.GetCount();
	if (nIndex > 0)
	{
		nIndex = m_clComBoxIdleReason.GetCurSel();
		m_clComBoxIdleReason.GetLBText(nIndex, sData);
		reportData.AppendFormat(_T("%s,"), sData);
	}
	else
	{
		reportData.AppendFormat(_T("Code1,Reason1,"));
	}

	//Idle Start Time
	reportData.AppendFormat(_T("%s,"), g_clTaskWork[m_nUnit].m_szIdleStartTime);	//Excuting 하고 바로 Idle 전환한 시간
	

	CTime cTime = CTime::GetCurrentTime();
	CString strData;
	strData.Format(_T("%02d%02d%02d%02d%02d%02d"),
		cTime.GetYear(),
		cTime.GetMonth(),
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());


	_stprintf_s(g_clTaskWork[m_nUnit].m_szIdleEndTime, SIZE_OF_100BYTE, _T("%s"), strData);

	//Idle End Time
	reportData.AppendFormat(_T("%s,"), g_clTaskWork[m_nUnit].m_szIdleEndTime);// _T("2024/12/29 15:20:10"));
	//Note
	m_clCeditIdleNoteVal.GetWindowText(sData);
	reportData.AppendFormat(_T("%s,"), sData);

	//reportData: 0 = code, 1 = startTime , 2 = EndTime , 3 = Note
	g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(IDLE_REASON_REPORT_10402, reportData);	//Idle Reason Report

	g_pCarAABonderDlg->KillTimer(WM_IDLE_REASON_TIMER);
	g_pCarAABonderDlg->SetTimer(WM_IDLE_REASON_TIMER, g_clMesCommunication[m_nUnit].IdleSetTimeInterval * 60000, NULL);		//Idle Ok Button
	CDialogEx::OnOK();
}
void CIdlePopupDlg::setOperatorID(CString opId)
{
	//m_clColorStaticIdleOpIdVal.SetWindowText(opId);
	//m_clColorStaticIdleOpIdVal.Invalidate();
}

void CIdlePopupDlg::OnStnClickedStaticIdleOpIdVal()
{
	// TODO: Add your control notification handler code here
	/*CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		CString sData;
		m_clColorStaticIdleOpIdVal.GetWindowText(sData);
		pDlg->SetReturnValue(sData);
		if (pDlg->DoModal() == IDOK)
		{
			m_clColorStaticIdleOpIdVal.SetWindowText(pDlg->GetReturnValue());
		}

		delete pDlg;
	}*/
}


void CIdlePopupDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here

	if (bShow == TRUE)
	{

		//m_clComBoxIdleGroup.ResetContent();
		m_clComBoxIdleReason.ResetContent();

		
		m_clCeditIdleNoteVal.SetWindowTextA(_T(""));


		//std::vector<RcmdParam1> results = g_clReportData.T1_FindChildList(g_clReportData.rSetCode_Idle_Reason.parameters);
		//std::vector<RcmdParam1> results = g_clReportData.vIdleReason;
		
		CString sData;
		sData.Empty();
		for (int i = 0; i < g_clReportData.vIdleReason.size(); i++)
		{
			sData.Format(_T("%s,%s"), g_clReportData.vIdleReason[i].cpName, g_clReportData.vIdleReason[i].cepVal);
			m_clComBoxIdleReason.AddString(sData);
		}

		m_clComBoxIdleReason.SetCurSel(0);
	}
}


void CIdlePopupDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	g_pCarAABonderDlg->EnableWindow(TRUE);
	CDialogEx::OnClose();
}
