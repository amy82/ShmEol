#pragma once


// CMainDlg 대화 상자입니다.
#include "Utility\GridCtrl\GridCtrl.h"

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMainDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	void ShowMainData();
	void GetMainData();
	void InitModelGridCtrl();
	void InitRecipeGridCtrl();
	void setRecipeComboBox();

	void showRecipeGrid();
	int getRecipeGrid();

	void InitIdleReasonSet();

	CLabel m_clColorStaticTitle;

	CLabel m_clColorStaticOperatorId;
	CLabel m_clColorStaticOperatorIdVal;

	CLabel m_clColorStaticRecipeId;

	CLabel m_clColorStaticRecipe;
	CLabel m_clColorStaticModel;

	CLabel m_clColorStaticCommState;
	CLabel m_clColorStaticCommStateVal;
	CLabel m_clColorStaticControlState;
	CLabel m_clColorStaticControlStateVal;
	


	CButtonCT m_clColorButtonMainSave;
	CButtonCT m_clColorButtonMainModelAdd;
	CButtonCT m_clColorButtonMainModelDel;
	CButtonCT m_clColorButtonMainModelLoad;
	CButtonCT m_clColorButtonMainModelChange;
	CButtonCT m_clColorButtonMainRecipeSave;
	CButtonCT m_clColorButtonMainRecipeDelete;
	CButtonCT m_clColorButtonMainRecipeLoad;
	CButtonCT m_clColorButtonMainRecipeCreate;
	CButtonCT m_clColorButtonMainRecipeApply;
	CButtonCT m_clColorButtonMainRecipeDown;

	CButtonCT m_clColorButtonMainAbortedReport;
	CButtonCT m_clColorButtonMainMaterialIdReport;

	CButtonCT m_clColorButtonMainControlOfflineReq;
	CButtonCT m_clColorButtonMainControlOnlineRemoteReq;

	CEdit m_edtAbortLot;
	CEdit m_edtMaterialId;
	
	CGridCtrl m_clGridModel;
	CGridCtrl m_clGridRecipe;

	CComboBox m_clComboRecipeId;
private:
	int m_nUnit;
	int GridRow;
	int GridCol;
	int ModelCurCol;

	int IdleReportCurrentIndex;

	int currentRecipeNo;
	int recipeGridHeight;
	int recipeGridViewMax;
	int recipeGridRow;
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;


	void InitCtrl();
	void ShowGridData();
	
	void GetGridData();
public:
	void setCommunicationState(int state);
	void setControlState(int state);
	void ModelListDataSet();//modelList RcmdCommandGroup modelList);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedStaticMainOperatorIdVal();
	afx_msg void OnBnClickedButtonMainSave();
	afx_msg void OnBnClickedButtonMainModelAdd();
	afx_msg void OnBnClickedButtonMainModelDel();
	afx_msg void OnBnClickedButtonMainModelChange();
	afx_msg void OnBnClickedButtonMainModelLoad();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMainRecipeSave();
	afx_msg void OnBnClickedButtonMainRecipeDownReq();
	afx_msg void OnBnClickedButtonMainRecipeApply();
	afx_msg void OnBnClickedButtonMainRecipeDel();
	afx_msg void OnCbnSelchangeComboRecipeIdVal();
	afx_msg void OnBnClickedButtonMainRecipeLoad();

	afx_msg void OnNMClickedRecipeGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonMainRecipeCreate();
	afx_msg void OnBnClickedButtonMainAbortedReport();
	afx_msg void OnBnClickedButtonMainMaterialIdReport();
	afx_msg void OnBnClickedButtonMainControlOfflineReq();
	afx_msg void OnBnClickedButtonMainControlOnlineRemoteReq();
};
