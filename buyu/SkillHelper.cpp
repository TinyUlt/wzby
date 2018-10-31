#include "Global.h"
#include "SkillHelper.h"
#include "LogSys.h"
#include "MonsterHelper.h"
SkillHelper::SkillHelper()
{
}


SkillHelper::~SkillHelper()
{
}

void SkillHelper::InitSkillConfig(string fname) {
	fstream input(fname, ios::in | ios::binary);
	if (!input) {
		g_global.logSys->LogInWindow(fname + "加载失败");
		return;
	}
	//Proto_MonsterList pml;
	PKL.ParseFromIstream(&input);

	auto size = PKL.dic_size();
	for (int i = 0; i < size; ++i)
	{
		Proto_Skill* pm = PKL.mutable_dic(i);
		auto id = pm->id();
		
		IdToSkill[id] = pm;
	}
	g_global.logSys->LogInWindow(fname + "加载成功");
}
void SkillHelper::InitSkillBuf(string fname) {
	fstream input(fname, ios::in | ios::binary);
	if (!input) {
		g_global.logSys->LogInWindow(fname + "加载失败");
		return;
	}
	BUF.ParseFromIstream(&input);
	auto size = BUF.dic_size();
	for (int i = 0; i < size; ++i)
	{
		Proto_Buf* pm = BUF.mutable_dic(i);
		auto id = pm->id();

		IdToBuf[id] = pm;
	}
	g_global.logSys->LogInWindow(fname + "加载成功");
}
void SkillHelper::InitSkillEffectConfig(string fname) {
	fstream input(fname, ios::in | ios::binary);
	if (!input) {
		g_global.logSys->LogInWindow(fname + "加载失败");
		return;
	}
	//Proto_MonsterList pml;
	PKE.ParseFromIstream(&input);

	auto size = PKE.dic_size();
	for (int i = 0; i < size; ++i)
	{
		Proto_SkillEffect* pm = PKE.mutable_dic(i);
		auto id = pm->id();

		IdToSkillEffect[id] = pm;
	}
	g_global.logSys->LogInWindow(fname + "加载成功");
}
void SkillHelper::InitLearnSkill(string fname) {
	fstream input(fname, ios::in | ios::binary);
	if (!input) {
		g_global.logSys->LogInWindow(fname + "加载失败");
		return;
	}
	LearnSkillList.ParseFromIstream(&input);
	auto size = LearnSkillList.dic_size();
	for (int i = 0; i < size; ++i) {
		Proto_LearnSkill* ls = LearnSkillList.mutable_dic(i);
		
		for (int j = 0; j < ls->mutable_fixedskill()->size(); j++) {
			TypeToLearnSkillsId[ls->type()].push_back(ls->mutable_fixedskill(j)->id());
		}
		for (int k = 0; k < ls->mutable_learnskill()->size(); k++) {
			TypeToLearnSkillsId[ls->type()].push_back(ls->mutable_learnskill(k)->id());
		}
		
	}
	g_global.logSys->LogInWindow(fname + "加载成功");
}
bool SkillHelper::IsSkill(int id) {

	return
		id == Skill_Frozen ||
		id == Skill_PoFuChenZhou;
}
bool SkillHelper::TryGetSkillConfig(int id, Proto_Skill** skill) {
	if (IdToSkill.count(id) == 0) {
		return false;
	}
	*skill = IdToSkill[id];
	return true;
}
bool SkillHelper::TryGetCastdistance(int id, float& distance) {
	Proto_Skill* skillConfig = NULL;
	if (!TryGetSkillConfig(id, &skillConfig)) {
		return false;
	}

	distance = skillConfig->castdistance() + skillConfig->levcastdistance();
	return true;

}
bool SkillHelper::TryGetCoolingTime(int id, int& time) {
	Proto_Skill* skillConfig = NULL;
	if (!TryGetSkillConfig(id, &skillConfig)) {
		return false;
	}
	time = skillConfig->coolingtime();
	return true;
}
bool SkillHelper::TryGetSkillEffectConfig(int id, Proto_SkillEffect** skill) {
	if (IdToSkillEffect.count(id) == 0) {
		return false;
	}
	*skill = IdToSkillEffect[id];
	return true;
}
bool SkillHelper::TryGetSkillGroup(int monsterType, map<int, SkillBaseModel*>& skillGroup) {
	/*vector<int> list;
	if (!g_global.monsterHelper->TryGetSkillsId(monsterType, list)) {
		return false;
	}*/

	for (auto id : TypeToLearnSkillsId[monsterType]) {
		
		if (Skill_Frozen == id ) {
			auto frozenData = g_global.skillHelper->FrozenSkillPool.acquire_object();
			auto skill = IdToSkill[id];
			frozenData->Init(true,skill->coolingtime(), skill->castdistance());
			skillGroup[id] = frozenData;
		}
		else if (Skill_Heal == id) {
			auto data = g_global.skillHelper->HealSkilllPool.acquire_object();
			auto skill = IdToSkill[id];
			int bufId = skill->mutable_bufflist()->id();
			auto dmg = IdToBuf[bufId]->damage();
			data->Init(true, skill->coolingtime(), dmg);
			skillGroup[id] = data;
		}
		else if (Slill_SpeedUp == id) {
			auto data = g_global.skillHelper->SpeedUpSkillPool.acquire_object();
			auto skill = IdToSkill[id];

			data->Init(true, skill->coolingtime());
			skillGroup[id] = data;
		}
		else if (Skill_PoFuChenZhou == id) {
			auto pofuchenzhouData = g_global.skillHelper->PoFuChenZhouSkillPool.acquire_object();
			auto skill = IdToSkill[id];
			pofuchenzhouData->Init(true, skill->coolingtime(), skill->castdistance());
			skillGroup[id] = pofuchenzhouData;
		}
		else if (Skill_BaWangZhan == id) {
			auto data = g_global.skillHelper->BaWangZhanSkillPool.acquire_object();
			auto skill = IdToSkill[id];
			data->Init(true, skill->coolingtime(), skill->range(), skill->castdistance());
			skillGroup[id] = data;
		}
		else if (Skill_ChongFengXianZhen == id) {
			auto data = g_global.skillHelper->ChongFengXianZhenSkillPool.acquire_object();
			auto skill = IdToSkill[id];
			data->Init(true, skill->coolingtime(), 1, skill->castdistance());
			skillGroup[id] = data;
		}
	}
	return !skillGroup.empty();
}