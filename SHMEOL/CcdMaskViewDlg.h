#pragma once

#include "Utility\SliderCtrlEx\SliderCtrlEx.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
// CCcdMaskViewDlg 대화 상자입니다.

class CCcdMaskViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdMaskViewDlg)

public:
	CCcdMaskViewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdMaskViewDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CCD_MASK_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void InitCtrl();

	void DrawMask();
	void DrawCenterLine(CDMPoint clDPt);
	void DrawCircleLine(CDMPoint clDPt);

	void CopyBackup(int nMarkNo);

public:
	void InitMaskViewDlg(int nUnit, int nMarkNo , int dSizeX , int dSizeY);
	void InitMaskImage(int dSizeX, int dSizeY);
	void EnableOverlay();
	void ResizeImage(int nZoom);

	int m_iMarkSetSizeX;
	int m_iMarkSetSizeY;
private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;
	CRect m_rcDispWin;
	int m_nUnit;
	int m_nMarkNo;

	MIL_ID m_MilMask;//0 = 작은 마크이미지 , 1 = 마스크 설정가능한 확대 이미지
	MIL_ID m_MilMaskOverlay;//0 = 작은 마크이미지 , 1 = 마스크 설정가능한 확대 이미지

	MIL_DOUBLE m_MilTransparentColor[2];//0 = 작은 마크이미지 , 1 = 마스크 설정가능한 확대 이미지

	unsigned char* m_pMaskBuff;

	bool m_bEnableOverlay;
	bool m_bInitOverlay;

	int m_nMovePixel;
	bool m_bDrawEdge;
	bool m_bMaskDrag;
	bool m_bEraseMask;

	int m_nBrushSize;
	int m_nCircleSize;
	int m_nCircleSizeOffset;
	int m_nEdgeSmooth;
	int m_nZoomSize;

	double m_dZoomX;
	double m_dZoomY;

	CPoint m_clPtMarkSize;
	CPoint m_clPtPicPos;
	CDMPoint m_clCdCenter;
	CPoint m_clPtDispSize;

	
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
    CLabel m_clColorStaticTopBar;
    CLabel m_clColorStaticSmooth;
    CLabel m_clColorStaticSmoothVal;
    CLabel m_clColorStaticBrushSize;
    CLabel m_clColorStaticBrushSizeVal;

	CButtonCT m_clColorButtonMoveUp;
	CButtonCT m_clColorButtonMoveDown;
	CButtonCT m_clColorButtonMoveLeft;
	CButtonCT m_clColorButtonMoveRight;
	CButtonCT m_clColorButtonMoveGap;
	CButtonCT m_clColorButtonDrawEdge;
	CButtonCT m_clColorButtonMaskClear;
	CButtonCT m_clColorButtonMaskErase;
	CButtonCT m_clColorButtonMaskBG;

	CSliderCtrlEx m_clSliderCtrlExBrushSize;

    CButtonCT m_clColorButtonSave;
    CButtonCT m_clColorButtonClose;
	afx_msg void OnBnClickedButtonCcdMaskViewMoveUp();
	afx_msg void OnBnClickedButtonCcdMaskViewMoveDown();
	afx_msg void OnBnClickedButtonCcdMaskViewMoveLeft();
	afx_msg void OnBnClickedButtonCcdMaskViewMoveRight();
	afx_msg void OnBnClickedButtonCcdMaskViewMoveGap();
	afx_msg void OnStnClickedStaticCcdMaskViewEdgeSmoothVal();
	afx_msg void OnBnClickedButtonCcdMaskViewDrawEdge();
	afx_msg void OnStnClickedStaticCcdMaskViewBrushSizeVal();
	afx_msg void OnBnClickedButtonCcdMaskViewMaskClear();
	afx_msg void OnBnClickedButtonCcdMaskViewMaskErase();
	afx_msg void OnBnClickedButtonCcdMaskViewBgMask();
	afx_msg void OnBnClickedButtonCcdMaskViewSave();
	afx_msg void OnBnClickedButtonCcdMaskViewClose();
};
