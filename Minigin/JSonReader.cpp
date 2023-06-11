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
#include "ResourceManager.h"
#include "SDL.h"
#include "TextComp.h"
#include "HealthBoardComp.h"
#include <memory>
#include "EnemyComp.h"
#include "CollisionComp.h"

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
	const rapidjson::Value& blockSizeWidth = doc["BlockWidth"];
	const rapidjson::Value& blockSizeHeight = doc["BlockHeight"];

	const rapidjson::Value& blockTexture = doc["BlockTexture"];
	const rapidjson::Value& blockRowIDs = doc["BlockXIDs"];
	const rapidjson::Value& blockColIDs = doc["BlockYIDs"];

	const rapidjson::Value& diamondBlockTexture = doc["DiamondBlockTexture"];
	const rapidjson::Value& diamondBlockRowIDs = doc["DiamondBlockXIDs"];
	const rapidjson::Value& diamondBlockColIDs = doc["DiamondBlockYIDs"];

	const rapidjson::Value& borderBlockTexture = doc["BorderBlockTexture"];
	const rapidjson::Value& borderBlockRowIDs = doc["BorderBlockXIDs"];
	const rapidjson::Value& borderBlockColIDs = doc["BorderBlockYIDs"];

	// making level
	auto& scene = SceneManager::GetInstance().CreateScene(levelName.GetString());

	float borderSize{ 16.f };
	glm::vec2 LevelOffset{ 51.f, 85.f };

	//float gridBlockWidth{ 13.f };
	//float gridBlockHeight{ 15.f };

	// movable blocks
	for (size_t y = 0; y < blockRowIDs.GetArray().Size(); y++)
	{
		glm::vec2 pos{ (blockRowIDs.GetArray()[y].GetInt()* blockSizeWidth.GetInt()) + LevelOffset.x + borderSize - blockSizeWidth.GetInt(),
			(blockColIDs.GetArray()[y].GetInt()* blockSizeHeight.GetInt()) + LevelOffset.y + borderSize - blockSizeHeight.GetInt() };
		std::string fileName{ blockTexture.GetString() };
		auto block = std::make_shared<Block>(pos, "Blocks/" + fileName, true);
		auto blockObj = block->GetBlockObj();
		blockObj->AddComponent(std::make_shared<SpriteAnimatorComp>(blockObj));

		m_pBlocks.push_back(block);
		scene.Add(blockObj);
	}

	// non movable blocks
	for (size_t y = 0; y < diamondBlockRowIDs.GetArray().Size(); y++)
	{
		glm::vec2 pos{ (diamondBlockRowIDs.GetArray()[y].GetInt()* blockSizeWidth.GetInt()) + LevelOffset.x + borderSize - blockSizeWidth.GetInt(),
			(diamondBlockColIDs.GetArray()[y].GetInt()* blockSizeHeight.GetInt()) + LevelOffset.y + borderSize - blockSizeHeight.GetInt() };
		std::string fileName{ diamondBlockTexture.GetString() };
		auto block = std::make_shared<Block>(pos, "Blocks/" + fileName, false);
		auto blockObj = block->GetBlockObj();
		//blockObj->AddComponent(std::make_shared<SpriteAnimatorComp>(blockObj));

		m_pBlocks.push_back(block);
		scene.Add(blockObj);
	}

	// border blocks
	for (size_t y = 0; y < borderBlockRowIDs.GetArray().Size(); y++)
	{
		glm::vec2 pos{ (borderBlockRowIDs.GetArray()[y].GetInt()* blockSizeWidth.GetInt()) + LevelOffset.x + borderSize - blockSizeWidth.GetInt(),
			(borderBlockColIDs.GetArray()[y].GetInt()* blockSizeHeight.GetInt()) + LevelOffset.y + borderSize - blockSizeHeight.GetInt() };
		std::string fileName{ borderBlockTexture.GetString() };
		auto block = std::make_shared<Block>(pos, "Blocks/" + fileName, false);
		auto blockObj = block->GetBlockObj();
		//blockObj->AddComponent(std::make_shared<SpriteAnimatorComp>(blockObj));

		m_pBlocks.push_back(block);
		scene.Add(blockObj);
	}

	// enemys
	// health board
	glm::ivec2 blockSize{ 32, 32 };

	auto health = std::make_shared<GameObject>();
	auto healthBoard = std::make_shared<HealthBoardComp>(health);

	auto enemy = std::make_shared<GameObject>();
	enemy.get()->Initialize();
	auto actorEnemy = std::make_shared<EnemyComp>(enemy);
	actorEnemy->SetRandomMovement(true);

	auto colCompEnemy = std::make_shared<CollisionComp>(enemy, blockSize, m_pBlocks, m_pEnemys);

	auto spriteCompEnemy = std::make_shared<SpriteAnimatorComp>(enemy);
	spriteCompEnemy->SetDirectionalSprites(Direction::Down, { "Enemys/Enemy_09.png", "Enemys/Enemy_10.png" });
	spriteCompEnemy->SetDirectionalSprites(Direction::Left, { "Enemys/Enemy_11.png", "Enemys/Enemy_12.png" });
	spriteCompEnemy->SetDirectionalSprites(Direction::Up, { "Enemys/Enemy_13.png", "Enemys/Enemy_14.png" });
	spriteCompEnemy->SetDirectionalSprites(Direction::Right, { "Enemys/Enemy_15.png", "Enemys/Enemy_16.png" });

	actorEnemy->GetEnemySubject()->AddObserver(healthBoard);

	enemy->AddComponent(actorEnemy);
	enemy->AddComponent(spriteCompEnemy);
	enemy->AddComponent(colCompEnemy);

	enemy->SetLocalPosition(236.f, 336.f);
	scene.Add(enemy);
	m_pEnemys.push_back(enemy);

	return scene;
}

std::vector<std::shared_ptr<dae::Block>> dae::JSonReader::GetBlocks() const
{
	return m_pBlocks;
}

std::vector<std::shared_ptr<dae::GameObject>> dae::JSonReader::GetEnemys() const
{
	return m_pEnemys;
}
