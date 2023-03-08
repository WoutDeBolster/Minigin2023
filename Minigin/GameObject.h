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
		GameObject() = default;
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update(float deltaTime);
		virtual void Render() const;

		void UpdateWorldPosition();
		void UpdateWorldRotation();
		void UpdateWorldScale();

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetWorldRotation();
		const glm::vec3& GetWorldScale();

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetLocalRotation() const;
		const glm::vec3& GetLocalScale() const;

		void SetWorldPosition(float x, float y);
		void SetWorldRotation(float x, float y);
		void SetWorldScale(float x, float y);

		void SetLocalPosition(float x, float y);
		void SetLocalRotation(float x, float y);
		void SetLocalScale(float x, float y);

		// components
		void AddComponent(std::shared_ptr<BaseComponent> myComponent);
		template <typename T>
		std::shared_ptr<T> GetComponent() const
		{
			for (std::shared_ptr<BaseComponent> bc : m_Components)
			{
				std::shared_ptr<T> castedPointer = dynamic_pointer_cast<T>(bc);
				if (castedPointer)
				{
					return castedPointer;
				}
			}
			return nullptr;
		}
		void RemoveComponent(std::shared_ptr<BaseComponent> myComponent);

		// parent
		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos = true, bool keepWorldRot = true, bool keepWorldScale = true);
		std::shared_ptr<GameObject> GetParent() const;

		// child
		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(size_t idx) const;
		void RemoveChild(size_t idx);
		void RemoveChild(std::shared_ptr<GameObject> child);
		void AddChild(std::shared_ptr<GameObject> child);

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components;

		std::weak_ptr<GameObject> m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Childeren;
	};
}
