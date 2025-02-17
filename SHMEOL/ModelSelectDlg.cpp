// ModelSelectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ModelSelectDlg.h"
#include "AutoInsp.h"
#include "afxdialogex.h"


// CModelSelectDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModelSelectDlg, CDialogEx)

CModelSelectDlg::CModelSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MODEL_SELECT, pParent)
{

}

CModelSelectDlg::~CModelSelectDlg()
{
}

void CModelSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MODERATE_MODEL, m_ColorbuttonModelModerate);
	DDX_Control(pDX, IDC_BUTTON_NARROW_MODEL, m_ColorbuttonModelNarrow);
}


BEGIN_MESSAGE_MAP(CModelSelectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MODEL_SELECT_EXIT, &CModelSelectDlg::OnBnClickedButtonModelSelectExit)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_MODERATE_MODEL, &CModelSelectDlg::OnBnClickedButtonModerateModel)
	ON_BN_CLICKED(IDC_BUTTON_NARROW_MODEL, &CModelSelectDlg::OnBnClickedButtonNarrowModel)
	ON_BN_CLICKED(IDC_BUTTON_MODEL_SELECT_LOAD, &CModelSelectDlg::OnBnClickedButtonModelSelectLoad)
END_MESSAGE_MAP()


// CModelSelectDlg 메시지 처리기입니다.

void CModelSelectDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, RGB_DLG_BG);
}


void CModelSelectDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//this->ShowCurrentModel();
}


BOOL CModelSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CModelSelectDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

void CModelSelectDlg::ShowCurrentModel()
{
	if (g_clModelType.m_nModelIndex == MODERATE_MODEL)
	{
		m_ColorbuttonModelNarrow.state = 0;
		m_ColorbuttonModelModerate.state = 1;

		m_ColorbuttonModelNarrow.Invalidate();
		m_ColorbuttonModelModerate.Invalidate();
	}
	else
	{
		m_ColorbuttonModelModerate.state = 0;
		m_ColorbuttonModelNarrow.state = 1;

		m_ColorbuttonModelNarrow.Invalidate();
		m_ColorbuttonModelModerate.Invalidate();
	}
	
}

void CModelSelectDlg::OnBnClickedButtonModelSelectExit()
{
	ShowWindow(SW_HIDE);
}

void CModelSelectDlg::OnBnClickedButtonModerateModel()
{
	m_ColorbuttonModelNarrow.state = 0;
	m_ColorbuttonModelModerate.state = 1;

	m_ColorbuttonModelNarrow.Invalidate();
	m_ColorbuttonModelModerate.Invalidate();
}


void CModelSelectDlg::OnBnClickedButtonNarrowModel()
{
	m_ColorbuttonModelModerate.state = 0;
	m_ColorbuttonModelNarrow.state = 1;

	m_ColorbuttonModelNarrow.Invalidate();
	m_ColorbuttonModelModerate.Invalidate();
}


void CModelSelectDlg::OnBnClickedButtonModelSelectLoad()
{

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용 불가."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("일시 정지 중 사용 불가."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	CString strModelName = _T("");
	int i;

	//g_clAdo.Disconnect();

	if (m_ColorbuttonModelModerate.state == 1)
	{
		g_clModelType.m_nModelIndex = MODERATE_MODEL;

		strModelName = _T("MODERATE");
		_tcscpy_s(g_clSysData.m_szModelName, SIZE_OF_100BYTE, (TCHAR*)(LPCTSTR)strModelName);
		g_clModelType.mTSave();

		// MODEL TYPE LOAD
		g_clModelType.mTLoad();

		for (i = 0; i < MAX_UNIT_COUNT; i++)
		{
			g_clModelData[i].Load(g_clSysData.m_szModelName);
			//g_clModelData[i].EpoxyDataLoad(g_clSysData.m_szModelName);
			g_clMarkData[i].LoadData(g_clSysData.m_szModelName);
			g_clModelData[i].PatternLoad(g_clSysData.m_szModelName);        //패턴 이미지 로드
			g_clModelData[i].AcmisDataLoad(g_clSysData.m_szModelName);
			
			
		}
	}
	else
	{
		g_clModelType.m_nModelIndex = NARROW_MODEL;
		strModelName = _T("NARROW");
		_tcscpy_s(g_clSysData.m_szModelName, SIZE_OF_100BYTE, (TCHAR*)(LPCTSTR)strModelName);
		g_clModelType.mTSave();

		// MODEL TYPE LOAD
		g_clModelType.mTLoad();

		for (i = 0; i < MAX_UNIT_COUNT; i++)
		{
			g_clModelData[i].Load(g_clSysData.m_szModelName);
			//g_clModelData[i].EpoxyDataLoad(g_clSysData.m_szModelName);
			g_clMarkData[i].LoadData(g_clSysData.m_szModelName);
			g_clModelData[i].PatternLoad(g_clSysData.m_szModelName);        //패턴 이미지 로드
			g_clModelData[i].AcmisDataLoad(g_clSysData.m_szModelName);
		}
	}
}
