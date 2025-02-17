#pragma once

#include "Utility\BaseThread\BaseThread.h"
#include "Utility\Serial\Serial.h"

class CSerialThread :
	public CBaseThread
{
public:
	CSerialThread();
	~CSerialThread();

public:
	bool OpenKeyenceSerial(int nUnit, int nPort, int nBaudRate);
	void CloseKeyenceSerial(int nUnit);
	void RecvKeyenceSerial(int nUnit);
	void ParseKeyenceSerial(int nUnit, unsigned char* pRecvBuff, int nRecvLen);
	void ProcessKeyencePacket(int nUnit, unsigned char* pRecvBuff, int nRecvLen);
	bool SendKeyenceMeasureSet(int nUnit);
	bool SendKeyLockSet(int nUnit, bool bLock);

	bool OpenLightSerial(int nUnit, int nPort, int nBaudRate);
	void CloseLightSerial(int nUnit);
	void RecvLightSerial(int nUnit);
	void ParseLightSerial(int nUnit, unsigned char* pRecvBuff, int nRecvLen);
	bool SendLightOnOffSet(int nUnit, unsigned char cCmd, int nCh, bool bOn = true, bool bAllCh = false);
	bool SendLightSet(int nUnit, unsigned char cCmd, int nCh, int nChVal, bool bAllCh = false);
	
	//¹ÙÄÚµå

	bool OpenBcrSerial(int nUnit, int nPort, int nBaudRate);
	void CloseBcrSerial(int nUnit);
	void RecvBcrSerial(int nUnit);
	bool TransmitBcrSerial(int nUnit, CString sBcrData);
	void ParseBcrSerial(int nUnit, unsigned char* pRecvBuff, int nRecvLen);

	//UV
	bool OpenUvSerial(int nUnit, int nPort, int nBaudRate);
	void CloseUvSerial(int nUnit);
	bool UV_Shutter_Open(int nUnit);
	bool UV_Shutter_Close(int nUnit);
	bool UV_Shutter_PowerSet(int nUnit, int value);
protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

private:
	unsigned char m_sKeyenceBuff[MAX_UNIT_COUNT][SIZE_OF_1K];
	int m_nKeyencePacketBuffPosi[MAX_UNIT_COUNT];
	bool m_bKeyenceStxState[MAX_UNIT_COUNT];

	unsigned char m_sLightPacketBuff[MAX_UNIT_COUNT][SIZE_OF_1K];
	int m_nLightBuffPosi[MAX_UNIT_COUNT];
	bool m_bLightStxState[MAX_UNIT_COUNT];

	unsigned char m_sLBcrPacketBuff[MAX_UNIT_COUNT][SIZE_OF_1K];
	int m_nBcrBuffPosi[MAX_UNIT_COUNT];
	bool m_bBcrStxState[MAX_UNIT_COUNT];

private:
	CSerial m_clSerialKeyence[MAX_UNIT_COUNT];
	bool m_bKeyenceOpen[MAX_UNIT_COUNT];
	
	CSerial m_clSerialLight[MAX_UNIT_COUNT];
	bool m_bLightOpen[MAX_UNIT_COUNT];

	CSerial m_clSerialBcr[MAX_UNIT_COUNT];
	bool m_bBcrOpen[MAX_UNIT_COUNT];

	CSerial m_clSerialUv[MAX_UNIT_COUNT];
	bool m_bUvOpen[MAX_UNIT_COUNT];


};

