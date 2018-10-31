#include "Global.h"
#include "MoveModel.h"
#include "PathHelper.h"
#include "LogSys.h"
#include "MessageModel.h"
#include "MessageHelper.h"
#include "SendModel.h"
#include "ItemModel.h"
#include "AttackModel.h"
#include "gt_buyu.pb.h"
#include "PosModel.h"
#include "FrozenModel.h"
using namespace gt_msg;
MoveModel::MoveModel()
{
	pathList.clear();
	Message = NULL;
	Host = NULL;
	Attack = NULL;
	Pos = NULL;
	IsSetPath = false;
}


MoveModel::~MoveModel()
{
}
void MoveModel::Bind(ItemModel* host, AttackModel* attack, PosModel* pos, FrozenModel* frozen, MessageModel* message) {
	Message = message;
	Host = host;
	Attack = attack;
	Pos = pos;
	Frozen = frozen;
}
void MoveModel::Init(bool enable, int cellIndex, float speed) {
	Enable = enable;
	Speed = speed;
	PathIndex = 0;
	CellList.clear();
	FrameList.clear();
	pathList.clear();
	tempPathList.clear();

	AddCellList(cellIndex);
}

void MoveModel::Update(int frame) {
	if (!Enable) {
		return;
	}
	CalFrame = frame - Frozen->GetPassFrame();
	NowFrame = frame;

	//Â·¾¶½áÊø
	if (IsSetPath) {
		if (!FrameList.empty() && FrameList[FrameList.size() - 1] <= CalFrame) {
			if (Host->ItemMoveState == ItemState_MovingFreedom) {
				Host->ItemMoveState = ItemState_MoveFreedomEnd;
			}
			else if (Host->ItemMoveState == ItemState_MovingTrack) {
				Host->ItemMoveState = ItemState_MovingTrackEnd;
			}
			else if (Host->ItemMoveState == ItemState_MovingBack) {
				Host->ItemMoveState = ItemState_MovingBackEnd;
			}
		}
		if (TryGetPosByFrame(CalFrame, Pos->Position)) {

		}
		/*char ch[100];
		sprintf_s(ch, "x:%f, z:%f", Pos->Position.x, Pos->Position.z);
		g_global.logSys->LogInWindow(ch);*/
	}
	
	
}
int MoveModel::GetCellIndex() {
	return g_global.pathHelper->GetCellIndex(Pos->Position, CellList);
}
void MoveModel::AddCellList(int index) {
	CellList.push_back(g_global.pathHelper->GetCellByIndex(index));
}
bool MoveModel::CalculatePath(int endCellIndex, const Vector3& pos, const float range) {
	
	Vector3 v3;
	if (!FrameList.empty()) {
		TryGetPosByFrame(g_global.GetExecuteDelayFrameForServer(NowFrame), v3);
	}
	else {
		v3 = Pos->Position;
	}

	if (!g_global.pathHelper->CalculatePath(
		v3,
		pos,
		endCellIndex,
		tempPathList,
		CellList
	)) {
		g_global.logSys->LogInWindow("CalculatePath failed");
		return false;
	}
	if (tempPathList.size() > 0) {

		tempPathListEx.clear();
		//auto data = g_global.messageHelper->Get_S_MovePosList();

		auto d = Vector3::SqrMagnitude(tempPathList[0], tempPathList[tempPathList.size()-1]);

		
		if (d< range*range) {
			
			tempPathListEx.push_back(tempPathList[0]);
			
		}
		else
		{
			for (size_t i = 0; i < tempPathList.size(); i++) {

				auto& v2 = tempPathList[i];
				tempPathListEx.push_back(v2);
				//v2.assignVec3(data->mutable_list()->Add());

				if (range>0) {
					if (i + 1 < tempPathList.size()) {
						auto& v1 = tempPathList[i + 1];
						Vector3 v3;
						if (Vector3::TryGetPointInLineWitchIsLengthFrom1Point(pos, v1, v2, range * range, v3)) {
							//v3.assignVec3(data->mutable_list()->Add());
							tempPathListEx.push_back(v3);
							break;
						}
					}
				}

			}
		}

		auto data = Message->SendMovePosList(Host->Id, g_global.GetExecuteDelayFrameForServer(NowFrame), tempPathListEx);
		/*data->set_frame(g_global.GetExecuteDelayFrameForServer(NowFrame));
		data->set_id(Host->Id);
		Message->StoreMessage(MSG_S_MovePosList, data, g_global.GetExecuteDelayFrameForServer(NowFrame), NowFrame);
		Send->SendMsg(INVALID_CHAIR, MSG_S_MovePosList, data);*/
		PosListPack.CopyFrom(*data);
	}
	IsSetPath = false;
	return true;
	//State = MoveState::MoveState_TobeMoved;
}
void MoveModel::SetPath(S_MovePosList* posList) {
	
	FrameList.clear();

	pathList.clear();
	for (int i = 0; i < posList->list_size(); i++) {

		pathList.push_back(posList->mutable_list()->Get(i));
		
		if (i == 0) {
			FrameList.push_back(NowFrame);
		}
		else {
			float distance = Vector3::Distance(pathList[i], pathList[i - 1]);
			int frame =(int) (distance / Speed);
			FrameList.push_back(FrameList[i - 1] + frame);
		}
	}

	PathIndex = 0; 
	IsSetPath = true;
	Frozen->Reset();
	//State = MoveState::MoveState_Moving;
}

//void MoveModel::CalculateAndSetPath(int endCellIndex, int frame, const Vector3& pos) {
//	float mL = 10;
//	/*auto d = Vector3::SqrMagnitude(pos, Position);
//	if (d< mL) {
//
//		return;
//	}*/
//	Vector3 v3;
//	if (TryGetPosByFrame(frame, v3)) {
//		Pos->Position = v3;
//	}
//	//char ch[100];
//	////auto dfs = df.sqrMagnitude();
//	//sprintf_s(ch, "start:%f,%f end:%f,%f", Position.x, Position.z, pos.x, pos.z);
//	//g_global.logSys->LogInWindow(ch);
//
//	if (!g_global.pathHelper->CalculatePath(
//		Pos->Position,
//		pos,
//		endCellIndex,
//		tempPathList,
//		CellList
//	)) {
//		return;
//	}
//	if (tempPathList.size() > 0) {
//
//		FrameList.clear();
//		pathList.clear();
//		
//		for (int i = 0; i < tempPathList.size(); i++) {
//
//			auto& v2 = tempPathList[i];
//			pathList.push_back(v2);
//
//			if (i + 1 < tempPathList.size()) {
//				auto& v1 = tempPathList[i + 1];
//				Vector3 v3;
//				if (Vector3::TryGetPointInLineWitchIsLengthFrom1Point(pos, v1, v2, mL, v3)) {
//					pathList.push_back(v3);
//					break;
//				}
//			}
//		}
//		
//		for (int i = 0; i < pathList.size(); i++) {
//
//			if (i == 0) {
//				FrameList.push_back(NowFrame);
//			}
//			else {
//				float distance = Vector3::Distance(pathList[i], pathList[i - 1]);
//				int frame = distance / Speed;
//				FrameList.push_back(FrameList[i - 1] + frame);
//			}
//		}
//
//		PathIndex = 0;
//	}
//}

bool MoveModel::TryGetPosByFrame(int frame, Vector3& pos) {

	
	if (FrameList.empty() )
	{
		return false;
	}
	if (FrameList[0] > frame) {
		pos = pathList[0];

		return false;
	}
	
	if (FrameList[FrameList.size() - 1] <= frame) {
		pos = pathList[pathList.size() - 1];
		/*if (State != MoveState::MoveState_TobeMoved) {
			State = MoveState::MoveState_End;
		}*/
		
		return false;
	}
	//State = MoveState::Moving;
	

	for (size_t i = 0; i < FrameList.size(); i++)
	{
		if (FrameList[i] < frame)
		{
			PathIndex = i;
		}
	}
	
	Vector3 v0 = pathList[PathIndex];
	Vector3 v2 = pathList[PathIndex+1];
	Vector3 v3 = v2 - v0;

	int f0 = FrameList[PathIndex];
	int passFrame = frame - f0;
	int sectionFrame = FrameList[PathIndex+1] - f0;

	float fp = ((float)passFrame) / ((float)sectionFrame);

	pos = v3 * fp + v0;
	return true;
}

void MoveModel::SetPosAndVOffset(R_Move* move) {

	MovePack.mutable_data()->CopyFrom(*(move->mutable_data()));

	this->Pos->SetPosition(move->mutable_data()->position(), move->cellindex());
	//this->Pos->CellIndex = move->cellindex();// cellIndex;
	//this->Pos->Position = move->mutable_data()->position();// pos;
	FrameList.clear();
}