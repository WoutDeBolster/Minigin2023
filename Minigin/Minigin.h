#pragma once
#include <string>
#include <functional>
struct SDL_Window;
namespace dae
{

	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		SDL_Window* GetWindow();

	private:
		static const int m_MsPerFrame = 16; //16 for 60 FPSComp, 33 for 30 FPSComp
		const float m_FixedTimeStep = 0.02f;
	};
}