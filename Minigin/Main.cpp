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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

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

	//// rotating characters
	//// -------------------
	//auto character1 = std::make_shared<GameObject>();
	//std::shared_ptr<TextureComp> textureChar1 = std::make_shared<TextureComp>(character1, "Pengo.png");
	//transform = std::make_shared<TransformComp>(character1);

	//character1->AddComponent(textureChar1);
	//character1->AddComponent(transform);

	//character1->SetWorldPosition(216, 180);
	//scene.Add(character1);

	//auto character2 = std::make_shared<GameObject>();
	//std::shared_ptr<TextureComp> textureChar2 = std::make_shared<TextureComp>(character2, "Enemy.png");
	//transform = std::make_shared<TransformComp>(character2);

	//character2->AddComponent(textureChar2);
	//character2->AddComponent(transform);

	//character2->SetWorldPosition(200, 180);

	//// tests
	//character1->AddChild(character2);
	//character1->RemoveChild(character2);
	//character1->AddChild(character2);

	//// OBJ READER
	//// ----------
	//TestObjReader();

	//// Imgui TEST
	//// ----------
	//SDL_Window* window{ g_engine.GetWindow() };
	//auto ImguiObj = std::make_shared<GameObject>();
	//std::shared_ptr<ImguiComp> imgui = std::make_shared<ImguiComp>(ImguiObj, window);

	//ImguiObj->AddComponent(imgui);
	//scene.Add(ImguiObj);

	// TEST Input
	// ----------
	// player 1
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
	input.SetButtonCommand(controllerOne, dae::GamePad::ControllerButton::ButtonA,
		new MoveCommand(player1, 100.f, glm::f32vec2{ 0.f, 1.f }), InputType::keyPressed);
	input.SetButtonCommand(controllerOne, dae::GamePad::ControllerButton::ButtonB,
		new MoveCommand(player1, 100.f, glm::f32vec2{ 1.f, 0.f }), InputType::keyPressed);
	input.SetButtonCommand(controllerOne, dae::GamePad::ControllerButton::ButtonY,
		new MoveCommand(player1, 100.f, glm::f32vec2{ 0.f, -1.f }), InputType::keyPressed);
	input.SetButtonCommand(controllerOne, dae::GamePad::ControllerButton::ButtonX,
		new MoveCommand(player1, 100.f, glm::f32vec2{ -1.f, 0.f }), InputType::keyPressed);

	// player 2
	input.SetButtonCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Down,
		new MoveCommand(player2, 100.f, glm::f32vec2{ 0.f, 1.f }), InputType::keyPressed);
	input.SetButtonCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Right,
		new MoveCommand(player2, 100.f, glm::f32vec2{ 1.f, 0.f }), InputType::keyPressed);
	input.SetButtonCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Up,
		new MoveCommand(player2, 100.f, glm::f32vec2{ 0.f, -1.f }), InputType::keyPressed);
	input.SetButtonCommand(controllerTwo, dae::GamePad::ControllerButton::Dpad_Left,
		new MoveCommand(player2, 100.f, glm::f32vec2{ -1.f, 0.f }), InputType::keyPressed);
}

int main(int, char* []) {
	g_engine.Run(load);
	return 0;
}