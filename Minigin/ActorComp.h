#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class ActorComp : public BaseComponent, public Subject
	{
	public:
		ActorComp(std::shared_ptr<GameObject> pOwner);
		~ActorComp() = default;

		ActorComp(const ActorComp&) = delete;
		ActorComp(ActorComp&&) = delete;
		ActorComp& operator= (const ActorComp&) = delete;
		ActorComp& operator= (const ActorComp&&) = delete;

		void Update(float deltaTime) override;
		void Die();

		void SetRandomMovement(bool randomMovementOn);
		bool IsMovingRandomly() const;

		Subject* GetActorSubject() const;

	private:
		std::unique_ptr<Subject> m_pActorChanged;

		bool m_RandomMovement{ false };
		glm::f32vec2 m_LastDir{ 0.f, 1.f };
		float m_Speed{ 50.f };
	};
}