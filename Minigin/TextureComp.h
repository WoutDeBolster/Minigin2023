#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Texture2D;
	class TextureComp final : public BaseComponent
	{
	public:
		TextureComp(std::weak_ptr<GameObject> pOwner, const std::string& filename);
		~TextureComp() = default;

		TextureComp(const TextureComp&) = delete;
		TextureComp(TextureComp&&) = delete;
		TextureComp& operator= (const TextureComp&) = delete;
		TextureComp& operator= (const TextureComp&&) = delete;

		void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}