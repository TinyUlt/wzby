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
	//���﹤��
	MonsterHelper* monsterHelper;
	//·������
	PathHelper* pathHelper;
	//
	MessageHelper* messageHelper;
	//������
	ScorePoolHelper* scorePoolHelper;
	//
	SkillHelper* skillHelper;

	LogSys* logSys;
	string abs_dir;
	//·��
	std::string work_dir;
	//��־ϵͳ


	////�ӳٶ���ִ֡��
	int ExecuteDelayFrameForClien;
	int ExecuteDelayFrameForServer;
	int PosSendFrame;//�ͻ��˼������֡����λ�õ�

	//��ʼ��
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
	//�Ƿ��Ѿ���ʼ��
	bool inited;
};
extern Global g_global;
