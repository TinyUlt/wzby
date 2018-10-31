#include "Global.h"
#include "MonsterHelper.h"

#include "LogSys.h"


MonsterHelper::MonsterHelper()
{
}


MonsterHelper::~MonsterHelper()
{
}

void MonsterHelper::Init() {

}
void MonsterHelper::InitConfig(string fname) {

	fstream input(fname, ios::in | ios::binary);
	if (!input) {
		g_global.logSys->LogInWindow(fname + "加载失败");
		return;
	}
	//Proto_MonsterList pml;
	PML.ParseFromIstream(&input);

	auto size = PML.dic_size();
	for (int i = 0; i < size; ++i)
	{
		Proto_Monster* pm = PML.mutable_dic(i);
		auto type = pm->type();
		auto name = pm->modlename();
		auto multiple = pm->scal();
		//TypeToName[type] = name;
		NameToType[name] = type;
		//TypeToMultiple[type] = multiple;
		TypeToMonster[type] = pm;
	}
	g_global.logSys->LogInWindow(fname + "加载成功");


}
bool MonsterHelper::IsContainMonsterByType(int type) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}

	return true;
}
bool MonsterHelper::TryGetMonsterConfig(int type, Proto_Monster** monster) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}
	*monster = TypeToMonster[type];
	return true;
}
bool MonsterHelper::TryGetTypeByName(string name, int& type){
	if (NameToType.count(name) == 0) {
		return false;
	}

	type = NameToType[name];
	return true;
}
bool MonsterHelper::TryGetNameByType(int type, string& name) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}

	name = TypeToMonster[type]->modlename();
	return true;
}
bool MonsterHelper::TryGetMultipleByType(int type, int& multiple) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}

	multiple = TypeToMonster[type]->scal();
	return true;
}
bool MonsterHelper::TryGetMonster(ItemModel** monster) {

	*monster = MonsterPool.acquire_object();
	return true;
}
bool MonsterHelper::RebackMonster(ItemModel* monster) {

	MonsterPool.release_object(monster);
	return true;
}
bool MonsterHelper::TryGetAttackDistance(int type, float& distance) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}
	distance = TypeToMonster[type]->actiondistance();
	return true;
}
bool MonsterHelper::TryGetAttackInteval(int type, float& interval) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}

	interval = TypeToMonster[type]->minactiontime()*60;
	return true;
}
bool MonsterHelper::TryGetMoveSpeed(int type, float& speed) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}

	speed = TypeToMonster[type]->movespeed()/60.0f;

	return true;
}
bool MonsterHelper::TryGetExp(int type, int& exp) {
	if (TypeToMonster.count(type) == 0) {
		return false;
	}
	exp = TypeToMonster[type]->exp();
	return exp;
}
bool MonsterHelper::TryGetActiontime(int type, float& actiontime) {
	Proto_Monster* config = NULL;
	if (!TryGetMonsterConfig(type, &config)) {
		return false;
	}

	actiontime = config->minactiontime();
	return true;
}
//bool MonsterHelper::TryGetSkillsId(int type, vector<int>& skillId) {
//	Proto_Monster* config = NULL;
//	if (!TryGetMonsterConfig(type, &config)) {
//		return false;
//	}
//	for (int i = 0; i < config->skilllist_size(); i++) {
//		skillId.push_back(config->mutable_skilllist(i)->id());
//	}
//	
//	return true;
//}
bool MonsterHelper::TryGetMaxHP(int type, int& hp) {
	Proto_Monster* config = NULL;
	if (!TryGetMonsterConfig(type, &config)) {
		return false;
	}

	hp = config->maxhp();
	return true;
}
bool MonsterHelper::TryGetDMG(int type, int& dmg) {
	Proto_Monster* config = NULL;
	if (!TryGetMonsterConfig(type, &config)) {
		return false;
	}

	dmg = config->attack();
	return true;
}
bool MonsterHelper::TryGetSkillsId(int type, vector<int>& list) {
	Proto_Monster* config = NULL;
	if (!TryGetMonsterConfig(type, &config)) {
		return false;
	}

	for (int i = 0; i < config->skilllist_size(); i++) {
		auto data = config->mutable_skilllist(i);
		list.push_back(data->id());
	}

	return !list.empty();
}