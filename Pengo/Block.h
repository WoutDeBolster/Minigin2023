#pragma once
#include <glm/glm.hpp>
#include <string>
#include "GameObject.h"

class Block
{
public:
	Block();
	~Block() = default;

	Block(const Block&) = delete;
	Block(Block&&) = delete;
	Block& operator= (const Block&) = delete;
	Block& operator= (const Block&&) = delete;

	std::shared_ptr<dae::GameObject> MakeBlock(glm::vec2 pos, std::string fileName);


private:


	std::vector<std::shared_ptr<dae::GameObject>> m_Blocks;
};

