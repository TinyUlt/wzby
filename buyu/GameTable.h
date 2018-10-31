#pragma once
//
#include <queue>

#include "Vector3.h"
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>
#include "gt_buyu.pb.h"
#include "HttpClient.h"
#include "TimeController.h"
#include "ClientFrameModel.h"
#include "ItemCache.h"
#include "TimerModel.h"
#include "MessageModel.h"
#include "SendModel.h"
#include "BulletCache.h"
#include "SpawnCache.h"
using namespace std;
using namespace gt_msg;
//using namespace network;

//struct CMD_GP_C_PropertyBuy;
////kz接口
//interface ITableCon
//{
//public:
//	virtual void SetMaxFishMul(int   nMaxFish) = NULL;
//	//更新子弹库存
//	virtual void UpdateUserBullet(bool   bIsRobot, WORD  wChairID, int nBulletIndex, int  nBulletScore, LONGLONG llCurWinScore) = NULL;
//	//鱼库存是否足够
//	virtual bool ModifyFishStock(WORD  wChairID, int nHitFishMul,LONGLONG llFishScore, LONGLONG llCurWinScore) = NULL;
//	//清理库存
//	virtual bool ClearUserStock(WORD wChairID) = NULL;
//
//	virtual int  GetPlayGameLv(DWORD  dwGameid) = NULL;
//
//};
interface ITableFrame;
struct  OnEvent{
	WORD seatId;
	WORD cmdid;
	::google::protobuf::Message*  message;
	LONGLONG user_score;
};
struct OnGameSceneEvent {
	WORD seatId;
	LONGLONG user_score;
	LPCTSTR nickName;
	DWORD gameID;
	DWORD experience;
};
//struct OnPropertyBuy {
//	WORD seatId;
//	CMD_GP_C_PropertyBuy* data;
//};
//enum CompetitionStatus
//{
//	WaitingForOne,
//	FirstIn,
//	GameStart,
//	GameOver,
//};

class GameTable
{
public:
	GameTable();
	~GameTable();


	//底层桌子句柄
	ITableFrame* m_table_frame_;
	//c句柄
	//ITableCon* m_table_con;

	//玩家列表
	
	//Product MonsterProduct;
	ItemCache ItemManager;
	//ItemCache PlayerManager;
	BulletCache BulletManager;
	SpawnCache SpawnManager;

	DWORD StartMillisecond;
	DWORD NowMillisecond;
	DWORD OldMillisecond;

	DWORD EnterMillisecond;
	DWORD LeaveMillisecond;
	int NowFrame;

	//UpdateBase UpdateMonster;
	TimerModel UpdateTest;
	TimerModel UpdateDelayTest;
	MessageModel Message;
	SendModel Send;
	ClientFrameModel ClientFrame[GAME_PLAYER];

	//int GetNowFrame();
	//queue<TobeMessage*>ToDoThings;
	//map<int, S_SpawnItem*> TodoMonsters;

	void GameTable::Init(ITableFrame* table_frame_);
	int GetDelayFrame(int frame);
	int GetDelayFrame();
	//主循环
	void Update(DWORD tick);
	void StartGame(WORD chairId, int frameOffset);

	//测试
	void TestUpdate(int frame);
	void TestDelayUpdate(int frame);
	void Revieve_DelayTest(WORD chairId, R_TestDelay* pack);

	//怪逻辑
	void MonstersUpdate(int frame);
	//void MonstersSpawn();
	//void MonsterKill();
	//void SendPrvMonsters(WORD wChairID);
	//void UpdateMonsterMove();
	//void Send_MonsterMove();
	//void GetTodoSpawnItem(vector<S_SpawnItem*>& list);
	////消息逻辑
	//void MessageUpdate(int frame);
	//void StoreClientMessage(WORD chairId, google::protobuf::Message* msg, int toBeFrame, int nowFrame);
	//void StoreServerMessage(google::protobuf::Message* msg, int toBeFrame);
	//void ExcuteMessage(google::protobuf::Message* msg);
	//玩家逻辑
	//void PlayersUpdate(int frame);
	//void Revieve_SelfMove(WORD chairId, R_Move* move);
	//void Send_SelfMove(WORD chairId, R_Move* move);
	//void Send_OtherSPos(WORD chairId, int frame);
	//void Send_SpawnPlayers(WORD chairId);
	//void Revieve_SelfAttack(WORD chairId, R_Attack* attack);
	//void Send_SelfAttack(WORD chairId, R_Attack* attack);
	//void Revieve_SelfHigTarget(WORD chairId, R_HitTarget* hit);
	//void Send_PlayerSocre(WORD chairId);
	//void Recivev_Freezen(WORD chairId);
	//
	bool OnEventSendGameScene(WORD userCount, WORD wChairID, LONGLONG user_score, LPCTSTR nickName, DWORD gameId, DWORD userId, DWORD  experience, bool isWeiXinUser, TCHAR *openId, TCHAR * unionId, bool isAndroid, BYTE masterOrder, DWORD masterRight);
	//用户离开
	void OnEventUserExit(int userCount);
	//客户端消息
	bool OnFrameMessage(WORD wChairID, WORD cmdid, void* data, WORD data_size);
	bool OnGameMessage(DWORD userID, WORD wChairID, WORD cmdid, void* data, WORD data_size, BYTE masterOrder, DWORD masterRight);
	void OnActionUserStandUp(WORD userCount, WORD chair_id, IServerUserItem* server_user_item, bool lookon_user);
	//void InAddProp(WORD wChairID, CMD_GP_C_PropertyBuy* data);
	void WXHttpFinish(network::HttpClient *httpClient, network::HttpResponse *response);
	//用户进入
	void OnEventUserEnter(int userCount);
	//数据库消息接收
	void OnDataBaseMessage(WORD request_id, void* data, WORD data_size);
	//游戏退出后的结算
	void OnCalcScore(WORD chairId);
	//void SendTestDelayMsg(WORD wChairID, MSG_ID id, google::protobuf::Message* msg);
	//void SendMsg(WORD wChairID, MSG_ID id, google::protobuf::Message* msg);
	//void Broadcast(WORD wChairID, MSG_ID id, google::protobuf::Message* msg);
};

