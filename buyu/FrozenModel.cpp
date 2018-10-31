#include "Global.h"
#include "FrozenModel.h"

FrozenModel::FrozenModel()
{
	IsFrozen = false;
}


FrozenModel::~FrozenModel()
{
}

void FrozenModel::Init(bool enable) {
	Enable = enable;
	IsFrozen = false;
	Reset();
}
void FrozenModel::Update(int frame) {

	if (!Enable) {
		return;
	}
	NowFrame = frame;
	
	if (IsFrozen == true) {
		PassFrameNow = frame - FreezenStartFrame;
		if (FreezenEndFrame < frame) {
			IsFrozen = false;
			PassFramePre += FreezenEndFrame - FreezenStartFrame;
			PassFrameNow = 0;
		}
	}
}

void FrozenModel::SetFreezen(S_Hit* freezen) {
	if (!Enable) {
		return;
	}
	List.push_back(*freezen);
	int endFrame = freezen->endframe();
	
	if (endFrame >= NowFrame) {
		IsFrozen = true;
	}
	PassFrameNow = 0;
	FreezenStartFrame = freezen->frame();
	FreezenEndFrame = endFrame;
}
int FrozenModel::GetPassFrame() {
	if (!Enable) {
		return 0;
	}
	return PassFrameNow + PassFramePre;
}
void FrozenModel::Reset() {
	PassFrameNow = 0;
	PassFramePre = 0;
	List.clear();
}