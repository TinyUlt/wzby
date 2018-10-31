#pragma once
#include "gt_buyu.pb.h"
#include <vector>
using namespace std;
using namespace gt_msg;
class ItemModel;
class MessageModel;
class ItemCache;
class SkillBaseModel
{
public:
	SkillBaseModel();
	virtual ~SkillBaseModel();
	void Bind(ItemModel* host, ItemCache* ItemManager, MessageModel* message);
	virtual void Trigger(S_Attack* attack) = 0;
	virtual void Back() = 0;
	virtual void Update(int frame);
	int Type;
	int NowFrame;
	int CoolingTime;
	bool Enable;
	MessageModel* Message;
	ItemCache* ItemManager;
	ItemModel* Host;
	vector<ItemModel*> ItemList;
};

