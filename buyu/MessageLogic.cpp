#include "GameTable.h"
#include "Global.h"

void GameTable::MessageUpdate(int frame) {
	while (1) {
		if (!ToDoThings.empty()) {
			auto& pack = ToDoThings.front();
			if (pack->frame <= frame) {
				ExcuteMessage(pack->msg);
				ToDoThings.pop();
				g_global.messageHelper->Back_TobeMessage(pack);
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}

	queue<TobeMessage*>* toDoThings;
	for (int i = 0; i < GAME_PLAYER; i++) {

		PlayerManager.GetTodoThings(i, &toDoThings);// PlayerList[i].ToDoThings;
		if (!toDoThings->empty()) {
			auto& pack = toDoThings->front();
			if (pack->frame <= frame) {

				ExcuteMessage(pack->msg);

				toDoThings->pop();
				g_global.messageHelper->Back_TobeMessage(pack);
			}
		}
	}
}

void GameTable::StoreServerMessage(google::protobuf::Message* msg, int toBeFrame) {
	auto tobeMsg = g_global.messageHelper->Get_TobeMessage();
	tobeMsg->frame = toBeFrame;
	tobeMsg->msg = msg;

	ToDoThings.push(tobeMsg);
}
void GameTable::StoreClientMessage(WORD chairId, google::protobuf::Message* msg, int toBeFrame, int nowFrame) {
	auto tobeMsg = g_global.messageHelper->Get_TobeMessage();
	tobeMsg->frame = toBeFrame;
	tobeMsg->msg = msg;
	if (toBeFrame <= nowFrame) {
		ExcuteMessage(msg);
		g_global.messageHelper->Back_TobeMessage(tobeMsg);
	}
	else {
		queue<TobeMessage*>*toDoThings;
		PlayerManager.GetTodoThings(chairId, &toDoThings);
		toDoThings->push(tobeMsg);
	}

}
//void GameTable::GetTodoSpawnMonster(vector<S_SpawnMonster*>& list) {
//	for (auto& m : ToDoThings) {
//
//	}
//}
void GameTable::ExcuteMessage(google::protobuf::Message* msg) {
	auto& typeName = msg->GetTypeName();

	if (typeName == "gt_msg.S_MonsterMove") {
		auto move = (S_MonsterMove*)msg;

		MonsterManager.SetMonsterPosition(move->id(), move->mutable_pos());

		g_global.messageHelper->Back_S_MonsterMove(move);
		//todo
	}
	else if (typeName == "gt_msg.S_SpawnMonster") {
		S_SpawnMonster* spawn = (S_SpawnMonster*)msg;
		
		MonsterManager.Spawn(*spawn);

		g_global.messageHelper->Back_S_SpawnMonster(spawn);

		TodoMonsters.erase(spawn->id());
	}
	else if (typeName == "gt_msg.R_Move") {
		R_Move* move = (R_Move*)msg;

		PlayerManager.SetPosition(move->mutable_data()->chairid(), *(move->mutable_data()->mutable_position()), move->cellindex());

		g_global.messageHelper->Back_R_Move(move);
	}
	else if (typeName == "gt_msg.R_AttackStart") {

		R_AttackStart* attack = (R_AttackStart*)msg;
		//todo
		g_global.messageHelper->Back_R_AttackStart(attack);
	}
	else if (typeName == "gt_msg.S_KillMonster") {
		S_KillMonster* killMonster = (S_KillMonster*)msg;

		MonsterManager.Erase(killMonster->id());

		g_global.messageHelper->Back_S_KillMonster(killMonster);
	}
	else if (typeName == "gt_msg.S_Freezen") {
		S_Freezen* freezen = (S_Freezen*)msg;
		MonsterManager.Freezen(freezen);
		g_global.messageHelper->Back_S_Freezen(freezen);
	}
}