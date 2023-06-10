
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"

// comps
#include "TextureComp.h"
#include "TextComp.h"
#include "FPSComp.h"
#include "HealthBoardComp.h"
#include "HealthComp.h"
#include "ScoreBoardComp.h"
#include "PointsComp.h"
#include "ActorComp.h"
#include "EnemyComp.h"
#include "CollisionComp.h"
#include "SpriteAnimatorComp.h"

// other
#include "Font.h"
#include "Achievements.h"
#include "Observer.h"
#include "Block.h"
#include "JSonReader.h"
#include "SoundSystem.h"
#include "AudioClip.h"

dae::Minigin g_engine("../Data/");

using namespace dae;

std::shared_ptr<GameObject> MakeTextObj(glm::vec2 pos, const std::string& text,
	std::shared_ptr<Font> font, const SDL_Color& color, Scene& scene)
{
	auto textObj = std::make_shared<GameObject>();
	textObj.get()->Initialize();
	auto textComp = std::make_shared<TextComp>(textObj, text, font, color);

	textObj->AddComponent(textComp);

	textObj->SetLocalPosition(pos.x, pos.y);

	scene.Add(textObj);
	return textObj;
}

std::shared_ptr<GameObject> MakePlayer(unsigned int playerIdx, glm::vec2 pos, Scene& scene)
{
	//// fonts
	//std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	// player itself
	auto player = std::make_shared<GameObject>();
	player.get()->Initialize();
	auto actorPlayer = std::make_shared<ActorComp>(player);

	player->AddComponent(actorPlayer);

	player->SetLocalPosition(pos.x, pos.y);

	// input
	const float playerSpeed{ 100.f };
	auto& input = InputManager::GetInstance();

	// player 1
	input.SetGamePadCommand(playerIdx, dae::GamePad::ControllerButton::Dpad_Down,
		new MoveCommand(player, playerSpeed, glm::f32vec2{ 0.f, 1.f }), InputType::keyPressed);
	input.SetGamePadCommand(playerIdx, dae::GamePad::ControllerButton::Dpad_Right,
		new MoveCommand(player, playerSpeed, glm::f32vec2{ 1.f, 0.f }), InputType::keyPressed);
	input.SetGamePadCommand(playerIdx, dae::GamePad::ControllerButton::Dpad_Up,
		new MoveCommand(player, playerSpeed, glm::f32vec2{ 0.f, -1.f }), InputType::keyPressed);
	input.SetGamePadCommand(playerIdx, dae::GamePad::ControllerButton::Dpad_Left,
		new MoveCommand(player, playerSpeed, glm::f32vec2{ -1.f, 0.f }), InputType::keyPressed);

	scene.Add(player);

	return player;
}

void StandertBackground(dae::Scene& scene)
{
	//// background
	//auto go = std::make_shared<dae::GameObject>();
	//go.get()->Initialize();
	//std::shared_ptr<dae::TextureComp> textureBackground = std::make_shared<dae::TextureComp>(go, "background.tga");

	//go->AddComponent(textureBackground);

	//scene.Add(go);

	//// dae logo
	//go = std::make_shared<dae::GameObject>();
	//go.get()->Initialize();
	//std::shared_ptr<dae::TextureComp> textureLogo = std::make_shared<dae::TextureComp>(go, "logo.tga");

	//go->AddComponent(textureLogo);

	//go->SetLocalPosition(216, 180);
	//scene.Add(go);

	//// top text
	//auto to = std::make_shared<dae::GameObject>();
	//to.get()->Initialize();
	//std::shared_ptr<dae::Font> font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//std::shared_ptr<dae::TextComp> text = std::make_shared<dae::TextComp>(to, "Programming 4 Assignment"
	//	, font, SDL_Color{ 255, 255, 255 });

	//to->AddComponent(text);

	//to->SetLocalPosition(80, 20);
	//scene.Add(to);

	// FPS object
	auto FPSCompCounter = std::make_shared<dae::GameObject>();
	FPSCompCounter.get()->Initialize();
	std::shared_ptr<dae::FPSComp> FPS = std::make_shared<dae::FPSComp>(FPSCompCounter);
	std::shared_ptr<dae::Font> font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	std::shared_ptr<dae::TextComp> text2 = std::make_shared<dae::TextComp>(FPSCompCounter, std::to_string(FPS->GetFPS())
		, font2, SDL_Color{ 255, 255, 255 });

	FPSCompCounter->AddComponent(FPS);
	FPSCompCounter->AddComponent(text2);

	FPSCompCounter->SetLocalPosition(10, 10);
	scene.Add(FPSCompCounter);
}

void SoundLoading()
{
#if _DEBUG
	ServisLocator::RegisterSoundSystem(std::make_shared<LogginSoundSystem>(std::make_shared<SdlSoundSystem>()));
#else
	ServisLocator::RegisterSoundSystem(std::make_shared<SdlSoundSystem>());
#endif
	// first test play
	//ServisLocator::RegisterSoundSystem(std::make_shared<LogginSoundSystem>(std::make_shared < SdlSoundSystem>()));

	ServisLocator::GetSoundSystem().InitSoundSystem();
	ServisLocator::GetSoundSystem().RegisterSound(0, "../Data/Main BGM (Popcorn).mp3");
	ServisLocator::GetSoundSystem().RegisterSound(1, "../Data/Block Stopped.mp3");
	ServisLocator::GetSoundSystem().RegisterSound(2, "../Data/Touch Snow-Bee.mp3");
	ServisLocator::GetSoundSystem().RegisterSound(3, "../Data/Snow-Bee Squashed.mp3");
	ServisLocator::GetSoundSystem().play(0, 50, true);
}

void MakeLevel(std::string levelFile)
{
	auto reader = std::make_shared<JSonReader>(levelFile);
	auto& scene = reader->MakeLevel();
	auto pBlocks = reader->GetBlocks();

	StandertBackground(scene);
	SoundLoading();

	glm::ivec2 blockSize{ 32, 32 };
	std::vector<std::shared_ptr<GameObject>> pEnemys;

	// fonts
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	// health board
	auto health = MakeTextObj({ 34.f, 50.f }, "Lives: 3", font2, SDL_Color{ 1, 1, 1, 1 }, scene);
	auto healthBoard = std::make_shared<HealthBoardComp>(health);

	// score board
	auto score = MakeTextObj({ 420.f, 50.f }, "Score: 0", font2, SDL_Color{ 1, 1, 1, 1 }, scene);
	auto scoreBoard = std::make_shared<ScoreBoardComp>(score);

	// enemys
	auto enemy = std::make_shared<GameObject>();
	enemy.get()->Initialize();
	auto actorEnemy = std::make_shared<EnemyComp>(enemy);
	actorEnemy->SetRandomMovement(true);

	auto colCompEnemy = std::make_shared<CollisionComp>(enemy, blockSize);
	for (size_t i = 0; i < pBlocks.size(); i++)
	{
		colCompEnemy->AddObject(pBlocks[i]);
	}

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
	pEnemys.push_back(enemy);

	// player and collision
	auto player1 = MakePlayer(0, { 264.f, 300.f }, scene);
	auto colComp = std::make_shared<CollisionComp>(player1, blockSize);
	for (size_t i = 0; i < pBlocks.size(); i++)
	{
		colComp->AddObject(pBlocks[i]);
	}
	for (size_t i = 0; i < pEnemys.size(); i++)
	{
		colComp->AddEnemys(pEnemys[i]);
	}

	// sprites
	auto spriteComp = std::make_shared<SpriteAnimatorComp>(player1);
	spriteComp->SetDirectionalSprites(Direction::Down, { "Pengo/Pengo_01.png", "Pengo/Pengo_02.png" });
	spriteComp->SetDirectionalSprites(Direction::Left, { "Pengo/Pengo_03.png", "Pengo/Pengo_04.png" });
	spriteComp->SetDirectionalSprites(Direction::Up, { "Pengo/Pengo_05.png", "Pengo/Pengo_06.png" });
	spriteComp->SetDirectionalSprites(Direction::Right, { "Pengo/Pengo_07.png", "Pengo/Pengo_08.png" });

	// points and health
	auto pointsComp = std::make_shared<PointsComp>(player1);
	auto healthComp = std::make_shared<HealthComp>(player1);

	pointsComp->GetPointSubject()->AddObserver(scoreBoard);
	healthComp->GetHeatlthSubject()->AddObserver(healthBoard);

	player1->AddComponent(colComp);
	player1->AddComponent(spriteComp);
	player1->AddComponent(pointsComp);
	player1->AddComponent(healthComp);
}

void load()
{
	MakeLevel("../Data/Level_1.json");
	MakeLevel("../Data/Level_2.json");
	MakeLevel("../Data/Level_3.json");
}

int main(int, char* []) {
	g_engine.Run(load);
	return 0;
}