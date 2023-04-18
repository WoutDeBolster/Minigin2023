#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComp.h"

namespace dae
{
	class HealthBoardComp : public BaseComponent, public Observer
	{
	public:
		HealthBoardComp(std::shared_ptr<GameObject> pOwner);
		~HealthBoardComp() = default;

		HealthBoardComp(const HealthBoardComp&) = delete;
		HealthBoardComp(HealthBoardComp&&) = delete;
		HealthBoardComp& operator= (const HealthBoardComp&) = delete;
		HealthBoardComp& operator= (const HealthBoardComp&&) = delete;

		void Update(float deltaTime) override;

		void Notify(const GameObject& actor, Event events) override;
	private:
		std::shared_ptr<TextComp> m_pText;
	};
}