#pragma once

#include "Utility\BaseThread\BaseThread.h"

class CFileThread :
	public CBaseThread
{
public:
	CFileThread(void);
	~CFileThread(void);

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

