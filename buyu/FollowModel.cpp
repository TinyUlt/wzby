#include "Global.h"
#include "FollowModel.h"
#include "MoveModel.h"
//#include "PlayerModel.h"
#include "MessageHelper.h"
#include "MessageModel.h"
#include "SendModel.h"
#include "ItemModel.h"
#include "PosModel.h"
#include "LogSys.h"
FollowModel::FollowModel()
{
	DetectInterval = 10;
	Move = NULL;
	Message = NULL;
	Host = NULL;
	Pos = NULL;
}


FollowModel::~FollowModel()
{
}

void FollowModel::Bind(ItemModel* host, MoveModel* move, FrozenModel* frozen, PosModel* pos, MessageModel* message/*, SendModel* send*/) {
	this->Move = move;
	this->Message = message;
	//this->Send = send;
	this->Host = host;
	this->Pos = pos;
	this->Frozen = frozen;
}
void FollowModel::Init(bool enable, float castdistance) {
	Enable = enable;
	this->Leader = NULL;
	Castdistance = castdistance;
	//this->Range = range;
	Timer.SetInterval(DetectInterval);
}

void FollowModel::SetLeaderPos(ItemModel* leader) {
	if (!Enable) {
		return;
	}
	//如果在返回途中，或者处于冰冻状态 不能被激怒
	if (Host->ItemMoveState == ItemState_MovingBack || Frozen->IsFrozen) {
		return;
	}
	//保存激怒前的位置
	if (Leader == NULL) {
		OriginalPosition = Pos->Position;
		OriginalCellIndex = Move->GetCellIndex();
	}
	//设置被跟随者
	Leader = leader;
	Host->ItemMoveState = ItemState_MovingTrack;
}
void FollowModel::Update(int frame) {
	if (!Enable) {
		return;
	}
	if (!Move->Enable) {
		return;
	}
	if (Leader == NULL) {
		return;
	}
	////有问题
	//if (Host->ItemMoveState == ItemState_Attacking) {
	//	return;
	//}
	//如果返回结束
	if (Host->ItemMoveState == ItemState_MovingBackEnd) {
		
		
	}
	//如果跟随超出距离 和 如果追随者离开或死亡 返回原点
	else if (Host->ItemMoveState == ItemState_MovingTrack && IsOutOfOrigin() || !Leader->Enable){
		Move->CalculatePath(OriginalCellIndex, OriginalPosition, 0);
		Host->ItemMoveState = ItemState_MovingBack;
		Leader = NULL;
	}else if (Host->ItemMoveState == ItemState_MovingTrack 
		|| Host->ItemMoveState == ItemState_MovingTrackEnd 
		|| ItemState_AttackEnd == Host->ItemMoveState
		/*|| ItemState_Attacking == Host->ItemMoveState*/) {
		
		if (Timer.Update(frame)) 
		{
				//g_global.logSys->LogInWindow("1111");
			if (this->Leader != NULL) {
				auto& p = Leader->Pos.Position;
				if (!p.equal(OldPlayerPosition)) {
					//g_global.logSys->LogInWindow("2222");

					do {
						//auto d = Vector3::SqrMagnitude(p, Pos->Position);
						if (IsInCastdistance()) {
							//g_global.logSys->LogInWindow("3333");
							if (Host->ItemMoveState == ItemState_MovingTrack || 
								Host->ItemMoveState == ItemState_MovingFreedom || 
								ItemState_AttackEnd == Host->ItemMoveState) {
								//g_global.logSys->LogInWindow("4444");
							}
							else {
								//g_global.logSys->LogInWindow("5555");
								break;
							}
						}
						//g_global.logSys->LogInWindow("6666");
						Move->CalculatePath(Leader->Pos.CellIndex, p, Castdistance*0.9);
						Host->ItemMoveState = ItemState_MovingTrack;
						//g_global.logSys->LogInWindow("aaa");
					} while (0);
					
					OldPlayerPosition = p;
				}
			}
		}
	}
}
bool FollowModel::IsInCastdistance() {
	if (Leader == NULL) {
		return true;
	}
	auto d = Vector3::SqrMagnitude(Leader->Pos.Position, Pos->Position);
	return d < Castdistance*Castdistance;
}
bool FollowModel::IsOutOfOrigin() {
	return Vector3::SqrMagnitude(OriginalPosition, Pos->Position) > 50;
}