#pragma once
#include "BaseModel.h"
#include "TimerModel.h"
#include <random>
class MoveModel;
class FollowModel;
class ItemModel;
class FreedomModel :public BaseModel
{
public:
	FreedomModel();
	~FreedomModel();

	void Bind(ItemModel* host, MoveModel* move, FollowModel* follow);
	void Init(bool enable, int seed);
	void Update(int frame);

	void SetAPath();

	MoveModel* Move;
	FollowModel* Follow;
	ItemModel* Host;

	std::default_random_engine R;
	//PlayerModel* Player;
};

