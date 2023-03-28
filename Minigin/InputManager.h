#pragma once
#include <memory>
#include <map>
#include "GamePad.h"
#include "Command.h"
#include "Singleton.h"

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

		void SetButtonCommand(unsigned int controllerIndex, GamePad::ControllerButton button, Command* command, InputType inputType);

	private:
		GamePad* m_pXboxController = nullptr;
		InputType m_InputType = InputType::keyDown;
		std::vector<GamePad*> m_pControllers;

		std::map<std::pair<unsigned, GamePad::ControllerButton>, std::pair<std::unique_ptr<Command>, InputType>> m_Commands;
	};
}
