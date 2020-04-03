#pragma once
#include "CSingleton.h"
#include "CTimer.h"

class CTimeManager :
	public CSingleton<CTimeManager>
{
public:
	CTimeManager();
	~CTimeManager();
public:
	float fDeltaTime;
private:
	map<string, CTimer *> m_Timers;
public:
	CTimer * AddTimer(CRString _Key, CTimer * _pTimer);
	CTimer * FindTimer(CRString _Key);
	void RemoveTimer(CRString _Key);

	float m_fDeltaTime;
	float m_fFPS;
	void Update();
};

#define TIME (*CTimeManager::GetInstance())
#define GetNowTimepoint chrono::system_clock::now()
