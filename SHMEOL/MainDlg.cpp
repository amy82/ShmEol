// MainDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// CMainDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{
	m_nUnit = UNIT_AA1;
	ModelCurCol = 0;
	recipeGridViewMax = 15;
	IdleReportCurrentIndex = -1;
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_MAIN_TITLE, m_clColorStaticTitle);

	DDX_Control(pDX, IDC_STATIC_MAIN_OPERATOR_ID, m_clColorStaticOperatorId);
	DDX_Control(pDX, IDC_STATIC_MAIN_OPERATOR_ID_VAL, m_clColorStaticOperatorIdVal);

	DDX_Control(pDX, IDC_STATIC_MAIN_RECIPE_ID, m_clColorStaticRecipeId);
	DDX_Control(pDX, IDC_COMBO_RECIPE_ID_VAL, m_clComboRecipeId);
	

	DDX_Control(pDX, IDC_STATIC_MAIN_RECIPE, m_clColorStaticRecipe);
	DDX_Control(pDX, IDC_STATIC_MAIN_MODEL, m_clColorStaticModel);

	
	//
	DDX_Control(pDX, IDC_STATIC_MAIN_COMM_STATE, m_clColorStaticCommState);
	DDX_Control(pDX, IDC_STATIC_MAIN_COMM_STATE_VAL, m_clColorStaticCommStateVal);
	DDX_Control(pDX, IDC_STATIC_MAIN_CONTROL_STATE, m_clColorStaticControlState);
	DDX_Control(pDX, IDC_STATIC_MAIN_CONTROL_STATE_VAL, m_clColorStaticControlStateVal);
	//
	//

	DDX_Control(pDX, IDC_BUTTON_MAIN_SAVE, m_clColorButtonMainSave);
	DDX_Control(pDX, IDC_BUTTON_MAIN_MODEL_ADD, m_clColorButtonMainModelAdd);
	DDX_Control(pDX, IDC_BUTTON_MAIN_MODEL_DEL, m_clColorButtonMainModelDel);
	DDX_Control(pDX, IDC_BUTTON_MAIN_MODEL_LOAD, m_clColorButtonMainModelLoad);
	
	DDX_Control(pDX, IDC_BUTTON_MAIN_MODEL_CHANGE, m_clColorButtonMainModelChange);
	DDX_Control(pDX, IDC_BUTTON_MAIN_RECIPE_SAVE, m_clColorButtonMainRecipeSave);
	DDX_Control(pDX, IDC_BUTTON_MAIN_RECIPE_APPLY, m_clColorButtonMainRecipeApply);
	DDX_Control(pDX, IDC_BUTTON_MAIN_RECIPE_DOWN_REQ, m_clColorButtonMainRecipeDown);
	
	DDX_Control(pDX, IDC_BUTTON_MAIN_RECIPE_DEL, m_clColorButtonMainRecipeDelete);
	DDX_Control(pDX, IDC_BUTTON_MAIN_RECIPE_LOAD, m_clColorButtonMainRecipeLoad);
	DDX_Control(pDX, IDC_BUTTON_MAIN_RECIPE_CREATE, m_clColorButtonMainRecipeCreate);
	
	DDX_Control(pDX, IDC_BUTTON_MAIN_ABORTED_REPORT, m_clColorButtonMainAbortedReport);
	DDX_Control(pDX, IDC_BUTTON_MAIN_MATERIAL_ID_REPORT, m_clColorButtonMainMaterialIdReport);
	
	
	DDX_Control(pDX, IDC_EDIT_ABORTED_LOT, m_edtAbortLot);
	DDX_Control(pDX, IDC_EDIT_MATERIAL_ID, m_edtMaterialId);
	

	DDX_Control(pDX, IDC_BUTTON_MAIN_CONTROL_OFFLINE_REQ, m_clColorButtonMainControlOfflineReq);
	DDX_Control(pDX, IDC_BUTTON_MAIN_CONTROL_ONLINE_REMOTE_REQ, m_clColorButtonMainControlOnlineRemoteReq);
	
	
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_MAIN_OPERATOR_ID_VAL, &CMainDlg::OnStnClickedStaticMainOperatorIdVal)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_SAVE, &CMainDlg::OnBnClickedButtonMainSave)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MODEL_ADD, &CMainDlg::OnBnClickedButtonMainModelAdd)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MODEL_DEL, &CMainDlg::OnBnClickedButtonMainModelDel)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MODEL_CHANGE, &CMainDlg::OnBnClickedButtonMainModelChange)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MODEL_LOAD, &CMainDlg::OnBnClickedButtonMainModelLoad)

	ON_NOTIFY(NM_CLICK, IDC_STATIC_MAIN_GRID_RECIPE, &CMainDlg::OnNMClickedRecipeGrid)

	ON_NOTIFY(NM_CLICK, IDC_STATIC_MAIN_GRID_MODEL, &CMainDlg::OnGridClick)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BUTTON_MAIN_RECIPE_SAVE, &CMainDlg::OnBnClickedButtonMainRecipeSave)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_RECIPE_DOWN_REQ, &CMainDlg::OnBnClickedButtonMainRecipeDownReq)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_RECIPE_APPLY, &CMainDlg::OnBnClickedButtonMainRecipeApply)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_RECIPE_DEL, &CMainDlg::OnBnClickedButtonMainRecipeDel)
	ON_CBN_SELCHANGE(IDC_COMBO_RECIPE_ID_VAL, &CMainDlg::OnCbnSelchangeComboRecipeIdVal)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_RECIPE_LOAD, &CMainDlg::OnBnClickedButtonMainRecipeLoad)

	ON_BN_CLICKED(IDC_BUTTON_MAIN_RECIPE_CREATE, &CMainDlg::OnBnClickedButtonMainRecipeCreate)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_ABORTED_REPORT, &CMainDlg::OnBnClickedButtonMainAbortedReport)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MATERIAL_ID_REPORT, &CMainDlg::OnBnClickedButtonMainMaterialIdReport)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_CONTROL_OFFLINE_REQ, &CMainDlg::OnBnClickedButtonMainControlOfflineReq)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_CONTROL_ONLINE_REMOTE_REQ, &CMainDlg::OnBnClickedButtonMainControlOnlineRemoteReq)
END_MESSAGE_MAP()


// CMainDlg 메시지 처리기입니다.


//-----------------------------------------------------------------------------
//
//	RECIPE 그리드 클릭
//
//-----------------------------------------------------------------------------
void CMainDlg::OnNMClickedRecipeGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString szData = _T("");
	CString sMsg = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 0 && nCol > 0)
	{
		//this->ShowSelectedAxis();
	}
	int curCol = nCol;


	//nRow = 세로
	//nCol = 가로
	//
	//nCol 0 = CheckBox, 1 = name , 2 = val
	if ((nRow >= 1 && nRow < recipeGridRow))
	{
		if (nCol == 0)	//CheckBox
		{
			CGridCellCheck* pCheckBox = (CGridCellCheck*)m_clGridRecipe.GetCell(nRow, 0);
			pCheckBox->SetCheck(!pCheckBox->GetCheck());
		}
		else if (nCol == 2)	//Paramval
		{
			CString sData = m_clGridRecipe.GetItemText(nRow, 2);
			CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
			if (pDlg != NULL)
			{
				if (pDlg->DoModal() == IDOK)
				{
					m_clGridRecipe.SetItemText(nRow, nCol, pDlg->GetReturnVal(), 6);
				}

				delete pDlg;
				m_clGridRecipe.Invalidate();
			}
		}
		
	}



	szData.Empty();
	sMsg.Empty();
}
BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 컨트롤 초기화
	this->InitCtrl();

	//콤보박스
	this->setRecipeComboBox();

	// 그리드 초기화
	this->InitModelGridCtrl();
	//
	this->InitRecipeGridCtrl();

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMainDlg::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	ModelCurCol = pItem->iRow;

	if (ModelCurCol > ModelList.m_nTotalCount)
	{
		ModelCurCol = ModelList.m_nTotalCount;
	}

	

	// Trace(_T("Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CMainDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];
	m_nUnit = nUnit;
	_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[MAIN]")); //, m_nUnit + 1);
	GetDlgItem(IDC_STATIC_MAIN_TITLE)->SetWindowText(szTitle);

	this->ShowMainData();
}


void CMainDlg::InitCtrl()
{

	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));


	m_clColorStaticTitle.SetBkColor(RGB_CTRL_BG);
	m_clColorStaticTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTitle.SetFont(&m_clFontBig);
	m_clColorStaticTitle.SetFontBold(TRUE);
	m_clColorStaticTitle.SetBorder(FALSE);
	m_clColorStaticTitle.SetFontSize(15);


	m_clColorStaticOperatorId.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOperatorId.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOperatorId.SetFont(&m_clFontSmall);

	m_clColorStaticOperatorIdVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOperatorIdVal.SetFont(&m_clFontBig);

	m_clColorStaticRecipeId.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRecipeId.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRecipeId.SetFont(&m_clFontSmall);
	


	m_clColorStaticRecipe.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRecipe.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRecipe.SetFont(&m_clFontSmall);

	m_clColorStaticModel.SetBkColor(RGB_DLG_BG);
	m_clColorStaticModel.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticModel.SetFont(&m_clFontSmall);


	m_clColorStaticCommState.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCommState.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCommState.SetFont(&m_clFontSmall);

	m_clColorStaticCommStateVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCommStateVal.SetFont(&m_clFontBig);
	m_clColorStaticCommStateVal.SetFontSize(15);
	m_clColorStaticCommStateVal.SetBorder(TRUE);

	m_clColorStaticControlState.SetBkColor(RGB_DLG_BG);
	m_clColorStaticControlState.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticControlState.SetFont(&m_clFontSmall);
	

	m_clColorStaticControlStateVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticControlStateVal.SetFont(&m_clFontBig);
	m_clColorStaticControlStateVal.SetFontSize(14);
	m_clColorStaticControlStateVal.SetBorder(TRUE);


	m_clComboRecipeId.SetFont(&m_clFontSmall);


	m_edtAbortLot.SetWindowTextA(_T("0"));
	m_edtMaterialId.SetWindowTextA(_T("0"));
}
void CMainDlg::GetGridData()
{


}
void CMainDlg::ShowGridData()
{
	int i = 0;
	CString sData = _T("");
	ModelCurCol = ModelList.m_nCurrentNo;
	for (i = 0; i < g_MaxModelCount; i++)
	{
		int mCount = ModelList.m_clModelList.GetCount();
		if (i < mCount)
		{
			m_clGridModel.SetItemText(i + 1, 1, ModelList.m_clModelList[i].m_szName);


			if (i == ModelList.m_nCurrentNo - 1)
			{
				m_clGridModel.SetItemBkColor(i + 1, 1, MODEL_GRID_COLOR_SELECT);
			}
			else
			{
				m_clGridModel.SetItemBkColor(i + 1, 1, GRID_COLOR_WHITE);
			}
		}
		else
		{
			m_clGridModel.SetItemText(i + 1, 1, _T(""));
		}


		
		
	}
	m_clGridModel.Invalidate();
	sData.Empty();
}
void CMainDlg::ModelListDataSet()
{
	
	int cnt = g_clReportData.vModelLIst.size();
	if (cnt > 0)
	{
		int i = 0;
		CModelInfo clModelInfo;
		ModelList.m_clModelList.RemoveAll();

		for (i = 0; i < cnt; i++)
		{
			clModelInfo.m_nNo = i + 1;
			_tcscpy_s(clModelInfo.m_szName, SIZE_OF_100BYTE, g_clReportData.vModelLIst[i].cepVal);
			ModelList.m_clModelList.Add(clModelInfo);
		}

		ModelList.ModelListSave();
		ModelList.ModelListLoad();
		ShowGridData();
	}
}
void CMainDlg::InitIdleReasonSet()
{
	int i = 0;
	for (i = 0; i < 1; i++)
	{


	}
	//비가동 사유 콤보 박스 추가하기
}
//----------------------------------------------------------------------------- 
//
// RECIPE GRID GET
//
//-----------------------------------------------------------------------------

int CMainDlg::getRecipeGrid()
{
	int i = 0;
	int j = 0;
	CString sData = _T("");
	CString sName = _T("");
	TCHAR szLog[SIZE_OF_1K];
	int nRtn = 0;	//0 = 은 변경이 없는 경우

	currentRecipeNo = m_clComboRecipeId.GetCurSel();
	m_clComboRecipeId.GetLBText(currentRecipeNo, sData);


	//
	g_clMesCommunication[m_nUnit].m_sMesPPID.Format(_T("%s"), sData);		// getRecipeGrid Send S1F11 Save button

	if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() > 0)
	{
		g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].PPId = sData.GetString();
	}
	g_clMesCommunication[m_nUnit].m_sMesRecipeRevision.Format(_T("%s"), g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].VERSION.c_str());	//get Grid
	int GridRow = m_clGridRecipe.GetRowCount() - 1;

	int getCount = g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMap.size();

	for (i = 0; i < GridRow; i++)	//Grid 총 개수라서 title 1개 빠져야된다.
	{
		sName = m_clGridRecipe.GetItemText(i + 1, 1);	//1 = name , 2 = val
		sData = m_clGridRecipe.GetItemText(i + 1, 2);	//1 = name , 2 = val
		CGridCellCheck* pCheckBox = (CGridCellCheck*)m_clGridRecipe.GetCell(i + 1, 0);
		BOOL bChk = FALSE;

		//parmMapChk
		//if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmChecked[i] == "1")
		if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk[sName.GetString()] == "1")
		{
			bChk = TRUE;
		}
		if (bChk != pCheckBox->GetCheck())
		{
			nRtn = eUploadListChanged;
		}
		if (pCheckBox->GetCheck() == TRUE)
		{
			//g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmChecked[i] = "1";
			g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk[sName.GetString()] = "1";
		}
		else
		{
			//g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmChecked[i] = "0";
			g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk[sName.GetString()] = "0";
		}
		
		
		if (pCheckBox->GetCheck() == TRUE)
		{
			
			if (i < getCount)
			{
				//if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmChecked[i] == "1")
				if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk[sName.GetString()] == "1")
				{
					//if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmVal[i] != sData.GetString())		//순서 확인하고 넣어야 할수도
					if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMap[sName.GetString()] != sData.GetString())		//순서 확인하고 넣어야 할수도
					{
						nRtn = eEdited;
					}
				}
				//g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmVal[i] = sData.GetString();	//순서가 바껴있으면 위험
				
				g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMap[sName.GetString()] = sData.GetString();// g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmVal[i];
			}
		}
	}


	return nRtn;		//0일대 변경 없음 , 1 = 체크만 바꼈을때 , 2 값만 변경
}
//----------------------------------------------------------------------------- 
//
// RECIPE GRID SHOW
//
//-----------------------------------------------------------------------------

void CMainDlg::showRecipeGrid()
{

	int i = 0;
	int j = 0;
	int GRID_DLG = IDC_STATIC_MAIN_GRID_RECIPE;
	CWnd *pWnd = (CWnd*)GetDlgItem(GRID_DLG);
	int gridWidth1 = 25;
	int gridWidth2 = 240;
	int gridWidth3 = 100;
	int totalWidth = gridWidth1 + gridWidth2 + gridWidth3;
	int xMargin = 21;
	int margin = 4;
	CString sData = _T("");
	TCHAR szLog[SIZE_OF_1K];
	int row = 1;

	int nOldNumRows = m_clGridRecipe.GetRowCount();


	CRect rect;
	int totalCnt = g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size(); 

	if (totalCnt > 0)
	{
		GetDlgItem(GRID_DLG)->GetWindowRect(rect);
		ScreenToClient(rect);

		//for (i = 0; i < 1; i++)		//1로 고정
		int subCnt = g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmName.size();

		
		if (subCnt < recipeGridViewMax)
		{
			recipeGridRow = recipeGridViewMax;
		}
		else
		{
			recipeGridRow = subCnt + 1;
		}
		

		m_clGridRecipe.SetEditable(TRUE);
		rect.right = totalWidth + xMargin + 0; 
		//rect.bottom = (gridHeight*nSizeGridRow) + margin;
		rect.bottom = (recipeGridHeight * recipeGridViewMax) + margin;
		
		pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.
		
		GetDlgItem(GRID_DLG)->GetWindowRect(rect);
		ScreenToClient(rect);

		m_clGridRecipe.MoveWindow(rect);

		m_clGridRecipe.SetRowCount(recipeGridRow);
		
		for (i = 0; i < recipeGridRow - 1; i++)	//Title 은빼야돼서 -1
		{

			if (i == 0)
			{
				m_clGridRecipe.SetColumnWidth(0, gridWidth1);
				if (subCnt < recipeGridViewMax)
				{
					m_clGridRecipe.SetColumnWidth(1, gridWidth2 + 17);
				}
				else
				{
					m_clGridRecipe.SetColumnWidth(1, gridWidth2);
				}
				
				m_clGridRecipe.SetColumnWidth(2, gridWidth3);
				
			}


			if (i < subCnt)
			{
				m_clGridRecipe.SetRowHeight(i + 1, recipeGridHeight);
				if (m_clGridRecipe.SetCellType(i + 1, 0, RUNTIME_CLASS(CGridCellCheck)) == false)
				{
					continue;
				}
				// 체크박스를 처음부터 선택된 상태로 설정
				CGridCellCheck* pCheckBox = (CGridCellCheck*)m_clGridRecipe.GetCell(i + 1, 0);

				//if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmChecked[i] == "1")
				if(g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk[g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmName[i]] == "1")
				{
					pCheckBox->SetCheck(TRUE);
				}
				else
				{
					pCheckBox->SetCheck(FALSE);
				}
				

				m_clGridRecipe.SetItemText(i + 1, 1, g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmName[i].c_str());
				m_clGridRecipe.SetItemText(i + 1, 2, atof(g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMap[g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmName[i]].c_str()), 6);
				//m_clGridRecipe.SetItemText(i + 1, 2, atof(g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmVal[i].c_str()), 6);

				m_clGridRecipe.SetItemFormat(i + 1, 1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				m_clGridRecipe.SetItemFormat(i + 1, 2, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				CGridCellCheck* pCheckBox = (CGridCellCheck*)m_clGridRecipe.GetCell(i + 1, 0);

				// 체크박스를 체크된 상태로 설정 (TRUE: 선택된 상태)
				pCheckBox->SetCheck(FALSE);

				m_clGridRecipe.SetItemText(i + 1, 1, _T(""));
				m_clGridRecipe.SetItemText(i + 1, 2, _T(""));
			}
		}
	}

	m_clGridRecipe.Invalidate();

	m_clGridRecipe.SetEditable(FALSE);
}

//----------------------------------------------------------------------------- 
//
// 그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CMainDlg::InitRecipeGridCtrl()
{
	CRect rect;
	int i, j;
	int GRID_DLG = IDC_STATIC_MAIN_GRID_RECIPE;
	CWnd *pWnd = (CWnd*)GetDlgItem(GRID_DLG);
	int subCnt = 1;
	if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() > 0)
	{
		subCnt = g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmName.size();
	}


	GridCol = 3;	//오른쪽
	int margin = 4;
	recipeGridHeight = 30;
	int gridWidth1 = 25;
	int gridWidth2 = 240;
	int gridWidth3 = 100;
	//int totalWidth = gridWidth1 + gridWidth2 + (gridWidth3*(GridCol - 1));
	int totalWidth = gridWidth1 + gridWidth2 + gridWidth3;
	int viewRow = recipeGridViewMax;
	int xMargin = 21;
	recipeGridRow = subCnt + 1;	//아래쪽
	int nSizeGridRow = GridRow - 2;



	GetDlgItem(GRID_DLG)->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + xMargin;
	//rect.bottom = (gridHeight*nSizeGridRow) + margin;
	rect.bottom = (recipeGridHeight * viewRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(GRID_DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridRecipe.Create(rect, this, GRID_DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridRecipe.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridRecipe.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridRecipe.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridRecipe.SetReference_Setting();
	m_clGridRecipe.SetEditable(TRUE);
	m_clGridRecipe.EnableSelection(FALSE);

	m_clGridRecipe.SetRowCount(recipeGridRow);
	m_clGridRecipe.SetColumnCount(GridCol);
	m_clGridRecipe.SetFixedRowCount(1);			//가로
	//m_clGridRecipe.SetFixedColumnCount(1);	//세로

	//TCHAR* pszCol[] = { _T("Lcb"), _T("Spec") };
	CString sData = _T("");

	m_clGridRecipe.SetItemText(0, 0, _T(""));
	m_clGridRecipe.SetItemText(0, 1, _T("PPARMNAME"));
	m_clGridRecipe.SetItemText(0, 2, _T("PPARAMVAL"));

	for (i = 0; i < recipeGridRow; i++)		//GridRow = 207
	{
		m_clGridRecipe.SetRowHeight(i, recipeGridHeight);
		if (i > 0)
		{
			if (m_clGridRecipe.SetCellType(i, 0, RUNTIME_CLASS(CGridCellCheck)) == false)
			{
				continue;
			}
			// 체크박스를 처음부터 선택된 상태로 설정
			CGridCellCheck* pCheckBox = (CGridCellCheck*)m_clGridRecipe.GetCell(i, 0);

			// 체크박스를 체크된 상태로 설정 (TRUE: 선택된 상태)
			pCheckBox->SetCheck(TRUE); 
		}
		 for (j = 0; j < GridCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridRecipe.SetColumnWidth(j, gridWidth1);
					//m_clGridRecipe.SetCellType(i, j, RUNTIME_CLASS(CGridCellCheck));
					
				}
				else if (j == 1)
				{
					m_clGridRecipe.SetColumnWidth(j, gridWidth2);
					m_clGridRecipe.SetItemText(1, j, _T("Parameter 01"));
				}
				else
				{
					m_clGridRecipe.SetColumnWidth(j, gridWidth3);
					m_clGridRecipe.SetItemText(1, j, _T("100.000000"));
				}

			}
			m_clGridRecipe.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}

	
	

	
	m_clGridRecipe.SetEditable(FALSE);
	m_clGridRecipe.Invalidate();




	sData.Empty();
}

//-----------------------------------------------------------------------------
//
// RECIPE 콤보 박스
//
//-----------------------------------------------------------------------------
void CMainDlg::setRecipeComboBox()
{
	m_clComboRecipeId.ResetContent();

	//
	int mCount = ModelList.m_vRecipeVec.size();
	currentRecipeNo = -1;
	for (int i = 0; i < mCount; i++)
	{
		if (ModelList.m_vRecipeVec[i].c_str() == g_clMesCommunication[m_nUnit].m_sMesPPID)
		{
			currentRecipeNo = i;
		}
		//m_clComboRecipeId.InsertString(0, ModelList.m_clRecipeList[i].m_szName);
		m_clComboRecipeId.AddString(ModelList.m_vRecipeVec[i].c_str());
	}
	TCHAR szLog[SIZE_OF_1K];


	int itemCount = m_clComboRecipeId.GetCount();
	if (itemCount < 1 || currentRecipeNo < 0)//ModelList.m_nRecipeCurrentNo < 0 || ModelList.m_nRecipeCurrentNo > itemCount)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[RECIPE] Empty"));
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		m_clComboRecipeId.SetCurSel(currentRecipeNo);
	}

}

//-----------------------------------------------------------------------------
//
// 그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CMainDlg::InitModelGridCtrl()
{
	CRect rect;
	int i, j;
	int GRID_DLG = IDC_STATIC_MAIN_GRID_MODEL;
	CWnd *pWnd = (CWnd*)GetDlgItem(GRID_DLG);
	GridRow = g_MaxModelCount + 1;	//아래쪽

	GridCol = 2;	//오른쪽
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 50;
	int gridWidth2 = 200;
	int totalWidth = gridWidth1 + (gridWidth2*(GridCol - 1));
	int nSizeGridRow = GridRow - 2; // 	- 레이저
	GetDlgItem(GRID_DLG)->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	//rect.bottom = (gridHeight*nSizeGridRow) + margin;
	rect.bottom = (gridHeight * GridRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(GRID_DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridModel.Create(rect, this, GRID_DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridModel.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridModel.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridModel.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridModel.SetReference_Setting();
	m_clGridModel.EnableSelection(FALSE);

	m_clGridModel.SetRowCount(GridRow);
	m_clGridModel.SetColumnCount(GridCol);
	m_clGridModel.SetFixedRowCount(1);
	m_clGridModel.SetFixedColumnCount(1);


	//TCHAR* pszCol[] = { _T("Lcb"), _T("Spec") };
	CString sData = _T("");

	m_clGridModel.SetItemText(0, 0, _T("No"));
	m_clGridModel.SetItemText(0, 1, _T("Model"));

	for (i = 0; i < GridRow; i++)
	{
		m_clGridModel.SetRowHeight(i, gridHeight);
		if (i > 0)
		{
			sData.Format(_T("%d"), i);
			m_clGridModel.SetItemText(i, 0, sData);

			
		}
		
		for (j = 0; j < GridCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridModel.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridModel.SetColumnWidth(j, gridWidth2);
					
				}
			}
			m_clGridModel.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	sData.Empty();
}

void CMainDlg::setCommunicationState(int state)
{
	switch (state)
	{
	case 1:
		m_clColorStaticCommStateVal.SetWindowText(_T("Disabled"));
		break;
	case 2:
		m_clColorStaticCommStateVal.SetWindowText(_T("Enabled"));
		break;
	case 3:
		m_clColorStaticCommStateVal.SetWindowText(_T("NotCommunication"));
		break;
	case 4:
		m_clColorStaticCommStateVal.SetWindowText(_T("WaitCRFromHost"));
		break;
	case 5:
		m_clColorStaticCommStateVal.SetWindowText(_T("WaitDelay"));
		break;
	case 6:
		m_clColorStaticCommStateVal.SetWindowText(_T("WaitCRA"));
		break;
	case 7:
		m_clColorStaticCommStateVal.SetWindowText(_T("Communicating"));
		break;
	default:
		m_clColorStaticCommStateVal.SetWindowText(_T("OffLine"));
		break;
	}
	m_clColorStaticCommStateVal.Invalidate();
	/*typedef enum __GEMCommunicationState
	{
		GEMCommunicationState_Disabled = 1,
		GEMCommunicationState_Enabled = 2,
		GEMCommunicationState_NotCommunication = 3,
		GEMCommunicationState_WaitCRFromHost = 4,
		GEMCommunicationState_WaitDelay = 5,
		GEMCommunicationState_WaitCRA = 6,
		GEMCommunicationState_Communicating = 7
	} GEMCommunicationState;*/
}
void CMainDlg::setControlState(int state)
{
	g_pCarAABonderDlg->m_clButtonMes[0].state = 0;

	m_clColorButtonMainControlOfflineReq.state = 0;
	m_clColorButtonMainControlOnlineRemoteReq.state = 0;
	switch (state)
	{
	case 1:
		
		m_clColorStaticControlStateVal.SetWindowText(_T("Connected / EquipmentOffline"));
		break;
	case 2:
		m_clColorStaticControlStateVal.SetWindowText(_T("Connected / AttemptOnline"));
		break;
	case 3:
		m_clColorStaticControlStateVal.SetWindowText(_T("Disconnected / HostOffline"));
		break;
	case 4:
		g_pCarAABonderDlg->m_clButtonMes[0].state = 1;
		m_clColorButtonMainControlOnlineRemoteReq.state = 1;
		m_clColorStaticControlStateVal.SetWindowText(_T("Connected / OnlineLocal"));
		break;
	case 5:
		g_pCarAABonderDlg->m_clButtonMes[0].state = 1;
		m_clColorButtonMainControlOnlineRemoteReq.state = 1;
		m_clColorStaticControlStateVal.SetWindowText(_T("Connected / OnlineRemote"));
		break;
	default:
		m_clColorStaticControlStateVal.SetWindowText(_T("Disconnected / EquipmentOffline"));
		break;
	}
	if (m_clColorButtonMainControlOnlineRemoteReq.state == 0)
	{
		m_clColorButtonMainControlOfflineReq.state = 1;
	}
	g_pCarAABonderDlg->m_clButtonMes[0].Invalidate();

	m_clColorStaticControlStateVal.Invalidate();
	m_clColorButtonMainControlOfflineReq.Invalidate();
	m_clColorButtonMainControlOnlineRemoteReq.Invalidate();
	/*typedef enum __GEMControlState
	{
	GEMControlState_EquipmentOffline = 1,
	GEMControlState_AttemptOnline = 2,
	GEMControlState_HostOffline = 3,
	GEMControlState_OnlineLocal = 4,
	GEMControlState_OnlineRemote = 5
	} GEMControlState;*/
}

//-----------------------------------------------------------------------------
//
//	티칭 데이터 표시
//
//-----------------------------------------------------------------------------
void CMainDlg::ShowMainData()
{
	TCHAR szData[SIZE_OF_100BYTE];

	m_clColorStaticOperatorIdVal.SetWindowText(g_clMesCommunication[m_nUnit].m_sMesOperatorID);


	//_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nRoiSizeX);
	//m_clColorStaticSfrXSizeVal.SetWindowText(szData);
}


void CMainDlg::GetMainData()
{
	CString sData = _T("");

	m_clColorStaticOperatorIdVal.GetWindowText(sData);
	g_clMesCommunication[m_nUnit].m_sMesOperatorID = sData;
	//m_clColorStaticOperatorIdVal.SetWindowText(g_clMesCommunication[m_nUnit].m_sMesOperatorID);
	// 단변	
	//
	//g_clModelData[m_nUnit].m_nRoiSizeX = _ttoi((TCHAR*)(LPCTSTR)sData);
}

void CMainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, RGB_DLG_BG);
}


HBRUSH CMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_RADIO_MANUAL_LASER_1)
	{
		pDC->SetTextColor(RGB_COLOR_WHITE);
		pDC->SetBkMode(TRANSPARENT);

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMainDlg::OnStnClickedStaticMainOperatorIdVal()
{

	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		CString sData;
		m_clColorStaticOperatorIdVal.GetWindowText(sData);
		pDlg->SetReturnValue(sData);
		if (pDlg->DoModal() == IDOK)
		{

			if (g_ShowMsgModal(_T("확인"), _T("OPERATOR ID 저장하시겠습니까?"), RGB_COLOR_RED) == true)
			{

			
				this->GetMainData();


				g_clMesCommunication[m_nUnit].secsGemSave();		//OP ID SAVE
				g_clMesCommunication[m_nUnit].secsGemLoad();

				ShowMainData();

				AddLog(_T("[INFO] MAIN 설정 저장"), 0, m_nUnit);


				m_clColorStaticOperatorIdVal.SetWindowText(pDlg->GetReturnValue());

				g_clMesCommunication[m_nUnit].m_sMesOperatorID.Format(_T("%s"), pDlg->GetReturnValue());
			}
		}

		delete pDlg;
	}
}


void CMainDlg::OnBnClickedButtonMainSave()
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

	
}


void CMainDlg::OnBnClickedButtonMainModelAdd()
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
	int i = 0;
	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			TCHAR szIniBuff[SIZE_OF_1K];
			//pDlg->GetReturnValue()
			//m_clColorStaticOperatorIdVal.SetWindowText(pDlg->GetReturnValue());

			//g_clMesCommunication[m_nUnit].m_sMesOperatorID.Format(_T("%s"), pDlg->GetReturnValue());
			CModelInfo clModelInfo;
			clModelInfo.m_nNo = ModelList.m_clModelList.GetCount() + 1;// i + 1;
			_tcscpy_s(clModelInfo.m_szName, SIZE_OF_100BYTE, pDlg->GetReturnValue());
			ModelList.m_clModelList.Add(clModelInfo);
		}

		delete pDlg;
	}

	//Get Data

	ModelList.ModelListSave();
	ModelList.ModelListLoad();

	ShowGridData();
	//Show Data
}


void CMainDlg::OnBnClickedButtonMainModelDel()
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


	//ModelList.m_nCurrentNo = ModelCurCol;
	int mCount = ModelList.m_clModelList.GetCount();
	if (ModelCurCol <= mCount)
	{
		if (ModelList.m_nCurrentNo >= ModelCurCol)
		{
			ModelList.m_nCurrentNo -= 1;
		}
		ModelList.m_clModelList.RemoveAt(ModelCurCol - 1);

		ModelList.ModelListSave();
		ModelList.ModelListLoad();

		ShowGridData();
	}
	

	


	//TCHAR szLog[SIZE_OF_1K];
	//_stprintf_s(szLog, SIZE_OF_1K, _T("[MODEL] DEL MODEL :(%s)"), ModelList.m_szCurrentModel);
	//AddLog(szLog, 0, 0);
}


void CMainDlg::OnBnClickedButtonMainModelChange()
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

	int i = 0;
	CString sData = _T("");
	sData = m_clGridModel.GetItemText(ModelCurCol, 1);


	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	pDlg->SetReturnValue(sData);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			TCHAR szIniBuff[SIZE_OF_1K];
			_stprintf_s(ModelList.m_clModelList[ModelCurCol-1].m_szName, SIZE_OF_100BYTE, _T("%s"), pDlg->GetReturnValue());

			ModelList.ModelListSave();
			ModelList.ModelListLoad();

			ShowGridData();
		}

		delete pDlg;
	}
	sData.Empty();
}

//LOAD
void CMainDlg::OnBnClickedButtonMainModelLoad()
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


	ModelList.m_nCurrentNo = ModelCurCol;


	ModelList.ModelListSave();
	ModelList.ModelListLoad();

	ShowGridData();


	//strLog.Format(_T("[MODEL] %s/%d - Load 완료") , modelList.curModelName , ModelCurCol);
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("[MODEL] CURRENT MODEL :(%s)"), ModelList.m_szCurrentModel);
	AddLog(szLog, 0, 0);
}


void CMainDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow == TRUE)
	{
		//Recipe xml Load
		//Recipe Parameter Grid show
		m_clComboRecipeId.SetCurSel(currentRecipeNo);

		//
		m_edtAbortLot.SetWindowTextA(g_clTaskWork[m_nUnit].m_szChipID);
		m_edtMaterialId.SetWindowTextA(g_clReportData.rMaterial_Id_Confirm.MaterialId);
		ShowGridData();

		showRecipeGrid();
	}
}
void CMainDlg::OnCbnSelchangeComboRecipeIdVal()
{
	//RECIPE 
	//COMBOX 변경됐을때


	

}

void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
}


void CMainDlg::OnBnClickedButtonMainRecipeSave()
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
	TCHAR szLog[SIZE_OF_1K];
	//S6F11
	//Event = Process Program State Changed Report)
	CString sData = _T("");
	CString sMsg = _T("");
	m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sData);

	if (sData != g_clMesCommunication[m_nUnit].m_sMesPPID)
	{
		sMsg.Format(_T("(%s) 사용중인 RECIPE ID가 아닙니다."), sData);
		g_ShowMsgPopup(_T("ERROR"), sMsg, RGB_COLOR_RED);
		return;
	}

	int ppIndex = getRecipeGrid();	//2 = 값이 변경, 4 = 체크 변경

	if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() < 1)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Recipe Empty Save Fail"));
		AddLog(szLog, 0, 0);
		return;
	}
	if (ppIndex == 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Recipe no Change"));
		AddLog(szLog, 0, 0);

		g_ShowMsgPopup(_T("INFO"), szLog, RGB_COLOR_RED);
		return;
	}
	//체크가 다르면 4
	//값이 바뀌면 2번
	g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = ppIndex;		//4 = UploadListChanged   2 = Edited
	g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eOperator;		//1 = Host, 2 = Operator

	if (g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] == eEdited)
	{
		//eEdited면 version 을 1씩 플러스??
		int tempVer = stoi(g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].VERSION);
		tempVer++;
		if (tempVer < 1)
		{
			tempVer = 1;
		}
		g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].VERSION = to_string(tempVer);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Rerpot] Process Program State Changed Report - Edited(%s)"), g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].VERSION.c_str());
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Rerpot] Process Program State Changed Report - UploadListChanged"));
	}
	AddLog(szLog, 0, 0);


	g_clMesCommunication[m_nUnit].RecipeIniSave(g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip);
	ModelList.RecipeModelSave();

	


	


	m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sData);

	g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601, sData);	//--------Save Button



	sData.Empty();
	sMsg.Empty();
}


void CMainDlg::OnBnClickedButtonMainRecipeDownReq()
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

	//Download Request
	//S7F25 - Formatted Process Program Request

	CString sData = _T("");
	m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sData);

	g_pCarAABonderDlg->m_clUbiGemDlg.FormattedProcessProgramRequest(sData);	//S7F25 - Formatted Process Program Request
	
}


void CMainDlg::OnBnClickedButtonMainRecipeApply()
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

	//팝업뜨고 apply 선택시

	//S6F11 - Event = Process Program State Changed Report
	//2.Edited
	//2.by Operator


	CWnd* pMainWnd = AfxGetMainWnd();  // 메인 윈도우 가져오기

									   // 메시지 박스 표시 (제목을 "Confirmation"으로 설정)
									   //SetWindowPos(pMainWnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	int result = pMainWnd->MessageBox(_T("Apply Host Recipe Parameter Value?"), _T("Apply Host Recipe Confirm!!!"), MB_YESNO | MB_ICONQUESTION | MB_SERVICE_NOTIFICATION);


	if (result == IDYES)
	{
		// 사용자가 Yes를 선택한 경우
		//AfxMessageBox(_T("You clicked Yes."));
		CString sData = _T("");
		m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sData);


		if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() > 0)
		{
			g_clMesCommunication[m_nUnit].m_sMesRecipeRevision.Format(_T("%s"), g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].VERSION.c_str());	//Apply
		}

		g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eEdited;		//2 (Edited)
		g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eOperator;		//1 = Host, 2 = Operator


		g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601, sData);	//----Apply button
	}
}


void CMainDlg::OnBnClickedButtonMainRecipeDel()
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


	//S6F11
	//Event = Process Program State Changed Report)


	CString sData = _T("");
	CString sMsg = _T("");
	m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sData);

	if (sData == g_clMesCommunication[m_nUnit].m_sMesPPID)
	{
		sMsg.Format(_T("(%s) 사용중인 RECIPE ID 입니다."), sData);
		g_ShowMsgPopup(_T("ERROR"), sMsg, RGB_COLOR_RED);
		return;
	}

	sMsg.Format(_T("(%s) RECIPE ID 삭제하시겠습니까?"), sData);
	if (g_ShowMsgModal(_T("확인"), sMsg, RGB_COLOR_RED) == false)
	{
		return;
	}
	


	if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() > 0)
	{
		g_clMesCommunication[m_nUnit].m_sMesRecipeRevision.Format(_T("%s"), g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].VERSION.c_str());		//xxx
	}
	g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eDeleted;		//3 Deleted
	g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eOperator;		//1 = Host, 2 = Operator


	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("[Rerpot] Process Program State Changed Report - Deleted"));
	AddLog(szLog, 0, 0);


	m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sData);
	g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601, sData);	//----Del button 사용안함 xxxx
	



	ModelList.xmlRecipeDelete(sData);		//RECIPE XML FILE DELETE

	ModelList.iniRecipeListLoad();	//XML 파일 생성후 전체 LIST LOAD

	setRecipeComboBox();	//Recipe 콤보박스 갱신
	sData.Empty();
}





void CMainDlg::OnBnClickedButtonMainRecipeLoad()
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


	//S6F11
	//Event = Process Program State Changed Report)

	CString sData = _T("");
	CString sMsg = _T("");
	m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sData);

	sMsg.Format(_T("(%s) RECIPE ID로 변경 하시겠습니까?"), sData);

	if (g_ShowMsgModal(_T("확인"), sMsg, RGB_COLOR_RED) == false)
	{
		return;
	}
	if (sData == g_clMesCommunication[m_nUnit].m_sMesPPID)
	{
		//이미 사용중인 레시피 입니다.
		sMsg.Format(_T("이미 사용중인 레시피입니다.(%s)"), sData);	// TODO: 레시피 변경시 기존 레시피 확인하기 250217
		AddLog(sMsg, 1, m_nUnit);
		return;
	}
	TCHAR szLog[SIZE_OF_1K];

	int nIndex = m_clComboRecipeId.GetCurSel();
	m_clComboRecipeId.GetLBText(nIndex, sData);

	_stprintf_s(szLog, SIZE_OF_1K, _T("[RECIPE] CURRENT :(%s)"), sData);
	AddLog(szLog, 0, m_nUnit);

	//현재 모델 변경해야된다.

	//ini Load
	g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip = g_clMesCommunication[m_nUnit].RecipeIniLoad(sData);

	if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() < 1)
	{
		sMsg.Format(_T("(%s) RECIPE LOAD FAIL"), sData);
		g_ShowMsgPopup(_T("ERROR"), sMsg, RGB_COLOR_RED);
		return;
	}
	currentRecipeNo = nIndex;
	//Grid show
	showRecipeGrid();


	g_clMesCommunication[m_nUnit].m_sMesPPID.Format(_T("%s"), sData);	//Send S1F11  Load Button
	g_clMesCommunication[m_nUnit].m_sRecipeId.Format(_T("%s"), sData);
	g_clMesCommunication[m_nUnit].m_sMesRecipeRevision.Format(_T("%s"), g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].VERSION.c_str());	//Load

	ModelList.RecipeModelSave();
}


void CMainDlg::OnBnClickedButtonMainRecipeCreate()
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

	TCHAR szLog[SIZE_OF_1K];

	int i = 0;


	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		CString sCopyData = _T("");
		CString sMsg = _T("");
		m_clComboRecipeId.GetLBText(m_clComboRecipeId.GetCurSel(), sCopyData);

		pDlg->SetReturnValue(sCopyData);
		if (pDlg->DoModal() == IDOK)
		{
			sMsg.Format(_T("(%s) RECIPE 생성 하시겠습니까?"), pDlg->GetReturnValue());

			if (g_ShowMsgModal(_T("확인"), sMsg, RGB_COLOR_RED) == true)
			{

				//이미 존재하는 레시피인지 확인
				int mCount = ModelList.m_vRecipeVec.size();
				for (i = 0; i < mCount; i++)
				{
					if (ModelList.m_vRecipeVec[i].c_str() == pDlg->GetReturnValue())	// TODO: 레시피 생성시 기존 레시피 확인하기 250217
					{
						sMsg.Format(_T("이미 존재하는 레시피입니다.(%s)"), pDlg->GetReturnValue());
						AddLog(sMsg, 1, m_nUnit);
						return;
					}
				}


				//xml 파일 생성
				ModelList.xmlRecipeCreate(sCopyData, pDlg->GetReturnValue());	//파일 복사


				std::vector<_PP_RECIPE_SPEC> vRecipeTemp = g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip;
				if (vRecipeTemp.size() > 0)
				{
					vRecipeTemp[0].PPId = pDlg->GetReturnValue();
					vRecipeTemp[0].VERSION = "1";

					g_clMesCommunication[m_nUnit].RecipeIniSave(vRecipeTemp);


					ModelList.iniRecipeListLoad();	//XML 파일 생성후 전체 LIST LOAD

					setRecipeComboBox();	//Recipe 콤보박스 갱신

					g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eCreated;		//1 = Created
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eOperator;		//1 = Host, 2 = Operator


					TCHAR szLog[SIZE_OF_1K];
					_stprintf_s(szLog, SIZE_OF_1K, _T("[Rerpot] Process Program State Changed Report - Created"));
					AddLog(szLog, 0, 0);


					g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601, vRecipeTemp[0].PPId.c_str());	//----Create Button
				}
				else
				{
					AddLog(_T("[INFO] Recipe Create Fail"), 1, m_nUnit);
				}
				
			}
		}

		delete pDlg;
	}
}


void CMainDlg::OnBnClickedButtonMainAbortedReport()
{
	CString sData = _T("");
	CString sMsg = _T("");
	m_edtAbortLot.GetWindowText(sData);
	if (sData.GetLength() < 1)
	{
		sMsg.Format(_T("LOT 입력해 주세요."));
		g_ShowMsgPopup(_T("ERROR"), sMsg, RGB_COLOR_RED);
		return;
	}
	


	

	sMsg.Format(_T("(%s) LOT ABORT? "), sData);

	if (g_ShowMsgModal(_T("확인"), sMsg, RGB_COLOR_RED) == false)
	{
		return;
	}
	g_clReportData.strAbortedLot = sData.GetString();


	sMsg.Format(_T("(%s) LOT ABORT REPORT "), sData);
	AddLog(sMsg, 0, 0);
	g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(ABORTED_REPORT_10712);



	sData.Empty();
	sMsg.Empty();
}


void CMainDlg::OnBnClickedButtonMainMaterialIdReport()
{
	CString sData;
	CString sMsg;
	m_edtMaterialId.GetWindowText(sData);

	if (sData.GetLength() < 1)
	{
		sMsg.Format(_T("MATERIAL ID 입력해 주세요."));
		g_ShowMsgPopup(_T("ERROR"), sMsg, RGB_COLOR_RED);
		return;
	}





	sMsg.Format(_T("(%s) MATERIAL ID REPORT? "), sData);

	if (g_ShowMsgModal(_T("확인"), sMsg, RGB_COLOR_RED) == false)
	{
		return;
	}

	g_clReportData.rMaterial_Id_Confirm.MaterialId = sData;

	sMsg.Format(_T("(%s) MATERIAL ID REPORT "), sData);
	AddLog(sMsg, 0, 0);

	g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(MATERIAL_ID_REPORT_10713);
}


void CMainDlg::OnBnClickedButtonMainControlOfflineReq()
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

	CString sMsg;
	sMsg.Format(_T("설비 오프라인 전환하시겠습니까? "));

	if (g_ShowMsgModal(_T("확인"), sMsg, RGB_COLOR_RED) == false)
	{
		return;
	}


	AddLog(_T("[INFO] Online Offline Req"), 0, m_nUnit);
	g_pCarAABonderDlg->m_clUbiGemDlg.OnBnClickedButtonUbigemCsOffline();
	sMsg.Empty();
}


void CMainDlg::OnBnClickedButtonMainControlOnlineRemoteReq()
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
	CString sMsg;
	sMsg.Format(_T("설비 온라인 전환하시겠습니까? "));

	if (g_ShowMsgModal(_T("확인"), sMsg, RGB_COLOR_RED) == false)
	{
		return;
	}


	AddLog(_T("[INFO] Online Remote Req"), 0, m_nUnit);
	g_pCarAABonderDlg->m_clUbiGemDlg.OnBnClickedButtonUbigemCsOnlineRemote();
	sMsg.Empty();
}
