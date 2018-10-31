#pragma once
#include <vector>
using namespace std;
class MulModel
{
public:
	MulModel();
	~MulModel();
	void Init(bool enable, vector<int>& list, int nowMul);
	bool Contain(int mul);
	void Set(int mul);
	vector<int> List;
	int Value;
};

