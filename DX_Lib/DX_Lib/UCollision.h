#include "UObject.h"

#pragma once
class UCollision : public UObject
{
public:
	enum class ECollisionType :uint8_t {
		RECT,
		Sphere,
		Pixel,
	};

	bool Init()noexcept override;
	bool Release()noexcept override;
	bool Frame(float)override;
	bool Render(float)override;
};

