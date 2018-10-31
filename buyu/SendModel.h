#pragma once
#include "typedefine.h"
#include "gt_buyu.pb.h"

using namespace gt_msg;
using namespace std;
interface ITableFrame;
class ItemCache;
class SendModel
{
public:
	SendModel();
	~SendModel();


	void Bind(ITableFrame* table_frame);


	//void SendTestDelayMsg(WORD wChairID, MSG_ID id, google::protobuf::Message* msg);
	//void SendMsg(WORD wChairID, MSG_ID id, google::protobuf::Message* msg);
	void SendMsgEx(int itemId, MSG_ID msgId, google::protobuf::Message* msg);
	//void Broadcast(WORD wChairID, MSG_ID id, google::protobuf::Message* msg);

	ITableFrame* m_table_frame_;

	//PlayerCache* PlayerManager;
};

