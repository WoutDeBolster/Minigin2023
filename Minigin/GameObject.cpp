#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject()
{
}

void dae::GameObject::Initialize()
{
	m_pTransfrom = std::make_shared<TransformComp>(shared_from_this());
	AddComponent(m_pTransfrom);
}

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

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_pTransfrom->SetLocalPosition(x, y, 0.f);
}

const glm::vec3& dae::GameObject::GetWorldPosition() const
{
	return m_pTransfrom->GetWorldPosition();
}

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return m_pTransfrom->GetLocalPosition();
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.push_back(myComponent);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.erase(std::find(m_Components.begin(), m_Components.end(), myComponent));
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos)
{
	if (m_Parent.lock() == nullptr)
	{
		SetLocalPosition(GetWorldPosition().x, GetWorldPosition().y);
	}
	else
	{
		// pos
		if (keepWorldPos == false)
		{
			m_pTransfrom->SetPositionDirty();
		}
	}

	if (m_Parent.lock() != nullptr)
	{
		m_Parent.lock().get()->RemoveChild(static_cast<std::shared_ptr<GameObject>>(this));
	}
	m_Parent = parent;
	if (m_Parent.lock() != nullptr)
	{
		m_Parent.lock().get()->AddChild(static_cast<std::shared_ptr<GameObject>>(this));
	}
}

std::weak_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_Parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Childeren.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(size_t idx) const
{
	if (idx < m_Childeren.size())
	{
		return m_Childeren[idx];
	}
	return std::shared_ptr<dae::GameObject>();
}

void dae::GameObject::RemoveChild(size_t idx)
{
	m_Childeren[idx]->SetParent(nullptr);
	for (size_t i = 0; i < m_Childeren[idx].get()->GetChildCount(); ++i)
	{
		std::shared_ptr<GameObject> currentChild{ m_Childeren[idx].get()->GetChildAt(i) };
		currentChild.get()->RemoveChild(i);
	}
	m_Childeren.erase(std::find(m_Childeren.begin(), m_Childeren.end(), GetChildAt(idx)));
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	child->SetParent(nullptr);
	for (size_t i = 0; i < child->GetChildCount(); ++i)
	{
		std::shared_ptr<GameObject> currentChild{ child->GetChildAt(i) };
		currentChild.get()->RemoveChild(i);
	}
	m_Childeren.erase(std::find(m_Childeren.begin(), m_Childeren.end(), child));
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	child.get()->SetParent(m_Parent.lock());
	m_Childeren.push_back(child);
}