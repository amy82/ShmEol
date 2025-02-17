// DioDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "DioDlg.h"
#include "afxdialogex.h"

#define WM_UI_TIMER			WM_USER + 999

// CDioDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDioDlg, CDialogEx)

CDioDlg::CDioDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDioDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;

	m_dwPrevDIn = -1;
	m_dwPrevDOut = -1;
}

CDioDlg::~CDioDlg()
{
}

void CDioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DIO_TITLE, m_clColorStaticTitle);
}


BEGIN_MESSAGE_MAP(CDioDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_GRID_DIO_OUTPUT, &CDioDlg::OnNMDblClickedDOut)
END_MESSAGE_MAP()


// CDioDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CDioDlg::OnPaint()
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
BOOL CDioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();
	
	// 그리드 컨트롤 초기화
    this->InitInGridCtrl();
    this->InitOutGridCtrl();

	// DIO 명칭 표시
	this->ShowDIOName();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CDioDlg::InitCtrl()
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
}

//-----------------------------------------------------------------------------
//
// 그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CDioDlg::InitInGridCtrl()
{
    TCHAR* pszColIn[] = { _T("no"), _T("Input"), _T("Signal") };
    CRect rect;
    CString StrTemp;
    int i, j;
    int DLG = IDC_STATIC_GRID_DIO_INPUT;
    int GridRow = 33;//아래
    int GridCol = 3;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 250;
    int gridWidth2 = 80;
    int totalWidth = gridWidth1 + (gridWidth2*(GridCol - 1));
    //
    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*GridRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.
    ///////////////////////////////////////////////////////////////////////////
    //
    //	GRID INPUT
    //

    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridCtrlDIn.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridCtrlDIn.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridCtrlDIn.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridCtrlDIn.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridCtrlDIn.SetReference_Setting();
    m_clGridCtrlDIn.EnableSelection(FALSE);

    m_clGridCtrlDIn.SetRowCount(GridRow);
    m_clGridCtrlDIn.SetColumnCount(GridCol);
    m_clGridCtrlDIn.SetFixedRowCount(1);
    m_clGridCtrlDIn.SetFixedColumnCount(1);

    for (i = 0; i < GridRow; i++)
    {
        m_clGridCtrlDIn.SetRowHeight(i, gridHeight);
        if (i > 0)
            m_clGridCtrlDIn.SetItemText(i, 0, i);

        for (j = 0; j < GridCol; j++)
        {
            if (i == 0)
            {
                m_clGridCtrlDIn.SetItemText(i, j, pszColIn[j]);

                if (j == 1)
                {
                    m_clGridCtrlDIn.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridCtrlDIn.SetColumnWidth(j, gridWidth2);
                }
            }

            m_clGridCtrlDIn.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CDioDlg::InitOutGridCtrl()
{
    TCHAR* pszColOut[] = { _T("No"),  _T("Output"), _T("Signal") };
    CRect rect;
    CString StrTemp;
    int i, j;
    int DLG = IDC_STATIC_GRID_DIO_OUTPUT;
    int GridRow = 33;//아래
    int GridCol = 3;//옆
    //
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 250;
    int gridWidth2 = 80;
    int totalWidth = gridWidth1 + (gridWidth2*(GridCol - 1));
    //
    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*GridRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.
    ///////////////////////////////////////////////////////////////////////////
    //
    //	GRID OUTPUT
    //
    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridCtrlDOut.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridCtrlDOut.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridCtrlDOut.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridCtrlDOut.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridCtrlDOut.SetReference_Setting();
    m_clGridCtrlDOut.EnableSelection(FALSE);

    m_clGridCtrlDOut.SetRowCount(GridRow);
    m_clGridCtrlDOut.SetColumnCount(GridCol);
    m_clGridCtrlDOut.SetFixedRowCount(1);
    m_clGridCtrlDOut.SetFixedColumnCount(1);

    for (i = 0; i < GridRow; i++)
    {
        m_clGridCtrlDOut.SetRowHeight(i, gridHeight);
        if (i > 0)
            m_clGridCtrlDOut.SetItemText(i, 0, i);

        for (j = 0; j < GridCol; j++)
        {
            if (i == 0)
            {
                m_clGridCtrlDOut.SetItemText(i, j, pszColOut[j]);

                if (j == 1)
                {
                    m_clGridCtrlDOut.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridCtrlDOut.SetColumnWidth(j, gridWidth2);
                }
            }

            m_clGridCtrlDOut.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}

//-----------------------------------------------------------------------------
//
//	DIO 명칭 표시
//
//-----------------------------------------------------------------------------
void CDioDlg::ShowDIOName()
{
	TCHAR* pszIn[] = {

		_T("DOOR OPEN LEFT"),				//1
		_T("DOOR OPEN BACK"),
		_T("DOOR OPEN RIGHT"),
		_T("AREA SENSOR"),
		_T(""),							//5
		_T(""),
		_T(""),
		_T("	"),
		_T("PCB VACUUM"),				//9
		_T("제품 감지"),				//10 							
		_T("START PB LEFT"),
		_T("START PB RIGHT"),
		_T("PCB VACUUM PB"),
		_T("    "),
		_T("	"),						//15					  
		_T("    "),						//16
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),						//20
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),						//25
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),
		_T("    "),						//30
		_T("    "),
		_T("    ")
	};

	TCHAR* pszOut[] = { 
		_T("TOWER LAMP-R"),
		_T("TOWER LAMP-Y"),
		_T("TOWER LAMP-G"),					 //1
		_T("BUZZER S1"),
		_T("BUZZER S2"),							//5
		_T("BUZZER S3"),
		_T("BUZZER S4"),
		_T("	"),
		_T("PCB 흡착"),
		_T("DOOR UNLOCK ALL"),			//10
		_T("START PB LED LEFT"),
		_T("START PB LED RIGHT"),
		_T("PCB VACUUM PB LED"),
		_T("PCB 탈착"),
		_T(""),
		_T("	"),					//16
		_T(""),
		_T("	"),
		_T("	"),
		_T("	"),						//20
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),						//25
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),
		_T("	"),		//30
		_T("	"),		//31
		_T("	")		//32	

	};

	int i;
	TCHAR szNo[SIZE_OF_100BYTE];

	for (i = 0; i < 32; i++)
	{
		/*_stprintf_s(szNo, SIZE_OF_100BYTE, _T("DI-%03X"), (m_nUnit * 32) + i);
		m_clGridCtrlDIn.SetItemText(i + 1, 1, szNo);*/

		m_clGridCtrlDIn.SetItemText(i + 1, 1, pszIn[i]);

		/*_stprintf_s(szNo, SIZE_OF_100BYTE, _T("DO-%03X"), (m_nUnit * 32) + i);
		m_clGridCtrlDOut.SetItemText(i + 1, 1, szNo);*/

		m_clGridCtrlDOut.SetItemText(i + 1, 1, pszOut[i]);
	}
	m_clGridCtrlDIn.Invalidate();
	m_clGridCtrlDOut.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CDioDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];

	m_nUnit = nUnit;
	_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[DIO]")); //, m_nUnit + 1);
	GetDlgItem(IDC_STATIC_DIO_TITLE)->SetWindowText(szTitle);

	this->ShowDIOName();
}

//-----------------------------------------------------------------------------
//
// OnShowWindow
//
//-----------------------------------------------------------------------------
void CDioDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		SetTimer(WM_UI_TIMER, 100, NULL);
	}
	else
	{
		KillTimer(WM_UI_TIMER);
	}
}

//-----------------------------------------------------------------------------
//
//	OnTimer
//
//-----------------------------------------------------------------------------
void CDioDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
		
	case WM_UI_TIMER:
		// INPUT 상태 표시
		this->ShowDInState();
		// OUT 상태표시
		this->ShowDOutState();
		break;
		
	}
	CDialogEx::OnTimer(nIDEvent);
}

//-----------------------------------------------------------------------------
//
//	INPUT 상태 표시
//
//-----------------------------------------------------------------------------
void CDioDlg::ShowDInState()
{
	DWORD dwState;
	CString sData = _T("");
	int i;

	dwState = g_clDioControl.GetDIn(m_nUnit);


	if (dwState != m_dwPrevDIn)
	{
		m_dwPrevDIn = dwState;

		for (i = 0; i < 32; i++)
		{
			sData = m_clGridCtrlDIn.GetItemText(i + 1, 1);
			if ((dwState & 0x01) == 0x01)
			{				
				m_clGridCtrlDIn.SetItemBkColor(i + 1, 2, RGB_COLOR_GREEN);
			}
			else
			{
				m_clGridCtrlDIn.SetItemBkColor(i + 1, 2, RGB_COLOR_WHITE);
			}

			dwState = dwState >> 1;
		}

		m_clGridCtrlDIn.Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//	OUTUPT 상태 표시
//
//-----------------------------------------------------------------------------
void CDioDlg::ShowDOutState()
{
	DWORD dwState;
	CString sData = _T("");	
	int i = 0;
	int j = 0;

	//dwState = g_clDioControl.GetDOut(0);//m_nUnit); GetByteOut
	for (j = 0; j < 4; j++)
	{
		dwState = g_clDioControl.GetByteOut(0,j);//m_nUnit); 
		if (dwState != m_dwPrevDOut)
		{
			m_dwPrevDOut = dwState;
			for (i = 0; i < 8; i++)//for (i = 0; i < 32; i++)
			{
				//sData = m_clGridCtrlDOut.GetItemText((i + 1) + (j * 8), 1);

				if ((dwState & 0x01) == 0x01)
				{
					m_clGridCtrlDOut.SetItemBkColor((i + 1) + (j * 8), 2, RGB_COLOR_GREEN);
				}
				else
				{
					m_clGridCtrlDOut.SetItemBkColor((i + 1) + (j * 8), 2, RGB_COLOR_WHITE);
				}

				dwState = dwState >> 1;
			}

			m_clGridCtrlDOut.Invalidate();
		}
	}


	sData.Empty();
}

//-----------------------------------------------------------------------------
//
//	D-OUT 그리드 더블클릭
//
//-----------------------------------------------------------------------------
void CDioDlg::OnNMDblClickedDOut(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;	
	int nRow, nCol;
	DWORD dwOut = 0;
	DWORD dwPivot = 0x01;
	int nModuleNo = 0;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	int mByteOffset = (nRow - 1) / 8;


	nModuleNo = 1;

	int m_nCurrentCh = 0;
	//dwOut = g_clDioControl.GetDOut(0); 
	dwOut = g_clDioControl.GetByteOut(m_nCurrentCh, mByteOffset);

	if (nRow >= 1 && nCol >= 1)
	{
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
		nRow = ((nRow - 1) % 8) + 1;
		dwPivot = (dwPivot << (nRow - 1));

		if ((dwOut & dwPivot) == dwPivot)
		{
			dwOut &= ~dwPivot;
		}
		else
		{
			dwOut |= dwPivot;
		}

		nModuleNo = (m_nCurrentCh * 2) + 1;
		g_clDioControl.ByteWriteDOut(nModuleNo, mByteOffset, dwOut);
		////g_clDioControl.WriteDOut(nModuleNo, dwOut);
	}

}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CDioDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
