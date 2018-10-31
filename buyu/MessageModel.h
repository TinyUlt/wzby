#pragma once
#include "gt_buyu.pb.h"
#include <vector>
#include "typedefine.h"
#include <map>
#include "Vector3.h"
using namespace std;
using namespace gt_msg;
class ItemCache;
class TobeMessage;
class SendModel;
class SpawnMessage;
class ItemModel;
class MessageModel
{
public:
	MessageModel();
	~MessageModel();

	void Init(bool enable);
	void Bind(/*ItemCache* playerManager,*/ ItemCache* monsterManager/*, SendModel* send*/);

	void Update(int frame);
	//void StoreServerMessage(MSG_ID msgId, google::protobuf::Message* msg, int toBeFrame);
	//void StoreClientMessage(WORD chairId, MSG_ID msgId, google::protobuf::Message* msg, int toBeFrame, int nowFrame);
	void StoreMessage(MSG_ID msgId, void* msg, int toBeFrame, int nowFrame);
	void ExcuteMessage(MSG_ID msgId, void* msg);

	void SendMsg(WORD itemId, MSG_ID id, google::protobuf::Message* msg);
	void BroadcastMsg(WORD itemId, MSG_ID id, google::protobuf::Message* msg);

	void SendTestDelayMsg(int operatorId);
	void SendStartGame(int id, int result, int frame, int executedelayframe, int possendframe,  Vector3& pos);
	void SendSpawnPlayers(int id);
	void SendPrvMonsters(int id);
	S_KillItem* SendKillItem(int killerExpierence, int frame, int victimId, int killerId);
	S_ItemScore* SendScoreAndExpierence(int id, bool score = true, bool expierence = true);
	S_MovePosList* SendMovePosList(int id, int frame, vector<Vector3>& list);
	S_Attack* SendAttack(int attackerid, R_Attack* attack);
	void SendChangeMultiple(int operatorId, R_ChangeMultiple* recieve);
	void SendSpawnItem(SpawnMessage* msg);

	void SendMove(int id, R_Move* move);
	void SendFrozen(int operatorId, int frame, int endFrame, int victimsId);
	void SendSpeedUp(int operatorId, int frame);
	void SendHeal(int operatorId, int frame, vector<ItemModel*>& victims);
	void SendHit(int frame, int attackerId, int victimId, int skillId, LONGLONG score, int victimHP);
	void SendLV(int frame, int ItemId, int exp, int lv, int maxExp);

	//void SendPoFuChenZhou(int itemId, int frame, vector< int> victimsId);
	//void SendSelfAttack(int operatorId, R_Attack* attack);
	vector<TobeMessage*>ToDoThings;
	//ItemCache* PlayerManager;
	ItemCache* ItemManager;
	//SendModel* Send;
	
	//map<int, S_SpawnItem*> TodoMonsters;
	int NowFrame;
	bool Enable;
};