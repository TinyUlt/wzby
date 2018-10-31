//#include "stdafx.h"
#include "Vector3.h"


//#include"Plane.h"  
#include<iostream>  

const double uZero = 1e-6;
Vector3 Vector3::zero = Vector3(0, 0, 0);
Vector3 Vector3::up = Vector3(0, 1, 0);
Vector3 Vector3::right = Vector3(1, 0, 0);
Vector3 Vector3::forward = Vector3(0, 0, 1);
//复制构造函数，必须为常量引用参数，否则编译不通过  
Vector3::Vector3(const Vector3 &v) :x(v.x), y(v.y), z(v.z)
{
}

Vector3::~Vector3()
{
}
Vector3::Vector3(const gt_msg::Vec3 &v)
{
	conver(v);
}
Vector3::Vector3(const gt_msg::Vec2 &v)
{
	  x = v.x();
	  y = v.y();
	  z = 0;
}
void Vector3::operator=(const Vector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3 Vector3::operator+(const Vector3 &v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v)
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator/(const Vector3 &v)
{
	if (fabsf(v.x) <= uZero || fabsf(v.y) <= uZero || fabsf(v.z) <= uZero)
	{
		std::cerr << "Over flow!\n";
		return *this;
	}
	return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::operator*(const Vector3 &v)
{
	return Vector3(x*v.x, y*v.y, z*v.z);
}

Vector3 Vector3::operator+(float f)
{
	return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator-(float f)
{
	return Vector3(x - f, y - f, z - f);
}

Vector3 Vector3::operator/(float f)
{
	if (fabsf(f) < uZero)
	{
		std::cerr << "Over flow!\n";
		return *this;
	}
	return Vector3(x / f, y / f, z / f);
}

Vector3 Vector3::operator*(float f)
{
	return Vector3(x*f, y*f, z*f);
}
void Vector3::Set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
float Vector3::dot(const Vector3 &v)
{
	return x*v.x + y*v.y + z*v.z;
}
float Vector3::sqrMagnitude(){

	  return dot(*this);
}
float Vector3::length()
{
	return sqrtf(dot(*this));
}

void Vector3::normalize()
{
	float len = length();
	if (len < uZero) len = 1;
	//len = 1 / len;

	x /= len;
	y /= len;
	z /= len;
}
Vector3 Vector3::Normalized(const Vector3 &v) {
	double len = sqrt( v.x * v.x + v.y * v.y + v.z * v.z);
	if (len < uZero) len = 1;
	//len = 1 / len;
	return Vector3(v.x / len, v.y / len, v.z / len);
}
float Vector3::SqrMagnitude(const Vector3 &v1, const Vector3 &v2) {
	float x = v1.x - v2.x;
	float y = v1.y - v2.y;
	float z = v1.z - v2.z;
	return (x*x + y*y + z * z);
}
/*
Cross Product叉乘公式
aXb = | i,  j,  k  |
| a.x a.y a.z|
| b.x b.y b.z| = (a.x*b.z -a.z*b.y)i + (a.z*b.x - a.x*b.z)j + (a.x+b.y - a.y*b.x)k
*/
Vector3 Vector3::crossProduct(const Vector3 &v)
{
	return Vector3(y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}
float Vector3::Distance(const Vector3 &v1, const Vector3 &v2) {
	Vector3 v3 = v1;
	v3.subin(v2);
	return v3.length();
}
Vector3 Vector3::Cross(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}
float Vector3::Dot(const Vector3 &v1, const Vector3 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
//3个向量是否是同一边
bool Vector3::SameSide(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& P)
{
	auto A2 = A;
	Vector3 BA = A2 - B;
	Vector3 CA = A2 - C;
	Vector3 PA = A2 - P;

	Vector3 v1 = Vector3::Cross(BA, CA);
	Vector3 v2 = Vector3::Cross(BA, PA);//a × b = |a| |b| sin(θ) n

										// v1 and v2 should point to the same direction
	return Vector3::Dot(v1, v2) > 0;// v1.Dot(v2) >= 0;点乘的结果越大，表示两个向量越接近
}
//p点是否在三角形内
bool Vector3::PointinTriangle(const Vector3& A,const Vector3& B,const Vector3& C,const Vector3& P)
{
	return 
		SameSide(A, B, C, P) &&
		SameSide(B, C, A, P) &&
		SameSide(C, A, B, P);
}
bool Vector3::SameSideEX(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& P)
{
	auto A2 = A;
	Vector3 BA = A2 - B;
	Vector3 CA = A2 - C;
	Vector3 PA = A2 - P;

	Vector3 v1 = Vector3::Cross(BA, CA);
	Vector3 v2 = Vector3::Cross(BA, PA);//a × b = |a| |b| sin(θ) n

										// v1 and v2 should point to the same direction
	return Vector3::Dot(v1, v2) >= 0;// v1.Dot(v2) >= 0;点乘的结果越大，表示两个向量越接近
}
//p点是否在三角形内
bool Vector3::PointinTriangleEX(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& P)
{
	return 
		SameSideEX(A, B, C, P) &&
		SameSideEX(B, C, A, P) &&
		SameSideEX(C, A, B, P);
}
//p点是否在四边形内
bool Vector3::PointinQuadrangleEX(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D, const Vector3& P) {
	return
		SameSideEX(A, B, D, P) &&
		SameSideEX(D, A, C, P) &&
		SameSideEX(C, D, B, P) &&
		SameSideEX(B, C, A, P);
}
//AB 和 CD 是否相交
 bool Vector3::LinesCross(Vector3 A, Vector3 B, Vector3 C, Vector3 D)
{
	bool b1 = InSide(C, A, B, D);
	bool b2 = InSide(A, C, D, B);
	//bool b3 = PointInVector2(C, D, A);
	//bool b4 = PointInVector2(C, D, B);
	return b1 && b2 /*|| b3 || b4*/;
}
 //判断PO是否在 V1O V2O 中间
bool Vector3::InSide( Vector3& O, Vector3& V1, Vector3& V2, Vector3& P)
 {
	 Vector3& V1O = V1 - O;
	 Vector3& V2O = V2 - O;
	 Vector3& PO = P - O;

	 Vector3& v1 = Vector3::Cross(PO, V1O);
	 Vector3& v2 = Vector3::Cross(PO, V2O);

	 return Vector3::Dot(v1, v2) <= 0;
 }
bool Vector3::TryGetPointInLineWitchIsLengthFrom1Point(const Vector3& v0, const Vector3& v1, const Vector3& v2, const float mL, Vector3& v3) {

	

	float x0 = v0.x;
	float y0 = v0.z;
	float x1 = v1.x - x0;
	float y1 = v1.z - y0;
	float x2 = v2.x - x0;
	float y2 = v2.z - y0;

	auto x2x1 = x2 - x1;
	if (x2x1 == 0) {
		x2x1 = fmaxf((x2 - x1), (float)0.0001);
	}
	auto a = (y2 - y1) / x2x1;
	auto b = y2 - (y2 - y1) / x2x1 * x2;

	auto t1 = (mL - b * b) / (1 + a * a) + powf(a * b / (1 + a * a), 2);
	if (t1 >= 0)
	{
		t1 = sqrtf(t1);
		auto t2 = a * b / (a * a + 1);

		bool f1enable = false;
		bool f2enable = false;
		auto fx1 = t1 - t2;
		auto fy1 = fx1 * a + b;

		auto fx2 = -t1 - t2 ;
		auto fy2 = fx2 * a + b ;

		if (fx1 >= fminf(x1, x2) && fx1 <= fmaxf(x1, x2) && fy1>fminf(y1, y2) && fy1 <= fmaxf(y1, y2)) {
			f1enable = true;
			
		}
		if (fx2 >= fminf(x1, x2) && fx2 <= fmaxf(x1, x2) && fy2>fminf(y1, y2) && fy2 <= fmaxf(y1, y2)) {
			f2enable = true;
		}

		if (f1enable && f2enable) {
			if ((fx1 - x2)*(fx1 - x2) + (fy1 - y2)*(fy1 - y2) > (fx2 - x2)*(fx2 - x2) + (fy2 - y2)*(fy2 - y2)) {
				f1enable = false;

			}
			else {
				f2enable = false;
			}
		}
		if (f1enable) {
			v3.x = fx1 + x0;
			v3.z = fy1 + y0;
			v3.y = 0;

			return true;
		}
		else if (f2enable) {
			v3.x = fx2 + x0;
			v3.z = fy2 + y0;
			v3.y = 0;
			return true;
		}
		return false;
	}
	return false;
}
bool Vector3::PointinRectangle(const Vector3& v1, const Vector3& v2, const Vector3& P) {
	return (P.x > fmin(v1.x, v2.x) && P.x < fmax(v1.x, v2.x) && P.y > fmin(v1.y, v2.y) && P.y < fmax(v1.y, v2.y));
}
void Vector3::printVec3()
{
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}


void Vector3::reset()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

void Vector3::conver(const gt_msg::Vec3 &v)
{
	x = v.x();
	y = v.y();
	z = v.z();
}
void Vector3::subin(const Vector3 &v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
void Vector3::addin(const Vector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
void Vector3::addin(const Vec3 &v) {
	x += v.x();
	y += v.y();
	z += v.z();
}
void Vector3::mulin(const float &f)
{
	x *= f;
	y *= f;
	z *= f;
}
void Vector3::assignVec3(gt_msg::Vec3* v) {
	v->set_x(x);
	v->set_y(y);
	v->set_z(z);
}
void Vector3::assignVec3(gt_msg::Vec3& v) {
	v.set_x(x);
	v.set_y(y);
	v.set_z(z);
}
bool Vector3::equal(const Vector3 &v) {
	if (v.x == this->x && v.y == this->y && v.z == this->z) {
		return true;
	}
	return false;
}


//复制构造函数，必须为常量引用参数，否则编译不通过  
Vector2::Vector2(const Vector2 &v) :x(v.x), y(v.y)
{
}
Vector2::Vector2(const Vector3 &v) :x(v.x), y(v.y){

}
Vector2::~Vector2()
{
}
Vector2::Vector2(const gt_msg::Vec2 &v)
{
	x = v.x();
	y = v.y();
}
void Vector2::operator=(const Vector2 &v)
{
	x = v.x;
	y = v.y;
}

Vector2 Vector2::operator+(Vector2 &v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v)
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator/(const Vector2 &v)
{
	if (fabsf(v.x) <= uZero || fabsf(v.y) <= uZero )
	{
		std::cerr << "Over flow!\n";
		return *this;
	}
	return Vector2(x / v.x, y / v.y);
}

Vector2 Vector2::operator*(const Vector2 &v)
{
	return Vector2(x*v.x, y*v.y);
}

Vector2 Vector2::operator+(float f)
{
	return Vector2(x + f, y + f);
}

Vector2 Vector2::operator-(float f)
{
	return Vector2(x - f, y - f);
}

Vector2 Vector2::operator/(float f)
{
	if (fabsf(f) < uZero)
	{
		std::cerr << "Over flow!\n";
		return *this;
	}
	return Vector2(x / f, y / f);
}

Vector2 Vector2::operator*(float f)
{
	return Vector2(x*f, y*f);
}
float Vector2::sqrMagnitude(){

	  return dot(*this);
}
float Vector2::dot(const Vector2 &v)
{
	return x*v.x + y*v.y ;
}

float Vector2::length()
{
	return sqrtf(dot(*this));
}

void Vector2::normalize()
{
	float len = length();
	if (len < uZero) len = 1;
	len = 1 / len;

	x *= len;
	y *= len;
}

/*
Cross Product叉乘公式
aXb = | i,  j,  k  |
| a.x a.y a.z|
| b.x b.y b.z| = (a.x*b.z -a.z*b.y)i + (a.z*b.x - a.x*b.z)j + (a.x+b.y - a.y*b.x)k
*/


void Vector2::printVec2()
{
	std::cout << "(" << x << ", " << y <<  ")" << std::endl;
}

void Vector2::conver(const Vector3 &v)
{
	x = v.x;
	y = v.y;
}

void Vector2::reset()
{
	this->x = 0;
	this->y = 0;

}