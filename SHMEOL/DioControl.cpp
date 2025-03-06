#include "stdafx.h"
#include "DioControl.h"
#include "DioDefine.h"

CDioControl::CDioControl(void)
{
	int i;
	for(i = 0; i < MAX_DIO_COUNT; i++)
	{
		m_dwDIn[i] = 0;
		m_dwDOut[i] = 0;
	}

	for (i = 0; i < 2; i++)
	{
		ezSInput[i] = 0;
		ezSOutput[i] = 0;
	}

	for (i = 0; i < MAX_DIO_BYTE_COUNT; i++)
	{
		m_dByteDOutArr[i][0] = 0;
		m_dByteDOutArr[i][1] = 0;
		m_dByteDOutArr[i][2] = 0;
		m_dByteDOutArr[i][3] = 0;
	}
	// DIO 초기화
	//this->InitDio();
}

CDioControl::~CDioControl(void)
{
	// DIO Close
	this->CloseDio();
}

//-----------------------------------------------------------------------------
//
// DIO 모듈 초기화
//
//-----------------------------------------------------------------------------
bool CDioControl::InitDio()
{
#ifndef ON_LINE_DIO
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	DWORD dwRetVal;
	DWORD dwLevel;
	long lCount;

	dwLevel = HIGH;
	dwRetVal = 0;
	lCount = 0;

	if (AxlIsOpened() == false)
	{
		dwRetVal = AxlOpenNoReset(7);
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("DIO 라이브러리 초기화 실패"));
			//AddLog(szLog, 1, 999);
            AddLog(szLog, 1, 0);
            AddLog(szLog, 1, 1);
			return false;
		}
	}

	// 장착된 DIO 모듈 개수 확인
	dwRetVal = AxdInfoGetModuleCount(&lCount);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("DIO 모듈 개수 확인 실패"));
		//AddLog(szLog, 1, 999);
        AddLog(szLog, 1, 0);
        AddLog(szLog, 1, 1);
		return false;
	}

	if (lCount <= 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("시스템에 장착된 DIO 모듈이 없음"));
		//AddLog(szLog, 1, 999);
        AddLog(szLog, 1, 0);
        AddLog(szLog, 1, 1);
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
//
// DIO 모듈 Close
//
//-----------------------------------------------------------------------------
void CDioControl::CloseDio()
{
#ifndef ON_LINE_DIO
	return;
#endif

	if (AxlIsOpened())
	{
		AxlClose();
	}
}

//-----------------------------------------------------------------------------
//
// Ezi INPUT READ
//
//-----------------------------------------------------------------------------
bool CDioControl::eZiReadIn(int nModuleNo)
{

	return false;
}
//-----------------------------------------------------------------------------
//
// Ezi OUTPUT READ
//
//-----------------------------------------------------------------------------
int CDioControl::eZiReadOut(int nModuleNo, int noffset)
{

	return -1;
}
//-----------------------------------------------------------------------------
//
// INPUT READ
//
//-----------------------------------------------------------------------------
bool CDioControl::ReadDIn(int nModuleNo)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	DWORD dwInputVal;
	bool bRetVal;
	int nIndex;

	dwInputVal = 0;
	bRetVal = false;

	nIndex = (nModuleNo / 2);
	//
	if (AxdiReadInportDword(nModuleNo, 0, &dwInputVal) == AXT_RT_SUCCESS)
	{
		m_dwDIn[nIndex] = dwInputVal;

		bRetVal = true;
	}

	return bRetVal;
}
//-----------------------------------------------------------------------------
//
// INPUT READ
//
//-----------------------------------------------------------------------------
int CDioControl::ReadBitIn(int nModuleNo, int noffset)
{
	DWORD dwInputVal = 0;
	bool bRetVal = false;

	//noffset = 0 ~ 31
	//value = 0(Off), 1(On)
	//
	DWORD rtn = AxdoReadOutportBit(nModuleNo, noffset, &dwInputVal);
	if (rtn == AXT_RT_SUCCESS)
	{
		return (int)dwInputVal;
	}

	return -1;
	//===============================================================================================//
	// lModuleNo   : 모듈 번호
	// lOffset     : 입력 접점에 대한 Offset 위치
	// *upValue    : LOW(0)
	//             : HIGH(1)
	//===============================================================================================//
	//DWORD    __stdcall AxdiReadInportBit(long lModuleNo, long lOffset, DWORD *upValue);


}

DWORD CDioControl::GetEziOut(int nUnit)
{
	return 0x00;
}

//-----------------------------------------------------------------------------
//
// OUTPUT READ
//
//-----------------------------------------------------------------------------
bool CDioControl::ReadDOut(int nModuleNo)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	DWORD dwInputVal;
	bool bRetVal;
	int nIndex;

	dwInputVal = 0;
	bRetVal = false;

	nIndex = (nModuleNo / 2);

	if (AxdoReadOutportDword(nModuleNo, 0, &dwInputVal) == AXT_RT_SUCCESS)
	{
		m_dwDOut[nIndex] = dwInputVal;

		bRetVal = true;
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
// OUTPUT READ
//
//-----------------------------------------------------------------------------
bool CDioControl::ReadByteOut(int nModuleNo, int nOffset)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	DWORD dwInputVal;
	bool bRetVal;
	int nIndex;

	dwInputVal = 0;
	bRetVal = false;

	nIndex = (nModuleNo / 2);

	if (AxdoReadOutportByte(nModuleNo, nOffset, &dwInputVal) == AXT_RT_SUCCESS)
	{
		m_dByteDOutArr[nIndex][nOffset] = dwInputVal;

		bRetVal = true;
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
// OUTPUT WRITE
//
//-----------------------------------------------------------------------------
bool CDioControl::WriteDOut(int nModuleNo, DWORD dwOut)
{
	bool bRetVal;
	int nIndex;

	bRetVal = false;

	nIndex = (nModuleNo / 2);

#ifndef ON_LINE_DIO
	m_dwDOut[nIndex] = dwOut; 
	return true;
#endif

	m_clMutexWrite.Lock();

	if (AxdoWriteOutportDword(nModuleNo, 0, dwOut) == AXT_RT_SUCCESS)
	{ 
		m_dwDOut[nIndex] = dwOut;

		bRetVal = true;
	}
	m_clMutexWrite.Unlock();

	return bRetVal;
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CDioControl::ByteWriteDOut(int nModuleNo, int nOffset, DWORD dwOut)
{

	int nIndex = (nModuleNo / 2);
	m_clByteCriticalSection[nIndex][nOffset].Lock();
	bool bRetVal = false;

	

#ifndef ON_LINE_DIO
	m_dByteDOutArr[nIndex][nOffset] = dwOut;
	m_clByteCriticalSection[nIndex][nOffset].Unlock();
	return true;
#endif

	if (AxdoWriteOutportByte(nModuleNo, nOffset, dwOut) == AXT_RT_SUCCESS)
	{
		m_dByteDOutArr[nIndex][nOffset] = dwOut;
		bRetVal = true;
	}

	m_clByteCriticalSection[nIndex][nOffset].Unlock();
	return bRetVal;


	// 0번째 출력 접점 모듈의 Offset 0번지에서 byte 단위로 데이터를 출력한다.
	//AxdoWriteOutportByte(0, 0, 0xFF);
	//Function AxdoReadOutportByte(long lModuleNo, long lOffset, DWORD *upValue);
	//lOffset = 0 ~ 3
	//upValue 0 ~ FF
}

//-----------------------------------------------------------------------------
//
// PCB 제품 확인
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbSocketVacuumCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return bFlag;
#endif
#if 0
	int ch = nUnit * 0;
	static DWORD dwTickCount;
	int iModuleNo = (nUnit * 0) + 1;// (nUnit * 2) + 1;
	DWORD _shift = (nUnit * 16);
	// 전진
	if (bFlag == true)
	{
		if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_VACCUM_ON << _shift)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// 후진
	else
	{
		if (!(m_dwDIn[ch] & DIO_IN_PCB_SOCKET_VACCUM_ON << _shift))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{

		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_VACCUM_ON << _shift)
				{
					break;
				}
			}
			else
			{
				if (!(m_dwDIn[ch] & DIO_IN_PCB_SOCKET_VACCUM_ON << _shift))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
// EPOXY 도포
//
//-----------------------------------------------------------------------------
bool CDioControl::EpoxyDischargeOn(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	DWORD dwOutputVal;
	int iModuleNo = (nUnit * 0) + 1;
	DWORD _shift = (nUnit * 16);

	dwOutputVal = m_dwDOut[ch];

	// 흡착 
	if (bFlag == true)
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_EPOXY_ON << _shift);//DIO_OUT_EPOXY_ON
	}
	// 탈착
	else
	{
		dwOutputVal = dwOutputVal & ~(DIO_OUT_EPOXY_ON << _shift);//DIO_OUT_EPOXY_ON
	}

	if (this->WriteDOut(iModuleNo, dwOutputVal) == false)
	{
		return false;
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
// LENS 흡착/탈착
//
//-----------------------------------------------------------------------------
bool CDioControl::LensBufferVacuumOn(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	return true;
}

bool CDioControl::Start_Button_LedOn(int nUnit, bool bFlag, bool bWait)
{
	int ch = 0;
	DWORD dwTickCount;
	DWORD dwState;
	int iModuleNo = 1;
	int mOffset = 1;
	///dwState = m_dwDOut[ch];
	dwState = m_dByteDOutArr[0][mOffset];

	if (bFlag == true)
	{
		dwState = dwState | (DIO_OUT_START_PB_LED_L | DIO_OUT_START_PB_LED_R);
	}
	else
	{
		dwState = dwState & ~(DIO_OUT_START_PB_LED_L | DIO_OUT_START_PB_LED_R);
	}

	if (this->ByteWriteDOut(iModuleNo, mOffset, dwState) == false)
	{
		return false;
	}

	return true;
}
bool CDioControl::Stop_Button_LedOn(int nUnit, bool bFlag, bool bWait)
{
	int ch = 0;
	DWORD dwTickCount;
	DWORD dwState;
	int iModuleNo = 1;
	int mOffset = 1;
	///dwState = m_dwDOut[ch];
	dwState = m_dByteDOutArr[0][mOffset];

	if (bFlag == true)
	{
		dwState = dwState | (DIO_OUT_STOP_PB_LED);
	}
	else
	{
		dwState = dwState & ~(DIO_OUT_STOP_PB_LED);
	}


	if (this->ByteWriteDOut(iModuleNo, mOffset, dwState) == false)
	{
		return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
//
// PCB 흡착/탈착
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbVacuum(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
	int ch = 0;
	DWORD dwTickCount;
	DWORD dwState;
	int iModuleNo = 1;
	int mOffset = 1;
	///dwState = m_dwDOut[ch];
	dwState = m_dByteDOutArr[0][mOffset];
	if (bFlag == true)
	{
		dwState = dwState | (DIO_OUT_PCB_VACUUM_ON);
		dwState = dwState & ~(DIO_OUT_PCB_VACUUM_OFF);
	}
	// 탈착
	else
	{
		dwState = dwState | (DIO_OUT_PCB_VACUUM_OFF);
		dwState = dwState & ~(DIO_OUT_PCB_VACUUM_ON);
	}

	if (this->ByteWriteDOut(iModuleNo, mOffset, dwState) == false)
	{
		return false;
	}
	Sleep(500);

	if (bFlag == false)
	{
		dwState = dwState & ~(DIO_OUT_PCB_VACUUM_OFF);
	}
	if (this->ByteWriteDOut(iModuleNo, mOffset, dwState) == false)
	{
		return false;
	}

	Sleep(100);
	g_clDioControl.Stop_Button_LedOn(nUnit, bFlag);
	/*if (this->WriteDOut(iModuleNo, dwOutputVal) == false)
	{
		return false;
	}*/

	return true;
}

//-----------------------------------------------------------------------------
//
// PCB 흡착/탈착 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbVacuumCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	int ch = 0;
	if (bFlag == true)
	{
		if (m_dwDIn[ch] & DIO_IN_PCB_VACUUM)
		{
			return true;
		}
	}
	else
	{
		if (!(m_dwDIn[ch] & DIO_IN_PCB_VACUUM))
		{
			return true;
		}
	}


	return false;
}
//-----------------------------------------------------------------------------
//
// PCB STOP 버튼 
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbStopButtonCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	int ch = 0;
	if (bFlag == true)
	{
		if (m_dwDIn[ch] & DIO_IN_STOP_PB)
		{
			return true;
		}
	}
	else
	{
		if (!(m_dwDIn[ch] & DIO_IN_STOP_PB))
		{
			return true;
		}
	}


	return false;
}


//-----------------------------------------------------------------------------
//
// PCB 유/무 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbSensorCheck(int nUnit,  bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	int ch = 0;

	if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_CHECK)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//
// PCB Grip 전진/후진
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbGrip(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	static DWORD dwTickCount;
	DWORD dwOutputVal;
	int iModuleNo = (nUnit * 0) + 1;// (nUnit * 2) + 1;
	DWORD _shift = (nUnit * 16);
	dwOutputVal = m_dwDOut[ch];
	TCHAR szLog[SIZE_OF_1K];


	// 전진
	if (bFlag == true)
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_PCB_SOCKET_FORWARD << _shift);
	}
	// 탈착
	else
	{
		dwOutputVal = dwOutputVal & ~(DIO_OUT_PCB_SOCKET_FORWARD << _shift);
	}
	//if (bFlag == true)
	//{
	//	dwOutputVal = dwOutputVal | (DIO_OUT_PCB_SOCKET_FORWARD << _shift);
	//	dwOutputVal = dwOutputVal & ~(DIO_OUT_PCB_SOCKET_BACKWARD << _shift);
	//}
	//// 후진
	//else
	//{
	//	dwOutputVal = dwOutputVal | (DIO_OUT_PCB_SOCKET_BACKWARD << _shift);
	//	dwOutputVal = dwOutputVal & ~(DIO_OUT_PCB_SOCKET_FORWARD << _shift);
	//}
	if (this->WriteDOut(iModuleNo, dwOutputVal) == false)
	{
		return false;
	}
	if (bWait == true)
	{
		dwTickCount = GetTickCount();
		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[ch] | (DIO_IN_PCB_SOCKET_FORWARD << _shift)) 
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[ch] & ~(DIO_IN_PCB_SOCKET_FORWARD << _shift))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}
//

//-----------------------------------------------------------------------------
//
// DOOR 버튼 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::DoorBbCheck(int nUnit, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	DWORD dwTickCount;
	int iModuleNo = (nUnit * 0) + 1;// (nUnit * 2) + 1;
	DWORD _shift = (nUnit * 16);
	// 전진
	if (m_dwDIn[ch] & DIO_IN_DOOR_PB << _shift)
	{
		return true;
	}
	else
	{
		return false;
	}

	if (bWait == true)
	{

		dwTickCount = GetTickCount();

		while (1)
		{
			if (m_dwDIn[ch] & DIO_IN_DOOR_PB << _shift)
			{
				break;
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
// LENS BUFFER 유/무 센서 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::LensBufferSensorCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
// LENS BUFFER 유/무 흡착 감지
//
//-----------------------------------------------------------------------------

bool CDioControl::LensBufferVacuumOnCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	return false;
}


bool CDioControl::CurtainDoorCheck(int nUnit, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	int ch = 0;
	if (!(m_dwDIn[ch] & DIO_IN_LIGHT_CURTAIN))
	{
		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------
//
// START 버튼 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::StartBbCheck(int nUnit, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	int ch = 0;

	DWORD dwState = 0;
	dwState |= DIO_IN_START_PB_L;
	dwState |= DIO_IN_START_PB_R;

	if ((m_dwDIn[ch] & dwState) == dwState)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//
// PCB Grip 전진/후진 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbGripCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	static DWORD dwTickCount;
	int iModuleNo = (nUnit * 0) + 1;// (nUnit * 2) + 1;
	DWORD _shift = (nUnit * 16);
	// 전진
	if (bFlag == true)
	{
		if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_FORWARD << _shift)
		{
			return true;
		}
		else
		{
			return false; 
		}
	}
	// 후진
	else
	{
		if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_BACKWARD << _shift)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{

		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_FORWARD << _shift)
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_BACKWARD << _shift)
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}


//-----------------------------------------------------------------------------
//
// PCB Grip 상승/하강
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbGripUp(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
	//int ch = nUnit * 0;
	//static DWORD dwTickCount;
	//DWORD dwOutputVal;
	//int iModuleNo = (nUnit * 0) + 1;// (nUnit * 2) + 1;
	//DWORD _shift = (nUnit * 16);
	//dwOutputVal = m_dwDOut[ch];

	//// 전진
	//if (bFlag == true)
	//{
	//	dwOutputVal = dwOutputVal | (DIO_OUT_PCB_SOCKET_UP << _shift);
	//	dwOutputVal = dwOutputVal & ~(DIO_OUT_PCB_SOCKET_DOWN << _shift);
	//}
	//// 후진
	//else
	//{
	//	dwOutputVal = dwOutputVal | (DIO_OUT_PCB_SOCKET_DOWN << _shift);
	//	dwOutputVal = dwOutputVal & ~(DIO_OUT_PCB_SOCKET_UP << _shift);
	//}

	//this->WriteDOut(iModuleNo, dwOutputVal);

	//if (bWait == true)
	//{
	//	dwTickCount = GetTickCount();
	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[ch] & (DIO_IN_PCB_SOCKET_UP << _shift))
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (m_dwDIn[ch] & (DIO_IN_PCB_SOCKET_DOWN << _shift))
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	//Sleep((DWORD)(g_clModelData[nUnit].m_dPCBGripUpDelay * 1000));

	return true;
}

//-----------------------------------------------------------------------------
//
// PCB Grip 상승/하강 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbGripUpCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//int ch = nUnit * 0;
	//static DWORD dwTickCount;
	//int iModuleNo = (nUnit * 0) + 1;// (nUnit * 2) + 1;
	//DWORD _shift = (nUnit * 16);
	//// 상승
	//if (bFlag == true)
	//{
	//	if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_UP << _shift)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	//// 하강
	//else
	//{
	//	if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_DOWN << _shift)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//if (bWait == true)
	//{

	//	dwTickCount = GetTickCount();

	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_UP << _shift)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (m_dwDIn[ch] & DIO_IN_PCB_SOCKET_DOWN << _shift)
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}


//-----------------------------------------------------------------------------
//
// LENS 제품 확인
//
//-----------------------------------------------------------------------------
bool CDioControl::LensSocketCheck(int nUnit, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	static DWORD dwTickCount;

	if (m_dwDIn[nUnit] & DIO_IN_LENS_SOCKET_CHECK)
	{
		return true;
	}
	else
	{
		return false;
	}

	if (bWait == true)
	{
		dwTickCount = GetTickCount();

		while (1)
		{
			if (m_dwDIn[nUnit] & DIO_IN_LENS_SOCKET_CHECK)
			{
				break;
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}


bool CDioControl::CurtainUpDown(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	DWORD dwTickCount;
	DWORD dwOutputVal;
	int iModuleNo = (nUnit * 2) + 1;

	dwOutputVal = m_dwDOut[nUnit];

	// 전진
	if (bFlag == true)
	{
		dwOutputVal = dwOutputVal | DIO_OUT_DOOR_SHUTTER_UP;
		dwOutputVal = dwOutputVal & ~DIO_OUT_DOOR_SHUTTER_DOWN;
	}
	// 후진
	else
	{
		dwOutputVal = dwOutputVal | DIO_OUT_DOOR_SHUTTER_DOWN;
		dwOutputVal = dwOutputVal & ~DIO_OUT_DOOR_SHUTTER_UP;
	}

	if (this->WriteDOut(iModuleNo, dwOutputVal) == false)
		return false;

	if (bWait == true)
	{
		dwTickCount = GetTickCount();
		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[nUnit] & DIO_IN_DOOR_SHUTTER_UP)
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[nUnit] & DIO_IN_DOOR_SHUTTER_DOWN)
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > 5000)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}


bool CDioControl::CurtainUpDownCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	DWORD dwTickCount;

	// 전진
	if (bFlag == true)
	{
		if (m_dwDIn[nUnit] & DIO_IN_DOOR_SHUTTER_UP)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// 후진
	else
	{
		if (m_dwDIn[nUnit] & DIO_IN_DOOR_SHUTTER_DOWN)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{

		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[nUnit] & DIO_IN_DOOR_SHUTTER_UP)
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[nUnit] & DIO_IN_DOOR_SHUTTER_DOWN)
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//----------------------------------------------------------------------------
//
// PCB SOCKET UP / DOWN
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbSocketUp(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int outCh = 0;
	static DWORD dwTickCount;
	DWORD dwOutputVal;
	int iModuleNo = 1;
	
	DWORD dwState = 0;
	dwOutputVal = m_dwDOut[outCh];
	DWORD _shift = (nUnit * 16);
	// 전진
	if (bFlag == true)
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_PCB_SOCKET_UP << _shift);
		dwOutputVal = dwOutputVal & (~DIO_OUT_PCB_SOCKET_DOWN << _shift);
	}
	// 후진
	else
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_PCB_SOCKET_DOWN << _shift);
		dwOutputVal = dwOutputVal & (~DIO_OUT_PCB_SOCKET_UP << _shift);
	}

	if (this->WriteDOut(iModuleNo, dwOutputVal) == false)
		return false;

	if (bWait == true)
	{
		dwTickCount = GetTickCount();
		while (1)
		{
			if (bFlag == true)
			{
				dwState |= (DIO_IN_PCB_SOCKET_UP << _shift);
				if ((m_dwDIn[nUnit] & dwState) == dwState)//if (m_dwDIn[nUnit] & DIO_IN_LENS_GRIP)
				{
					break;
				}
			}
			else
			{
				dwState |= (DIO_IN_PCB_SOCKET_DOWN << _shift);
				if ((m_dwDIn[nUnit] & dwState) == dwState)//if (m_dwDIn[nUnit] & DIO_IN_LENS_UNGRIP)
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
// PCB SOCKET UP / DOWN 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::PcbSocketUpCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	DWORD dwTickCount;
	DWORD dwState = 0;
	int ioIndex = 0; 
	DWORD _shift = (nUnit * 16);
	// 전진
	if (bFlag == true)
	{
		if (m_dwDIn[ioIndex] & (DIO_IN_PCB_SOCKET_UP << _shift))
		{
			return true;
		}
		else
		{
			if (bWait == false)
			{
				return false;
			}
		}
	}
	// 후진
	else
	{
		if (m_dwDIn[ioIndex] & (DIO_IN_PCB_SOCKET_DOWN << _shift))
		{
			return true;
		}
		else
		{
			if (bWait == false)
			{
				return false;
			}
		}
	}

	if (bWait == true)
	{
		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[ioIndex] & (DIO_IN_PCB_SOCKET_UP << _shift))
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[ioIndex] & (DIO_IN_PCB_SOCKET_DOWN << _shift))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
// LENS Grip 전진/후진
//
//-----------------------------------------------------------------------------
bool CDioControl::LensGrip(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
// LENS Grip 전진/후진 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::LensGripCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
// LENS Stage Grip 전진/후진
//
//-----------------------------------------------------------------------------
bool CDioControl::LensStageGrip(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//static DWORD dwTickCount;
	//DWORD dwOutputVal;
	//int iModuleNo = (nUnit * 2) + 1;

	//dwOutputVal = m_dwDOut[nUnit];

	//// 전진
	//if (bFlag == true)
	//{
	//	dwOutputVal = dwOutputVal | DIO_OUT_LENS_STAGE_GRIP_FOR;
	//	dwOutputVal = dwOutputVal & ~DIO_OUT_LENS_STAGE_GRIP_BACK;
	//}
	//// 후진
	//else
	//{
	//	dwOutputVal = dwOutputVal | DIO_OUT_LENS_STAGE_GRIP_BACK;
	//	dwOutputVal = dwOutputVal & ~DIO_OUT_LENS_STAGE_GRIP_FOR;
	//}

	//this->WriteDOut(iModuleNo, dwOutputVal);

	//if (bWait == true)
	//{
	//	dwTickCount = GetTickCount();
	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_LENS_STAGE_GRIP_FOR)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_LENS_STAGE_GRIP_BACK)
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
// LENS Stage Grip 전진/후진 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::LensStageGripCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//static DWORD dwTickCount;

	//// 전진
	//if (bFlag == true)
	//{
	//	if (m_dwDIn[nUnit] & DIO_IN_LENS_STAGE_GRIP_FOR)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	//// 후진
	//else
	//{
	//	if (m_dwDIn[nUnit] & DIO_IN_LENS_STAGE_GRIP_BACK)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//if (bWait == true)
	//{

	//	dwTickCount = GetTickCount();

	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_LENS_STAGE_GRIP_FOR)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_LENS_STAGE_GRIP_BACK)
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
// 검사 FEED 전진/ 후진
//
//-----------------------------------------------------------------------------
bool CDioControl::FeedMove(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//static DWORD dwTickCount;
	//DWORD dwOutputVal;
	//int iModuleNo = (nUnit * 2) + 1;

	//dwOutputVal = m_dwDOut[nUnit];

	//// 전진
	//if (bFlag == true)
	//{
	//	dwOutputVal = dwOutputVal | DIO_OUT_FEED_FORWARD;
	//	dwOutputVal = dwOutputVal & ~DIO_OUT_FEED_BACKWARD;
	//}
	//// 후진
	//else
	//{
	//	dwOutputVal = dwOutputVal | DIO_OUT_FEED_BACKWARD;
	//	dwOutputVal = dwOutputVal & ~DIO_OUT_FEED_FORWARD;
	//}

	//this->WriteDOut(iModuleNo, dwOutputVal);

	//if (bWait == true)
	//{
	//	dwTickCount = GetTickCount();
	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_FEED_FORWARD)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_FEED_BACKWARD)
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
// 검사 FEED 전진/ 후진 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::FeedMoveCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//static DWORD dwTickCount;

	//// 전진
	//if (bFlag == true)
	//{
	//	if (m_dwDIn[nUnit] & DIO_IN_FEED_FORWARD)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	//// 후진
	//else
	//{
	//	if (m_dwDIn[nUnit] & DIO_IN_FEED_BACKWARD)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//if (bWait == true)
	//{

	//	dwTickCount = GetTickCount();

	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_FEED_FORWARD)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_FEED_BACKWARD)
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
// 컨택 상승 / 하강
//
//-----------------------------------------------------------------------------
bool CDioControl::ContactUp(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	static DWORD dwTickCount;
	DWORD dwOutputVal;

	int iModuleNo = 1;

	
	dwOutputVal = m_dwDOut[ch];



	// 전진
	if (bFlag == true)
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_CONTACT_UP);
		dwOutputVal = dwOutputVal & ~(DIO_OUT_CONTACT_DOWN);
	}
	// 후진
	else
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_CONTACT_DOWN);
		dwOutputVal = dwOutputVal & ~(DIO_OUT_CONTACT_UP);
	}

	

	this->WriteDOut(iModuleNo, dwOutputVal);

	if (bWait == true)
	{
		dwTickCount = GetTickCount();
		while (1)
		{ 
			if (bFlag == true)
			{
				if (m_dwDIn[ch] & (DIO_IN_CONTACT_UP))
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[ch] & (DIO_IN_CONTACT_DOWN))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}
//-----------------------------------------------------------------------------
//
// 컨택 상승 / 하강 확인
//
//-----------------------------------------------------------------------------
bool CDioControl::ContactUpcheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	static DWORD dwTickCount;

	// 상승
	if (bFlag == true)
	{
		if (m_dwDIn[ch] & (DIO_IN_CONTACT_UP))
		{
			return true;
		}
		else
		{
			if (bWait == false)
			{
				return false;
			}
		}
	}
	// 하강
	else
	{
		if (m_dwDIn[ch] & (DIO_IN_CONTACT_DOWN))
		{
			return true;
		}
		else
		{
			if (bWait == false)
			{
				return false;
			}
		}
	}

	

	if (bWait == true)
	{

		dwTickCount = GetTickCount();

		while (1)
		{

			if (bFlag == true)
			{
				if (m_dwDIn[ch] & (DIO_IN_CONTACT_UP))
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[ch] & (DIO_IN_CONTACT_DOWN))
				{
					break;
				}
			}
			

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}


//-----------------------------------------------------------------------------
//
// DARK PUSHER 상승 / 하강
//
//-----------------------------------------------------------------------------
bool CDioControl::DarkPusher(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	static DWORD dwTickCount;
	DWORD dwOutputVal;
	int iModuleNo = 1;
	DWORD _shift = (nUnit * 16);
	dwOutputVal = m_dwDOut[ch];

	// 상승
	if (bFlag == true)
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_DARK_PUSHER_UP); 
		dwOutputVal = dwOutputVal & ~(DIO_OUT_DARK_PUSHER_DOWN);
	}
	// 하강
	else
	{
		dwOutputVal = dwOutputVal | (DIO_OUT_DARK_PUSHER_DOWN);
		dwOutputVal = dwOutputVal & ~(DIO_OUT_DARK_PUSHER_UP);
	}

	this->WriteDOut(iModuleNo, dwOutputVal);

	if (bWait == true)
	{
		dwTickCount = GetTickCount();
		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[ch] & (DIO_IN_DARK_PUSHER_UP))
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[ch] & (DIO_IN_DARK_PUSHER_DOWN)) 
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
// DARK PUSHER 상승 / 하강 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::DarkPusherCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif
#if 0
	int ch = nUnit * 0;
	static DWORD dwTickCount;
	DWORD _shift = (nUnit * 16);
	// 상승
	if (bFlag == true)
	{
		if (m_dwDIn[ch] & (DIO_IN_DARK_PUSHER_UP))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// 하강
	else
	{
		if (m_dwDIn[ch] & (DIO_IN_DARK_PUSHER_DOWN))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{

		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[ch] & (DIO_IN_DARK_PUSHER_UP))
				{
					break;
				}
			}
			else
			{
				if (m_dwDIn[ch] & (DIO_IN_DARK_PUSHER_DOWN))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
//	UV 조명 On/Off
//
//-----------------------------------------------------------------------------
bool CDioControl::UVOn(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	UV 조명 On/Off 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::UVOnCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//static DWORD dwTickCount;

	//// UV ON
	//if (bFlag == true)
	//{
	//	if (m_dwDIn[nUnit] & DIO_IN_UV_ON)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	//else
	//{
	//	if (!(m_dwDIn[nUnit] & DIO_IN_UV_ON))
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//if (bWait == true)
	//{
	//	dwTickCount = GetTickCount();

	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_UV_ON)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (!(m_dwDIn[nUnit] & DIO_IN_UV_ON))
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
//	UV SHUTTER OPEN/CLOSE
//
//-----------------------------------------------------------------------------
bool CDioControl::UVShutter(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//static DWORD dwTickCount;
	//DWORD dwOutput;
	//int iModuelNo = (nUnit * 2) + 1;

	//dwOutput = m_dwDOut[nUnit];

	//// SHUTTER OPEN
	//if (bFlag == true)
	//{
	//	dwOutput |= DIO_OUT_UV_SHUTTER;
	//}
	//// SHUTTER CLOSE
	//else
	//{
	//	dwOutput &= ~DIO_OUT_UV_SHUTTER;
	//}

	//this->WriteDOut(iModuelNo, dwOutput);

	//if (bWait == true)
	//{
	//	dwTickCount = GetTickCount();
	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_UV_SHUTTER_OPEN)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (!(m_dwDIn[nUnit] & DIO_IN_UV_SHUTTER_CLOSE))
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
//	UV SHUTTER 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::UVShutterCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	//static DWORD dwTickCount;

	//// OPEN
	//if (bFlag == true)
	//{
	//	if (m_dwDIn[nUnit] & DIO_IN_UV_SHUTTER_OPEN)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	//// CLOSE
	//else
	//{
	//	if (m_dwDIn[nUnit] & DIO_IN_DARK_PUSHER_DOWN)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//if (bWait == true)
	//{

	//	dwTickCount = GetTickCount();

	//	while (1)
	//	{
	//		if (bFlag == true)
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_UV_SHUTTER_OPEN)
	//			{
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			if (m_dwDIn[nUnit] & DIO_IN_UV_SHUTTER_CLOSE)
	//			{
	//				break;
	//			}
	//		}

	//		if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
	//		{
	//			return false;
	//		}

	//		Sleep(10);
	//	}
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
//	UV ERROR 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::UVErrorCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return false;
#endif

	/*static DWORD dwTickCount;

	if (bFlag == true)
	{
		if (m_dwDIn[nUnit] & DIO_IN_UV_ERROR)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!(m_dwDIn[nUnit] & DIO_IN_UV_ERROR))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{
		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[nUnit] & DIO_IN_UV_ERROR)
				{
					break;
				}
			}
			else
			{
				if (!(m_dwDIn[nUnit] & DIO_IN_UV_ERROR))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}*/
	return true;
}

//-----------------------------------------------------------------------------
//
//	UV READY 상태 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::UVReadyCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	/*static DWORD dwTickCount;

	if (bFlag == true)
	{
		if (m_dwDIn[nUnit] & DIO_IN_UV_READY)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!(m_dwDIn[nUnit] & DIO_IN_UV_READY))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{
		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[nUnit] & DIO_IN_UV_READY)
				{
					break;
				}
			}
			else
			{
				if (!(m_dwDIn[nUnit] & DIO_IN_UV_READY))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}*/
	return true;
}

//-----------------------------------------------------------------------------
//
//	UV 조리개 MAX/MIN 감지
//
//-----------------------------------------------------------------------------
bool CDioControl::UVApertureCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	/*static DWORD dwTickCount;

	if (bFlag == true)
	{
		if (m_dwDIn[nUnit] & DIO_IN_UV_APERTURE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!(m_dwDIn[nUnit] & DIO_IN_UV_APERTURE))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{
		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[nUnit] & DIO_IN_UV_APERTURE)
				{
					break;
				}
			}
			else
			{
				if (!(m_dwDIn[nUnit] & DIO_IN_UV_APERTURE))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}*/
	return true;
}

//-----------------------------------------------------------------------------
//
//	UV 사용시간 
//
//-----------------------------------------------------------------------------
bool CDioControl::UVUseTimeCheck(int nUnit, bool bFlag, bool bWait)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	/*static DWORD dwTickCount;

	if (bFlag == true)
	{
		if (m_dwDIn[nUnit] & DIO_IN_UV_USE_TIME)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!(m_dwDIn[nUnit] & DIO_IN_UV_USE_TIME))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bWait == true)
	{
		dwTickCount = GetTickCount();

		while (1)
		{
			if (bFlag == true)
			{
				if (m_dwDIn[nUnit] & DIO_IN_UV_USE_TIME)
				{
					break;
				}
			}
			else
			{
				if (!(m_dwDIn[nUnit] & DIO_IN_UV_USE_TIME))
				{
					break;
				}
			}

			if ((GetTickCount() - dwTickCount) > MAX_WAIT_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}*/
	return true;
}


//-----------------------------------------------------------------------------
//
//	DOOR 상태 반환
//
//-----------------------------------------------------------------------------
int CDioControl::GetDoorState()
{
#ifndef ON_LINE_DIO
	return true;
#endif

	DWORD dwState = 0;
	DWORD dwSumState = 0;


	dwState |= DIO_IN_DOOR_OPEN_1;
	dwSumState = m_dwDIn[0] & dwState;
	dwState |= DIO_IN_DOOR_OPEN_2;
	dwSumState = m_dwDIn[0] & dwState;
	dwState |= DIO_IN_DOOR_OPEN_3;
	dwSumState = m_dwDIn[0] & dwState;

	//1 = 좌측 도어 열림
	//2 = 뒷면 도어 열림
	//3 = 좌측,뒷면 열림
	//4 = 우측
	//5 = 좌,우 열림
	//6 = 뒤면, 우측
	//7 = 3개다 열림

	return dwSumState;
}

bool CDioControl::SetBuzzer(bool bOn, int nType)
{
#ifndef ON_LINE_DIO
	return true;
#endif
	DWORD dwState;
	int iModuleNo = 1;
	int mOffset = 0;
	///dwState = m_dwDOut[0];
	dwState = m_dByteDOutArr[0][mOffset];
	// BUZZER OFF
	dwState &= ~(DIO_OUT_BUZZER_1 | DIO_OUT_BUZZER_2 | DIO_OUT_BUZZER_3 | DIO_OUT_BUZZER_4);

	if (bOn == true)
	{
		switch (nType)
		{
		case 0:
			dwState &= ~(DIO_OUT_BUZZER_1 | DIO_OUT_BUZZER_2 | DIO_OUT_BUZZER_3 | DIO_OUT_BUZZER_4);
			break;
		case 1:
			dwState |= DIO_OUT_BUZZER_1;
			dwState &= ~(DIO_OUT_BUZZER_2 | DIO_OUT_BUZZER_3 | DIO_OUT_BUZZER_4);
			break;
		case 2:
			dwState |= DIO_OUT_BUZZER_3;
			dwState &= ~(DIO_OUT_BUZZER_1 | DIO_OUT_BUZZER_2 | DIO_OUT_BUZZER_4);
			break;
		default:
			dwState &= ~(DIO_OUT_BUZZER_1 | DIO_OUT_BUZZER_2 | DIO_OUT_BUZZER_3 | DIO_OUT_BUZZER_4);
			break;
		}
	}
	/*if (this->WriteDOut(iModuleNo, dwState) == false) {
		return false;
	}*/
	if (this->ByteWriteDOut(iModuleNo, mOffset, dwState) == false)
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	타워램프 컨트롤
//
//-----------------------------------------------------------------------------
bool CDioControl::SetTowerLamp(int nType, bool bOn)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	DWORD dwState = 0;
	int iModuleNo = 1;
	int mOffset = 0;
	//dwState = m_dwDOut[0];
	dwState = m_dByteDOutArr[0][mOffset];
	switch (nType)
	{
		// ALL OFF
	case 0:
		dwState &= ~(DIO_OUT_TOWER_LAMP_R | DIO_OUT_TOWER_LAMP_G | DIO_OUT_TOWER_LAMP_Y);
		break;
		// LAMP RED
	case 1:
		if (bOn == true)
		{
			dwState |= DIO_OUT_TOWER_LAMP_R;
			dwState &= ~(DIO_OUT_TOWER_LAMP_G | DIO_OUT_TOWER_LAMP_Y);
		}
		else
		{
			dwState &= ~DIO_OUT_TOWER_LAMP_R;
		}
		break;
		// LAMP GREEN
	case 2:
		if (bOn == true)
		{
			dwState |= DIO_OUT_TOWER_LAMP_G;
			dwState &= ~(DIO_OUT_TOWER_LAMP_R | DIO_OUT_TOWER_LAMP_Y);
		}
		else
		{
			dwState &= ~DIO_OUT_TOWER_LAMP_G;
		}
		break;
		// LAMP YELLOW
	case 3:
		if (bOn == true)
		{
			dwState |= DIO_OUT_TOWER_LAMP_Y;
			dwState &= ~(DIO_OUT_TOWER_LAMP_R | DIO_OUT_TOWER_LAMP_G);
		}
		else
		{
			dwState &= ~DIO_OUT_TOWER_LAMP_Y;
		}
		break;
	}

	/*if (this->WriteDOut(iModuleNo, dwOutputVal) == false)
	{
		return false;
	}*/
	if (this->ByteWriteDOut(iModuleNo, mOffset, dwState) == false)
	{
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	DOOR UNLOCK 동작
//
//-----------------------------------------------------------------------------
bool CDioControl::DoorUnLock(int index, bool bFlag)
{
#ifndef ON_LINE_DIO
	return false;
#endif
	DWORD dwState = 0;
	int nModuleNo = 1;
	int mOffset = 1;
	////dwState = m_dwDOut[0];
	dwState = m_dByteDOutArr[0][mOffset];

	//도어락에 led가 켜지면 open상태이다.
	if (bFlag == true)
	{
		dwState |= DIO_OUT_DOOR_UNLOCK_ALL;
		//dwState = dwState | (DIO_OUT_DOOR_UNLOCK_ALL);
	}
	else
	{
		dwState &= ~DIO_OUT_DOOR_UNLOCK_ALL;
		//dwState = dwState & ~(DIO_OUT_DOOR_UNLOCK_ALL);
	}

	/*if (this->WriteDOut(nModuleNo, dwState) == false)
	{
		return false;
	}*/

	if (this->ByteWriteDOut(nModuleNo, mOffset, dwState) == false)
	{
		return false;
	}

	return true;

}


//-----------------------------------------------------------------------------
//
//	DOOR UNLOCK상태 반환
//
//-----------------------------------------------------------------------------
bool CDioControl::GetDoorUnLockState()
{
#ifndef ON_LINE_DIO
	return true;
#endif
	DWORD dwState = 0;
	dwState |= DIO_IN_DOOR_OPEN_1;
	dwState |= DIO_IN_DOOR_OPEN_2;
	dwState |= DIO_IN_DOOR_OPEN_3;


	DWORD dwSumState = m_dwDIn[0] & dwState;

	if (dwSumState > 0)
	{
		return false;
	}
	return true;
}



//-----------------------------------------------------------------------------
//
//	LG DOOR 신호
//
//-----------------------------------------------------------------------------
bool CDioControl::LGDoorSignalOn(bool bFlag)
{
#ifndef ON_LINE_DIO
	return true;
#endif

	int ch = 0;
	DWORD dwTickCount;
	DWORD dwState;
	int iModuleNo = 1;
	int mOffset = 3;
	dwState = m_dByteDOutArr[0][mOffset];

	if (bFlag == true)
	{
		dwState = dwState | (DIO_OUT_LG_DOOR);
	}
	// 탈착
	else
	{
		dwState = dwState & ~(DIO_OUT_LG_DOOR);
	}

	if (this->ByteWriteDOut(iModuleNo, mOffset, dwState) == false)
	{
		return false;
	}

	return true;

}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CDioControl::eZiWriteOut(int nUnit, DWORD dwPrevOut , DWORD dwCurOut)
{
	return false;
}
