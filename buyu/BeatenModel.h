#pragma once
class FollowModel;
class AttackModel;
class ItemModel;
class BulletModel;
class MessageModel;
class BeatenModel
{
public:
	BeatenModel();
	~BeatenModel();
	void Init(bool enable);
	void Bind(ItemModel* host, FollowModel* follow, AttackModel* attack, MessageModel* message);
	void Update(int frame);
	void Trigger(ItemModel* attacker, BulletModel* bullet);
	bool Enable;
	int NowFrame;

	FollowModel* Follow;
	AttackModel* Attack;
	ItemModel* Host;
	MessageModel* Message;
};

