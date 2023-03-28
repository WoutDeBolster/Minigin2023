#pragma once
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void Execute(float deltaTime) = 0;
		virtual void Undo(float deltaTime) = 0;
	};

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(std::shared_ptr<GameObject> object, float speed, glm::f32vec2 dir);

		void Execute(float deltaTime) override;
		void Undo(float deltaTime) override;
	private:
		std::weak_ptr<GameObject> m_pObj;
		float m_Speed;
		glm::f32vec2 m_Dir;
	};
}



