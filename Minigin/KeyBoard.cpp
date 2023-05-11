//#include "KeyBoard.h"
//#include <Windows.h>
//
//using namespace dae;
//
//class KeyBoard::KeyBoardImpl
//{
//public:
//	KeyBoardImpl(unsigned int controllerIndex);
//
//	void Update();
//
//	bool IsDownThisFrame(SDL_KeyboardEvent button) const;
//	bool IsUpThisFrame(SDL_KeyboardEvent button) const;
//	bool IsPressed(SDL_KeyboardEvent button) const;
//
//private:
//	SDL_KeyboardEvent m_CurrentState{};
//	SDL_KeyboardEvent m_PreviusState{};
//
//	BYTE m_ButtonPressedThisFrame;
//	BYTE m_ButtonReleasedThisFrame;
//
//	unsigned int m_KeyboardIndex{ 0 };
//};
//
//
//dae::KeyBoard::KeyBoard(unsigned int controllerIndex)
//{
//	m_pImpl = new KeyBoardImpl(controllerIndex);
//}
//
//dae::KeyBoard::~KeyBoard()
//{
//	delete m_pImpl;
//}
//
//void dae::KeyBoard::Update()
//{
//	m_pImpl->Update();
//}
//
//bool dae::KeyBoard::IsDown(SDL_KeyboardEvent key)
//{
//	return m_pImpl->IsDownThisFrame(key);
//}
//
//bool dae::KeyBoard::IsUp(SDL_KeyboardEvent key)
//{
//	return m_pImpl->IsUpThisFrame(key);
//}
//
//bool dae::KeyBoard::IsPressed(SDL_KeyboardEvent key)
//{
//	return m_pImpl->IsPressed(key);
//}
//
//KeyBoard::KeyBoardImpl::KeyBoardImpl(unsigned int)
//{
//
//}
//
//void KeyBoard::KeyBoardImpl::Update()
//{
//}
//
//bool KeyBoard::KeyBoardImpl::IsDownThisFrame(SDL_KeyboardEvent) const
//{
//	return false;
//}
//
//bool KeyBoard::KeyBoardImpl::IsUpThisFrame(SDL_KeyboardEvent) const
//{
//	return false;
//}
//
//bool KeyBoard::KeyBoardImpl::IsPressed(SDL_KeyboardEvent) const
//{
//	return false;
//}
