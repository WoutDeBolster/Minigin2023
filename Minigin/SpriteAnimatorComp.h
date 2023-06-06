#pragma once
#include "BaseComponent.h"
#include <string>
#include <unordered_map>

namespace dae
{
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	class Texture2D;
	class SpriteAnimatorComp final : public BaseComponent
	{
	public:
		SpriteAnimatorComp(std::weak_ptr<GameObject> pOwner);
		~SpriteAnimatorComp() = default;

		SpriteAnimatorComp(const SpriteAnimatorComp&) = delete;
		SpriteAnimatorComp(SpriteAnimatorComp&&) = delete;
		SpriteAnimatorComp& operator= (const SpriteAnimatorComp&) = delete;
		SpriteAnimatorComp& operator= (const SpriteAnimatorComp&&) = delete;

		void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetDirection(const Direction direction);
		void SetDirectionalSprites(const Direction direction, const std::vector<std::string>& spriteFile);
	private:

		std::unordered_map<Direction, std::vector<std::shared_ptr<Texture2D>>> m_Sprites;
		Direction m_currentDirection{ Direction::Up };
		int m_currentSpriteIndex{ 0 };

		bool m_IsMoving{ false };
		float m_SpriteTimer{ 0.f };
	};
}