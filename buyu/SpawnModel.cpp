#include "Global.h"
#include "SpawnModel.h"
#include "PathHelper.h"
//#include "ItemCache.h"
#include "MessageModel.h"
#include "Global.h"
#include "MonsterHelper.h"
#include "SkillHelper.h"
#include "MessageHelper.h"
#include "SkillBaseModel.h"
SpawnModel::SpawnModel()
{

}


SpawnModel::~SpawnModel()
{
}
void SpawnModel::Bind(MessageModel* message) {
	Message = message;
	
}
void SpawnModel::Init(
	int id,
	ItemTeam teamId,
	Vector3 bornPos,
	int type,
	int maxCount,
	int duration,
	int lineCount,
	bool moveEnable,
	bool freedomEnable,
	bool attackEnable,
	bool beatenEnable,
	bool followEnable,
	bool frozenEnable,
	bool eventNotifyEnabel,
	bool hpEnable,
	bool lvEnable,
	bool autoAttack
) {
	Id = id;
	TeamId = teamId;
	Count = 0;
	Pos.Position = bornPos;
	Pos.CellIndex = g_global.pathHelper->GetCellIndex(bornPos);
	MonsterType = type;
	MaxCount = maxCount;
	Duration = duration;
	
	LineCount = lineCount;
	Timer.SetInterval(Duration);
	LineTimer.SetInterval(0, 0, 0, 0);

	MoveEnable = moveEnable,
	FreedomEnable = freedomEnable;
	AttackEnable = attackEnable;
	BeatenEnable = beatenEnable;
	FollowEnable = followEnable;
	FrozenEnable = frozenEnable;
	EventNotifyEnabel = eventNotifyEnabel;
	HPEnable = hpEnable;
	LVEnable = lvEnable;
	//ClientFrameEnable = clientFrameEnable;
	AutoAttack = autoAttack;
}
void SpawnModel::Create(
	int itemId,
	int frame, 
	LONGLONG score, 
	int experience, 
	int lv, 
	int multiple,
	vector<int>& mulList)
{

	vector<int> skillsId;
	if (!g_global.monsterHelper->TryGetSkillsId(MonsterType, skillsId)) {
		return;
	}
	float moveSpeed = 0;
	if (!g_global.monsterHelper->TryGetMoveSpeed(MonsterType, moveSpeed)) {
		return;
	}
	float actiontime = 0;
	if (!g_global.monsterHelper->TryGetActiontime(MonsterType, actiontime)) {
		return;
	}
	int dmg = 0;
	if (!g_global.monsterHelper->TryGetDMG(MonsterType, dmg)) { 
		return;
	}
	int hp = 0;
	if (!g_global.monsterHelper->TryGetMaxHP(MonsterType, hp)) {
		return;
	}
	float distance = 0;
	if (!g_global.skillHelper->TryGetCastdistance(skillsId[0], distance)) {
		return;
	}

	map<int, SkillBaseModel*> skillGroup;
	if (!g_global.skillHelper->TryGetSkillGroup(MonsterType, skillGroup)) {
		//return;
	}

	SpawnMessage* msg = g_global.messageHelper->Get_SpawnMessage();
	msg->ItemId = itemId;
	msg->TeamId = TeamId;
	msg->Frame = frame;
	msg->Seed = Seed;
	msg->Type = MonsterType;
	msg->Score = score;
	msg->HP = hp;
	msg->EXP = experience;
	msg->LV = lv;
	msg->DMG = dmg;
	msg->Pos = Pos.Position;
	msg->SpawnId = Id;
	msg->CellIndex = Pos.CellIndex;
	msg->MoveEnable = MoveEnable;
	msg->FreedomEnable = FreedomEnable;
	msg->AttackEnable = AttackEnable;
	msg->BeatenEnable = BeatenEnable;
	msg->FollowEnable = FollowEnable;
	msg->FrozenEnable = FrozenEnable;
	msg->EventNotifyEnable = EventNotifyEnabel;
	msg->AutoAttack = AutoAttack;
	msg->Actiontime =int(actiontime * 60);
	msg->Castdistance = distance;
	msg->MoveSpeed = moveSpeed;
	msg->SkillsId = skillsId;
	msg->HPEnable = HPEnable;
	msg->LVEnable = LVEnable;
	msg->SkillPack = skillGroup;
	msg->Multiple = multiple;
	msg->MulList = mulList;
	Message->SendSpawnItem(msg);
}
void SpawnModel::Update(int frame) {
	NowFrame = frame;
	if (MaxCount > Count) {
		if (Timer.Update(frame)) {
			Seed = rand();
			LineTimer.SetInterval(30, frame, LineCount);
		}
	}

	if (LineTimer.Update(frame)) {
		vector<int > list;
		Create(-1, g_global.GetExecuteDelayFrameForServer(NowFrame), 5, -1, 1, 0, list);
		Count++;
	}
}
void SpawnModel::SubCount() {
	Count--;
	Timer.SetInterval(Duration, NowFrame);
}
