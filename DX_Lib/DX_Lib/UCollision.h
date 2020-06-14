#include "UObject.h"
#include "FRect.h"
#include "FVector.h"


#pragma once
class UCollision : public UObject
{
public:
	enum class ECollisionType :uint8_t {
		RECT,
		Sphere,
		Pixel,
	};

	static  bool RectToRect(const FRect& Lhs, const FRect& Rhs);;
	static  bool RectToPoint(const FRect& Lhs, const FVector2& Rhs);
	static  bool SphereToPoint(const FRect& Lhs, const FVector2& Rhs);

	bool Init()noexcept override;
	bool Release()noexcept override;
	bool Frame(float)override;
	bool Render(float)override;
};

