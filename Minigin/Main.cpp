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

void TestImgui()
{

}

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// background
	auto go = std::make_shared<GameObject>();
	std::shared_ptr<TextureComp> textureBackground = std::make_shared<TextureComp>(go, "background.tga");
	std::shared_ptr<TransformComp> transform = std::make_shared<TransformComp>(go);

	go->AddComponent(textureBackground);
	go->AddComponent(transform);

	scene.Add(go);

	// dae logo
	go = std::make_shared<GameObject>();
	std::shared_ptr<TextureComp> textureLogo = std::make_shared<TextureComp>(go, "logo.tga");
	transform = std::make_shared<TransformComp>(go);

	go->AddComponent(textureLogo);
	go->AddComponent(transform);

	go->SetWorldPosition(216, 180);
	scene.Add(go);

	// top text
	auto to = std::make_shared<GameObject>();
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<TextComp> text = std::make_shared<TextComp>(to, "Programming 4 Assignment"
		, font, SDL_Color(255, 255, 255));
	transform = std::make_shared<TransformComp>(to);

	to->AddComponent(text);
	to->AddComponent(transform);

	to->SetWorldPosition(80, 20);
	scene.Add(to);

	// FPS object
	auto FPSCompCounter = std::make_shared<GameObject>();
	std::shared_ptr<FPSComp> FPS = std::make_shared<FPSComp>(FPSCompCounter);
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	std::shared_ptr<TextComp> text2 = std::make_shared<TextComp>(FPSCompCounter, std::to_string(FPS->GetFPS())
		, font2, SDL_Color(255, 255, 255));
	transform = std::make_shared<TransformComp>(FPSCompCounter);

	FPSCompCounter->AddComponent(FPS);
	FPSCompCounter->AddComponent(text2);
	FPSCompCounter->AddComponent(transform);

	FPSCompCounter->SetWorldPosition(10, 10);
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
}

int main(int, char* []) {
	g_engine.Run(load);
	return 0;
}