#include "Global.h"
#include "SendModel.h"
#include "StdAfx.h"
#include "ItemCache.h"

SendModel::SendModel()
{
}


SendModel::~SendModel()
{
}
void SendModel::Bind(ITableFrame* table_frame) {
	m_table_frame_ = table_frame;
	//PlayerManager = playerManager;
}
//111111
//void SendModel::SendTestDelayMsg(WORD wChairID, MSG_ID id, google::protobuf::Message* msg) {
//	if (wChairID >= GAME_PLAYER && wChairID < INVALID_CHAIR) {
//		return;
//	}
//	if (msg == NULL) {
//		return;
//	}
//
//	BYTE*   bybufer = NULL;
//	int nsize = msg->ByteSize();
//	bybufer = new BYTE[nsize];
//	msg->SerializeToArray(bybufer, nsize);
//
//	//m_table_frame_->SendTableData(wChairID, id, bybufer, nsize);
//
//
//
//	if (m_table_frame_ != NULL)
//	{
//		if (wChairID == INVALID_CHAIR) {
//			for (int i = 0; i < GAME_PLAYER; i++) {
//				{
//					if (m_table_frame_->GetTableUserItem(i)) {
//						m_table_frame_->SendTableData(i, id, bybufer, nsize);
//					}
//				}
//
//			}
//		}
//		else {
//			if (m_table_frame_->GetTableUserItem(wChairID)) {
//				{
//					/*if (MSG_JoinFreeResponsefish3d == id) {
//					g_global.logSys->LogInWindow("11111");
//					}*/
//					m_table_frame_->SendTableData(wChairID, id, bybufer, nsize);
//				}
//			}
//
//		}
//	}
//	SafeDelete(bybufer);
//}
void SendModel::SendMsgEx(int itemId, MSG_ID msgId, google::protobuf::Message* msg) {

	BYTE*   bybufer = NULL;
	int nsize = msg->ByteSize();
	bybufer = new BYTE[nsize];
	msg->SerializeToArray(bybufer, nsize);

	if (m_table_frame_->GetTableUserItem(itemId)) {
		
		m_table_frame_->SendTableData(itemId, msgId, bybufer, nsize);
	}

}
void SendModel::WriteScore(WORD itemId, LONGLONG score, LONGLONG grade) {
	tagScoreInfo score_info;
	memset(&score_info, 0, sizeof(tagScoreInfo));
	score_info.lScore = score;
	score_info.lGrade = grade;
	if (score > 0L) {

		score_info.cbType = SCORE_TYPE_WIN;
	}
	else if (score < 0L) {

		score_info.cbType = SCORE_TYPE_LOSE;
	}
	else
	{
		score_info.cbType = SCORE_TYPE_DRAW;
	}
	if (m_table_frame_ != NULL) {
		m_table_frame_->WriteUserScore(itemId, score_info);

		
	}
	
}
//void SendModel::SendMsg(WORD wChairID, MSG_ID id, google::protobuf::Message* msg)
//{
//	//111111
//	//if (wChairID >= GAME_PLAYER && wChairID < INVALID_CHAIR) {
//	//	return;
//	//}
//	//if (msg == NULL) {
//	//	return;
//	//}
//
//	//BYTE*   bybufer = NULL;
//	//int nsize = msg->ByteSize();
//	//bybufer = new BYTE[nsize];
//	//msg->SerializeToArray(bybufer, nsize);
//
//	////m_table_frame_->SendTableData(wChairID, id, bybufer, nsize);
//
//
//
//	//if (m_table_frame_ != NULL)
//	//{
//	//	if (wChairID == INVALID_CHAIR) {
//	//		for (int i = 0; i < GAME_PLAYER; i++) {
//	//			if (PlayerManager->PlayerList[i].Enable) {
//	//				if (m_table_frame_->GetTableUserItem(i)) {
//	//					m_table_frame_->SendTableData(i, id, bybufer, nsize);
//	//				}
//	//			}
//
//	//		}
//	//	}
//	//	else {
//	//		if (m_table_frame_->GetTableUserItem(wChairID)) {
//	//			if (m_table_frame_->GetTableUserItem(wChairID)) {
//	//				/*if (MSG_JoinFreeResponsefish3d == id) {
//	//				g_global.logSys->LogInWindow("11111");
//	//				}*/
//	//				m_table_frame_->SendTableData(wChairID, id, bybufer, nsize);
//	//			}
//	//		}
//
//	//	}
//	//}
//	//SafeDelete(bybufer);
//}
//void SendModel::Broadcast(WORD wChairID, MSG_ID id, google::protobuf::Message* msg) {
//	//111111
//	/*if (wChairID >= GAME_PLAYER && wChairID < INVALID_CHAIR) {
//		return;
//	}
//	if (msg == NULL) {
//		return;
//	}
//
//	BYTE*   bybufer = NULL;
//	int nsize = msg->ByteSize();
//	bybufer = new BYTE[nsize];
//	msg->SerializeToArray(bybufer, nsize);
//
//	if (m_table_frame_ != NULL) {
//		for (int i = 0; i < GAME_PLAYER; i++) {
//			if (PlayerManager->PlayerList[i].Enable && i != wChairID) {
//				if (m_table_frame_->GetTableUserItem(i)) {
//					m_table_frame_->SendTableData(i, id, bybufer, nsize);
//				}
//			}
//
//		}
//	}
//
//	SafeDelete(bybufer);*/
//}