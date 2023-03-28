#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class TransformComp final : public BaseComponent
	{
	public:
		TransformComp(std::weak_ptr<GameObject> pOwner);
		virtual ~TransformComp() = default;

		TransformComp(const TransformComp&) = delete;
		TransformComp(TransformComp&&) = delete;
		TransformComp& operator= (const TransformComp&) = delete;
		TransformComp& operator= (const TransformComp&&) = delete;

		void Update(float deltaTime) override;

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		const void SetLocalPosition(float x, float y, float z);
		const void SetLocalPosition(const glm::vec3& position);
		const void SetPositionDirty();

	private:
		void UpdateWorldPosition();

		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
		bool m_IsDirty;
	};
}
