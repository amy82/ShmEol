#pragma once

#include "utility\basethread\basethread.h"
class CCustomThread :
	public CBaseThread
{
public:
	CCustomThread(void);
	~CCustomThread(void);
	
	void SetUnit(int nUnit) { m_nUnit = nUnit; }
	int m_nUnit;
protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

private:
	int m_nCustomStartStep;
	int m_nCustomEndStep;
	int m_nCustomCurrentStep;

	int CustomMode;			//1 = CCD ¿µ»ó Start
	bool bCustomWorkRun;
	
	DWORD m_dwCustomTickCount;
public:
	int CCD_Run(int nStep);
	int CCD_Retry_Run(int nStep);
	int TPTest_Run(int nStep);




	void CustomThreadrun(int Mode);
};

