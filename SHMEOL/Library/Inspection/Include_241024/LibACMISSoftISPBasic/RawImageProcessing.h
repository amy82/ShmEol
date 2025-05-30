#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>

namespace ACMISSoftISP
{
	typedef struct _POINTF
	{
		double x, y;
	} POINTD;

	class ACMISSOFTISPBASIC_API CStopWatch
	{
	private:
		LARGE_INTEGER freq, start, end;

	public:
		CStopWatch()
		{
			QueryPerformanceFrequency(&freq);
			start.QuadPart = 0;
			end.QuadPart = 0;
			StartTime();
		};

		inline void StartTime()
		{
			QueryPerformanceCounter(&start);
		};

		inline double CheckTime()
		{
			QueryPerformanceCounter(&end);

			return (double)(end.QuadPart - start.QuadPart) / (freq.QuadPart * 1000); // ms
			//TRACE("%.2f msec\n", elapsed);
		};
	};

	// blob 을 표현하는 run length encoding data
	class CBlobRunLengthData
	{
	public:
		BOOL visited;
		unsigned short blob_index;	// blob 번호
		unsigned short row;
		unsigned short col_start;		// run length encoding start
		unsigned short col_length;		// run length encoding end
		CBlobRunLengthData() {};
		CBlobRunLengthData(unsigned short blob_index, unsigned short row, unsigned short start, unsigned short length)
		{
			this->blob_index = blob_index;
			this->row = row;
			this->col_start = start;
			this->col_length = length;
			this->visited = FALSE;
		};
	};

	class CRawImageProccessor
	{
	private:
		enum COLORCHANNEL
		{
			chR = 0,
			chGr,
			chGb,
			chB
		};

		enum BAYERORDER
		{
			bayerOrderRGGB = 0,
			bayerOrderBGGR
		};

		// raw image 크기 만큼의 bayer type array 를 저장 하는 table
		// 0 : R, 1 : G, 2 : B, 3 : c
		BYTE *BayerTypeTable;
		int *IntegralImageSum[4];
		int *IntegralImageCount[4];
		int width, height;

		void NormalizeLSCTable(int blockCountX, int blockCountY);
		void SaveTextLSCRawTrainingModel(int blockCountX, int blockCountY);

	public:
		CRawImageProccessor();
		virtual ~CRawImageProccessor();

		BYTE *ColorPlane[4];

		BYTE * GetBayerTypeTable() { return BayerTypeTable; }

		// 0 : RGBC, 1 : BGGR
		void GenerateBayerTypeTable(int width, int height, BAYERORDER bayerOrder);
		void CalculateIntegralImage(BYTE *SrcImage, int width, int height);
		void DestroyBayerTypeTable();
		void CalculateMeanBlock(CRectEx rect, float mean[4]);

		// Integral Sum 과 Count 로 해당 Block 의 평균을 리턴 (width, height 도 이미 CalculateIntegralImage 에서 이미 저장 해놓음)
		void CalculateMeanBlock(int x0, int y0, int x1, int y1, float mean[4]);

		void CalculateMeanBlockDirect(BYTE *raw, int width, int height, int x0, int y0, int x1, int y1, float mean[4]);
		void SplitColorPlane(BYTE *pixel, int width, int height);
	};

	ACMISSOFTISPBASIC_API void Threshold(BYTE *srcpixel, int width, int height, CBlobList *bloblist, int min_thr, int max_thr, int MinArea, int BoundaryMarginX, int BoundaryMarginY);
	ACMISSOFTISPBASIC_API float Intensity(BYTE *pixel, int width, int height, CRectEx roi);
	ACMISSOFTISPBASIC_API void MeanImage(BYTE *image, BYTE *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImage2Byte(unsigned short *image, unsigned short *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImage4Byte(int *image, int *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageFloat(BYTE *image, float *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageFloat2Byte(unsigned short *image, float *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageFloat4Byte(int *image, float *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageDouble(BYTE *image, double *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageDouble2Byte(unsigned short *image, double *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageDouble4Byte(int *image, double *dest, int width, int height, int WindowSize, int startX = 0, int startY = 0, int endX = 0, int endY = 0);

	ACMISSOFTISPBASIC_API double SumBlock(const BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT rtROI);
	ACMISSOFTISPBASIC_API double SumBlock(const unsigned short* pBuffer, int nImageWidth, int nImageHeight, RECT rtROI);
	ACMISSOFTISPBASIC_API double SumBlock(const int* pBuffer, int nImageWidth, int nImageHeight, RECT rtROI);
	ACMISSOFTISPBASIC_API double SumBlock(const BYTE* pBuffer, int nWidth, int nHeight, int nBlockWidth, int nBlockHeight, int nStartX, int nStartY, int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);
	ACMISSOFTISPBASIC_API double SumBlock(const unsigned short* pBuffer, int nWidth, int nHeight, int nBlockWidth, int nBlockHeight, int nStartX, int nStartY, int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);
	ACMISSOFTISPBASIC_API double SumBlock(const int* pBuffer, int nWidth, int nHeight, int nBlockWidth, int nBlockHeight, int nStartX, int nStartY, int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);

	ACMISSOFTISPBASIC_API void MergeAdjacentBlob(CBlobList &BlobList, CBlobList *BlobListMergedResult, int BlockCriteria, int distance, int MaxRecursiveCount = 1000);
	ACMISSOFTISPBASIC_API float CalculateRegionIntensity(BYTE *pixel, int width, int height, CRectEx roi);

	ACMISSOFTISPBASIC_API void LensShadingCorrection(BYTE *pixel, BYTE *DestPixel, int MeanBlockSize, int width, int height, int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);
	ACMISSOFTISPBASIC_API void LensShadingCorrection(unsigned short *pixel, unsigned short *DestPixel, int MeanBlockSize, int width, int height, int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);
	ACMISSOFTISPBASIC_API void LensShadingCorrection(int *pixel, int *DestPixel, int MeanBlockSize, int width, int height, EDATAFORMAT eDataFormat, int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);
	ACMISSOFTISPBASIC_API float IntensityFiltered(BYTE *pixel, int width, int height, CRectEx roi, float filter);
	ACMISSOFTISPBASIC_API float IntensityMax(float *pixel, int width, int height, RECT roi);
	ACMISSOFTISPBASIC_API bool IntensityMax(float *pixel, int width, int height, RECT roi, float &maxValue, int &maxX, int &maxY);
	ACMISSOFTISPBASIC_API void IntensityRGB(BYTE *pixel, int width, int height, CRectEx roi, float *R, float *G, float *B);

	ACMISSOFTISPBASIC_API int CalcAvgSdv(BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(short *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(unsigned short *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(int *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(float *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(double *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(void *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType, int Variable_Type);
	ACMISSOFTISPBASIC_API bool AverageImage(BYTE **pBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec, int nImageCount, BYTE *pDstBuffer);
	ACMISSOFTISPBASIC_API bool GetIRImage(const BYTE **pSrcBuffer, int nImageWidth, int nImageHeight, TDATASPEC tDataSpec, BYTE *pDstBuffer);
	ACMISSOFTISPBASIC_API void MakeGammaLUT(EDATAFORMAT eDataFormat, double dGamma, std::vector<double>& vGamma);
	ACMISSOFTISPBASIC_API void MakeGammaLUT(EDATAFORMAT eDataFormat, double m_dGamma, std::vector<unsigned short> &m_vGamma);
	ACMISSOFTISPBASIC_API void MakeGammaLUT(EDATAFORMAT eDataFormat, double m_dGamma, std::vector<int> &m_vGamma);

	ACMISSOFTISPBASIC_API bool xMakeCompPWLLUT(int nSizeLut, int nSizeInOut, long * pLutX, long * pLutY);
	ACMISSOFTISPBASIC_API long* xGetCompPWLLUTData();
	ACMISSOFTISPBASIC_API long xGetCompPWLLUTDataSize();
	ACMISSOFTISPBASIC_API void xClearCompPWLLUTData();
	ACMISSOFTISPBASIC_API bool xMakeDecompPWLLUT(int nSizeLut, int nSizeInOut, long * pLutX, long * pLutY);
	ACMISSOFTISPBASIC_API long* xGetDecompPWLLUTData();
	ACMISSOFTISPBASIC_API long xGetDecompPWLLUTDataSize();
	ACMISSOFTISPBASIC_API void xClearDecompPWLLUTData();
};
