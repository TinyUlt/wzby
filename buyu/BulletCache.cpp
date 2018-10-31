#include "Global.h"
#include "BulletCache.h"
#include "SkillHelper.h"


BulletCache::BulletCache()
{
	Id = 0;
}

BulletCache::~BulletCache()
{
}
void BulletCache::Bind(MessageModel* message) {
	Message = message;
}
void BulletCache::Update(int frame) {
	NowFrame = frame;
	for (auto iter : Dic) {
		auto value = iter.second;
		if (!value->Update(frame)) {
			TobeDelete.push_back(iter.first);
		}
	}

	for (auto& key : TobeDelete) {
		EraseDic(key);
	}
	TobeDelete.clear();
}
BulletModel* BulletCache::CreateBullet(
	ItemModel* creator, 
	ItemModel* victim, 
	int skillId, 
	bool multipleEnable,
	int multipleValue,
	bool dmgEnable,
	int dmgValue) {
	
	BulletModel* bullet = g_global.skillHelper->BulletPool.acquire_object();
	Proto_Skill* skillConfig = NULL;
	Proto_SkillEffect* skillEffectConfig = NULL;
	if (g_global.skillHelper->TryGetSkillConfig(skillId, &skillConfig)&&
		g_global.skillHelper->TryGetSkillEffectConfig(skillConfig->effectid(), &skillEffectConfig)) {
		
		bullet->Bind(creator, victim, Message);
		bullet->Init(
			multipleEnable,
			multipleValue,
			dmgEnable,
			dmgValue,
			skillConfig->type(), 
			skillId, 
			(int) (skillConfig->intonatetime() * 60),
			float(skillEffectConfig->flyspeed() / 60.0), 
			NowFrame
		);
		Dic[Id] = bullet;
		Id++;

		return bullet;
	}
	return NULL;
}
void BulletCache::EraseDic(int id) {
	if (this->Dic.count(id) == 0) {
		return;
	}
	g_global.skillHelper->BulletPool.release_object(this->Dic[id]);
	Dic.erase(id);
}
void BulletCache::EraseDic(BulletModel* value) {

	EraseDic(value->Id);
}
bool BulletCache::TryGetBulletsPoint(google::protobuf::RepeatedPtrField<TestPoint>* list) {

	for (auto& bullet : Dic) {
		auto p = list->Add();
		p->set_id(bullet.second->Id);
		bullet.second->Pos.Position.assignVec3(p->mutable_point());
	}
	return true;
}
