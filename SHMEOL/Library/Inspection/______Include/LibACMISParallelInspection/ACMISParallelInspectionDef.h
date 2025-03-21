#pragma once

#include <LibACMISCommon\ACMISCommon.h>
#include <LibACMISImage\ACMISImageDef.h>
#include <LibACMISResolution\ACMISResolutionDef.h>
#include <LibACMISShading\ACMISShadingDef.h>
#include <LibACMISEtc\ACMISEtcDef.h>
#include <LibACMISCommon\InspectionErrorCode.h>

#include <atlstr.h>

//#define FUNCTION_GROUT_ENABLE


// 검사 항목 공용체
#ifdef FUNCTION_GROUT_ENABLE
typedef enum _enumFunctionGroupType
{
	ENUM_FUNCTION_GROUP_BLEMISH,
	ENUM_FUNCTION_GROUP_RESOLUTION,
	ENUM_FUNCTION_GROUP_OPTICAL_CENTER,
	ENUM_FUNCTION_GROUP_SNR,
	ENUM_FUNCTION_GROUP_ETC,
	ENUM_FUNCTION_GROUP_DARK_TEST,
	ENUM_FUNCTION_GROUP_SHADING,
	MAX_COUNT_FUNCTION_GROUP_TYPE
} ENUM_FUNCTION_GROUP_TYPE;
#endif

typedef struct _tagParallelInpsectInput
{
	INSPECTION_INPUT* pInspectionInput;
	std::vector<TBufferInfo*> vBufferInfo;
} ParallelInpsectInput;


// 각 검사 항목별 결과 구조체 - 수정 필요
typedef struct _tagBlemishResult
{
	int nSingleDefectCount;
	vTBlobResult vBlobResult;
	int nDefectCount[EIMAGEREGION_MAX];
	TDefectResult tMaxResult[EIMAGEREGION_MAX];
	TCircleData tCircleData;
	RECT rtBorderLine;
	std::vector<double> vSaturationResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_BLEMISH;

typedef struct _tagDefectResult
{
	std::vector<int> vDefectCount;
	std::vector<int> vCoupletCount;
	std::vector<int> vClusterCount;
	std::vector<int> vClusterColorCount;
	std::vector<int> vLineCount;
	int nColumnFPNCount;
	std::vector< std::vector<TDefectResult> > vDefectResult;
	std::vector< std::vector<TBlobResult> > vCoupletResult;
	std::vector< std::vector<TBlobResult> > vClusterResult;
	std::vector< std::vector<TBlobResult> > vClusterColorResult;
	std::vector< std::vector<TDefectResult> > vLineResult;
	std::vector<TDefectResult> vColumnFPNResult;
	std::vector<TDefectResult> vMaxResult;
	TCircleSpecN tCircleSpec;
	TCircleData tCircleData;
	std::vector<double> vSaturationResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_DEFECT;

typedef struct _tagEIAJResult
{
	std::vector<TEIAJROIResult*> vectorROIResult;
} RESULT_EIAJ;

typedef struct _tagSFRResult
{
	std::vector<TSFRROIResult*> vectorSFRResult;
} RESULT_SFR;

typedef struct _tagOCResult
{
	double decenterX;
	double decenterY;
} RESULT_OC;

typedef struct _tagFiducialMarkResult
{
	double dfov;
	double hfov;
	double vfov;
	double tiltX;
	double tiltY;
	double rotation;
	double distortion;
} RESULT_FIDUCIAL_MARK;

typedef struct _tagSNRBWResult
{
	std::vector<TSNRBWResult*> vectorSNRBWResult;
	std::vector<TSNRResult*> vectorSNRResult;
	// 수정 필요...
} RESULT_SNR_BW;

typedef struct _tagSNRNormResult
{
	std::vector<TSNRNormResult*> vectorSNRNormResult;
	TSNRResult* ptagMinSNRResult;
	// 수정 필요...
} RESULT_SNR_NORM;

typedef struct _tagColorReproductionResult
{
	std::vector<TColorReproductionResult*> vectorColorReproductionResult;
} RESULT_COLOR_REPRODUCTION;

typedef struct _tagIRFilterResult
{
	TIRFilterResult tagIRFilterResult;
	RECT rcROI;
} RESULT_IR_FILTER;

typedef struct _tagColorIntensityResult
{
	std::vector<TColorIntensityResult*> vectorColorIntensityResult;
} RESULT_COLOR_INTENSITY;

typedef struct _tagRelativeIlluminationResult
{
	TRelativeIlluminationResultN* pResult;
	std::vector<RECT*> vectorInspectionROI;
} RESULT_RELATIVE_ILLUMINATION;

typedef struct _tagRelativeIlluminationXResult
{
	TRelativeIlluminationResultX* ptagCenterResult;
	std::vector<TRelativeIlluminationResultX*> vectorRegionResult;
} RESULT_RELATIVE_ILLUMINATION_X;

typedef struct _tagRelativeUniformityResult
{
	TRelativeUniformityResult* pResult;
} RESULT_RELATIVE_UNIFORMITY;

typedef struct _tagColorUniformityResult
{
	std::vector<TColorUniformityResultN*> vectorColorUniformityResult;
	TColorUniformityResultN* ptagMaxResult;
} RESULT_COLOR_UNIFORMITY;

typedef struct _tagShadingUniformityResult
{
	TShadingUniformityResult tagCenterResult;
	std::vector<TShadingUniformityResult*> vectorShadingUniformityResult;
} RESULT_SHADING_UNIFORMITY;

typedef struct _tagColorSensitivityResult
{
	std::vector<TColorSensitivityResult*> vectorColorSensitivityResult;
	std::vector<RECT*> vectorInspectionROI;
} RESULT_COLOR_SENSITIVITY;

typedef struct _tagCOMMON_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
} COMMON_EXTRA_SPEC, OPTICAL_CENTER_EXTRA_SPEC, SHADING_EXTRA_SPEC;

typedef struct _tagBLEMISH_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	ESaturationMethod eSaturationMethod;
	int nUsingMask;
	CString strMaskFilePath;
} BLEMISH_EXTRA_SPEC;

typedef struct _tagDARK_TEST_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	int nTestInspectType;
	TDefectOffset tDefectOffset;
	ESaturationMethod eSaturationMethod;
	TCircleSpecN tCircleSpec;
	int nUsingMask;
	CString strMaskFilePath;
} DARK_TEST_EXTRA_SPEC;

typedef struct _tagRESOLUTION_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	TFiducialMarkSpecN tFiducialMarkSpec;
} RESOLUTION_EXTRA_SPEC, SNR_EXTRA_SPEC, ETC_EXTRA_SPEC;
