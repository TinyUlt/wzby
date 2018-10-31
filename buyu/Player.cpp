#include "Player.h"



Player::Player()
{
	ResetAll();
}


Player::~Player()
{
}
void Player::ResetDelayTest() {
	DelaySendTestTicks.clear();
	DelayRevieveTestTicks.clear();
	FrameOffset = 0;

	EnableGetFrame = true;
}
void Player::ResetScore() {
	Score = 0;
}
void Player::ResetAll() {

	IsEnterGameScene = false;
	ResetDelayTest();
	ResetScore();
	/*SendTestDelayTick = 0;
	RevieveTestDelayTick = 0;*/
	
}
bool Player::EnableSend() {
	if (DelaySendTestTicks.size() == DelayRevieveTestTicks.size()&& DelaySendTestTicks.size() < DelayTestMaxCount) {
		return true;
	}
	return false;
}
void Player::SendDalayTest() {
	 
	DelaySendTestTicks.push_back(GetTickCount());
}
void Player::RevieveDalayTest() {
	DelayRevieveTestTicks.push_back(GetTickCount());
}
bool Player::TryGetFrameOffset(int& frameOffset) {
	if (!EnableGetFrame) {
		return false;
	}
	if (DelaySendTestTicks.size() != DelayTestMaxCount ||
		DelayRevieveTestTicks.size() != DelayTestMaxCount) {
		return false;
	}

	vector<LONGLONG> tickOffset;
	for (int i = 0; i < DelayTestMaxCount; i++) {
		tickOffset.push_back(DelayRevieveTestTicks[i] - DelaySendTestTicks[i]);
	}
	
	LONGLONG maxValue= LONGLONGLOW;
	LONGLONG minValue = LONGLONGHIGH;
	for (int i = 0; i < DelayTestMaxCount; i++) {
		if (tickOffset[i] > maxValue) {
			maxValue = tickOffset[i];
		}
		if (tickOffset[i] < minValue) {
			minValue = tickOffset[i];
		}
	}
	LONGLONG sum = 0;
	for (int i = 0; i < DelayTestMaxCount; i++) {
		if (tickOffset[i] != maxValue && tickOffset[i] != minValue) {
			sum += tickOffset[i];
		}
	}
	LONGLONG avg = sum / (DelayTestMaxCount - 2);

	LONGLONG OneTimeDelay = avg / 2;

	frameOffset = 60 * OneTimeDelay / 1000;
	EnableGetFrame = false;
	return true;
}