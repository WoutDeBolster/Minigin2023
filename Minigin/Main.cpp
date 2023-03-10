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

using namespace dae;

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

	//
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}