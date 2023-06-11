#include "CollisionComp.h"
#include "SpriteAnimatorComp.h"
#include "ActorComp.h"
#include "EnemyComp.h"
#include "HealthComp.h"
#include "PointsComp.h"
#include "SoundSystem.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <iostream>

dae::CollisionComp::CollisionComp(std::weak_ptr<GameObject> pOwner, glm::ivec2 textureSize,
	std::vector<std::shared_ptr<Block>> blockObjs, std::vector<std::shared_ptr<GameObject>> EnemyObjs)
	: BaseComponent(pOwner)
	, m_ObjTexSize{ textureSize }
	, m_pBlockObjs{ blockObjs }
	, m_pEnemyObjs{ EnemyObjs }
{
}

void dae::CollisionComp::AddObject(std::shared_ptr<Block> blockObjs)
{
	m_pBlockObjs.emplace_back(std::move(blockObjs));
}

void dae::CollisionComp::AddEnemys(std::shared_ptr<GameObject> EnemyObjs)
{
	m_pEnemyObjs.emplace_back(std::move(EnemyObjs));
}

void dae::CollisionComp::Update(float deltaTime)
{
	if (m_pBlockObjs.size() > 0)
	{
		CheckCollsionWithBlocks(deltaTime);
		PushBlock(deltaTime);
		if (m_SlowDownTimer > 0.f)
		{
			m_SlowDownTimer -= deltaTime;
		}
	}

	if (m_pEnemyObjs.size() > 0 && m_AllEnemysDead == false)
	{
		CheckCollisionWithEnemys();
	}
	if (m_pEnemyObjs.empty() && m_AllEnemysDead)
	{
		SceneManager::GetInstance().SetSceneActive("Level1", false);
		SceneManager::GetInstance().SetSceneActive("Level2", true);
	}
}

bool dae::CollisionComp::IsOverlapping() const
{
	return m_IsOverlapping;
}

float dae::CollisionComp::GetSlowDownTimer() const
{
	return m_SlowDownTimer;
}

glm::vec2 dae::CollisionComp::GetHitDir() const
{
	return m_HitDirection;
}

void dae::CollisionComp::PushBlock(float deltaTime)
{
	if (m_BlockPushed)
	{
		CheckCollsionPushedObj(m_pPuchedObject, deltaTime);

		glm::vec3 currentPos{ m_pPuchedObject->GetBlockObj()->GetWorldPosition() };

		// move pos game obejct
		currentPos.x += m_SlidingSpeed * m_SlideDir.x * deltaTime;
		currentPos.y += m_SlidingSpeed * m_SlideDir.y * deltaTime;
		m_pPuchedObject->GetBlockObj()->SetLocalPosition(currentPos.x, currentPos.y);
	}
}

void dae::CollisionComp::CheckCollsionWithBlocks(float deltaTime)
{
	auto ownerObj = GetGameObject().lock();
	auto ownerPos = ownerObj->GetWorldPosition();
	auto ownerSize = glm::ivec2{ 24, 24 };

	for (size_t i = 0; i < m_pBlockObjs.size(); i++)
	{
		auto objPos = m_pBlockObjs[i]->GetBlockObj()->GetWorldPosition();

		if (ownerPos.x <= objPos.x + m_ObjTexSize.x &&
			ownerPos.x + ownerSize.x >= objPos.x &&
			ownerPos.y <= objPos.y + m_ObjTexSize.y &&
			ownerPos.y + ownerSize.y >= objPos.y)
		{
			m_IsOverlapping = true;
			//std::cout << "Hit" << std::endl;

			// getting direction between player and block
			m_HitDirection = GetDirection(objPos, m_ObjTexSize, ownerPos, ownerSize);
			m_LatestHitDirection = m_HitDirection;

			// if it is not a random actor or if the block cant be pushed
			if (ownerObj->GetComponent<ActorComp>() != nullptr && m_pBlockObjs[i]->GetIsPushible())
			{
				// setting up glidding
				m_pPuchedObject = std::move(m_pBlockObjs[i]);
				m_pBlockObjs.erase(std::remove(m_pBlockObjs.begin(), m_pBlockObjs.end(), m_pBlockObjs[i]));

				// first see if there is a block in the direction of pushing
				m_PuchedObjectOriginalPos = objPos;

				for (size_t q = 0; q < m_pBlockObjs.size(); q++)
				{
					auto otherBlock = m_pBlockObjs[q]->GetBlockObj()->GetWorldPosition();
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
					m_BlockNextToBlock = false;

					// slow down player
					m_SlowDownTimer = 2.f;
				}
			}
			else
			{
				// move the random moving object back a bit
				auto actorSpeed{ 50.f };
				ownerPos.x -= actorSpeed * m_HitDirection.x * deltaTime * 1.5f;
				ownerPos.y -= actorSpeed * m_HitDirection.y * deltaTime * 1.5f;
				ownerObj->SetLocalPosition(ownerPos.x, ownerPos.y);
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

void dae::CollisionComp::CheckCollisionWithEnemys()
{
	auto ownerObj = GetGameObject().lock();
	auto ownerPos = ownerObj->GetWorldPosition();
	auto ownerSize = glm::ivec2{ 24, 24 };

	for (size_t i = 0; i < m_pEnemyObjs.size(); i++)
	{
		auto objPos = m_pEnemyObjs[i]->GetWorldPosition();

		if (ownerPos.x <= objPos.x + ownerSize.x &&
			ownerPos.x + ownerSize.x >= objPos.x &&
			ownerPos.y <= objPos.y + ownerSize.y &&
			ownerPos.y + ownerSize.y >= objPos.y)
		{
			ownerObj->GetComponent<HealthComp>()->DistractHealth(1);
			ownerObj->SetLocalPosition(264.f, 300.f);
		}
	}
}

void dae::CollisionComp::CheckCollsionPushedObj(std::weak_ptr<Block> block, float deltaTime)
{
	auto ownerPos = block.lock()->GetBlockObj()->GetWorldPosition();

	// hitting blocks
	for (size_t i = 0; i < m_pBlockObjs.size(); i++)
	{
		auto objPos = m_pBlockObjs[i]->GetBlockObj()->GetWorldPosition();

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
				m_pBlockObjs.push_back(m_pPuchedObject);
				m_BlockPushed = false;

				// move object a bit back
				glm::vec3 currentPos{ m_pPuchedObject->GetBlockObj()->GetWorldPosition() };

				currentPos.x -= m_SlidingSpeed * m_SlideDir.x * deltaTime * 1.5f;
				currentPos.y -= m_SlidingSpeed * m_SlideDir.y * deltaTime * 1.5f;
				m_pPuchedObject->GetBlockObj()->SetLocalPosition(currentPos.x, currentPos.y);

				// sound
				ServisLocator::GetSoundSystem().play(1, 50, false);

				break;
			}
		}
	}

	// hitting enemys
	for (size_t i = 0; i < m_pEnemyObjs.size(); i++)
	{
		auto objPos = m_pEnemyObjs[i]->GetWorldPosition();

		if (ownerPos.x <= objPos.x + m_ObjTexSize.x &&
			ownerPos.x + m_ObjTexSize.x >= objPos.x &&
			ownerPos.y <= objPos.y + m_ObjTexSize.y &&
			ownerPos.y + m_ObjTexSize.y >= objPos.y)
		{
			//std::cout << "Hit Enemy" << std::endl;

			m_pEnemyObjs[i]->GetComponent<EnemyComp>()->Die();
			GetGameObject().lock()->GetComponent<PointsComp>()->AddPoints(100);
			m_pEnemyObjs.erase(std::remove(m_pEnemyObjs.begin(), m_pEnemyObjs.end(), m_pEnemyObjs[i]));
			if (m_pEnemyObjs.empty())
			{
				m_AllEnemysDead = true;
			}
		}
	}
}

void dae::CollisionComp::BreakBlock(std::weak_ptr<Block> block)
{
	// TODO: this is so skuffed plz fix this
	std::vector<std::string> BreakableObjFiles{ "Blocks/BreakingBlock_01.png", "Blocks/BreakingBlock_02.png",
		"Blocks/BreakingBlock_03.png", "Blocks/BreakingBlock_04.png",
		"Blocks/BreakingBlock_05.png", "Blocks/BreakingBlock_06.png",
		"Blocks/BreakingBlock_07.png", "Blocks/BreakingBlock_08.png" };

	if (block.lock()->GetBlockObj()->GetComponent<SpriteAnimatorComp>() != nullptr)
	{
		block.lock()->GetBlockObj()->GetComponent<SpriteAnimatorComp>()->PlayAnimation(BreakableObjFiles, true);
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
