// IoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInspDlg.h"
#include "IoDlg.h"
#include "afxdialogex.h"

#define IO_CHANNEL_MAX 1
// IoDlg 대화 상자입니다.
static TCHAR* szInput[IO_CHANNEL_MAX][32] = { {
        _T("   EMERGENCY S/W1(MAIN)"),
        _T("   TRAY 흡탈착 압력계"),
        _T("   MAIN AIR"),
        _T("   DOOR SENSOR #1"),
        _T("   AREA SENSOR"),
        _T("   TRAY 상부감지 #1"),
        _T("   TRAY 상부감지 #2"),
        _T("   TRAY 상부감지 #3"),
        _T("   TRAY 상부감지 #4"),
        _T("   TRAY 하부감지 #1"),
        _T("   TRAY 하부감지 #2"),
        _T("   TRAY 하부감지 #3"),
        _T("   TRAY 하부감지 #4"),
        _T("   TRAY SLIDE RAIL 감지 #1"),
        _T("   TRAY SLIDE RAIL 감지 #2"),
        _T("   TRAY SLIDE RAIL 감지 #3"),
        _T("   TRAY SLIDE RAIL 감지 #4"),
        _T("   TRAY CLAMP 감지 #1"),
        _T("   TRAY UNCLAMP 감지 #1"),
        _T("   TRAY CLAMP 감지 #2"),
        _T("   TRAY UNCLAMP 감지 #2"),
        _T("   TRAY CLAMP 감지 #3"),
        _T("   TRAY UNCLAMP 감지 #3"),
        _T("   TRAY CLAMP 감지 #4"),
        _T("   TRAY UNCLAMP 감지 #4"),
        _T("   Socket ReTurn 감지"),
        _T("   Socket Turn 감지"),
        _T("   Socket Grip 후진 감지"),
        _T("   Socket Grip 전진 감지"),
        _T("   "),
        _T("   "),
        _T("   제품 감지")
    } 
};

static TCHAR* szOutput[IO_CHANNEL_MAX][32] = { {
        _T("   SOCKET 90도 회전 전진"),
        _T("   SOCKET 90도 회전 후진"),
        _T("   SOCKET 전진"),
        _T("   SOCKET 후진"),
        _T("   GRIPPER #1 UP"),
        _T("   GRIPPER #1 DOWN"),
        _T("   GRIPPER #1 전진"),
        _T("   GRIPPER #1 후진"),
        _T("   GRIPPER #2 UP"),
        _T("   GRIPPER #2 DOWN"),
        _T("   GRIPPER #2 전진"),
        _T("   GRIPPER #2 후진"),
        _T("   TRAY 탈착"),
        _T("   TRAY 흡착"),
        _T("   TRAY CLAMP #1 전진"),
        _T("   TRAY CLAMP #1 후진"),
        _T("   TRAY CLAMP #2 전진"),
        _T("   TRAY CLAMP #2 후진"),
        _T("   TRAY CLAMP #3 전진"),
        _T("   TRAY CLAMP #3 후진"),
        _T("   TRAY CLAMP #4 전진"),
        _T("   TRAY CLAMP #4 후진"),
        _T("   BUZZER S1"),
        _T("   BUZZER S2"),
        _T("   BUZZER S3"),
        _T("   BUZZER S4"),
        _T("   TOWER LAMP-R"),
        _T("   TOWER LAMP-Y"),
        _T("   TOWER LAMP-G"),
        _T("   "),
        _T("   "),
        _T("   ")
    }
};

IMPLEMENT_DYNAMIC(CIoDlg, CDialogEx)

CIoDlg::CIoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IO, pParent)
{
    m_nCurrentCh = 0;
}

CIoDlg::~CIoDlg()
{
}

void CIoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIoDlg, CDialogEx)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CIoDlg 메시지 처리기입니다.


void CIoDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 여기에 메시지 처리기 코드를 추가합니다.
                       // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
    CRect rect;
    GetClientRect(rect);
    dc.FillSolidRect(rect, MAIN_BG_COLOR);
}


BOOL CIoDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.
    setInterface();
    InitGridCtrl_In();
    InitGridCtrl_Out();
    IoInChChange();
    IoOutChChange();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CIoDlg::setInterface()
{
    //CCalibrationDlg* pFrame = (CCalibrationDlg*)AfxGetApp()->m_pMainWnd;

    //WINDOWPLACEMENT wndpl;

    //this->GetWindowPlacement(&wndpl);

    //wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos1.right + 100;
    //wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;
    //wndpl.rcNormalPosition.top = pFrame->m_rectCamDispPos1.top - SUB_DLG_OFFSET_Y + 10;
    //wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 85;
    //this->MoveWindow(&wndpl.rcNormalPosition);
    ////
    //m_IoTitleView
    //    .SetBkColor(M_COLOR_WHITE)
    //    .SetTextColor(M_COLOR_BLACK)
    //    .SetFontBold(TRUE)
    //    .SetFontSize(15);

    //CString str = "";
    //str.Format("Ch-%d", m_nCurrentCh);
    //m_IoTitleView.SetWindowText(str);

    //m_btn_Left.state = 150;
    //m_btn_Right.state = 150;
}

void CIoDlg::InitGridCtrl_In()
{
    CRect rect;
    CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_IO_IN_GRID);
    inRow = 33;// 65;//아래
    inCol = 3;//옆
    int margin = 4;// 20;
    int gridHeight = 25;
    int gridWidth1 = 60;
    int gridWidth2 = 300;
    int gridWidth3 = 60;
    int totalWidth = gridWidth1 + gridWidth2 + gridWidth3;
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*inRow) + 4;	//rect.bottom = (gridHeight*inRow) +margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

    GetDlgItem(IDC_STATIC_IO_IN_GRID)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGrid_IO_In.Create(rect, this, IDC_STATIC_IO_IN_GRID, WS_TABSTOP | WS_VISIBLE);

    m_clGrid_IO_In.SetTextBkColor(GRID_COLOR_WHITE);
    m_clGrid_IO_In.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGrid_IO_In.SetFixedTextColor(GRID_COLOR_WHITE);
    m_clGrid_IO_In.SetReference_Setting();
    m_clGrid_IO_In.EnableSelection(FALSE);
    m_clGrid_IO_In.SetRowCount(inRow);
    m_clGrid_IO_In.SetColumnCount(inCol);
    m_clGrid_IO_In.SetFixedRowCount(1);
    m_clGrid_IO_In.SetFixedColumnCount(1);
    CString tmpStr = "";


    m_clGrid_IO_In.SetItemText(0, 0, _T("No"));
    m_clGrid_IO_In.SetItemText(0, 1, "입력 Comment");
    m_clGrid_IO_In.SetItemText(0, 2, "입력");
    //
    for (int i = 0; i<inRow - 1; i++)
    {
        tmpStr.Format("%d", i + 1);
        m_clGrid_IO_In.SetItemText(i + 1, 0, tmpStr);
    }
    //
    /*m_clGrid_IO_In.SetItemText(1, 1, "EMERGENCY S/W #1");
    m_clGrid_IO_In.SetItemText(5, 1, "MAIN AIR");
    m_clGrid_IO_In.SetItemText(7, 1, "DOOR SENSOR #1");
    m_clGrid_IO_In.SetItemText(8, 1, "DOOR SENSOR #2");
    m_clGrid_IO_In.SetItemText(9, 1, "DOOR SENSOR #3");
    m_clGrid_IO_In.SetItemText(10, 1, "DOOR SENSOR #4");
    m_clGrid_IO_In.SetItemText(11, 1, "DOOR SENSOR #5");
    m_clGrid_IO_In.SetItemText(12, 1, "DOOR SENSOR #6");
    m_clGrid_IO_In.SetItemText(19, 1, "UV - ON");
    m_clGrid_IO_In.SetItemText(25, 1, "EPOXY 토출 ON");*/
    //m_clGrid_IO_In.SetItemText(31, 1, "LIGHT CURTAIN");
    //-============================================================================================================
    //-32
    /*m_clGrid_IO_In.SetItemText(33, 1, "SENSOR CONTACT");
    m_clGrid_IO_In.SetItemText(34, 1, "HOLDER GRIP 전진");
    m_clGrid_IO_In.SetItemText(35, 1, "HOLDER GRIP 후진");
    m_clGrid_IO_In.SetItemText(36, 1, "DOOR OPEN");
    m_clGrid_IO_In.SetItemText(37, 1, "DOOR CLOSE");
    m_clGrid_IO_In.SetItemText(39, 1, "START PB");
    m_clGrid_IO_In.SetItemText(40, 1, "DOOR PB");
    m_clGrid_IO_In.SetItemText(50, 1, "LENS GRIP 후진");
    m_clGrid_IO_In.SetItemText(51, 1, "LENS GRIP 전진");
    m_clGrid_IO_In.SetItemText(52, 1, "PCB GRIP 후진");
    m_clGrid_IO_In.SetItemText(53, 1, "PCB GRIP 전진");
    m_clGrid_IO_In.SetItemText(57, 1, "클립 소켓 CLOSE");
    m_clGrid_IO_In.SetItemText(62, 1, "LASER/CAM 후진");
    m_clGrid_IO_In.SetItemText(63, 1, "LASER/CAM 전진");
    */

    //
    int i = 0, j = 0;
    for (i = 0; i < inRow; i++)
    {
        m_clGrid_IO_In.SetRowHeight(i, gridHeight);

        for (j = 0; j < inCol; j++)
        {
            m_clGrid_IO_In.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGrid_IO_In.SetColumnWidth(j, gridWidth1);
                }
                else if (j == 1) {
                    m_clGrid_IO_In.SetColumnWidth(j, gridWidth2);
                }
                else {
                    m_clGrid_IO_In.SetColumnWidth(j, gridWidth3);
                }
            }
        }
    }
    m_clGrid_IO_In.Invalidate();
}
void CIoDlg::InitGridCtrl_Out()
{
    CRect rect;
    CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_IO_OUT_GRID);
    outRow = 33;// 65;//아래
    outCol = 3;//옆
    inRow = 33;// 65;//아래
    inCol = 3;//옆
    int margin = 4;// 20;
    int gridHeight = 25;
    int gridWidth1 = 60;
    int gridWidth2 = 300;
    int gridWidth3 = 60;
    int totalWidth = gridWidth1 + gridWidth2 + gridWidth3;
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*inRow) + 4;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

    GetDlgItem(IDC_STATIC_IO_OUT_GRID)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGrid_IO_Out.Create(rect, this, IDC_STATIC_IO_OUT_GRID, WS_TABSTOP | WS_VISIBLE);

    m_clGrid_IO_Out.SetTextBkColor(GRID_COLOR_WHITE);
    m_clGrid_IO_Out.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGrid_IO_Out.SetFixedTextColor(GRID_COLOR_WHITE);
    m_clGrid_IO_Out.SetReference_Setting();
    m_clGrid_IO_Out.EnableSelection(FALSE);
    m_clGrid_IO_Out.SetRowCount(outRow);
    m_clGrid_IO_Out.SetColumnCount(outCol);
    m_clGrid_IO_Out.SetFixedRowCount(1);
    m_clGrid_IO_Out.SetFixedColumnCount(1);

    CString tmpStr = "";


    m_clGrid_IO_Out.SetItemText(0, 0, _T("No"));
    m_clGrid_IO_Out.SetItemText(0, 1, "출력 Comment");
    m_clGrid_IO_Out.SetItemText(0, 2, "출력");

    //
    for (int i = 0; i<outRow - 1; i++)
    {
        tmpStr.Format("%d", i + 1);
        m_clGrid_IO_Out.SetItemText(i + 1, 0, tmpStr);
    }
    //
    //m_clGrid_IO_Out.SetItemText(8, 1, "TOWER LAMP - R");	
    //m_clGrid_IO_Out.SetItemText(9, 1, "TOWER LAMP - Y");	
    //m_clGrid_IO_Out.SetItemText(10, 1, "TOWER LAMP - G");	
    ////
    //m_clGrid_IO_Out.SetItemText(12, 1, "BUZZER1");
    //m_clGrid_IO_Out.SetItemText(13, 1, "BUZZER2");	
    //m_clGrid_IO_Out.SetItemText(14, 1, "BUZZER3");	
    //m_clGrid_IO_Out.SetItemText(15, 1, "BUZZER4");																//												//
    //m_clGrid_IO_Out.SetItemText(18, 1, "UV - ON");				
    //m_clGrid_IO_Out.SetItemText(19, 1, "UV - EMG");			
    //
    //m_clGrid_IO_Out.SetItemText(24, 1, "EPOXY 토출 ON");			
    /*m_clGrid_IO_Out.SetItemText(32, 1, "HOLDER GRIP 후진");
    m_clGrid_IO_Out.SetItemText(33, 1, "HOLDER GRIP 전진");
    m_clGrid_IO_Out.SetItemText(34, 1, "DOOR CLOSE");
    m_clGrid_IO_Out.SetItemText(35, 1, "DOOR OPEN");
    m_clGrid_IO_Out.SetItemText(36, 1, "LENS GRIP 후진");
    m_clGrid_IO_Out.SetItemText(37, 1, "LENS GRIP 전진");
    m_clGrid_IO_Out.SetItemText(38, 1, "PCB GRIP 후진");
    m_clGrid_IO_Out.SetItemText(39, 1, "PCB GRIP 전진");
    m_clGrid_IO_Out.SetItemText(42, 1, "LASER/CAM 후진");
    m_clGrid_IO_Out.SetItemText(43, 1, "LASER/CAM 전진");
    m_clGrid_IO_Out.SetItemText(48, 1, "START PB");
    m_clGrid_IO_Out.SetItemText(49, 1, "DOOR PB");*/


    //
    int i = 0, j = 0;
    for (i = 0; i < outRow; i++)
    {
        m_clGrid_IO_Out.SetRowHeight(i, gridHeight);

        for (j = 0; j < outCol; j++)
        {
            m_clGrid_IO_Out.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGrid_IO_Out.SetColumnWidth(j, gridWidth1);
                }
                else if (j == 1) {
                    m_clGrid_IO_Out.SetColumnWidth(j, gridWidth2);
                }
                else {
                    m_clGrid_IO_Out.SetColumnWidth(j, gridWidth3);
                }
            }
        }
    }
    m_clGrid_IO_Out.Invalidate();
}
void CIoDlg::IoInChChange()
{
    int i = 0;

    for (i = 1; i < 33; i++)
    {
        m_clGrid_IO_In.SetItemText(i, 1, szInput[m_nCurrentCh][i - 1]);
        if (_tcslen(szInput[m_nCurrentCh][i - 1]) <= 0)
        {
            m_clGrid_IO_In.SetItemBkColor(i, 2, GRID_COLOR_DIO_IN);// RGB_COLOR_WHITE);
        }
    }

    m_clGrid_IO_In.Invalidate();
}

void CIoDlg::IoOutChChange()
{
    int i = 0;

    for (i = 1; i < 33; i++)
    {
        m_clGrid_IO_Out.SetItemText(i, 1, szOutput[m_nCurrentCh][i - 1]);
        if (_tcslen(szOutput[m_nCurrentCh][i - 1]) <= 0)
        {
            m_clGrid_IO_Out.SetItemBkColor(i, 2, GRID_COLOR_DIO_OUT);// RGB_COLOR_WHITE);
        }
    }

    m_clGrid_IO_Out.Invalidate();
}