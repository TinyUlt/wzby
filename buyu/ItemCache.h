#pragma once
#include <map>
#include <vector>
#include "gt_buyu.pb.h"
#include "Vector3.h"
using namespace std;
using namespace gt_msg;
class BulletCache;
class ItemModel;
class MessageModel;
class SendModel;
class ItemModel;
class SpawnCache;
class SpawnMessage;
//class ProducteFishPack;
enum MonsterBehaviour
{
	Aggressive = 1,//有攻击性
	Harmless = 2,//无害的
};
enum MonsterMove {
	Static = 1,//静止的
	Freedom = 2,//自由的
};

class ItemCache
{
public:
	ItemCache();
	~ItemCache();

	void Bind(BulletCache* bulletManager, SpawnCache* spawnManager, MessageModel* message, SendModel* send);
	void Update(int frame);
	void SetId(S_SpawnItem& pack);
	//void Store(S_SpawnItem& pack);
	/*void TobeSpawn(
		int frame,
		int seed,
		int spawnId,
		int type, 
		const Vector3& pos, 
		int cellIndex, 
		bool moveEnable,
		bool freedomEnable,
		bool attackEnable,
		bool beatenEnable,
		bool followEnable,
		bool frozenEnable);*/
	//void Spawn(S_SpawnItem& pack);
	void Spawn( SpawnMessage* msg);
	bool TryGetMonsterById(int id, ItemModel** monster);
	bool TryGetMonstersPoint(google::protobuf::RepeatedPtrField<TestPoint>* list);
	bool TryGetAllMonster(vector<S_SpawnItem*>&);
	bool TryGetItemByDistance(vector<ItemModel*>& list, Vector3& pos, float distance);
	bool TryGetItemByDistanceSqr(vector<ItemModel*>& list, Vector3& pos, float distanceSqr);
	bool TryGetItemIdByDistance(vector<int>& list, Vector3& pos, float distance);
	void EraseDic(int id);
	void EraseDic(ItemModel* value);
	void Freezen(S_Hit* freezen);
	//vector<ItemModel*>* GetTobeSendMove();
	int GetMonsterSize();
	//void SetMonsterPosition(int id, Vec3* pos);
	void SetPath(int id, S_MovePosList* posList);
	void SetMul(int operatorId, int mul);
	void Attack(int attackId, int skillId, ItemModel* victim);
	void SkillTrigger(int itemId, S_Attack* attack);
	void SetPosition(R_Move* move);
	BulletCache* BulletManager;
	
	//鱼列表
	int Id;
	map<int, ItemModel*>  Dic;
	map<int, ItemModel*> ToBeDeleted;
	vector<int> HaveDeleted;

	//vector<ItemModel*> TobeSendMove;

	MessageModel* Message;
	SendModel* Send;
	SpawnCache* SpawnManager;
	int NowFrame;
};