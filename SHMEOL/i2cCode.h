#pragma once

bool CPRIFunc_Insp::func_Insp_3M_Register(bool mDarkMode)
{
	TCHAR szLog[SIZE_OF_1K];
	int errorCode = 0;
	byte WData[1];

	unsigned int nSlaveAddress = 0x50;
	unsigned int nAddress1 = 0x8A80;
	unsigned int nAddress2 = 0xBF61;
	if (mDarkMode == true)
	{
		//Dark Test
		WData[0] = 0x00;//HCG Mode
	}
	else
	{
		//White Test
		WData[0] = 0x01;//LCG Mode
	}

	Sleep(15);
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress1, 2, WData, (unsigned short)1);
	if (errorCode)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[0x8A80] Write Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("[0x8A80] Set = %d"), WData[0]);
	AddLog(szLog, 0, m_nUnit);
	Sleep(15);
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress2, 2, WData, (unsigned short)1);
	if (errorCode)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[0xBF61] Write Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(szLog, SIZE_OF_1K, _T("[0xBF61] Set = %d"), WData[0]);
	AddLog(szLog, 0, m_nUnit);
	return true;
}
