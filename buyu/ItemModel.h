#pragma once
#include "MoveModel.h"
#include "FollowModel.h"
#include "FreedomModel.h"
#include "FrozenModel.h"
#include "AttackModel.h"
#include "BeatenModel.h"
#include "ValueModel.h"
#include "ExperienceModel.h"
#include "EventNotifyModel.h"
#include "PosModel.h"
#include "MulModel.h"
#include "MulSkillModel.h"
#include "LVModel.h"
#include "DMGSkillModel.h"
#include "ScoreModel.h"
class PlayerModel;
class MessageModel;
class SendModel;
class SkillBaseModel;
class ItemCache;
class ItemModel 
{
public:
	ItemModel();
	~ItemModel();

	void Bind(ItemCache* itemManager, BulletCache* bulletManager, MessageModel* message, SendModel* send);
	bool Init(SpawnMessage* pack);
	
	int GetId();
	bool Update(int frame);
	int GetType();
	void SetFreezen(S_Hit* freezen);
	S_SpawnItem* GetPack();

	void SetPath(S_MovePosList* posList);
	//void CalculateAndSetPath(S_MonsterTerminal* data);
	void Back();
	bool Enable;

	int Id;
	int Type;
	int Frame;
	int SpawnId;
	int StartFrame;

	ItemTeam TeamId;
	MoveState ItemMoveState;//-1待创建， 0活着，1 路径走完， 2 被杀死
	//AttackState ItemAttackState;
	S_SpawnItem ItemPack;

	PosModel Pos;
	EventNotifyModel EventNotify;
	FrozenModel Frozen;
	MoveModel Move;
	FollowModel Follow;
	AttackModel Attack;
	FreedomModel Freedom;
	BeatenModel Beaten;

	LVModel LV;
	MulModel Mul;

	ValueModel HP;
	ScoreModel Score;
	ValueModel DMG;
	
	
	MessageModel* Message;
	ItemCache* ItemManager;

	map<int, SkillBaseModel*> SkillGroup;

};

