#include "Global.h"
#include "SpeedUpSkillModel.h"
#include "ItemCache.h"
#include "ItemModel.h"
#include "SkillHelper.h"


SpeedUpSkillModel::SpeedUpSkillModel()
{
}


SpeedUpSkillModel::~SpeedUpSkillModel()
{
}

void SpeedUpSkillModel::Init(bool enable, int cd) {

}
void SpeedUpSkillModel::Trigger(S_Attack* attack) {
	Message->SendSpeedUp(Host->Id, g_global.GetExecuteDelayFrameForServer(NowFrame));
}
void SpeedUpSkillModel::Back() {
	g_global.skillHelper->SpeedUpSkillPool.release_object(this);
}