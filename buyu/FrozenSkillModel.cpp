#include "Global.h"
#include "FrozenSkillModel.h"

#include "SkillHelper.h"
#include "ItemCache.h"

FrozenSkillModel::FrozenSkillModel()
{
	Type = Skill_Frozen;
}


FrozenSkillModel::~FrozenSkillModel()
{
}

void FrozenSkillModel::Init(bool enable, int coolingTime, float rang) {
	Rang = rang;
	Enable = enable;
	CoolingTime = coolingTime;
}
void FrozenSkillModel::Trigger(S_Attack* attack) {
	ItemList.clear();
	//IdList.clear();

	Vector3& vec3 = Host->Pos.Position;
	ItemManager->TryGetItemByDistance(ItemList, vec3, Rang);
	for (auto item : ItemList) {
		if (item->Frozen.Enable) {
			IdList.push_back(item->Id);
		}
	}

	int frame = g_global.GetExecuteDelayFrameForServer(NowFrame);
	for (auto & m : ItemList) {
		if (m->Frozen.Enable) {
			Message->SendFrozen(Host->Id,frame, frame + 60 * 10, m->Id);
			//ItemManager->Freezen(data);
			
		}
	}
}

void FrozenSkillModel::Back() {
	g_global.skillHelper->FrozenSkillPool.release_object(this);
}