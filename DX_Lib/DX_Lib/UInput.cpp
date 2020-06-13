#include "UInput.h"
#include <algorithm>
#include "UWindow.h"

UInput::~UInput() noexcept {
}

// 이벤트 요구조건을 충족한다면 콜백
// 노티파이 이벤트 , 체킹을 원하는 키상태 , 체킹을 원하는 키인덱스
EKeyState UInput::GetCurrentTargetKeyState(unsigned int TargetKeyIdx) const& {
	if (TargetKeyIdx >= KeyNumber) {
		std::stringstream ss;
		ss << __FUNCTION__ << __LINE__ << __FILE__ << std::endl;
		throw std::exception(ss.str().c_str());
	};
	return CurrentKeyState[TargetKeyIdx];
}

void UInput::InputEventRegist_Implementation(std::function<void(float)> Event, EKeyState KeyState, unsigned int KeyIndex) & noexcept {
	InputEventTable.emplace_back(std::move(Event),
		(KeyState), (KeyIndex));
}

void UInput::EventNotify(const float DeltaTime) & noexcept {
	for (const auto& Element : InputEventTable) {
		const auto& [Event, KeyState, KeyIdx] = Element;
		if (CurrentKeyState[KeyIdx] == KeyState) {
			Event(DeltaTime);
		};
	};
}

bool UInput::Init()
{
	HRESULT hr = DirectInput8Create(UWindow::Instance().hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDI, NULL);

	hr = m_pDI->CreateDevice(GUID_SysKeyboard, &m_pKey, NULL);
	hr = m_pDI->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);

	m_pKey->SetDataFormat(&c_dfDIKeyboard);
	m_pMouse->SetDataFormat(&c_dfDIMouse);
	// 협조레벨

	hr = m_pKey->SetCooperativeLevel(UWindow::Instance().hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);
	hr = m_pMouse->SetCooperativeLevel(UWindow::Instance().hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);
	while (m_pKey->Acquire() == DIERR_INPUTLOST);
	while (m_pMouse->Acquire() == DIERR_INPUTLOST);
	return true;
}
bool UInput::Frame()
{
	HRESULT hr;
	GetCursorPos(&m_MousePos);// 스크린좌표
	ScreenToClient(UWindow::Instance().hWnd, &m_MousePos);

	ZeroMemory(KeyState, sizeof(BYTE) * KeyNumber);

	if (FAILED(m_pKey->GetDeviceState(KeyNumber, KeyState)))
	{
		while (m_pKey->Acquire() == DIERR_INPUTLOST);
		m_pKey->Acquire();
	};

	for (uint32_t i = 0; i < KeyNumber; ++i) {
		bool bCurrentPress = KeyState[i] & 0x80;
		EKeyState& KeyState = CurrentKeyState[i];

		// T T 
		if (bCurrentPress == true && (KeyState == EKeyState::Press ||
			KeyState == EKeyState::Hold)) {
			KeyState = EKeyState::Hold;
		}
		// T F
		// 프레스 홀드 릴리즈 플 
		else if (bCurrentPress == true && (KeyState == EKeyState::Release ||
			KeyState == EKeyState::Free)) {
			KeyState = EKeyState::Press;
		}
		// F T
		else if (bCurrentPress == false && (KeyState == EKeyState::Press ||
			KeyState == EKeyState::Hold)) {
			KeyState = EKeyState::Release;
		}
		// F F
		else if (bCurrentPress == false && (KeyState == EKeyState::Release ||
			KeyState == EKeyState::Free)) {
			KeyState = EKeyState::Free;
		};
	};

	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));
	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE),
		&m_MouseState);
	if (FAILED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE),
		&m_MouseState)))
	{
		while (m_pMouse->Acquire() == DIERR_INPUTLOST);
		m_pMouse->Acquire();
	}

	EventNotify(0);

	return true;
}
UInput::UInput() {
	std::fill_n(std::begin(CurrentKeyState), KeyNumber, EKeyState::Free);
};

bool UInput::Release()
{
	if (m_pKey)
	{
		m_pKey->Unacquire();
		m_pKey->Release();
	}
	if (m_pMouse)
	{
		m_pMouse->Unacquire();
		m_pMouse->Release();
	}
	if (m_pDI) m_pDI->Release();
	return true;
}