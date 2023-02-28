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

		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const;

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

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
	};
}
