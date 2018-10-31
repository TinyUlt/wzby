#include "Global.h"
#include "MessageModel.h"
#include "ItemCache.h"
#include "MessageHelper.h"
#include "LogSys.h"
#include "SendModel.h"
#include "ItemModel.h"
#include "SkillHelper.h"
MessageModel::MessageModel()
{
}


MessageModel::~MessageModel()
{
}


void MessageModel::Init(bool enable) {
	Enable = enable;
	//	清理
	while (1) {
		if (!ToDoThings.empty()) {
			auto& pack = ToDoThings.front();
			ToDoThings.erase(ToDoThings.begin());
			g_global.messageHelper->Back_TobeMessage(pack);
		}
		else {
			break;
		}
	}
}

void MessageModel::Bind(/*ItemCache* playerManager,*/ ItemCache* monsterManager/*, SendModel* send*/) {
	//PlayerManager = playerManager;
	ItemManager = monsterManager;
	//Send = send;
}

void MessageModel::Update(int frame) {
	NowFrame = frame;
	//g_global.logSys->LogInWindow("000");
	if (!Enable) {
		return;
	}
	
	for (auto iter = ToDoThings.begin(); iter != ToDoThings.end(); ) {
		auto& pack = *iter;
		if (pack->frame <= frame) {
			ExcuteMessage(pack->id, pack->msg);
			g_global.messageHelper->Back_TobeMessage(pack);
			iter = ToDoThings.erase(ToDoThings.begin());
		}
		else {
			iter++;
		}
	}

	//while (1) {
	//	if (!ToDoThings.empty()) {
	//		auto& pack = *ToDoThings.begin();
	//		//g_global.logSys->LogInWindow("222");

	//		/*char ch[100];
	//		sprintf_s(ch, "now: %d, pack: %d", frame, pack->frame);
	//		g_global.logSys->LogInWindow(ch);*/

	//		if (pack->frame <= frame) {
	//			//g_global.logSys->LogInWindow("333");
	//			ExcuteMessage(pack->id, pack->msg);
	//			g_global.messageHelper->Back_TobeMessage(pack);
	//			ToDoThings.erase(ToDoThings.begin());
	//			
	//		}
	//		else {
	//			/*char ch[100];
	//			sprintf_s(ch, "%d,%d", pack->frame, frame);
	//			g_global.logSys->LogInWindow(ch);*/
	//			break;
	//		}
	//	}
	//	else {
	//		break;
	//	}
	//}
}

void MessageModel::StoreMessage( MSG_ID msgId, void* msg, int toBeFrame, int nowFrame) {
	//Send->se
	
	if (toBeFrame <= nowFrame) {
		ExcuteMessage(msgId, msg);
	}
	else {
		auto tobeMsg = g_global.messageHelper->Get_TobeMessage();
		tobeMsg->id = msgId;
		tobeMsg->frame = toBeFrame;
		tobeMsg->msg = msg;
		ToDoThings.push_back(tobeMsg);
	}

	
}

void MessageModel::ExcuteMessage(MSG_ID msgId, void* msg) {
	
	if (msgId == MSG_S_MovePosList) {
		auto posList = (S_MovePosList*)msg;

		ItemManager->SetPath(posList->moverid(), posList);

		g_global.messageHelper->Back_S_MovePosList(posList);
		//todo
	}
	else if (msgId == MSG_S_SpawnItemEx) {
		SpawnMessage* spawn = (SpawnMessage*)msg;
		ItemManager->Spawn( spawn);
		
		g_global.messageHelper->Back_SpawnMessage(spawn);
	}
	else if (msgId == MSG_R_Move) {
		R_Move* move = (R_Move*)msg;

		ItemManager->SetPosition(move);

		g_global.messageHelper->Back_R_Move(move);
	}
	else if (msgId == MSG_S_LV) {
		S_LV* lv = (S_LV*)msg;
		g_global.messageHelper->Back_S_LV(lv);
	}
	else if (msgId == MSG_S_Attack) {
		
		S_Attack* attack = (S_Attack*)msg;

		
		if (attack->skillid() <= 1000) {
			ItemModel* victim = NULL;
			if (ItemManager->TryGetMonsterById(attack->victimid(), &victim)) {
				ItemManager->Attack(attack->attackerid(), attack->skillid(), victim);
			}
		}
		else {
			if (attack->skillid() == Skill_Heal ||
				attack->skillid() == Skill_Frozen || 
				attack->skillid() == Skill_PoFuChenZhou ||
				attack->skillid() == Skill_BaWangZhan || 
				attack->skillid() == Skill_ChongFengXianZhen) {
			
				ItemManager->SkillTrigger(attack->attackerid(), attack);
			}
			
			else {
				g_global.logSys->LogInWindow("技能未实现");

			}
		}

		g_global.messageHelper->Back_S_Attack(attack);
	}
	else if (msgId == MSG_S_Hit) {
		S_Hit* hit = (S_Hit*)msg;

		if (hit->skillid() == Skill_Frozen) {
			ItemManager->Freezen(hit);
		}
		g_global.messageHelper->Back_S_Hit(hit);
	}
	else if (msgId == MSG_S_KillItem) {
		S_KillItem* KillItem = (S_KillItem*)msg;

		ItemManager->EraseDic(KillItem->deadid());

		g_global.messageHelper->Back_S_KillItem(KillItem);
	}
	else if (MSG_S_ChangeMultiple == msgId) {

		S_ChangeMultiple* changeMultiple = (S_ChangeMultiple*)msg;
		ItemManager->SetMul(changeMultiple->itemid(), changeMultiple->value());
		g_global.messageHelper->Back_S_ChangeMultiple(changeMultiple);
		//ItemManager->SetMul()
	}
	else {
		char ch[64];
		sprintf_s(ch, "未处理消息：%d", msgId);
		g_global.logSys->LogInWindow(ch, TraceLevel_Exception);
	}
}

void MessageModel::SendMsg(WORD itemId, MSG_ID id, google::protobuf::Message* msg) {
	if (INVALID_CHAIR == itemId) {
		for (auto& pair : ItemManager->Dic) {
			auto& item = pair.second;
			item->EventNotify.SendMsg(id, msg);
		}
	}
	else if(ItemManager->Dic.count(itemId) > 0){
		ItemManager->Dic[itemId]->EventNotify.SendMsg(id, msg);
	}
}
void MessageModel::BroadcastMsg(WORD itemId, MSG_ID id, google::protobuf::Message* msg) {
	/*if (ItemManager->Dic.count(itemId) <= 0) {
		return;
	}*/
	for (auto& pair : ItemManager->Dic) {
		auto& key = pair.first;
		if (key != itemId) {
			auto& item = pair.second;
			item->EventNotify.SendMsg(id, msg);
		}
	}
}
void MessageModel::SendTestDelayMsg(int operatorId) {
	//111111
	/*S_TestDelay* pack = g_global.messageHelper->Get_S_TestDelay();

	Send->SendTestDelayMsg(operatorId, MSG_S_TestDelay, pack);
	g_global.messageHelper->Back_S_TestDelay(pack);*/
}
void MessageModel::SendStartGame(int id, int result, int frame, int executedelayframe, int possendframe,  Vector3& pos) {
	S_StartGame* startGame = g_global.messageHelper->Get_S_StartGame();
	startGame->set_resultcode(result);
	startGame->set_frame(frame);
	startGame->set_executedelayframe(executedelayframe);
	startGame->set_possendframe(possendframe);
	//pos.assignVec3(startGame->mutable_bornposition());

	SendMsg(id, MSG_S_StartGame, startGame);
	
	g_global.messageHelper->Back_S_StartGame(startGame);
}
void MessageModel::SendSpawnPlayers(int id) {
	//111111
	/*for (int i = 0; i < GAME_PLAYER; i++) {
		if (PlayerManager->PlayerList[i].Enable) {
			

			Send->SendMsg(id, MSG_S_SpawnItem, &PlayerManager->PlayerList[i].Pack);
			
		}
	}

	auto resp = PlayerManager->PlayerList[id].Pack;
	
	PlayerManager->PlayerList[id].Pos.GetPosition((resp.mutable_pos()));
	for (int i = 0; i < GAME_PLAYER; i++) {
		if (PlayerManager->PlayerList[i].Enable && i != id) {
			Send->SendMsg(i, MSG_S_SpawnItem, &resp);
		}
	}*/
	
}
void MessageModel::SendPrvMonsters(int id) {
	
	//发送怪物
	for (auto& iter : ItemManager->Dic) {
		auto key = iter.first;
		auto value = iter.second;

		SendMsg(id, MSG_S_SpawnItem, value->GetPack());

		if (value->TeamId == PlayerTeam) {
			SendMsg(id, MSG_S_Move, &value->Move.MovePack);
		}
		else if (value->TeamId == MonsterTeam) {
			SendMsg(id, MSG_S_MovePosList, &value->Move.PosListPack);
		}
		

		for (auto& freezen : value->Frozen.List) {
			SendMsg(id, MSG_S_Hit, &freezen);
		}
	}
	//发送待办事务
	for (auto& message : ToDoThings) {
		switch (message->id)
		{
		case MSG_S_SpawnItem:
			SendMsg(id, message->id, (google::protobuf::Message*)message->msg);
			break;
		case MSG_S_MovePosList:
			SendMsg(id, message->id, (google::protobuf::Message*)message->msg);
			break;
		default:
			break;
		}
	}
}
S_KillItem* MessageModel::SendKillItem(int killerExpierence, int frame, int victimId, int killerId) {
	S_KillItem* KillItem = g_global.messageHelper->Get_S_KillItem();
	KillItem->set_killerexperience(killerExpierence);
	KillItem->set_frame(frame);
	KillItem->set_deadid(victimId);
	KillItem->set_killerid(killerId);
	KillItem->set_rebirth(10 * 60);
	SendMsg(INVALID_CHAIR, MSG_S_KillItem, KillItem);
	StoreMessage(MSG_S_KillItem, KillItem, frame, NowFrame);

	return KillItem;
}
S_ItemScore* MessageModel::SendScoreAndExpierence(int id, bool score, bool expierence) {
	//111111
	/*S_ItemScore* playerScore = g_global.messageHelper->Get_S_ItemScore();
	playerScore->set_chairid(id);
	playerScore->set_score(PlayerManager->PlayerList[id].Score.Value);
	playerScore->set_experience(PlayerManager->PlayerList[id].Experience.Value);
	Send->SendMsg(INVALID_CHAIR, MSG_S_ItemScore, playerScore);
	g_global.messageHelper->Back_S_ItemScore(playerScore);

	return playerScore;*/
	return NULL;
}

S_MovePosList* MessageModel::SendMovePosList(int id, int frame, vector<Vector3>& list) {

	auto data = g_global.messageHelper->Get_S_MovePosList();
	data->set_frame(frame);
	data->set_moverid(id);
	for (auto& v : list) {
		v.assignVec3(data->mutable_list()->Add());
	}
	StoreMessage(MSG_S_MovePosList, data, frame, NowFrame);
	SendMsg(INVALID_CHAIR, MSG_S_MovePosList, data);

	return data;
}

void MessageModel::SendSpawnItem(SpawnMessage* msg) {

	if (msg->ItemId < 0) {
		msg->ItemId = ItemManager->Id;
		ItemManager->Id++;
	}

	gt_msg::S_SpawnItem* resp = g_global.messageHelper->Get_S_SpawnItem();;
	resp->set_frame(msg->Frame);
	resp->set_itemid(msg->ItemId);
	resp->set_teamid(msg->TeamId);
	resp->set_type(msg->Type);
	resp->set_score(msg->Score);
	resp->set_hp(msg->HP);
	resp->set_exp(msg->EXP);
	resp->set_lv(msg->LV);
	resp->set_maxexp(LVModel::GetMaxExp(msg->EXP));
	resp->set_multiple(msg->Multiple);
	for (auto mul : msg->MulList) {
		resp->add_mullist(mul);
	}
	msg->Pos.assignVec3(resp->mutable_pos());

	msg->ItemPack = *resp;
	
	StoreMessage(MSG_S_SpawnItemEx, msg, msg->Frame, NowFrame);
	BroadcastMsg(resp->itemid(), MSG_S_SpawnItem, resp);
	g_global.messageHelper->Back_S_SpawnItem(resp);
}

void MessageModel::SendMove(int id, R_Move* move) {
	
	move->mutable_data()->set_moverid(id);
	StoreMessage(MSG_R_Move, move, move->mutable_data()->frame(), NowFrame);
	S_Move* resp = g_global.messageHelper->Get_S_Move();;
	*(resp->mutable_data()) = *(move->mutable_data());
	BroadcastMsg(id, MSG_S_Move, resp);
	g_global.messageHelper->Back_S_Move(resp);
}
void MessageModel::SendHeal(int operatorId, int frame, vector<ItemModel*>& victims) {
	auto data = g_global.messageHelper->Get_S_Hit();

	data->set_casterid(operatorId);
	for (auto item : victims) {
		auto victim = data->add_victimlist();
		victim->set_id(item->Id);
		victim->set_hp(item->HP.Value);
	}
	data->set_skillid(Skill_Heal);
	data->set_attackerscore(-1);
	data->set_frame(frame);
	StoreMessage(MSG_S_Hit, data, frame, NowFrame);
	SendMsg(INVALID_CHAIR, MSG_S_Hit, data);
}
void MessageModel::SendSpeedUp(int operatorId, int frame) {
	auto data = g_global.messageHelper->Get_S_Hit();
	data->set_casterid(operatorId);
	auto victim = data->add_victimlist();
	victim->set_id(operatorId);
	victim->set_hp(-1);
	data->set_skillid(Slill_SpeedUp);
	data->set_attackerscore(-1);
	data->set_frame(frame);
	StoreMessage(MSG_S_Hit, data, frame, NowFrame);
	SendMsg(INVALID_CHAIR, MSG_S_Hit, data);
}
void MessageModel::SendFrozen(int opratorId, int frame, int endFrame, int id) {
	
	auto data = g_global.messageHelper->Get_S_Hit();

	data->set_casterid(opratorId);
	auto victim = data->add_victimlist();
	victim->set_id(id);
	victim->set_hp(-1);
	data->set_skillid(Skill_Frozen);
	data->set_attackerscore(-1);
	//data->set_victimhp(victimHP);
	data->set_frame(frame);
	data->set_endframe(endFrame);
	//StoreMessage(MSG_S_Hit, data, frame, NowFrame);
	SendMsg(INVALID_CHAIR, MSG_S_Hit, data);
	StoreMessage(MSG_S_Hit, data, frame, NowFrame);

}
void MessageModel::SendChangeMultiple(int operatorId, R_ChangeMultiple* recieve) {
	auto data = g_global.messageHelper->Get_S_ChangeMultiple();

	data->set_frame(recieve->frame());
	data->set_itemid(operatorId);
	data->set_value(recieve->value());

	SendMsg(INVALID_CHAIR, MSG_S_ChangeMultiple, data);
	StoreMessage(MSG_S_ChangeMultiple, data, recieve->frame(), NowFrame);
}
S_Attack* MessageModel::SendAttack(int attackerid, R_Attack* attack) {
	auto data = g_global.messageHelper->Get_S_Attack();

	data->set_attackerid(attackerid);
	data->set_frame(attack->frame());
	data->set_victimid(attack->victimid());
	data->set_skillid(attack->skillid());
	data->set_skilllevel(attack->skilllevel());
	data->mutable_direction()->CopyFrom(*(attack->mutable_direction()));
	StoreMessage(MSG_S_Attack, data, attack->frame(), NowFrame);
	SendMsg(INVALID_CHAIR, MSG_S_Attack, data);

	return data;
}
void MessageModel::SendHit(int frame, int attackerId, int victimId, int skillId, LONGLONG score, int victimHP) {
	auto data = g_global.messageHelper->Get_S_Hit();

	data->set_casterid(attackerId);
	auto victim = data->add_victimlist();
	victim->set_id(victimId);
	victim->set_hp(victimHP);
	data->set_skillid(skillId);
	data->set_attackerscore(score);
	//data->set_victimhp(victimHP);
	data->set_frame(frame);
	StoreMessage(MSG_S_Hit, data, frame, NowFrame);
	SendMsg(INVALID_CHAIR, MSG_S_Hit, data);
}
void MessageModel::SendLV(int frame, int ItemId, int exp, int lv, int maxExp) {
	auto data = g_global.messageHelper->Get_S_LV();
	data->set_itemexp(exp);
	data->set_itemid(ItemId);
	data->set_level(lv);
	data->set_maxexp(maxExp);
	StoreMessage(MSG_S_LV, data, frame, NowFrame);
	SendMsg(INVALID_CHAIR, MSG_S_LV, data);
}