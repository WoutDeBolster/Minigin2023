#include "TextureComp.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextureComp.h"

dae::TextureComp::TextureComp(std::weak_ptr<GameObject> pOwner, const std::string& filename)
	:BaseComponent(pOwner)
{
	SetTexture(filename);
}

void dae::TextureComp::Update(float)
{
}

void dae::TextureComp::Render() const
{
	const auto& pos = m_pGameObject.lock().get()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::TextureComp::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
