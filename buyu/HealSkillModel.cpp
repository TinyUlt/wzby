#include "Global.h"
#include "HealSkillModel.h"
#include "ItemCache.h"
#include "ItemModel.h"
#include "SkillHelper.h"


HealSkillModel::HealSkillModel()
{
	Type = Skill_Heal;
}


HealSkillModel::~HealSkillModel()
{
}
void HealSkillModel::Init(bool enable, int cd, int damage) {
	Enable = enable;
	CoolingTime = cd;
	Damage = damage;
}
void HealSkillModel::Trigger(S_Attack* attack) {
	ItemList.clear();
	ItemList.push_back(Host);
	Host->HP.Add(Damage);
	Message->SendHeal(Host->Id, g_global.GetExecuteDelayFrameForServer(NowFrame), ItemList);
}
void HealSkillModel::Back() {
	g_global.skillHelper->HealSkilllPool.release_object(this);
}