#pragma once
class MessageModel;
class BulletModel;
class ItemModel;
class DMGSkillModel
{
public:
	DMGSkillModel();
	~DMGSkillModel();
	void Bind(BulletModel* host, MessageModel* message);
	void Init(bool enable, int value);
	void Update(int frame);
	bool Hit(ItemModel* attacker, ItemModel* victim);
	
	int NowFrame;
	bool Enable;
	int Value;
	BulletModel* Host;
	MessageModel* Message;
};

