#pragma once

#include "utility\basethread\basethread.h"
class CLensAxisThread :
	public CBaseThread
{
public:
	CLensAxisThread(void);
	~CLensAxisThread(void);
	
	void SetUnit(int nUnit) { m_nUnit = nUnit; }
	int m_nUnit;
	bool bLensWorkRun;
protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

private:
	int m_nLensStartStep;
	int m_nLensEndStep;
	int m_nLensCurrentStep;

	int LensMode;			//1 = CCD ¿µ»ó Start


	
	
public:
	int Lens_Laser_Run(int nStep);
	//
	void LensThreadrun(int Mode);
};

