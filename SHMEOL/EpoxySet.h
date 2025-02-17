#pragma once

#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"

// CEpoxySet 대화 상자입니다.

class CEpoxySet : public CDialogEx
{
	DECLARE_DYNAMIC(CEpoxySet)

public:
	CEpoxySet(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEpoxySet();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EPOXY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	void InitCtrl();
	void InitEpoxyLineGridCtrl();
	void InitEpoxyLineLengthGridCtrl();
	void InitEpoxyCurveLengthGridCtrl();

	void InitEpoxyRectInspGridCtrl();			// 도포검사 직선 구간 셋팅.
	void InitEpoxyCircleRectInspGridCtrl();		// 도포검사 곡선 구간 셋팅.
	void InitEpoxyInspSpecGridCtrl();			// 도포검사 스펙.

	void ShowEpoxySet();
	void GetEpoxyData();
private:
	CGridCtrl m_clGridEpoxyLine;
	CGridCtrl m_clGridEpoxyLineLength;
	CGridCtrl m_clGridEpoxyCurveLength;
	CGridCtrl m_clGridEpoxyInspRect;
	CGridCtrl m_clGridEpoxyCircleRect;
	CGridCtrl m_clGridEpoxyInspSpec;
public:
	void SetUnit(int nUnit) { m_nUnit = nUnit; }

private:
	int m_nUnit;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonEpoxySave();
	afx_msg void OnStnDblclickStaticEpoxyLineGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnDblclickStaticEpoxyLineLengthGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnDblclickStaticEpoxyCurveLengthGrid(NMHDR* pNMHDR, LRESULT* pResult);
	
	afx_msg void OnStnDblclickStaticEpoxyInspGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnDblclickStaticEpoxyInspCircleGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnDblclickStaticEpoxyInspSpecGrid(NMHDR* pNMHDR, LRESULT* pResult);
	
};
