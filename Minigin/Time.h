#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Time final : public BaseComponent
	{
	public:
		Time(std::shared_ptr<GameObject> pOwner);

		void Update(float detlaTime) override;

		// 1 / deltaTime = fps
	private:

	};
}