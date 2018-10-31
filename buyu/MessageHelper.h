#pragma once
#include "gt_buyu.pb.h"
#include "ObjectPool.h"
#include "typedefine.h"
#include "Vector3.h"
#include "SkillBaseModel.h"
using namespace gt_msg;
using namespace std;
#define MESSAGEFUC(TYPE) ObjectPool<TYPE> TYPE##_Pool;\
TYPE* Get_##TYPE()\
{\
	auto pack = TYPE##_Pool.acquire_object(); \
	pack->Clear();\
	return pack;\
}\
TYPE* Get_##TYPE(void* data, unsigned short data_size)\
{\
	auto pack = Get_##TYPE();\
	pack->ParseFromArray(data, data_size);\
	return pack;\
}\
void Back_##TYPE(TYPE* data){ TYPE##_Pool.release_object(data);}

#define POOLFUC(TYPE) ObjectPool<TYPE> TYPE##_Pool;\
TYPE* Get_##TYPE()\
{\
	auto pack = TYPE##_Pool.acquire_object(); \
	return pack;\
}\
void Back_##TYPE(TYPE* data){ TYPE##_Pool.release_object(data);}


class TobeMessage{
public:
	MSG_ID id;
	int frame;
	void* msg;
};
class SpawnMessage {
public:
	string NickName;
	DWORD GameId;
	DWORD UserId;
	//int Id;
	int Frame;
	int TeamId;
	int Type;
	LONGLONG Score;
	int HP;
	int EXP;
	int LV;
	int DMG;
	int Multiple;
	vector<int> MulList;
	Vector3 Pos;
	int SpawnId;
	int Seed;
	int ItemId;
	int CellIndex;
	bool MoveEnable;
	bool FreedomEnable;
	bool AttackEnable;
	bool BeatenEnable;
	bool FollowEnable;
	bool FrozenEnable;
	bool EnableSendMsg;
	bool EnableWriteScore;
	bool HPEnable;
	bool LVEnable;
	bool AutoAttack;
	vector<int> SkillsId;
	float MoveSpeed;
	int Actiontime;
	float Castdistance;

	S_SpawnItem ItemPack;
	map<int, SkillBaseModel*> SkillPack;
	
};
class MessageHelper
{
public:
	MessageHelper();
	~MessageHelper();
	
	MESSAGEFUC(S_StartGame);
	MESSAGEFUC(S_Move);
	MESSAGEFUC(R_TestDelay);
	//MESSAGEFUC(R_HitTarget);
	MESSAGEFUC(S_Attack);
	MESSAGEFUC(R_Attack);
	MESSAGEFUC(R_Move);
	MESSAGEFUC(S_TestDelay);
	MESSAGEFUC(S_KillItem);
	MESSAGEFUC(S_SpawnItem);
	/*MESSAGEFUC(S_Freezen);*/
	//MESSAGEFUC(S_MonsterMove);
	MESSAGEFUC(S_MovePosList);
	
	MESSAGEFUC(S_Hit);
	MESSAGEFUC(S_LV);
	MESSAGEFUC(S_ItemScore);
	MESSAGEFUC(S_ChangeMultiple);
	MESSAGEFUC(R_ChangeMultiple);
	/*MESSAGEFUC(S_PoFuChenZhou);*/

	POOLFUC(SpawnMessage);
	

	ObjectPool<TobeMessage> TobeMessage_Pool;
	TobeMessage* Get_TobeMessage() {
		auto pack = TobeMessage_Pool.acquire_object();
		pack->msg = NULL;
		return pack;
	}
	void Back_TobeMessage(TobeMessage* pack) {
		pack->msg = NULL;
		TobeMessage_Pool.release_object(pack);
	}

	/*ObjectPool<SpawnMessage> SpawnMessage_Pool;
	SpawnMessage* Get_SpawnMessage() {
		auto pack = SpawnMessage_Pool.acquire_object();
		return pack;
	}
	void Back_SpawnMessage(SpawnMessage* pack) {
		SpawnMessage_Pool.release_object(pack);
	}*/
};

