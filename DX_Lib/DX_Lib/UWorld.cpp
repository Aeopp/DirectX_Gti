#include "UWorld.h"
#include <algorithm>
#include "helper.h"

UWorld::UWorld() {};
UWorld::~UWorld() noexcept {};

bool UWorld::Init()
{
    return true;
}

bool UWorld::Release() noexcept
{
    for (auto& Actor : ActorList) {
        DX::Safe_Release(Actor);
    };
    ActorList.clear();
    return true;
}

bool UWorld::Frame(float DeltaTime)
{
    for (auto& Actor : ActorList) {
        if (IsValid(Actor)) {
            Actor->Frame(DeltaTime);
        }
    }
    return true;
}

bool UWorld::Render(float DeltaTime)
{
    for (auto& Actor : ActorList) {
        if (IsValid(Actor)) {
            Actor->Render(DeltaTime);
        }
    }
    return true;
}
