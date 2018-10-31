#pragma once
//#include "ValueModel.h"
class MessageModel;
class BulletModel;
class ItemModel;
class MulSkillModel
{
public:
	MulSkillModel();
	~MulSkillModel();
	void Bind(BulletModel* host, MessageModel* message);
	void Init(bool enable, LONGLONG value);
	void Update(int frame);
	bool Hit(ItemModel* attacker, ItemModel* victim);

	bool Enable;
	int NowFrame;
	int Value;
	//ValueModel Value;
	BulletModel* Host;
	MessageModel* Message;
	//ValueModel Score;
};

