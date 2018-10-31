#include "Global.h"
#include "ItemModel.h"
#include "PathHelper.h"
#include "MessageHelper.h"
#include "SkillBaseModel.h"
using namespace std;
ItemModel::ItemModel()
{
	Id = -1;
}


ItemModel::~ItemModel()
{
	
}
void ItemModel::Bind(ItemCache* itemManager, BulletCache* bulletManager, MessageModel* message, SendModel* send) {
	Message = message;
	ItemManager = itemManager;
	EventNotify.Bind(send);
	Follow.Bind(this, &Move, &Frozen, &Pos, message);
	Move.Bind(this, &Attack, &Pos, &Frozen, message);
	Attack.Bind(this, bulletManager, &Move, &Pos, &Frozen, message);
	Beaten.Bind(this, &Follow, &Attack, message);
	Freedom.Bind(this, &Move, &Follow);
	LV.Bind(this, message);
}

bool ItemModel::Init(SpawnMessage* pack) {
	Enable = true;
	Id = pack->ItemId;
	ItemPack = pack->ItemPack;
	TeamId = (ItemTeam)pack->TeamId;
	StartFrame = pack->Frame;
	Type = pack->Type;
	SpawnId = pack->SpawnId;
	SkillGroup = pack->SkillPack;

	for (auto& iter : SkillGroup) {
		auto& skill = iter.second;
		skill->Bind(this, ItemManager, Message);
	}

	Pos.		Init(pack->Pos, pack->CellIndex);
	Move.		Init(pack->MoveEnable, pack->CellIndex, pack->MoveSpeed);
	Beaten.		Init(pack->BeatenEnable);
	Freedom.	Init(pack->FreedomEnable, pack->Seed);
	Follow.		Init(pack->FollowEnable, pack->Castdistance);
	Attack.		Init(pack->AttackEnable, pack->AutoAttack, pack->Actiontime, pack->SkillsId);
	Frozen.		Init(pack->FrozenEnable);
	Score.		Init(pack->Score);
	HP.			Init(pack->HP);
	LV.			Init(pack->LVEnable, pack->LV, pack->EXP);
	DMG.		Init(pack->DMG);
	Mul.		Init(true,pack->MulList, pack->Multiple);
	EventNotify.Init(pack->EventNotifyEnable, Id);
	//ItemAttackState = AttackState_None;
	ItemMoveState = ItemState_None;
	return true;
}

int ItemModel::GetId() {
	return Id;
}
int ItemModel::GetType() {
	return Type;
}
bool ItemModel::Update(int frame) {

	Frame = frame;

	if (!Enable) {
		return false;
	}
	Frozen.Update(frame);
	Move.Update(frame);
	Freedom.Update(frame);
	Follow.Update(frame);
	Attack.Update(frame);
	Beaten.Update(frame);
	LV.Update(frame);

	for (auto& iter : SkillGroup) {
		auto skill = iter.second;
		skill->Update(frame);
	}
	return true;

}

S_SpawnItem* ItemModel::GetPack() {
	Pos.Position.assignVec3(ItemPack.mutable_pos());
	return &ItemPack; 
}

void ItemModel::SetFreezen(S_Hit* freezen) {

	Frozen.SetFreezen(freezen);
}


void ItemModel::SetPath(S_MovePosList* posList) {
	Move.SetPath(posList);
}
//void ItemModel::CalculateAndSetPath(S_MonsterTerminal* data) {
//	//Move.CalculateAndSetPath(data->endcellindex(),data->frame(), data->pos());
//}
void ItemModel::Back() {
	for (auto& iter : SkillGroup) {
		auto skill = iter.second;
		skill->Back();
	}
	SkillGroup.clear();
}