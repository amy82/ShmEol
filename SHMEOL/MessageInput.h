#pragma once


// CMessageInput 대화 상자입니다.

class CMessageInput : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageInput)

public:
	CMessageInput(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMessageInput();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MESSAGE_TYPE1 };
#endif

private:
	int m_nUnit;
	
public:
	int nPopupId;
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;


	CEdit m_edtMsgText;
	CLabel m_clColorStaticTitle;
	CButtonCT m_clColorButtonConfirm;
	bool editInputReadOnly;

	CBrush m_brush;  // 클래스 멤버 선언
	COLORREF m_bgColor;

	void InitCtrl();
	void setEditInput(CString title,int index,  CString txt);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMsgSend();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
