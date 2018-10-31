#pragma once
#include "typedefine.h"
#include "gt_buyu.pb.h"
using namespace gt_msg;

class SendModel;
class EventNotifyModel
{
public:
	EventNotifyModel();
	~EventNotifyModel();
	void Bind(SendModel* send);
	void Init(bool enable,int id);
	void SendMsg(MSG_ID msgId, google::protobuf::Message* msg);
	bool Enable;
	int Id;
	SendModel* Send;
};

