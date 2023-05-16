#include <iostream>
#include "AudioClip.h"

AudioClip::AudioClip(const std::string& fileName)
{
	m_FileName = fileName;
}

AudioClip::~AudioClip()
{
	Mix_FreeChunk(m_pSound);
}

void AudioClip::LoadSound()
{
	Mix_Chunk* m{ Mix_LoadWAV(m_FileName.c_str()) };
	if (m == nullptr)
	{
		std::cout << "loadMusic failed " << Mix_GetError() << std::endl;
	}
	m_pSound = m;
	m_IsLoaded = true;
}

bool AudioClip::IsLoaded()
{
	return m_IsLoaded;
}

void AudioClip::PlaySound()
{
	m_pSound->volume = static_cast<Uint8>(m_Volume);
	Mix_PlayChannel(-1, m_pSound, 0);
}

void AudioClip::SetVolume(int volume)
{
	m_Volume = (MIX_MAX_VOLUME * volume) / 100;
}

int AudioClip::GetVolume()
{
	return m_Volume;
}
