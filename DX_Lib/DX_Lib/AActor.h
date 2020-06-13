#pragma once
#include "UObject.h"
#include "FVector.h"
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
public:
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
	

	inline class UMesh* GetMesh()const& noexcept {
		return _Mesh;
	};
	inline FVector3 GetLocation()const&noexcept{
		return _Location;
	}
	inline void SetLocation(FVector3 Rhs)&noexcept {
		_Location = std::move_if_noexcept(Rhs);
	}
private:
	template <typename UObjectType>
	void SetComponentMemberVariableByObjectType(UObjectType* ComponentType);
protected:
	AActor() = default;
	virtual ~AActor()noexcept;
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
	if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Mesh)>, UObjectType>) {
		_Mesh = ComponentType;
	}
	else if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Collision)>, UObjectType>) {
		_Collision = ComponentType;
	};
};

template <typename UObjectType>
void AActor::EraseComponent(UObjectType* _Object)&
{
	if (IsValid(_Object) == false)return;

	if (auto iter = std::find(std::begin(ComponentList), std::end(ComponentList), _Object);
		iter != std::end(ComponentList)) {
		(*iter)->Release();
		(*iter) = nullptr;
		ComponentList.erase(iter);
	};

	if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Mesh)>, UObjectType>) {
		_Mesh = nullptr;
	}
	else if constexpr (std::is_same_v<std::remove_pointer_t<decltype(_Collision)>, UObjectType>) {
		_Collision = nullptr;
	}
}
