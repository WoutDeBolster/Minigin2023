#pragma once
#include <memory>
#include <map>
#include "GamePad.h"
#include "Command.h"
#include "Singleton.h"
#include "KeyBoard.h"

namespace dae
{
	enum class InputType
	{
		keyPressed,
		keyUp,
		keyDown
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput(float deltaTime);

		void SetGamePadCommand(unsigned int controllerIndex, GamePad::ControllerButton button, Command* command, InputType inputType);
		//void SetGamePadCommand(unsigned int keyboardIndex, SDL_KeyboardEvent key, Command* command, InputType inputType);

	private:
		InputType m_InputType = InputType::keyDown;
		std::vector<GamePad*> m_pControllers;
		//std::vector<KeyBoard*> m_pKeyboards;

		std::map<std::pair<unsigned, GamePad::ControllerButton>, std::pair<std::unique_ptr<Command>, InputType>> m_GamePadCommands;
		//std::map<std::pair<unsigned, SDL_KeyboardEvent>, std::pair<std::unique_ptr<Command>, InputType>> m_KeyboardCommands;
	};
}
