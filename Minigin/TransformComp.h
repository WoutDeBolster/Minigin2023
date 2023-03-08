#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class TransformComp final : public BaseComponent
	{
	public:
		TransformComp(std::shared_ptr<GameObject> pOwner);
		virtual ~TransformComp() = default;

		TransformComp(const TransformComp&) = delete;
		TransformComp(TransformComp&&) = delete;
		TransformComp& operator= (const TransformComp&) = delete;
		TransformComp& operator= (const TransformComp&&) = delete;

		void Update(float deltaTime) override;

		const glm::vec3& GetWorldPosition() const;
		const glm::vec3& GetWorldRotation() const;
		const glm::vec3& GetWorldScale() const;

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetLocalRotation() const;
		const glm::vec3& GetLocalScale() const;

		const bool IsPosDirty() const;
		const bool IsRotDirty() const;
		const bool IsScaleDirty() const;


		void SetWorldPosition(float x, float y, float z);
		void SetWorldRotation(float x, float y, float z);
		void SetWorldScale(float x, float y, float z);

		void SetLocalPosition(float x, float y, float z);
		void SetLocalRotation(float x, float y, float z);
		void SetLocalScale(float x, float y, float z);

		void SetPosClean();
		void SetRotClean();
		void SetScaleClean();

		void SetPosDirty();
		void SetRotDirty();
		void SetScaleDirty();

	private:
		bool m_PosNeedsUpdate = false;
		bool m_RotNeedsUpdate = false;
		bool m_ScaleNeedsUpdate = false;

		glm::vec3 m_WorldPosition{ 0.f, 0.f, 0.f };
		glm::vec3 m_WorldRotation{ 0.f, 0.f, 0.f };
		glm::vec3 m_WorldScale{ 1.f, 1.f, 1.f };

		glm::vec3 m_LocalPosition{ 0.f, 0.f, 0.f };
		glm::vec3 m_LocalRotation{ 0.f, 0.f, 0.f };
		glm::vec3 m_LocalScale{ 1.f, 1.f, 1.f };
	};
}
