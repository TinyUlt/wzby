#include "Global.h"
#include "TimerModel.h"



TimerModel::TimerModel()
{
	Interval = 0;
	PrvTime = 0;
	active = false;
}


TimerModel::~TimerModel()
{
}
void TimerModel::SetInterval(int interval, int prvTime, int maxTime, int needWaitTime) {
	Interval = (LONGLONG)interval;
	PrvTime = prvTime;
	MaxTime = maxTime;
	ExecuteTime = 0;
	UntilWaitTime = 0;
	NeedWaitTime = needWaitTime;
	active = true;
}
bool TimerModel::Update(LONGLONG duration) {
	if (!active) {
		return false;
	}
	if (UntilWaitTime == 0) {
		UntilWaitTime = duration + NeedWaitTime;
	}
	if (UntilWaitTime > duration) {
		return false;
	}

	if (MaxTime != -1) {
		if (ExecuteTime >= MaxTime) {
			return false;
		}
	}
	if (PrvTime == 0) {
		PrvTime = duration;
	}
	if (duration - PrvTime >= Interval) {
		PrvTime = duration;
		ExecuteTime++;
		return true;
	}
	return false;
}
