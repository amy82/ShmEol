#pragma once

#include "utility\basethread\basethread.h"

class CVisionGrabThread :
	public CBaseThread
{
public:
	CVisionGrabThread(void);
	~CVisionGrabThread(void);

	void SetUnit(int nUnit) { m_nUnit = nUnit; }

protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

private:
	int m_nUnit;
};

