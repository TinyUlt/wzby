#include "Global.h"
#include "DMGSkillModel.h"
#include "ItemModel.h"
#include "BulletModel.h"
#include "LogSys.h"
#include "ScorePoolHelper.h"
#include "MonsterHelper.h"
#include "MessageModel.h"


DMGSkillModel::DMGSkillModel()
{
}


DMGSkillModel::~DMGSkillModel()
{
}
void DMGSkillModel::Bind(BulletModel* host, MessageModel* message) {
	Host = host;
	Message = message;
}
void DMGSkillModel::Init(bool enable, int value) {
	Enable = enable;
	Value = value;
}
void DMGSkillModel::Update(int frame) {
	NowFrame = frame;
}
bool DMGSkillModel::Hit(ItemModel* attacker, ItemModel* victim) {
	if (!Enable) {
		return true;
	}
	if (!victim->HP.TrySub(Value)) {
		//ËÀÍö

		victim->HP.Value = 0;
		Message->SendHit(
			g_global.GetExecuteDelayFrameForServer(NowFrame),
			attacker->Id,
			victim->Id,
			Host->SkillId,
			attacker->Score.GetScore(),
			victim->HP.Value
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
		Host->Enable = false;
		g_global.logSys->LogInWindow("ËÀÍö");
		return false;
	}
	else {
		//¿ÛÑª

		Message->SendHit(
			g_global.GetExecuteDelayFrameForServer(NowFrame),
			attacker->Id,
			victim->Id,
			Host->SkillId,
			attacker->Score.GetScore(),
			victim->HP.Value
		);


		return true;
	}
}