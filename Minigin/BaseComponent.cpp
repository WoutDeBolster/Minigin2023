#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::weak_ptr<GameObject> pOwner)
{
	m_pGameObject = pOwner;
}

void dae::BaseComponent::Render() const
{
}
