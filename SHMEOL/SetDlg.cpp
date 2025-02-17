// SetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInspDlg.h"
#include "SetDlg.h"
#include "afxdialogex.h"


// CSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INFO, pParent)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_LOAD, m_Btn_Info_Load);
    DDX_Control(pDX, IDC_BUTTON_SAVE, m_Btn_Info_Save);
    DDX_Control(pDX, IDC_BUTTON_OPER, m_Btn_Oper);
    DDX_Control(pDX, IDC_BUTTON_ENG, m_Btn_Eng);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CSetDlg 메시지 처리기입니다.


void CSetDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 여기에 메시지 처리기 코드를 추가합니다.
                       // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
    CRect rect;
    GetClientRect(rect);
    dc.FillSolidRect(rect, MAIN_BG_COLOR);
}


BOOL CSetDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
