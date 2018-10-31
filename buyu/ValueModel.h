#pragma once
#include "typedefine.h"
class ValueModel
{
public:
	ValueModel();
	~ValueModel();

	void Init(LONGLONG score);
	//³É¹¦·µ»Øtrue
	bool TrySub(LONGLONG score);
	void Add(LONGLONG score);
	
	LONGLONG Value;
	LONGLONG MaxValue;
};

