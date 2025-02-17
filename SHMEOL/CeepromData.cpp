#include "stdafx.h"
#include "AutoInspDlg.h"
//#include "path.h"
#include "CeepromData.h"
//
//extern CDBLoadData			DbLoadData;
//extern CeepromData			eepromData;
CeepromData::CeepromData()
{

}

CeepromData::~CeepromData()
{
}

//STRING 은 ASCII 로 변경
//HEX 는 는 값 그대로 (12 = 0X12)
//FLOAT 는 HEX로 변경해서 입력
//-12.22 = 0xc143851f
//CString data = _T("0.12345");//0x3dfcd35b   //48464950515253
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CeepromData::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}


void CeepromData::HexToString(byte* rtnData, int Length, TCHAR* strData, int nType)
{
	int i = 0;
	int value = 0;
	float fNum = 0.0;
	UINT32 fTemp = 0;
	CString mData;
	CString tempData;
	mData.Empty();
	tempData.Empty();

	for (int i = 0; i < Length; i++)
	{
		tempData.AppendFormat("%02X", (char*)rtnData[i]);		//HEX -> FLOAT
	}
	if (nType == FLOAT_MODE)
	{
		sscanf_s(tempData, "%X", &fTemp);
		fNum = *((float*)&fTemp);
		_stprintf_s(strData, SIZE_OF_100BYTE, _T("%f"), fNum);
	}
	else if (nType == DEC_MODE)
	{

		value = (int)strtol(tempData, NULL, 16);
		mData.AppendFormat("%d", value);
		_stprintf_s(strData, SIZE_OF_100BYTE, _T("%s"), mData);
	}
	else if (nType == ASCII_MODE)
	{
		for (i = 0; i < Length; i++)
		{
			value = (byte)_tcstol(tempData.Mid(i * 2, 2), NULL, 16);
			mData.AppendFormat("%c", value);

		}
		_stprintf_s(strData, SIZE_OF_100BYTE, _T("%s"), mData);
	}

}
void CeepromData::StringToHex(string title, CString data, byte* rtnData, int index = 0)
{
#if 0
	int i = 0;
	int value = 0;
	int StrLength = 0;
	int findPos = -1;
	int mOffset = 0;
	float fNum = 0.0;
	byte szTemp[MAX_PATH];
	data.Trim();
	memset(szTemp, 0, sizeof(szTemp));
	memset(rtnData, 0x00, sizeof(rtnData));
	findPos = data.Find(_T("0x"));	//(data.Find(_T("0x")) + 1) * 2;	//0x 찾아서 16진수이면 그대로 입력
	StrLength = data.GetLength();
	CString logStr;
	CString strTemp;
	logStr.Empty();
	strTemp.Empty();
	if (findPos == 0)		//0이면 0x있는 16진수 이다
	{
		StrLength = (StrLength - 1) / 2;		//0x 문자길이 1개 삭제
		mOffset = 2;
	}
	//if (title.compare(strArr[2]) == 0 || title.compare(strArr[3]) == 0)
	if (title.compare(MesSpecList[105]) == 0 || title.compare(MesSpecList[106]) == 0)
	{
		findPos = 2;
		StrLength = 1;
		value = _ttoi(data);
		memcpy(szTemp, &value, sizeof(int));
		for (i = 0; i < StrLength; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[StrLength - i - 1]);// szTemp[3 - x]);
		}
	}
	//else if (title.compare(strArr[0]) == 0 || title.compare(strArr[1]) == 0		//정수
	//	|| title.compare(strArr[4]) == 0 || title.compare(strArr[5]) == 0)
	else if (title.compare(strArr[103]) == 0 || title.compare(strArr[104]) == 0		//정수
		|| title.compare(strArr[107]) == 0 || title.compare(strArr[108]) == 0)
	{
		findPos = 2;
		StrLength = 2;		// 1;leng = 1;
		value = _ttoi(data);
		memcpy(szTemp, &value, sizeof(int));
		for (i = 0; i < StrLength; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[StrLength - i - 1]);// szTemp[3 - x]);
		}
	}
	else// if (title.compare("Pixel Size") == 0)		//float 4byte 실수
	{
		//230421 eol은 eeprom쓰는거 외에 실수라서 이쪽으로 이동
		findPos = 1;
		StrLength = 4;
		fNum = (float)_ttof(data);//fNum = (_ttof(WriteData));//atof  //wtof
		memcpy(szTemp, &fNum, sizeof(float));//들어갈때 반대로 값이 들어간다 

	}
	//
	//Height - Y
	for (int i = 0; i < StrLength; i++)
	{
		if (findPos == 0)
		{
			//16진수 0x~~~~
			rtnData[i] = (byte)_tcstol(data.Mid(i * 2 + mOffset, 2), NULL, 16);
		}
		else if (findPos == 1)
		{
			//float 실수
			rtnData[i] = szTemp[3 - i];
		}
		else if (findPos == 2)
		{
			//정수 1920
			rtnData[i] = (byte)_tcstol(strTemp.Mid(i * 2 + mOffset, 2), NULL, 16);
		}
		else
		{
			//ex)LGIT 
			value = (int)(data[i]);
			rtnData[i] = value & 0xFF;
		}
		logStr.AppendFormat("%02X", rtnData[i]);
	}

	 
	CString viewLog;
	if (index == 0)
	{
		viewLog.Format("[MIN] %s=%s[%s]", title.c_str(), data, logStr);
	}
	else
	{
		viewLog.Format("[MAX] %s=%s[%s]", title.c_str(), data, logStr);
	}
	
	AddLog(viewLog, 0 , m_nUnit);
	viewLog.Empty();
	logStr.Empty();
	strTemp.Empty();
#endif
	return;
}

bool CeepromData::EEPROM_TotalRead_Type(unsigned short slaveAddress, unsigned int StartAddress, unsigned int EndAddress, byte* TotalData, int ReadLength)
{
	CString tempData = _T("");

	int errorCode = 0;
	int i = 0;
	int j = 32;
	int readCount = EndAddress - StartAddress;//총 82개 읽어야됨

	for (i = 0; i <= readCount; i++)
	{
		//virtual int ReadI2CBurst(unsigned short nSlaveAddr, unsigned short nAddr, unsigned char nAddrByteCount, unsigned char* pData, unsigned short nReadByteCount) = 0;
		errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)slaveAddress, (unsigned short)StartAddress + i, 1, TotalData + i, (unsigned short)ReadLength);

		if (errorCode)
		{
			tempData.Format("[MANUAL] eeprom READ Fail!");
			AddLog(tempData, 1, m_nUnit);

			tempData.Format("Error : %d", errorCode);
			AddLog(tempData, 1, m_nUnit);

			tempData.AppendFormat(" %s", GetErrorStr(errorCode));
			AddLog(tempData, 1, m_nUnit);
			return false;
		}
		j++;
		Sleep(2);
	}
	return true;
}
#if 0
void CeepromData::eeprom_Data_Sum(CString WriteData, int WritebyteLength, int type, byte* rtnData, bool autoRun)
{
	unsigned char pData[MAX_PATH];
	int errorCode = 0;
	int i = 0;
	int j = 0;
	int leng = WriteData.GetLength();
	int value = 0;
	float fNum = 0.0;
	double testnum = 0.0;
	CString strTemp;
	int startNum = 0;
	unsigned char szTemp[MAX_PATH];
	memset(pData, 0, sizeof(pData));
	memset(rtnData, 0, sizeof(WritebyteLength));

	if (type == FLOAT_MODE)
	{
		fNum = (float)_ttof(WriteData);//fNum = (_ttof(WriteData));//atof  //wtof
		memcpy(szTemp, &fNum, sizeof(float));//들어갈때 반대로 값이 들어간다 
	}
	else if (type == ASCII_MODE)
	{
		startNum = (WritebyteLength - 1 - leng);
		strTemp = CovertToHex(WriteData, type);
	}
	strTemp.Replace(" ", "");
	//
	switch (type)
	{
	case ASCII_MODE:
		leng = WritebyteLength;
		break;
	case FLOAT_MODE:
		leng = 4;
		for (i = 0; i < leng; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[3 - i]);// szTemp[3 - x]);
		}
		break;
	case DEC_MODE:
		//
		leng = 1;
		//dec -->hex로 바꾸는 코드
		value = _ttoi(WriteData);
		strTemp.Format("%x ", value);
		//
		
		//strTemp.Format("%s", WriteData);//그대로 쓰는 코드
		break;
	case HEX_MODE:
		strTemp.Format("%s", WriteData);//그대로 쓰는 코드

		break;

	}
	for (int i = 0; i < leng; i++)
	{
		if (type == ASCII_MODE)
		{
				if (i == (leng - 1))
				{
					pData[i] = (unsigned char)_tcstol("00", NULL, 16);
				}
				else if (i >= (startNum))
				{
					//value = (int)(WriteData[i - startNum]);
					pData[i] = (unsigned char)_tcstol(strTemp.Mid((i- startNum) * 2, 2), NULL, 16);
				}
				else
				{
					pData[i] = (unsigned char)_tcstol("00", NULL, 16);
				}
		}
		else
		{
			pData[i] = (unsigned char)_tcstol(strTemp.Mid(i * 2, 2), NULL, 16);//hex코드로 입력했을대기존코드
			
		}
		rtnData[i] = pData[i];
	}
}
#endif
CString CeepromData::EEPROM_Read(unsigned short slaveAddress, int ReadAddress, int ReadbyteLength, int type, int autoRun)
{
	CString rtnStr = _T("");
	CString tempData = _T("");
	unsigned char pData[MAX_PATH];
	int errorCode = 0;
	int i = 0;
	memset(pData, 0x00, sizeof(pData));
	BYTE	m_Str_DataLength = 1;  //(byte)ReadbyteLength;
	Sleep(2);
	for (int j = 0; j < ReadbyteLength; j++)
	{

		//errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)0x52, (unsigned short)ReadAddress + j, 1, pData + j, (unsigned short)m_Str_DataLength);
		errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)slaveAddress, (unsigned short)ReadAddress + j, 1, pData + j, (unsigned short)m_Str_DataLength);

		Sleep(2);
		if (errorCode)
		{
			tempData.Format("Error : %d", errorCode);
			AddLog(tempData, 1, m_nUnit);
			tempData.AppendFormat(" %s", GetErrorStr(errorCode));
			AddLog(tempData, 1, m_nUnit);
			tempData.Format("FALSE");
			return tempData;
		}
	}
	rtnStr.Empty();
	tempData.Empty();
	for (int i = 0; i < ReadbyteLength; i++)
	{
		tempData.AppendFormat("%02X", (char*)pData[i]);
	}
	rtnStr = CovertToChar(tempData, type);

	if (autoRun == false)
	{
		AddLog(rtnStr, 1, m_nUnit);
	}
	return rtnStr;
}
byte CeepromData::EEPROM_Write(CString WriteAddress, CString WriteData , int WritebyteLength , int type, byte* rtnData , bool autoRun)
{
	unsigned char pData[MAX_PATH];
	int errorCode = 0;
	int i = 0;
	int j = 0;
	int leng = WriteData.GetLength();
	int value = 0;
	float fNum = 0.0;
	CString strTemp;
	int startNum = 0;
	unsigned char szTemp[MAX_PATH];
	memset(pData, 0, sizeof(pData));
	memset(szTemp, 0x00, sizeof(szTemp));
	memset(rtnData, 0x00, 32);
	if (!g_clLaonGrabberWrapper[m_nUnit].m_pBoard->IsConnected())
	{
		AddLog("[CCD] Grabber Board 해제 상태", 1, m_nUnit);
		return (byte)errorCode;
	}
	if (type == DEC_MODE)
	{
		strTemp = WriteData;
	}
	else if (type == FLOAT_MODE)
	{
		fNum = (_ttof(WriteData));
		memcpy(szTemp, &fNum, sizeof(float));//들어갈때 반대로 값이 들어간다
	}
	else if (type == ASCII_MODE)
	{
		strTemp = CovertToHex(WriteData, type);
	}
	strTemp.Replace(" ", "");
	//
	switch (type)
	{
	case ASCII_MODE:
		/*for (i = 0; i < leng; i++)
		{
			value = (int)(WriteData[i]);
			strTemp.AppendFormat("%x ", value);
		}*/
		
		break;
	case FLOAT_MODE:
		leng = 4;
		for (i = 0; i < leng; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[3 - i]);// szTemp[3 - x]);
		}
		break;
	case DEC_MODE:
		//
		leng = 1;
		//dec -->hex로 바꾸는 코드
		//value = _ttoi(WriteData);
		//strTemp.Format("%x ", value);
		//
		
		strTemp.Format("%s", WriteData);//그대로 쓰는 코드
		break;
	}
	for (int i = 0; i < leng; i++)
	{
		pData[i] = (unsigned char)_tcstol(strTemp.Mid(i * 2, 2), NULL, 16);//hex코드로 입력했을대기존코드
		
	}
	memcpy(rtnData, pData, leng);
	return (byte)errorCode;



	/*unsigned int nSlaveAddress;
	unsigned int nAddress;
	BYTE	m_Str_DataLength = (byte)WritebyteLength;
	sscanf_s(WriteAddress.GetBuffer(0), "%x", &nAddress);
	Sleep(10);
	errorCode = theApp.MainDlg->m_pBoard->WriteI2CBurst((unsigned short)0x50, (unsigned short)nAddress, 2, pData, (unsigned short)m_Str_DataLength);
	Sleep(1);
	if (autoRun == true)
	{
		return (byte)errorCode;
	}
	
	CString logStr = _T("");
	if (errorCode)
	{
		logStr.Format("Error : %d", errorCode);
		theApp.MainDlg->putListLog(logStr);
		logStr.AppendFormat(" %s", GetErrorStr(errorCode));
		theApp.MainDlg->putListLog(logStr);
	}
	else
	{
		theApp.MainDlg->putListLog("wright ok!");
	}*/
	return (byte)errorCode;
}

CString CeepromData::CovertToHex(CString data, int type)
{
	CString rtnValue;
	CString temporary;
	unsigned char szTemp[1024];
	int value = 0;
	float fNum = 0.0;
	temporary.Empty();
	rtnValue.Empty();
	data.Replace(" ", "");
	memset(szTemp, 0x00, 1024);
	int len = 0;

	if (type == FLOAT_MODE)
	{
		fNum = (_ttof(data));
		memcpy(szTemp, &fNum, sizeof(float));
		len = 4;
	}
	else if (type == ASCII_MODE)
	{
		len = data.GetLength();
	}
	else if (type == DEC_MODE)
	{
		len = 1;
	}
	else if (type == HEX_MODE)
	{
		len = 1;// data.GetLength();
	}
	for (int x = 0; x < len; x++)
	{
		if (type == FLOAT_MODE)
		{
			temporary.Format("%02X", szTemp[3 - x]);// szTemp[3 - x]);
													//Hex 로 변경
		}
		else if (type == ASCII_MODE)
		{
			value = (int)(data[x]);
			temporary.Format("%X", value);//temporary.Format("%02X", value);기존
										  //temporary.Format("%d", value);//
										  //ASCII : 입력된 String 을 ASCII Code 로 변경
		}
		else if (type == DEC_MODE)
		{
			value = _ttoi(data);
			temporary.Format("%X", value);
		}
		else if (type == HEX_MODE)
		{
			value = _ttoi(data);
			temporary.Format("%X", value);
		}
		rtnValue += temporary;
	}
	return rtnValue;
}
CString CeepromData::CovertToChar(CString data, int mode)
{
	CString rtnValue;
	CString temporary;
	temporary.Empty();
	rtnValue.Empty();
	data.Replace(" ", "");
	int len = (int)data.GetLength();
	byte value;
	UINT32 AAA;
	float fNum = 0.0;
	if (mode == ASCII_MODE)
	{
		for (int x = 0; x < len; x++)
		{
			value = (byte)_tcstol(data.Mid(x * 2, 2), NULL, 16);
			temporary.Format("%c", value);
			rtnValue += temporary;
		}
	}
	else if (mode == FLOAT_MODE)
	{
		sscanf_s(data.GetBuffer(0), "%X", &AAA);
		fNum = *((float*)&AAA);
		rtnValue.Format("%f", fNum);
	}
	else if (mode == DEC_MODE)
	{
		value = (byte)_tcstol(data.Mid(0, 2), NULL, 16);
		temporary.Format("%d", value);
		//temporary.Format("%X", value); 기존코드
		rtnValue += temporary;
	}
	else if (mode == HEX_MODE)
	{
		len = len / 2;
		for (int x = 0; x < len; x++)
		{
			value = (byte)_tcstol(data.Mid(x * 2, 2), NULL, 16);
			temporary.Format("%02X", value);
			rtnValue += temporary;
		}
	}

	return rtnValue;
}

bool CeepromData::CompareHexData(CString firstData, CString secondData, int type)
{
	CString rtnValue = _T("");
	CString strTemp = _T("");

	unsigned char firstTemp[MAX_PATH];
	unsigned char secondTemp[MAX_PATH];
	int i = 0;
	int j = 0;
	float fNum = 0.0;
	int sTemp = 0;
	int result = -1;
	int dataLength = 0;
	memset(firstTemp, 0x00, sizeof(firstTemp));
	memset(secondTemp, 0x00, sizeof(secondTemp));

	switch (type)
	{
	case ASCII_MODE://ascii
		dataLength = firstData.GetLength();
		if(dataLength >secondData.GetLength())
		{
			dataLength = secondData.GetLength();
		}
		for (i = 0; i < dataLength; i++)
		{
			sTemp = (int)(firstData[i]);
			strTemp.Format("%x ", sTemp);//%x = hex
			firstTemp[i] = (unsigned char)_tcstol(strTemp.Mid(0, 2), NULL, 16);
			//
			sTemp = (int)(secondData[i]);
			strTemp.Format("%x ", sTemp);//%x = hex
			secondTemp[i] = (unsigned char)_tcstol(strTemp.Mid(0, 2), NULL, 16);
		}
		result = _memicmp(firstTemp, secondTemp, dataLength);
		break;

	case FLOAT_MODE://float
		fNum = (_ttof(firstData));
		memcpy(firstTemp, &fNum, sizeof(float));
		fNum = (_ttof(secondData));
		memcpy(secondTemp, &fNum, sizeof(float));
		result = _memicmp(firstTemp, secondTemp, sizeof(float));
		break;
	case DEC_MODE://hex
		firstTemp[i] = (unsigned char)_tcstol(firstData.Mid(0, 2), NULL, 16);
		secondTemp[i] = (unsigned char)_tcstol(secondData.Mid(0, 2), NULL, 16);
		result = _memicmp(firstTemp, secondTemp, sizeof(float));
		break;
	case HEX_MODE:
		for (i = 0; i < 4; i++)
		{
			firstTemp[i] = (unsigned char)_tcstol(firstData.Mid(0, 2), NULL, 16);
			secondTemp[i] = (unsigned char)_tcstol(secondData.Mid(0, 2), NULL, 16);
		}

		result = _memicmp(firstTemp, secondTemp, sizeof(float));
		break;
	}

	if (result == 0)
	{
		return true;
	}
	return false;

}





CString CeepromData::GetErrorStr(int errorCode)
{
	CString retStr;
	switch (errorCode)
	{
	case ERR_BOARD_GET_LIST:
		retStr = "ERR_BOARD_GET_LIST";
		break;
	case ERR_BOARD_NO_DEVICE:
		retStr = "ERR_BOARD_NO_DEVICE";
		break;
	case ERR_BOARD_OPEN:
		retStr = "ERR_BOARD_OPEN";
		break;
	case ERR_BOARD_INIT:
		retStr = "ERR_BOARD_INIT";
		break;
	case ERR_BOARD_SET_POWER_5_12:
		retStr = "ERR_BOARD_SET_POWER_5_12";
		break;
	case ERR_BOARD_GRAB_START:
		retStr = "ERR_BOARD_GRAB_START";
		break;
	case ERR_BOARD_I2C_WRITE:
		retStr = "ERR_BOARD_I2C_WRITE";
		break;
	case ERR_BOARD_I2C_READ:
		retStr = "ERR_BOARD_I2C_READ";
		break;
	case ERR_BOARD_BOOT_CAMERA:
		retStr = "ERR_BOARD_BOOT_CAMERA";
		break;
	case ERR_BOARD_CLOSE:
		retStr = "ERR_BOARD_CLOSE";
		break;
	case ERR_BOARD_LOAD_MODEL:
		retStr = "ERR_BOARD_LOAD_MODEL";
		break;
	default:
		break;
	}
	return retStr;
}

