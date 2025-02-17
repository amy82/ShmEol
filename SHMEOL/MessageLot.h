#pragma once


// CMessageLot dialog

class CMessageLot : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageLot)

public:
	CMessageLot(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMessageLot();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MESSAGE_TYPE2};
#endif
public:
	//CLabel m_clColorStaticIdleLotTitle;
	CEdit m_edtLotTitle;

	CLabel m_clColorStaticIdleLotId;
	CLabel m_clColorStaticIdleLotIdVal;

	CBrush m_brCheck;
public:
	void SetUnit(int nUnit);

	void InitCtrl();
	void setMode(int index, int nBuzzer = 0);
	void setContent(CString title);
	void setLotID(CString lotId, CString lotIdVal);
private:
	CFont m_clFontSmall;
	CFont m_clFontMid;
	CFont m_clFontBig;

	CButtonCT m_ColorbuttonClose;
	CButtonCT m_ColorbuttonRetry;

	int nMode;
	int nBuzzerOnType;
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
	afx_msg void OnStnClickedStaticIdleLotIdVal();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
	virtual void OnCancel();
};
