#include "Global.h"
#include "ValueModel.h"



ValueModel::ValueModel()
{
}


ValueModel::~ValueModel()
{
}
void ValueModel::Init(LONGLONG score) {
	Value = score;
	MaxValue = score;
}
bool ValueModel::TrySub(LONGLONG score) {

	if (Value - score < 0) {
		return false;
	}
	Value -= score;
	return true;
}
void ValueModel::Add( LONGLONG score) {
	Value += score;
	if (MaxValue < Value) {
		Value = MaxValue;
	}
}