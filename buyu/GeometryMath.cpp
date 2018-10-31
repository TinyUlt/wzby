#include "GeometryMath.h"


bool GeometryMath::CircleVsCircle(Vector2 positionA, float radiusA, Vector2 positionB, float radiusB)
{
	float num = (radiusA + radiusB) * (radiusA + radiusB);
	float num2 = (positionA - positionB).sqrMagnitude();
	return num2 < num;
}

bool GeometryMath::CircleVsThickLine(Vector2 position, float radius, Vector2 lineP1, Vector2 lineP2, float thickness, bool flatA)
{
	Vector2 closestPointOnLineSegment = GetClosestPointOnLineSegment(lineP1, lineP2, position);
	auto num = (closestPointOnLineSegment - position).sqrMagnitude();
	float num2 = radius + thickness;
	if (num <= num2 * num2)
	{
		if (!flatA)
		{
			return true;
		}
		if ((lineP2 - lineP1).dot(position - lineP1) > 0)
		{
			return true;
		}
	}
	return false;
}

Vector2 GeometryMath::GetClosestPointOnLineSegment(Vector2 lineP1, Vector2 lineP2, Vector2 point)
{
	Vector2 value = point - lineP1;
	Vector2 vector = lineP2 - lineP1;
	auto distanceSquared = vector.sqrMagnitude();
	float num = value.dot( vector);
	float num2 = 0;
	if (distanceSquared != 0)
	{
		num2 = num / distanceSquared;
	}
	if (num2 < 0)
	{
		return lineP1;
	}
	if (num2 > 1)
	{
		return lineP2;
	}
	return lineP1 + vector * num2;

}
