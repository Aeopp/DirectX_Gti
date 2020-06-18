#pragma once
#include <string_view>
#include <string>

using namespace std::string_view_literals;
using namespace std::string_literals;

// TODO :: 교체해주세요
namespace path {
	namespace s {
		static inline const std::string DefaultResourcePath{ "..\\..\\..\\Resource\\" };
		static inline const std::string TimeGame = "MapleData\\BGM\\TimeGate.mp3";
		static inline const std::string WhenTheMorningComess = "MapleData\\BGM\\WhenTheMorningComess.mp3";
	}
	namespace w {
		static inline const std::wstring DefaultResourcePath{ L"..\\..\\..\\Resource\\" };
		static inline const std::wstring DefaultMapleResourcePath{ 
			L"..\\..\\..\\Resource\\MapleData\\Texture\\" };
		static inline const std::wstring DefaultPlayerPath
		{ L"..\\..\\..\\Resource\\\\MapleData\\Texture\\Animation\\Player\\" }; 
		static inline const std::wstring IMAGE = L"Lin.png";
	}
}
