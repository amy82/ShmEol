#pragma once
#include "../../Serial/Serial.h"

class AutoInspDlg;
class COcControl
{
public:
	COcControl();
	~COcControl();

private:
	AutoInspDlg* m_pMainDlg;
public:
	void SetMainDlgPtr(AutoInspDlg* pDlg) { m_pMainDlg = pDlg; }
	void init();
public:
	//백두 조명 컨트롤러
	CSerial LightSerial;
	bool OpenLightSerial(unsigned int nPort, unsigned int nBaudRate);
	bool OpenLightClose();
	bool SendLightONOFF(bool USE);
	bool SendLightChange(int USE);
	bool SendLightValue(int data);
	bool SendLightLxStep(int data);
	bool LxSetDataSave();


	//
	//210724
	bool Send_12CHChannel_Value(int nCh, int data);		//12Ch 컨트롤러용 
	bool Send_12CHLightONOFF(bool Use);		//12Ch 컨트롤러용 
	//
	//----------------------------------------------------------------------------------------
};

