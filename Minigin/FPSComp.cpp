#include "FPSComp.h"
#include "GameObject.h"
#include "TextComp.h"
#include <string>

dae::FPSComp::FPSComp(std::weak_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::FPSComp::Update(float deltaTime)
{
	m_FPS = static_cast<int>(1.f / deltaTime);
	m_TextUpdateTimer += deltaTime;

	if (m_TextUpdateTimer >= 0.5f)
	{
		GetGameObject().lock().get()->GetComponent<TextComp>()->SetText(std::to_string(m_FPS) + "FPS");
		m_TextUpdateTimer = 0.f;
	}
}

int dae::FPSComp::GetFPS() const
{
	return m_FPS;
}