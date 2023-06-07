#include "CollisionComp.h"
#include "GameObject.h"
#include <iostream>

dae::CollisionComp::CollisionComp(std::weak_ptr<GameObject> pOwner, glm::ivec2 textureSize, std::vector<glm::vec2> objPos)
	: BaseComponent(pOwner)
	, m_ObjTexSize{ textureSize }
	, m_objsPos{ objPos }
{
}

void dae::CollisionComp::Update(float)
{
	CheckCollsionWithBlocks();
}

bool dae::CollisionComp::IsOverlapping()
{
	return m_IsOverlapping;
}

glm::vec2 dae::CollisionComp::GetHitDir()
{
	return m_LastDirection;
}

void dae::CollisionComp::CheckCollsionWithBlocks()
{
	auto ownerPos = GetGameObject().lock()->GetWorldPosition();
	auto ownerSize = glm::ivec2{ 24, 24 };
	for (auto objPos : m_objsPos)
	{
		m_IsOverlapping = true;

		if (ownerPos.x <= objPos.x + m_ObjTexSize.x &&
			ownerPos.x + ownerSize.x >= objPos.x &&
			ownerPos.y <= objPos.y + m_ObjTexSize.y &&
			ownerPos.y + ownerSize.y >= objPos.y)
		{
			m_IsOverlapping = true;

			// give direction
			float directionX = (objPos.x + m_ObjTexSize.x) - (ownerPos.x + ownerSize.x);
			float directionY = (objPos.y + m_ObjTexSize.y) - (ownerPos.y + ownerSize.y);
			std::cout << directionX << ", " << directionY << std::endl;

			if (std::abs(directionX) > std::abs(directionY))
			{
				if (directionX > 0)
				{
					m_LastDirection.x = 1.f;
					m_LastDirection.y = 0.f;
				}
				else
				{
					m_LastDirection.x = -1.f;
					m_LastDirection.y = 0.f;
				}
			}
			else
			{
				if (directionY > 0)
				{
					m_LastDirection.x = 0.f;
					m_LastDirection.y = 1.f;
				}
				else
				{
					m_LastDirection.x = 0.f;
					m_LastDirection.y = -1.f;
				}
			}
			break;
		}
		else
		{
			m_IsOverlapping = false;
			m_LastDirection = { 0,0 };
		}
	}
}
