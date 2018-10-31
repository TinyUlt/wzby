#pragma once
#include "SkillBaseModel.h"
class HealSkillModel : public SkillBaseModel
{
public:
	HealSkillModel();
	~HealSkillModel();

	void Init(bool enable, int cd, int damage);
	void Trigger(S_Attack* attack);
	void Back();

	int Damage;
	
};

