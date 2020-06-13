#include "FMath.h"
#include "UWindow.h"

FVector3 FMath::ScreenToNDC(FVector2 Coordinate)
{
	auto& [x, y] = Coordinate;
	const auto [left, top, right, bottom] = UWindow::Instance().GetClientFRect();

	FVector3 v;
	v.x = ((float)x / (float)right) * 2.0f - 1.0f; //-1.0f;
	v.y = -(((float)y / (float)bottom) * 2.0f - 1.0f);// 1.0f;

	return v;
}
