#include "UWorld.h"
#include <algorithm>
#include "helper.h"
#include "UMesh.h"
#include "UCollision.h"
#include <iterator>


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
        Safe_Delete(Actor);
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
    };
    if (CollisionList.size() < 2) {
        // 충돌검사를 할 필요가없으므로 안한다.
    }
    for (auto Lhs = std::begin(CollisionList); Lhs != std::end(CollisionList);++Lhs){
        if (IsValid(*Lhs) == false || (*Lhs)->bEnable==false) {
            continue;
        }
        auto Rhs = Lhs;
        std::advance(Rhs, 1);

        for (Rhs; Rhs != std::end(CollisionList);++Rhs) {
            if (IsValid(*Rhs) == false || (*Rhs)->bEnable == false) {
                continue;
            }

            // 여기서 충돌 검사를 수행한다.
            // 서로 충돌했다면 서로 히트 이벤트를 발생시켜준다.
            
        }
    };
    for (auto& Mesh : MeshList) {
        if (IsValid(Mesh)) {
            Mesh->Frame(DeltaTime);
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
    for (auto& Collision : CollisionList) {
        if (IsValid(Collision)) {
            Collision->Render(DeltaTime);
        }
    }
    for (auto& Mesh : MeshList) {
        if (IsValid(Mesh)) {
            Mesh->Render(DeltaTime);
        }
    }
    return true;
}
