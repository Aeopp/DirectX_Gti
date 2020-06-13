#pragma once
#include <memory>
#include <type_traits>
#include <mutex>

#include "Declare.h"

// ����� ����Ǵ� CPP�� �Ҹ��� ������ �ݵ�ñ���

// TODO :: Sub Ŭ���� Super Ŭ���� ������ �����������
// TODO :: ������ ��� ����ϸ� �ȵ�
// TODO :: private �⺻ ������ �Ҹ��� �����ϰ� �ݵ�� cpp�� ����
// TODO :: SINGLETON_DECLARE(SubClass) DELETE_MOVE_COPY(Subclass) 
// TODO :: friend class std::unique_ptr<SubClass>::deleter_type;
template <class ManagerType>
class SingleTon
{
public:
	template<typename...Types>
	static ManagerType& Instance(Types&&... params)
	{
		static std::unique_ptr<ManagerType> InstancePtr;
		static std::once_flag OnceFlag;
		std::call_once(OnceFlag, [](auto&&... params) {
			InstancePtr.reset(new ManagerType(std::forward<Types>(params)...)); },
			std::forward<Types>(params)...);
		return *(InstancePtr.get());
	};
protected:
	SingleTon() = default;
	~SingleTon()noexcept = default;
private:
	DECLARE_DELETE_MOVE_COPY(SingleTon)
};
