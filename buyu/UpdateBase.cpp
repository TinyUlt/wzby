#include "UpdateBase.h"



UpdateBase::UpdateBase()
{
	Interval = 0;
	PrvTime = 0;
}


UpdateBase::~UpdateBase()
{
}
void UpdateBase::SetInterval(int interval) {
	Interval = interval;
	PrvTime = 0;
}
bool UpdateBase::Update(LONGLONG duration) {

	if (duration - PrvTime >= Interval) {
		PrvTime = duration;
		return true;
	}
	return false;
}
