#include "Global.h"
#include "AttackModel.h"
#include "LogSys.h"
//#include "PlayerModel.h"
#include "ItemModel.h"
#include "SendModel.h"
#include "MessageModel.h"
#include "PosModel.h"
#include "BulletModel.h"
#include "MessageHelper.h"
#include "FrozenModel.h"
#include "BulletCache.h"
AttackModel::AttackModel()
{
	Host = NULL;
	Message = NULL;
	//Send = NULL;
	Move = NULL;
	Pos = NULL;
	Victim = NULL;
}


AttackModel::~AttackModel()
{
}

void AttackModel::Init(bool enable, bool autoAttack, int actiontime, vector<int>& skillsId) {

	Enable = enable;
	AutoAttack = autoAttack;
	//Range = range;
	//SkillId = skillId;
	Victim = NULL;
	SkillsId = skillsId;
	SetInterval(actiontime);
	
	
}
void AttackModel::Bind( ItemModel* host, BulletCache* bulletManager, MoveModel* move, PosModel* pos, FrozenModel* frozen, MessageModel* message/*, SendModel* send*/) {
	this->Host = host;
	this->Message = message;
	//this->Send = send;
	this->Move = move;
	this->Pos = pos;
	this->Frozen = frozen;
	this->BulletManager = bulletManager;
}
void AttackModel::SetInterval(int frame) {
	Timer.SetInterval(frame, -1);
}
void AttackModel::Update(int frame) {
	if (!Enable) {
		return;
	}
	//×Ô¶¯¹¥»÷
	if (!AutoAttack) {
		return;
	}

	//±»±ù¶³
	if (Frozen->Enable && Frozen->IsFrozen) {
		return;
	}

	//do {

	//} while (0);

	////ÔÚ·Ç×·×Ù×´Ì¬ÏÂ
	//if (!(Host->ItemMoveState == ItemState_MovingTrack || Host->ItemMoveState == ItemState_MovingTrackEnd)) {
	//	Victim = NULL;
	//}
	/*if (Host->ItemMoveState != ItemState_MovingTrack) {

	}*/
	//if (Host->ItemMoveState == ItemState_MovingTrackEnd && Victim == NULL /*|| !Victim->Enable*/) {
	//	Victim = NULL;
	//	Host->ItemMoveState = ItemState_None;
	//	return;
	//}
	
	
	

	const auto& playerPos = Victim->Pos.Position;
	const auto& monsterPos = Pos->Position;

	if (Host->ItemMoveState == ItemState_MovingTrackEnd || 
		ItemState_AttackEnd == Host->ItemMoveState ) 
	{
		
		if (Victim == NULL) {
			Host->ItemMoveState = ItemState_None;
			return;
		}
		if (!Victim->Enable) {
			Victim = NULL;
			Host->ItemMoveState = ItemState_None;
			return;
		}
		if (Timer.Update(frame)) {

			auto data = g_global.messageHelper->Get_R_Attack();
			data->set_frame(g_global.GetExecuteDelayFrameForServer(frame));
			data->set_victimid(Victim->Id);
			data->set_skillid(GetSkill());
			Message->SendAttack(Host->Id, data);
			g_global.messageHelper->Back_R_Attack(data);
			
			g_global.logSys->LogInWindow("¹¥»÷");
			Host->ItemMoveState = ItemState_Attacking;
		}
		else {
			
		}
	}
}
int AttackModel::GetSkill() {
	int index = rand() % SkillsId.size();
	return SkillsId[index];
}
void AttackModel::SetVictim(ItemModel* victim) {
	if (!Enable) {
		return;
	}
	Victim = victim;
}
//void AttackModel::ManualAttack(ItemModel* target) {
//	if (!Enable) {
//		return;
//	}
//	if (AutoAttack) {
//		return;
//	}
//
//	if (target != NULL) {
//		BulletManager->CreateBullet(Host, target, SkillId);
//	}
//}