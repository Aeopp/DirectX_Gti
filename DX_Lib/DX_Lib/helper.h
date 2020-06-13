#pragma once
#include <string>
#include <string_view>

namespace std {
	static	std::string WtoS(const std::wstring& wstringTOstring) {
		return std::string{ wstringTOstring.begin(), wstringTOstring.end() };
	};
	static	std::wstring StoW(const std::string& stringTOwstring) {
		return std::wstring{ stringTOwstring.begin(), stringTOwstring.end() };
	};
};

// ³Î°Ë»ç
template<typename _ptrType>
static bool IsValid(_ptrType ptr) {
	static_assert(std::is_pointer_v<_ptrType> && L"Not Pointer Type");

	return (ptr != nullptr);
};

namespace DX {
	template<typename _ptrType>
	static void Safe_Release(_ptrType& ptr) {
		static_assert((std::is_pointer_v<_ptrType > == true)
			&& L"is not pointer type");

		if (ptr != nullptr) {
			ptr->Release();
			ptr = nullptr;
		}
	};

	template<typename ..._DX_PTR_TYPE>
	static void CheckValidRelease(_DX_PTR_TYPE&&... ptrs) {
		static auto CheckRelease =
			[](auto& ptr) noexcept {
			if (IsValid(ptr)) {
				ptr->Release();
				ptr = nullptr;
			}
		};
		(CheckRelease(ptrs), ...);
	}
}



