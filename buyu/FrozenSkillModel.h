#pragma once
#include "SkillBaseModel.h"

class FrozenSkillModel: public SkillBaseModel
{
public:
	FrozenSkillModel();
	~FrozenSkillModel();
	
	void Init(bool enable,int cd, float rang);
	void Trigger(S_Attack* attack);
	void Back();
	float Rang;
	
	vector<int> IdList;
};

