#pragma once


// CIdlePopupDlg dialog

class CIdlePopupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIdlePopupDlg)

public:
	CIdlePopupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIdlePopupDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IDLE_POPUP };
#endif
public:
	CLabel m_clColorStaticIdleIdleTitle;


	//CLabel m_clColorStaticIdleOpId;
	//CLabel m_clColorStaticIdleOpIdVal;

	//CLabel m_clColorStaticIdleGroup;
	//CComboBox m_clComBoxIdleGroup;

	CLabel m_clColorStaticIdleReason;
	CComboBox m_clComBoxIdleReason;


	CLabel m_clColorStaticIdleNote;
	//CLabel m_clColorStaticIdleNoteVal;
	CEdit m_clCeditIdleNoteVal;

	CBrush m_brCheck;
public:
	void SetUnit(int nUnit);

	void InitCtrl();
	void setOperatorID(CString opId);
private:
	CFont m_clFontSmall;
	CFont m_clFontMid;
	CFont m_clFontBig;

	int m_nUnit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedStaticIdleOpIdVal();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
};
