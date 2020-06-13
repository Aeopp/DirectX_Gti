#pragma once
#include <string>
// ������Ʈ ���� ��� ��ü ������� ����
// �����ڿ� �Ҹ��ڴ� private �ڿ������� ������Ʈ ���� ��� ��ü�� ����
//friend class UWorld;
class UObject abstract{
public:
	friend class UWorld;

	virtual bool Init()noexcept abstract;
	virtual bool Release()noexcept abstract;
	virtual bool Frame(float)abstract;
	virtual bool Render(float)abstract;

	inline std::string GetTag()const& noexcept {
		return _Tag;
	}
	inline std::string SetTag(std::string Rhs) & noexcept {
		_Tag = std::move(Rhs);
	}
	inline uint32_t GetUniqueNumber()const& noexcept {
		return Unique_Number;
	};
protected:
	static inline uint32_t Number = 0;
	UObject() :Unique_Number{ Number } {
		UObject::Number++;
	};
	virtual ~UObject()noexcept;
	
	std::string _Tag{};
	const uint32_t Unique_Number{};
};

