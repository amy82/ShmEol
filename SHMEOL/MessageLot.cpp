// IdlePopupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MessageLot.h"
#include "afxdialogex.h"


// CMessageLot dialog

IMPLEMENT_DYNAMIC(CMessageLot, CDialogEx)

CMessageLot::CMessageLot(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MESSAGE_TYPE2, pParent)
{
	m_nUnit = UNIT_AA1;
	nMode = 0;
	nBuzzerOnType = 0;
	m_brCheck.CreateSolidBrush(RGB(45, 45, 45));
}

CMessageLot::~CMessageLot()
{
}

void CMessageLot::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT_MSG2_TITLE, m_edtLotTitle);

	DDX_Control(pDX, IDC_STATIC_MSG2_LOT_ID, m_clColorStaticIdleLotId);
	DDX_Control(pDX, IDC_STATIC_MSG2_LOT_ID_VAL, m_clColorStaticIdleLotIdVal);


	DDX_Control(pDX, IDOK, m_ColorbuttonRetry); 
	DDX_Control(pDX, IDCANCEL, m_ColorbuttonClose);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageLot, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CMessageLot::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC_MSG2_LOT_ID_VAL, &CMessageLot::OnStnClickedStaticIdleLotIdVal)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CMessageLot::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMessageLot message handlers


//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CMessageLot::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

BOOL CMessageLot::OnInitDialog()
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
void CMessageLot::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	//m_clColorStaticTopBar.SetBkColor(RGB_COLOR_BLACK);
	//m_clColorStaticTopBar.SetTextColor(RGB_COLOR_WHITE);
	//m_clColorStaticIdleLotTitle.SetBkColor(RGB_DLG_BG);
	//m_clColorStaticIdleLotTitle.SetTextColor(RGB_COLOR_WHITE);
	//m_clColorStaticIdleLotTitle.SetFont(&m_clFontSmall);
	
	m_clColorStaticIdleLotId.SetBkColor(RGB_DLG_BG);
	m_clColorStaticIdleLotId.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticIdleLotId.SetFont(&m_clFontSmall);

	m_clColorStaticIdleLotIdVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticIdleLotIdVal.SetFont(&m_clFontBig);
	m_clColorStaticIdleLotIdVal.SetFontSize(15);
	m_clColorStaticIdleLotIdVal.SetFontBold(TRUE);

	CFont m_font;
	// 폰트 설정 (Arial, 크기 20)
	m_font.CreatePointFont(135, _T("맑은 고딕"));  // 크기 20포인트는 200 단위 사용
	m_edtLotTitle.SetFont(&m_font);
	m_edtLotTitle.ModifyStyle(0, ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN);
}

BOOL CMessageLot::PreTranslateMessage(MSG* pMsg)
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
			return TRUE;
		}

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CMessageLot::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CMessageLot::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, RGB(10, 10, 10));// RGB_DLG_BG);
}

void CMessageLot::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//g_pCarAABonderDlg->EnableWindow(TRUE);
	CDialogEx::OnClose();
}


void CMessageLot::OnBnClickedCancel()	//CLOSE
{
	// TODO: Add your control notification handler code here
	if (nMode == eLGIT_OP_CALL)// 7 = LGIT_LOT_ID_FAIL
	{
		g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(OP_RECOGNIZED_OP_CALL_REPORT_10801);
	}
	//g_pCarAABonderDlg->EnableWindow(TRUE);
	CDialogEx::OnCancel();
}

void CMessageLot::OnBnClickedOk()		//RETRY
{
	// TODO: Add your control notification handler code here
	if (nMode == eLGIT_LOT_ID_FAIL || nMode == eLGIT_PP_SELECT)// 7 = LGIT_LOT_ID_FAIL
	{
		g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(OBJECT_ID_REPORT_10701);
	}


	//g_clMesCommunication[m_nUnit].m_dLotProcessingState
	//eScan = 1, eReady, eWait, eProcessing, eCompleted


	//CString reportData = _T("");
	//int nIndex = 0;
	//CString sData = _T("");

	//Operator ID
	/*m_clColorStaticIdleLotIdVal.GetWindowText(sData);
	if (sData.GetLength() < 1)
	{
		return;
	}
	reportData.AppendFormat(_T("%s,"), sData);*/

	//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(IDLE_REASON_REPORT_10402, reportData);
	//

	//g_pCarAABonderDlg->EnableWindow(TRUE);
	CDialogEx::OnOK();
}
void CMessageLot::setMode(int index, int nBuzzer)
{
	nMode = index;
	nBuzzerOnType = nBuzzer;
}

void CMessageLot::setLotID(CString lotId, CString lotIdVal)
{
	m_clColorStaticIdleLotId.SetWindowText(lotId);
	m_clColorStaticIdleLotId.Invalidate();

	m_clColorStaticIdleLotIdVal.SetWindowText(lotIdVal);
	m_clColorStaticIdleLotIdVal.Invalidate();
}

void CMessageLot::setContent(CString title)
{
	title.Replace(_T("\n"), _T("\r\n"));
	m_edtLotTitle.SetWindowText(title);
	m_edtLotTitle.Invalidate();
}

void CMessageLot::OnStnClickedStaticIdleLotIdVal()
{
	// TODO: Add your control notification handler code here
	/*CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		CString sData;
		m_clColorStaticIdleLotIdVal.GetWindowText(sData);
		pDlg->SetReturnValue(sData);
		if (pDlg->DoModal() == IDOK)
		{
			m_clColorStaticIdleLotIdVal.SetWindowText(pDlg->GetReturnValue());
		}

		delete pDlg;
	}*/
}


void CMessageLot::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here

	if (bShow == TRUE)
	{
		g_pCarAABonderDlg->EnableWindow(FALSE);

		if (nMode == eLGIT_OP_CALL)
		{
			this->SetWindowTextA(_T("LGIT_OP_CALL"));
		}
		if (nMode == eLGIT_LOT_ID_FAIL)
		{
			this->SetWindowTextA(_T("LGIT_LOT_ID_FAIL"));
		}
		if (nMode == eLGIT_PP_SELECT)
		{
			this->SetWindowTextA(_T("LGIT_PP_SELECT"));
		}
		if (nMode == eLGIT_LOT_ID_FAIL || nMode == eLGIT_PP_SELECT)
		{
			m_ColorbuttonRetry.ShowWindow(SW_SHOW);
		}
		else
		{
			m_ColorbuttonRetry.ShowWindow(SW_HIDE);
		}

		if (nMode == eLGIT_OP_CALL)
		{
			this->SetWindowTextA(_T("LGIT_OP_CALL"));
			m_ColorbuttonClose.SetWindowTextA(_T("Confirm"));
		}
		else
		{
			m_ColorbuttonClose.SetWindowTextA(_T("Close"));
		}


		if (nBuzzerOnType == 1)
		{
			//buzzer on
			g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
		}
	}
	else
	{
		g_pCarAABonderDlg->EnableWindow(TRUE);
		if (nBuzzerOnType == 1)
		{
			//buzzer off
			g_clDioControl.SetBuzzer(true, BUZZER_OFF);
		}
	}
}




void CMessageLot::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	CDialogEx::OnOK();
}


void CMessageLot::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnCancel();
}
