#include "Astar.h"



Astar::Astar()
{
}


Astar::~Astar()
{
}

void PathSearchInfo::calculatePath(int startX, int startY, int endX, int endY, std::vector<Vector3>& pathList)//����·��
{
	pathList.clear();
	clearPath();
#ifndef NOMAL_SEARCH_PATH
	//�õ���ʼ��Ľڵ�
	PathSprite*    _endNode = m_inspectArray[startX][startY];
	if (_endNode == NULL) {
		return;
	}
	//�õ�������Ľڵ�
	PathSprite*   _startNode = m_inspectArray[endX][endY];
	if (_startNode == NULL) {
		return;
	}
	//��Ϊ�ǿ�ʼ�� �ѵ���ʼ��ľ�����Ϊ0, FֵҲΪ0
	_startNode->m_costToSource = 0;
	_startNode->m_FValue = 0;

	//���Ѿ������ĵ�Ӽ���б���ɾ��
	m_inspectArray[endX][endY] = NULL;
	//�Ѹõ�����Ѿ���������б���
	m_haveInspectList.push_back(_startNode);
	//Ȼ����뿪���б�
	m_openList.push_back(_startNode);

	PathSprite* _node = NULL;
	while (true)
	{
		//�õ�����ʼ������ĵ�(����ǵ�һ��ִ��, �õ��������)
		_node = getMinPathFormOpenList();
		if (!_node)
		{
			//����·��
			break;
		}
		//�Ѽ�����ĵ�ӿ����б���ɾ��
		removeObjFromOpenList(_node);
		int _x = _node->m_x;
		int _y = _node->m_y;

		//
		if (_x == startX && _y == startY)
		{
			break;
		}

		//���8����������ڽڵ��Ƿ���Է��뿪���б���

		PathSprite* _adjacent = NULL;

		_adjacent = getObjFromInspectArray(_x + 1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x - 1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x + 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x + 1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x - 1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x - 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);


	}

	while (_node)
	{
		//��·������뵽·���б���
		pathList.push_back(Vector3((float)(_node->m_x+0.5), 0,(float) (_node->m_y+0.5)));
		_node = _node->m_parent;
	}
#else
	//�õ���ʼ��Ľڵ�
	PathSprite*   _startNode = m_inspectArray[startX][startY];
	//�õ�������Ľڵ�
	PathSprite*  _endNode = m_inspectArray[endX][endY];

	//��Ϊ�ǿ�ʼ�� �ѵ���ʼ��ľ�����Ϊ0, FֵҲΪ0
	_startNode->m_costToSource = 0;
	_startNode->m_FValue = 0;

	//���Ѿ������ĵ�Ӽ���б���ɾ��
	m_inspectArray[startX][startY] = NULL;
	//�Ѹõ�����Ѿ���������б���
	m_haveInspectList.push_back(_startNode);
	//Ȼ����뿪���б�
	m_openList.push_back(_startNode);

	PathSprite* _node = NULL;
	while (true)
	{
		//�õ�����ʼ������ĵ�(����ǵ�һ��ִ��, �õ��������)
		_node = getMinPathFormOpenList();
		if (!_node)
		{
			break;
		}
		//�Ѽ�����ĵ�ӿ����б���ɾ��
		removeObjFromOpenList(_node);
		int _x = _node->m_x;
		int _y = _node->m_y;

		//
		if (_x == endX && _y == endY)
		{
			break;
		}

		//���8����������ڽڵ��Ƿ���Է��뿪���б���
		PathSprite* _adjacent = NULL;

		_adjacent = getObjFromInspectArray(_x + 1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x - 1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x + 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x + 1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x - 1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(_x - 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);


	}

	while (_node)
	{
		//��·������뵽·���б���
		m_pathList.insert(m_pathList.begin(), Vector2(_node->m_x, _node->m_y));
		_node = _node->m_parent;
	}

#endif
	/*Vector2  _pArray[200];
	for (int i = 0; i < m_pathList.size(); i++)
	{
	_pArray[i] = m_pathList[i];
	}
	sendData((const char*)&_pArray, sizeof(Vector2)*m_pathList.size(), NULL);*/
}

PathSprite* PathSearchInfo::getMinPathFormOpenList()
{
	if (m_openList.size()>0) {
		PathSprite* _sp = *m_openList.begin();
		for (std::vector<PathSprite*>::iterator iter = m_openList.begin(); iter != m_openList.end(); iter++)
		{
			if ((*iter)->m_FValue < _sp->m_FValue)
			{
				_sp = *iter;
			}
		}
		return _sp;
	}
	else
	{
		return NULL;
	}

}
bool PathSearchInfo::removeObjFromOpenList(PathSprite* sprite)
{
	if (!sprite) {
		return  false;
	}
	for (std::vector<PathSprite*>::iterator iter = m_openList.begin(); iter != m_openList.end(); iter++)
	{
		if (*iter == sprite)
		{
			m_openList.erase(iter);
			return true;
		}
	}
	return false;

}

PathSprite* PathSearchInfo::getObjFromInspectArray(int x, int y)
{
	if (x >= 0 && y >= 0 && x < m_mapSize.width && y < m_mapSize.height) {
		return m_inspectArray[x][y];
	}
	return  NULL;
}

void PathSearchInfo::inspectTheAdjacentNodes(PathSprite* node, PathSprite* adjacent, PathSprite* endNode)
{
	if (adjacent)
	{
		float _x =float( abs(endNode->m_x - adjacent->m_x));
		float _y =float( abs(endNode->m_y - adjacent->m_y));

		float F, G, H1, /*H2,*/ H3;
		adjacent->m_costToSource = node->m_costToSource + calculateTwoObjDistance(node, adjacent);//����ۼƵ�·��
		G = adjacent->m_costToSource;

		//�����㷨, �о�H2����
		H1 = _x + _y;

		H3 = max(_x, _y);

#if 1 //A*�㷨 = Dijkstra�㷨 + �����������
		F = G + H1;
#endif
#if 0//Dijkstra�㷨
		F = G;
#endif
#if 0//�����������
		H2 = hypot(_x, _y);
		F = H2;
#endif
		adjacent->m_FValue = F;

		adjacent->m_parent = node;//���ø��ڵ�


		m_haveInspectList.push_back(adjacent);
		node->m_child = adjacent;//�����ӽڵ�

		PathSearchInfo::m_inspectArray[adjacent->m_x][adjacent->m_y] = NULL;//�Ѽ����ĵ�Ӽ���б���ɾ��
		PathSearchInfo::m_openList.push_back(adjacent);//���뿪���б�
	}
}

float PathSearchInfo::calculateTwoObjDistance(PathSprite* obj1, PathSprite* obj2)
{

	float _x =float( abs(obj2->m_x - obj1->m_x));
	float _y =float( abs(obj2->m_y - obj1->m_y));

	return _x + _y;
}

void PathSearchInfo::clearPath()
{
	resetInspectArray();

	//���Ƴ����ϰ���ĵ�ͼ�������б���
	m_openList.clear();
	m_haveInspectList.clear();

}
void PathSearchInfo::resetInspectArray()
{
	for (std::vector<PathSprite*>::iterator iter = m_haveInspectList.begin(); iter != m_haveInspectList.end(); iter++)
	{
		(*iter)->m_costToSource = 0;
		(*iter)->m_FValue = 0;
		(*iter)->m_parent = NULL;
		(*iter)->m_child = NULL;

		m_inspectArray[(*iter)->m_x][(*iter)->m_y] = (*iter);
	}
}
createMapData::createMapData(MapGroup* map)
{
	//getMapdataFromXML(mapPath);

	//std::string & _str = m_mapXml.m_data;
	int  _width = 100;
	int  _height = 100;
	int index = 0;

	for (int j = 0; j < _width; j++) {
		std::vector<PathSprite*> _pathSprite;
		m_inspectArray.push_back(_pathSprite);
		for (int i = 0; i < _height; i++) {
			index = j * _height + i;
			if (map->mutable_pathlist()->Get(index)==1) {

				PathSprite* _pathSprite = new PathSprite();
				_pathSprite->m_x = j;
				_pathSprite->m_y = i;

				m_inspectArray[j].push_back(_pathSprite); //�ѵ�ͼ�����еĵ�һһ��Ӧ�������б���
			}
			else
			{
				m_inspectArray[j].push_back(NULL);
			}
		}
	}
}