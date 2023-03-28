#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComp.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

dae::TextComp::TextComp(std::shared_ptr<GameObject> pOwner, const std::string& text,
	const std::shared_ptr<Font> font, const SDL_Color& color)
	: BaseComponent(pOwner)
	, m_NeedsUpdate(true)
	, m_text(text)
	, m_font(font)
	, m_textTexture(nullptr)
	, m_Color{ color }
{
}

void dae::TextComp::Update(float)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // TODO: only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComp::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = m_pGameObject.lock().get()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComp::SetText(const std::string& text)
{
	m_text = text;
	m_NeedsUpdate = true;
}