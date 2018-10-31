#include "Global.h"
#include "PoFuChenZhouSkillModel.h"
#include "ItemCache.h"
#include "ItemModel.h"
#include "SkillHelper.h"
PoFuChenZhouSkillModel::PoFuChenZhouSkillModel()
{
	Type = Skill_PoFuChenZhou;
}


PoFuChenZhouSkillModel::~PoFuChenZhouSkillModel()
{
}

void PoFuChenZhouSkillModel::Init(bool enable, int coolingTime, float rang) {
	Rang = rang;
	Enable = enable;
	CoolingTime = coolingTime;
}
void PoFuChenZhouSkillModel::Trigger(S_Attack* attack) {
	ItemList.clear();
	Vector3& vec3 = Host->Pos.Position;
	ItemManager->TryGetItemByDistance(ItemList, vec3, Rang);
	for (auto & m : ItemList) {
		if (m->Id != attack->attackerid()) {
			ItemManager->Attack(attack->attackerid(), attack->skillid(), m);
		}
	}
}
void PoFuChenZhouSkillModel::Back() {
	g_global.skillHelper->PoFuChenZhouSkillPool.release_object(this);
}