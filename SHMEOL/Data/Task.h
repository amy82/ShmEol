#pragma once
class CTask
{
public:
	CTask();
	~CTask();

public:
	//////////////////////////////////////////////////////////////////////////
	//운전상태
	//0 = 정지
	//1 = 운전중
	//2 = 일시 정지
	byte m_Unit_State_Pcb;
	byte m_Unit_State_Lens;
	byte m_Unit_State_Epoxy;
	byte m_Unit_State_Loading;
	byte m_Unit_State_UnLoading;
	//
	byte m_Unit_Ready_Pcb;
	byte m_Unit_Ready_Lens;
	byte m_Unit_Ready_Epoxy;
	byte m_Unit_Ready_Loading;
	byte m_Unit_Ready_UnLoading;
	//////////////////////////////////////////////////////////////////////////
	//일시정지시 Step 상태
	byte m_Old_Step_Pcb;
	byte m_Old_Step_Lens;
	byte m_Old_Step_Epxy;
	byte m_Old_Step_Loading;
	byte m_Old_Step_UnLoading;

	//현재 알람 발생 상태
	bool	m_Alarm_Pcb;
	bool	m_Alarm_Lens;
	bool	m_Alarm_Epoxy;
	bool	m_Alarm_Loading;
	bool	m_Alarm_UnLoading;

	int		PcbReadyStep;
	int		LensReadyStep;
	int		LoadingReadyStep;
	int		UnloadingReadyStep;

	///int		LensTask, PCBTask, EpoxyTask, UnloadingTask;
	//int		LensPickupTask, PCBPickupTask, UnloadingPickupTask;
	//AA부 상태 체크
	//운전상태
	//0 = 정지
	//1 = 운전중
	//2 = 일시 정지
	byte		m_State_AA[4];
};

