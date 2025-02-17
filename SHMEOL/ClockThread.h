#pragma once

#include "Utility\BaseThread\BaseThread.h"

class CClockThread :
	public CBaseThread
{
public:
	CClockThread(void);
	~CClockThread(void);

protected:
	virtual void ThreadConstructor();
	virtual void TheradDestructor();
	virtual void ThreadCallBack();

private:
	void ShowCurrDate();
	void ShowCurrTime();

private:
	DWORD m_dwTickCount;
};

