#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl.h>

dae::InputManager::InputManager()
{
	// TODO: standerd of 2 controllers ther should be a better way to do this
	m_pControllers.push_back(new GamePad(0));
	m_pControllers.push_back(new GamePad(1));
}

dae::InputManager::~InputManager()
{
	for (size_t i = 0; i < m_pControllers.size(); ++i)
	{
		delete m_pControllers[i];
	}
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
	for (size_t i = 0; i < m_pControllers.size(); ++i)
	{
		m_pControllers[i]->Update();

		for (auto CommandsIterator = m_Commands.begin(); CommandsIterator != m_Commands.end(); ++CommandsIterator)
		{
			switch (CommandsIterator->second.second)
			{
			case dae::InputType::keyPressed:
				if (m_pControllers[i]->IsPressed(CommandsIterator->first.second))
				{
					CommandsIterator->second.first.get()->Execute(deltaTime);
				}
				break;
			case dae::InputType::keyUp:
				if (m_pControllers[i]->IsUp(CommandsIterator->first.second))
				{
					CommandsIterator->second.first.get()->Execute(deltaTime);
				}
				break;
			case dae::InputType::keyDown:
				if (m_pControllers[i]->IsDown(CommandsIterator->first.second))
				{
					CommandsIterator->second.first.get()->Execute(deltaTime);
				}
				break;
			default:
				continue;
				break;
			}

			if (m_pControllers[i]->IsPressed(GamePad::ControllerButton::LeftShoulder))
			{
				return false;
			}
		}
	}

	return true;
}

void dae::InputManager::SetButtonCommand(unsigned int controllerIndex, GamePad::ControllerButton button, Command* command, InputType inputType)
{
	m_Commands[std::make_pair(controllerIndex, button)] = std::make_pair(std::unique_ptr<Command>(command), inputType);
}
