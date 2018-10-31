#pragma once
#include <vector>
#include "gt_buyu.pb.h"
using namespace gt_msg;
using namespace std;
class FrozenModel
{
public:
	FrozenModel();
	~FrozenModel();
	void Init(bool enable);
	void Update(int frame);
	void SetFreezen(S_Hit* freezen);
	int GetPassFrame();
	void Reset();
	bool Enable;
	bool IsFrozen;
	int FreezenStartFrame;
	int FreezenEndFrame;
	int NowFrame;
	
	int PassFrameNow;
	int PassFramePre;
	vector<S_Hit> List;
};
