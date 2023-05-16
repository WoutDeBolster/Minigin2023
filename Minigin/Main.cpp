#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
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

#include "TextComp.h"
#include "TextureComp.h"
#include "FPSComp.h"
#include "TransformComp.h"
#include "ImguiComp.h"
#include "HealthBoardComp.h"
#include "ScoreBoardComp.h"
#include "HealthComp.h"
#include "PointsComp.h"
#include "ActorComp.h"
#include "Achievements.h"
#include "Subject.h"
#include "SoundSystem.h"

#include "ObjReader.h"

using namespace dae;

dae::Minigin g_engine("../Data/");

void TestObjReader()
{
	//std::vector<Vertex> vertices;
	//std::vector<Face> faces;

	//auto objReader = std::make_shared<ObjReader>("LowPolyBunny.obj");
	//objReader.get()->ParseObjFile(vertices, faces);
	//objReader.get()->WriteBobj("LowPolyBunnyBinary.Bobj");
}

void StandertBackground(Scene& scene)
{
	// background
	auto go = std::make_shared<GameObject>();
	go.get()->Initialize();
	std::shared_ptr<TextureComp> textureBackground = std::make_shared<TextureComp>(go, "background.tga");

	go->AddComponent(textureBackground);

	scene.Add(go);

	// dae logo
	go = std::make_shared<GameObject>();
	go.get()->Initialize();
	std::shared_ptr<TextureComp> textureLogo = std::make_shared<TextureComp>(go, "logo.tga");

	go->AddComponent(textureLogo);

	go->SetLocalPosition(216, 180);
	scene.Add(go);

	// top text
	auto to = std::make_shared<GameObject>();
	to.get()->Initialize();
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<TextComp> text = std::make_shared<TextComp>(to, "Programming 4 Assignment"
		, font, SDL_Color(255, 255, 255));

	to->AddComponent(text);

	to->SetLocalPosition(80, 20);
	scene.Add(to);

	// FPS object
	auto FPSCompCounter = std::make_shared<GameObject>();
	FPSCompCounter.get()->Initialize();
	std::shared_ptr<FPSComp> FPS = std::make_shared<FPSComp>(FPSCompCounter);
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	std::shared_ptr<TextComp> text2 = std::make_shared<TextComp>(FPSCompCounter, std::to_string(FPS->GetFPS())
		, font2, SDL_Color(255, 255, 255));

	FPSCompCounter->AddComponent(FPS);
	FPSCompCounter->AddComponent(text2);

	FPSCompCounter->SetLocalPosition(10, 10);
	scene.Add(FPSCompCounter);
}

void ImguiTest(Scene&)
{
	//// Imgui TEST
	//// ----------
	//SDL_Window* window{ g_engine.GetWindow() };
	//auto ImguiObj = std::make_shared<GameObject>();
	//std::shared_ptr<ImguiComp> imgui = std::make_shared<ImguiComp>(ImguiObj, window);

	//ImguiObj->AddComponent(imgui);
	//scene.Add(ImguiObj);
}

void InputTest(Scene& scene)
{
	// TEST Input
	// ----------
	// player 1
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	auto player1 = std::make_shared<GameObject>();
	player1.get()->Initialize();
	auto textPlayer1 = std::make_shared<TextComp>(player1, "Player1: Movement using buttons", font2, SDL_Color(200, 200, 200));

	player1->AddComponent(textPlayer1);

	player1->SetLocalPosition(10, 120);
	scene.Add(player1);

	// player 2
	auto player2 = std::make_shared<GameObject>();
	player2.get()->Initialize();
	auto textPlayer2 = std::make_shared<TextComp>(player2, "player2: Movement using dpad", font2, SDL_Color(200, 200, 200));

	player2->AddComponent(textPlayer2);

	player2->SetLocalPosition(10, 150);
	scene.Add(player2);


	// input
	auto& input = InputManager::GetInstance();
	const unsigned int controllerOne{ 0 };
	const unsigned int controllerTwo{ 1 };

	// player 1
	input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonA,
		new MoveCommand(player1, 100.f, glm::f32vec2{ 0.f, 1.f }), InputType::keyPressed);
	input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonB,
		new MoveCommand(player1, 100.f, glm::f32vec2{ 1.f, 0.f }), InputType::keyPressed);
	input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonY,
		new MoveCommand(player1, 100.f, glm::f32vec2{ 0.f, -1.f }), InputType::keyPressed);
	input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonX,
		new MoveCommand(player1, 100.f, glm::f32vec2{ -1.f, 0.f }), InputType::keyPressed);

	// player 2
	input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Down,
		new MoveCommand(player2, 100.f, glm::f32vec2{ 0.f, 1.f }), InputType::keyPressed);
	input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Right,
		new MoveCommand(player2, 100.f, glm::f32vec2{ 1.f, 0.f }), InputType::keyPressed);
	input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Up,
		new MoveCommand(player2, 100.f, glm::f32vec2{ 0.f, -1.f }), InputType::keyPressed);
	input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Left,
		new MoveCommand(player2, 100.f, glm::f32vec2{ -1.f, 0.f }), InputType::keyPressed);
}

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

std::shared_ptr<GameObject> MakePlayer(unsigned int playerIdx, dae::GamePad::ControllerButton inputGainScore, dae::GamePad::ControllerButton inputLoseHealth,
	glm::vec2 pos, const SDL_Color& uiColor, Scene& scene)
{
	// fonts
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	// player 1
	// --------
	auto achievementObserver = std::make_shared<Achievements>();

	// health
	auto health = MakeTextObj({ pos.x, 50 + pos.y }, "Health: 3", font2, uiColor, scene);
	auto healthPlayer1 = std::make_shared<HealthComp>(health);
	auto healthBoard = std::make_shared<HealthBoardComp>(health);

	health->AddComponent(healthPlayer1);
	health->AddComponent(healthBoard);
	healthPlayer1->GetHeatlthSubject()->AddObserver(healthBoard);
	healthPlayer1->GetHeatlthSubject()->AddObserver(achievementObserver);
	scene.Add(health);

	// points
	auto points = MakeTextObj({ pos.x, 100 + pos.y }, "Points: 0", font2, uiColor, scene);
	auto pointsPlayer1 = std::make_shared<PointsComp>(points);
	auto scoreBoard = std::make_shared<ScoreBoardComp>(points);

	points->AddComponent(pointsPlayer1);
	points->AddComponent(scoreBoard);
	pointsPlayer1->GetPointSubject()->AddObserver(scoreBoard);
	pointsPlayer1->GetPointSubject()->AddObserver(achievementObserver);
	scene.Add(health);

	// input
	auto& input = InputManager::GetInstance();

	input.SetGamePadCommand(playerIdx, inputLoseHealth, new LoseHealthCommand(healthPlayer1, 1), InputType::keyDown);
	input.SetGamePadCommand(playerIdx, inputGainScore, new GainScoreCommand(pointsPlayer1, 25), InputType::keyDown);

	// player itself
	auto player = std::make_shared<GameObject>();
	player.get()->Initialize();
	auto textPlayer = std::make_shared<TextComp>(player, "Player " + std::to_string(playerIdx) + ":", font, uiColor);
	auto actorPlayer = std::make_shared<ActorComp>(player);

	//player->AddComponent(textPlayer);
	player->AddComponent(actorPlayer);

	player->SetLocalPosition(pos.x, pos.y);

	scene.Add(player);

	return player;
}

void ObserverTest(Scene& scene)
{
	// players
	auto player1 = MakePlayer(1, dae::GamePad::ControllerButton::ButtonA, dae::GamePad::ControllerButton::ButtonB, { 0, 250 }, SDL_Color{ 255, 0, 0 }, scene);
	auto player2 = MakePlayer(2, dae::GamePad::ControllerButton::ButtonX, dae::GamePad::ControllerButton::ButtonY, { 300, 250 }, SDL_Color{ 0, 0, 255 }, scene);
}

void SoundTest(Scene&)
{
#if _DEBUG
	ServisLocator::RegisterSoundSystem(std::make_shared<LogginSoundSystem>(std::make_shared<SdlSoundSystem>()));
#else
	ServisLocator::RegisterSoundSystem(std::make_shared<SdlSoundSystem>());
#endif

	//ServisLocator::RegisterSoundSystem(std::make_shared<LogginSoundSystem>(std::make_shared < SdlSoundSystem>()));

	ServisLocator::GetSoundSystem().InitSoundSystem();
	ServisLocator::GetSoundSystem().RegisterSound(0, "../Data/Jingle.mp3");
	ServisLocator::GetSoundSystem().play(0, 100);
}

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");


	StandertBackground(scene);

	//ImguiTest(scene);

	//InputTest(scene);

	//ObserverTest(scene);

	SoundTest(scene);

	//// players
	//auto player1 = MakePlayer(1, dae::GamePad::ControllerButton::ButtonA, dae::GamePad::ControllerButton::ButtonB, { 0, 250 }, SDL_Color{ 255, 0, 0 }, scene);
	//auto player2 = MakePlayer(2, dae::GamePad::ControllerButton::ButtonX, dae::GamePad::ControllerButton::ButtonY, { 300, 250 }, SDL_Color{ 0, 0, 255 }, scene);


	//auto textureComp = std::make_shared<TextureComp>(player1, "Sprites/Pengo/Pengo_01.png");
	//player1->AddComponent(textureComp);

	//// input
	//auto& input = InputManager::GetInstance();
	//const unsigned int controllerOne{ 0 };
	//const unsigned int controllerTwo{ 1 };

	//// player 1
	//input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonA,
	//	new MoveCommand(player1, 100.f, glm::f32vec2{ 0.f, 1.f }), InputType::keyPressed);
	//input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonB,
	//	new MoveCommand(player1, 100.f, glm::f32vec2{ 1.f, 0.f }), InputType::keyPressed);
	//input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonY,
	//	new MoveCommand(player1, 100.f, glm::f32vec2{ 0.f, -1.f }), InputType::keyPressed);
	//input.SetGamePadCommand(controllerOne, dae::GamePad::ControllerButton::ButtonX,
	//	new MoveCommand(player1, 100.f, glm::f32vec2{ -1.f, 0.f }), InputType::keyPressed);

	//// player 2
	//input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Down,
	//	new MoveCommand(player2, 100.f, glm::f32vec2{ 0.f, 1.f }), InputType::keyPressed);
	//input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Right,
	//	new MoveCommand(player2, 100.f, glm::f32vec2{ 1.f, 0.f }), InputType::keyPressed);
	//input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Up,
	//	new MoveCommand(player2, 100.f, glm::f32vec2{ 0.f, -1.f }), InputType::keyPressed);
	//input.SetGamePadCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Left,
	//	new MoveCommand(player2, 100.f, glm::f32vec2{ -1.f, 0.f }), InputType::keyPressed);
}

int main(int, char* []) {
	g_engine.Run(load);
	return 0;
}