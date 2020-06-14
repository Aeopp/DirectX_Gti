#include "FMath.h"
#include "UWindow.h"
#include <cmath>
FVector3 FMath::ScreenToNDC(FVector2 Coordinate)
{
	auto& [x, y] = Coordinate;
	const auto [left, top, right, bottom] = UWindow::Instance().GetClientFRect();

	FVector3 v;
	v.x = (x / (int)right) * 2.0f - 1.0f; //-1.0f;
	v.y = -((y / (int)bottom) * 2.0f - 1.0f);// 1.0f;

	return v;
}

float FMath::Distance(const FVector2& Lhs, const FVector2& Rhs)
{
	float x, y;
	x = Rhs.x - Lhs.x;
	y = Rhs.y - Lhs.y;
	return sqrtf(x * x + y * y);
}
