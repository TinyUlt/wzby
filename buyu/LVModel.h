#pragma once

#include "MessageModel.h"
class ItemModel;
class LVModel
{
public:
	LVModel();
	~LVModel();
	void Bind(ItemModel* host, MessageModel* message);
	void Update(int frame);
	void Init(bool enable, int lv, int exp);
	bool AddExp(int exp);//Éý¼¶·µ»Øtrue
	void Send();
	static int GetMaxExp(int lv);
	bool Enable;
	int Exp;
	
	int Level;
	int NowFrame;
	int OldLevel;
	ItemModel* Host;
	MessageModel* Message;
};

