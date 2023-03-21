#pragma once
#include "BaseComponent.h"
#include <vector>
#include <array>
#include <SDL.h>

namespace dae
{
	// trash the cash 
	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		Transform transform;
		int ID;
	};

	class GameObject3DAlt
	{
	public:
		Transform* transform;
		int ID;
	};

	class ImguiComp final : public BaseComponent
	{
	public:
		ImguiComp(SDL_Window* pWindow, std::shared_ptr<GameObject> pOwner);
		virtual ~ImguiComp();

		ImguiComp(const ImguiComp&) = delete;
		ImguiComp(ImguiComp&&) = delete;
		ImguiComp& operator= (const ImguiComp&) = delete;
		ImguiComp& operator= (const ImguiComp&&) = delete;

		void Update(float deltaTime) override;
		virtual void Render() const override;

	private:
		void Exercise1();
		void Exercise2();

		SDL_Window* m_pWindow{};

		std::vector<float> m_AverageEx1{};
		std::vector<float> m_AverageEx2{};

		std::array<int, 67108864> m_ArrayEx1{};
		std::array<GameObject3DAlt, 67108864> m_ArrayEx2{};

		std::vector<float> m_StepSizes{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };

		int m_SampleSizeEx1{ 100 };

		bool m_StartEx1{ false };
		bool m_StartEx2{ false };
	};
}

