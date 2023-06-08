#pragma once
#include <vector>
#include <string>
#include "Block.h"
#include "Scene.h"

namespace dae
{
	class JSonReader
	{
	public:
		JSonReader(std::string fileLoc);
		~JSonReader() = default;

		JSonReader(const JSonReader&) = delete;
		JSonReader(JSonReader&&) noexcept = delete;
		JSonReader& operator=(const JSonReader&) = delete;
		JSonReader& operator=(JSonReader&&) noexcept = delete;

		dae::Scene& MakeLevel();
		std::vector<std::shared_ptr<Block>> GetBlocks() const;

	private:
		std::string m_File;

		// level objects
		std::string m_LevelName{};
		std::vector<std::shared_ptr<Block>> m_pBlocks;
	};
}


