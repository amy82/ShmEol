
#ifndef _USERCOMMONDEFINE_H
#define _USERCOMMONDEFINE_H

#include "AutoInspDlg.h"
#include "Data\ModuleData.h"
#include "Data\Task.h"
#include "Data\Work.h"
#include "Data\Model.h"
#include "DioControl.h"
#include "AXTDefine.h"
#include "AxlMotorSet.h"
#include "Log\Log.h"

extern CModuleData MouduleData;
extern CTask Task;
extern CWork Work;
extern CModelData Modeldata[MAX_UNIT_COUNT];
extern CLog  LogModule;
extern CAxlMotorSet Motor;
extern CDioControl DioControl;
#pragma once




// CDlgSlideBar 대화 상자입니다.
class UserCommon
{
public:
	UserCommon();
	~UserCommon();

	CRect	m_MainPos;

	CRect	m_Title1_Pos;
	CRect	m_Title2_Pos;

	CRect	m_CCD1_Pos;
	CRect	m_CCD2_Pos;

	CRect	m_ListBox1_Pos;
	CRect	m_ListBox2_Pos;

	CRect	m_MainRunBtnStartPos1;
	CRect	m_MainRunBtnStartPos2;

	CRect	m_BarGraphPos1;
	CRect	m_BarGraphPos2;

	CRect	m_SubDlgPos;
	
	COLORREF SUBDLGCOLOR;// = RGB(10, 10, 10);
};

#endif