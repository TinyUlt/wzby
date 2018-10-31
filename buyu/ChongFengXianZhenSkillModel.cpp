#include "Global.h"
#include "ItemCache.h"
#include "ItemModel.h"
#include "SkillHelper.h"
#include "ChongFengXianZhenSkillModel.h"



ChongFengXianZhenSkillModel::ChongFengXianZhenSkillModel()
{
	Type = Skill_ChongFengXianZhen;
}


ChongFengXianZhenSkillModel::~ChongFengXianZhenSkillModel()
{
}

void ChongFengXianZhenSkillModel::Init(bool enable, int coolingTime, float width, float length)
{
	Enable = enable;
	CoolingTime = coolingTime;
	Width = width;
	Length = length;
	MaxLengthSqr = width * width + length * length;
}
void ChongFengXianZhenSkillModel::Trigger(S_Attack* attack) {

	ItemList.clear();

	if (!ItemManager->TryGetItemByDistanceSqr(ItemList, Host->Pos.Position, MaxLengthSqr)) {
		return;
	}

	ItemModel* victime = NULL;
	if (!ItemManager->TryGetMonsterById(attack->victimid(), &victime)) {
		return;
	}

	Vector3 line1(*(attack->mutable_direction())); /*= victime->Pos.Position - Host->Pos.Position*/;
	Vector3 farMid = line1 * Length;

	Vector3 n = Vector3::Normalized(Vector3::Cross(farMid, Vector3::up)) * Width;

	Vector3 A = Host->Pos.Position + farMid - n;
	Vector3 D = Host->Pos.Position + farMid + n;
	Vector3 C = Host->Pos.Position + n;
	Vector3 B = Host->Pos.Position - n;


	for (auto item : ItemList) {
		if (item->Id != attack->attackerid()) {
			if (Vector3::PointinQuadrangleEX(A, B, C, D, item->Pos.Position)) {
				ItemManager->Attack(attack->attackerid(), attack->skillid(), item);
			}
		}
	}

	Host->Pos.SetPosition(attack->position(), attack->cellindex());
}
void ChongFengXianZhenSkillModel::Back() {
	g_global.skillHelper->ChongFengXianZhenSkillPool.release_object(this);
}