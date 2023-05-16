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

	void LoadMusic();
	void LoadSound();

	bool IsLoaded();

	void PlayMusic();
	void PlaySound();

	void SetVolume(int volume);
	int GetVolume();

private:
	Mix_Chunk* m_pSound = nullptr;
	std::string m_FileName;

	bool m_IsLoaded = false;
	int m_Volume = 0;
};