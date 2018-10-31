#include "StdAfx.h"
#include "GameTable.h"
//#include "Vector3.h"
#include "typedefine.h"
#include <iostream>
#include <string>
//#include "PropHead.h"
//#include <json/json.h>
#include "Global.h"
#include "LogSys.h"
#include "MonsterHelper.h"
#include "MessageHelper.h"
#include "Global.h"
#include "PathHelper.h"
#include "SkillHelper.h"
GameTable::GameTable()
{
	m_table_frame_ = NULL;
}


GameTable::~GameTable()
{
	m_table_frame_ = NULL;
	
	//g_global.UnRegisterGameTable(this);
	
}
//int GameTable::GetNowFrame() {
//	return (int)(NowMillisecond - StartMillisecond) * 60 / 1000;
//}
void GameTable::Init(ITableFrame* iTableFrame) {
	m_table_frame_ = iTableFrame;
	StartMillisecond = GetTickCount();
	EnterMillisecond = StartMillisecond;
	LeaveMillisecond = StartMillisecond;
	//MonsterProduct.Init();
	UpdateTest.SetInterval(60);
	for (int i = 0; i < GAME_PLAYER; i++) {
	
		ClientFrame[i].Bind(&Message);
	}
	
	/*Monster *bbb;
	g_global.monsterHelper->TryGetMonster(&bbb);*/
	//char ch[32];
	//WideCharToMultiByte(CP_ACP, 0, iTableFrame->GetGameServiceOption()->szServerName, -1, ch, LEN_MD5, 0, 0);
	g_global.init();
	//PlayerManager.Bind(&PlayerManager, &ItemManager, &BulletManager, &Message, &Send);
	//PlayerManager.Bind(&BulletManager, &SpawnManager, &Message, &Send);
	BulletManager.Bind(&Message);
	ItemManager.Bind(&BulletManager, &SpawnManager, &Message, &Send);
	SpawnManager.Bind(&Message);
	Message.Bind(&ItemManager/*, &Send*/);
	Send.Bind(m_table_frame_);

	Message.Enable = true;
	
	//Monster *mmm;
	//g_global.monsterHelper->TryGetMonster(&mmm);
	//g_global.monsterHelper->TryGetMonster(&mmm);

	//g_global.messageHelper->Get_R_TestDelay();
	//g_global.messageHelper->Get_R_TestDelay();
	SpawnManager.Init();
}
int GameTable::GetDelayFrame(int frame) {
	return frame + g_global.ExecuteDelayFrameForServer;
}
int GameTable::GetDelayFrame() {
	return GetDelayFrame(NowFrame);
}
void GameTable::Update(DWORD tick) {
	NowMillisecond = GetTickCount();

	NowFrame = (int)(NowMillisecond - StartMillisecond - (EnterMillisecond - LeaveMillisecond)) * 60 / 1000;

	if (UpdateTest.Update(NowMillisecond)) {
		TestUpdate(NowFrame);
	}
	/*char ch[100];
	sprintf_s(ch, "frame:%d", NowFrame);
	g_global.logSys->LogInWindow(ch);*/

	Message.Update(NowFrame);
	ItemManager.Update(NowFrame);
	//PlayerManager.Update(NowFrame);
	SpawnManager.Update(NowFrame);
	TestDelayUpdate(NowFrame);
	
	BulletManager.Update(NowFrame);
}
void GameTable::StartGame(WORD chairId, int frameOffset){
	
	
	if (ItemManager.Dic.count(chairId) <= 0) {
		return;
	}
	auto item = ItemManager.Dic[chairId];
	Message.SendStartGame(
		chairId, 
		0, 
		NowFrame + frameOffset, 
		g_global.ExecuteDelayFrameForClien, 
		g_global.PosSendFrame, 
		item->Pos.Position
	);
	//Message.SendSpawnPlayers(chairId);
	Message.SendPrvMonsters(chairId);
	//Message.SendScoreAndExpierence(chairId);
	item->Enable = true;
}
bool GameTable::OnEventSendGameScene(
	WORD userCount, 
	WORD wChairID, 
	LONGLONG user_score, 
	LPCTSTR nickName, 
	DWORD gameId, 
	DWORD userId, 
	DWORD  experience, 
	bool isWeiXinUser, 
	TCHAR *openId,
	
	TCHAR * unionId,
	bool isAndroid, BYTE masterOrder, DWORD masterRight)
{
	
	user_score = 100000;
	//ClientFrame[wChairID].Init(wChairID);

	//表示断线重连的玩家
	/*if (PlayerManager.PlayerList[wChairID].Enable == true) {
		
		PlayerManager.PlayerList[wChairID].Enable = false;
	}
	else */
	//{
	vector<int > list;
	list.push_back(2);
	list.push_back(5);
	list.push_back(10);
	list.push_back(20);
	list.push_back(50);
	SpawnManager.Dic[0].Create(wChairID, -1, user_score, 10, 1, 10, list);
	StartGame(wChairID, 0);
		
	
	return true;
}

void GameTable::OnActionUserStandUp(WORD userCount , WORD chair_id, IServerUserItem* server_user_item, bool lookon_user) {

	
}
bool GameTable::OnFrameMessage(WORD wChairID, WORD cmdid, void* data, WORD data_size) {

	
	switch (cmdid)
	{
	case SUB_GF_USER_TAKE_SCORE: {
		
		

		return true;
	}
	case SUB_GF_USER_BAOFEN_SCORE: {
		
		

		return true;
	}
	default:
		return false;
	}
}
bool GameTable::OnGameMessage( DWORD userID,WORD wChairID, WORD cmdid, void* data, WORD data_size, BYTE masterOrder, DWORD masterRight)
{
	/*char ch2[100];
	sprintf_s(ch2, "cmdid:%d", cmdid);
	g_global.logSys->LogInWindow(ch2);*/
	if (wChairID < 0 || wChairID >= GAME_PLAYER) {
		g_global.logSys->LogInWindow("座位越界", TraceLevel_Warning);
		return false;
	}
	if (ItemManager.Dic.count(wChairID) == 0) {
		g_global.logSys->LogInWindow("无该玩家", TraceLevel_Warning);
		return false;
	}
	switch (cmdid) {
	
	case MSG_R_Move: {
		/*char ch[100];
		sprintf_s(ch, "move frame:%d", NowFrame);
		g_global.logSys->LogInWindow(ch);*/
		auto move = g_global.messageHelper->Get_R_Move(data, data_size);
		
		Message.SendMove(wChairID, move);
		//Revieve_SelfMove(wChairID, move);
		break;
	}
	case MSG_R_Attack: {
		char ch[100];
		sprintf_s(ch, "Attack frame:%d", NowFrame);
		g_global.logSys->LogInWindow(ch);
		//111111
		R_Attack* attack = g_global.messageHelper->Get_R_Attack(data, data_size);
		//Message.SendAttack(attack->frame(), wChairID, attack->victimid(), attack->skillid(), attack->skilllevel());
		Message.SendAttack( wChairID, attack);
		g_global.messageHelper->Back_R_Attack(attack);
		
		
		break;
	}
	case MSG_R_ChangeMultiple: {

		R_ChangeMultiple* recieveData = g_global.messageHelper->Get_R_ChangeMultiple(data, data_size);
		
		
		ItemModel* item = NULL;
		if (ItemManager.TryGetMonsterById(wChairID, &item)) {

			if (item->Mul.Contain(recieveData->value())) {
				Message.SendChangeMultiple(wChairID, recieveData);
			}
			
		}
		g_global.messageHelper->Back_R_ChangeMultiple(recieveData);
		//item->Mul.Set()
		break;
	}
	/*case MSG_R_HitTarget: {
		R_HitTarget* hit = g_global.messageHelper->Get_R_HitTarget(data, data_size);
		
		Revieve_SelfHigTarget(wChairID, hit);
		break;
	}*/
	case MSG_R_TestDelay: {
		auto delay = g_global.messageHelper->Get_R_TestDelay(data, data_size);
		
		Revieve_DelayTest(wChairID, delay);
		break;
	}
	/*case MSG_R_Freezen: {

		Recivev_Freezen(wChairID);
		break;
	}*/
	}
	
	return true;
}
void GameTable::OnEventUserEnter(int userCount)
{
	if (userCount == 1) {
		EnterMillisecond = GetTickCount();
	}
}

void GameTable::OnEventUserExit(int userCount)
{
	if (userCount == 0) {
		LeaveMillisecond = GetTickCount();
	}
}

void GameTable::OnDataBaseMessage(WORD request_id, void* data, WORD data_size) {

	
	
}
void GameTable::OnCalcScore(WORD chairId) { 
	if (ItemManager.Dic.count(chairId) == 0) {
		return;
	}
	ItemManager.Dic[chairId]->Enable = false;
	ItemManager.Dic.erase(chairId);
}