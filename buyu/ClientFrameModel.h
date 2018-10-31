#pragma once
#include "typedefine.h"
#include <vector>

using namespace std;

//class SendModel;
class ItemModel;
class MessageModel;
class ClientFrameModel
{
public:
	ClientFrameModel();
	~ClientFrameModel();

	void Init(int itemId);
	void Bind(MessageModel* message/*, SendModel* send*/);
	void Update(int frame);
	bool EnableSend();
	void SendDalayTest();
	void RevieveDalayTest();
	bool TryGetFrameOffset(int& frameOffset);

	bool Enable;
	int FrameOffset;
	vector<DWORD> DelaySendTestTicks;
	vector<DWORD> DelayRevieveTestTicks;
	const size_t DelayTestMaxCount = 5;
	bool EnableGetFrame;
	//ItemModel* Item;
	int ItemId;
	MessageModel* Message;
};

