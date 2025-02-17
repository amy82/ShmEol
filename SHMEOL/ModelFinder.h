#pragma once
class CModelFinder
{
public:
	CModelFinder();
	~CModelFinder();

public:
	void InitMark();
	void EnableOverlay();
	void CloseModelFind();

	void SettingFindMark(int nUnit, int nNo);
	bool RegistMark(int nUnit, int nNo);

	void LoadMark(CString sModelName);
	void LoadMark(CString sModelName, int nUnit, int nNo);
	bool SaveMark(CString sModelName, int nUnit, int nNo);
	void DeleteMark(CString sModelName, int nUnit, int nNo);
	void ReSortMark(CString sModelName, int nUnit, int nNo);
	void ReNumberMark(CString sModelName, int nUnit, int nOldNo, int nNewNo);

	void DrawMarkOverlay(int nUnit, int nNo);

	bool FindModel(int nUnit, int nNo, bool bAreaFlag, CDMPoint& clFindPos, double& dScore, double& dAngle, double& dFitError, CDMPoint& clMarkSize, CDMPoint& clMarkCenter);
	bool FindBestModel(int nUnit, bool bAreaFlag, int& nFindNo, double& dCenterX, double& dCenterY, double& dAngle, double& dScore, CDMPoint& clMarkSize, CDMPoint& clMarkCenter);

public:
	//MIL_ID m_MilMarkSystem;
	MIL_ID m_MilMarkDisplay[2];//0 = 작은 마크이미지 , 1 = 마스크 설정가능한 확대 이미지
	MIL_ID m_MilMarkImage[2];//0 = 작은 마크이미지 , 1 = 마스크 설정가능한 확대 이미지
	MIL_ID m_MilMarkOverlay[2];//0 = 작은 마크이미지 , 1 = 마스크 설정가능한 확대 이미지
	long m_lTransparentColor[2];//0 = 작은 마크이미지 , 1 = 마스크 설정가능한 확대 이미지
	MIL_ID MilMarkTempImage;

	MIL_ID m_MilModModel[MAX_UNIT_COUNT][MAX_MARK_COUNT];
	MIL_ID m_MilModResult[MAX_UNIT_COUNT];


	
	CPoint m_clPtSmallMarkDispSize;		//축소 마크 이미지
	CPoint m_clPtZoomMarkDispSize;		//확대 마크 이미지


	CPoint m_clPtMarkMaxSize;		//확대 마크 이미지
	CPoint m_clPtMarkDispSize;		//확대 마크 이미지

	CPoint m_clPtMarkSize[MAX_UNIT_COUNT][MAX_MARK_COUNT];
	CPoint m_clPtMarkCenterPos;
	CPoint m_clPtMarkStartPos;

	bool m_bMarkState[MAX_UNIT_COUNT][MAX_MARK_COUNT];
	bool m_bInitMarkOverlay;
	bool m_bEnableMarkOverlay;
};
