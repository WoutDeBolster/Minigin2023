#include "Command.h"
#include <glm/glm.hpp>

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

void dae::MoveCommand::Undo(float)
{
}
