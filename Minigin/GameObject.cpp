#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#pragma warning( disable : 4172) // todo: vraag waarom dit er is (versta dit niet 100%)

void dae::GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Update(deltaTime);
	}

	UpdateWorldPosition();
	UpdateWorldRotation();
	UpdateWorldScale();
}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Render();
	}
}

void dae::GameObject::UpdateWorldPosition()
{
	auto transfrom = GetComponent<TransformComp>();

	if (transfrom->IsPosDirty())
	{
		if (m_Parent.lock() == nullptr)
		{
			SetWorldPosition(transfrom->GetLocalPosition().x, transfrom->GetLocalPosition().y);
		}
		else
		{
			SetWorldPosition
			(
				m_Parent.lock().get()->GetWorldPosition().x + transfrom->GetLocalPosition().x,
				m_Parent.lock().get()->GetWorldPosition().y + transfrom->GetLocalPosition().y
			);
		}
		transfrom->SetPosClean();
	}
}

void dae::GameObject::UpdateWorldRotation()
{
	auto transfrom = GetComponent<TransformComp>();

	if (transfrom->IsRotDirty())
	{
		if (m_Parent.lock() == nullptr)
		{
			SetWorldRotation(transfrom->GetLocalRotation().x, transfrom->GetLocalRotation().y);
		}
		else
		{
			SetWorldRotation
			(
				m_Parent.lock().get()->GetWorldRotation().x + transfrom->GetLocalRotation().x,
				m_Parent.lock().get()->GetWorldRotation().y + transfrom->GetLocalRotation().y
			);
		}
		transfrom->SetRotClean();
	}
}

void dae::GameObject::UpdateWorldScale()
{
	auto transfrom = GetComponent<TransformComp>();

	if (transfrom->IsScaleDirty())
	{
		if (m_Parent.lock() == nullptr)
		{
			SetWorldScale(transfrom->GetLocalScale().x, transfrom->GetLocalScale().y);
		}
		else
		{
			SetWorldScale
			(
				m_Parent.lock().get()->GetWorldScale().x + transfrom->GetLocalScale().x,
				m_Parent.lock().get()->GetWorldScale().y + transfrom->GetLocalScale().y
			);
		}
		transfrom->SetScaleClean();
	}
}

void dae::GameObject::SetWorldPosition(float x, float y)
{
	GetComponent<TransformComp>()->SetWorldPosition(x, y, 0.f);
}

void dae::GameObject::SetWorldRotation(float x, float y)
{
	GetComponent<TransformComp>()->SetWorldRotation(x, y, 0.f);
}

void dae::GameObject::SetWorldScale(float x, float y)
{
	GetComponent<TransformComp>()->SetWorldScale(x, y, 0.f);
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	GetComponent<TransformComp>()->SetLocalPosition(x, y, 0.f);
}

void dae::GameObject::SetLocalRotation(float x, float y)
{
	GetComponent<TransformComp>()->SetLocalRotation(x, y, 0.f);
}

void dae::GameObject::SetLocalScale(float x, float y)
{
	GetComponent<TransformComp>()->SetLocalScale(x, y, 0.f);
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_Parent.lock() != nullptr)
	{
		return m_Parent.lock().get()->GetWorldPosition() + GetLocalPosition();
	}
	return GetLocalPosition();
}

const glm::vec3& dae::GameObject::GetWorldRotation()
{
	if (m_Parent.lock() != nullptr)
	{
		return m_Parent.lock().get()->GetWorldRotation() + GetLocalRotation();
	}
	return GetLocalRotation();
}

const glm::vec3& dae::GameObject::GetWorldScale()
{
	if (m_Parent.lock() != nullptr)
	{
		return m_Parent.lock().get()->GetWorldScale() + GetLocalScale();
	}
	return GetLocalScale();
}

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return GetComponent<TransformComp>()->GetLocalPosition();
}

const glm::vec3& dae::GameObject::GetLocalRotation() const
{
	return GetComponent<TransformComp>()->GetLocalRotation();
}

const glm::vec3& dae::GameObject::GetLocalScale() const
{
	return GetComponent<TransformComp>()->GetLocalScale();
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.push_back(myComponent);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.erase(std::find(m_Components.begin(), m_Components.end(), myComponent));
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos, bool keepWorldRot, bool keepWorldScale)
{
	if (m_Parent.lock() == nullptr)
	{
		SetLocalPosition(GetWorldPosition().x, GetWorldPosition().y);
	}
	else
	{
		// pos
		if (keepWorldPos)
		{
			SetLocalPosition
			(
				GetLocalPosition().x - m_Parent.lock().get()->GetWorldPosition().x,
				GetLocalPosition().y - m_Parent.lock().get()->GetWorldPosition().y
			);
		}
		GetComponent<TransformComp>()->SetPosDirty();

		// rot
		if (keepWorldRot)
		{
			SetLocalRotation
			(
				GetLocalRotation().x - m_Parent.lock().get()->GetWorldRotation().x,
				GetLocalRotation().y - m_Parent.lock().get()->GetWorldRotation().y
			);
		}
		GetComponent<TransformComp>()->SetRotDirty();

		// scale
		if (keepWorldScale)
		{
			SetLocalScale
			(
				GetLocalScale().x - m_Parent.lock().get()->GetWorldScale().x,
				GetLocalScale().y - m_Parent.lock().get()->GetWorldScale().y
			);
		}
		GetComponent<TransformComp>()->SetScaleDirty();
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

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_Parent.lock();
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