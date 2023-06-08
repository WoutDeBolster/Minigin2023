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

			// getting direction between player and block
			m_HitDirection = GetDirection(objPos, m_ObjTexSize, ownerPos, ownerSize);
			m_LatestHitDirection = m_HitDirection;

			// first see if there is a block in the direction of pushing
			m_PuchedObjectOriginalPos = objPos;

			for (size_t q = 0; q < m_pObjs.size(); q++)
			{
				auto otherBlock = m_pObjs[q]->GetWorldPosition();
				float smallOfset{ 1.f };
				auto distanceBetweenOrinalPos = std::sqrt(std::pow((otherBlock.x - m_PuchedObjectOriginalPos.x), 2) + std::pow((otherBlock.y - m_PuchedObjectOriginalPos.y), 2));

				if (distanceBetweenOrinalPos <= m_ObjTexSize.x + smallOfset || distanceBetweenOrinalPos <= m_ObjTexSize.y + smallOfset)
				{
					m_BlockClose = true;
					// if the player is pushing towards the close block
					auto DirectionCloseBlock = GetDirection(m_PuchedObjectOriginalPos, m_ObjTexSize, otherBlock, m_ObjTexSize);
					if (DirectionCloseBlock == -m_HitDirection)
					{
						m_BlockNextToBlock = true;
						break;
					}
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
				m_BlockPushed = false;
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
			//auto distanceBetweenOrinalPos = std::sqrt(std::pow((objPos.x - m_PuchedObjectOriginalPos.x), 2) + std::pow((objPos.y - m_PuchedObjectOriginalPos.y), 2));
			auto directionBetweenBlocks = GetDirection(ownerPos, m_ObjTexSize, objPos, m_ObjTexSize);
			if (directionBetweenBlocks == -m_LatestHitDirection)
			{
				// stop gliding
				m_pObjs.push_back(m_pPuchedObject);
				m_BlockPushed = false;

				// move object a bit back
				glm::vec3 currentPos{ m_pPuchedObject->GetWorldPosition() };

				currentPos.x -= m_SlidingSpeed * m_SlideDir.x * deltaTime * 1.5f;
				currentPos.y -= m_SlidingSpeed * m_SlideDir.y * deltaTime * 1.5f;
				m_pPuchedObject->SetLocalPosition(currentPos.x, currentPos.y);

				break;
			}
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

glm::f32vec2 dae::CollisionComp::GetDirection(glm::f32vec2 objPos1, glm::f32vec2 objSize1, glm::f32vec2 objPos2, glm::f32vec2 objSize2) const
{
	// give direction
	float directionX = (objPos1.x + objSize1.x) - (objPos2.x + objSize2.x);
	float directionY = (objPos1.y + objSize1.y) - (objPos2.y + objSize2.y);
	//std::cout << directionX << ", " << directionY << std::endl;

	if (std::abs(directionX) > std::abs(directionY))
	{
		if (directionX > 0)
		{
			return { 1.f, 0.f };
		}
		else
		{
			return { -1.f, 0.f };
		}
	}
	else
	{
		if (directionY > 0)
		{
			return { 0.f, 1.f };
		}
		else
		{
			return { 0.f, -1.f };
		}
	}
}
