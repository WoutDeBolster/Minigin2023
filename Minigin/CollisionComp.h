#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class CollisionComp final : public BaseComponent
	{
	public:
		CollisionComp(std::weak_ptr<GameObject> pOwner, glm::ivec2 textureSize);
		virtual ~CollisionComp() = default;

		CollisionComp(const CollisionComp&) = delete;
		CollisionComp(CollisionComp&&) = delete;
		CollisionComp& operator= (const CollisionComp&) = delete;
		CollisionComp& operator= (const CollisionComp&&) = delete;

		void AddObject(std::shared_ptr<GameObject> blockObj);
		void Update(float deltaTime) override;

		bool IsOverlapping();
		glm::f32vec2 GetHitDir();
	private:
		void PushBlock(float deltaTime);
		void CheckCollsionWithBlocks();
		void CheckCollsionPushedObj(std::weak_ptr<GameObject> block, float deltaTime);
		void BreakBlock(std::weak_ptr<GameObject> block);
		glm::f32vec2 GetDirection(glm::f32vec2 objPos1, glm::f32vec2 objSize1, glm::f32vec2 objPos2, glm::f32vec2 objSize2) const;

		// collision vars
		glm::ivec2 m_ObjTexSize;
		std::vector<std::shared_ptr<GameObject>> m_pObjs;
		bool m_IsOverlapping{};
		glm::f32vec2 m_HitDirection{};
		glm::f32vec2 m_LatestHitDirection{};

		// block sliding vars
		bool m_BlockPushed{ false };
		float m_SlidingSpeed{ 200.f };
		glm::f32vec2 m_SlideDir{};
		std::shared_ptr<GameObject> m_pPuchedObject;
		glm::f32vec2 m_PuchedObjectOriginalPos{};

		// breaking vars
		bool m_BlockClose{ false };
		bool m_BlockNextToBlock{ false };
		float m_SpriteTimer{ 0.f };
	};
}

