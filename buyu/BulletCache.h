#pragma once
#include <map>
#include <vector>
#include "gt_buyu.pb.h"
#include "Vector3.h"
#include "typedefine.h"
using namespace std;
using namespace gt_msg;
class BulletModel;
class ItemModel;
class MessageModel;
class BulletCache
{
public:
	BulletCache();
	~BulletCache();
	void Bind(MessageModel* message);
	void Update(int frame);
	BulletModel* CreateBullet(
		ItemModel* creator,
		ItemModel* victim, 
		int skillId,
		bool multipleEnable,
		int multipleValue, 
		bool dmgEnable,
		int dmgValue);
	bool TryGetBulletsPoint(google::protobuf::RepeatedPtrField<TestPoint>* list);
	void EraseDic(int id);
	void EraseDic(BulletModel* value);
	map<int, BulletModel*>  Dic;
	vector<int> TobeDelete;
	int NowFrame;
	int Id;
	MessageModel* Message;
};

