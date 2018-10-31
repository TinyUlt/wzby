#include "ScoreModel.h"
#include "ItemModel.h"
#include "MessageModel.h"


ScoreModel::ScoreModel()
{
}


ScoreModel::~ScoreModel()
{
}
void ScoreModel::Bind(ItemModel* host, MessageModel* message) {
	Host = host;
	Message = message;
}
void ScoreModel::Init(LONGLONG value) {
	Value = value;
	WinLoseScore = 0;
}
void ScoreModel::AddScore(LONGLONG score, bool isBankOpreate) {
	this->Value += score;
	if (!isBankOpreate) {

		this->WinLoseScore += score;
	}
}
bool ScoreModel::TrySubScore(LONGLONG score) {
	if (Value - score < 0) {
		return false;
	}
	Value -= score;
	return true;
}
LONGLONG ScoreModel::GetScore() {
	return Value;
}
LONGLONG ScoreModel::GetWinLoseScore() {
	return WinLoseScore;
}