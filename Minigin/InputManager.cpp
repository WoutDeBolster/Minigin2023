#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl.h>
#include "SceneManager.h"

dae::InputManager::InputManager()
{
	// TODO: standerd of 2 controllers ther should be a better way to do this
	m_pControllers.push_back(new GamePad(0));
	m_pControllers.push_back(new GamePad(1));;
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

		for (auto CommandsIterator = m_GamePadCommands.begin(); CommandsIterator != m_GamePadCommands.end(); ++CommandsIterator)
		{
			// checking if scene is active for command
			if (!SceneManager::GetInstance().IsSceneActive(CommandsIterator->first.first))
			{
				continue;
			}

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

	//for (size_t i = 0; i < m_pKeyboards.size(); ++i)
	//{

	//}

	return true;
}

void dae::InputManager::SetGamePadCommand(GamePad::ControllerButton button, Command* command, InputType inputType, std::string sceneName)
{
	m_GamePadCommands.insert({ std::make_pair(sceneName, button), std::make_pair(std::unique_ptr<Command>(command), inputType) });
}

//void dae::InputManager::SetGamePadCommand(unsigned int keyboardIndex, SDL_KeyboardEvent key, Command* command, InputType inputType)
//{
//	m_KeyboardCommands[std::make_pair(keyboardIndex, key)] = std::make_pair(std::unique_ptr<Command>(command), inputType);
//}
