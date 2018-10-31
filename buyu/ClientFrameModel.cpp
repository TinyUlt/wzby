#include "Global.h"
#include "ClientFrameModel.h"
//#include "SendModel.h"
#include "ItemModel.h"
#include "MessageModel.h"

ClientFrameModel::ClientFrameModel()
{
	EnableGetFrame = false;
	Message = NULL;
	//Item = NULL;
}


ClientFrameModel::~ClientFrameModel()
{
}
void ClientFrameModel::Init(int itemId) {
	Enable = false;
	DelaySendTestTicks.clear();
	DelayRevieveTestTicks.clear();
	FrameOffset = 0;
	ItemId = itemId;
	EnableGetFrame = true;
}
void ClientFrameModel::Bind(MessageModel* message/*, SendModel* send*/) {
	//this->Send = send;
	//this->Item = item;
	this->Message = message;
}
void ClientFrameModel::Update(int frame) {
	if (!Enable) {
		return;
	}
	if (EnableSend()) {
		SendDalayTest();
		Message->SendTestDelayMsg(ItemId);
	}
}

bool ClientFrameModel::EnableSend() {
	if (DelaySendTestTicks.size() == DelayRevieveTestTicks.size() && DelaySendTestTicks.size() < DelayTestMaxCount) {
		return true;
	}
	return false;
}
void ClientFrameModel::SendDalayTest() {

	DelaySendTestTicks.push_back(GetTickCount());
}
void ClientFrameModel::RevieveDalayTest() {
	DelayRevieveTestTicks.push_back(GetTickCount());
}
bool ClientFrameModel::TryGetFrameOffset(int& frameOffset) {
	if (!EnableGetFrame) {
		return false;
	}
	if (DelaySendTestTicks.size() != DelayTestMaxCount ||
		DelayRevieveTestTicks.size() != DelayTestMaxCount) {
		return false;
	}

	vector<LONGLONG> tickOffset;
	for (size_t i = 0; i < DelayTestMaxCount; i++) {
		tickOffset.push_back(DelayRevieveTestTicks[i] - DelaySendTestTicks[i]);
	}

	LONGLONG maxValue = LONGLONGLOW;
	LONGLONG minValue = LONGLONGHIGH;
	for (size_t i = 0; i < DelayTestMaxCount; i++) {
		if (tickOffset[i] > maxValue) {
			maxValue = tickOffset[i];
		}
		if (tickOffset[i] < minValue) {
			minValue = tickOffset[i];
		}
	}
	LONGLONG sum = 0;
	for (size_t i = 0; i < DelayTestMaxCount; i++) {
		if (tickOffset[i] != maxValue && tickOffset[i] != minValue) {
			sum += tickOffset[i];
		}
	}
	LONGLONG avg = sum / (DelayTestMaxCount - 2);

	LONGLONG OneTimeDelay = avg / 2;

	frameOffset =(int)( 60 * OneTimeDelay / 1000);
	EnableGetFrame = false;
	return true;
}
