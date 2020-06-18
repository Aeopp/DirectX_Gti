#pragma once
#include <numbers>
#include <numeric>
#include "FVector.h"
#include "FRect.h"

class FMath
{
public:
	static inline constexpr double PI = std::numbers::pi;
	static inline constexpr float Eplision = std::numeric_limits<float>::epsilon();
	static FVector3 ScreenToNDC(FVector2 Coordinate);
	static float Distance(const FVector2& Lhs, const FVector2& Rhs);
	static	float DegreeTORadian(const float Degree);
	static	float RadianTODegree(const float Degree);
};


