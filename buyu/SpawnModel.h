#pragma once
#include "PosModel.h"
#include "TimerModel.h"
#include <vector>
using namespace std;
class MessageModel;

class SpawnModel
{
public:
	SpawnModel();
	~SpawnModel();

	void Bind(MessageModel* message);
	void Init(
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
	);
	void Update(int frame);
	void Create(
		int itemId,
		int frame,
		LONGLONG score,
		int experience,
		int lv,
		int multiple,
		vector<int>& mulList
	);
	PosModel Pos;
	TimerModel Timer;
	TimerModel LineTimer;
	//vector<TimerModel> TimerList;
	//ItemCache* ItemManager;
	MessageModel* Message;
	
	//SpawnExMessage Pack;
	void SubCount();
	int Id;
	ItemTeam TeamId;
	int MonsterType;
	int MaxCount;
	int Duration;

	int Count;
	int LineCount;

	bool MoveEnable;
	bool FreedomEnable;
	bool AttackEnable;
	bool BeatenEnable;
	bool FollowEnable;
	bool FrozenEnable;
	bool EventNotifyEnabel;
	bool HPEnable;
	bool LVEnable;
	bool AutoAttack;
	int NowFrame;
	int Seed;
};

