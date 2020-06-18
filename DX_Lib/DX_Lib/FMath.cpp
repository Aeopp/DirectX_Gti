#include "FMath.h"
#include "UWindow.h"
#include <cmath>
FVector3 FMath::ScreenToNDC(FVector2 Coordinate)
{
	auto& [WorldX, WorldY] = Coordinate;
	const auto [left, top, ClientWindowWidth, ClientWindowHeight] = UWindow::Instance().GetClientFRect();

	FVector3 Ndc_Pos;
	Ndc_Pos.x = (WorldX / (int)ClientWindowWidth) 
	* 2.0f - 1.0f; //-1.0f;
	Ndc_Pos.y = -((WorldY / (int)ClientWindowHeight) 
	* 2.0f - 1.0f);// 1.0f;

	return Ndc_Pos;
}

float FMath::Distance(const FVector2& Lhs, const FVector2& Rhs)
{
	float x, y;
	x = Rhs.x - Lhs.x;
	y = Rhs.y - Lhs.y;
	return sqrtf(x * x + y * y);
}

float FMath::DegreeTORadian(const float Degree)
{
	return Degree*(FMath::PI / 180.f);
}
float FMath::RadianTODegree(const float Radian)
{
	return  (180.f / FMath::PI) *Radian;
}
