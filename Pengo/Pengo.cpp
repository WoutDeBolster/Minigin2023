
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

// other
#include "Font.h"
#include "Achievements.h"
#include "Observer.h"

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
	// fonts
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	// player itself
	auto player = std::make_shared<GameObject>();
	player.get()->Initialize();
	auto actorPlayer = std::make_shared<ActorComp>(player);
	auto terxturePlayer = std::make_shared<TextureComp>(player, "Pengo/Pengo_01.png");

	player->AddComponent(actorPlayer);
	player->AddComponent(terxturePlayer);

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

void ObserverTest(Scene& scene)
{
	// players
	auto player1 = MakePlayer(0, { 0, 250 }, scene);
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

	// top text
	auto to = std::make_shared<dae::GameObject>();
	to.get()->Initialize();
	std::shared_ptr<dae::Font> font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<dae::TextComp> text = std::make_shared<dae::TextComp>(to, "Programming 4 Assignment"
		, font, SDL_Color{ 255, 255, 255 });

	to->AddComponent(text);

	to->SetLocalPosition(80, 20);
	scene.Add(to);

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

std::shared_ptr<GameObject> Block(glm::vec2 pos)
{
	auto block = std::make_shared<GameObject>();
	block.get()->Initialize();
	auto texBlock = std::make_shared<TextureComp>(block, "Blocks/Block_01.png");

	block->AddComponent(texBlock);
	block->SetLocalPosition(pos.x, pos.y);

	return block;
}

void BuildLevel(Scene& scene)
{
	float blockSize{ 32.f };
	float borderSize{ 16.f };
	glm::vec2 LevelOffset{ 26.f, 60.f };

	float gridBlockWidth{ 13.f };
	float gridBlockHeight{ 15.f };

	for (float y = 0; y < gridBlockHeight; y++)
	{
		for (float x = 0; x < gridBlockWidth; x++)
		{
			auto block = Block({ (x * blockSize) + LevelOffset.x + borderSize , (y * blockSize) + LevelOffset.y + borderSize });
			scene.Add(block);
		}
	}

	// border
	auto border = std::make_shared<GameObject>();
	border.get()->Initialize();
	auto texBorder = std::make_shared<TextureComp>(border, "GameBorder.png");

	border->AddComponent(texBorder);
	border->SetLocalPosition(LevelOffset.x, LevelOffset.y);

	scene.Add(border);
}

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	StandertBackground(scene);
	ObserverTest(scene);
	BuildLevel(scene);
}

int main(int, char* []) {
	g_engine.Run(load);
	return 0;
}