#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComp final : public BaseComponent
	{
	public:
		HealthComp(std::shared_ptr<GameObject> pOwner, int health = 3);
		~HealthComp() = default;

		HealthComp(const HealthComp&) = delete;
		HealthComp(HealthComp&&) = delete;
		HealthComp& operator= (const HealthComp&) = delete;
		HealthComp& operator= (const HealthComp&&) = delete;

		void Update(float deltaTime) override;
		void DistractHealth(int amount);

		int GetHealth();
		Subject* GetHeatlthSubject();

	private:
		std::unique_ptr<Subject> m_pHealthChanged;

		int m_Health;
	};
}
