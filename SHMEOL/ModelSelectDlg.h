#pragma once
#include "afxwin.h"
#include "Utility\ButtonEx\ButtonCT.h"

// CModelSelectDlg 대화 상자입니다.

class CModelSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSelectDlg)

public:
	CModelSelectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModelSelectDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODEL_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SetUnit(int nUnit);
private:
	CGridCtrl m_clGridModelSelect;
	int m_nUnit;

public:
	CButtonCT m_ColorbuttonModelModerate;
	CButtonCT m_ColorbuttonModelNarrow;

public:
	void ShowCurrentModel();

public:
	afx_msg void OnBnClickedButtonModelSelectExit();
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonModerateModel();
	afx_msg void OnBnClickedButtonNarrowModel();
	afx_msg void OnBnClickedButtonModelSelectLoad();
};
