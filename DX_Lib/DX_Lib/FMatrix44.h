#pragma once
#include <algorithm>
#include <array>

struct float44{
	union 
	{
		std::array<std::array<float, 4>, 4> element{};
		float _11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44;
	};
};


class FVector3;

struct FMatrix44 : public float44
{
	explicit FMatrix44() noexcept{
		Identity();
	}
	FMatrix44(const FMatrix44&) = default;
	FMatrix44(FMatrix44&&)noexcept = default;
	FMatrix44& operator=(const FMatrix44&) = default;
	FMatrix44& operator=(FMatrix44&&) = default;
	~FMatrix44()noexcept = default;




	inline void Identity() & noexcept {
		std::fill(std::begin(element), std::end(element),
			std::array<float, 4>{0.f, 0.f, 0.f, 0.f});
		_11 = _22 = _33 = _44 = 1;
	};

	inline FMatrix44 operator*(const FMatrix44& Rhs)const&  noexcept {
		FMatrix44 ret;
		for (int iColumn = 0; iColumn < 4; iColumn++)
		{
			for (int iRow = 0; iRow < 4; iRow++)
			{
				ret.element[iRow][iColumn] =
					element[iRow][0] * Rhs.element[0][iColumn] +
					element[iRow][1] * Rhs.element[1][iColumn] +
					element[iRow][2] * Rhs.element[2][iColumn] +
					element[iRow][3] * Rhs.element[3][iColumn];
			}
		}
		return ret;
	};

	void Scale(const FVector3& V);
	void XRotate(const float Radian);
	void YRotate(const float Radian);
	void ZRotate(const float Radian);
	void Translation(const FVector3& V);
	FMatrix44 Transpose();
	FMatrix44 Inverse(); 
};

