#pragma once
#include<string>
//#include "gt_buyu.pb.h"
#include "ObjectPool.h"
#include "ItemModel.h"
//#include "MonsterPro.h"
//class Monster;
//using namespace gt_msg;
using namespace std;


class MonsterHelper
{
public:
	MonsterHelper();
	~MonsterHelper();

	void Init();
	void InitConfig(string fname);

	bool IsContainMonsterByType(int type);
	bool TryGetMonster(ItemModel** monster);
	bool TryGetMonsterConfig(int type, Proto_Monster** monster);
	bool TryGetTypeByName(string name, int& type);
	bool TryGetNameByType(int type, string& name);
	bool TryGetMultipleByType(int type, int& multiple);
	bool TryGetAttackDistance(int type, float& distance);//米
	bool TryGetAttackInteval(int type, float& interval);//帧
	bool TryGetMoveSpeed(int type, float& speed);//米/帧
	bool TryGetExp(int type, int& exp);//经验
	//bool TryGetMoveSpeed(int type, float& speed);
	bool TryGetActiontime(int type, float& actiontime);
	bool TryGetSkillsId(int type, vector<int>& skillId);
	bool TryGetMaxHP(int type, int& hp);
	bool TryGetDMG(int type, int& dmg);
	//bool TryGetSkillsId(int type, vector<int>& list);
	bool RebackMonster(ItemModel* monster);
	/*bool TryGetMonsterPro(MonsterPro** monster);
	bool RebackMonsterPro(MonsterPro* monster);*/
private:
	//鱼对象池
	ObjectPool<ItemModel> MonsterPool;
	//ObjectPool<MonsterPro> MonsterProPool;

	map<string, int> NameToType;
	//map<int, string> TypeToName;
	//map<int, int>  TypeToMultiple;
	map<int, Proto_Monster*> TypeToMonster;
	Proto_MonsterList PML;
};

