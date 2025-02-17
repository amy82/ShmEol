#include "stdafx.h"
#include "ReportClass.h"


CReportClass::CReportClass()
{
	//Set.1
	vOfflineReason.clear();
	vIdleReason.clear();
	vModelLIst.clear();
	vPPUploadFail.clear();

	//Set.2
	vLotIdFail.clear();
	vPPSelect.clear();
	vPPUploadConfirm.clear();
	vLotStart.clear();
	vMaterialExchange.clear();
}


CReportClass::~CReportClass()
{
}
