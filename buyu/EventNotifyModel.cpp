#include "Global.h"
#include "EventNotifyModel.h"
#include "SendModel.h"
#include "ItemModel.h"
#include "LogSys.h"
EventNotifyModel::EventNotifyModel()
{
}


EventNotifyModel::~EventNotifyModel()
{


}

void EventNotifyModel::Bind(ItemModel* host, SendModel* send) {
	Send = send;
	Host = host;
}
void EventNotifyModel::Init(bool enableSendMsg, bool enableWriteScore) {
	EnableSendMsg = enableSendMsg;
	EnableWriteScore = enableWriteScore;
	
}
void EventNotifyModel::SendMsg(MSG_ID smgId, google::protobuf::Message* msg) {
	if (!EnableSendMsg) {
		return;
	}
	Send->SendMsgEx(Host->Id, smgId, msg);
}
void EventNotifyModel::WriteScore(LONGLONG score, LONGLONG grade) {
	if (!EnableWriteScore) {
		return;
	}
	Send->WriteScore(Host->Id, score, grade);
	char ch[512];
	sprintf(ch, "%s(%d)，写入数据库 %lld 金币 \n", Host->NickName.c_str(), (int)Host->UserId, score);
	g_global.logSys->LogInFile(ch);
}