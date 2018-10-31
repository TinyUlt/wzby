#include "Global.h"
#include "HPModel.h"
#include "MessageModel.h"
#include "BulletModel.h"
#include "ItemModel.h"
#include "MonsterHelper.h"
#include "LogSys.h"
HPModel::HPModel()
{
}


HPModel::~HPModel()
{
}

void HPModel::Bind(ItemModel* host, MessageModel* message) {
	this->Host = host;
	this->Message = message;
}
void HPModel::Init(bool enable, int value) {
	Enable = enable;
	Value.Value = value;
}
void HPModel::Update(int frame){
	NowFrame = frame;
}
bool HPModel::Hurt(ItemModel* attacker, BulletModel* bullet) {
	if (!Enable) {
		return true;
	}
	//if (!Value.TrySub(bullet->Value)) {
	//	//ËÀÍö

	//	Value.Value = 0;
	//	Message->SendHit(
	//		g_global.GetExecuteDelayFrameForServer(NowFrame),
	//		attacker->Id,
	//		Host->Id,
	//		bullet->SkillId,
	//		attacker->Score.Value,
	//		Value.Value
	//	);


	//	int exp = 0;
	//	g_global.monsterHelper->TryGetExp(Host->Type, exp);

	//	attacker->LV.AddExp(exp);

	//	Message->SendKillItem(
	//		attacker->LV.Exp,
	//		g_global.GetExecuteDelayFrameForServer(NowFrame),
	//		Host->Id,
	//		attacker->Id
	//	);
	//	Host->Enable = false;
	//	g_global.logSys->LogInWindow("ËÀÍö");
	//	return false;
	//}
	//else {
	//	//¿ÛÑª

	//	Message->SendHit(
	//		g_global.GetExecuteDelayFrameForServer(NowFrame),
	//		attacker->Id,
	//		Host->Id,
	//		bullet->SkillId,
	//		attacker->Score.Value,
	//		Value.Value
	//	);

	//
	//	return true;
	//}
}
bool HPModel::IsDead() {
	return false;
}