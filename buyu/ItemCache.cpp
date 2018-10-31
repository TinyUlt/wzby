#include "Global.h"
#include "ItemCache.h"
#include "ItemModel.h"
#include "PathHelper.h"
#include "MonsterHelper.h"
#include "LogSys.h"
#include "SendModel.h"
#include "BulletCache.h"
#include "SkillHelper.h"
#include "MessageHelper.h"
#include "MessageModel.h"
#include "SendModel.h"
#include "SpawnCache.h"
#include "MoveModel.h"

//#include "MessageModel.h"

ItemCache::ItemCache()
{
	Id = 100;
	NowFrame = 0;
}


ItemCache::~ItemCache()
{
}
void ItemCache::Bind(BulletCache* bulletManager, SpawnCache* spawnManager, MessageModel* message,  SendModel* send) {
	Message = message;
	Send = send;
	BulletManager = bulletManager;
	SpawnManager = spawnManager;
}

void ItemCache::Update(int frame) {
	NowFrame = frame;

	//遍历活着的怪物
	for (auto& iter : this->Dic) {
		auto key = iter.first;
		auto value = iter.second;
		if (value->Enable) {
			if (!value->Update(frame)) {

			}
		}
	}
}
void ItemCache::EraseDic(int id) {
	if (this->Dic.count(id) == 0) {
		return;
	}
	SpawnManager->Dic[Dic[id]->SpawnId].SubCount();
	this->Dic[id]->Back();
	g_global.monsterHelper->RebackMonster(this->Dic[id]);
	Dic.erase(id);

	
}
void ItemCache::EraseDic(ItemModel* value) {
	
	EraseDic(value->Id);
}
void ItemCache::SetId(S_SpawnItem& pack) {
	pack.set_itemid(Id++);
}

void ItemCache::Spawn( SpawnMessage* msg) {

	
	ItemModel* item = NULL;
	if (!g_global.monsterHelper->TryGetMonster(&item)) {
		return;
	}

	item->Bind(this, BulletManager, Message, Send);
	item->Init(msg);

	Dic[item->GetId()] = item;


}
bool ItemCache::TryGetMonsterById(int id, ItemModel** monster) {

	if (Dic.count(id) == 0) {
		return false;
	}

	*monster = Dic[id];
	return true;
}
void ItemCache::SetMul(int operatorId, int mul) {

	ItemModel* item = NULL;
	if (!TryGetMonsterById(operatorId, &item)) {
		return;
	}

	item->Mul.Set(mul);

}
bool ItemCache::TryGetMonstersPoint(google::protobuf::RepeatedPtrField<TestPoint>* list) {
	for (auto iter : this->Dic) {
		auto key = iter.first;
		auto value = iter.second;

		auto p = list->Add();
		p->set_id(key);
		value->Pos.Position.assignVec3(p->mutable_point());
	}

	return list->size() == 0 ? false : true;
}
bool ItemCache::TryGetAllMonster(vector<S_SpawnItem*>& list) {

	for (auto& iter : this->Dic) {
		auto key = iter.first;
		auto value = iter.second;
		list.push_back(value->GetPack());
	}
	
	return list.empty()?false:true;
}
bool ItemCache::TryGetItemByDistance(vector<ItemModel*>& list, Vector3& pos, float distance) {

	return TryGetItemByDistanceSqr(list, pos, distance * distance);
	
}
bool ItemCache::TryGetItemByDistanceSqr(vector<ItemModel*>& list, Vector3& pos, float distanceSqr) {
	for (auto& iter : this->Dic) {
		//auto key = iter.first;
		auto value = iter.second;

		auto& monsterPos = value->Pos.Position;
		if ((pos.x - monsterPos.x)*(pos.x - monsterPos.x) + (pos.z - monsterPos.z)*(pos.z - monsterPos.z) < distanceSqr) {
			list.push_back(value);
		}
	}
	return list.empty() ? false : true;
}
bool ItemCache::TryGetItemIdByDistance(vector<int>& list, Vector3& pos, float distance) {


	for (auto& iter : this->Dic) {
		//auto key = iter.first;
		auto value = iter.second;

		auto& monsterPos = value->Pos.Position;
		if ((pos.x - monsterPos.x)*(pos.x - monsterPos.x) + (pos.z - monsterPos.z)*(pos.z - monsterPos.z) < distance * distance) {
			list.push_back(value->Id);
		}
	}
	return list.empty() ? false : true;
}
void ItemCache::Freezen(S_Hit* freezen) {

	for (int i = 0; i < freezen->victimlist_size(); i++) {
		int id = freezen->mutable_victimlist(i)->id();
		this->Dic[id]->SetFreezen(freezen);
	}
	
}

int ItemCache::GetMonsterSize() {
	return Dic.size();
}

void ItemCache::SetPath(int id, S_MovePosList* posList) {
	if (Dic.count(id) > 0) {
		Dic[id]->SetPath(posList);
	}
}
//void ItemCache::CalculateAndSetPath(int id, S_MonsterTerminal* data) {
//	if (Dic.count(id) > 0) {
//		Dic[id]->CalculateAndSetPath(data);
//	}
//}
void ItemCache::Attack(int attackId, int skillId, ItemModel* victim) {
	int id = attackId;//attack->attackerid();
	if (Dic.count(id) > 0) {

		auto item = Dic[id];
		bool multipleEnable;
		bool dmgEnable;
		if (item->TeamId == PlayerTeam) {
			multipleEnable = true;
			dmgEnable = false;
		}
		else if (item->TeamId == MonsterTeam) {
			multipleEnable = false;
			dmgEnable = true;
		}
		BulletManager->CreateBullet(
			item, 
			victim, 
			skillId, 
			multipleEnable, 
			item->Mul.Value, 
			dmgEnable, 
			item->DMG.Value);
	}
}
void ItemCache::SetPosition(R_Move* move) {
	int id = move->mutable_data()->moverid();
	if (Dic.count(id) > 0) {
		Dic[id]->Move.SetPosAndVOffset(move);
	}
}
void ItemCache::SkillTrigger(int itemId, S_Attack* attack) {
	if (Dic.count(itemId) == 0) {
		return;
	}
	auto item = Dic[itemId];
	if (item->SkillGroup.count(attack->skillid()) == 0) {
		return;
	}
	auto skill = item->SkillGroup[attack->skillid()];
	skill->Trigger(attack);
}