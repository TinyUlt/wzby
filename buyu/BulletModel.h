#pragma once
#include "PosModel.h"
#include "ItemModel.h"
#include "TimerModel.h"
#include "MulSkillModel.h"
#include "DMGSkillModel.h"
/**
* @brief 子弹组建
* @need 创建者、受击者 
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
	//死亡返回true
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