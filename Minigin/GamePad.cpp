#include "GamePad.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

using namespace dae;

class GamePad::GamePadImpl
{
public:
	GamePadImpl(unsigned int controllerIndex);

	void Update();

	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviusState{};

	WORD m_ButtonPressedThisFrame;
	WORD m_ButtonReleasedThisFrame;

	unsigned int m_GamePadIndex{ 0 };
};


GamePad::GamePad(unsigned int controllerIndex)
{
	pImpl = new GamePadImpl(controllerIndex);
}

void GamePad::Update()
{
	delete pImpl;
}

bool GamePad::IsDown(ControllerButton button)
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool GamePad::IsUp(ControllerButton button)
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool GamePad::IsPressed(ControllerButton button)
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

// GamePadImpl
// -----------
GamePad::GamePadImpl::GamePadImpl(unsigned int controllerIndex)
	: m_GamePadIndex{ controllerIndex }
{
	ZeroMemory(&m_PreviusState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
}

void GamePad::GamePadImpl::Update()
{
	CopyMemory(&m_PreviusState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_GamePadIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons xor m_PreviusState.Gamepad.wButtons; // ^ is xor
	m_ButtonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons); // ~ is invert
}

bool GamePad::GamePadImpl::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonPressedThisFrame & static_cast<int>(button);
}

bool GamePad::GamePadImpl::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonReleasedThisFrame & static_cast<int>(button);
}

bool GamePad::GamePadImpl::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & static_cast<int>(button);
}