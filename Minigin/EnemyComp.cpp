#include "EnemyComp.h"
#include "GameObject.h"
#include "CollisionComp.h"
#include "SpriteAnimatorComp.h"

dae::EnemyComp::EnemyComp(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
	m_pEnemyChanged = std::make_unique<Subject>();
}

void dae::EnemyComp::Update(float deltaTime)
{
	if (m_RandomMovement)
	{
		// if colliside with somthingw
		auto ownerObj = GetGameObject().lock();
		auto colComp = ownerObj->GetComponent<CollisionComp>();
		if (colComp != nullptr)
		{
			if (colComp->GetHitDir() != m_LastDir)
			{
				auto objTransform{ ownerObj->GetComponent<TransformComp>() };
				glm::vec3 currentPos{ objTransform->GetWorldPosition() };

				// move pos game obejct
				currentPos.x += m_Speed * m_LastDir.x * deltaTime;
				currentPos.y += m_Speed * m_LastDir.y * deltaTime;
				objTransform->SetLocalPosition(currentPos.x, currentPos.y, currentPos.z);

				// sprite rotation and switching
				if (m_LastDir == glm::f32vec2{ 0.f, 1.f })
				{
					ownerObj->GetComponent<SpriteAnimatorComp>()->SetDirection(Direction::Down);
				}
				else if (m_LastDir == glm::f32vec2{ 1.f, 0.f })
				{
					ownerObj->GetComponent<SpriteAnimatorComp>()->SetDirection(Direction::Right);
				}
				else if (m_LastDir == glm::f32vec2{ 0.f, -1.f })
				{
					ownerObj->GetComponent<SpriteAnimatorComp>()->SetDirection(Direction::Up);
				}
				else if (m_LastDir == glm::f32vec2{ -1.f, 0.f })
				{
					ownerObj->GetComponent<SpriteAnimatorComp>()->SetDirection(Direction::Left);
				}
			}
			else
			{
				// rotate object if it hit a wall
				if (m_LastDir == glm::f32vec2{ 0.f, 1.f })
				{
					// form down to right
					m_LastDir = glm::f32vec2{ 1.f, 0.f };
				}
				else if (m_LastDir == glm::f32vec2{ 1.f, 0.f })
				{
					// form right to up
					m_LastDir = glm::f32vec2{ 0.f, -1.f };
				}
				else if (m_LastDir == glm::f32vec2{ 0.f, -1.f })
				{
					// form up to left
					m_LastDir = glm::f32vec2{ -1.f, 0.f };
				}
				else if (m_LastDir == glm::f32vec2{ -1.f, 0.f })
				{
					// form left to down
					m_LastDir = glm::f32vec2{ 0.f, 1.f };
				}
			}
		}
	}
}

void dae::EnemyComp::Die()
{
	m_pEnemyChanged.get()->Notify(*GetGameObject().lock().get(), Event::EnemyDie);
}

void dae::EnemyComp::SetRandomMovement(bool randomMovementOn)
{
	m_RandomMovement = randomMovementOn;
}

bool dae::EnemyComp::IsMovingRandomly() const
{
	return m_RandomMovement;
}

dae::Subject* dae::EnemyComp::GetEnemySubject() const
{
	return m_pEnemyChanged.get();
}

