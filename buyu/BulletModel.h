#pragma once
#include "PosModel.h"
#include "ItemModel.h"
#include "TimerModel.h"
#include "MulSkillModel.h"
#include "DMGSkillModel.h"
/**
* @brief �ӵ��齨
* @need �����ߡ��ܻ��� 
*/
class MessageModel;
class BulletModel
{
public:
	BulletModel();
	~BulletModel();
	void Bind(ItemModel* creator, ItemModel* victim, MessageModel* message);
	void Init(
		bool multipleEnable,
		int multipleValue,
		bool dmgEnable,
		int dmgValue,
		//BulletHurtType hurtType, 
		SkillType type, 
		int skillId,
		int intonateTime, 
		float speed,  
		int frame
		//int value
	);
	bool Update(int frame);
	//��������true
	bool Hit(ItemModel* attacker, ItemModel* victim);
	bool Enable;
	float Speed;
	int StartFrame;
	int Id;
	int SkillId;
	bool IsFlying;
	TimerModel Timer;
	SkillType Type;
	PosModel Pos;
	ItemModel* Creator;
	ItemModel* Victim;
	BulletHurtType HurtType;
	//int Value;
	int NowFrame;
	MulSkillModel Multiple;
	DMGSkillModel DMG;
	MessageModel* Message;
};