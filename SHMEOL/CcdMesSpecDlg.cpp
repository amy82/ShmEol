// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdMesSpecDlg.h"
#include "afxdialogex.h"


// CCcdMesSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdMesSpecDlg, CDialogEx)

CCcdMesSpecDlg::CCcdMesSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdMesSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
}

CCcdMesSpecDlg::~CCcdMesSpecDlg()
{
}

void CCcdMesSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CCD_MES_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_MES_SPEC_LOAD, m_clColorButtonLoad);
	DDX_Control(pDX, IDC_BUTTON_CCD_MES_SPEC_CLOSE, m_clColorButtonClose);
	
}


BEGIN_MESSAGE_MAP(CCcdMesSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()

    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_MES_SPEC_GRID1, &CCcdMesSpecDlg::OnNMDblClickedMesGrid1)

	ON_BN_CLICKED(IDC_BUTTON_CCD_MES_SPEC_SAVE, &CCcdMesSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MES_SPEC_CLOSE, &CCcdMesSpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MES_SPEC_LOAD, &CCcdMesSpecDlg::OnBnClickedButtonCcdMesSpecLoad)
END_MESSAGE_MAP()


// CCcdMesSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::OnPaint()
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
BOOL CCcdMesSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
    this->InitMesGridCtrl1();
    
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	

}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::InitMesGridCtrl1()
{
#if 0
    TCHAR* pszCol[] = { _T("No"), _T("Item"), _T("Min"), _T("Max") };

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_MES_SPEC_GRID1;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = MES_VERIFY_SPEC_COUNT + 1;// MesMaxCount1 + 1;//아래
	int SpecCol = 4;// 3;//옆
    int margin = 4;
    int gridHeight = 25;
	int gridWidth0 = 30;
	int gridWidth1 = 240;
	int gridWidth2 = 100;// 75;
    int totalWidth = gridWidth0 + gridWidth1 + (gridWidth2*(SpecCol - 2));
	int viewRow = 30;
	int xMargin = 21;
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + xMargin;
    //rect.bottom = (gridHeight*SpecRow) + margin;
	rect.bottom = (gridHeight*viewRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
	m_clGridMesSpec1.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridMesSpec1.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridMesSpec1.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridMesSpec1.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridMesSpec1.SetReference_Setting();
    m_clGridMesSpec1.EnableSelection(FALSE);
    m_clGridMesSpec1.SetRowCount(SpecRow);
    m_clGridMesSpec1.SetColumnCount(SpecCol);
    m_clGridMesSpec1.SetFixedRowCount(1);
    m_clGridMesSpec1.SetFixedColumnCount(1);

    for (i = 0; i < SpecRow; i++)
    {
		m_clGridMesSpec1.SetRowHeight(i, gridHeight);
		m_clGridMesSpec1.SetItemText(i + 1, 0, i);
		m_clGridMesSpec1.SetItemText(i + 1, 1, MesSpecList[i].c_str());

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
					m_clGridMesSpec1.SetColumnWidth(j, gridWidth0);
                }
				else if (j == 1)
				{
					m_clGridMesSpec1.SetColumnWidth(j, gridWidth1);
				}
                else
                {
					m_clGridMesSpec1.SetColumnWidth(j, gridWidth2);
                }

				m_clGridMesSpec1.SetItemText(i, j, pszCol[j]);
            }
			if (j == 0)
			{
				m_clGridMesSpec1.SetItemFormat(i, j, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				m_clGridMesSpec1.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
        }
    }
#endif
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
        this->ShowMesGridSpec();
	}
}
//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 Get
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::GetMesSpec()
{
	//int i = 0;
	//CString tmpStr = "";
	//for (i = 0; i < MES_VERIFY_SPEC_COUNT; i++)
	//{
	//	tmpStr = m_clGridMesSpec1.GetItemText(i + 1, 2);	//Min Spec
	//	_stprintf_s(EEpromVerifyData.vMinData[i], SIZE_OF_100BYTE, tmpStr);
	//	tmpStr = m_clGridMesSpec1.GetItemText(i + 1, 3);	//Max Spec
	//	_stprintf_s(EEpromVerifyData.vMaxData[i], SIZE_OF_100BYTE, tmpStr);



	//}
//	tmpStr.Empty();
}
//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::ShowMesGridSpec()
{
	//TCHAR szData[SIZE_OF_100BYTE];
	//int i = 0;
	//int mMesval1 = 0;
	//for (i = 0; i < MES_VERIFY_SPEC_COUNT; i++)//for (i = 0; i < MesMaxCount1; i++)
	//{
	//	m_clGridMesSpec1.SetItemText(i + 1, 2, EEpromVerifyData.vMinData[i]);
	//	m_clGridMesSpec1.SetItemText(i + 1, 3, EEpromVerifyData.vMaxData[i]);
	//}
	//m_clGridMesSpec1.Invalidate();
}
#if 0
//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------

void CCcdMesSpecDlg::GetLcbSpec()
{
    CString sData = _T("");
    int i;

    /*for (i = 0; i < g_StainLcbcount; i++)
    {
        sData = m_clGridMesSpec2.GetItemText(i + 1, 1);
        g_clModelData[m_nUnit].m_LcbSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
    }*/
    g_clSysData.sDSave();
}
void CCcdMesSpecDlg::GetYmeanSpec()
{
    CString sData = _T("");
    int i;
	
	
    for (i = 0; i < g_StainYmeancount; i++)
    {
        sData = m_clGridMesSpec3.GetItemText(i + 1, 1);
        g_clModelData[m_nUnit].m_YmeanSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
    }
    g_clSysData.sDSave();
}
#endif
//-----------------------------------------------------------------------------
//
//	버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
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
	}*/

	if (g_ShowMsgModal(_T("확인"), _T("SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false) {
		return;
	}

	this->GetMesSpec();
    
	MesDataSave();
	MesDataLoad();

	this->ShowMesGridSpec();
	AddLog(_T("[INFO] SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::OnNMDblClickedMesGrid1(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    //if (nRow >= 1 && nCol >= 1)
	if ((nRow >= 5 && nRow <= 13) && nCol == 3)
	{
		return;
	}
	if ((nRow == 39) && nCol == 3)
	{
		return;
	}
	if ((nRow >= 21 && nRow <= 24) && nCol == 2)
	{
		return;
	}
	if ((nRow >= 1 ) && nCol >= 2)	//ApsSpecRow 빼기 1 한건 Epoxy 값은 사용안해서 제외
    {
    //    sData = m_clGridMesSpec1.GetItemText(nRow, nCol);
    //    CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
    //    if (pDlg != NULL)
    //    {
    //        if (pDlg->DoModal() == IDOK)
    //        {
				//if (nRow == 3 || nRow == 4)//if (nRow == 67 || nRow == 68)
				//{
				//	sData.Format(_T("%.0lf"), pDlg->GetReturnVal());
				//}
				//else
				//{
				//	sData.Format(_T("%.06lf"), pDlg->GetReturnVal());
				//}
    //           
				//m_clGridMesSpec1.SetItemText(nRow, nCol, sData);

				//m_clGridMesSpec1.Invalidate();
    //        }

    //        delete pDlg;
    //    }
    }
}
#if 0
void CCcdMesSpecDlg::OnNMDblClickedMesGrid2(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridMesSpec2.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridMesSpec2.SetItemText(nRow, nCol, sData);

				m_clGridMesSpec2.Invalidate();
            }

            delete pDlg;
        }
    }
}

void CCcdMesSpecDlg::OnNMDblClickedMesGrid3(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridMesSpec3.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridMesSpec3.SetItemText(nRow, nCol, sData);

				m_clGridMesSpec3.Invalidate();
            }

            delete pDlg;
        }
    }
}


void CCcdMesSpecDlg::OnNMDblClickedMesGrid4(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridMesSpec4.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridMesSpec4.SetItemText(nRow, nCol, sData);

				m_clGridMesSpec4.Invalidate();
			}

			delete pDlg;
		}
	}
}

#endif
//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdMesSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdMesSpecDlg::PreTranslateMessage(MSG* pMsg)
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

void CCcdMesSpecDlg::OnBnClickedButtonCcdMesSpecLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	g_clSysData.OcOffsetLoad();
	MesDataLoad();	//load button

	this->ShowMesGridSpec();
}
