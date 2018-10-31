 
#include "Global.h"
#include "LogSys.h"
#include "MonsterHelper.h"
#include "PathHelper.h"
#include "ScorePoolHelper.h"
#include "MessageHelper.h"
#include "SkillHelper.h"
#define SafeDelete(pData) { try { delete pData; } catch (...) { ASSERT(FALSE); } pData=NULL; } 
Global g_global;


Global::Global()
{

	
	inited = false;
}


Global::~Global()
{
	SafeDelete(logSys);
	SafeDelete(monsterHelper);
	SafeDelete(pathHelper);
	SafeDelete(messageHelper);
	SafeDelete(scorePoolHelper);
	SafeDelete(skillHelper);
}


void Global::init() {
	if (inited)
	{
		return;
	}

	logSys = new LogSys();
	monsterHelper = new MonsterHelper();
	pathHelper = new PathHelper();
	messageHelper = new MessageHelper();
	scorePoolHelper = new ScorePoolHelper();
	skillHelper = new SkillHelper();



	ExecuteDelayFrameForClien = 10;
	ExecuteDelayFrameForServer = 5;
	PosSendFrame = 6;

	char module_name[MAX_PATH];
	GetModuleFileNameA(NULL, module_name, MAX_PATH);
	work_dir = module_name;
	std::string::size_type last_backslash = work_dir.rfind('\\', work_dir.size());
	if (last_backslash != std::string::npos)
		work_dir.erase(last_backslash + 1);

	abs_dir = "3DfishServer\\";

	string fileName = "NavMesh.bytes";
	InitPath(work_dir + abs_dir + fileName);

	fileName = "ConfigList_Monster.bytes";
	InitMonster(work_dir + abs_dir + fileName);

	fileName = "ProductLogic.bytes";
	InitPathLogic(work_dir + abs_dir + fileName);

	fileName = "ConfigList_Skill.bytes";
	InitSkill(work_dir + abs_dir + fileName);

	fileName = "ConfigList_Buf.bytes";
	InitSkillBuf(work_dir + abs_dir + fileName);

	fileName = "ConfigList_SkillEffect.bytes";
	InitSkillEffect(work_dir + abs_dir + fileName);

	fileName = "ConfigList_LearnSkill.bytes";
	InitLearnSkill(work_dir + abs_dir + fileName);
	//读取房间参数
	inited = true;
}
void Global::InitPathLogic(string fname) {
	//pathHelper->InitProduction(fname);
}
void Global::InitPath(string fname) {
	pathHelper->InitPath(fname);
}
void Global::InitMonster(string fname) {
	monsterHelper->InitConfig(fname);
}
void Global::InitSkill(string fname) {
	skillHelper->InitSkillConfig(fname);
}
void Global::InitSkillBuf(string fname) {
	skillHelper->InitSkillBuf(fname);
}
void Global::InitSkillEffect(string fname) {
	skillHelper->InitSkillEffectConfig(fname);
}
void Global::InitLearnSkill(string fname) {
	skillHelper->InitLearnSkill(fname);
}
int Global::GetExecuteDelayFrameForServer(int frame) {
	return ExecuteDelayFrameForServer + frame;
}