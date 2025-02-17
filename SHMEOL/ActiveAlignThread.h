#pragma once

#include "utility\basethread\basethread.h"
#include "PcbProcess.h"
#include "LensProcess.h"

class CActiveAlignThread :
	public CBaseThread
{
public:
	CActiveAlignThread(void);
	~CActiveAlignThread(void);
	
protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

public:
	void SetUnit(int nUnit);

public:
	CPcbProcess m_clPcbProcess;
	CLensProcess m_clLensProcess;

	DWORD m_dwTickCount[2];
	int m_nUnit;
	int m_nStep;
};

