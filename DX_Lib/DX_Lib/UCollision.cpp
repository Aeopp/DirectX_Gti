#include "UCollision.h"
#include "FMath.h"

 bool UCollision::RectToRect(const FRect& Lhs, const FRect& Rhs) {
	if (Lhs.left > Rhs.right)
		return false;
	else if (Lhs.right < Rhs.left)
		return false;
	else if (Lhs.top > Rhs.bottom)
		return false;
	else if (Lhs.bottom < Rhs.top)
		return false;

	return true;
}

bool UCollision::RectToPoint(const FRect& Lhs, const FVector2& Rhs)
{
	if (Rhs.x < Lhs.left)
		return false;
	else if (Rhs.x > Lhs.right)
		return false;
	else if (Rhs.y < Lhs.top)
		return false;
	else if (Rhs.y > Lhs.bottom)
		return false;
	return true;
}

bool UCollision::SphereToPoint(const FRect& Lhs, const FVector2& Rhs)
{
	return FMath::Distance(Rhs, { (Lhs.right + Lhs.left) / 2,
		(Lhs.bottom + Lhs.top) / 2 });
}

bool UCollision::Init() noexcept
{
	return true;
};

bool UCollision::Release() noexcept
{
	return true;
};

bool UCollision::Frame(float)
{
	return true;
};

bool UCollision::Render(float)
{
	return true;
};
