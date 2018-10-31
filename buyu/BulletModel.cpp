#include "Global.h"
#include "BulletModel.h"
#include "ItemModel.h"
#include "LogSys.h"
#include "FollowModel.h"
#include "MessageModel.h"
BulletModel::BulletModel()
{
	Enable = false;
}


BulletModel::~BulletModel()
{
}

void BulletModel::Bind(ItemModel* creator, ItemModel* victim, MessageModel* message) {
	Creator = creator;
	Victim = victim;
	Message = message;
	Multiple.Bind(this, message);
	DMG.Bind(this, message);
}
void BulletModel::Init(
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
) {
	Enable = true;
	Pos.Position = Creator->Pos.Position;
	Speed = speed;
	StartFrame = frame + intonateTime;
	//Value = value;
	Type = type;
	SkillId = skillId;
	IsFlying = false;
	Multiple.Init(multipleEnable, multipleValue);
	DMG.Init(dmgEnable, dmgValue);
	//HurtType = hurtType;

	if (Type == SkillType::AutoTrigger) {
		Multiple.NowFrame = frame;
		DMG.NowFrame = frame;
		/*if ( !Creator->Follow.IsInCastdistance()) {
			g_global.logSys->LogInWindow("闪避");
			
		}
		else */
		{
			Victim->Beaten.Trigger(Creator, this);
		}
		
		Enable = false;
	}
	else {
		Timer.SetInterval(0, -1, -1, intonateTime);
	}
	
	/*char ch[40];
	sprintf_s(ch, "Speed :%f", speed);
	g_global.logSys->LogInWindow(ch);*/


}
bool BulletModel::Update(int frame) {
	NowFrame = frame;
	if (!Enable) {
		return false;
	}
	Multiple.Update(frame);
	DMG.Update(frame);
	if(Timer.Update(frame)) 
	{
		Creator->ItemMoveState = ItemState_AttackEnd;
		if (Speed == 0){
			Victim->Beaten.Trigger(Creator, this);
			Enable = false;
			return false;
		}
		IsFlying = true;
	}
	if (IsFlying) {
		int frameOffset = frame - StartFrame;
		StartFrame = frame;

		Vector3& normal = Vector3::Normalized(Victim->Pos.Position - Pos.Position);
		Pos.Position.addin(normal * Speed * (float)(frameOffset));
		if ( Vector3::SqrMagnitude(Victim->Pos.Position, Pos.Position)<1) {
			Victim->Beaten.Trigger(Creator, this);

			Enable = false;
			return false;
		}
	}
	
	return true;
}

bool BulletModel::Hit(ItemModel* attacker, ItemModel* victim) {

	bool killed = false;
	//只对近战其作用
	if (Speed == 0 && !Creator->Follow.IsInCastdistance()) {
		g_global.logSys->LogInWindow("闪避");
		Message->SendHit(
			g_global.GetExecuteDelayFrameForServer(NowFrame),
			attacker->Id,
			victim->Id,
			SkillId,
			-1,
			-1
		);

	}
	else {
		if (!Multiple.Hit(attacker, victim)) {
			killed = true;
		}
		if (!DMG.Hit(attacker, victim)) {
			killed = true;
		}
	}
	
	return killed;
}