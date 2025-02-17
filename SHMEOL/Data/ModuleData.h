#pragma once
#include "../AXTDefine.h"
class CModuleData
{
public:
	CModuleData();
	~CModuleData();

public:
	void Load();
	void Save();
	void CopyBackup();

public:
	int m_nSysNo;
	int m_nUnitNo;

	TCHAR m_szMesIp[SIZE_OF_100BYTE];			// MES IP
	int m_nMesPort;								// MES 포트
	TCHAR m_szFactoryCd[SIZE_OF_100BYTE];		// 설비코드

	TCHAR m_szModelName[SIZE_OF_100BYTE];		// 모델 명
	TCHAR m_szPassword[SIZE_OF_100BYTE];		// 비밀번호
	TCHAR m_szAAIp[SIZE_OF_100BYTE];			// MAIN PC IP
	TCHAR m_szInspIp[SIZE_OF_100BYTE];			// 화상검사기 PC IP

	double	m_dMotorSpeed[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];		//속도
	double	m_dMotorAccTime[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];	//가속
	double  m_dMotorDecTime[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];	//감속
	double	m_dMotorResol[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];		//전자기어비
	double	m_dOrgDataset[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];		//강제원점

	double	m_dLimitSFRBalance[MAX_UNIT_COUNT];

	CDPoint m_clOCSpec[MAX_UNIT_COUNT];
	double m_dOCSpecTh[MAX_UNIT_COUNT];

	int m_nAAPort;				// MAIN PC Port
	int m_nInspPort;			// 화상검사기 PC Port
	int m_nLightPort;			// 조명 컨트롤러 포트
	int m_nDomeLightPort[2];	// DOME 조명 컨틀롤러 포트
	int m_nLaserPort[2];		// 변위센서 포트

	int m_nSFR_Type[MAX_LAST_INSP_COUNT + MAX_DOME_INSP_ADD];

	TCHAR m_szMesPath[SIZE_OF_1K];				// MES LOF DATA 저장 경로
};

