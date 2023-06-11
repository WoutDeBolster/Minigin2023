#pragma once
#include <vector>
#include <string>
#include "Block.h"
#include "Scene.h"

namespace dae
{
	class JSonReader : public Singleton<JSonReader>
	{
	public:
		JSonReader() = default;
		~JSonReader() = default;

		JSonReader(const JSonReader&) = delete;
		JSonReader(JSonReader&&) noexcept = delete;
		JSonReader& operator=(const JSonReader&) = delete;
		JSonReader& operator=(JSonReader&&) noexcept = delete;

		dae::Scene& MakeLevel(const std::string& filePath);

		dae::Scene& MakeScoreScene(const std::string& sceneName);
		void ReadHighScore(const std::string& filePath);
		void WriteHighscore(const std::string& filePath);
		void AddToTotalScore(int score);

		std::vector<std::shared_ptr<Block>> GetBlocks() const;
		std::vector<std::shared_ptr<GameObject>> GetEnemys() const;

	private:
		void MakeEnemy(glm::vec2 pos, dae::Scene& scene);
		std::string m_File;

		// level objects
		std::vector<std::shared_ptr<Block>> m_pBlocks;
		std::vector<std::shared_ptr<GameObject>> m_pEnemys;
		std::vector<int> m_Scores;
		int m_CurrentScore{};
	};
}


