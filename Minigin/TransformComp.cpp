#include "TransformComp.h"
#include "GameObject.h"

dae::TransformComp::TransformComp(std::weak_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
	, m_LocalPosition{ 0.f, 0.f, 0.f }
	, m_WorldPosition{ 0.f, 0.f, 0.f }
	, m_IsDirty{ false }
{
}

void dae::TransformComp::Update(float)
{
}

const glm::vec3& dae::TransformComp::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3& dae::TransformComp::GetWorldPosition()
{
	if (m_IsDirty)
	{
		UpdateWorldPosition();
	}

	return m_WorldPosition;
}

const void dae::TransformComp::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;

	SetPositionDirty();
}

const void dae::TransformComp::SetLocalPosition(const glm::vec3& position)
{
	SetLocalPosition(position.x, position.y, position.z);
}

const void dae::TransformComp::SetPositionDirty()
{
	m_IsDirty = true;
}

void dae::TransformComp::UpdateWorldPosition()
{
	const auto componentOwner = m_pGameObject.lock().get();
	if (componentOwner->GetParent().lock() == nullptr)
		m_WorldPosition = m_LocalPosition;
	else
	{
		const auto parentWorldPos = componentOwner->GetParent().lock()->GetWorldPosition();

		m_WorldPosition = parentWorldPos + m_LocalPosition;
	}
	m_IsDirty = false;
}
