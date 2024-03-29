#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void RemoveScene(const std::string& name);

		void SetSceneActive(const std::string& name, bool isActive);
		bool IsSceneActive(const std::string& name);
		Scene& GetActiveScene();

		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);
		void Render();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
