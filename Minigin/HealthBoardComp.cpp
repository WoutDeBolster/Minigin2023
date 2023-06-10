#include "HealthBoardComp.h"
#include "HealthComp.h"
#include "GameObject.h"
#include "ActorComp.h"
#include "EnemyComp.h"
#include "SoundSystem.h"

dae::HealthBoardComp::HealthBoardComp(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
	m_pText = pOwner.get()->GetComponent<TextComp>();
}

void dae::HealthBoardComp::Update(float)
{
}

void dae::HealthBoardComp::Notify(GameObject& actor, Event events)
{
	switch (events)
	{
	case dae::Event::ActorDie:
		actor.DestryoyGameObject();
		ServisLocator::GetSoundSystem().play(2, 50, false);
		break;
	case dae::Event::EnemyDie:
		actor.DestryoyGameObject();
		ServisLocator::GetSoundSystem().play(3, 50, false);
		break;
	case dae::Event::HealthChanged:
		int health = actor.GetComponent<HealthComp>().get()->GetHealth();
		m_pText.get()->SetText("Heath: " + std::to_string(health));
		break;

	}
}
