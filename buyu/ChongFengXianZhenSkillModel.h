#pragma once
#include "SkillBaseModel.h"
class ChongFengXianZhenSkillModel : public SkillBaseModel
{
public:
	ChongFengXianZhenSkillModel();
	~ChongFengXianZhenSkillModel();

	void Init(bool enable, int coolingTime, float width, float length);
	void Trigger(S_Attack* attack);
	void Back();

	float Width;
	float Length;
	float MaxLengthSqr;
};

