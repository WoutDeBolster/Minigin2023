#include "Block.h"
#include "TextureComp.h"


dae::Block::Block(glm::vec2 pos, std::string fileName, bool Pushable)
	: m_IsPushible{ Pushable }
{
	auto block = std::make_shared<GameObject>();
	block.get()->Initialize();
	auto texBlock = std::make_shared<TextureComp>(block, "Blocks/Block_01.png");

	block->AddComponent(texBlock);
	block->SetLocalPosition(pos.x, pos.y);

	m_BlockObj = block;
}

std::shared_ptr<dae::GameObject> dae::Block::GetBlockObj()
{
	return m_BlockObj;
}
