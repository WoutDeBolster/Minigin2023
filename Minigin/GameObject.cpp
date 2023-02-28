#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

void dae::GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetPosition() const
{
	return m_transform.GetPosition();
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.push_back(myComponent);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.erase(std::find(m_Components.begin(), m_Components.end(), myComponent));
}
