#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComp.h"
#include <vector>

namespace dae
{
	class ScoreBoardComp final : public BaseComponent, public Observer
	{
	public:
		ScoreBoardComp(std::shared_ptr<GameObject> pOwner);
		~ScoreBoardComp() = default;

		ScoreBoardComp(const ScoreBoardComp&) = delete;
		ScoreBoardComp(ScoreBoardComp&&) = delete;
		ScoreBoardComp& operator= (const ScoreBoardComp&) = delete;
		ScoreBoardComp& operator= (const ScoreBoardComp&&) = delete;

		void Update(float deltaTime) override;

		void Notify(const GameObject& actor, Event events) override;
	private:
		std::shared_ptr<TextComp> m_pText;
	};
}
