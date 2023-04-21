#pragma once
#include "Observer.h"

namespace dae
{
	enum class Achievement
	{
		Win,
		FirstBlood,
	};

	class Achievements final : public Observer
	{
	public:
		Achievements() = default;
		~Achievements() = default;

		Achievements(const Achievements&) = delete;
		Achievements(Achievements&&) = delete;
		Achievements& operator= (const Achievements&) = delete;
		Achievements& operator= (const Achievements&&) = delete;

		void Notify(const GameObject& actor, Event events) override;

	private:
		void Unlock(Achievement achievement);

		bool m_NoONeElseDied{ true };

		// achievements
		bool m_WinUnlocked{ false };
		bool m_FirstBloodUnlocked{ false };
	};
}