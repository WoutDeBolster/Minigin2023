#include "SpriteComp.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::SpriteComp::SpriteComp(std::weak_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
}

void dae::SpriteComp::Update(float deltaTime)
{
	// timer
	const float timeInterval = 0.25f;
	m_SpriteTimer += deltaTime;


	// if there is more than 1 sprite on the current direction
	if (m_Sprites[m_currentDirection].size() >= 1)
	{
		if (m_SpriteTimer >= timeInterval && m_IsMoving)
		{
			// cycle to the next sprite
			m_currentSpriteIndex = (m_currentSpriteIndex + 1) % m_Sprites[m_currentDirection].size();
			m_SpriteTimer = 0.0f;
		}
	}
}

void dae::SpriteComp::Render() const
{
	const auto& pos = GetGameObject().lock().get()->GetWorldPosition();
	const auto currentSprite = m_Sprites.at(m_currentDirection)[m_currentSpriteIndex];
	Renderer::GetInstance().RenderTexture(*currentSprite, pos.x, pos.y);
}

void dae::SpriteComp::SetDirection(const Direction direction)
{
	if (m_currentDirection != direction)
	{
		m_currentDirection = direction;
		m_currentSpriteIndex = 0;
	}
}

void dae::SpriteComp::SetDirectionalSprites(Direction direction, const std::vector<std::string>& spriteFile)
{
	// getting 2D textures and setting them in the sprite vector with the given direction
	std::vector<std::shared_ptr<Texture2D>> textureVec;
	for (std::string file : spriteFile)
	{
		textureVec.push_back(ResourceManager::GetInstance().LoadTexture(file));
	}

	m_Sprites[direction] = textureVec;
}
