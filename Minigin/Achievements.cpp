#include "Achievements.h"
#include "GameObject.h"
#include "PointsComp.h"
#include <iostream>

void dae::Achievements::Notify(GameObject& actor, Event events)
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
		if (!m_WinUnlocked)
		{
			std::cout << "YOU WIN!" << std::endl;
			m_WinUnlocked = true;
		}
		break;
	case dae::Achievement::FirstBlood:
		if (!m_FirstBloodUnlocked)
		{
			std::cout << "FIRTS BLOOD!" << std::endl;
			m_FirstBloodUnlocked = true;
		}
		break;
	default:
		break;
	}
}
