// AlarmDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "AlarmDlg.h"
#include "afxdialogex.h"


// CAlarmDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAlarmDlg, CDialogEx)

CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlarmDlg::IDD, pParent)
{
	int i;

	m_nUnit = UNIT_AA1;
	

	for(i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_nAlarmPage[i] = 0;
		m_nAlarmIndex[i] = 0;
		m_nCurrentPage[i] = 0;
		m_pAlarmList[i] = NULL;
	}


	m_sAlarmLog = _T("");
}

CAlarmDlg::~CAlarmDlg()
{
	int i = 0;
	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		if (m_pAlarmList[i] != NULL)
		{
			delete[] m_pAlarmList[i];
			m_pAlarmList[i] = NULL;
		}
	}
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ALARM_TITLE, m_clColorStaticTitle);
	//DDX_Control(pDX, IDC_LIST_ALARM_LIST, m_clListCtrlAlarm);
	DDX_Control(pDX, IDC_BUTTON_ALARM_PREV, m_clColorButtonPrev);
	DDX_Control(pDX, IDC_BUTTON_ALARM_NEXT, m_clColorButtonNext);
	DDX_Control(pDX, IDC_BUTTON_ALARM_CLEAR, m_clColorButtonClear);
	DDX_Control(pDX, IDC_STATIC_ALARM_PAGE, m_clColorStaticPage);
}


BEGIN_MESSAGE_MAP(CAlarmDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ALARM_PREV, &CAlarmDlg::OnBnClickedButtonAlarmPrev)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_NEXT, &CAlarmDlg::OnBnClickedButtonAlarmNext)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_CLEAR, &CAlarmDlg::OnBnClickedButtonAlarmClear)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CAlarmDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CAlarmDlg::OnPaint()
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
BOOL CAlarmDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	this->InitGridCtrl_Alarm();

	int i = 0;
	int j = 0;
	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_pAlarmList[i] = new CString[MAX_ALARM_LIST_IN_PAGE * MAX_PAGE_COUNT];
		for (j = 0; j < MAX_ALARM_LIST_IN_PAGE * MAX_PAGE_COUNT; j++)
		{
			m_pAlarmList[i][j].Empty();
		}
	}

	this->InitCtrl();

	// 현재 페이지 표시
	this->ShowCurrentPage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CAlarmDlg::InitGridCtrl_Alarm()
{
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_ALARM_GRID);
	AlarmRow = MAX_ALARM_LIST_IN_PAGE + 1;//아래
	AlarmCol = 3;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 50;
	int gridWidth2 = 100;
	int gridWidth3 = 750;
	int totalWidth = gridWidth1 + gridWidth2 + (gridWidth3*(AlarmCol - 2));
	//
	pWnd->GetWindowRect(rect);//pWnd->GetClientRect(rect);
	ScreenToClient(rect);//ClientToScreen(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*AlarmRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_ALARM_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridAlarm.Create(rect, this, IDC_STATIC_ALARM_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridAlarm.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridAlarm.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridAlarm.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridAlarm.SetReference_Setting();
	m_clGridAlarm.EnableSelection(FALSE);
	m_clGridAlarm.SetRowCount(AlarmRow);
	m_clGridAlarm.SetColumnCount(AlarmCol);
	m_clGridAlarm.SetFixedRowCount(1);
	m_clGridAlarm.SetFixedColumnCount(1);

	CString tmpStr = "";

	m_clGridAlarm.SetItemText(0, 0, "No");
	m_clGridAlarm.SetItemText(0, 1, "Time");
	m_clGridAlarm.SetItemText(0, 2, "알람 내역");
	////
	int i = 0, j = 0;
	for (i = 0; i < AlarmRow; i++)
	{
		m_clGridAlarm.SetRowHeight(i, gridHeight);

		for (j = 0; j < AlarmCol; j++)
		{
			m_clGridAlarm.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridAlarm.SetColumnWidth(j, gridWidth1);
				}
				else if (j == 1) {
					m_clGridAlarm.SetColumnWidth(j, gridWidth2);
				}
				else {
					m_clGridAlarm.SetColumnWidth(j, gridWidth3);
				}
			}
		}
	}
	m_clGridAlarm.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	현재 페이지 표시
//
//-----------------------------------------------------------------------------
void CAlarmDlg::ShowCurrentPage()
{
	TCHAR szPage[SIZE_OF_100BYTE];
	TCHAR szNo[SIZE_OF_100BYTE];
	int i;

	for (i = 0; i < (MAX_ALARM_LIST_IN_PAGE + 1); i++)
	{
		if (i > 0)
		{
			_stprintf_s(szNo, SIZE_OF_100BYTE, _T("%d"), (m_nCurrentPage[m_nUnit] * MAX_ALARM_LIST_IN_PAGE) + i);
			m_clGridAlarm.SetItemText(i, 0, szNo);
		}
	}
	m_clGridAlarm.Invalidate();

	_stprintf_s(szPage, SIZE_OF_100BYTE, _T("%d / %d"), m_nCurrentPage[m_nUnit] + 1, MAX_PAGE_COUNT);
	m_clColorStaticPage.SetWindowText(szPage);
}

void CAlarmDlg::ShowGridCtrl_Alarm()
{

}

//-----------------------------------------------------------------------------
//
//	알람 추가
//
//-----------------------------------------------------------------------------
void CAlarmDlg::AddAlarm_N(CString sAlarm)
{
	SYSTEMTIME stSysTime;
	GetLocalTime(&stSysTime);
	if (m_pAlarmList[m_nUnit] != NULL)
	{
		m_pAlarmList[m_nUnit][m_nAlarmIndex[m_nUnit]].Format(_T("%02d:%02d:%02d / %s"), stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond,
			(TCHAR*)(LPCTSTR)sAlarm);

		if (m_pAlarmList[m_nUnit][m_nAlarmIndex[m_nUnit]].GetLength() > 0)
		{
			AfxExtractSubString(sAlarm, m_pAlarmList[m_nUnit][m_nAlarmIndex[m_nUnit]], 0, _T('/'));
			m_clGridAlarm.SetItemText(m_nAlarmIndex[m_nUnit] + 1 - (m_nCurrentPage[m_nUnit] * MAX_ALARM_LIST_IN_PAGE), 1, sAlarm);
			AfxExtractSubString(sAlarm, m_pAlarmList[m_nUnit][m_nAlarmIndex[m_nUnit]], 1, _T('/'));
			m_clGridAlarm.SetItemText(m_nAlarmIndex[m_nUnit] + 1 - (m_nCurrentPage[m_nUnit] * MAX_ALARM_LIST_IN_PAGE), 2, sAlarm);
			m_clGridAlarm.Invalidate();
		}
		// 알람 리스트 표시
		//this->ShowAlarmList();

		m_nAlarmIndex[m_nUnit]++;
		if (m_nAlarmIndex[m_nUnit] > (MAX_PAGE_COUNT * MAX_ALARM_LIST_IN_PAGE) - 1)//
		{
			m_nAlarmIndex[m_nUnit] = 0;// (MAX_PAGE_COUNT * MAX_ALARM_LIST_IN_PAGE) - 1;
		}

		m_sAlarmLog.Format(_T("[%02d:%02d:%02d] %s"), stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, sAlarm);

		// 알람 저장
		this->SaveAlarm(m_sAlarmLog);
	}
}

//-----------------------------------------------------------------------------
//
//	알람 저장
//
//-----------------------------------------------------------------------------
void CAlarmDlg::SaveAlarm(CString sAlarm)
{
	//알람 폴더
	//년 월 일
	TCHAR szFilePath[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];


	CFileFind clFinder;
	SYSTEMTIME stSysTime;
	FILE *out;

	CString sForderName = _T("");
	CString sFileName = _T("");
	CString sMode = _T("");

	GetLocalTime(&stSysTime);

	//if (clFinder.FindFile(BASE_ALARM_PATH) == FALSE)	//기본 알람 로그 생성 
	//	CreateDirectory(BASE_ALARM_PATH, NULL);

	//sForderName.Format(_T("%s\\%04d%02d"), BASE_ALARM_PATH, stSysTime.wYear, stSysTime.wMonth);	//년 월 폴더 없으면 생성.
	//if (clFinder.FindFile(sForderName) == FALSE)
	//	CreateDirectory(sForderName, NULL);

	

	if (clFinder.FindFile(BASE_ALARM_PATH) == FALSE)
		CreateDirectory(BASE_ALARM_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_ALARM_PATH); 
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%04d%02d"), BASE_ALARM_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%04d%02d\\%02d"), BASE_ALARM_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	clFinder.Close();

	//sFileName.Format(_T("%s\\Alarm_Data_%04d%02d%02d.txt"), sForderName, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	//_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\AlarmData_AA%d_%d_%02d.txt"), szPath, g_clSysData.m_nSysNo + 1, g_clSysData.m_nUnitNo + 1, stSysTime.wDay);
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\AlarmData_AA%d_%04d%02d%02d.txt"), szPath, m_nUnit + 1, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);


	if (!fopen_s(&out, szFilePath, "a"))
	{
		fprintf_s(out, "%s\n", (LPSTR)(LPCSTR)sAlarm);
		fclose(out);
	}

}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CAlarmDlg::InitCtrl()
{
	//int i;

	//// 폰트 생성
	//m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	//m_clFontMid.CreateFont(22, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	//m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	  m_clColorStaticTitle.SetBkColor(RGB_CTRL_BG);
	  m_clColorStaticTitle.SetTextColor(RGB_COLOR_WHITE);
	  m_clColorStaticTitle.SetFont(&m_clFontBig);
	  m_clColorStaticTitle.SetFontBold(TRUE);
	  m_clColorStaticTitle.SetBorder(FALSE);
	  m_clColorStaticTitle.SetFontSize(15);


	//m_clListCtrlAlarm.ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
	//m_clListCtrlAlarm.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//m_clHeaderCtrlEx.SubclassWindow(m_clListCtrlAlarm.GetHeaderCtrl()->m_hWnd);
	//m_clHeaderCtrlEx.SetFont(&m_clFontSmall);
	//m_clHeaderCtrlEx.SetHeight(62);

	//m_clHeaderCtrlEx.SetBkColor(GRID_COLOR_TITLE);// (RGB(54, 73, 93));
	//m_clHeaderCtrlEx.SetTextColor(RGB_COLOR_WHITE);

	//m_clListCtrlAlarm.InsertColumn(0, _T("시간"), LVCFMT_CENTER, 200, -1);
	//m_clListCtrlAlarm.InsertColumn(1, _T("알람 내역"), LVCFMT_CENTER, 705, -1);
	//m_clListCtrlAlarm.DeleteAllItems();
	//m_clListCtrlAlarm.SetFont(&m_clFontMid);


	//for (i = 0; i < MAX_ALARM_COUNT; i++)
	//{
	//	m_clListCtrlAlarm.InsertItem(i, _T(""));
	//}

	//m_clColorStaticPage.SetFont(&m_clFontMid);
	//m_clColorStaticPage.SetBkColor(RGB_COLOR_WHITE);

	//m_clColorButtonClear.SetCtrlFont(18, 0, _T("맑은 고딕"));
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CAlarmDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];

	m_nUnit = nUnit;
	_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[ALARM]")); //, m_nUnit + 1);
	GetDlgItem(IDC_STATIC_ALARM_TITLE)->SetWindowText(szTitle);
}


//-----------------------------------------------------------------------------
//
//	알람 리스트 표시
//
//-----------------------------------------------------------------------------
void CAlarmDlg::ShowAlarmList_N()
{
	CString sToken = _T("");

	int i = 0;
	int nIndex;
	for (i = 0; i < MAX_ALARM_LIST_IN_PAGE; i++)
	{
		m_clGridAlarm.SetItemText(i + 1, 1, _T(""));
		m_clGridAlarm.SetItemText(i + 1, 2, _T(""));

		nIndex = (m_nCurrentPage[m_nUnit] * MAX_ALARM_LIST_IN_PAGE) + i;

		if ((nIndex >= 0) && (nIndex < (MAX_PAGE_COUNT * MAX_ALARM_LIST_IN_PAGE)))
		{
			if (m_pAlarmList[m_nUnit][nIndex].GetLength() > 0)
			{
				AfxExtractSubString(sToken, m_pAlarmList[m_nUnit][nIndex], 0, _T('/'));
				m_clGridAlarm.SetItemText(i + 1, 1, sToken);
				AfxExtractSubString(sToken, m_pAlarmList[m_nUnit][nIndex], 1, _T('/'));
				m_clGridAlarm.SetItemText(i + 1, 2, sToken);
				m_clGridAlarm.Invalidate();
			}
		}
	}

}
//-----------------------------------------------------------------------------
//
//	알람 리스트 표시(0:지우기, 1:전체 다시 그리기, 2:현재 페이지만)
//
//-----------------------------------------------------------------------------
void CAlarmDlg::ShowAlarmList(int nMode)
{
	//int nIndex;	
	//CString szTime = _T("");
	//CString szAlarm = _T("");
	//CString szTemp = _T("");	
	//int i;

	//switch (nMode)
	//{
	//case 0:
	//	for (i = 0; i < MAX_ALARM_COUNT; i++)
	//	{
	//		m_clListCtrlAlarm.SetItemText(i, 0, _T(""));
	//		m_clListCtrlAlarm.SetItemText(i, 1, _T(""));
	//	}
	//	break;
	//case 1:
	//	for (i = 0; i < MAX_ALARM_COUNT; i++)
	//	{
	//		nIndex = MAX_ALARM_COUNT * m_nCurrentPage[m_nUnit] + i;
	//		szTemp = m_pAlarmList[m_nUnit][nIndex];
	//		if (szTemp.GetLength() > 0)
	//		{
	//			// [00:00:00]
	//			szTime = m_pAlarmList[m_nUnit][nIndex].Mid(0, 10);
	//			szAlarm = m_pAlarmList[m_nUnit][nIndex].Mid(10 + 1);

	//			m_clListCtrlAlarm.SetItemText(i, 0, szTime);
	//			m_clListCtrlAlarm.SetItemText(i, 1, szAlarm);

	//			if (m_nCurrentPage[m_nUnit] == m_nAlarmPage[m_nUnit] + 1)
	//			{
	//				if (i >= m_nAlarmIndex[m_nUnit])
	//				{
	//					m_clListCtrlAlarm.SetItemText(i, 0, _T(""));
	//					m_clListCtrlAlarm.SetItemText(i, 1, _T(""));
	//				}
	//			}
	//		}
	//	}
	//	break;
	//case 2:
	//	for (i = 0; i <= m_nAlarmIndex[m_nUnit]; i++)
	//	{
	//		nIndex = MAX_ALARM_COUNT * m_nAlarmPage[m_nUnit] + i;
	//		nIndex = MAX_ALARM_COUNT * m_nCurrentPage[m_nUnit] + i;
	//		szTemp = m_pAlarmList[m_nUnit][nIndex];
	//		if (szTemp.GetLength() > 0)
	//		{
	//			// [00:00:00]
	//			szTime = m_pAlarmList[m_nUnit][nIndex].Mid(0, 10);
	//			szAlarm = m_pAlarmList[m_nUnit][nIndex].Mid(10 + 1);

	//			m_clListCtrlAlarm.SetItemText(i, 0, szTime);
	//			m_clListCtrlAlarm.SetItemText(i, 1, szAlarm);				
	//		}
	//	}
	//}
}

////-----------------------------------------------------------------------------
////
////	현재 페이지 표시
////
////-----------------------------------------------------------------------------
//void CAlarmDlg::ShowCurrentPage()
//{
//	TCHAR szPage[SIZE_OF_100BYTE];
//
//	_stprintf_s(szPage, SIZE_OF_100BYTE, _T("%d / %d"), m_nCurrentPage[m_nUnit] + 1, MAX_PAGE_COUNT);
//	m_clColorStaticPage.SetWindowText(szPage);
//}

//-----------------------------------------------------------------------------
//
//	버튼 : PREV
//
//-----------------------------------------------------------------------------
void CAlarmDlg::OnBnClickedButtonAlarmPrev()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nCurrentPage[m_nUnit] == 0)
		return;

	m_nCurrentPage[m_nUnit]--;

	if (m_nCurrentPage[m_nUnit] < 0)
		m_nCurrentPage[m_nUnit] = 0;
	
	// 현재 페이지 표시
	this->ShowCurrentPage();
	// 알람 리스트 표시
	this->ShowAlarmList_N();

	/*this->ShowAlarmList(0);
	this->ShowAlarmList(1);

	this->ShowCurrentPage();*/
}

//-----------------------------------------------------------------------------
//
//	버튼 : NEXT
//
//-----------------------------------------------------------------------------
void CAlarmDlg::OnBnClickedButtonAlarmNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nCurrentPage[m_nUnit]++;

	if (m_nCurrentPage[m_nUnit] > MAX_PAGE_COUNT - 1)
		m_nCurrentPage[m_nUnit] = MAX_PAGE_COUNT - 1;
	

	// 현재 페이지 표시
	this->ShowCurrentPage();

	// 알람 리스트 표시
	this->ShowAlarmList_N();

	//this->ShowAlarmList(0);
	//this->ShowAlarmList(1);

	//this->ShowCurrentPage();
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLEAR
//
//-----------------------------------------------------------------------------
void CAlarmDlg::OnBnClickedButtonAlarmClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_ShowMsgModal(_T("확인"), _T("알람 내역을 지우시겠습니까?"), RGB_COLOR_RED) == false)
		return;


	m_nAlarmIndex[m_nUnit] = 0;

	//m_iAlarmPage[1] = 0;
	//m_iAlarmCnt[1] = 0;

	//int curIndex = m_iAlarmKind;
	//m_iAlarmKind = 1;

	//initGrid();

	////g_AlarmCnt = 0;
	////g_AlarmFlag = checkAlarm();

	//m_iAlarmKind = curIndex;
	int i = 0;
	int j = 0;
	for (i = 0; i < (MAX_ALARM_LIST_IN_PAGE * MAX_PAGE_COUNT); i++)
	{
		m_pAlarmList[m_nUnit][i].Empty();
	}

	for (i = 0; i < AlarmRow; i++)
	{

		if (i == 0)
		{
			continue;
		}
		for (j = 0; j < AlarmCol; j++)
		{
			m_clGridAlarm.SetItemText(i, j, "");
		}

	}
	m_clGridAlarm.Invalidate();
	for (i = 1; i < MAX_ALARM_LIST_IN_PAGE; i++)
	{
		m_clGridAlarm.SetItemText(i, 1, _T(""));
		m_clGridAlarm.SetItemText(i, 2, _T(""));
	}
	m_clGridAlarm.Invalidate();
	//this->ShowAlarmList(0);
}

//-----------------------------------------------------------------------------
//
//	알람 추가
//
//-----------------------------------------------------------------------------
void CAlarmDlg::AddAlarm(CString szAlarm)
{
	SYSTEMTIME stSysTime;
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	CFileFind clFinder;
	CString sWriteMode = _T("");
	FILE* fp;

	GetLocalTime(&stSysTime);

	if (m_nAlarmIndex[m_nUnit] >= MAX_ALARM_COUNT)
	{
		m_nAlarmIndex[m_nUnit] = 0;
		m_nAlarmPage[m_nUnit]++;

		if (m_nAlarmPage[m_nUnit] == MAX_PAGE_COUNT)
		{
			m_nAlarmPage[m_nUnit] = 9;
		}
	}

	m_pAlarmList[m_nUnit][MAX_ALARM_COUNT * m_nAlarmPage[m_nUnit] + m_nAlarmIndex[m_nUnit]].Format(_T("[%02d:%02d:%02d] %s"),
		stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, (TCHAR*)(LPCTSTR)szAlarm);

	this->ShowAlarmList(0);
	this->ShowAlarmList(2);

	m_nCurrentPage[m_nUnit] = m_nAlarmPage[m_nUnit];
	m_nAlarmIndex[m_nUnit]++;

	this->ShowCurrentPage();

	if (clFinder.FindFile(BASE_ALARM_PATH) == FALSE)
		CreateDirectory(BASE_ALARM_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%04d%02d"), BASE_ALARM_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%04d%02d\\%02d"), BASE_ALARM_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);
		
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\AlarmData-AA%d-%d-%02d.csv"), szPath, g_clSysData.m_nSysNo, g_clSysData.m_nUnitNo, stSysTime.wDay);
	
	_stprintf_s(szLog, SIZE_OF_1K, _T("'%02d:%02d:%02d, %s"), stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, (TCHAR*)(LPCTSTR)szAlarm);

	sWriteMode = _T("a + t");

	_tfopen_s(&fp, szFilePath, sWriteMode);
	if (fp != NULL)
	{
		fwrite(szLog, _tcslen(szLog) * sizeof(TCHAR), 1, fp);
		fwrite(_T("\r\n"), _tcslen(_T("\r\n")) * sizeof(TCHAR), 1, fp);

		fclose(fp);
	}
}

//-----------------------------------------------------------------------------
//
//	PreTranlsateMessage
//
//-----------------------------------------------------------------------------
BOOL CAlarmDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ALARM_PREV)->m_hWnd)
		{
			//m_clColorButtonPrev.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ALARM_NEXT)->m_hWnd)
		{
			//m_clColorButtonNext.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ALARM_CLEAR)->m_hWnd)
		{
			//m_clColorButtonClear.SetSelected(true);
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ALARM_PREV)->m_hWnd)
		{
			//m_clColorButtonPrev.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ALARM_NEXT)->m_hWnd)
		{
			//m_clColorButtonNext.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ALARM_CLEAR)->m_hWnd)
		{
			//m_clColorButtonClear.SetSelected(false);
		}
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


void CAlarmDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow == TRUE)
	{
		// 현재 페이지 표시
		this->ShowCurrentPage();

		// 알람 리스트 표시
		this->ShowAlarmList_N();
	}
	else
	{
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
