#pragma once

struct FVector2 {
	FVector2() = default;
	FVector2(const int x, const int y) :
		x{ static_cast<float>(x) }, y{ static_cast<float>(y) }{};
	FVector2(const float x, const float y) :
		x{x}, y{y}		{};

	FVector2(const FVector2&) = default;
	FVector2(FVector2&&) = default;
	FVector2& operator=(FVector2&&) = default;
	FVector2& operator=(const FVector2&) noexcept = default;

	FVector2 operator+(const FVector2& Rhs)const& noexcept;
	FVector2 operator+(const float Scala)const& noexcept;
	bool operator==(const FVector2& Rhs)const& noexcept;
	FVector2 operator-(const FVector2& Rhs)const& noexcept;
	FVector2 operator*(const float Scala)const& noexcept;
	FVector2 operator/(const float Scala)const& noexcept;

	float DotProduct(const FVector2 & Rhs)const& noexcept;
	float Length()const& noexcept;
	FVector2 Normalize()const& noexcept;
	// Return Value Degree
	float Angle(const FVector2 & Rhs)const& noexcept;





	float x{};
	float y{};
};
struct FVector3 {
	FVector3() = default;
	FVector3(const int x, const int y, const int z) :
		x{ static_cast<float>(x) }, y{ static_cast<float>( y) }, z{ static_cast<float>(z)}{};
	FVector3(const float x, const float y, const float z) :
		x{ x }, y{ y }, z{ z }	{};

	//
	FVector3(const FVector3&) = default;
	FVector3(FVector3&&) noexcept= default;
	FVector3& operator=(FVector3&&) = default;
	FVector3& operator=(const FVector3&) noexcept = default;


	FVector3 operator+(const FVector3& Rhs)const& noexcept;
	FVector3 operator+(const float Scala)const& noexcept;
	bool operator==(const FVector3& Rhs)const&noexcept;
	FVector3 operator-(const FVector3& Rhs)const& noexcept;
	FVector3 operator*(const float Scala)const& noexcept;
	FVector3 operator/(const float Scala)const& noexcept;

	float DotProduct(const FVector3& Rhs)const& noexcept;
	float Length()const& noexcept;
	FVector3 Normalize()const& noexcept;
	// Return Value Degree
	float Angle(const FVector3& Rhs)const& noexcept;

	
	float x{};
	float  y{};
	float z{};
};
struct FVector4 {
	FVector4() = default;
	FVector4(const float x, const float y, const float z,const float w) :
		x{ x }, y{ y }, z{ z }, w{w}{};
	FVector4(const int x, const int y, const int z,const int w) :
		x{ static_cast<float>(x) }, y{ static_cast<float>(y) }, 
		z{ static_cast<float>(z) }, w{ static_cast<float>(w) } {};


	FVector4(const FVector4&) = default;
	FVector4(FVector4&&) = default;
	FVector4& operator=(FVector4&&) = default;
	FVector4& operator=(const FVector4&) noexcept = default;

	FVector4 operator+(const FVector4 & Rhs)const& noexcept;
	FVector4 operator+(const float Scala)const& noexcept;
	bool operator==(const FVector4 & Rhs)const& noexcept;
	FVector4 operator-(const FVector4 & Rhs)const& noexcept;
	FVector4 operator*(const float Scala)const& noexcept;
	FVector4 operator/(const float Scala)const& noexcept;

	float DotProduct(const FVector4 & Rhs)const& noexcept;
	float Length()const& noexcept;
	FVector4 Normalize()const& noexcept;
	// Return Value Degree
	float Angle(const FVector4 & Rhs)const& noexcept;


	float x{}; float  y{}; float  z{}; float  w{};
};

