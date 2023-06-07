#include "CollisionComp.h"
#include "SpriteAnimatorComp.h"
#include <iostream>

dae::CollisionComp::CollisionComp(std::weak_ptr<GameObject> pOwner, glm::ivec2 textureSize)
	: BaseComponent(pOwner)
	, m_ObjTexSize{ textureSize }
{
}

void dae::CollisionComp::AddObject(std::shared_ptr<GameObject> blockObj)
{
	m_pObjs.emplace_back(std::move(blockObj));
}

void dae::CollisionComp::Update(float deltaTime)
{
	if (m_pObjs.size() > 0)
	{
		CheckCollsionWithBlocks();
		PushBlock(deltaTime);
	}
}

bool dae::CollisionComp::IsOverlapping()
{
	return m_IsOverlapping;
}

glm::vec2 dae::CollisionComp::GetHitDir()
{
	return m_HitDirection;
}

void dae::CollisionComp::PushBlock(float deltaTime)
{
	if (m_BlockPushed)
	{

		CheckCollsionPushedObj(m_pPuchedObject, deltaTime);

		glm::vec3 currentPos{ m_pPuchedObject->GetWorldPosition() };

		// move pos game obejct
		currentPos.x += m_SlidingSpeed * m_SlideDir.x * deltaTime;
		currentPos.y += m_SlidingSpeed * m_SlideDir.y * deltaTime;
		m_pPuchedObject->SetLocalPosition(currentPos.x, currentPos.y);
	}
}

void dae::CollisionComp::CheckCollsionWithBlocks()
{
	auto ownerPos = GetGameObject().lock()->GetWorldPosition();
	auto ownerSize = glm::ivec2{ 24, 24 };

	for (size_t i = 0; i < m_pObjs.size(); i++)
	{
		auto objPos = m_pObjs[i]->GetWorldPosition();

		if (ownerPos.x <= objPos.x + m_ObjTexSize.x &&
			ownerPos.x + ownerSize.x >= objPos.x &&
			ownerPos.y <= objPos.y + m_ObjTexSize.y &&
			ownerPos.y + ownerSize.y >= objPos.y)
		{
			m_IsOverlapping = true;

			// setting up glidding
			m_pPuchedObject = std::move(m_pObjs[i]);
			m_pObjs.erase(std::remove(m_pObjs.begin(), m_pObjs.end(), m_pObjs[i]));

			// give direction
			float directionX = (objPos.x + m_ObjTexSize.x) - (ownerPos.x + ownerSize.x);
			float directionY = (objPos.y + m_ObjTexSize.y) - (ownerPos.y + ownerSize.y);
			std::cout << directionX << ", " << directionY << std::endl;

			if (std::abs(directionX) > std::abs(directionY))
			{
				if (directionX > 0)
				{
					m_HitDirection.x = 1.f;
					m_HitDirection.y = 0.f;
				}
				else
				{
					m_HitDirection.x = -1.f;
					m_HitDirection.y = 0.f;
				}
			}
			else
			{
				if (directionY > 0)
				{
					m_HitDirection.x = 0.f;
					m_HitDirection.y = 1.f;
				}
				else
				{
					m_HitDirection.x = 0.f;
					m_HitDirection.y = -1.f;
				}
			}

			// first see if there is a block in the direction of pushing
			m_PuchedObjectOriginalPos = objPos;

			for (size_t q = 0; q < m_pObjs.size(); q++)
			{
				auto otherBlock = m_pObjs[q]->GetWorldPosition();
				float smallOfset{ 5.f };
				auto distanceBetweenOrinalPos = std::sqrt(std::pow((otherBlock.x - m_PuchedObjectOriginalPos.x), 2) + std::pow((otherBlock.y - m_PuchedObjectOriginalPos.y), 2));

				if (distanceBetweenOrinalPos <= m_ObjTexSize.x + smallOfset || distanceBetweenOrinalPos <= m_ObjTexSize.y + smallOfset)
				{
					m_BlockNextToBlock = true;
					break;
				}
			}

			// slide object if there is no block net to it
			if (!m_BlockNextToBlock)
			{
				m_SlideDir = m_HitDirection;
				m_BlockPushed = true;
			}
			else
			{
				BreakBlock(m_pPuchedObject);

				//m_pObjs.emplace_back(std::move(m_pPuchedObject));
				m_BlockNextToBlock = false;
			}

			break;
		}
		else
		{
			m_IsOverlapping = false;
			m_HitDirection = { 0,0 };
		}
	}
}

void dae::CollisionComp::CheckCollsionPushedObj(std::weak_ptr<GameObject> block, float deltaTime)
{
	auto ownerPos = block.lock()->GetWorldPosition();

	for (size_t i = 0; i < m_pObjs.size(); i++)
	{
		auto objPos = m_pObjs[i]->GetWorldPosition();

		if (ownerPos.x <= objPos.x + m_ObjTexSize.x &&
			ownerPos.x + m_ObjTexSize.x >= objPos.x &&
			ownerPos.y <= objPos.y + m_ObjTexSize.y &&
			ownerPos.y + m_ObjTexSize.y >= objPos.y)
		{
			// stop gliding
			m_pObjs.push_back(m_pPuchedObject);
			m_BlockPushed = false;

			// move object a bit back
			glm::vec3 currentPos{ m_pPuchedObject->GetWorldPosition() };

			currentPos.x -= m_SlidingSpeed * m_SlideDir.x * deltaTime * 2.f;
			currentPos.y -= m_SlidingSpeed * m_SlideDir.y * deltaTime * 2.f;
			m_pPuchedObject->SetLocalPosition(currentPos.x, currentPos.y);

			break;
		}
	}
}

void dae::CollisionComp::BreakBlock(std::weak_ptr<GameObject> block)
{
	// TODO: this is so skuffed plz fix this
	std::vector<std::string> BreakableObjFiles{ "Blocks/BreakingBlock_01.png", "Blocks/BreakingBlock_02.png",
												"Blocks/BreakingBlock_03.png" , "Blocks/BreakingBlock_04.png" ,
												"Blocks/BreakingBlock_05.png", "Blocks/BreakingBlock_06.png",
												"Blocks/BreakingBlock_07.png", "Blocks/BreakingBlock_08.png" };

	if (block.lock()->GetComponent<SpriteAnimatorComp>() != nullptr)
	{
		block.lock()->GetComponent<SpriteAnimatorComp>()->PlayAnimation(BreakableObjFiles, true);
	}
}
