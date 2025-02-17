#include "stdafx.h"
#include "ModuleData.h"


CModuleData::CModuleData()
{
	int i, j;
	m_nSysNo = 0;
	m_nUnitNo = 0;

	_tcscpy_s(m_szModelName, SIZE_OF_100BYTE, _T("TEST"));
	_tcscpy_s(m_szPassword, SIZE_OF_100BYTE, _T("1111"));

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_MOTOR_COUNT; j++)
		{
			m_dMotorSpeed[i][j] = 0.0;
			m_dMotorAccTime[i][j] = 0.0;
			m_dMotorDecTime[i][j] = 0.0;
			m_dMotorResol[i][j] = 0.0;
			m_dOrgDataset[i][j] = 0.0;
		}
	}

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_dLimitSFRBalance[i] = 0.01;
		m_clOCSpec[i].x = m_clOCSpec[i].y = 0.02;
		m_dOCSpecTh[i] = 0.02;

		m_nLaserPort[i] = 0;
	}

	m_nLightPort = 0;

	memset(m_szMesPath, 0x00, sizeof(m_szMesPath));
}


CModuleData::~CModuleData()
{
}
