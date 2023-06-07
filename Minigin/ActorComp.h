#pragma once
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

		Subject* GetActorSubject() const;

	private:
		std::unique_ptr<Subject> m_pActorChanged;
	};
}