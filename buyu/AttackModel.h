#pragma once
#include "TimerModel.h"
#include <vector>
using namespace std;
//class TimerModel;
class PlayerModel;
class ItemModel;
class SendModel;
class MessageModel;
class MoveModel;
class PosModel;
class FrozenModel;
class BulletCache;
class AttackModel
{
public:
	AttackModel();
	~AttackModel();
	void Init(bool enable, bool autoAttack, int actiontime, vector<int>& skillsId);
	void Bind(ItemModel* host, BulletCache* bulletManager, MoveModel* move, PosModel* pos, FrozenModel* frozen, MessageModel* message/*, SendModel* send*/);
	void Update(int frame);
	void SetInterval(int frame);
	//void SetTargetPos(PosModel* target);
	void SetVictim(ItemModel* victim);
	int GetSkill();
	//void ManualAttack(ItemModel* target);
	BulletCache* BulletManager;
	TimerModel Timer;
	ItemModel* Host;
	//SendModel* Send;
	MessageModel* Message;
	MoveModel* Move;
	PosModel* Pos;
	FrozenModel* Frozen;
	//PlayerModel* AttackPlayer;
	//PosModel* TargetPos;
	ItemModel* Victim;
	bool Enable;
	//float Range;
	vector<int> SkillsId;
	bool AutoAttack;
	
};

