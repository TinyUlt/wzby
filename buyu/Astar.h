#pragma once
#include <string>
#include <vector>
#include <iostream>
//#include <functional>
#include <stdio.h>  
#include <math.h>
#include <algorithm>
#include "Vector3.h"
#include "gt_buyu.pb.h"
using namespace gt_msg;
using namespace std;
class Astar
{
public:
	Astar();
	~Astar();
};

class DataStruct
{
public:
	int startx;
	int starty;
	int endx;
	int endy;
};
//class Vector2
//{
//public:
//	Vector2() {};
//	Vector2(float x, float y) : x(x), y(y)
//	{
//	}
//	int x;
//	int y;
//};
struct CCSize
{
	int width;
	int height;
};

struct MapXML
{
	std::string m_data;
	CCSize m_size;
};
class PathSprite
{
public:
	PathSprite() :m_parent(NULL),
		m_child(NULL),
		m_costToSource(0),
		m_FValue(0),
		m_startX(0),
		m_startY(0),
		m_endX(0),
		m_endY(0)
	{

	};
public:
	PathSprite * m_parent;//���ڵ�
	PathSprite* m_child;//�ӽڵ�
	float m_costToSource;//����ʼ��ľ���
	int m_x;//��ͼ����
	int m_y;
	float m_FValue;

	int m_startX;//��ʼ��
	int m_startY;

	int m_endX;//������
	int m_endY;

};

class PathSearchInfo
{
public:
	PathSearchInfo(CCSize size, std::vector< std::vector<PathSprite*>> inspectArray) :m_mapSize(size), m_inspectArray(inspectArray) {};
	~PathSearchInfo() {};
	CCSize m_mapSize;
	std::vector< std::vector<PathSprite*>> m_inspectArray;
	//std::vector<Vector2> m_pathList;//·���б�
	std::vector<PathSprite*> m_haveInspectList;//�������б�
	std::vector<PathSprite*> m_openList;//�����б�(���������ڽڵ�)
	//std::function<void(const char*, int, int)> sendData;
	void calculatePath(int startX, int startY, int endX, int endY, std::vector<Vector3>& pathList);

	PathSprite* getMinPathFormOpenList();
	bool removeObjFromOpenList(PathSprite* sprite);

	PathSprite* getObjFromInspectArray(int x, int y);

	void inspectTheAdjacentNodes(PathSprite* node, PathSprite* adjacent, PathSprite* endNode);

	float calculateTwoObjDistance(PathSprite* obj1, PathSprite* obj2);
	void clearPath();
	void resetInspectArray();

};

class createMapData
{
public:
	//MapXML m_mapXml;
	std::vector< std::vector<PathSprite*>> m_inspectArray;
	createMapData(MapGroup* map);
	
};