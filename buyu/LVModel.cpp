#include "Global.h"
#include "LVModel.h"
#include "MessageHelper.h"
#include "MessageModel.h"
#include "ItemModel.h"
LVModel::LVModel()
{
}


LVModel::~LVModel()
{
}
void LVModel::Bind(ItemModel* host, MessageModel* message) {
	Host = host;
	Message = message;
}
void LVModel::Init(bool enable, int lv, int exp) {
	Enable = enable;
	OldLevel = lv;
	Exp = exp;
	Level = lv;
}
void LVModel::Update(int frame) {
	NowFrame = frame;
}
int LVModel::GetMaxExp(int lv) {
	return 100 + lv * 20;
}
bool LVModel::AddExp(int exp) {

	if (!Enable) {
		return false;
	}
	Exp += exp;

	if (Exp >= GetMaxExp(Level)) {
		Exp = Exp - GetMaxExp(Level) ;
		Level++;
		
	}
	//Level = Exp / 100 + 1;
	if (OldLevel != Level) {
		OldLevel = Level;
		Send();
		return true;
	}
	return false;
}
void LVModel::Send() {
	if (!Enable) {
		return;
	}
	Message->SendLV(g_global.GetExecuteDelayFrameForServer(NowFrame), Host->Id, Exp, Level, GetMaxExp(Level));
}