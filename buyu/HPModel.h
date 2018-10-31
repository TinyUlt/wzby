#pragma once
#include "ValueModel.h"
class MessageModel;
class ItemModel;
class BulletModel;
class HPModel
{
public:
	HPModel();
	~HPModel();
	void Bind(ItemModel* host, MessageModel* message);
	void Init(bool enable, int value);
	void Update(int frame);
	bool Hurt(ItemModel* attacker, BulletModel* bullet);
	bool IsDead();
	bool Enable;
	int NowFrame;
	ItemModel* Host;
	ValueModel Value;
	MessageModel* Message;
};

