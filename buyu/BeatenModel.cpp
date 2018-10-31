#include "Global.h"
#include "BeatenModel.h"
#include "ItemModel.h"
#include "FollowModel.h"
#include "AttackModel.h"
#include "MonsterHelper.h"
#include "BulletModel.h"
#include "ScorePoolHelper.h"
#include "MessageHelper.h"
#include "MessageModel.h"
#include "LogSys.h"
BeatenModel::BeatenModel()
{
	Follow = NULL;
	Attack = NULL;
}


BeatenModel::~BeatenModel()
{
}
void BeatenModel::Init(bool enable) {
	Enable = enable;
}
void BeatenModel::Bind(ItemModel* host, FollowModel* follow, AttackModel* attack, MessageModel* message) {
	Follow = follow;
	Attack = attack;
	Host = host;
	
	Message = message;
}
void BeatenModel::Update(int frame) {
	NowFrame = frame;
	if (!Enable) {
		return;
	}
}
void BeatenModel::Trigger(ItemModel* attacker, BulletModel* bullet) {
	if (!Enable) {
		return;
	}

	//int multiple = 0;
	//if (!g_global.monsterHelper->TryGetMultipleByType(monster->GetType(), multiple)) {
	//	//获取不到倍数
	//	return;
	//}
	int exp = 0;
	Proto_Monster* monster = NULL;
	if (g_global.monsterHelper->TryGetMonsterConfig(Host->Type, &monster)) {
		exp = monster->exp();
	}
	
	if (bullet->Hit(attacker, Host)) {
		return;
	}
	
	/*if (bullet->HurtType == MultipleHurt) {
		if (!Host->Multiple.Hit(attacker, bullet)) {
			return;
		}
		
	}else if(bullet->HurtType == HPHurt){*/
		//if (!Host->HP.Hurt(attacker, bullet)) {
		//	//死亡
		//	return;
		//}
	//}
	

	if (Follow != NULL) {
		Follow->SetLeaderPos(attacker);
	}
	if (Attack != NULL) {
		Attack->SetVictim(attacker);
	}
	
}