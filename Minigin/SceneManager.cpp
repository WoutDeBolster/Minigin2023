#include "SceneManager.h"
#include "Scene.h"
#include <memory>

void dae::SceneManager::Update(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		if (scene != nullptr)
		{
			if (scene->IsSceneActive())
			{
				scene->Update(deltaTime);
			}
		}
	}
}

void dae::SceneManager::FixedUpdate(float fixedTime)
{
	for (auto& scene : m_scenes)
	{
		if (scene != nullptr)
		{
			if (scene->IsSceneActive())
			{
				scene->FixedUpdate(fixedTime);
			}
		}
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		if (scene != nullptr)
		{
			if (scene->IsSceneActive())
			{
				scene->Render();
			}
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::RemoveScene(const std::string& name)
{
	m_scenes.erase(std::remove_if(m_scenes.begin(), m_scenes.end(), [&](std::shared_ptr<Scene> pScene)
		{
			return pScene->GetSceneName() == name;
		}));
}

void dae::SceneManager::SetSceneActive(const std::string& name, bool isActive)
{
	for (auto& scene : m_scenes)
	{
		if (scene->GetSceneName() == name)
		{
			scene->SetSceneActivity(isActive);
		}
	}
}

bool dae::SceneManager::IsSceneActive(const std::string& name)
{
	for (auto& scene : m_scenes)
	{
		if (scene->GetSceneName() == name)
		{
			return scene->IsSceneActive();
		}
	}
	return false;
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	for (auto& scene : m_scenes)
	{
		if (scene->IsSceneActive())
		{
			return *scene;
		}
	}

	return *m_scenes[0];
}
