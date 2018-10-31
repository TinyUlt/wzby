#pragma once
#include "SkillBaseModel.h"
#include <vector>
using namespace std;
class AttackSkillModel : public SkillBaseModel
{
public:
	AttackSkillModel();
	~AttackSkillModel();
	void Init(bool enable, int coolingTime, float rang);
	void Trigger(S_Attack* attack);
	void Back();
};

