#pragma once

#include "utility\basethread\basethread.h"

class CMonitorThread :
	public CBaseThread
{
public:
	CMonitorThread(void);
	~CMonitorThread(void);

protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

private:
	DWORD m_dwTickCount;
	bool m_bPrevOrgFlag[MAX_UNIT_COUNT];


	int m_bPrevDoorState;
	bool m_bPrevArea;
	bool m_bPrevVacuumState;
	bool m_bLampFlick;
	int m_nPortNo;
	int iSlaveNo;
	unsigned long uLatch;
public:
	void CheckDioState();

	void CheckAutoRunState();
	void CheckCurtainState();
	void CheckDoorBbState();

	void CheckPcbVacuumBbState();
};

