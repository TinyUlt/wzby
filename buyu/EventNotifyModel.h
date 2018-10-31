#pragma once
#include "typedefine.h"
#include "gt_buyu.pb.h"
using namespace gt_msg;

class SendModel;
class ItemModel;
class EventNotifyModel
{
public:
	EventNotifyModel();
	~EventNotifyModel();
	void Bind(ItemModel* host,SendModel* send);
	void Init(bool enableSendMsg, bool enableWriteScore);
	void SendMsg(MSG_ID msgId, google::protobuf::Message* msg);
	void WriteScore(LONGLONG score, LONGLONG grade);
	bool EnableSendMsg;
	bool EnableWriteScore;
	SendModel* Send;
	ItemModel* Host;
};

