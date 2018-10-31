#pragma once

#include "Vector3.h"
#include "Global.h"
#include <fstream>
//#include "Astar.h"
#include "Nav.h"

using namespace std;
//class PathHelper {
//
//};
//
//class PathTransformInfo
//{
//	public:
//	float RadianOffset;
//	float DeepOffset;
//	float SpeedScale = 1;
//};
//class ProducteFishPack
//{
//public:
//	ProducteFishPack() {
//		Id = 0;
//		Frame = 0;
//		StartFrame = 0;
//		Type = 0;
//		PathName = "";
//		AngleOffset = 0;
//		SpeedScale = 0;
//		FollowCount = 0;
//		FollowDistance = 0;
//		Forever = false;
//		positionOffset.reset();
//	};
//	int		Id;
//	int		Frame;
//	int		StartFrame;
//	int		Type;
//	string	PathName;
//	int		AngleOffset;
//	float	SpeedScale;
//	int		FollowCount;
//	int		FollowDistance;
//	Vector3 positionOffset;
//	bool    Forever;
//
//	void AssignSpawnItem(gt_msg::S_SpawnItem& spm) {
//		spm.set_id(this->Id);
//		spm.set_frame(this->StartFrame + g_global.ExecuteDelayFrameForServer);
//		spm.set_pathname(this->PathName);
//		spm.set_speedscale(this->SpeedScale);
//		spm.set_angleoffset(this->AngleOffset);
//		spm.set_type(this->Type);
//		this->positionOffset.assignVec3(spm.mutable_positionoffset());
//		spm.set_forever(this->Forever);
//	}
//};
class PathHelper
{
public:
	PathHelper();
	~PathHelper();
//
	void InitPath(string fname);
	//void CalculatePath(float startX, float startY, float endX, float endY, std::vector<Vector3>& pathList);
	bool CalculatePath( Vector3 startPos, Vector3 endPos, int endCellIndex, std::vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList);
	int GetCellIndex(const Vector3& pos);
	int GetCellIndex( Vector3& pos, vector<Navgation::Cell*>& cellList);
	int GetCellIndexAndSetMoveVector(int oldIndex, const Vector3& pos, Vector3& VOffset);
	void RandomCellIndex(std::default_random_engine& r, int& index, Vector3& pos);
	Navgation::Cell* GetCellByIndex(int index);
private:

	Nav nav;
	NavData navData;
	//PathSearchInfo* pathSearch;
	//MapGroup mapGroup;
//	void InitProduction(string fname);
//	void ReleasProduction();
//	bool TryGet(string name, google::protobuf::RepeatedPtrField<PointInfo>* &posList, PathTransformInfo& transformInfo);
//	bool TryGetProducteFishList(vector<ProducteFishPack>& returnValue);
//	float GetWorldSize();
//private:
//	//void CreateFramePathLogic(ref List<ProducteFishPack> producteFishList);
//	void FramePathCircle(
//		vector<ProducteFishPack>& producteFishList,
//		ProductItem* productItem,
//		int& frame,
//		string typeName,
//		int AngleOffset,
//		float speedScale,
//		int FollowCount,
//		int FollowDistance,
//		bool Forever
//	);
//	void ProductLogicFish(
//		vector<ProducteFishPack>& producteFishList,
//		int frame,
//		string typeName,
//		string pathName,
//		int AngleOffset,
//		float speedScale,
//		int FollowCount,
//		int FollowDistance,
//		bool Forever
//	);
//
//	map<string, SinglePath* > dict;
//	ProductItem* EnterItem;
//	ProductItem* AddFishItem;
//	ProductItemGroup Production;
//	PathGroup Pg;
//	bool ParseProduction;
//	float WorldSize;
//
//	
};

