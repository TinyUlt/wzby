#pragma once
#include "Vector3.h"
#include <vector>
#include "Nav.h"
#include "BaseModel.h"
using namespace std;
//class S_MovePosList;
class MessageModel;
class ItemModel;
class AttackModel;
class PosModel;
class FrozenModel;
//enum MoveState {
//	MoveState_TobeMoved = 0,
//	MoveState_Moving = 1,
//	MoveState_End = 2,
//	MoveState_Stop = 2,
//};
//class Navgation::Cell;
class MoveModel:public BaseModel
{
public:
	MoveModel();
	~MoveModel();
	void Bind(ItemModel* host, AttackModel* attack,PosModel* pos, FrozenModel* frozen, MessageModel* message);
	void Init(bool enable, int cellIndex, float speed);
	void Update(int frame);
	bool TryGetPosByFrame(int frame, Vector3& pos);
	bool CalculatePath(int endCellIndex, const Vector3& pos, const float range);
	void SetPath(S_MovePosList* posList);
	int GetCellIndex();
	void AddCellList(int index);
	void SetPosAndVOffset(R_Move* move);

	//void CalculateAndSetPath(int endCellIndex, int frame, const Vector3& pos);
	//void SetBornPosition(Vector3& pos);
	//bool IsMoving();
	
	vector<Vector3> tempPathList;
	vector<Vector3> tempPathListEx;
	vector<Vector3> pathList;
	vector<int> FrameList;
	vector<Navgation::Cell*> CellList;

	int PathIndex;
	float Speed;// 每帧多少米
	int NowFrame;
	int CalFrame;
	//MoveState State;
	S_MovePosList PosListPack;
	S_Move MovePack;

	MessageModel* Message;
	ItemModel* Host;
	AttackModel* Attack;
	PosModel* Pos;
	FrozenModel* Frozen;
	bool IsSetPath;
	//int SetPathFrame;
	//int OldIndex;
};

