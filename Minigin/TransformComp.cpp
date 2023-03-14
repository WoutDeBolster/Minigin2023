#include "TransformComp.h"

dae::TransformComp::TransformComp(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::TransformComp::Update(float)
{
}

const glm::vec3& dae::TransformComp::GetWorldPosition() const
{
	return m_WorldPosition;
}

const glm::vec3& dae::TransformComp::GetWorldRotation() const
{
	return m_WorldRotation;
}

const glm::vec3& dae::TransformComp::GetWorldScale() const
{
	return m_WorldScale;
}

const glm::vec3& dae::TransformComp::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3& dae::TransformComp::GetLocalRotation() const
{
	return m_LocalRotation;
}

const glm::vec3& dae::TransformComp::GetLocalScale() const
{
	return m_LocalScale;
}

void dae::TransformComp::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void dae::TransformComp::SetWorldRotation(float x, float y, float z)
{
	m_WorldRotation.x = x;
	m_WorldRotation.y = y;
	m_WorldRotation.z = z;
}

void dae::TransformComp::SetWorldScale(float x, float y, float z)
{
	m_WorldScale.x = x;
	m_WorldScale.y = y;
	m_WorldScale.z = z;
}

void dae::TransformComp::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	m_PosNeedsUpdate = true;
}

void dae::TransformComp::SetLocalRotation(float x, float y, float z)
{
	m_LocalRotation.x = x;
	m_LocalRotation.y = y;
	m_LocalRotation.z = z;
	m_RotNeedsUpdate = true;
}

void dae::TransformComp::SetLocalScale(float x, float y, float z)
{
	m_LocalScale.x = x;
	m_LocalScale.y = y;
	m_LocalScale.z = z;
	m_ScaleNeedsUpdate = true;
}

void dae::TransformComp::SetPosDirty()
{
	m_PosNeedsUpdate = true;
}

void dae::TransformComp::SetRotDirty()
{
	m_RotNeedsUpdate = true;
}

void dae::TransformComp::SetScaleDirty()
{
	m_ScaleNeedsUpdate = true;
}

void dae::TransformComp::SetPosClean()
{
	m_PosNeedsUpdate = false;
}

void dae::TransformComp::SetRotClean()
{
	m_RotNeedsUpdate = false;
}

void dae::TransformComp::SetScaleClean()
{
	m_ScaleNeedsUpdate = false;
}

const bool dae::TransformComp::IsPosDirty() const
{
	return m_PosNeedsUpdate;
}

const bool dae::TransformComp::IsRotDirty() const
{
	return m_RotNeedsUpdate;
}

const bool dae::TransformComp::IsScaleDirty() const
{
	return m_ScaleNeedsUpdate;
}
