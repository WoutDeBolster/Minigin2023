#pragma once

namespace dae
{
	class GameObject;
	enum class Event
	{
		ActorDie,
		EnemyDie,
		GainPoints,
		HealthChanged,
	};

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator= (const Observer&) = delete;
		Observer& operator= (const Observer&&) = delete;

		virtual void Notify(const GameObject& actor, Event events) = 0;
	};
}