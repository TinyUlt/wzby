#include "Global.h"
#include "FreedomModel.h"

#include "MoveModel.h"
//#include "PlayerModel.h"
#include "MessageHelper.h"
#include "MessageModel.h"
#include "SendModel.h"
#include "ItemModel.h"
#include "PosModel.h"
#include "PathHelper.h"

FreedomModel::FreedomModel()
{
	Move = NULL;

}


FreedomModel::~FreedomModel()
{
}

void FreedomModel::Bind(ItemModel* host, MoveModel* move, FollowModel* follow) {
	this->Host = host;
	this->Move = move;
	this->Follow = follow;
}
void FreedomModel::Init(bool enable, int seed) {
	Enable = enable;
	R.seed(seed);
	/*if (enable) {
		SetAPath();
	}*/
}
void FreedomModel::Update(int frame) {
	if (!Enable) {
		return;
	}
	if (!Move->Enable) {
		return;
	}
	/*if (Follow != NULL && 
		Follow->Enable && 
		(Follow->State == FollowState::FollowState_Trace || 
		 Follow->State == FollowState::FollowState_Back)) {
		return;
	}*/
	if (Host->ItemMoveState == ItemState_MoveFreedomEnd || 
		Host->ItemMoveState == ItemState_MovingBackEnd || 
		Host->ItemMoveState == ItemState_None) {
		SetAPath();
	}
}
void FreedomModel::SetAPath() {
	int cellIndex;
	Vector3 pos;
	g_global.pathHelper->RandomCellIndex(R, cellIndex, pos);
	if (Move->CalculatePath(cellIndex, pos, 0)) {
		Host->ItemMoveState = ItemState_MovingFreedom;
	}
	else {
		Host->ItemMoveState = ItemState_None;
	}
	
}