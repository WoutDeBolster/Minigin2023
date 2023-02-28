#include "TransformComp.h"

dae::TransformComp::TransformComp(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::TransformComp::Update(float)
{
}

const glm::vec3& dae::TransformComp::GetPosition() const
{
	return m_Position;
}

void dae::TransformComp::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
	m_IsDirty = true;
}
