#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator= (const BaseComponent&) = delete;
		BaseComponent& operator= (const BaseComponent&&) = delete;

		virtual void Update(float deltaTime) = 0;
		virtual void Render() const;

	protected:
		// todo: make getter vfor owner and put owner in private
		std::weak_ptr<GameObject> m_pGameObject;
	};
}