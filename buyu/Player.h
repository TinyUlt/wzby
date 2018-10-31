#pragma once
#include "ItemBase.h"
#include "MessageHelper.h"
#include <queue>
class Player:public ItemBase
{
public:
	Player();
	~Player();

	bool IsEnterGameScene;
	LONGLONG Score;

	int FrameOffset;
	queue<TobeMessage*>ToDoThings;
	
	void SendDalayTest();
	void RevieveDalayTest();
	bool TryGetFrameOffset(int& frameOffset);

	void ResetDelayTest();
	void ResetScore();
	void ResetAll();
	bool EnableSend();

private:
	vector<DWORD> DelaySendTestTicks;
	vector<DWORD> DelayRevieveTestTicks;
	const int DelayTestMaxCount = 5;
	bool EnableGetFrame;
};

