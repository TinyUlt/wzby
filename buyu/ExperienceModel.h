#pragma once
class ExperienceModel
{
public:
	ExperienceModel();
	~ExperienceModel();

	void Init(bool enable, int value);
	void Update(int frame);
	void Bind();

	bool Enable;
	int Value;
};

