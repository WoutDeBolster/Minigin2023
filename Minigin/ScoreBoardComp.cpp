#include "ScoreBoardComp.h"
#include "GameObject.h"
#include "HealthComp.h"
#include "PointsComp.h"

dae::ScoreBoardComp::ScoreBoardComp(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
	m_pText = pOwner.get()->GetComponent<TextComp>();
}

void dae::ScoreBoardComp::Update(float)
{
}

void dae::ScoreBoardComp::Notify(const GameObject& actor, Event events)
{
	switch (events)
	{
	case dae::Event::GainPoints:
		int points = actor.GetComponent<PointsComp>().get()->GetPoints();
		m_pText.get()->SetText("Points: " + std::to_string(points));
		break;
	}
}
