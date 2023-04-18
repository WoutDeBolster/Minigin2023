#include "Achievements.h"
#include "GameObject.h"
#include "PointsComp.h"
#include <iostream>

void dae::Achievements::Notify(const GameObject& actor, Event events)
{
	switch (events)
	{
	case dae::Event::ActorDie:
		if (m_NoONeElseDied)
		{
			Unlock(Achievement::FirstBlood);
			m_NoONeElseDied = false;
		}
		break;
	case dae::Event::GainPoints:
		if (actor.GetComponent<PointsComp>().get()->GetPoints() >= 300)
		{
			Unlock(Achievement::Win);
		}
		break;
	default:
		break;
	}
}

void dae::Achievements::Unlock(Achievement achievement)
{
	switch (achievement)
	{
	case dae::Achievement::Win:
		std::cout << "YOU WIN!" << std::endl;
		break;
	case dae::Achievement::FirstBlood:
		std::cout << "FIRTS BLOOD!" << std::endl;
		break;
	default:
		break;
	}
}
