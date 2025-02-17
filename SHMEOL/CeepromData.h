#pragma once
class CeepromData
{

public:
	CeepromData();
	~CeepromData();
private:
	int m_nUnit;
public:
	void SetUnit(int nUnit);
	
	bool EEPROM_TotalRead_Type(unsigned short slaveAddress, unsigned int StartAddress, unsigned int EndAddress, byte* TotalData, int ReadLength);
	CString EEPROM_Read(unsigned short slaveAddress, int ReadAddress, int ReadbyteLength, int type, int autoRun);

	void HexToString(byte* rtnData, int Length, TCHAR* strData, int nType);
	void StringToHex(string title, CString data, byte* rtnData, int index);//index 0 = min , 1 = max

	byte EEPROM_Write(CString WriteAddress, CString Data, int byteLength, int type , byte* rtnData, bool autoRun);
	void eeprom_Data_Sum(CString WriteData, int WritebyteLength, int type, byte* rtnData, bool autoRun);
	//
	CString GetErrorStr(int errorCode);
	CString CovertToHex(CString data, int type);
	CString CovertToChar(CString data, int type);
	bool CompareHexData(CString firstData, CString secondData, int type);
public:
	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	//EEPROM LOAD DATA
	//
	CString BARCODE_ID;
	CString UPDDATE_BY;
	CString UPDATE_DATE;
	CString UPDATE_DATE_DETAIL[6];
	CString MAP_VER;
	CString SMT_FLAG;
	CString CAM_LOCATION;
	//
	CString MANUFACTURER_NAME;
	CString MANUFACTURER_PN;
	CString PLACE_OF_MANUFACTURE;
	CString MANUFACTURE_ASSEMBLY_LINE;
	CString LENS_NAME;
	CString SENSOR_NAME;
	CString SERIALIZER_NAME;
	
	CString CFA;
	CString LENGTH_FOCUS;
	CString IMGR_INPUT_CLK_FREQ;
	CString DISTORTION_MODEL;
	//
	//AA
	CString OC_X, OC_Y;
	CString RC2800K, BC2800K, CRCB2800K;
	CString RC6500K, BC6500K, CRCB6500K;
	CString RI_RED[10][10],  RICLEAR_R[10][10], RICLEAR_B[10][10] , RI_BLUE[10][10];
	CString MTF_0F;
	CString MTF_4F_A, MTF_4F_B, MTF_4F_C, MTF_4F_D;
	CString MTF_8F_A, MTF_8F_B, MTF_8F_C, MTF_8F_D;
	//
	//CAL
	CString DISTORTION_CX, DISTORTION_CY;
	CString DIST_K1, DIST_K2, DIST_K3, DIST_K4, DIST_K5, DIST_K6;
	CString DIST_P1, DIST_P2;
	CString AVR_D, MAX_D;
	CString DIS_FOCAL_LENGTH;
	CString CAM_ROLL, CAM_PITCH, CAM_YAW;
	//
	//

	
	//
	////--------------------------------------------------------------------------------------------------------------------------------

};




class CVerifyData
{
public:
	TCHAR	vMinData[MES_VERIFY_SPEC_COUNT][SIZE_OF_100BYTE];
	//byte	vMinHexData[MES_VERIFY_SPEC_COUNT][SIZE_OF_100BYTE];		//eeprom write 할 때 index 주의해야된다 
	

	TCHAR	vMaxData[MES_VERIFY_SPEC_COUNT][SIZE_OF_100BYTE];
	//byte	vMaxHexData[MES_VERIFY_SPEC_COUNT][SIZE_OF_100BYTE];
	
	CVerifyData()
	{
		Reset();
	}
	void Reset()
	{
		for (int i = 0; i < MES_VERIFY_SPEC_COUNT; i++)
		{
			_stprintf_s(vMinData[i], SIZE_OF_100BYTE, _T(""));
			_stprintf_s(vMaxData[i], SIZE_OF_100BYTE, _T(""));
			//memset(vMinHexData[i], 0x00, sizeof(vMinHexData[i]));
			//memset(vMaxHexData[i], 0x00, sizeof(vMaxHexData[i]));
		}
	}
};
