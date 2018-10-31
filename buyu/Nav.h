#pragma once
#include "gt_buyu.pb.h"
#include "Vector3.h"
#include <vector>
#include <map>
#include "ObjectPool.h"
#include <random>
using namespace gt_msg;
using namespace std;

namespace Navgation {
	class Near {
	public:
		bool Enable;
		int Index;////��������
		float Distance;//����������ľ���
		int PointIndex[2];//���ڵĵ�����
		int LineIndex;//���ڵı�
		int OtherLineIndex;//�������������ڵı�
	};
	class Cell {
	public:
		int index = -1;//��������
		Vector3 v[3];// �����
		Vector3 MidPos;//���ĵ�
		Vector3 LineMidPos[3];//�����ĵ�
		Vector3 Normalize[3];//�����ĵ�
		float LineMidSqrDistance[3];//���߾���
		vector<Near> nears;//��������

		float costToSource;//��Դ�ľ���
		float fValue;//����ֵ
		Cell* parent;//���ڵ�
		int InLineIndex;//�����
		Cell() {
			reset();
		}
		void reset() {
			costToSource = 0;
			fValue = 0;
			parent = NULL;
			InLineIndex = -1;
		}
	};
	class NavPoint
	{
	public:
		int Index;//�б��е�����
		Vector3 v;//�õ�����
		int ConnectIndex;//������ӵ���һ�ߵĵ�����
		NavPoint() {
			reset();
		}
		void reset() {
			Index = -1;
			ConnectIndex = -1;
		}
	};
}


class Nav
{
public:
	Nav();
	~Nav();
	void Init(gt_msg::NavData & data);
	void RandomCellIndex(std::default_random_engine& r,int& index, Vector3& pos);
	int GetCellIndex(const Vector3& pos);
	int GetCellIndex(Vector3& pos, vector<Navgation::Cell*>& cellList);
	bool tryGetCellInCellListByPos(Vector3& pos, vector<Navgation::Cell*>& cellList, Navgation::Cell** cell);

	bool TryGetPath( Vector3& startPos, Vector3& endPos, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList);
	bool TryGetPath(int startCellIndex, int endCellIndex, const Vector3& startPos, const Vector3& endPos, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList);
	bool TryGetPath(Navgation::Cell* startCell, Navgation::Cell* endCell, const Vector3& startPos, const Vector3& endPos, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList);
	bool TryGetPath(Vector3& startPos, const Vector3& endPos, int endCellIndex, vector<Vector3>& pathList, vector<Navgation::Cell*>& cellList);
	void BuildCellPath(Navgation::Cell* startCell, Navgation::Cell* endCell, const Vector3& startPos, const Vector3& endPos, vector<Navgation::Cell*>& cellList);
	void Get1PointIndexBy2LineIndex(int aLineIndex, int bLineIndex, int& pointIndex);
	void Get2PointIndexBy1LineIndex(int lineIndex, int& pointIndex1, int& pointIndex2);
	void InspectTheAdjacentNodes(Navgation::Cell* cell, Navgation::Cell* adjacent, float distance, const Vector3& endPos);
	void GetEqualPoint(Navgation::Cell* a, Navgation::Cell* b, Vector3& v1, Vector3& v2);
	void BuildPointPath( Vector3 startPos,  Vector3 endPos, vector<Vector3>& pathList);
	int WhichIsBetween(const Vector3& O/*ԭ��*/,const Vector3& F/*first*/,const Vector3& S/*second*/, const Vector3& P);
	bool IsBetween(const Vector3& O/*ԭ��*/, const Vector3& F/*first*/, const Vector3& S/*second*/, const Vector3& P);
	bool IsFirstBetween(const Vector3& O/*ԭ��*/, const Vector3& F/*first*/, const Vector3& S/*second*/, const Vector3& P);
	bool IsSecondBetween(const Vector3& O/*ԭ��*/, const Vector3& F/*first*/, const Vector3& S/*second*/, const Vector3& P);
	int GetCellIndexAndSetMoveVector(int oldIndex,  Vector3 pos, Vector3& VOffset);
	int GetFirstI();
	int GetFirstStep();
	int GetFirstStepReal();
	int GetSecondI();
	int GetSecondStep();
	int GetSecondStepReal();
	bool IsFirstStepEnd();
	bool IsSecendStepEnd();
	bool IsFirstEnd();
	bool IsSecendEnd();
	Navgation::Cell* GetMinPathFormOpenList();
	Navgation::Cell* GetCellInCellListByPos(const Vector3& pos, vector<Navgation::Cell*>& cellList);
	Navgation::Cell* GetCellWitchCross(Navgation::Cell* startCell, const Vector3& V1, const Vector3& V2, Vector3& VOffset, int lastLineIndex);
	//void RemoveObjFromOpenList(Navgation::Cell*);

	ObjectPool<Navgation::NavPoint> NavPoint_Pool;

	vector<Navgation::Cell> List;
	vector<Navgation::NavPoint*> FirstPoints;
	vector<Navgation::NavPoint*> SecondPoints;
	map<int, Navgation::Cell*> closeList;
	vector<Navgation::Cell*> openList;
	//vector<Navgation::Cell*> cellList;
	vector<Vector3> FinalPath;
	int ListCount;

	Vector3 lastFirstV;
	Vector3 lastSecondV;
	
	Vector3 V1;
	Vector3 V2;

	int firstI;//��һ��������
	int secondI ;//�ڶ���������
	int firstStep;//��һ������Ծ���
	int secondStep;//�ڶ�������Ծ���
	int firstUntil;//��һ������󵽴�����
	int secondUntil;//�ڶ�������󵽴�����
	bool isFirstQ;//ִ�е�һ����
	int last;//���ĵ�����
};

