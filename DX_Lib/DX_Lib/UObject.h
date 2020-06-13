#pragma once
#include <string>
// 오브젝트 생성 담당 객체 프렌드로 지정
// 생성자와 소멸자는 private 자원관리는 오브젝트 생성 담당 객체가 수행
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

