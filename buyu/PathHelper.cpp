#include "Global.h"
#include "PathHelper.h"

#include "LogSys.h"
#include "MonsterHelper.h"
//
PathHelper::PathHelper()
{
	//EnterItem = NULL;
	//AddFishItem = NULL;
	//ParseProduction = false;
}


PathHelper::~PathHelper()
{
	//ReleasProduction();
}

void PathHelper::InitPath(string fname) {
	fstream input(fname, ios::in | ios::binary);
	if (!input) {
		//g_global.logSys
		g_global.logSys->LogInWindow(fname + "加载失败");
		return;
	}


	navData.ParseFromIstream(&input);
	nav.Init(navData);
/*
	auto size = Pg.pathlist_size();
	for (int i = 0; i < size; ++i)
	{
		SinglePath* singlePath = Pg.mutable_pathlist(i);
		string pathName = singlePath->pathname();

		dict[pathName] = singlePath;
	}*/
	
	//createMapData* MapData = new createMapData(&mapGroup);
	//pathSearch = new PathSearchInfo(CCSize{ 100, 100 }, MapData->m_inspectArray);

	g_global.logSys->LogInWindow(fname + "加载成功");

	//std::vector<Vector3> pathList;
	//nav.TryGetPath(Vector3(10, 0, 7), Vector3(13, 0, 10), pathList);
	//std::vector<Vector3> pathList2;

	//nav.TryGetPath(Vector3(10, 0 , 7), Vector3(13, 0, 10), pathList2);

	std::vector<Vector3> pathList;
	vector<Navgation::Cell*> cellList;

	nav.TryGetPath(&nav.List[525], &nav.List[573], Vector3((float)15.6, 0, (float)80), Vector3((float)44.6, 0, (float)86.40000), pathList, cellList);
	/*CalculatePath(
		Vector3((float)17.4193783, 0, (float)26.2007542),
		Vector3((float)8.91149139, 0, (float) 24.1939583),
		85,
		pathList,
		cellList);*/

}
//void PathHelper::CalculatePath(float startX, float startZ, float endX, float endZ, std::vector<Vector3>& pathList) {
//	//pathSearch->calculatePath(startX, startZ, endX, endZ, pathList);
//	
//}
int PathHelper::GetCellIndex(const Vector3& pos) {
	return nav.GetCellIndex(pos);
}
int PathHelper::GetCellIndex(Vector3& pos, vector<Navgation::Cell*>& cellList) {
	return nav.GetCellIndex(pos, cellList);
}
bool PathHelper::CalculatePath( Vector3 startPos, Vector3 endPos, int endCellIndex, std::vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList) {
	return nav.TryGetPath(startPos, endPos,  endCellIndex, pathList, cellList);
	//nav.TryGetPath(startPos, endPos, pathList, cellList);
}
int PathHelper::GetCellIndexAndSetMoveVector(int oldIndex,const Vector3& pos, Vector3& VOffset) {
	return nav.GetCellIndexAndSetMoveVector( oldIndex, pos, VOffset);
}
void PathHelper::RandomCellIndex(std::default_random_engine& r, int& index, Vector3& pos) {
	nav.RandomCellIndex(r, index, pos);
}
Navgation::Cell* PathHelper::GetCellByIndex(int index) {
	return &nav.List[index];
}
//void PathHelper::InitProduction(string fname) {
//	fstream input(fname, ios::in | ios::binary);
//	if (!input) {
//		g_global.logSys->LogInWindow(fname + "加载失败");
//		return;
//	}
//	
//	Production.ParseFromIstream(&input);
//	auto itemlist_size = Production.itemlist_size();
//	for (int i = 0; i < itemlist_size; ++i)
//	{
//		auto item = Production.mutable_itemlist(i);
//
//		auto contentitems_size = item->contentitems_size();
//		for (int j = 0; j < contentitems_size; j++) {
//
//			auto content = item->mutable_contentitems(j);
//
//			auto productitemindex_size = content->productitemindex_size();
//			for (int k = 0; k < productitemindex_size; k++) {
//
//				auto index = content->productitemindex(k);
//				content->mutable_items()->AddAllocated(Production.mutable_itemlist(index));
//			}
//		}
//		
//	}
//	this->EnterItem = Production.mutable_itemlist(Production.mainenter());
//	this->AddFishItem = Production.mutable_itemlist(Production.addfishenter());
//	g_global.logSys->LogInWindow(fname + "加载成功");
//	ParseProduction = true;
//
//}
//void PathHelper::ReleasProduction() {
//	if (ParseProduction == false) {
//		return;
//	}
//
//	for (int i = 0; i < Production.itemlist_size(); ++i)
//	{
//		auto item = Production.mutable_itemlist(i);
//		for (int j = 0; j < item->contentitems_size(); j++) {
//
//			auto content = item->mutable_contentitems(j);
//
//			for (int k = 0; k < content->productitemindex_size(); k++) {
//
//				auto index = content->productitemindex(k);
//				content->mutable_items()->ReleaseLast();
//			}
//		}
//
//	}
//
//	ParseProduction = true;
//}
//bool PathHelper::TryGetProducteFishList(vector<ProducteFishPack>& returnValue) {
//	if (EnterItem == NULL) {
//		g_global.logSys->LogInWindow("enterItem == NULL");
//		return false;
//	}
//	int frame = 0;
//	FramePathCircle(returnValue, EnterItem, frame, "xiaohuangyu", 0, 1, 0, 0,false);
//	return true;
//}
//void PathHelper::FramePathCircle(
//	vector<ProducteFishPack>& producteFishList,
//	ProductItem* productItem,
//	int& frame,
//	string typeName,
//	int AngleOffset,
//	float speedScale,
//	int FollowCount,
//	int FollowDistance,
//	bool Forever
//) {
//	if (productItem == NULL) {
//		return;
//	}
//	if (productItem->contentitems_size() == 0) {
//
//		int finalFrame = frame;
//		ProductLogicFish(producteFishList, finalFrame, typeName, productItem->contentname(), AngleOffset, speedScale, FollowCount, FollowDistance, Forever);
//	}
//	{
//		for (int i = 0; i < productItem->time(); i++) {
//
//			for (int j = 0; j < productItem->contentitems_size(); j++) {
//
//				auto item = productItem->mutable_contentitems(j);
//
//				//把该名字加到子级的所有鱼中， 子级有,子级优先. 子级无,父级优先
//				string t = typeName;
//				if (item->fishlist_size() > 0) {
//					int RandKey = rand() % item->fishlist_size();
//					t = item->fishlist(RandKey);
//				}
//
//				int newAngleOffset = item->angleoffset();
//				if (newAngleOffset == 0) {
//					newAngleOffset = AngleOffset;
//				}
//				int newFollowCount = item->followcount();
//				if (newFollowCount == 0) {
//					newFollowCount = FollowCount;
//				}
//				int newFollowDistance = item->followdistance();
//				if (newFollowDistance == 0) {
//					newFollowDistance = FollowDistance;
//				}
//
//				bool newForever = item->forever();
//				if (newForever == false) {
//					newForever = Forever;
//				}
//
//
//				float newSpeedScale = item->speedscale();
//				newSpeedScale *= speedScale;
//
//				{
//					int RandKey = rand() % item->items_size();
//
//					FramePathCircle(producteFishList, item->mutable_items(RandKey), frame, t, newAngleOffset, newSpeedScale, newFollowCount, newFollowDistance, newForever);
//				}
//				frame = item->frame() + frame;
//			}
//		}
//	}
//}
//void PathHelper::ProductLogicFish(
//	vector<ProducteFishPack>& producteFishList,
//	int frame,
//	string typeName,
//	string pathName,
//	int AngleOffset,
//	float speedScale,
//	int FollowCount,
//	int FollowDistance,
//	bool Forever
//) {
//	if (AngleOffset == -1) {
//
//		AngleOffset = rand() % 360;
//	}
//
//	int fishType = -1;
//	if (g_global.monsterHelper->TryGetTypeByName(typeName, fishType)) {
//		ProducteFishPack pp;
//		pp.Frame = frame;
//		pp.Type = fishType;
//		pp.PathName = pathName;
//		pp.AngleOffset = AngleOffset;
//		pp.SpeedScale = speedScale;
//		pp.FollowCount = FollowCount;
//		pp.FollowDistance = FollowDistance;
//		pp.Forever = Forever;
//		producteFishList.push_back(pp);
//	}
//}
//bool PathHelper::TryGet(string name, google::protobuf::RepeatedPtrField<PointInfo>* &pointList, PathTransformInfo& transformInfo) {
//
//	if (dict.count(name) > 0) {
//		SinglePath* path = dict[name];
//		transformInfo.RadianOffset = path->radianoffset();
//		transformInfo.DeepOffset = path->deepoffset();
//		transformInfo.SpeedScale = path->speedscale();
//		string copyName = path->copypathname();
//		if (copyName != "") {
//			
//			if (dict.count(copyName)) {
//
//				SinglePath* copyPath = dict[copyName];
//				pointList = copyPath->mutable_pathpointlist();
//				transformInfo.RadianOffset += copyPath->radianoffset();
//				transformInfo.DeepOffset += copyPath->deepoffset();
//				transformInfo.SpeedScale *= copyPath->speedscale();
//				return true;
//			}
//			else {
//				return false;
//			}
//		}
//		else {
//			pointList = path->mutable_pathpointlist();
//			return true;
//		}
//	}
//	else {
//		return false;
//	}
//}
