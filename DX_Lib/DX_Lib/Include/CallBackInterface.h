#pragma once
#include <utility>
#include <type_traits>
template<typename _SubTy>
class Interface_CallBack abstract
{
public:
	// TODO :: InputEventRegist_Implementation 반드시 구현
	template<typename ...RegistInfomationTypes>
	void EventRegist(RegistInfomationTypes&&... RegistInfoParams) & noexcept;;

	virtual void EventNotify(const float DeltaTime) & noexcept abstract;
};

// TODO :: InputEventRegist_Implementation 반드시 구현
template<typename _SubTy>
template<typename ...RegistInfomationTypes>
inline void Interface_CallBack<_SubTy>::EventRegist(RegistInfomationTypes&& ...RegistInfoParams) & noexcept {
	static_assert(std::is_same_v<Interface_CallBack<Interface_CallBack>,
		decltype(*this)> == false && __FUNCTION__);

	_SubTy* SELF = static_cast<_SubTy*>(this);
	SELF->InputEventRegist_Implementation(std::forward<RegistInfomationTypes>(RegistInfoParams)...);
}
