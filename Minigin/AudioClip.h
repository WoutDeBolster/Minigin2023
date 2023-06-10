#pragma once
#include <string>
#include "SDL_mixer.h"

class AudioClip final
{
public:
	AudioClip(const std::string& fileName);
	~AudioClip();

	AudioClip(const AudioClip&) = delete;
	AudioClip(AudioClip&&) = delete;
	AudioClip& operator= (const AudioClip&) = delete;
	AudioClip& operator= (const AudioClip&&) = delete;

	void LoadSound();

	bool IsSoundLoaded();

	void PlaySound();

	void SetVolume(int volume);
	int GetVolume();

	void SetLoop(bool loopSound);

private:
	Mix_Chunk* m_pSound = nullptr;
	Mix_Chunk* m_pMusic = nullptr;
	std::string m_FileName;

	bool m_IsSoundLoaded = false;
	bool m_IsMusicLoaded = false;
	bool m_LoopSound = false;
	int m_Volume = 0;
};