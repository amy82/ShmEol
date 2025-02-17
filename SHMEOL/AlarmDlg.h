#pragma once
#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\HeaderCtrlEx\HeaderCtrlEx.h"
#include "Utility\ButtonEx\ButtonCT.h"
#define MAX_ALARM_COUNT				30
#define MAX_PAGE_COUNT				10

#define		MAX_ALARM_PAGE_CNT			20			// 알람 히스토리 창의 최대 알람 페이지 수..
#define		MAX_ALARM_LIST_IN_PAGE		24			// 알람 페이지 당 출력되는 알람 수..
// CAlarmDlg 대화 상자입니다.

class CAlarmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmDlg)

public:
	CAlarmDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAlarmDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CString m_sAlarmLog;

public:
	void SetUnit(int nUnit);
	void AddAlarm(CString szAlarm);
	void AddAlarm_N(CString sAlarm);

	void ShowCurrentPage();
	void ShowAlarmList_N();
private:
	void InitCtrl();
	
	void ShowAlarmList(int nMode);
	void SaveAlarm(CString szAlarm);

private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	int m_nUnit;

	CHeaderCtrlEx m_clHeaderCtrlEx;
	CString* m_pAlarmList[2];
	int m_nAlarmPage[2];
	int m_nAlarmIndex[2];
	int m_nCurrentPage[2];
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAlarmPrev();
	afx_msg void OnBnClickedButtonAlarmNext();
	afx_msg void OnBnClickedButtonAlarmClear();

public:
    CLabel m_clColorStaticTitle;
    CLabel m_clColorStaticPage;
	//CListCtrl m_clListCtrlAlarm;
	CButtonCT m_clColorButtonPrev;
    CButtonCT m_clColorButtonNext;
    CButtonCT m_clColorButtonClear;

	//grid
	CGridCtrl m_clGridAlarm;

	int AlarmRow;
	int AlarmCol;
	//

public:
	void	InitGridCtrl_Alarm();
	void	ShowGridCtrl_Alarm();

    
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
