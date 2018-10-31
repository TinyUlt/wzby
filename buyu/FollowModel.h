#pragma once
#include "TimerModel.h"
#include "Vector3.h"
#include "BaseModel.h"
class MoveModel;
class PlayerModel;
class MessageModel;
class SendModel;
class ItemModel;
class PosModel;
class FrozenModel;
//enum FollowState {
//	FollowState_Stop = 0,
//	FollowState_Trace = 1,
//	FollowState_Back = 2,
//};
class FollowModel:public BaseModel
{
public:
	FollowModel();
	~FollowModel();

	void Bind(ItemModel* host, MoveModel* move, FrozenModel* frozen, PosModel* pos, MessageModel* message/*, SendModel* send*/);
	void Init(bool enable, float castdistance);
	void Update(int frame);
	void SetLeaderPos(ItemModel* pos);
	//是否在攻击距离内
	bool IsInCastdistance();
	//是否超出原点
	bool IsOutOfOrigin();
	int DetectInterval;
	Vector3 OldPlayerPosition;
	Vector3 OriginalPosition;
	int OriginalCellIndex;
	MoveModel* Move;
	FrozenModel* Frozen;
	//PlayerModel* Player;
	ItemModel* Leader;
	//SendModel* Send;
	MessageModel* Message;
	ItemModel* Host;
	PosModel* Pos;
	TimerModel Timer;
	float Castdistance;
	//FollowState State;
};

