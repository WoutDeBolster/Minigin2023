#pragma once
#include "GameObject.h"
#include "HealthComp.h"
#include "PointsComp.h"
#include <iostream>

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void Execute(float deltaTime) = 0;
		virtual void Undo(float deltaTime);
	};

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(std::shared_ptr<GameObject> object, float speed, glm::f32vec2 dir);

		void Execute(float deltaTime) override;
	private:
		std::weak_ptr<GameObject> m_pObj;
		float m_Speed;
		glm::f32vec2 m_Dir;
	};

	class LoseHealthCommand final : public Command
	{
	public:
		LoseHealthCommand(std::shared_ptr<HealthComp> health, unsigned int amountLost);

		void Execute(float deltaTime) override;
	private:
		std::shared_ptr<HealthComp> m_Health;
		unsigned int m_AmountLost;
	};

	class GainScoreCommand final : public Command
	{
	public:
		GainScoreCommand(std::shared_ptr<PointsComp> points, int amountGain);

		void Execute(float deltaTime) override;
	private:
		std::shared_ptr<PointsComp> m_Points;
		int m_AmountGain;
	};

	class PlaySoundEffectCommand final : public Command
	{
	public:
		PlaySoundEffectCommand(const std::string& fileName);

		void Execute(float deltaTime) override;
	private:
		std::string m_File;
	};


	class SkipLevelCommand final : public Command
	{
	public:
		SkipLevelCommand();

		void Execute(float deltaTime) override;
	private:
	};
}



