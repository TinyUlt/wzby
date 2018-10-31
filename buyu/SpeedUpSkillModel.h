#pragma once
#include "SkillBaseModel.h"

class SpeedUpSkillModel: public SkillBaseModel
{
public:
	SpeedUpSkillModel();
	~SpeedUpSkillModel();
	void Init(bool enable, int cd);
	void Trigger(S_Attack* attack);
	void Back();
};

