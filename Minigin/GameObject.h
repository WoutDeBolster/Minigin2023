#pragma once
#include <memory>
#include <vector>
#include "TransformComp.h"

namespace dae
{
	class BaseComponent;
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject();
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initialize();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float fixedTime);
		virtual void Render() const;

		const glm::vec3& GetWorldPosition() const;
		const glm::vec3& GetLocalPosition() const;

		void SetLocalPosition(float x, float y);

		// components
		void AddComponent(std::shared_ptr<BaseComponent> myComponent);
		template <typename T>
		std::shared_ptr<T> GetComponent() const
		{
			for (std::shared_ptr<BaseComponent> bc : m_Components)
			{
				std::shared_ptr<T> castedPointer = std::dynamic_pointer_cast<T>(bc);
				if (castedPointer)
				{
					return castedPointer;
				}
			}
			return nullptr;
		}
		void RemoveComponent(std::shared_ptr<BaseComponent> myComponent);

		// parent
		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos = false);
		std::weak_ptr<GameObject> GetParent() const;

		// child
		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(size_t idx) const;
		void RemoveChild(size_t idx);
		void RemoveChild(std::shared_ptr<GameObject> child);
		void AddChild(std::shared_ptr<GameObject> child);

	private:

		std::vector<std::shared_ptr<BaseComponent>> m_Components;

		std::shared_ptr<TransformComp> m_pTransfrom;
		std::weak_ptr<GameObject> m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Childeren;
	};
}
