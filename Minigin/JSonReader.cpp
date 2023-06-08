#include "JSonReader.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "SceneManager.h"
#include "SpriteAnimatorComp.h"

dae::JSonReader::JSonReader(std::string fileLoc)
	: m_File{ fileLoc }
{
}

dae::Scene& dae::JSonReader::MakeLevel()
{
	// Open the file
	std::ifstream is{ m_File };

	assert(!is.fail() && "File Not found");

	rapidjson::IStreamWrapper isw{ is };

	// Parse the JSON document
	rapidjson::Document doc;
	doc.ParseStream(isw);

	// ******************
	// getting the values
	// ******************
	const rapidjson::Value& levelName = doc["LevelName"];
	const rapidjson::Value& blockTexture = doc["TextureName"];
	const rapidjson::Value& blockSizeWidth = doc["BlockWidth"];
	const rapidjson::Value& blockSizeHeight = doc["BlockHeight"];
	const rapidjson::Value& blockRowIDs = doc["BlockXIDs"];
	const rapidjson::Value& blockColIDs = doc["BlockYIDs"];

	// making level
	auto& scene = SceneManager::GetInstance().CreateScene(levelName.GetString());

	float borderSize{ 16.f };
	glm::vec2 LevelOffset{ 26.f, 60.f };

	//float gridBlockWidth{ 13.f };
	//float gridBlockHeight{ 15.f };
	for (size_t y = 0; y < blockColIDs.GetArray().Size(); y++)
	{
		glm::vec2 pos{ (blockRowIDs.GetArray()[y].GetInt() * blockSizeWidth.GetInt()) + LevelOffset.x + borderSize - blockSizeWidth.GetInt() ,
						(blockColIDs.GetArray()[y].GetInt() * blockSizeHeight.GetInt()) + LevelOffset.y + borderSize - blockSizeHeight.GetInt() };
		std::string fileName{ blockTexture.GetString() };
		auto block = std::make_shared<Block>(pos, "Blocks/" + fileName, true);
		auto blockObj = block->GetBlockObj();
		blockObj->AddComponent(std::make_shared<SpriteAnimatorComp>(blockObj));

		m_pBlocks.push_back(block);
		scene.Add(blockObj);
	}
	return scene;
}

std::vector<std::shared_ptr<dae::Block>> dae::JSonReader::GetBlocks() const
{
	return m_pBlocks;
}
