#pragma once
#include "typedefine.h"
class ValueModel
{
public:
	ValueModel();
	~ValueModel();

	void Init(LONGLONG score);
	//�ɹ�����true
	bool TrySub(LONGLONG score);
	void Add(LONGLONG score);
	
	LONGLONG Value;
	LONGLONG MaxValue;
};

