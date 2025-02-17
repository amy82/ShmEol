// EpoxySet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EpoxySet.h"
#include "afxdialogex.h"


// CEpoxySet 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEpoxySet, CDialogEx)

CEpoxySet::CEpoxySet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EPOXY, pParent)
{

}

CEpoxySet::~CEpoxySet()
{
}

void CEpoxySet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEpoxySet, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_SAVE, &CEpoxySet::OnBnClickedButtonEpoxySave)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_LINE_GRID, &CEpoxySet::OnStnDblclickStaticEpoxyLineGrid)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_LINE_LENGTH_GRID, &CEpoxySet::OnStnDblclickStaticEpoxyLineLengthGrid)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_CURVE_LENGTH_GRID, &CEpoxySet::OnStnDblclickStaticEpoxyCurveLengthGrid)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_INSP_RECT_GRID, &CEpoxySet::OnStnDblclickStaticEpoxyInspGrid)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_INSP_CIRCLE_GRID, &CEpoxySet::OnStnDblclickStaticEpoxyInspCircleGrid)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_INSP_SPEC_GRID, &CEpoxySet::OnStnDblclickStaticEpoxyInspSpecGrid)

	
END_MESSAGE_MAP()


// CEpoxySet 메시지 처리기입니다.


//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CEpoxySet::InitCtrl()
{

}


//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CEpoxySet::InitEpoxyLineGridCtrl()
{
	TCHAR* pszCol[] = { _T("Motor"), _T("Set") };
	TCHAR* pszRow[] = { _T(""), _T("Line Speed(mm/s)") , _T("Line Acc/Dec(mm/s)"), 
		_T("Curve Speed(mm/s)") , _T("Curve Acc/Dec(mm/s)"), 
		_T("ON Time(s)") , _T("OFF Time(s)") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_EPOXY_LINE_GRID;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = 7;// sizeof(STAIN_BLEMISH_SPEC_NAME) / sizeof(STAIN_BLEMISH_SPEC_NAME[0]) + 1;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 140;
	int gridWidth2 = 90;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyLine.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyLine.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridEpoxyLine.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyLine.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridEpoxyLine.SetReference_Setting();
	m_clGridEpoxyLine.EnableSelection(FALSE);
	m_clGridEpoxyLine.SetRowCount(SpecRow);
	m_clGridEpoxyLine.SetColumnCount(SpecCol);
	m_clGridEpoxyLine.SetFixedRowCount(1);
	m_clGridEpoxyLine.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridEpoxyLine.SetRowHeight(i, gridHeight);
		m_clGridEpoxyLine.SetItemText(i + 1, 0, pszRow[i + 1]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyLine.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridEpoxyLine.SetColumnWidth(j, gridWidth2);
				}

				m_clGridEpoxyLine.SetItemText(i, j, pszCol[j]);
			}

			m_clGridEpoxyLine.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CEpoxySet::InitEpoxyLineLengthGridCtrl()
{
	TCHAR* pszCol[] = { _T("직선도포"), _T("길이") };
	//TCHAR* pszRow[] = { _T(""), _T("Line Speed(mm/s)")};
	TCHAR szData[SIZE_OF_100BYTE];
	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_EPOXY_LINE_LENGTH_GRID;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = 5;// sizeof(STAIN_BLEMISH_SPEC_NAME) / sizeof(STAIN_BLEMISH_SPEC_NAME[0]) + 1;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 100;
	int gridWidth2 = 70;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyLineLength.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyLineLength.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridEpoxyLineLength.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyLineLength.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridEpoxyLineLength.SetReference_Setting();
	m_clGridEpoxyLineLength.EnableSelection(FALSE);
	m_clGridEpoxyLineLength.SetRowCount(SpecRow);
	m_clGridEpoxyLineLength.SetColumnCount(SpecCol);
	m_clGridEpoxyLineLength.SetFixedRowCount(1);
	m_clGridEpoxyLineLength.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridEpoxyLineLength.SetRowHeight(i, gridHeight);
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("LINE%d"), i + 1);
		m_clGridEpoxyLineLength.SetItemText(i + 1, 0, szData);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyLineLength.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridEpoxyLineLength.SetColumnWidth(j, gridWidth2);
				}

				m_clGridEpoxyLineLength.SetItemText(i, j, pszCol[j]);
			}

			m_clGridEpoxyLineLength.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}


//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CEpoxySet::InitEpoxyCurveLengthGridCtrl()
{
	TCHAR* pszCol[] = { _T("곡선도포"), _T("CEN X"), _T("CEN Y") , _T("END X"), _T("END Y") };
	//TCHAR* pszRow[] = { _T(""), _T("Line Speed(mm/s)")};
	TCHAR szData[SIZE_OF_100BYTE];
	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_EPOXY_CURVE_LENGTH_GRID;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = 5;// sizeof(STAIN_BLEMISH_SPEC_NAME) / sizeof(STAIN_BLEMISH_SPEC_NAME[0]) + 1;//아래
	int SpecCol = 5;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 100;
	int gridWidth2 = 54;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyCurveLength.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyCurveLength.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridEpoxyCurveLength.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyCurveLength.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridEpoxyCurveLength.SetReference_Setting();
	m_clGridEpoxyCurveLength.EnableSelection(FALSE);
	m_clGridEpoxyCurveLength.SetRowCount(SpecRow);
	m_clGridEpoxyCurveLength.SetColumnCount(SpecCol);
	m_clGridEpoxyCurveLength.SetFixedRowCount(1);
	m_clGridEpoxyCurveLength.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridEpoxyCurveLength.SetRowHeight(i, gridHeight);
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("CURVE P%d"), i + 1);
		m_clGridEpoxyCurveLength.SetItemText(i + 1, 0, szData);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyCurveLength.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridEpoxyCurveLength.SetColumnWidth(j, gridWidth2);
				}

				m_clGridEpoxyCurveLength.SetItemText(i, j, pszCol[j]);
			}

			m_clGridEpoxyCurveLength.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}


void CEpoxySet::InitEpoxyInspSpecGridCtrl()
{
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_EPOXY_INSP_SPEC_GRID);
	int nRow = 7;//아래
	int nCol = 3;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 180;
	int gridWidth2 = 80;
	int totalWidth = gridWidth1 + (gridWidth2*(nCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*nRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_EPOXY_INSP_SPEC_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyInspSpec.Create(rect, this, IDC_STATIC_EPOXY_INSP_SPEC_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyInspSpec.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyInspSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyInspSpec.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyInspSpec.SetReference_Setting();
	m_clGridEpoxyInspSpec.EnableSelection(FALSE);
	m_clGridEpoxyInspSpec.SetRowCount(nRow);
	m_clGridEpoxyInspSpec.SetColumnCount(nCol);
	m_clGridEpoxyInspSpec.SetFixedRowCount(1);
	m_clGridEpoxyInspSpec.SetFixedColumnCount(1);

	CString tmpStr = "";

	m_clGridEpoxyInspSpec.SetItemText(1, 0, "Epoxy 도포 크기 (mm)");
	m_clGridEpoxyInspSpec.SetItemText(2, 0, "검사 영역 안쪽 Offset(mm)");
	m_clGridEpoxyInspSpec.SetItemText(3, 0, "검사 영역 바깥 Offset (mm)");
	m_clGridEpoxyInspSpec.SetItemText(4, 0, "도포 검사 OK Limit (%)");
	m_clGridEpoxyInspSpec.SetItemText(5, 0, "Square 검사 Spec (%)");
	m_clGridEpoxyInspSpec.SetItemText(6, 0, "Square 연속 끊어진 구간 (mm)");																							//

	m_clGridEpoxyInspSpec.SetItemText(0, 0, "원형도포 검사설정");
	m_clGridEpoxyInspSpec.SetItemText(0, 1, "X");
	m_clGridEpoxyInspSpec.SetItemText(0, 2, "Y");

	//
	int i = 0, j = 0;
	for (i = 0; i < nRow; i++)
	{
		m_clGridEpoxyInspSpec.SetRowHeight(i, gridHeight);

		for (j = 0; j < nCol; j++)
		{
			m_clGridEpoxyInspSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyInspSpec.SetColumnWidth(j, gridWidth1);
				}
				else {
					m_clGridEpoxyInspSpec.SetColumnWidth(j, gridWidth2);
				}
			}
		}
	}
	m_clGridEpoxyInspSpec.Invalidate();
}



void CEpoxySet::InitEpoxyCircleRectInspGridCtrl()
{
	CRect rect;
	int DLG = IDC_STATIC_EPOXY_INSP_CIRCLE_GRID;
	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	//;//
	int nRow = 5;//아래
	int nCol = 5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 100;
	int gridWidth2 = 55;
	int totalWidth = gridWidth1 + (gridWidth2*(nCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*nRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyCircleRect.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyCircleRect.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleRect.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyCircleRect.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleRect.SetReference_Setting();
	m_clGridEpoxyCircleRect.EnableSelection(FALSE);
	m_clGridEpoxyCircleRect.SetRowCount(nRow);
	m_clGridEpoxyCircleRect.SetColumnCount(nCol);
	m_clGridEpoxyCircleRect.SetFixedRowCount(1);
	m_clGridEpoxyCircleRect.SetFixedColumnCount(1);

	CString tmpStr = "";
	m_clGridEpoxyCircleRect.SetItemText(0, 0, "원형 검사 영역");
	m_clGridEpoxyCircleRect.SetItemText(1, 0, " LT");
	m_clGridEpoxyCircleRect.SetItemText(2, 0, " RT");
	m_clGridEpoxyCircleRect.SetItemText(4, 0, " RB");
	m_clGridEpoxyCircleRect.SetItemText(3, 0, " LB");
	//
	m_clGridEpoxyCircleRect.SetItemText(0, 1, "X");
	m_clGridEpoxyCircleRect.SetItemText(0, 2, "Y");
	m_clGridEpoxyCircleRect.SetItemText(0, 3, "Width");
	m_clGridEpoxyCircleRect.SetItemText(0, 4, "height");

	//
	int i = 0, j = 0;
	for (i = 0; i < nRow; i++)
	{
		m_clGridEpoxyCircleRect.SetRowHeight(i, gridHeight);

		for (j = 0; j < nCol; j++)
		{
			m_clGridEpoxyCircleRect.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyCircleRect.SetColumnWidth(j, gridWidth1);
				}
				else {
					m_clGridEpoxyCircleRect.SetColumnWidth(j, gridWidth2);
				}
			}
		}
	}
	m_clGridEpoxyCircleRect.Invalidate();
}


void CEpoxySet::InitEpoxyRectInspGridCtrl()
{
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_EPOXY_INSP_RECT_GRID);
	int nRow = 5;//아래
	int nCol = 5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 130;
	int gridWidth2 = 55;
	int totalWidth = gridWidth1 + (gridWidth2*(nCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*nRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_EPOXY_INSP_RECT_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyInspRect.Create(rect, this, IDC_STATIC_EPOXY_INSP_RECT_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyInspRect.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyInspRect.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyInspRect.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyInspRect.SetReference_Setting();
	m_clGridEpoxyInspRect.EnableSelection(FALSE);
	m_clGridEpoxyInspRect.SetRowCount(nRow);
	m_clGridEpoxyInspRect.SetColumnCount(nCol);
	m_clGridEpoxyInspRect.SetFixedRowCount(1);
	m_clGridEpoxyInspRect.SetFixedColumnCount(1);

	CString tmpStr = "";
	m_clGridEpoxyInspRect.SetItemText(0, 0, "사각도포 검사 영역");
	m_clGridEpoxyInspRect.SetItemText(1, 0, " Left");
	m_clGridEpoxyInspRect.SetItemText(2, 0, " Right");
	m_clGridEpoxyInspRect.SetItemText(3, 0, " Top");
	m_clGridEpoxyInspRect.SetItemText(4, 0, " Bottom");
	//


	m_clGridEpoxyInspRect.SetItemText(0, 1, "X");
	m_clGridEpoxyInspRect.SetItemText(0, 2, "Y");
	m_clGridEpoxyInspRect.SetItemText(0, 3, "Width");
	m_clGridEpoxyInspRect.SetItemText(0, 4, "Height");

	//
	int i = 0, j = 0;
	for (i = 0; i < nRow; i++)
	{
		m_clGridEpoxyInspRect.SetRowHeight(i, gridHeight);

		for (j = 0; j < nCol; j++)
		{
			m_clGridEpoxyInspRect.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyInspRect.SetColumnWidth(j, gridWidth1);
				}
				else {
					m_clGridEpoxyInspRect.SetColumnWidth(j, gridWidth2);
				}
			}
		}
	}
	m_clGridEpoxyInspRect.Invalidate();
}

BOOL CEpoxySet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
	this->InitEpoxyLineGridCtrl();
	this->InitEpoxyLineLengthGridCtrl();
	this->InitEpoxyCurveLengthGridCtrl();
	this->InitEpoxyRectInspGridCtrl();
	this->InitEpoxyCircleRectInspGridCtrl();
	this->InitEpoxyInspSpecGridCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CEpoxySet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow == TRUE)
	{
		this->ShowEpoxySet();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CEpoxySet::ShowEpoxySet()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i = 0;

	m_clGridEpoxyLine.SetItemText(1, 1, g_clModelData[m_nUnit].m_EpoxyLineSpeed, 3);
	m_clGridEpoxyLine.SetItemText(2, 1, g_clModelData[m_nUnit].m_EpoxyLineAccDec, 3);
	m_clGridEpoxyLine.SetItemText(3, 1, g_clModelData[m_nUnit].m_EpoxyCurveSpeed, 3);
	m_clGridEpoxyLine.SetItemText(4, 1, g_clModelData[m_nUnit].m_EpoxyCurveAccDec, 3);
	m_clGridEpoxyLine.SetItemText(5, 1, g_clModelData[m_nUnit].m_EpoxyOnTime, 3);
	m_clGridEpoxyLine.SetItemText(6, 1, g_clModelData[m_nUnit].m_EpoxyOffTime, 3);


	
	for (i = 0; i < 4; i++)
	{
		//라인도포 길이 설정
		m_clGridEpoxyLineLength.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_EpoxyLineLength[i], 2);
		//곡선도포 길이 설정
		m_clGridEpoxyCurveLength.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_EpoxyCurveCenterXPoint[i], 2);
		m_clGridEpoxyCurveLength.SetItemText(i + 1, 2, g_clModelData[m_nUnit].m_EpoxyCurveCenterYPoint[i], 2);
		m_clGridEpoxyCurveLength.SetItemText(i + 1, 3, g_clModelData[m_nUnit].m_EpoxyCurveEndXPoint[i], 2);
		m_clGridEpoxyCurveLength.SetItemText(i + 1, 4, g_clModelData[m_nUnit].m_EpoxyCurveEndYPoint[i], 2);
	}


	for (i = 0; i < 4; i++)
	{
		m_clGridEpoxyInspRect.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_ResingRectStart[i].x, 3);
		m_clGridEpoxyInspRect.SetItemText(i + 1, 2, g_clModelData[m_nUnit].m_ResingRectStart[i].y, 3);
		m_clGridEpoxyInspRect.SetItemText(i + 1, 3, g_clModelData[m_nUnit].m_ResingRectSize[i].x, 3);
		m_clGridEpoxyInspRect.SetItemText(i + 1, 4, g_clModelData[m_nUnit].m_ResingRectSize[i].y, 3);
	}


	for (i = 0; i < 4; i++)
	{
		m_clGridEpoxyCircleRect.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_CircleDrawCenter[i].x, 3);
		m_clGridEpoxyCircleRect.SetItemText(i + 1, 2, g_clModelData[m_nUnit].m_CircleDrawCenter[i].y, 3);
	}

	for (i = 0; i < 4; i++)
	{
		m_clGridEpoxyCircleRect.SetItemText(i + 1, 3, g_clModelData[m_nUnit].m_CircleDrawSize[i].x, 3);
		m_clGridEpoxyCircleRect.SetItemText(i + 1, 4, g_clModelData[m_nUnit].m_CircleDrawSize[i].y, 3);
	}

	m_clGridEpoxyInspSpec.SetItemText(1, 1, g_clModelData[m_nUnit].m_ResinDrawSize.x, 3);
	m_clGridEpoxyInspSpec.SetItemText(1, 2, g_clModelData[m_nUnit].m_ResinDrawSize.y, 3);
	m_clGridEpoxyInspSpec.SetItemText(2, 1, g_clModelData[m_nUnit].m_dResinInspOffset[0].x, 3);
	m_clGridEpoxyInspSpec.SetItemText(2, 2, g_clModelData[m_nUnit].m_dResinInspOffset[0].y, 3);
	m_clGridEpoxyInspSpec.SetItemText(3, 1, g_clModelData[m_nUnit].m_dResinInspOffset[1].x, 3);
	m_clGridEpoxyInspSpec.SetItemText(3, 2, g_clModelData[m_nUnit].m_dResinInspOffset[1].y, 3);
	m_clGridEpoxyInspSpec.SetItemText(4, 1, g_clModelData[m_nUnit].m_nResinInspLimit, 3);
	m_clGridEpoxyInspSpec.SetItemText(4, 2, _T("--"));
	m_clGridEpoxyInspSpec.SetItemText(5, 1, g_clModelData[m_nUnit].m_dResinInspRectSpec, 3);
	m_clGridEpoxyInspSpec.SetItemText(5, 2, _T("--"));
	m_clGridEpoxyInspSpec.SetItemText(6, 1, g_clModelData[m_nUnit].m_dResinInspGapLength, 3);
	m_clGridEpoxyInspSpec.SetItemText(6, 2, _T("--"));




	m_clGridEpoxyCurveLength.Invalidate();
	m_clGridEpoxyLineLength.Invalidate();
	m_clGridEpoxyLine.Invalidate();
	m_clGridEpoxyInspRect.Invalidate();
	m_clGridEpoxyCircleRect.Invalidate();
	m_clGridEpoxyInspSpec.Invalidate();
}
void CEpoxySet::GetEpoxyData()
{
	TCHAR szData[SIZE_OF_100BYTE];
	CString sData = _T("");
	int i = 0;

	sData = m_clGridEpoxyLine.GetItemText(1, 1);
	g_clModelData[m_nUnit].m_EpoxyLineSpeed = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyLine.GetItemText(2, 1);
	g_clModelData[m_nUnit].m_EpoxyLineAccDec = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyLine.GetItemText(3, 1);
	g_clModelData[m_nUnit].m_EpoxyCurveSpeed = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyLine.GetItemText(4, 1);
	g_clModelData[m_nUnit].m_EpoxyCurveAccDec = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyLine.GetItemText(5, 1);
	g_clModelData[m_nUnit].m_EpoxyOnTime = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyLine.GetItemText(6, 1);
	g_clModelData[m_nUnit].m_EpoxyOffTime = _ttof((TCHAR*)(LPCTSTR)sData);


	for (i = 0; i < 4; i++)
	{
		sData = m_clGridEpoxyLineLength.GetItemText(1 + i, 1);
		g_clModelData[m_nUnit].m_EpoxyLineLength[i] = _ttof((TCHAR*)(LPCTSTR)sData);

		sData = m_clGridEpoxyCurveLength.GetItemText(1 + i, 1);
		g_clModelData[m_nUnit].m_EpoxyCurveCenterXPoint[i] = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyCurveLength.GetItemText(1 + i, 2);
		g_clModelData[m_nUnit].m_EpoxyCurveCenterYPoint[i] = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyCurveLength.GetItemText(1 + i, 3);
		g_clModelData[m_nUnit].m_EpoxyCurveEndXPoint[i] = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyCurveLength.GetItemText(1 + i, 4);
		g_clModelData[m_nUnit].m_EpoxyCurveEndYPoint[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}


	for (i = 0; i < 4; i++)
	{
		sData = m_clGridEpoxyInspRect.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_ResingRectStart[i].x = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyInspRect.GetItemText(i + 1, 2);
		g_clModelData[m_nUnit].m_ResingRectStart[i].y = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyInspRect.GetItemText(i + 1, 3);
		g_clModelData[m_nUnit].m_ResingRectSize[i].x = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyInspRect.GetItemText(i + 1, 4);
		g_clModelData[m_nUnit].m_ResingRectSize[i].y = _ttof((TCHAR*)(LPCTSTR)sData);
	}


	for (i = 0; i < 4; i++)
	{
		sData = m_clGridEpoxyCircleRect.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_CircleDrawCenter[i].x = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyCircleRect.GetItemText(i + 1, 2);
		g_clModelData[m_nUnit].m_CircleDrawCenter[i].y = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyCircleRect.GetItemText(i + 1, 3);
		g_clModelData[m_nUnit].m_CircleDrawSize[i].x = _ttof((TCHAR*)(LPCTSTR)sData);
		sData = m_clGridEpoxyCircleRect.GetItemText(i + 1, 4);
		g_clModelData[m_nUnit].m_CircleDrawSize[i].y = _ttof((TCHAR*)(LPCTSTR)sData);
	}


	sData = m_clGridEpoxyInspSpec.GetItemText(1, 1);
	g_clModelData[m_nUnit].m_ResinDrawSize.x = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(1, 2);
	g_clModelData[m_nUnit].m_ResinDrawSize.y = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(2, 1);
	g_clModelData[m_nUnit].m_dResinInspOffset[0].x = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(2, 2);
	g_clModelData[m_nUnit].m_dResinInspOffset[0].y = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(3, 1);
	g_clModelData[m_nUnit].m_dResinInspOffset[1].x = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(3, 2);
	g_clModelData[m_nUnit].m_dResinInspOffset[1].y = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(4, 1);
	g_clModelData[m_nUnit].m_nResinInspLimit = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(5, 1);
	g_clModelData[m_nUnit].m_dResinInspRectSpec = _ttof((TCHAR*)(LPCTSTR)sData);
	sData = m_clGridEpoxyInspSpec.GetItemText(6, 1);
	g_clModelData[m_nUnit].m_dResinInspGapLength = _ttof((TCHAR*)(LPCTSTR)sData);



}


void CEpoxySet::OnBnClickedButtonEpoxySave()
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

	if (g_ShowMsgModal(_T("확인"), _T("EPOXY 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	this->GetEpoxyData();

	//g_clModelData[m_nUnit].EpoxyDataSave(g_clSysData.m_szModelName);
	//AddLog(_T("[INFO] EPOXY DATA 저장"), 0, m_nUnit);
}


void CEpoxySet::OnStnDblclickStaticEpoxyLineGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridEpoxyLine.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridEpoxyLine.SetItemText(nRow, nCol, sData);

				m_clGridEpoxyLine.Invalidate();
			}

			delete pDlg;
		}
	}
}


void CEpoxySet::OnStnDblclickStaticEpoxyLineLengthGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridEpoxyLineLength.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridEpoxyLineLength.SetItemText(nRow, nCol, sData);

				m_clGridEpoxyLineLength.Invalidate();
			}

			delete pDlg;
		}
	}
}


void CEpoxySet::OnStnDblclickStaticEpoxyCurveLengthGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridEpoxyCurveLength.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridEpoxyCurveLength.SetItemText(nRow, nCol, sData);

				m_clGridEpoxyCurveLength.Invalidate();
			}

			delete pDlg;
		}
	}
}


void CEpoxySet::OnStnDblclickStaticEpoxyInspGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridEpoxyInspRect.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridEpoxyInspRect.SetItemText(nRow, nCol, sData);

				m_clGridEpoxyInspRect.Invalidate();
			}

			delete pDlg;
		}
	}
}

void CEpoxySet::OnStnDblclickStaticEpoxyInspCircleGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridEpoxyCircleRect.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridEpoxyCircleRect.SetItemText(nRow, nCol, sData);

				m_clGridEpoxyCircleRect.Invalidate();
			}

			delete pDlg;
		}
	}
}

void CEpoxySet::OnStnDblclickStaticEpoxyInspSpecGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridEpoxyInspSpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridEpoxyInspSpec.SetItemText(nRow, nCol, sData);

				m_clGridEpoxyInspSpec.Invalidate();
			}

			delete pDlg;
		}
	}
}
