#pragma once
#include "typedefine.h"
class UpdateBase
{
public:
	UpdateBase();
	virtual ~UpdateBase();

	void SetInterval(int interval);
	bool Update(LONGLONG duration);
	
private:
	int Interval;
	int PrvTime;
};

