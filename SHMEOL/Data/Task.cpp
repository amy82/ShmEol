#include "stdafx.h"
#include "Task.h"


CTask::CTask()
{
	m_Unit_State_Pcb		= 0;
	m_Unit_State_Lens		= 0;
	m_Unit_State_Epoxy		= 0;
	m_Unit_State_Loading	= 0;
	m_Unit_State_UnLoading	= 0;
	
	m_Unit_Ready_Pcb		= 0;
	m_Unit_Ready_Lens		= 0;
	m_Unit_Ready_Epoxy		= 0;
	m_Unit_Ready_Loading	= 0;
	m_Unit_Ready_UnLoading	= 0;
	
	m_Old_Step_Pcb			= 0;
	m_Old_Step_Lens			= 0;
	m_Old_Step_Epxy			= 0;
	m_Old_Step_Loading		= 0;
	m_Old_Step_UnLoading	 = 0;
	//
	//
	//현재 알람 발생 상태
	m_Alarm_Pcb				= 0;
	m_Alarm_Lens			= 0;
	m_Alarm_Epoxy			= 0;
	m_Alarm_Loading			= 0;
	m_Alarm_UnLoading		= 0;

	int i = 0;
	for (i = 0; i < 4; i++)
	{
		m_State_AA[i] = 0;		//AA부 상태 체크
	}
}


CTask::~CTask()
{
}
