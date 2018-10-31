#pragma once
#include "SkillBaseModel.h"


class PoFuChenZhouSkillModel: public SkillBaseModel
{
public:
	PoFuChenZhouSkillModel();
	~PoFuChenZhouSkillModel();

	void Init(bool enable, int coolingTime, float rang);
	void Trigger(S_Attack* attack);
	void Back();
	float Rang;
	
};

