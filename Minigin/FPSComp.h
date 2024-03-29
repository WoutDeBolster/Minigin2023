#pragma once
#include "BaseComponent.h"

namespace dae
{

	class FPSComp final : public BaseComponent
	{
	public:
		FPSComp(std::weak_ptr<GameObject> pOwner);
		~FPSComp() = default;

		FPSComp(const FPSComp&) = delete;
		FPSComp(FPSComp&&) = delete;
		FPSComp& operator= (const FPSComp&) = delete;
		FPSComp& operator= (const FPSComp&&) = delete;

		void Update(float deltaTime) override;

		int GetFPS() const;

	private:
		int m_FPS{};
		float m_TextUpdateTimer{};
	};
}