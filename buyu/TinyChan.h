#pragma once
#include <mutex>
#include <queue>
using namespace std;
enum ChanType
{
	StopGame_Chan,
	ProductFish_Chan,//产鱼通道
	Give_RedBag_Chan,
	Back_RedBag_Chan,
	Cost_RedBag_Chan,
	SendRedpackPoint_Chan,
	ScorePreRMBRate_Chan,
	Tax2RedpackRate_Chan,
	TaxRate_Chan,
	RedpackPerHour_Chan,
	SendRedpackTimeSpace_Chan,
	ClientRequestInfo_Chan,
	MaxTakeRedPackSum_Chan,
	MaxSingleRedPack_Chan,
	EabelRebpack_Chan,
	UpdateUserBounty_Chan

};
class Chan {
public:
	Chan();
	~Chan();
	ChanType type;
	void *data;
	bool isRef;
	int ConverToInt();
	float ConverToFloat();
	bool ConverToBool();
};
class TinyChan
{
public:
	TinyChan();
	~TinyChan();
	void Reset();
	//通道写入
	void PushGameChan(Chan* c);
	void PushGameChan(ChanType t , void* d, bool isRef = false);

	//通道读取
	Chan*  PopGameChan();

	bool IsEmpty();

private:
	//消息通道
	std::queue<Chan*> GameChan;
	//通道锁
	std::mutex mutex_chan_;

	


};

