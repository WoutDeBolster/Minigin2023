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
		std::cout << "loadSound failed " << Mix_GetError() << std::endl;
	}
	m_pSound = m;
	m_IsSoundLoaded = true;
}

bool AudioClip::IsSoundLoaded()
{
	return m_IsSoundLoaded;
}

void AudioClip::PlaySound()
{
	m_pSound->volume = static_cast<Uint8>(m_Volume);
	if (m_LoopSound)
	{
		Mix_PlayChannel(-1, m_pSound, -1);
	}
	else
	{
		Mix_PlayChannel(-1, m_pSound, 0);
	}
}

void AudioClip::PauzeSound()
{
	if (m_SoundPauzed)
	{
		Mix_Resume(-1);
		m_SoundPauzed = false;
	}
	else
	{
		Mix_Pause(-1);
		m_SoundPauzed = true;
	}
}

void AudioClip::SetVolume(int volume)
{
	m_Volume = (MIX_MAX_VOLUME * volume) / 100;
}

int AudioClip::GetVolume()
{
	return m_Volume;
}

void AudioClip::SetLoop(bool loopSound)
{
	m_LoopSound = loopSound;
}
