#pragma once


typedef struct STRUC_FIND_BLOB		//!! Find Data 
{
	BOOL	bSearchComp;//! 검색 완료 여부
	DOUBLE	dResultX;	//! 검색 결과
	DOUBLE	dResultY;
	DOUBLE	dMarkSizeX;	//! 검색 된 MARK의 크기
	DOUBLE  dMarkSizeY;
	DOUBLE	dMarkRefX;	//! MARK의 중심
	DOUBLE	dMarkRefY;
	CRect   clRect;		// 검색된 외곽 크기
	int     nCenterX;
	int     nCenterY;
	DOUBLE	dTime;		//! 측정 시간(ms)
	TCHAR	szFindMode[SIZE_OF_100BYTE];
} STRUC_FIND_BLOB;


class CMBlobObj
{
public:
	CMBlobObj(void);
	~CMBlobObj(void);

public:
	bool InitializeBlob(MIL_ID clMSystem);
	bool ReleaseBlob();

public:
	bool FindBlob(MIL_ID MilSystem,	MIL_ID MinBinImg, int nIndex, CRect clRect,	INT nThreshold, INT	nMinX, INT nMinY, INT nMaxX, INT nMaxY, STRUC_FIND_BLOB& stFindBlob, INT nOffsetX = 0, INT nOffsetY = 0);

public:
	LONG GetBlobCount();
	bool GetBlobMinMax(CDMPoint &dpMin, CDMPoint &dpMax);
	bool GetBlobSelect(double dCenX, double dCenY, STRUC_FIND_BLOB& stFindBlob);

private:
	MIL_ID	m_MilFeature;			//feature
	MIL_ID	m_MilBlobResult;
};

