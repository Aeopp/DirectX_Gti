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
        Safe_Release(Actor);
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
        // �浹�˻縦 �� �ʿ䰡�����Ƿ� ���Ѵ�.
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

            // ���⼭ �浹 �˻縦 �����Ѵ�.
            // ���� �浹�ߴٸ� ���� ��Ʈ �̺�Ʈ�� �߻������ش�.
            
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

//inline void UWorld::ExcludedObject(UObject* Object) & noexcept {
//
//    if (IsValid(Object) == false)return;
//
//    if (auto IsActor = dynamic_cast<AActor*>(Object);
//        IsValid(IsActor)) {
//        DeleteActor(IsActor);
//    }
//    else if (auto IsMesh = dynamic_cast<UMesh*>(Object);
//        IsValid(IsMesh)) {
//        if (auto iter = std::find(std::begin(MeshList), std::end(MeshList), Object);
//            iter != std::end(MeshList)) {
//            MeshList.erase(iter);
//        }
//    }
//    else if (auto IsCollision = dynamic_cast<UCollision*>(Object);
//        IsValid(IsMesh)) {
//        if (auto iter = std::find(std::begin(CollisionList), std::end(CollisionList), Object);
//            iter != std::end(CollisionList)) {
//            CollisionList.erase(iter);
//        }
//    }
//}
