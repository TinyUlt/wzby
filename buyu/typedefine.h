#pragma once

//#include<iostream>
//#include <fstream>
//#include <string>
//#include <map>

//#include "gt_buyu.pb.h"
//#include "Vector3.h"
//#include <vector>
//#include <windows.h> 
#include"afxwin.h"
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;


typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef __int64 LONGLONG;
typedef void *HANDLE;
typedef void far            *LPVOID;
#define GAME_PLAYER           6
#define countof_macro(x) (sizeof((x)) / sizeof(x)[0])
#define INVALID_CHAIR				0xFFFF								//ÎÞÐ§ÒÎ×Ó
#define LONGLONGHIGH 9223372036854775807
#define LONGLONGLOW -9223372036854775808

#define MARGINOFERROR 0.0001
enum MSG_ID {
	MSG_S_StartGame = 10000,
	MSG_S_FrameSync = 10001,
	MSG_S_SpawnItem = 10002,
	MSG_S_SpawnItemEx = 20002,
	MSG_S_KillItem = 10003,
	MSG_R_Move = 10004,
	MSG_S_Move = 10005,
	MSG_S_Level = 10006,
	MSG_R_HitTarget = 10009,
	MSG_S_ItemScore = 10010,
	MSG_S_TestDelay = 10011,
	MSG_R_TestDelay = 10012,
	//MSG_S_MonsterMove = 10013,
	MSG_S_MovePosList = 10014,
	MSG_S_Hit = 10017,
	MSG_S_LV = 10018,
	MSG_R_ChangeMultiple = 10019,
	MSG_S_ChangeMultiple = 10020,
	MSG_R_Attack = 10027,
	MSG_S_Attack = 10028,
	
	
	//MSG_S_MonsterTerminal = 10015,
	//MSG_S_SpawnPlayer = 10016,
	MSG_S_Freezen = 10101,
	MSG_R_Freezen = 10100,

	MSG_S_PoFuChenZhou = 10200

};
enum SkillId {
	Skill_Heal = 10000,
	Skill_Frozen = 10004,
	Slill_SpeedUp = 10005,
	Skill_PoFuChenZhou = 3001,
	Skill_BaWangZhan = 3002,
	Skill_ChongFengXianZhen = 3003	
};
enum MoveState
{
	ItemState_None,
	ItemState_MovingFreedom,
	ItemState_MovingTrack,
	ItemState_MovingBack,
	ItemState_MoveFreedomEnd,
	ItemState_MovingTrackEnd,
	ItemState_MovingBackEnd,
	ItemState_Attacking,
	ItemState_AttackEnd


};
enum AttackState {
	AttackState_None,
	AttackState_Ing
	
};
enum ItemTeam {
	PlayerTeam,
	MonsterTeam,
};
enum BulletHurtType {
	MultipleHurt,
	HPHurt
};