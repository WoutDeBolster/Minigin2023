#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::weak_ptr<GameObject> pOwner)
	: m_pGameObject{ pOwner }
{

}

void dae::BaseComponent::FixedUpdate(float)
{
}

void dae::BaseComponent::Render() const
{
}

std::weak_ptr<dae::GameObject> dae::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}
