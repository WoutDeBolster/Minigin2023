#include "Command.h"

dae::MoveCommand::MoveCommand(std::shared_ptr<GameObject> object, float speed, glm::f32vec2 dir)
	: m_pObj{ object }
	, m_Speed{ speed }
	, m_Dir{ dir }
{
}

void dae::MoveCommand::Execute(float deltaTime)
{
	auto objTransform{ m_pObj.lock().get()->GetComponent<TransformComp>() };
	glm::vec3 currentPos{ objTransform->GetWorldPosition() };

	// move pos game obejct
	currentPos.x += m_Speed * m_Dir.x * deltaTime;
	currentPos.y += m_Speed * m_Dir.y * deltaTime;
	objTransform->SetLocalPosition(currentPos.x, currentPos.y, currentPos.z);
}

void dae::Command::Undo(float)
{
}

dae::LoseHealthCommand::LoseHealthCommand(std::shared_ptr<HealthComp> points, unsigned int amountLost)
	: m_Health{ points }
	, m_AmountLost{ amountLost }
{
}

void dae::LoseHealthCommand::Execute(float)
{
	m_Health.get()->DistractHealth(m_AmountLost);
}

dae::GainScoreCommand::GainScoreCommand(std::shared_ptr<PointsComp> points, int amountGain)
	: m_Points{ points }
	, m_AmountGain{ amountGain }
{
}

void dae::GainScoreCommand::Execute(float)
{
	m_Points.get()->AddPoints(m_AmountGain);
}
