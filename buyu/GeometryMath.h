#pragma once
#include "Vector3.h"

class GeometryMath
{
public:
	static bool CircleVsCircle(Vector2 positionA, float radiusA, Vector2 positionB, float radiusB);
	static bool CircleVsThickLine(Vector2 position, float radius, Vector2 lineP1, Vector2 lineP2, float thickness, bool flatA);
	static Vector2 GetClosestPointOnLineSegment(Vector2 lineP1, Vector2 lineP2, Vector2 point);
};

