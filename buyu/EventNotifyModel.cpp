#include "EventNotifyModel.h"
#include "SendModel.h"


EventNotifyModel::EventNotifyModel()
{
}


EventNotifyModel::~EventNotifyModel()
{


}

void EventNotifyModel::Bind(SendModel* send) {
	Send = send;
}
void EventNotifyModel::Init(bool enable,int id) {
	Enable = enable;
	Id = id;
}
void EventNotifyModel::SendMsg(MSG_ID smgId, google::protobuf::Message* msg) {
	if (!Enable) {
		return;
	}
	Send->SendMsgEx(Id, smgId, msg);
}