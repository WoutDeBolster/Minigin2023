#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class EnemyComp final : public BaseComponent, public Subject
	{
	public:
		EnemyComp(std::shared_ptr<GameObject> pOwner);
		~EnemyComp() = default;

		EnemyComp(const EnemyComp&) = delete;
		EnemyComp(EnemyComp&&) = delete;
		EnemyComp& operator= (const EnemyComp&) = delete;
		EnemyComp& operator= (const EnemyComp&&) = delete;

		void Update(float deltaTime) override;
		void Die();

		void SetRandomMovement(bool randomMovementOn);
		bool IsMovingRandomly() const;

		Subject* GetEnemySubject() const;

	private:
		std::unique_ptr<Subject> m_pEnemyChanged;

		bool m_RandomMovement{ false };
		glm::f32vec2 m_LastDir{ 0.f, 1.f };
		float m_Speed{ 50.f };
	};
}
