#include "ScoreBoardComp.h"
#include "GameObject.h"
#include "HealthComp.h"
#include "PointsComp.h"
#include "SceneManager.h"
#include "Scene.h"
#include "JSonReader.h"

dae::ScoreBoardComp::ScoreBoardComp(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
	m_pText = pOwner.get()->GetComponent<TextComp>();
}

void dae::ScoreBoardComp::Update(float)
{
}

void dae::ScoreBoardComp::Notify(GameObject& actor, Event events)
{
	switch (events)
	{
	case dae::Event::GameDone:
		JSonReader::GetInstance().AddToTotalScore(actor.GetComponent<PointsComp>().get()->GetPoints());
		JSonReader::GetInstance().WriteHighscore("../Data/HightScore.json");
		JSonReader::GetInstance().ReadHighScore("../Data/HightScore.json");
		break;
	case dae::Event::GainPoints:
		int points = actor.GetComponent<PointsComp>().get()->GetPoints();
		m_pText.get()->SetText("Points: " + std::to_string(points));
		break;
	}
}
