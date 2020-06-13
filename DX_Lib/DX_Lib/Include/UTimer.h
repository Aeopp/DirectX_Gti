#pragma once
#include "SingleTon.h"
#include "CallBackInterface.h"
#include <Windows.h>
#include <chrono>
#include <vector>
#include <functional>
class UTimer : public SingleTon<UTimer>, public Interface_CallBack<UTimer>
{
public:
	enum class ECategory : uint8_t {
		Loop,
		Once,
	};
	std::wstring		m_csName{};
	std::wstring m_csBuffer;
	float		m_fSecondPerFrame{ 0 };
	float		m_fTimer{ 0 };;
	float		m_fFrameTime{ 0 };;
	DWORD		m_dwBeforeTick{ 0 };;
	DWORD		m_dwFrameCnt{ 0 };;
	int			m_dwFPS{ 0 };;
	float TimeScale{ 1.f };
	std::vector<std::tuple<std::function<void(float)>, ECategory, float, float>> TimerEventTable;
public:
	// 노티파이 이벤트 , 체킹을 원하는 키상태 , 체킹을 원하는 키인덱스
	void InputEventRegist_Implementation(std::function<void(float)> Event,
		ECategory    TimerState, float EventTime) & noexcept;;
	// 이벤트 요구조건을 충족한다면 콜백
	void EventNotify(const float DeltaTime) & noexcept override;
	inline void SetTimeScale(const float ScaleValue) & noexcept;
	inline float GetDeltaTime() const& noexcept;
	inline float GetCurrentTime() const& noexcept;

public:
	typedef std::chrono::high_resolution_clock	TClock;
	typedef std::chrono::milliseconds			TMilliSeconds;
	TClock::time_point m_BeforeClock;
public:
	virtual bool	Init();		// 초기화
	virtual bool	Frame();	// 계산
	virtual bool	Render();	// 드로우
	virtual bool	Release();	// 소멸
public:
	DECLARE_SINGLETON(UTimer)
};

inline float UTimer::GetCurrentTime() const& noexcept {
	return m_fTimer;
}

inline void UTimer::SetTimeScale(const float ScaleValue) & noexcept {
	TimeScale = ScaleValue;
}

inline float UTimer::GetDeltaTime() const& noexcept {
	return m_fSecondPerFrame * TimeScale;
}