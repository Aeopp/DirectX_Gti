#include "FVector.h"
#include <cmath>
#include "FMath.h"
#include "FMatrix44.h"
FVector3 FVector3::operator+(const FVector3& Rhs) const& noexcept
{
    return FVector3{ x + Rhs.x,y + Rhs.y,z + Rhs.z };
}

FVector3 FVector3::operator+(const float Scala) const& noexcept
{
    return FVector3{x+Scala,y+Scala,z+Scala};
}

bool FVector3::operator==(const FVector3& Rhs) const& noexcept
{
    if (std::fabs(x - Rhs.x) <= FMath::Eplision &&
        std::fabs(y - Rhs.y) <= FMath::Eplision &&
        std::fabs(z - Rhs.z) <= FMath::Eplision ){
        return true;
    }
    return false;
}

FVector3 FVector3::operator-(const FVector3& Rhs) const& noexcept
{
    // This - Rhs 
    return FVector3{ x - Rhs.x ,y- Rhs.y,z-Rhs.z  };
}

FVector3 FVector3::operator*(const float Scala) const& noexcept
{
    return FVector3{x*Scala,y*Scala,z*Scala};
}

FVector3 FVector3::operator/(const float Scala) const& noexcept
{
    return FVector3{x/Scala,y/Scala,z/Scala};
}

FVector3 FVector3::CrossProduct(const FVector3& Rhs) const& noexcept
{
    // yz zx xy
    return FVector3{       y*Rhs.z  - Rhs.z * y , z*Rhs.x - Rhs.x * z , x* Rhs.y - Rhs.y*z};
}

float FVector3::operator|(const FVector3& Rhs) const& noexcept
{
    return DotProduct(Rhs);
}

FVector3 FVector3::operator^(const FVector3& Rhs) const& noexcept
{
    return CrossProduct(Rhs);
}

float FVector3::DotProduct(const FVector3& Rhs) const& noexcept
{
    return  x * Rhs.x + y * Rhs.y + z * Rhs.z;
};

float FVector3::Length() const& noexcept
{
    return std::sqrtf(x * x + y * y + z * z);
}

FVector3 FVector3::Normalize() const& noexcept
{
    float _Length = Length();
    return FVector3{ x / _Length,y / _Length,z / _Length };
};

float FVector3::Angle(const FVector3& Rhs) const& noexcept
{
    FVector3 _Lhs = Normalize();
    FVector3 _Rhs = Rhs.Normalize();
    float Costheta{ _Lhs.DotProduct(_Rhs) };
    float RadianAngle = std::acosf(Costheta);
    return FMath::RadianTODegree(RadianAngle);
}

FVector3 FVector3::operator*(const FMatrix44& m)const& noexcept
{
    FVector3 v;
    v.x = x * m._11 + y * m._21 + z * m._31 + m._41;
    v.y = x * m._12 + y * m._22 + z * m._32 + m._42;
    v.z = x * m._13 + y * m._23 + z * m._33 + m._43;
    return v;

}

FVector2 FVector2::operator+(const FVector2& Rhs) const& noexcept
{
    return FVector2{ x + Rhs.x,y + Rhs.y };
}

FVector2 FVector2::operator+(const float Scala) const& noexcept
{
    return FVector2{ x + Scala,y + Scala};
}

bool FVector2::operator==(const FVector2& Rhs) const& noexcept
{
    if (std::fabs(x - Rhs.x) <= FMath::Eplision &&
        std::fabs(y - Rhs.y) <= FMath::Eplision ) {
        return true;
    }
    return false;
}

FVector2 FVector2::operator-(const FVector2& Rhs) const& noexcept
{
    // This - Rhs 
    return FVector2{ x - Rhs.x ,y - Rhs.y };
}

FVector2 FVector2::operator*(const float Scala) const& noexcept
{
    return FVector2{ x * Scala,y * Scala };
}

FVector2 FVector2::operator/(const float Scala) const& noexcept
{
    return FVector2{ x / Scala,y / Scala };
}

float FVector2::DotProduct(const FVector2& Rhs) const& noexcept
{
    return  x * Rhs.x + y * Rhs.y;
};
float FVector2::operator|(const FVector2& Rhs) const& noexcept
{
    return DotProduct(Rhs);
}
float FVector2::Length() const& noexcept
{
    return std::sqrtf(x * x + y * y );
}

FVector2 FVector2::Normalize() const& noexcept
{
    float _Length = Length();
    return FVector2{ x / _Length,y / _Length };
};

float FVector2::Angle(const FVector2& Rhs) const& noexcept
{
    FVector2 _Lhs = Normalize();
    FVector2 _Rhs = Rhs.Normalize();
    float Costheta{ _Lhs.DotProduct(_Rhs) };
    float RadianAngle = std::acosf(Costheta);
    return FMath::RadianTODegree(RadianAngle);
}

FVector4 FVector4::operator+(const FVector4& Rhs) const& noexcept
{
    return FVector4{ x + Rhs.x,y + Rhs.y,z + Rhs.z,w + Rhs.w };
}

FVector4 FVector4::operator+(const float Scala) const& noexcept
{
    return FVector4{ x + Scala,y + Scala,z + Scala,w + Scala };
}

bool FVector4::operator==(const FVector4& Rhs) const& noexcept
{
    if (std::fabs(x - Rhs.x) <= FMath::Eplision &&
        std::fabs(y - Rhs.y) <= FMath::Eplision &&
        std::fabs(z - Rhs.z) <= FMath::Eplision &&
        std::fabs(w  - Rhs.w ) <= FMath::Eplision) {
        return true;
    }
    return false;
}

FVector4 FVector4::operator-(const FVector4& Rhs) const& noexcept
{
    // This - Rhs 
    return FVector4{ x - Rhs.x ,y - Rhs.y,z - Rhs.z,w-Rhs.w };
}

FVector4 FVector4::operator*(const float Scala) const& noexcept
{
    return FVector4{ x * Scala,y * Scala,z * Scala,w * Scala };
}

FVector4 FVector4::operator/(const float Scala) const& noexcept
{
    return FVector4{ x / Scala,y / Scala,z / Scala ,w / Scala };
}

float FVector4::operator|(const FVector4& Rhs) const& noexcept
{
    return DotProduct(Rhs);
}

float FVector4::DotProduct(const FVector4& Rhs) const& noexcept
{
    return  x * Rhs.x + y * Rhs.y + z * Rhs.z + w * Rhs.w;
};

float FVector4::Length() const& noexcept
{
    return std::sqrtf(x * x + y * y + z * z + w*w);
}

FVector4 FVector4::Normalize() const& noexcept
{
    float _Length = Length();
    return FVector4{ x / _Length,y / _Length,z / _Length , w/_Length };
};

float FVector4::Angle(const FVector4& Rhs) const& noexcept
{
    FVector4 _Lhs = Normalize();
    FVector4 _Rhs = Rhs.Normalize();
    float Costheta{ _Lhs.DotProduct(_Rhs) };
    float RadianAngle = std::acosf(Costheta);
    return FMath::RadianTODegree(RadianAngle);
}





