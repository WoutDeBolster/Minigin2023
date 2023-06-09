#include "ActorComp.h"
#include "GameObject.h"
#include "CollisionComp.h"
#include "SpriteAnimatorComp.h"

dae::ActorComp::ActorComp(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
	m_pActorChanged = std::make_unique<Subject>();
}

void dae::ActorComp::Update(float)
{
}

void dae::ActorComp::Die()
{
	m_pActorChanged.get()->Notify(*GetGameObject().lock().get(), Event::ActorDie);
}

dae::Subject* dae::ActorComp::GetActorSubject() const
{
	return m_pActorChanged.get();
}

