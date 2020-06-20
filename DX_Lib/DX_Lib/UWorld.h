#pragma once
#include "SingleTon.h"
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>

#include "UObject.h"
#include "AActor.h"
#include "helper.h"

class UWorld : public SingleTon<UWorld>
{
public:
	bool Init();
	bool Release()noexcept;
	bool Frame(float DeltaTime);
	bool Render(float DeltaTime);
private:
	std::vector<class AActor*> ActorList{};
	std::vector<class UMesh*> MeshList{};
	std::vector<class UCollision*> CollisionList{};
public:
	template<typename UObjectType,typename...ParamPassType>
	UObjectType* CreateObject(class AActor* Owner,ParamPassType&&... Params)& {
		static_assert(std::is_base_of_v<UObject, UObjectType>, "Is Not Base of UObjectType");
		if (IsValid(Owner)) {
			UObjectType* _NewObject = new UObjectType(std::forward<ParamPassType>(Params)...);
			_NewObject->SetOwner(Owner);
			Owner->AddComponent(_NewObject);

			if constexpr (std::is_same_v<UMesh, UObjectType>) {
				MeshList.push_back(_NewObject);
				std::sort(std::begin(MeshList), std::end(MeshList), 
				[](auto Lhs,auto Rhs) {
				return Lhs->Layer < Rhs->Layer;	});
			}
			else if constexpr (std::is_same_v<UCollision, UObjectType> ) {
				CollisionList.push_back(_NewObject);
			}

			return _NewObject;
		}
	};

	// 액터가 이미 오브젝트의 자원 해제 이후 호출된다고 가정
	// 단순히 월드가 관리하는 대상에서 제외시켜주는 작업
	template<typename UObjectType>
	void ExcludedObject(UObjectType* Object)& noexcept{
		static_assert(std::is_base_of_v<UObject, UObjectType>, "Is Not Base of UObjectType");
		if (IsValid(Object) == false)return;

		if constexpr (std::is_same_v<UMesh, UObjectType>) {
			if (auto iter = std::find(std::begin(MeshList), std::end(MeshList), Object);
				iter != std::end(MeshList)) {
				MeshList.erase(iter);
			}
		}
		else if constexpr (std::is_same_v<UCollision, UObjectType>) {
			if (auto iter = std::find(std::begin(CollisionList), std::end(CollisionList), Object);
				iter != std::end(CollisionList)) {
				CollisionList.erase(iter);
			}
		}
	}
	
	template<typename ActorType,typename ...ParamPassType>
	ActorType* CreateActor(ParamPassType&&... Params)&{
		static_assert(std::is_base_of_v<AActor, ActorType>, "Is Not Base of AActorType");

		ActorType* _NewActor = new ActorType(std::forward<ParamPassType>(Params)...);
		ActorList.push_back(_NewActor);
		return _NewActor;
	};

	void DeleteActor(class AActor* Target)&{
		if (IsValid(Target) == false)return;

		if (auto iter = std::find(std::begin(ActorList), std::end(ActorList), Target);
			iter != std::end(ActorList)) {
			Safe_Release(*iter);
			Safe_Delete(*iter);
			ActorList.erase(iter);
		}
	};

	DECLARE_SINGLETON(UWorld)
};
