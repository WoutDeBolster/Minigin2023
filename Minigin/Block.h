#pragma once
#include <glm/glm.hpp>
#include <string>
#include "GameObject.h"

namespace dae
{
	class Block final
	{
	public:
		Block(glm::vec2 pos, std::string fileName, bool Pushable);
		~Block() = default;

		Block(const Block&) = delete;
		Block(Block&&) = delete;
		Block& operator= (const Block&) = delete;
		Block& operator= (const Block&&) = delete;

		std::shared_ptr<dae::GameObject> GetBlockObj();
		//void  (float elapsed);

	private:
		bool m_IsPushible;
		std::shared_ptr<dae::GameObject> m_BlockObj;
	};
}