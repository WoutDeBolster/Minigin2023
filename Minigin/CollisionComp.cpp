#include "CollisionComp.h"

dae::CollisionComp::CollisionComp(std::weak_ptr<GameObject> pOwner, glm::ivec2 textureSize, Scene& scene)
	: BaseComponent(pOwner)
	, m_TexSize{ textureSize }
	, m_Scene{ scene }
{
}

void dae::CollisionComp::Update(float)
{
}
