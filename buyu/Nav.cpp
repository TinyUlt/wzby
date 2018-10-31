#include "Global.h"
#include "Nav.h"
#include "LogSys.h"
#include <algorithm>
using namespace std;

Nav::Nav()
{
}


Nav::~Nav()
{
}

void Nav::Init(gt_msg::NavData& data) {
	List.clear();
	for (int i = 0; i < data.celllist_size(); i++) {
		gt_msg::Cell c = data.mutable_celllist()->Get(i);
		Navgation::Cell cell;
		cell.index = c.index();
		cell.v[0] = c.mutable_v()->Get(0);
		cell.v[1] = c.mutable_v()->Get(1);
		cell.v[2] = c.mutable_v()->Get(2);
		cell.MidPos = Vector3(c.midpos());
		cell.LineMidSqrDistance[0] = c.mutable_linemidsqrdistance()->Get(0);
		cell.LineMidSqrDistance[1] = c.mutable_linemidsqrdistance()->Get(1);
		cell.LineMidSqrDistance[2] = c.mutable_linemidsqrdistance()->Get(2);
		cell.LineMidPos[0] = c.mutable_linemidpos()->Get(0);
		cell.LineMidPos[1] = c.mutable_linemidpos()->Get(1);
		cell.LineMidPos[2] = c.mutable_linemidpos()->Get(2);
		cell.Normalize[0] = c.mutable_normalize()->Get(0);
		cell.Normalize[1] = c.mutable_normalize()->Get(0);
		cell.Normalize[2] = c.mutable_normalize()->Get(0);
		for (int j = 0; j < 3; j++) {

			auto n = c.mutable_nears()->Get(j);
			Navgation::Near ne;
			ne.Enable = n.enable();
			if (ne.Enable) {
				ne.Index = n.index();
				ne.Distance = n.distance();
				ne.OtherLineIndex = n.otherlineindex();
				ne.LineIndex = n.lineindex();
				ne.PointIndex[0] = n.mutable_pointindex()->Get(0);
				ne.PointIndex[1] = n.mutable_pointindex()->Get(1);
			}
			/*else {

			}*/
			
			
			cell.nears.push_back(ne);
		}
		List.push_back(cell);
	}
	ListCount = List.size();
}
void Nav::RandomCellIndex(std::default_random_engine& r, int& index, Vector3& pos){

	std::uniform_int_distribution<> u(0, List.size()-1);
	auto cell = List[u(r)];
	index = cell.index;
	pos = cell.MidPos;
}
int Nav::GetCellIndex(const Vector3& pos)
{
	for(auto& cell : List)
	{
		//change ex
		if (Vector3::PointinTriangleEX(cell.v[0], cell.v[1], cell.v[2], pos))
		{
			return cell.index;
		}
	}
	return -1;
}
bool Nav::tryGetCellInCellListByPos(Vector3& pos, vector<Navgation::Cell*>& cellList, Navgation::Cell** startCell)
{
	Vector3 startPosTemp = pos;
	//Navgation::Cell* startCell = NULL;
	*startCell = NULL;

	do {
		if (cellList.empty()) {
			auto index = GetCellIndex(startPosTemp);
			if (index >= 0) {
				*startCell = &List[index];
			}
		}

		if (*startCell != NULL) {
			break;
		}

		*startCell = GetCellInCellListByPos(startPosTemp, cellList);
		if (*startCell != NULL) {
			break;
		}

		startPosTemp = pos;
		startPosTemp.x = pos.x + (float)0.0001;
		*startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (*startCell != NULL) {
			pos = startPosTemp;
			break;
		}

		startPosTemp = pos;
		startPosTemp.x = pos.x - (float)0.0001;
		*startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (*startCell != NULL) {
			pos = startPosTemp;
			break;
		}

		startPosTemp = pos;
		startPosTemp.y = pos.y + (float)0.0001;
		*startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (*startCell != NULL) {
			pos = startPosTemp;
			break;
		}

		startPosTemp = pos;
		startPosTemp.y = pos.y - (float)0.0001;
		*startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (*startCell == NULL) {
			//pos = startPosTemp;
			return false;
		}

	} while (0);

	return true;
	//return startCell->index;
}
bool Nav::TryGetPath( Vector3& startPos, Vector3& endPos, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList) {
	Navgation::Cell* startCell = NULL;
	Navgation::Cell* endCell = NULL;

	//if (cellList.empty()) {
		for (auto& cell : List) {
			if (startCell == NULL && Vector3::PointinTriangleEX(cell.v[0], cell.v[1], cell.v[2], startPos))
			{
				startCell = &cell;
			}
			if (endCell == NULL && Vector3::PointinTriangleEX(cell.v[0], cell.v[1], cell.v[2], endPos))
			{
				endCell = &cell;
			}
			if (endCell != NULL && startCell != NULL)
			{
				break;
			}
		}
	//}
	//else {
	//	for (auto& cell : List) {
	//		
	//		if (endCell == NULL && Vector3::PointinTriangleEX(cell.v[0], cell.v[1], cell.v[2], endPos))
	//		{
	//			endCell = &cell;
	//			break;
	//		}
	//	}
	//	
	//	for (auto& cell : cellList) {
	//		if (startCell == NULL && Vector3::PointinTriangleEX(cell->v[0], cell->v[1], cell->v[2], startPos))
	//		{
	//			startCell = cell;
	//			break;
	//		}
	//		
	//	}
	//}
		if (startCell == NULL) {
			//Navgation::Cell* minDistanceCell;
			float minDistance = 1000000;
			for (auto& cell : List) {

				float distance = Vector3::SqrMagnitude(cell.MidPos, startPos);
				if (distance < minDistance)
				{
					minDistance = distance;
					startCell = &cell;


				}
			}
			float lineDistance = 10000;
			for (int i = 0; i < 3; i++) {
				float d = Vector3::SqrMagnitude(startCell->LineMidPos[i], startPos);
				if (d < lineDistance) {
					startPos = startCell->LineMidPos[i];
					lineDistance = d;
				}
			}
		}

	if (endCell == NULL) {
		//Navgation::Cell* minDistanceCell;
		float minDistance = 1000000;
		for (auto& cell : List) {

			float distance = Vector3::SqrMagnitude(cell.MidPos, endPos);
			if (distance < minDistance)
			{
				minDistance = distance;
				endCell = &cell;
				
				
			}
		}
		float lineDistance = 10000;
		for (int i = 0; i < 3; i++) {
			float d = Vector3::SqrMagnitude(endCell->LineMidPos[i], endPos);
			if (d < lineDistance) {
				endPos = endCell->LineMidPos[i];
				lineDistance = d;
			}
		}
	}

	if (endCell == NULL || startCell == NULL) {
		return false;;
	}

	BuildCellPath(startCell, endCell, startPos, endPos, cellList);
	BuildPointPath(startPos, endPos, pathList);
	return true;
}
bool Nav::TryGetPath(int startCellIndex, int endCellIndex,const Vector3& startPos,const Vector3& endPos, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList) {

	if (startCellIndex < 0 || startCellIndex >= ListCount || endCellIndex < 0 && endCellIndex >= ListCount) {
		return false;
	}

	Navgation::Cell& startCell = List[startCellIndex]; 
	Navgation::Cell& endCell = List[endCellIndex];

	return TryGetPath(&startCell, &endCell, startPos, endPos, pathList, cellList);
}
bool Nav::TryGetPath(Navgation::Cell* startCell, Navgation::Cell* endCell, const Vector3& startPos, const Vector3& endPos, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList) {
	BuildCellPath(startCell, endCell, startPos, endPos, cellList);
	BuildPointPath(startPos, endPos, pathList);
	return true;
}
Navgation::Cell* Nav::GetCellInCellListByPos(const Vector3& pos, vector<Navgation::Cell*>& cellList) {
	for (auto& cell : cellList) {

		if (Vector3::PointinTriangleEX(cell->v[0], cell->v[1], cell->v[2], pos))
		{
			return cell;
		}
	}
	return NULL;
}
int Nav::GetCellIndex(Vector3& pos, vector<Navgation::Cell*>& cellList) {
	Navgation::Cell* startCell = NULL;
	if (!tryGetCellInCellListByPos(pos, cellList, &startCell)) {
		return -1;
	}
	return startCell->index;
}
bool Nav::TryGetPath(Vector3& startPos,  const Vector3& endPos, int endCellIndex, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList) {
	
	if (endCellIndex < 0 || endCellIndex >= (int)List.size()) {
		return false;
	}
	Navgation::Cell& endCell = List[endCellIndex];
	if (!Vector3::PointinTriangleEX(endCell.v[0], endCell.v[1], endCell.v[2], endPos)) {
		return false;
	}

	//Vector3 startPosTemp = startPos;
	Navgation::Cell* startCell = NULL;
	if (!tryGetCellInCellListByPos(startPos, cellList, &startCell)) {
		return false;
	}
	/*do {
		if (cellList.empty()) {
			auto index = GetCellIndex(startPosTemp);
			if (index >= 0) {
				startCell = &List[index];
			}
		}

		if (startCell != NULL) {
			break;
		}

		startCell = GetCellInCellListByPos(startPosTemp, cellList);
		if (startCell != NULL) {
			break;
		}

		startPosTemp = startPos;
		startPosTemp.x = startPos.x + 0.0001;
		startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (startCell != NULL) {
			break;
		}

		startPosTemp = startPos;
		startPosTemp.x = startPos.x - 0.0001;
		startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (startCell != NULL) {
			break;
		}

		startPosTemp = startPos;
		startPosTemp.y = startPos.y + 0.0001;
		startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (startCell != NULL) {
			break;
		}

		startPosTemp = startPos;
		startPosTemp.y = startPos.y - 0.0001;
		startCell = GetCellInCellListByPos(startPosTemp, cellList);

		if (startCell == NULL) {
			return false;
		}

	} while (0);*/
		
	return TryGetPath(startCell, &endCell, startPos, endPos, pathList, cellList);
}

//得到最短路径单元格
Navgation::Cell* Nav::GetMinPathFormOpenList()
{
	if (openList.size() > 0)
	{
		vector<Navgation::Cell*>::iterator  minIter = openList.begin();
		//Navgation::Cell* minC = *minIter;
		for (auto iter = openList.begin(); iter != openList.end(); iter++) {
			
			if ((*iter)->fValue < (*minIter)->fValue)
			{
				minIter = iter;
			}
		}

		Navgation::Cell* cell = *minIter;
		openList.erase(minIter);

		return cell;
	}

	return NULL;
}
 void Nav::Get1PointIndexBy2LineIndex(int aLineIndex, int bLineIndex,int& pointIndex)
{
	if (aLineIndex == 0 && bLineIndex == 2 || aLineIndex == 2 && bLineIndex == 0)
	{
		pointIndex = 0;
	}
	else if (aLineIndex == 0 && bLineIndex == 1 || aLineIndex == 1 && bLineIndex == 0)
	{
		pointIndex = 1;
	}
	else if (aLineIndex == 1 && bLineIndex == 2 || aLineIndex == 2 && bLineIndex == 1)
	{
		pointIndex = 2;
	}
}
void Nav::Get2PointIndexBy1LineIndex(int lineIndex,  int& pointIndex1, int& pointIndex2)
 {
	 if (lineIndex == 0)
	 {
		 pointIndex1 = 0;
		 pointIndex2 = 1;
	 }
	 else if (lineIndex == 1)
	 {
		 pointIndex1 = 1;
		 pointIndex2 = 2;
	 }
	 else if (lineIndex == 2)
	 {
		 pointIndex1 = 2;
		 pointIndex2 = 0;
	 }
 }

//计算路径消耗
void Nav::InspectTheAdjacentNodes(Navgation::Cell* cell, Navgation::Cell* adjacent, float sqrDistance, const Vector3& endPos)
{
	if (adjacent == NULL)
	{
		return;
	}
	adjacent->costToSource = cell->costToSource + sqrDistance;
	auto G = adjacent->costToSource;
	auto H = Vector3::SqrMagnitude(endPos, adjacent->MidPos);
	adjacent->fValue = G + H;
	adjacent->parent = cell;

	closeList[adjacent->index] = (adjacent);
	openList.push_back(adjacent);
}
//获取两个三角形相邻的2个点

void Nav::GetEqualPoint(Navgation::Cell* a, Navgation::Cell* b, Vector3& v1, Vector3& v2)
{
	for (int i = 0; i < 3; i++)
	{
		auto& n = a->nears[i];
		if (n.Enable)
		{
			if (n.Index == b->index)
			{
				v1 = a->v[n.PointIndex[0]];
				v2 = a->v[n.PointIndex[1]];
			}
		}
	}
}

void Nav::BuildCellPath(Navgation::Cell* startCell, Navgation::Cell* endCell, const Vector3& startPos, const Vector3& endPos, vector<Navgation::Cell*>& cellList) {
	openList.clear();
	closeList.clear();
	cellList.clear();
	for (auto n : FirstPoints) {
		NavPoint_Pool.release_object(n);
	}
	FirstPoints.clear();
	for (auto n : SecondPoints) {
		NavPoint_Pool.release_object(n);
	}
	SecondPoints.clear();
	last = -1;//最后一个点是哪边的 0-first， 1-second

	Navgation::Cell* cell = NULL;
	
	if (startCell != endCell) {
		endCell->fValue = 0;
		endCell->costToSource = 0;

		closeList[endCell->index] = endCell;

		for (int i = 0; i < 3; i++) {
			
			auto& nc = endCell->nears[i];
			if (nc.Enable) {
				auto& ncc = List[nc.Index];
				ncc.InLineIndex = nc.OtherLineIndex;
				ncc.costToSource = Vector3::Distance(endPos, endCell->LineMidPos[i]);

				ncc.parent = endCell;
				openList.push_back(&ncc);
				closeList[ncc.index] = &ncc;
			}
		}

		while (true) {

			//得到离起始点最近的点(如果是第一次执行, 得到的是起点)
			cell = GetMinPathFormOpenList();
			if (cell == NULL || cell == startCell)
			{
				//不到路径
				break;
			}
			
			for (int i = 0; i < 3; i++)
			{
				auto& ncell = cell->nears[i];
				if (ncell.Enable)
				{
					auto& ncc = List[ncell.Index];

					if (closeList.count(ncc.index) == 0)
					{
						auto pointIndex = -1;
						Get1PointIndexBy2LineIndex(cell->InLineIndex, ncell.LineIndex, pointIndex);
						auto sqrDistance = cell->LineMidSqrDistance[pointIndex];

						ncc.InLineIndex = ncell.OtherLineIndex;

						InspectTheAdjacentNodes(cell, &ncc, sqrDistance, startPos);
					}
				}

			}
		}
	}
	else
	{
		cell = endCell;
	}

	
	int lastFirstIndex = 0;
	int lastSecondIndex = 0;
	bool v1equalLastFirstV = false;
	bool v2equalLastSecondV = false;
	lastFirstV.reset();
	lastSecondV.reset();
	while (cell != NULL)
	{
		//把路径点加入到路径列表中
		cellList.push_back(cell);

		auto parent = cell->parent;
		//cell->reset();// = null;

		if (parent != NULL)
		{
			//bool hasadd = false;
			
			v1equalLastFirstV = false;
			v2equalLastSecondV = false;
			GetEqualPoint(cell, parent, V1, V2);

			if (!V1.equal(lastFirstV)) {
				Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();
				navPoint->v = V1;
				navPoint->ConnectIndex = lastSecondIndex;
				FirstPoints.push_back(navPoint);
				lastFirstIndex = FirstPoints.size() - 1;
				lastFirstV = V1;
				last = 0;
			}
			else {
				v1equalLastFirstV = true;
			}
			if (!V2.equal(lastSecondV)) {
				Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();
				navPoint->v = V2;
				navPoint->ConnectIndex = lastFirstIndex;
				SecondPoints.push_back(navPoint);
				lastSecondIndex = SecondPoints.size() - 1;
				lastSecondV = V2;
				last = 1;
			}
			else {
				v2equalLastSecondV = true;
			}
			if (v1equalLastFirstV) {
				FirstPoints[FirstPoints.size() - 1]->ConnectIndex = lastSecondIndex;
			}
			if (v2equalLastSecondV) {
				SecondPoints[SecondPoints.size() - 1]->ConnectIndex = lastFirstIndex;
			}



			//if (FirstPoints.size() == 0)
			//{
			//	Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();// { v = V1, ConnectIndex = 0 };
			//	navPoint->v = V1;
			//	navPoint->ConnectIndex = 0;
			//	FirstPoints.push_back(navPoint);
			//	lastFirst = V1;
			//	hasadd = true;
			//	last = 2;
			//}
			//if (SecondPoints.size() == 0)
			//{
			//	Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();
			//	navPoint->v = V2;
			//	navPoint->ConnectIndex = 0;
			//	SecondPoints.push_back(navPoint);
			//	lastSecond = V2;
			//	hasadd = true;
			//	last = 2;
			//}

			//if (!hasadd)
			//{
			//	if (V1.equal(lastFirst))
			//	{
			//		Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();
			//		navPoint->Index = SecondPoints.size();
			//		navPoint->v = V2;
			//		navPoint->ConnectIndex = FirstPoints.size() - 1;
			//		SecondPoints.push_back(navPoint);
			//		//SecondPoints.Add(new NavPoint(){ Index = SecondPoints.Count, v = V2,  ConnectIndex = firstPoints.Count - 1 });
			//		FirstPoints[FirstPoints.size() - 1]->ConnectIndex = SecondPoints.size() - 1;
			//		//firstPoints[firstPoints.Count - 1].ConnectIndex = SecondPoints.Count - 1;
			//		//firstPoints[firstPoints.Count - 1].ConnectIndexs.Add(SecondPoints.Count - 1);
			//		//SecondPoints[SecondPoints.Count - 1].ConnectIndexs.Add(firstPoints.Count - 1);
			//		lastSecond = V2;
			//		last = 1;
			//		hasadd = true;
			//	}
			//	else if (V1.equal(lastSecond))
			//	{
			//		Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();
			//		navPoint->Index = FirstPoints.size();
			//		navPoint->v = V2;
			//		navPoint->ConnectIndex = SecondPoints.size() - 1;
			//		FirstPoints.push_back(navPoint);
			//		//firstPoints.Add(new NavPoint(){ Index = firstPoints.Count, v = V2, ConnectIndex = SecondPoints.Count - 1 });
			//		SecondPoints[SecondPoints.size() - 1]->ConnectIndex = FirstPoints.size() - 1;
			//		//SecondPoints[SecondPoints.Count - 1].ConnectIndex = firstPoints.Count - 1;
			//		//firstPoints[firstPoints.Count - 1].ConnectIndexs.Add(SecondPoints.Count - 1);
			//		//SecondPoints[SecondPoints.Count - 1].ConnectIndexs.Add(firstPoints.Count - 1);
			//		lastFirst = V2;
			//		last = 0;
			//		hasadd = true;
			//	}
			//}

			//if (!hasadd)
			//{
			//	if (V2.equal(lastFirst))
			//	{
			//		Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();
			//		navPoint->Index = SecondPoints.size();
			//		navPoint->v = V1;
			//		navPoint->ConnectIndex = FirstPoints.size() - 1;
			//		SecondPoints.push_back(navPoint);
			//		FirstPoints[FirstPoints.size() - 1]->ConnectIndex = SecondPoints.size() - 1;
			//		//SecondPoints.Add(new NavPoint(){ Index = SecondPoints.Count, v = V1, ConnectIndex = firstPoints.Count - 1 });
			//		//firstPoints[firstPoints.Count - 1].ConnectIndex = SecondPoints.Count - 1;
			//		//firstPoints[firstPoints.Count - 1].ConnectIndexs.Add(SecondPoints.Count - 1);
			//		//SecondPoints[SecondPoints.Count - 1].ConnectIndexs.Add(firstPoints.Count - 1);
			//		lastSecond = V1;
			//		last = 1;
			//	}
			//	else if (V2.equal(lastSecond))
			//	{
			//		Navgation::NavPoint* navPoint = NavPoint_Pool.acquire_object();
			//		navPoint->Index = FirstPoints.size();
			//		navPoint->v = V1;
			//		navPoint->ConnectIndex = SecondPoints.size() - 1;
			//		FirstPoints.push_back(navPoint);
			//		SecondPoints[SecondPoints.size() - 1]->ConnectIndex = FirstPoints.size() - 1;

			//		//firstPoints.Add(new NavPoint(){ Index = firstPoints.Count, v = V1, ConnectIndex = SecondPoints.Count - 1 });
			//		//SecondPoints[SecondPoints.Count - 1].ConnectIndex = firstPoints.Count - 1;
			//		//firstPoints[firstPoints.Count - 1].ConnectIndexs.Add(SecondPoints.Count - 1);
			//		//SecondPoints[SecondPoints.Count - 1].ConnectIndexs.Add(firstPoints.Count - 1);
			//		lastFirst = V1;
			//		last = 0;
			//	}
			//}
		}

		cell = parent;
	}

	//封尾
	if (last == 0)
	{
		FirstPoints[FirstPoints.size() - 1]->ConnectIndex = SecondPoints.size();
	}
	else if (last == 1)
	{
		SecondPoints[SecondPoints.size() - 1]->ConnectIndex = (FirstPoints.size());
	}

	for (auto& a : closeList) {
		a.second->reset();
	}
}
//返回0 P在中间， 1 F在中间 ， 2 S在中间
int Nav::WhichIsBetween(const Vector3& O/*原点*/, const Vector3& F/*first*/, const Vector3& S/*second*/, const Vector3& P)
{
	if (IsBetween(O, F, S, P))
	{
		return 0;
	}
	else if (IsFirstBetween(O, F, S, P))
	{
		return 1;
	}
	else if (IsSecondBetween(O, F, S, P))
	{
		return 2;
	}
	else
	{
		auto o = O;
		auto FN = Vector3::Normalized(o - F);
		auto PN = Vector3::Normalized(o - P);
		auto SN = Vector3::Normalized(o - S);
		if (FN.equal(PN))
		{
			return 1;
		}
		else if (SN.equal(PN))
		{
			return 2;
		}
		return 1;
	}
}
bool Nav::IsBetween(const Vector3& O/*原点*/,const Vector3& F/*first*/,const Vector3& S/*second*/,const Vector3& P)
{
	return Vector3::SameSide(O, F, S, P) && Vector3::SameSide(O, S, F, P);
}

//是否是first在中间
bool Nav::IsFirstBetween(const Vector3& O/*原点*/, const Vector3& F/*first*/, const Vector3& S/*second*/, const Vector3& P)
{
	if (IsBetween(O, S, P, F))
	{
		return true;
	}
	return false;
}
//是否是second在中间
bool Nav::IsSecondBetween(const Vector3& O/*原点*/, const Vector3& F/*first*/, const Vector3& S/*second*/, const Vector3& P)
{
	if (IsBetween(O, F, P, S))
	{
		return true;
	}
	return false;
}

int Nav::GetFirstI()
{
	return min(firstI, (int)FirstPoints.size() - 2);
}
int Nav::GetFirstStep()
{
	return min(firstI + firstStep + 1, (int)FirstPoints.size() - 1);
}
int Nav::GetFirstStepReal()
{
	return firstI + firstStep + 1;
}
int Nav::GetSecondI()
{
	return min(secondI, (int)SecondPoints.size() - 2);
}
int Nav::GetSecondStep()
{
	return min(secondI + secondStep + 1, (int)SecondPoints.size() - 1);
}
int Nav::GetSecondStepReal()
{
	return secondI + secondStep + 1;
}
bool Nav::IsFirstStepEnd()
{
	return firstI + firstStep + 1 >= (int)FirstPoints.size() - 2;

}
bool Nav::IsSecendStepEnd()
{
	return secondI + secondStep + 1 >= (int)SecondPoints.size() - 2;
}
bool Nav::IsFirstEnd()
{
	return firstI /*+ firstStep + 1 */ >= (int)FirstPoints.size() - 1;

}
bool Nav::IsSecendEnd()
{
	return secondI /*+ secondStep + 1*/ >= (int)SecondPoints.size() - 1;
}


void Nav::BuildPointPath( Vector3 startPos,  Vector3 endPos, vector<Vector3>& pathList) {

	pathList.clear();
	pathList.push_back(startPos);
	//pathList.push_back(startPos);
	if (last == -1)
	{
		pathList.push_back(endPos);
		return;
	}
	auto npf = NavPoint_Pool.acquire_object();
	npf->v = endPos;
	auto nps = NavPoint_Pool.acquire_object();
	nps->v = endPos;

	FirstPoints.push_back(npf);
	SecondPoints.push_back(nps);

	firstI = 0;
	secondI = 0;
	firstStep = 0;
	secondStep = 0;
	firstUntil = 0;
	secondUntil = 0;

	int bi1 = -1;
	int bi2 = -1;


	//判断从那个边开始
	if (FirstPoints[0]->ConnectIndex != 0)
	{
		isFirstQ = false;
		secondUntil = FirstPoints[0]->ConnectIndex;
	}
	else //if (SecondPoints[0]->ConnectIndex != 0)
	{
		isFirstQ = true;
		firstUntil = SecondPoints[0]->ConnectIndex;
	}


	int whileCount = 0;

	while (true)
	{
		//以防死循环
		if (whileCount > 1000)
		{
			g_global.logSys->LogInWindow("寻路失败1000");
			break;
		}
		else if (whileCount == 900) {
			char ch[100];
			sprintf_s(ch, "s:%f,%f e:%f,%f", startPos.x, startPos.z, endPos.x, endPos.z);
			g_global.logSys->LogInWindow(ch, TraceLevel_Exception);
		}
		
		whileCount++;

		//设置导航边开关
		if (isFirstQ)
		{
			if (GetFirstStepReal() > firstUntil)
			{
				isFirstQ = false;

				secondUntil = FirstPoints[GetFirstStep() - 1]->ConnectIndex;

			}
		}
		else
		{
			if (GetSecondStepReal() > secondUntil)
			{
				isFirstQ = true;
				//var ci = SecondPoints[GetSecondStep()-1].ConnectIndex;
				firstUntil = SecondPoints[GetSecondStep() - 1]->ConnectIndex;
			}
		}

		//var firstPointV = 
		//计算向量的相互位置
		bi1 = WhichIsBetween(startPos, FirstPoints[GetFirstI()]->v, SecondPoints[GetSecondI()]->v, FirstPoints[GetFirstStep()]->v);
		bi2 = WhichIsBetween(startPos, FirstPoints[GetFirstI()]->v, SecondPoints[GetSecondI()]->v, SecondPoints[GetSecondStep()]->v);

		//过滤钝角
		if (bi2 == 1)
		{
			//change ex
			if (Vector3::PointinTriangleEX(FirstPoints[GetFirstI()]->v, SecondPoints[GetSecondI()]->v, SecondPoints[GetSecondStep()]->v, startPos))
			{
				bi2 = 2;
			}
		}
		if (bi1 == 2)
		{
			//change ex
			if (Vector3::PointinTriangleEX(FirstPoints[GetFirstI()]->v, SecondPoints[GetSecondI()]->v, FirstPoints[GetFirstStep()]->v, startPos))
			{
				bi1 = 1;
			}
		}
		//如果2个子向量 在2个父向量里面
		if (bi1 == 0 && bi2 == 0)
		{
			if (IsFirstStepEnd() && IsSecendStepEnd())
			{
				break;
			}
			auto bb1 = WhichIsBetween(startPos, SecondPoints[GetSecondI()]->v, SecondPoints[GetSecondStep()]->v, FirstPoints[GetFirstStep()]->v);
			auto bb2 = WhichIsBetween(startPos, FirstPoints[GetFirstI()]->v, FirstPoints[GetFirstStep()]->v, SecondPoints[GetSecondStep()]->v);
			//如果两个子向量的错位，非正常
			if (bb1 == 0 && bb2 == 0)
			{
				//比较那个子向量比较长，设置另一边为拐点
				if (Vector3::SqrMagnitude(FirstPoints[GetFirstStep()]->v, startPos) > Vector3::SqrMagnitude(SecondPoints[GetSecondStep()]->v ,startPos))
				{
					bi1 = 2;
					bi2 = 2;
					secondI = GetSecondStep();
				}
				else
				{
					bi2 = 1;
					bi1 = 1;
					firstI = GetFirstStep();
				}
			}
		}

		//如果子向量在2个父向量中间（2个子向量位置正常）
		if (bi1 == 0 && isFirstQ)//s -- p_f -- f
		{
			firstI += (firstStep + 1);
			firstStep = 0;

		}
		//如果子向量中间隔了另一边的父向量， 则设置另一边为拐点
		if (/*(!IsFirstEnd()||IsSecendEnd()) &&*/ bi2 == 1)//s -- f -- p_s f为拐点
		{
			//如果另一个子向量不在2个父向量中间
			if (bi1 != 0)
			{
				startPos = FirstPoints[GetFirstI()]->v;
				pathList.push_back(startPos);
				firstStep = 0;
				secondStep = 0;
				secondI = FirstPoints[GetFirstI()]->ConnectIndex;
				firstI++;

				if (IsFirstEnd() || IsSecendEnd())
				{
					break;
				}

				secondUntil = secondI;
				firstUntil = firstI;
			}
			else
			{
				//跳过此轮， 等待另一边的计算
				secondUntil = GetSecondStep() - 1;
			}
		}
		//如果子向量中间隔了一个父向量
		else if (bi1 == 1 && isFirstQ)//s -- f -- p_f
		{
			firstStep++;
		}




		if (bi2 == 0 && !isFirstQ)//f -- p_s -- s
		{
			secondI += (secondStep + 1);
			secondStep = 0;
		}

		if (/*(!IsSecendEnd()||IsFirstEnd()) &&*/ bi1 == 2)//p_f -- s -- f， s为拐点
		{
			if (bi2 != 0)
			{
				startPos = SecondPoints[GetSecondI()]->v;
				pathList.push_back(startPos);
				firstStep = 0;
				secondStep = 0;
				firstI = SecondPoints[GetSecondI()]->ConnectIndex;
				secondI++;

				if (IsFirstEnd() || IsSecendEnd())
				{
					break;
				}
				secondUntil = secondI;
				firstUntil = firstI;
			}
			else
			{
				firstUntil = GetFirstStep() - 1;
			}

		}
		else if (bi2 == 2 && !isFirstQ)//p_s -- s -- f
		{
			secondStep++;
		}



	}
	pathList.push_back(endPos);

	for (auto n : FirstPoints) {
		NavPoint_Pool.release_object(n);
	}
	FirstPoints.clear();
	for (auto n : SecondPoints) {
		NavPoint_Pool.release_object(n);
	}
	SecondPoints.clear();
}
Navgation::Cell* Nav::GetCellWitchCross(Navgation::Cell* startCell,const Vector3& V1, const Vector3& V2,  Vector3& VOffset, int lastLineIndex)
{
	for (int i = 0; i < 3; i++)
	{
		if (lastLineIndex == i)
		{
			continue;
		}
		int i1 = -1;
		int i2 = -1;
		Get2PointIndexBy1LineIndex(i,  i1,  i2);

		Vector3& v1 = startCell->v[i1];
		Vector3& v2 = startCell->v[i2];

		if (Vector3::LinesCross(v1, v2, V1, V2))
		{
			if (startCell->nears[i].Enable)
			{
				Navgation::Cell* cell = &List[startCell->nears[i].Index];
				if (Vector3::PointinTriangleEX(cell->v[0], cell->v[1], cell->v[2], V2))
				{
					return cell;
				}
				else
				{
					return GetCellWitchCross(cell,  V1, V2, VOffset, startCell->nears[i].OtherLineIndex);
				}
			}
			else
			{
				VOffset = Vector3::zero;
			}
			break;

		}
	}
	return startCell;
}
int Nav::GetCellIndexAndSetMoveVector(int oldIndex, Vector3 pos,  Vector3& VOffset)
{
	if (oldIndex < 0 || oldIndex >= (int)List.size())
	{
		return GetCellIndex(pos);
	}
	Navgation::Cell& cell = List[oldIndex];
	if (!Vector3::PointinTriangleEX(cell.v[0], cell.v[1], cell.v[2], pos))
	{
		VOffset = Vector3::zero;
		return oldIndex;
	}
	if (VOffset.equal(Vector3::zero))
	{
		return oldIndex;
	}

	Navgation::Cell* finalCell = GetCellWitchCross(&cell, pos, pos + VOffset, VOffset, -1);
	
	return finalCell->index;
}