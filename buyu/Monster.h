#pragma once
#include "PathHelper.h"
#include "MoveModel.h"
#include "FollowModel.h"
class PlayerModel;
enum MonsterState
{
	None = 0,
	Alive = 1,
	PathDone = 2,
	Killed = 3

};
class Monster //:public ItemBase
{
public:
	Monster();
	~Monster();
	bool Init(S_SpawnMonster& pack);
	bool Init(
		int id,
		int startFrame,
		int type,
		Vec3 pos,
		bool moveEnable,
		bool followEnable
		/*string pathName,
		float angleOffset,
		float speedScale,
		Vector3 PositionOffset,
		bool forever*/
		);
	int GetId();
	bool Update(int frame);
	//int GetIndex(int frame);
	int GetType();
	//bool TryGetPointInfo(int index, Vector3& pos, int& distance);
	void SetFreezen(int startFrame, int endFrame);
	//bool TryGetPosition(Vec3& pos);
	bool IsNewPosition();
	MonsterState GetState();
	S_SpawnMonster* GetPack();
	void GetNewPosition(Vec3* pos);
	//void ChangePath(const Vector3& pos);
	void SetPosition(Vec3& pos);
	void SetPosition(Vector3& pos);
	Vector3 GetPosition();
	void GetPosition(Vec3* pos);


	//怪物被打
	void Beaten(PlayerModel* player);
	//vector<Vector3>* GetPathList();
	
private:
	//
	S_SpawnMonster Pack;
	int Id;
	int Frame;
	int Type;
	//string PathName;
	//float AngleOffset;
	//float SpeedScale;
	//Vector3 PositionOffset;
	//bool Forever;
	int StartFrame;
	MonsterState State;//-1待创建， 0活着，1 路径走完， 2 被杀死

	bool IsFreezen;
	int FreezenStartFrame;
	int FreezenEndFrame;

	MoveModel Move;
	FollowModel Follow;
	//google::protobuf::RepeatedPtrField<PointInfo>* PosList;
	//PathTransformInfo transformInfo;
	
};

