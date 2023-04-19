#include "HealthComp.h"

dae::HealthComp::HealthComp(std::shared_ptr<GameObject> pOwner, unsigned int health)
	: BaseComponent(pOwner)
	, m_Health{ health }
{
	m_pHealthChanged = std::make_unique<Subject>();
}

void dae::HealthComp::Update(float)
{

}

void dae::HealthComp::DistractHealth(int amount)
{
	if (m_Health > 0)
	{
		m_Health -= amount;
		// notify scoreComp
		m_pHealthChanged.get()->Notify(*GetGameObject().lock().get(), Event::HealthChanged);
	}
	else
	{
		// notify AchievementComp
		m_pHealthChanged.get()->Notify(*GetGameObject().lock().get(), Event::ActorDie);
	}
}

int dae::HealthComp::GetHealth()
{
	return m_Health;
}

dae::Subject* dae::HealthComp::GetHeatlthSubject()
{
	return m_pHealthChanged.get();
}

