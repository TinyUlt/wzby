#pragma once
#include "stdafx.h"
#include <string>
//#include "World.h"
using namespace std;
class MonsterHelper;
class PathHelper;
class MessageHelper;
class ScorePoolHelper;
class SkillHelper;
class LogSys;
class Global
{
public:
	
	Global();
	~Global();
	
	//World
	//World world;
	//怪物工厂
	MonsterHelper* monsterHelper;
	//路径工厂
	PathHelper* pathHelper;
	//
	MessageHelper* messageHelper;
	//分数池
	ScorePoolHelper* scorePoolHelper;
	//
	SkillHelper* skillHelper;

	LogSys* logSys;
	string abs_dir;
	//路径
	std::string work_dir;
	//日志系统


	////延迟多少帧执行
	int ExecuteDelayFrameForClien;
	int ExecuteDelayFrameForServer;
	int PosSendFrame;//客户端间隔多少帧发生位置的

	//初始化
	void init();
	void InitMonster(string fname);
	void InitSkill(string fname);
	void InitSkillEffect(string fname);
	void InitSkillBuf(string fname);
	void InitLearnSkill(string fname);
	void InitPathLogic(string fname);
	void InitPath(string fname);
	int GetExecuteDelayFrameForServer(int frame);
private:
	//是否已经初始化
	bool inited;
};
extern Global g_global;
