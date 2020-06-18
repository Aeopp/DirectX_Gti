#include "UCamera.h"
#include "helper.h"

void UCamera::SetOwner(AActor* POwner) & noexcept{
    _Owner = POwner;
}

AActor* UCamera::GetOwner() const& noexcept{
    return _Owner;  
}

bool UCamera::IsOwner() const& noexcept{
    return IsValid(_Owner);
}

bool UCamera::Init() noexcept{
    Super::Init();

    return true;
}

bool UCamera::Release() noexcept
{

    Super::Release();
    return true;
}

bool UCamera::Frame(float DeltaTime)
{
    Super::Frame(DeltaTime);

    return true;
}

bool UCamera::Render(float DeltaTime)
{
    Super::Render(DeltaTime);
    return true;
}
