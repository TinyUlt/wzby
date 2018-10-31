#pragma once
#include "Vector3.h"
#include "gt_buyu.pb.h"
using namespace gt_msg;
class PosModel
{
public:
	PosModel();
	~PosModel();

	//void Init(const Vec3& pos);
	void Init(const Vector3& pos, int cellIndex);
	void SetPosition(Vec3& pos);
	void GetPosition(Vec3* pos);
	void SetPosition(const Vec3& pos, int cellIndex);
	Vector3 Position;
	int CellIndex;
};

