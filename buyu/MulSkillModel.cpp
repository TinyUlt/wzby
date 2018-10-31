#include "Global.h"
#include "MulSkillModel.h"
#include "ItemModel.h"
#include "BulletModel.h"

#include "ScorePoolHelper.h"
#include "MonsterHelper.h"
#include "MessageModel.h"
MulSkillModel::MulSkillModel()
{
}


MulSkillModel::~MulSkillModel()
{
}

void MulSkillModel::Bind(BulletModel* host, MessageModel* message) {
	Host = host;
	Message = message;
}
void MulSkillModel::Init(bool enable, LONGLONG value) {
	Enable = enable;
	Value = value;
}
void MulSkillModel::Update(int frame) {
	NowFrame = frame;
}
bool MulSkillModel::Hit(ItemModel* attacker, ItemModel* victim) {
	if (!Enable) {
		return true;
	}
	if (!attacker->Score.TrySubScore(Value)) {
		//钱不够
		return true;
	}
	LONGLONG score = 0;

	if (g_global.scorePoolHelper->TryGetScore(Value, score)) {
		//可以获得分数

		attacker->Score.AddScore(score);
		Message->SendHit(
			g_global.GetExecuteDelayFrameForServer(NowFrame),
			attacker->Id,
			victim->Id,
			Host->SkillId,
			attacker->Score.GetScore(),
			-1
		);

		int exp = 0;
		g_global.monsterHelper->TryGetExp(victim->Type, exp);

		attacker->LV.AddExp(exp);

		Message->SendKillItem(
			attacker->LV.Exp,
			g_global.GetExecuteDelayFrameForServer(NowFrame),
			victim->Id,
			attacker->Id
		);
		//Message->SendScoreAndExpierence(attacker->Id);
		victim->Enable = false;
		return false;
	}
	else {
		Message->SendHit(
			g_global.GetExecuteDelayFrameForServer(NowFrame),
			attacker->Id,
			victim->Id,
			Host->SkillId,
			attacker->Score.GetScore(),
			-1
		);
	}
	return true;
}