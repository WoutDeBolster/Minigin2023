#include "JSonReader.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "SceneManager.h"
#include "SpriteAnimatorComp.h"
#include "ResourceManager.h"
#include "SDL.h"
#include "TextComp.h"
#include "HealthBoardComp.h"
#include <memory>
#include "EnemyComp.h"
#include "CollisionComp.h"
#include "Font.h"

dae::Scene& dae::JSonReader::MakeLevel(const std::string& filePath)
{
	// clear last values if there were any
	m_pBlocks.clear();
	m_pEnemys.clear();

	// Open the file
	std::ifstream is{ filePath };

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
	MakeEnemy({ LevelOffset.x + borderSize, (8 * 32.f) + LevelOffset.y + borderSize }, scene);
	MakeEnemy({ (12 * 32) + LevelOffset.x + borderSize, LevelOffset.y + borderSize }, scene);
	MakeEnemy({ (12 * 32) + LevelOffset.x + borderSize, (14 * 32.f) + LevelOffset.y + borderSize }, scene);


	return scene;
}

dae::Scene& dae::JSonReader::MakeScoreScene(const std::string& sceneName)
{
	// making Scene
	auto& scene = SceneManager::GetInstance().CreateScene(sceneName);

	// make text Objects and place them
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	for (size_t i = 0; i < m_Scores.size(); i++)
	{
		// stop at number 10
		if (i == 10.f)
		{
			break;
		}
		auto textObj = std::make_shared<GameObject>();
		textObj->Initialize();
		auto textComp = std::make_shared<TextComp>(textObj, std::to_string(i + 1) + ": " + std::to_string(m_Scores[i]), font, SDL_Color{ 1, 1, 1, 1 });

		textObj->AddComponent(textComp);
		textObj->SetLocalPosition(220.f, (50.f * i) + 50.f);
		scene.Add(textObj);
	}

	return scene;
}

void dae::JSonReader::ReadHighScore(const std::string& filePath)
{
	// getting highscores
	std::vector<int> scores{ };
	std::ifstream is{ filePath };

	assert(!is.fail() && "File Not found");

	rapidjson::IStreamWrapper isw{ is };
	rapidjson::Document document;
	document.ParseStream(isw);

	assert(document.IsArray() && "Json Highscore needs an array");

	const rapidjson::Value& scoresJson = document;

	for (size_t i = 0; i < scoresJson.Size(); i++)
	{
		scores.push_back(scoresJson[i].GetInt());
	}

	// sort them just to be sure
	std::sort(scores.begin(), scores.end(), std::greater());
	m_Scores = scores;
}

void dae::JSonReader::WriteHighscore(const std::string& filePath)
{
	// opening file
	std::ofstream os{ filePath };

	assert(!os.fail() && "File Not found");

	rapidjson::Document document;
	document.SetArray();

	// adding new score
	m_Scores.push_back(m_CurrentScore);

	// writing data	
	for (size_t i = 0; i < m_Scores.size(); i++)
	{
		rapidjson::Value value;
		value.SetInt(m_Scores[i]);
		document.PushBack(value, document.GetAllocator());
	}

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	std::string jsonString = buffer.GetString();

	os << jsonString;
}

void dae::JSonReader::AddToTotalScore(int score)
{
	m_CurrentScore += score;
}

std::vector<std::shared_ptr<dae::Block>> dae::JSonReader::GetBlocks() const
{
	return m_pBlocks;
}

std::vector<std::shared_ptr<dae::GameObject>> dae::JSonReader::GetEnemys() const
{
	return m_pEnemys;
}

void dae::JSonReader::MakeEnemy(glm::vec2 pos, dae::Scene& scene)
{
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

	enemy->SetLocalPosition(pos.x, pos.y);
	scene.Add(enemy);
	m_pEnemys.push_back(enemy);
}
