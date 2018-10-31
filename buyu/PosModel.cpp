#include "Global.h"
#include "PosModel.h"



PosModel::PosModel()
{
}


PosModel::~PosModel()
{
}
//void PosModel::Init(const Vec3& pos) {
//	Position = pos;
//}
void PosModel::Init(const Vector3& pos, int cellIndex) {

	Position = pos;
	CellIndex = cellIndex;

}
void PosModel::SetPosition(Vec3& pos) {
	Position.conver(pos);
}
void PosModel::GetPosition(Vec3* pos) {
	Position.assignVec3(pos);
}
void PosModel::SetPosition(const Vec3& pos, int cellIndex) {
	Position = pos;
	CellIndex = cellIndex;
}