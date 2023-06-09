#include "SpriteAnimatorComp.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextureComp.h"

dae::SpriteAnimatorComp::SpriteAnimatorComp(std::weak_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
}

void dae::SpriteAnimatorComp::Update(float deltaTime)
{
	// timer
	m_SpriteTimer += deltaTime;


	// if there is more than 1 sprite on the current direction
	if (m_Sprites[m_currentDirection].size() >= 1)
	{
		if (m_SpriteTimer >= m_TimeInterval && m_IsMoving)
		{
			// cycle to the next sprite
			m_currentSpriteIndex = (m_currentSpriteIndex + 1) % m_Sprites[m_currentDirection].size();
			m_SpriteTimer = 0.0f;
		}
	}

	if (static_cast<unsigned int>(m_currentSpriteIndex) == m_Sprites[m_currentDirection].size() - 1 && m_KillAfterAnimation)
	{
		GetGameObject().lock()->DestryoyGameObject();
	}
}

void dae::SpriteAnimatorComp::Render() const
{
	if (!m_Sprites.at(m_currentDirection).empty())
	{
		const auto& pos = GetGameObject().lock()->GetWorldPosition();
		const auto currentSprite = m_Sprites.at(m_currentDirection)[m_currentSpriteIndex];
		Renderer::GetInstance().RenderTexture(*currentSprite, pos.x, pos.y);
	}
}

void dae::SpriteAnimatorComp::SetDirection(const Direction direction)
{
	if (m_currentDirection != direction)
	{
		m_currentDirection = direction;
		m_currentSpriteIndex = 0;
	}
}

void dae::SpriteAnimatorComp::SetDirectionalSprites(Direction direction, const std::vector<std::string>& spriteFile)
{
	// getting 2D textures and setting them in the sprite vector with the given direction
	std::vector<std::shared_ptr<Texture2D>> textureVec;
	for (std::string file : spriteFile)
	{
		textureVec.push_back(ResourceManager::GetInstance().LoadTexture(file));
	}

	m_Sprites[direction] = textureVec;
}

void dae::SpriteAnimatorComp::PlayAnimation(const std::vector<std::string>& spriteFiles, bool KillAfterAnimation)
{
	m_TimeInterval = 0.25f;
	SetDirectionalSprites(Direction::Up, spriteFiles);
	m_KillAfterAnimation = KillAfterAnimation;

	GetGameObject().lock()->RemoveComponent(GetGameObject().lock()->GetComponent<TextureComp>());
}
