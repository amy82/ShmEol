// KeyBoardDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "KeyBoardDlg.h"
#include "afxdialogex.h"


// CKeyBoardDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CKeyBoardDlg, CDialogEx)

CKeyBoardDlg::CKeyBoardDlg(int nMaxCount, bool bPasswd, CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyBoardDlg::IDD, pParent)
{
	m_nMaxCount = nMaxCount;
	m_bPasswd = bPasswd;
}

CKeyBoardDlg::~CKeyBoardDlg()
{
}

void CKeyBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_KEYBOARD_TOP_BAR, m_clColorStaticTopBar);
	DDX_Control(pDX, IDC_STATIC_KEYBOARD_VAL, m_clColorStaticVal);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM0, m_clColorButtonNum[0]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM1, m_clColorButtonNum[1]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM2, m_clColorButtonNum[2]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM3, m_clColorButtonNum[3]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM4, m_clColorButtonNum[4]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM5, m_clColorButtonNum[5]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM6, m_clColorButtonNum[6]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM7, m_clColorButtonNum[7]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM8, m_clColorButtonNum[8]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_NUM9, m_clColorButtonNum[9]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_A, m_clColorButtonAlpha[0]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_B, m_clColorButtonAlpha[1]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_C, m_clColorButtonAlpha[2]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_D, m_clColorButtonAlpha[3]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_E, m_clColorButtonAlpha[4]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_F, m_clColorButtonAlpha[5]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_G, m_clColorButtonAlpha[6]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_H, m_clColorButtonAlpha[7]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_I, m_clColorButtonAlpha[8]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_J, m_clColorButtonAlpha[9]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_K, m_clColorButtonAlpha[10]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_L, m_clColorButtonAlpha[11]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_M, m_clColorButtonAlpha[12]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_N, m_clColorButtonAlpha[13]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_O, m_clColorButtonAlpha[14]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_P, m_clColorButtonAlpha[15]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_Q, m_clColorButtonAlpha[16]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_R, m_clColorButtonAlpha[17]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_S, m_clColorButtonAlpha[18]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_T, m_clColorButtonAlpha[19]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_U, m_clColorButtonAlpha[20]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_V, m_clColorButtonAlpha[21]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_W, m_clColorButtonAlpha[22]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_X, m_clColorButtonAlpha[23]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_Y, m_clColorButtonAlpha[24]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_APB_Z, m_clColorButtonAlpha[25]);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_DASH, m_clColorButtonDash);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_DOT, m_clColorButtonDot);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_DEL, m_clColorButtonDel);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_ENTER, m_clColorButtonEnter);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_CANCEL, m_clColorButtonCancel);
	DDX_Control(pDX, IDC_BUTTON_KEYBOARD_CLEAR, m_clColorButtonClear);
}


BEGIN_MESSAGE_MAP(CKeyBoardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_KEYBOARD_DASH, &CKeyBoardDlg::OnBnClickedButtonKeyboardDash)
	ON_BN_CLICKED(IDC_BUTTON_KEYBOARD_DOT, &CKeyBoardDlg::OnBnClickedButtonKeyboardDot)
	ON_BN_CLICKED(IDC_BUTTON_KEYBOARD_DEL, &CKeyBoardDlg::OnBnClickedButtonKeyboardDel)
	ON_BN_CLICKED(IDC_BUTTON_KEYBOARD_ENTER, &CKeyBoardDlg::OnBnClickedButtonKeyboardEnter)
	ON_BN_CLICKED(IDC_BUTTON_KEYBOARD_CANCEL, &CKeyBoardDlg::OnBnClickedButtonKeyboardCancel)
	ON_BN_CLICKED(IDC_BUTTON_KEYBOARD_CLEAR, &CKeyBoardDlg::OnBnClickedButtonKeyboardClear)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_KEYBOARD_NUM0, IDC_BUTTON_KEYBOARD_NUM9, &CKeyBoardDlg::OnBnClickedButtonKeyboardNum)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_KEYBOARD_APB_A, IDC_BUTTON_KEYBOARD_APB_Z, &CKeyBoardDlg::OnBnClickedButtonKeyboardAlpha)
END_MESSAGE_MAP()


// CKeyBoardDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnPaint()
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
BOOL CKeyBoardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CKeyBoardDlg::SetReturnValue(CString sTemp)
{ 
	m_sVal.Format(_T("%s"), sTemp);
	
};
//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::InitCtrl()
{
	int i;

	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticTopBar.SetBkColor(RGB_COLOR_BLACK);
	m_clColorStaticTopBar.SetTextColor(RGB_COLOR_WHITE);
	
	if (m_bPasswd == true)
	{
		m_clColorStaticTopBar.SetWindowText(_T("     KEYBOARD (비밀번호를 입력하세요!!!)"));
	}
	else
	{
		m_clColorStaticTopBar.SetWindowText(_T("     KEYBOARD"));
	}

	m_clColorStaticVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticVal.SetFont(&m_clFontBig);	

	m_clColorStaticVal.SetWindowText(m_sVal);
	m_clColorStaticVal.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : -
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardDash()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_sVal.GetLength() > m_nMaxCount)
		return;

	m_sVal += _T('-');
	m_sHiddenVal += _T('*');

	if (m_bPasswd == true)
		m_clColorStaticVal.SetWindowText(m_sHiddenVal);
	else
		m_clColorStaticVal.SetWindowText(m_sVal);
}

//-----------------------------------------------------------------------------
//
//	버튼 : .
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardDot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_sVal.GetLength() > m_nMaxCount)
		return;

	m_sVal += _T('.');
	m_sHiddenVal += _T('*');

	if (m_bPasswd == true)
		m_clColorStaticVal.SetWindowText(m_sHiddenVal);
	else
		m_clColorStaticVal.SetWindowText(m_sVal);
}

//-----------------------------------------------------------------------------
//
//	버튼 : DEL
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_sVal.GetLength() > 0)
	{
		m_sVal = m_sVal.Left(m_sVal.GetLength() - 1);
		m_sHiddenVal = m_sHiddenVal.Left(m_sHiddenVal.GetLength() - 1);

		if (m_bPasswd == true)
			m_clColorStaticVal.SetWindowText(m_sHiddenVal);
		else
			m_clColorStaticVal.SetWindowText(m_sVal);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : ENTER
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardEnter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDOK);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CANCEL
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDNO);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLEAR
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_sVal = _T("");
	m_sHiddenVal = _T("");

	if (m_bPasswd == true)
		m_clColorStaticVal.SetWindowText(m_sHiddenVal);
	else
		m_clColorStaticVal.SetWindowText(m_sVal);
}

//-----------------------------------------------------------------------------
//
//	버튼 : 0 ~ 9
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardNum(UINT nID)
{
	int nIndex;

	if (m_sVal.GetLength() > m_nMaxCount)
		return;

	nIndex = nID - IDC_BUTTON_KEYBOARD_NUM0;

	switch(nIndex)
	{
	case 0:		m_sVal += _T('0');	m_sHiddenVal += _T('*');		break;
	case 1:		m_sVal += _T('1');	m_sHiddenVal += _T('*');		break;
	case 2:		m_sVal += _T('2');	m_sHiddenVal += _T('*');		break;
	case 3:		m_sVal += _T('3');	m_sHiddenVal += _T('*');		break;
	case 4:		m_sVal += _T('4');	m_sHiddenVal += _T('*');		break;
	case 5:		m_sVal += _T('5');	m_sHiddenVal += _T('*');		break;
	case 6:		m_sVal += _T('6');	m_sHiddenVal += _T('*');		break;
	case 7:		m_sVal += _T('7');	m_sHiddenVal += _T('*');		break;
	case 8:		m_sVal += _T('8');	m_sHiddenVal += _T('*');		break;
	case 9:		m_sVal += _T('9');	m_sHiddenVal += _T('*');		break;
	}

	if (m_bPasswd == true)
		m_clColorStaticVal.SetWindowText(m_sHiddenVal);
	else
		m_clColorStaticVal.SetWindowText(m_sVal);
}

//-----------------------------------------------------------------------------
//
//	버튼 : A ~ Z
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnBnClickedButtonKeyboardAlpha(UINT nID)
{
	int nIndex;

	if (m_sVal.GetLength() > m_nMaxCount)
		return;

	nIndex = nID - IDC_BUTTON_KEYBOARD_APB_A;

	switch (nIndex)
	{
	case 0:		m_sVal += _T('A');	m_sHiddenVal += _T('*');		break;
	case 1:		m_sVal += _T('B');	m_sHiddenVal += _T('*');		break;
	case 2:		m_sVal += _T('C');	m_sHiddenVal += _T('*');		break;
	case 3:		m_sVal += _T('D');	m_sHiddenVal += _T('*');		break;
	case 4:		m_sVal += _T('E');	m_sHiddenVal += _T('*');		break;
	case 5:		m_sVal += _T('F');	m_sHiddenVal += _T('*');		break;
	case 6:		m_sVal += _T('G');	m_sHiddenVal += _T('*');		break;
	case 7:		m_sVal += _T('H');	m_sHiddenVal += _T('*');		break;
	case 8:		m_sVal += _T('I');	m_sHiddenVal += _T('*');		break;
	case 9:		m_sVal += _T('J');	m_sHiddenVal += _T('*');		break;
	case 10:	m_sVal += _T('K');	m_sHiddenVal += _T('*');		break;
	case 11:	m_sVal += _T('L');	m_sHiddenVal += _T('*');		break;
	case 12:	m_sVal += _T('M');	m_sHiddenVal += _T('*');		break;
	case 13:	m_sVal += _T('N');	m_sHiddenVal += _T('*');		break;
	case 14:	m_sVal += _T('O');	m_sHiddenVal += _T('*');		break;
	case 15:	m_sVal += _T('P');	m_sHiddenVal += _T('*');		break;
	case 16:	m_sVal += _T('Q');	m_sHiddenVal += _T('*');		break;
	case 17:	m_sVal += _T('R');	m_sHiddenVal += _T('*');		break;
	case 18:	m_sVal += _T('S');	m_sHiddenVal += _T('*');		break;
	case 19:	m_sVal += _T('T');	m_sHiddenVal += _T('*');		break;
	case 20:	m_sVal += _T('U');	m_sHiddenVal += _T('*');		break;
	case 21:	m_sVal += _T('V');	m_sHiddenVal += _T('*');		break;
	case 22:	m_sVal += _T('W');	m_sHiddenVal += _T('*');		break;
	case 23:	m_sVal += _T('X');	m_sHiddenVal += _T('*');		break;
	case 24:	m_sVal += _T('Y');	m_sHiddenVal += _T('*');		break;
	case 25:	m_sVal += _T('Z');	m_sHiddenVal += _T('*');		break;
	}

	if (m_bPasswd == true)
		m_clColorStaticVal.SetWindowText(m_sHiddenVal);
	else
		m_clColorStaticVal.SetWindowText(m_sVal);
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CKeyBoardDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CKeyBoardDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		//if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			//return TRUE;

		switch (pMsg->wParam)
		{
		case 0x08:
			this->OnBnClickedButtonKeyboardDel();
			break;
		case 0x6D:
			this->OnBnClickedButtonKeyboardDash();
			break;
		case 0x6E:
		case 0xBE:
			this->OnBnClickedButtonKeyboardDot();
			break;
		case VK_ESCAPE:
			this->OnBnClickedButtonKeyboardCancel();
			break;
		case VK_RETURN:
			this->OnBnClickedButtonKeyboardEnter();
			break;
		case 0x30:
		case 0x60:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM0);
			break;
		case 0x31:
		case 0x61:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM1);
			break;
		case 0x32:
		case 0x62:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM2);
			break;
		case 0x33:
		case 0x63:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM3);
			break;
		case 0x34:
		case 0x64:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM4);
			break;
		case 0x35:
		case 0x65:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM5);
			break;
		case 0x36:
		case 0x66:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM6);
			break;
		case 0x37:
		case 0x67:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM7);
			break;
		case 0x38:
		case 0x68:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM8);
			break;
		case 0x39:
		case 0x69:
			this->OnBnClickedButtonKeyboardNum(IDC_BUTTON_KEYBOARD_NUM9);
			break;
		case 0x41:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_A);
			break;
		case 0x42:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_B);
			break;
		case 0x43:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_C);
			break;
		case 0x44:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_D);
			break;
		case 0x45:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_E);
			break;
		case 0x46:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_F);
			break;
		case 0x47:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_G);
			break;
		case 0x48:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_H);
			break;
		case 0x49:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_I);
			break;
		case 0x4A:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_J);
			break;
		case 0x4B:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_K);
			break;
		case 0x4C:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_L);
			break;
		case 0x4D:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_M);
			break;
		case 0x4E:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_N);
			break;
		case 0x4F:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_O);
			break;
		case 0x50:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_P);
			break;
		case 0x51:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_Q);
			break;
		case 0x52:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_R);
			break;
		case 0x53:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_S);
			break;
		case 0x54:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_T);
			break;
		case 0x55:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_U);
			break;
		case 0x56:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_V);
			break;
		case 0x57:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_W);
			break;
		case 0x58:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_X);
			break;
		case 0x59:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_Y);
			break;
		case 0x5A:
			this->OnBnClickedButtonKeyboardAlpha(IDC_BUTTON_KEYBOARD_APB_Z);
			break;
		}
	}
	else if (pMsg->message == WM_KEYUP)
	{

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

