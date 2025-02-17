#pragma once
#include "utility\basethread\basethread.h"

class CCcdGrabThread :
	public CBaseThread
{
public:
	CCcdGrabThread(void);
	~CCcdGrabThread(void);

	void UpdateGrabStartTime();
    bool MIUCheck_process();
	void SetUnit(int nUnit){ m_nUnit = nUnit; }

protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

public:	
	DWORD m_dwTickCount;
	DWORD m_dwStartTickCount;
	int m_nFailCount;
	int m_nGrabIndex;

	int m_nCount;
	int m_nUnit;

};

