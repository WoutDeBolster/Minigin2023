#include "ImguiComp.h"
#include <array>
#include <chrono>
//#include <SDL.h>
//
////#include <imgui.h>
//#include <backends/imgui_impl_sdl.h>
//#include <backends/imgui_impl_opengl2.h>
//#include <imgui_plot.h>
//
//// exercise 1, 2 and 3 stuff
//// =========================
//struct Transform
//{
//	float matrix[16] = {
//		1,0,0,0,
//		0,1,0,0,
//		0,0,1,0,
//		0,0,0,1 };
//};
//
//class GameObject3D
//{
//public:
//	Transform transform;
//	int ID;
//};
//
//class GameObject3DAlt
//{
//public:
//	Transform* transform;
//	int ID;
//};
//
//std::array<int, 10000000> m_ArrayEx1{};
//std::array<GameObject3D, 10000000> m_ArrayEx2GO{};
//std::array<GameObject3DAlt, 10000000> m_ArrayEx2GOA{};
//// =========================
//
//dae::ImguiComp::ImguiComp(std::shared_ptr<GameObject> pOwner, SDL_Window* pWindow)
//	: BaseComponent(pOwner)
//	, m_pWindow{ pWindow }
//{
//	IMGUI_CHECKVERSION();
//	ImGui::CreateContext();
//	ImGui_ImplSDL2_InitForOpenGL(pWindow, SDL_GL_GetCurrentContext());
//	ImGui_ImplOpenGL2_Init();
//}
//
//dae::ImguiComp::~ImguiComp()
//{
//	ImGui_ImplOpenGL2_Shutdown();
//	ImGui_ImplSDL2_Shutdown();
//	ImGui::DestroyContext();
//
//	m_pWindow = nullptr;
//}
//
//void dae::ImguiComp::Update(float)
//{
//	// imgui
//	ImGui_ImplOpenGL2_NewFrame();
//	ImGui_ImplSDL2_NewFrame(m_pWindow);
//	ImGui::NewFrame();
//
//	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
//	ImGui::InputInt("# amount of samples", &m_SampleSizeEx1);
//	// exercise 1
//	if (ImGui::Button("Calculate Exercise 1"))
//	{
//		Exercise1();
//	}
//	if (m_Ex1Done)
//	{
//		ImGui::PlotConfig confEx1;
//		confEx1.values.xs = m_StepSizes.data();
//		confEx1.values.ys = m_AverageEx1.data();
//		confEx1.values.count = static_cast<int>(m_StepSizes.size());
//		confEx1.scale.min = 0;
//		confEx1.scale.max = *std::max_element(m_AverageEx1.begin(), m_AverageEx1.end());
//		confEx1.tooltip.show = true;
//		confEx1.tooltip.format = "x=%.2f, y=%.2f";
//		confEx1.grid_x.show = true;
//		confEx1.grid_y.show = true;
//		confEx1.frame_size = ImVec2(200, 100);
//		confEx1.line_thickness = 2.f;
//
//		ImGui::Plot("Exercise 1", confEx1);
//	}
//	ImGui::End();
//
//	// exercise 2 Game Object
//	ImGui::Begin("Exercise 2 and 3", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
//	ImGui::InputInt("# amount of samples", &m_SampleSizeEx2);
//	if (ImGui::Button("Calculate Exercise 2"))
//	{
//		Exercise2GameObj();
//	}
//	if (m_Ex2GODone)
//	{
//		ImGui::PlotConfig confEx2;
//		confEx2.values.xs = m_StepSizes.data();
//		confEx2.values.ys = m_AverageEx2GO.data();
//		confEx2.values.count = static_cast<int>(m_StepSizes.size());
//		confEx2.scale.min = 0;
//		confEx2.scale.max = *std::max_element(m_AverageEx2GO.begin(), m_AverageEx2GO.end());
//		confEx2.tooltip.show = true;
//		confEx2.tooltip.format = "x=%.2f, y=%.2f";
//		confEx2.grid_x.show = true;
//		confEx2.grid_y.show = true;
//		confEx2.frame_size = ImVec2(200, 100);
//		confEx2.line_thickness = 2.f;
//
//		ImGui::Plot("Exercise 2", confEx2);
//	}
//
//	// exercise 2 Game Object alt
//	if (ImGui::Button("Calculate Exercise 3"))
//	{
//		Exercise2GameObjAlt();
//	}
//	if (m_Ex2GOADone)
//	{
//		ImGui::PlotConfig confEx3;
//		confEx3.values.xs = m_StepSizes.data();
//		confEx3.values.ys = m_AverageEx2GOA.data();
//		confEx3.values.count = static_cast<int>(m_StepSizes.size());
//		confEx3.scale.min = 0;
//		confEx3.scale.max = *std::max_element(m_AverageEx2GOA.begin(), m_AverageEx2GOA.end());
//		confEx3.tooltip.show = true;
//		confEx3.tooltip.format = "x=%.2f, y=%.2f";
//		confEx3.grid_x.show = true;
//		confEx3.grid_y.show = true;
//		confEx3.frame_size = ImVec2(200, 100);
//		confEx3.line_thickness = 2.f;
//
//		ImGui::Plot("Exercise 2", confEx3);
//	}
//
//	if (m_Ex2GODone && m_Ex2GOADone)
//	{
//		const float* pGraphCombination[] = { m_AverageEx2GO.data(), m_AverageEx2GOA.data() };
//
//		ImGui::PlotConfig confEx23;
//		confEx23.values.xs = m_StepSizes.data();
//		confEx23.values.ys_list = &pGraphCombination[0];
//		confEx23.values.ys_count = 2;
//		confEx23.values.count = static_cast<int>(m_StepSizes.size());
//		confEx23.scale.min = 0;
//		confEx23.scale.max = 10000;
//		confEx23.tooltip.show = true;
//		confEx23.tooltip.format = "x=%.2f, y=%.2f";
//		confEx23.grid_x.show = true;
//		confEx23.grid_y.show = true;
//		confEx23.frame_size = ImVec2(200, 100);
//		confEx23.line_thickness = 2.f;
//
//		ImGui::Plot("Exercise 2 and 3 combined", confEx23);
//	}
//	ImGui::End();
//}
//
//void dae::ImguiComp::Render() const
//{
//	ImGui::Render();
//	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
//}
//
//void dae::ImguiComp::Exercise1()
//{
//	int stepSize{ 1 };
//	std::vector<long long> times{};
//
//	for (int x = 0; stepSize <= 1024; ++x)
//	{
//		for (size_t y = 0; y < m_SampleSizeEx1; ++y)
//		{
//			auto startTime = std::chrono::high_resolution_clock::now();
//
//			for (int i = 0; i < m_ArrayEx1.size(); i += stepSize)
//			{
//				m_ArrayEx1[i] += 1;
//			}
//
//			auto endTime = std::chrono::high_resolution_clock::now();
//			times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
//		}
//
//		long long totalTime{};
//		for (size_t i = 0; i < times.size(); ++i)
//		{
//			totalTime += times[i];
//		}
//
//		float averageTime{ static_cast<float>(totalTime) / static_cast<float>(m_SampleSizeEx1) };
//		totalTime = 0;
//		times.clear();
//		m_AverageEx1.push_back(averageTime);
//
//		stepSize *= 2;
//	}
//
//	m_Ex1Done = true;
//}
//
//void dae::ImguiComp::Exercise2GameObj()
//{
//	int stepSize{ 1 };
//	std::vector<long long> times{};
//
//	for (int x = 0; stepSize <= 1024; ++x)
//	{
//		for (size_t y = 0; y < m_SampleSizeEx2; ++y)
//		{
//			auto startTime = std::chrono::high_resolution_clock::now();
//
//			for (int i = 0; i < m_ArrayEx2GO.size(); i += stepSize)
//			{
//				m_ArrayEx2GO[i].ID += 1;
//			}
//
//			auto endTime = std::chrono::high_resolution_clock::now();
//			times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
//		}
//
//		long long totalTime{};
//		for (size_t i = 0; i < times.size(); ++i)
//		{
//			totalTime += times[i];
//		}
//
//		float averageTime{ static_cast<float>(totalTime) / static_cast<float>(m_SampleSizeEx2) };
//		totalTime = 0;
//		times.clear();
//		m_AverageEx2GO.push_back(averageTime);
//
//		stepSize *= 2;
//	}
//
//	m_Ex2GODone = true;
//}
//
//void dae::ImguiComp::Exercise2GameObjAlt()
//{
//	int stepSize{ 1 };
//	std::vector<long long> times{};
//
//	for (int x = 0; stepSize <= 1024; ++x)
//	{
//		for (size_t y = 0; y < m_SampleSizeEx2; ++y)
//		{
//			auto startTime = std::chrono::high_resolution_clock::now();
//
//			for (int i = 0; i < m_ArrayEx2GOA.size(); i += stepSize)
//			{
//				m_ArrayEx2GOA[i].ID += 1;
//			}
//
//			auto endTime = std::chrono::high_resolution_clock::now();
//			times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
//		}
//
//		long long totalTime{};
//		for (size_t i = 0; i < times.size(); ++i)
//		{
//			totalTime += times[i];
//		}
//
//		float averageTime{ static_cast<float>(totalTime) / static_cast<float>(m_SampleSizeEx2) };
//		totalTime = 0;
//		times.clear();
//		m_AverageEx2GOA.push_back(averageTime);
//
//		stepSize *= 2;
//	}
//
//	m_Ex2GOADone = true;
//}
