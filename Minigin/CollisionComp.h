#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "BaseComponent.h"
#include "Scene.h"

namespace dae
{
	class CollisionComp final : public BaseComponent
	{
	public:
		CollisionComp(std::weak_ptr<GameObject> pOwner, glm::ivec2 textureSize, Scene& scene);
		virtual ~CollisionComp() = default;

		CollisionComp(const CollisionComp&) = delete;
		CollisionComp(CollisionComp&&) = delete;
		CollisionComp& operator= (const CollisionComp&) = delete;
		CollisionComp& operator= (const CollisionComp&&) = delete;

		void Update(float deltaTime) override;
	private:
		glm::ivec2 m_TexSize;
		Scene& m_Scene;
	};
}

