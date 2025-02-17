#include "stdafx.h"
#include "UserCommon.h"

CModuleData MouduleData;
CTask Task;
CWork Work;
CModelData Modeldata[MAX_UNIT_COUNT];//CModelData g_clModelData[MAX_UNIT_COUNT];
CLog  LogModule;
CDioControl DioControl;
CAxlMotorSet Motor;
UserCommon::UserCommon()
{
	SUBDLGCOLOR = RGB(10, 10, 10);
}


UserCommon::~UserCommon()
{
}
