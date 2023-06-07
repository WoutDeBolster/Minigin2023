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
		CollisionComp(std::weak_ptr<GameObject> pOwner, glm::ivec2 textureSize, std::vector<glm::vec2> objPos);
		virtual ~CollisionComp() = default;

		CollisionComp(const CollisionComp&) = delete;
		CollisionComp(CollisionComp&&) = delete;
		CollisionComp& operator= (const CollisionComp&) = delete;
		CollisionComp& operator= (const CollisionComp&&) = delete;

		void Update(float deltaTime) override;

		bool IsOverlapping();
		glm::f32vec2 GetHitDir();
	private:
		glm::ivec2 m_ObjTexSize;
		std::vector<glm::vec2> m_objsPos;

		bool m_IsOverlapping{};
		glm::f32vec2 m_LastDirection{};
	};
}

