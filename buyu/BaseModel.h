#pragma once
class BaseModel
{
public:
	BaseModel();
	~BaseModel();
	virtual void Update(int frame) = 0;

	//void SetEnable(bool enable);
	//bool GetEnable();

	bool Enable;
};

