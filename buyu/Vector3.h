#pragma once
extern const double uZero;
#include "gt_buyu.pb.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace gt_msg;
class Vector3
{
public:
	float x, y, z;
	static Vector3 zero;
	static Vector3 up;
	static Vector3 right;
	static Vector3 forward;
public:
	Vector3() :x(-9999), y(-9999), z(-9999){}
	Vector3(float x1, float y1, float z1) :x(x1), y(y1), z(z1){}
	Vector3(const Vector3 &v);
	Vector3(const gt_msg::Vec3 &v);
	Vector3(const gt_msg::Vec2 &v);
	~Vector3();
	void operator=(const Vector3 &v);
	Vector3 operator+(const Vector3 &v);
	Vector3 operator-(const Vector3 &v);
	Vector3 operator/(const Vector3 &v);
	Vector3 operator*(const Vector3 &v);
	Vector3 operator+(float f);
	Vector3 operator-(float f);
	Vector3 operator/(float f);
	Vector3 operator*(float f);
	void Set(float x, float y, float z);
	float dot(const Vector3 &v);
	float sqrMagnitude();
	float length();
	void normalize();
	Vector3 crossProduct(const Vector3 &v);
	static float SqrMagnitude(const Vector3 &v1, const Vector3 &v2);
	static Vector3 Normalized(const Vector3 &v);
	static float Distance(const Vector3 &v1, const Vector3 &v2);
	static Vector3 Cross(const Vector3 &v1, const Vector3 &v2);
	static float Dot(const Vector3 &v1 , const Vector3 &v2);
	//3个向量是否是同一边
	static bool SameSide( const Vector3& A,  const Vector3& B, const Vector3& C, const Vector3& P);
	//p点是否在三角形内
	static bool PointinTriangle(const Vector3& A,const Vector3& B,const Vector3& C,const Vector3& P);
	//3个向量是否是同一边
	static bool SameSideEX(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& P);
	//p点是否在三角形内
	static bool PointinTriangleEX(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& P);
	//p点是否在四边形内
	static bool PointinQuadrangleEX(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D, const Vector3& P);
	//点p是否再矩形内
	static bool PointinRectangle(const Vector3& v1, const Vector3& v2, const Vector3& P);
	//点v0延申固定长度ml(L^2)达到向量v1 v2上的点
	static bool TryGetPointInLineWitchIsLengthFrom1Point(const Vector3& v0, const Vector3& v1, const Vector3& v2, const float mL, Vector3& v3);
	static bool LinesCross(Vector3 A, Vector3 B, Vector3 C, Vector3 D);
	static bool InSide(Vector3& O, Vector3& V1, Vector3& V2, Vector3& P);
	void printVec3();
	bool  IsInvalidVec3()
	{
		if (x == -9999.0f)return true;
		else if (y == -9999.0f)return true;
		else if (z == -9999.0f)return true;

		return false;
	}
	void reset();
	void conver(const gt_msg::Vec3 &v);
	void addin(const Vector3 &v);
	void subin(const Vector3 &v);
	void addin(const Vec3 &v);
	void mulin(const float &f);
	void assignVec3(gt_msg::Vec3* v);
	void assignVec3(gt_msg::Vec3& v);
	bool equal(const Vector3 &v);
};

class Vector2
{
public:
	float x, y;
public:
	Vector2() :x(-9999), y(-9999){}
	Vector2(float x1, float y1) :x(x1), y(y1){}
	Vector2(const Vector2 &v);
	Vector2(const gt_msg::Vec2 &v);
	Vector2(const Vector3 &v);
	~Vector2();
	void operator=(const Vector2 &v);
	Vector2 operator+(Vector2 &v);
	Vector2 operator-(const Vector2 &v);
	Vector2 operator/(const Vector2 &v);
	Vector2 operator*(const Vector2 &v);
	Vector2 operator+(float f);
	Vector2 operator-(float f);
	Vector2 operator/(float f);
	Vector2 operator*(float f);
	float dot(const Vector2 &v);
	float sqrMagnitude();
	float length();
	void normalize();
	Vector2 crossProduct(const Vector2 &v);
	void printVec2();
	void reset();
	bool  IsInvalidVec2()
	{
		if (x == -9999.0f)return true;
		else if (y == -9999.0f)return true;

		return false;
	}
	void conver(const Vector3 &v);
};

