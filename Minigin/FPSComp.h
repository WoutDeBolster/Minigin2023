#pragma once
#include "BaseComponent.h"

namespace dae
{

	class FPSComp final : public BaseComponent
	{
	public:
		FPSComp(std::shared_ptr<GameObject> pOwner);
		~FPSComp() = default;

		FPSComp(const FPSComp&) = delete;
		FPSComp(FPSComp&&) = delete;
		FPSComp& operator= (const FPSComp&) = delete;
		FPSComp& operator= (const FPSComp&&) = delete;

		void Update(float deltaTime) override;

		int GetFPS() const;

	private:
		int m_FPS{ 0 };
		float m_TextUpdateTimer{};
	};
}