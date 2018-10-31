#include "Monster.h"
#include "Global.h"

using namespace std;
Monster::Monster()
{
	Id = -1;
	State = MonsterState::None;

	Follow.BindMove(&Move);
	//Move = new MoveModel();
}


Monster::~Monster()
{
	/*if (Move != NULL) {
		delete(Move);
		Move = NULL;
	}*/
}
bool Monster::Init(S_SpawnMonster& pack) {
	this->Pack = pack;
	return Init(pack.id(), pack.frame(), pack.type(), pack.pos(), true, true);
}
bool Monster::Init(
	int id,
	int startFrame,
	int type,
	Vec3 pos,
	bool moveEnable,
	bool followEnable
) {
	Move.Init(moveEnable);
	Follow.Init(followEnable);
	//ItemBase::Init();
	IsFreezen = false;
	FreezenStartFrame = 0;
	FreezenEndFrame = 0;
	
	State = Alive;
	Id = id;
	StartFrame = startFrame;
	Type = type;
	Move.SetBornPosition(Vector3(pos));
	//Move.Position.conver(pos);
	
	return true;
}
int Monster::GetId() {
	return Id;
}
int Monster::GetType() {
	return Type;
}
bool Monster::Update(int frame) {

	Frame = frame - StartFrame;

	if (IsFreezen == true) {
		if (FreezenEndFrame <= frame) {
			IsFreezen = false;
		}
	}
	else {
		if (Follow.Enable) {
			Follow.Update(Frame);
		}
		
		Move.Update(Frame);
		//if (pathList.size() > 0) {

		//	//如果距离走完 则不动
		//	if (PathIndex  >= pathList.size() -1 ) {
		//		//Direction = -1;
		//	}
		//	else if (PathIndex  < 0) {
		//		//pathList.clear();
		//	}
		//	else {
		//		auto df = (pathList[PathIndex] - NewPos);
		//		if (df.sqrMagnitude() < 0.1 * 0.1) {
		//			PathIndex += Direction;
		//			CaculNormalize();
		//		}
		//		else {
		//			NewPos.addin(normalize * 0.01);
		//			HaveNewPos = true;
		//		}
		//	}
			/*if ( PathIndex < pathList.size()) {
				normalize = pathList[PathIndex] - pathList[PathIndex+1];
			}*/
			//if (PathIndex < pathList.size()) {
				
			//	if (df.sqrMagnitude() < 0.1 * 0.1) {
			//		if (PathIndex + 1 == pathList.size()) {
			//			
			//		}
			//		else {
			//			normalize = pathList[PathIndex + 1] - pathList[PathIndex];
			//		}
			//		//PathIndex += 1;
			//		//if (PathIndex < pathList.size()) {
			//			
			//			normalize.normalize();
			//		//}
			//		else {
			//			//停止
			//		}
			//		
			//	}
			//}
			//else {
			//	//停止
			//}
			
		//}
		/*Vector3 pos;
		int distance;
		if (!TryGetPointInfo(GetIndex(Frame), pos, distance)) {
			State = PathDone;
			return false;
		}*/
	

		//Position = pos;
		
	}
	
	return true;

}
//int Monster::GetIndex(int frame) {
//	int index = 0;
//	if (Forever) {
//		int length = this->PosList->size();
//		bool positive = (frame / length) % 2 == 0 ? true : false;
//
//		if (positive) {
//			index = frame % length;
//		}
//		else {
//			index = length - frame % length;
//		}
//	}
//	else {
//		index = frame;
//	}
//	return index;
//}
//bool Monster::TryGetPointInfo(int index, Vector3& pos, int& distance) {
//
//	if (index < 0 || index >= PosList->size()) {
//
//		return false;
//	}
//	
//	pos.reset();
//
//	auto& pathInfo = this->PosList->Get(index);
//	pos.x = pathInfo.x();
//	pos.y = pathInfo.y();
//	pos.z = pathInfo.z();
//	distance = pathInfo.distance();
//	return true;
//}


MonsterState Monster::GetState() {
	return State;
}
S_SpawnMonster* Monster::GetPack() {
	return &Pack; 
}

void Monster::SetFreezen(int startFrame, int endFrame) {

	if (endFrame > Frame) {
		IsFreezen = true;
	}
	FreezenStartFrame = startFrame;
	FreezenEndFrame = endFrame;
}
//bool Monster::TryGetPosition(Vec3& pos) {
//	if (LastChangePos.equal(Position)) {
//		return false;
//	}
//
//	Position.assignVec3(pos);
//	LastChangePos = Position;
//	return true;
//}

//vector<Vector3>* Monster::GetPathList() {
//	return &pathList;
//}


bool Monster::IsNewPosition() {
	return Move.IsNewPosition();
}
void Monster::GetNewPosition(Vec3* pos) {
	Move.GetNewPosition(pos);
}
//void Monster::ChangePath(const Vector3& pos) {
//	Move.SetPath(pos);
//}
void Monster::SetPosition(Vec3& pos) {
	Move.Position.conver(pos);
}
void Monster::SetPosition(Vector3& pos) {
	Move.Position = pos;
}
Vector3 Monster::GetPosition() {
	return Move.Position;
}
void Monster::GetPosition(Vec3* pos) {
	Move.Position.assignVec3(pos);
}

void Monster::Beaten(PlayerModel* player) {

	if (Follow.Enable) {
		Follow.SetFollowPlayer(player);
	}
}