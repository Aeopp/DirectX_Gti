#include "UTimer.h"

// 노티파이 이벤트 , 체킹을 원하는 키상태 , 체킹을 원하는 키인덱스
void UTimer::InputEventRegist_Implementation(std::function<void(float)> Event, ECategory TimerState, float EventTime) & noexcept {
	TimerEventTable.emplace_back(std::move(Event), std::move(TimerState),
		std::move(EventTime), std::move(EventTime));
}
// 이벤트 요구조건을 충족한다면 콜백
void UTimer::EventNotify(const float DeltaTime) & noexcept {
	for (auto iter = std::begin(TimerEventTable); iter != std::end(TimerEventTable);) {
		auto& [Event, TimerState, CurrentRemainTime, EventTime] = *iter;
		CurrentRemainTime -= DeltaTime;

		if (CurrentRemainTime < 0) {
			Event(DeltaTime);
			if (TimerState == UTimer::ECategory::Once) {
				iter = TimerEventTable.erase(iter);
				continue;
			}
			else if (TimerState == UTimer::ECategory::Loop) {
				CurrentRemainTime = CurrentRemainTime + EventTime;
			}
		}
		++iter;
	}
}

bool	UTimer::Init()
{
	// 추가종속성 : winmm.lib 추가
	// 1000 -> 1초
	m_dwBeforeTick = timeGetTime();// 1/1000.0f 정밀도
	m_BeforeClock = TClock::now();
	return true;
}
bool	UTimer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecondPerFrame = dwElapseTick / 1000.0f;
	m_fTimer += m_fSecondPerFrame;
	m_dwBeforeTick = dwCurrentTick;

	m_fFrameTime += m_fSecondPerFrame;
	if (m_fFrameTime > 1.0f)
	{
		m_dwFPS = m_dwFrameCnt;
		m_dwFrameCnt = 0;
		m_fFrameTime = m_fFrameTime - 1.0f;
	}
	m_dwFrameCnt++;
	m_dwBeforeTick = dwCurrentTick;

	EventNotify(GetDeltaTime());

	return true;
}
bool	UTimer::Render()
{
	return true;
}
bool	UTimer::Release()
{
	return true;
}


UTimer::UTimer() {

}
UTimer::~UTimer() noexcept {
}

