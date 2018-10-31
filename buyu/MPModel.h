#pragma once
#include "ValueModel.h"
class MessageModel;
class ItemModel;
class MPModel
{
public:
	MPModel();
	~MPModel();

	void Bind(ItemModel* host, MessageModel* message);
	void Init(int value);
	void Update(int frame);

	ItemModel* Host;
	ValueModel Value;
	MessageModel* Message;

};

