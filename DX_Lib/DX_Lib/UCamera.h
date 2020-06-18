#pragma once
#include "UObject.h"

class UCamera : public UObject
{
public: 
	friend class UWorld;
	using Super = UObject;

	void SetOwner(class AActor* POwner) & noexcept;
	class AActor* GetOwner()const& noexcept;
	bool IsOwner()const& noexcept;
	
	bool Init()noexcept override;
	bool Release()noexcept override;
	bool Frame(float DeltaTime)override;
	bool Render(float DeltaTime)override;
private:
	class AActor* _Owner{ nullptr };
};

