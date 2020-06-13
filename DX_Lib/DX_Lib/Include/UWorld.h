#pragma once
#include "SingleTon.h"
#include <type_traits>
#include <utility>
#include <vector>

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
public:
	template<typename UObjectType,typename...ParamPassType>
	UObjectType* CreateObject(class AActor* Owner,ParamPassType&&... Params)& {
		static_assert(std::is_base_of_v<UObject, UObjectType>, "Is Not Base of UObjectType");
		if (IsValid(Owner)) {
			UObjectType* _NewObject = new UObjectType(std::forward<ParamPassType>(Params)...);
			_NewObject->SetOwner(Owner);
			Owner->AddComponent(_NewObject);

			return _NewObject;
		}
	};

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
			(*iter)->Release();
			ActorList.erase(iter);
		}
	};

	DECLARE_SINGLETON(UWorld)
};
