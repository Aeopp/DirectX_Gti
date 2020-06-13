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
	// ��Ƽ���� �̺�Ʈ , üŷ�� ���ϴ� Ű���� , üŷ�� ���ϴ� Ű�ε���
	void InputEventRegist_Implementation(std::function<void(float)> Event,
		ECategory    TimerState, float EventTime) & noexcept;;
	// �̺�Ʈ �䱸������ �����Ѵٸ� �ݹ�
	void EventNotify(const float DeltaTime) & noexcept override;
	inline void SetTimeScale(const float ScaleValue) & noexcept;
	inline float GetDeltaTime() const& noexcept;
	inline float GetCurrentTime() const& noexcept;

public:
	typedef std::chrono::high_resolution_clock	TClock;
	typedef std::chrono::milliseconds			TMilliSeconds;
	TClock::time_point m_BeforeClock;
public:
	virtual bool	Init();		// �ʱ�ȭ
	virtual bool	Frame();	// ���
	virtual bool	Render();	// ��ο�
	virtual bool	Release();	// �Ҹ�
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