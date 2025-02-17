#include "StdAfx.h"
#include "MBlobObj.h"


CMBlobObj::CMBlobObj(void)
{
	m_MilFeature = M_NULL;
	m_MilBlobResult = M_NULL;
}


CMBlobObj::~CMBlobObj(void)
{
	this->ReleaseBlob();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CMBlobObj::InitializeBlob(MIL_ID clMSystem)
{
	if (NULL != m_MilFeature || 
		NULL != m_MilBlobResult)
	{
		this->ReleaseBlob();
	}

	if (m_MilFeature == M_NULL)
	{// Allocate a feature list.
		MblobAllocFeatureList(clMSystem, &m_MilFeature);
		if (m_MilFeature == M_NULL)
			return false;

		// Enable the Area and Center Of Gravity feature calculation. 
		MblobSelectFeature(m_MilFeature, M_AREA);
		MblobSelectFeature(m_MilFeature, M_BOX);
		MblobSelectFeature(m_MilFeature, M_COMPACTNESS);
		MblobSelectFeature(m_MilFeature, M_CENTER_OF_GRAVITY);
		MblobSelectFeature(m_MilFeature, M_FERET_MIN_DIAMETER);
		MblobSelectFeature(m_MilFeature, M_FERET_MAX_DIAMETER);
	}

	if (m_MilBlobResult == M_NULL)
	{// Allocate a blob result buffer. 
		MblobAllocResult(clMSystem, &m_MilBlobResult);
		
		if (m_MilBlobResult == M_NULL)
			return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CMBlobObj::ReleaseBlob()
{
	if (m_MilBlobResult != M_NULL) 
	{
		MblobFree(m_MilBlobResult);
		m_MilBlobResult = M_NULL;
	}

	if (m_MilFeature != M_NULL) 
	{
		MblobFree(m_MilFeature);
		m_MilFeature = M_NULL;
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CMBlobObj::FindBlob(MIL_ID MilSystem,	MIL_ID MinBinImg, int nIndex, CRect clRect,	INT nThreshold, INT	nMinX, INT nMinY, INT nMaxX, INT nMaxY, STRUC_FIND_BLOB& stFindBlob, INT nOffsetX/* = 0*/, INT nOffsetY/* = 0*/)
{
	MIL_ID		MilBlobFeature;
	MIL_ID		MilBlobResult;
	MIL_INT		nTotalBlob = 0;

	//memset(&stFindBlob, 0x00, sizeof(stFindBlob));

	if (m_MilFeature == M_NULL)
	{
		if (this->InitializeBlob(MilSystem) == false)
			return false;
	}

	MilBlobFeature = m_MilFeature;
	MilBlobResult = m_MilBlobResult;

	/* Binarize image. */
	nThreshold = abs(nThreshold);

//#ifdef _DEBUG
//	if (nIndex > 0)
//	{
//		MIL_ID MilBin = M_NULL;
//		MIL_DOUBLE	*nFindMinX, *nFindMaxX, *nFindMinY, *nFindMaxY;
//		MIL_DOUBLE	*nPosX, *nPosY;
//		double dX, dY, dLen, dMin = 999;
//		CString sTemp = _T("");
//
//		MbufChild2d(MinBinImg, clRect.left, clRect.top,
//			clRect.right - clRect.left,
//			clRect.bottom - clRect.top,
//			&MilBin);
//		sTemp.Format(_T("D:\\Debug\\FindBlob_%d.bmp"), nIndex + 1);
//		MbufSave(sTemp, MilBin);
//
//		MblobCalculate(MilBin, M_NULL, MilBlobFeature, MilBlobResult);
//		MblobGetNumber(MilBlobResult, &nTotalBlob);
//
//		nFindMinX = new MIL_DOUBLE[nTotalBlob];
//		nFindMinY = new MIL_DOUBLE[nTotalBlob];
//		nFindMaxX = new MIL_DOUBLE[nTotalBlob];
//		nFindMaxY = new MIL_DOUBLE[nTotalBlob];
//		nPosX = new MIL_DOUBLE[nTotalBlob];
//		nPosY = new MIL_DOUBLE[nTotalBlob];
//
//		if (nTotalBlob > 0)
//		{
//			MblobGetResult(MilBlobResult, M_BOX_X_MAX + M_TYPE_DOUBLE, nFindMaxX);
//			MblobGetResult(MilBlobResult, M_BOX_X_MIN + M_TYPE_DOUBLE, nFindMinX);
//			MblobGetResult(MilBlobResult, M_BOX_Y_MAX + M_TYPE_DOUBLE, nFindMaxY);
//			MblobGetResult(MilBlobResult, M_BOX_Y_MIN + M_TYPE_DOUBLE, nFindMinY);
//
//			MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_X + M_TYPE_DOUBLE, nPosX);
//			MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_Y + M_TYPE_DOUBLE, nPosY);
//
//			for (int i = 0; i < nTotalBlob; i++)
//			{
//				dX = nPosX[i] - clRect.CenterPoint().x;
//				dY = nPosY[i] - clRect.CenterPoint().y;;
//
//				dLen = (nFindMaxX[i] - nFindMinX[i]) * (nFindMaxY[i] - nFindMinY[i]);
//				if (fabs(dMin) < fabs(dLen))
//				{//! BLOB MAX SIZE
//					dMin = fabs(dLen);
//					
//					stFindBlob.bSearchComp = true;
//					stFindBlob.dResultX = nPosX[i] + clRect.left;
//					stFindBlob.dResultY = nPosY[i] + clRect.top;
//					stFindBlob.dMarkRefX = nPosX[i] + clRect.left;
//					stFindBlob.dMarkRefY = nPosY[i] + clRect.top;
//					stFindBlob.dMarkSizeX = nFindMaxX[i] - nFindMinX[i];
//					stFindBlob.dMarkSizeY = nFindMaxY[i] - nFindMinY[i];
//					_stprintf_s(stFindBlob.szFindMode, SIZE_OF_100BYTE, _T("BLOB"));					
//
//					g_clVision.DrawMOverlayBox(0, nFindMinX[i] + clRect.left, nFindMinY[i] + clRect.top, nFindMaxX[i] + clRect.left, nFindMaxY[i] + clRect.top, M_COLOR_MAGENTA, 1, FALSE);
//				}
//
//
//
//				//dLen = sqrt(dX*dX + dY*dY);
//				//if (fabs(dLen) < dMin) {		// 중앙(0,0)에 가장 가까운 블랍 선택
//				//	dMin = fabs(dLen);
//				//	nNo = i;
//				//}
//			}
//		}
//
//		delete[] nFindMinX;
//		delete[] nFindMinY;
//		delete[] nFindMaxX;
//		delete[] nFindMaxY;
//		delete[] nPosX;
//		delete[] nPosY;
//
//		MbufFree(MilBin);
//	}
//
//	return true;
//#endif
	// Calculate selected features for each blob.
	MblobCalculate(MinBinImg, M_NULL, MilBlobFeature, MilBlobResult);
	MblobGetNumber(MilBlobResult, &nTotalBlob);	

	MblobSelect(MilBlobResult, M_EXCLUDE, M_BOX_X_MIN, M_LESS_OR_EQUAL, clRect.left, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif
	MblobSelect(MilBlobResult, M_EXCLUDE, M_BOX_X_MAX, M_GREATER_OR_EQUAL,	clRect.right, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif
	MblobSelect(MilBlobResult, M_EXCLUDE, M_BOX_Y_MIN, M_LESS_OR_EQUAL,		clRect.top, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif
	MblobSelect(MilBlobResult, M_EXCLUDE, M_BOX_Y_MAX, M_GREATER_OR_EQUAL,	clRect.bottom, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif

	// Exclude blobs whose area is too small.
	MblobSelect(MilBlobResult, M_EXCLUDE, M_FERET_X, M_LESS, nMinX, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif
	MblobSelect(MilBlobResult, M_EXCLUDE, M_FERET_X, M_GREATER, nMaxX, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif
	MblobSelect(MilBlobResult, M_EXCLUDE, M_FERET_Y, M_LESS, nMinY, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif
	MblobSelect(MilBlobResult, M_EXCLUDE, M_FERET_Y, M_GREATER,	nMaxY, M_NULL);
#ifdef _DEBUG
	MblobGetNumber(MilBlobResult, &nTotalBlob);
#endif


	// Get the total number of selected blobs.
	MblobGetNumber(MilBlobResult, &nTotalBlob);
	if (nTotalBlob < 1)
	{
		//AfxMessageBox(_T("Blob Count Over..."));
		return false;
	}

	double dbFind_x = clRect.CenterPoint().x - nOffsetX;
	double dbFind_y = clRect.CenterPoint().y - nOffsetY;

	//pFindBlob->Initilize();
	this->GetBlobSelect(dbFind_x, dbFind_y, stFindBlob);

	MblobSelect(MilBlobResult, M_INCLUDE, M_ALL_BLOBS, M_NULL, M_NULL, M_NULL);

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
LONG CMBlobObj::GetBlobCount()
{
	MIL_INT		nTotalBlob = 0;

	if (m_MilBlobResult == M_NULL)
		return (LONG)nTotalBlob;

	MblobGetNumber(m_MilBlobResult,	&nTotalBlob);	// Get the total number of selected blobs.

	return (LONG)nTotalBlob;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CMBlobObj::GetBlobMinMax(CDMPoint &dpMin, CDMPoint &dpMax)
{
	MIL_ID		midBlobResult;
	INT nCount = GetBlobCount();
	MIL_DOUBLE	*nMinX, *nMaxX, *nMinY, *nMaxY;
	MIL_DOUBLE	*nPosX, *nPosY;
	DOUBLE dbMin_x = 9999999, dbMin_y = 9999999;
	DOUBLE dbMax_x = -9999999, dbMax_y = -9999999;

	if (nCount < 1)		return false;
	if (nCount > 999)	return false;
	
	midBlobResult = m_MilBlobResult;

	nMinX = new MIL_DOUBLE[nCount + 2];
	nMinY = new MIL_DOUBLE[nCount + 2];
	nMaxX = new MIL_DOUBLE[nCount + 2];
	nMaxY = new MIL_DOUBLE[nCount + 2];
	nPosX = new MIL_DOUBLE[nCount + 2];
	nPosY = new MIL_DOUBLE[nCount + 2];

	// get result
	MblobGetResult(midBlobResult, M_BOX_X_MAX + M_TYPE_DOUBLE, nMaxX);
	MblobGetResult(midBlobResult, M_BOX_X_MIN + M_TYPE_DOUBLE, nMinX);
	MblobGetResult(midBlobResult, M_BOX_Y_MAX + M_TYPE_DOUBLE, nMaxY);
	MblobGetResult(midBlobResult, M_BOX_Y_MIN + M_TYPE_DOUBLE, nMinY);

	MblobGetResult(midBlobResult, M_CENTER_OF_GRAVITY_X + M_TYPE_DOUBLE, nPosX);
	MblobGetResult(midBlobResult, M_CENTER_OF_GRAVITY_Y + M_TYPE_DOUBLE, nPosY);

	for (int i = 0; i < nCount; i++)
	{
		dbMin_x = min(dbMin_x, nMinX[i]);
		dbMin_y = min(dbMin_y, nMinY[i]);
		dbMax_x = max(dbMax_x, nMaxX[i]);
		dbMax_y = max(dbMax_y, nMaxY[i]);
	}
	dpMin.x = dbMin_x;	dpMin.y = dbMin_y;
	dpMax.x = dbMax_x;	dpMax.y = dbMax_y;

	delete[] nMinX;
	delete[] nMinY;
	delete[] nMaxX;
	delete[] nMaxY;
	delete[] nPosX;
	delete[] nPosY;

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CMBlobObj::GetBlobSelect(double dCenX, double dCenY, STRUC_FIND_BLOB& stFindBlob)
{
	MIL_ID		midBlobResult;
	int nCount = GetBlobCount();	
	int i;
	int nNo = 0;
	MIL_DOUBLE	*nMinX, *nMaxX, *nMinY, *nMaxY;
	MIL_DOUBLE	*nPosX, *nPosY;
	double dX = 0, dY = 0, dLen = 0, dMin = 99999;
	
	midBlobResult = m_MilBlobResult;

	nMinX = new MIL_DOUBLE[nCount + 2];
	nMinY = new MIL_DOUBLE[nCount + 2];
	nMaxX = new MIL_DOUBLE[nCount + 2];
	nMaxY = new MIL_DOUBLE[nCount + 2];
	nPosX = new MIL_DOUBLE[nCount + 2];
	nPosY = new MIL_DOUBLE[nCount + 2];

	// get result
	MblobGetResult(midBlobResult, M_BOX_X_MAX + M_TYPE_DOUBLE, nMaxX);
	MblobGetResult(midBlobResult, M_BOX_X_MIN + M_TYPE_DOUBLE, nMinX);
	MblobGetResult(midBlobResult, M_BOX_Y_MAX + M_TYPE_DOUBLE, nMaxY);
	MblobGetResult(midBlobResult, M_BOX_Y_MIN + M_TYPE_DOUBLE, nMinY);

	MblobGetResult(midBlobResult, M_CENTER_OF_GRAVITY_X + M_TYPE_DOUBLE, nPosX);
	MblobGetResult(midBlobResult, M_CENTER_OF_GRAVITY_Y + M_TYPE_DOUBLE, nPosY);

	for (i = 0; i < nCount; i++)
	{
		dX = nPosX[i] - dCenX;
		dY = nPosY[i] - dCenY;

		dLen = (nMaxX[i] - nMinX[i]) * (nMaxY[i] - nMinY[i]);
		if (fabs(dMin) < fabs(dLen))
		{//! BLOB MAX SIZE
			dMin = fabs(dLen);
			nNo = i;
		}

		//dLen = sqrt(dX*dX + dY*dY);
		//if (fabs(dLen) < dMin) {		// 중앙(0,0)에 가장 가까운 블랍 선택
		//	dMin = fabs(dLen);
		//	nNo = i;
		//}
	}
	
	stFindBlob.bSearchComp		= true;
	stFindBlob.dResultX		= nPosX[nNo];
	stFindBlob.dResultY		= nPosY[nNo];
	stFindBlob.dMarkRefX	= nPosX[nNo];
	stFindBlob.dMarkRefY	= nPosY[nNo];
	stFindBlob.dMarkSizeX	= nMaxX[nNo] - nMinX[nNo];
	stFindBlob.dMarkSizeY	= nMaxY[nNo] - nMinY[nNo];
	stFindBlob.clRect.left  = nMinX[nNo];
	stFindBlob.clRect.top   = nMinY[nNo];
	stFindBlob.clRect.right = nMaxX[nNo];
	stFindBlob.clRect.bottom = nMaxY[nNo];
	_stprintf_s(stFindBlob.szFindMode, SIZE_OF_100BYTE, _T("BLOB"));

	delete[] nMinX;
	delete[] nMinY;
	delete[] nMaxX;
	delete[] nMaxY;
	delete[] nPosX;
	delete[] nPosY;

	return true;
}
