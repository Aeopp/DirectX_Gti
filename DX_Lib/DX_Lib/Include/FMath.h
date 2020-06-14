#pragma once
#include <numbers>

#include "FVector.h"
#include "FRect.h"

class FMath
{
public:
	static inline constexpr double PI = std::numbers::pi;
	static FVector3 ScreenToNDC(FVector2 Coordinate);
	static float Distance(const FVector2& Lhs, const FVector2& Rhs);
};


