#pragma once
#include "SpawnModel.h"
#include <vector>
using namespace  std;

class MessageModel;
class SpawnCache
{
public:
	SpawnCache();
	~SpawnCache();

	void Bind(MessageModel* message);
	void Init();
	void Update(int frame);
	vector<SpawnModel> Dic;
	MessageModel* Message;
};

