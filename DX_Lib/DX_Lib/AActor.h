#pragma once
#include "UObject.h"
#include "FVector.h"
#include "helper.h"

#include <type_traits>
#include <utility>
#include <vector>
#include <typeinfo>


class AActor : public UObject
{
private:
	friend class UWorld;

	class UMesh* _Mesh = nullptr; 
	class UCollision* _Collision = nullptr;
	std::vector<class UObject*>ComponentList{};
	FVector3 _Location{}; 
	FVector3 Velocity{};
public:
	virtual ~AActor()noexcept;
	using Super = UObject; 
	virtual bool Init()noexcept;
	virtual bool Release()noexcept;
	virtual bool Frame(float);
	virtual bool Render(float);

	template<typename UObjectType>
	void AddComponent(UObjectType* _Object)&;
	template <typename UObjectType>
	void EraseComponent(UObjectType* _Object)&;

	void SetMesh(class UMesh* Rhs) & noexcept;
	
	inline FVector3 GetVelocity() noexcept {
		return Velocity;
	}; 
	inline void SetVelocity(FVector3 _SetLocation) noexcept {
		Velocity = std::move(_SetLocation);
	}
	inline class UMesh* GetMesh()const& noexcept {
		return _Mesh;
	};
	inline FVector3 GetLocation()const&noexcept{
		return _Location;
	}
	inline void SetLocation(FVector3 Rhs)&noexcept {
		_Location = std::move_if_noexcept(Rhs);
	}

	void MoveForward( float DeltaTime);
	void MoveBackward( float DeltaTime);
	void MoveRight( float DeltaTime);
	void MoveLeft( float DeltaTime);
private:
	template <typename UObjectType>
	void SetComponentMemberVariableByObjectType(UObjectType* ComponentType);
protected:
	AActor() = default;
	
};

template<typename UObjectType>
void AActor::AddComponent(UObjectType* _Object)&
{
	if (IsValid(_Object) == false)return;

	ComponentList.push_back(_Object);
	SetComponentMemberVariableByObjectType(_Object);
};

template <typename UObjectType>
void AActor::SetComponentMemberVariableByObjectType(UObjectType* ComponentType) {
	if (IsValid(ComponentType) == false) {
		return; 
	}

	if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Mesh)>, UObjectType>) {
		_Mesh = ComponentType;
	}
	else if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Collision)>, UObjectType>) {
		_Collision = ComponentType;
	};
};

// 런타임 타입체크아님 타입 명시해줘야 제대로 지워짐
template <typename UObjectType>
void AActor::EraseComponent(UObjectType* _Object)&
{
	if (IsValid(_Object) == false)return;

	if (auto iter = std::find(std::begin(ComponentList), std::end(ComponentList), _Object);
		iter != std::end(ComponentList)) {
		Safe_Release(*iter);
		Safe_Delete(*iter);
		ComponentList.erase(iter);
		// 액터에서 완전히 정리한 이후 월드가 관리하는 대상에서도 제외시켜준다
		UWorld::Instance().ExcludedObject(_Object);
	};

	if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Mesh)>, UObjectType>) {
		if (_Object == _Mesh) {
			_Mesh = nullptr;
		}
	}
	else if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Collision)>, UObjectType>) {
		if (_Object == _Collision) {
			_Collision = nullptr;
		}
	}
}
