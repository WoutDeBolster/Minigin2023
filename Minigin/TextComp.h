#pragma once
#include "BaseComponent.h"
#include <string>
#include <SDL.h>

namespace dae
{
	class Font;
	class Texture2D;
	class TextComp final : public BaseComponent
	{
	public:
		explicit TextComp(std::weak_ptr<GameObject> pOwner, const std::string& text,
			std::shared_ptr<Font> font, const SDL_Color& color);
		virtual ~TextComp() = default;

		TextComp(const TextComp& other) = delete;
		TextComp(TextComp&& other) = delete;
		TextComp& operator=(const TextComp& other) = delete;
		TextComp& operator=(TextComp&& other) = delete;

		void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text);

	private:
		bool m_NeedsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		SDL_Color m_Color;
	};
}
