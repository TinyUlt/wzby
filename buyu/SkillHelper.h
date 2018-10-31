#pragma once
#include "BulletModel.h"
#include "FrozenSkillModel.h"
#include "PoFuChenZhouSkillModel.h"
#include "BaWangZhanSkillModel.h"
#include "ChongFengXianZhenSkillModel.h"
#include "HealSkillModel.h"
#include "SpeedUpSkillModel.h"
#include "ObjectPool.h"

#include <string.h>
using namespace std;
class SkillBaseModel;
class SkillHelper
{
public:
	SkillHelper();
	~SkillHelper();

	void InitSkillConfig(string fname);
	void InitSkillBuf(string fname);
	void InitSkillEffectConfig(string fname);
	void InitLearnSkill(string fname);
	bool IsSkill(int id);
	bool TryGetSkillConfig(int id, Proto_Skill** skill);
	bool TryGetCastdistance(int id, float& distance);
	bool TryGetSkillEffectConfig(int id, Proto_SkillEffect** skill);
	bool TryGetCoolingTime(int id, int& time);
	bool TryGetSkillGroup(int monsterType, map<int, SkillBaseModel*>& skillGroup);
	Proto_SkillList PKL;
	Proto_BufList BUF;
	Proto_SkillEffectList PKE;
	Proto_LearnSkillList LearnSkillList;

	ObjectPool<BulletModel> BulletPool;
	ObjectPool<FrozenSkillModel> FrozenSkillPool;
	ObjectPool<PoFuChenZhouSkillModel> PoFuChenZhouSkillPool;
	ObjectPool<BaWangZhanSkillModel> BaWangZhanSkillPool;
	ObjectPool<ChongFengXianZhenSkillModel> ChongFengXianZhenSkillPool;
	ObjectPool<HealSkillModel> HealSkilllPool;
	ObjectPool<SpeedUpSkillModel>SpeedUpSkillPool;

	map<int, Proto_Skill*> IdToSkill;
	map<int, Proto_SkillEffect*> IdToSkillEffect;
	map<int, Proto_Buf*> IdToBuf;
	map<int, vector<int>> TypeToLearnSkillsId;
};