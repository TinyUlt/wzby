#include "MulModel.h"



MulModel::MulModel()
{
}


MulModel::~MulModel()
{
}

void MulModel::Init(bool enable, vector<int>& list, int nowMul) {
	List = list;
	Value = nowMul;
}
void MulModel::Set(int mul) {
	if (Contain(mul)) {
		Value = mul;
	}
}
bool MulModel::Contain(int mul) {
	for (auto m : List) {
		if (mul == m) {
			
			return true;
		}
	}
	return false;
}