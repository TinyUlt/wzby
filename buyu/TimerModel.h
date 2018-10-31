#pragma once
#include "typedefine.h"
class TimerModel
{
public:
	TimerModel();
	virtual ~TimerModel();

	void SetInterval(int interval, int prvTime = 0, int maxTime = -1, int needWaitTime = 0);
	bool Update(LONGLONG duration);
	
private:
	bool active;
	LONGLONG Interval;
	LONGLONG PrvTime;
	int MaxTime;
	int ExecuteTime;
	int UntilWaitTime;
	int NeedWaitTime;
};

