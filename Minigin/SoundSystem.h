#pragma once
#include "SDL_mixer.h"
#include <mutex>
#include "AudioClip.h"
#include <vector>
#include <memory>
#include <iostream>


using sound_id = unsigned short;
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;

	virtual void play(const sound_id id, const int volume) = 0;
	virtual void RegisterSound(const sound_id id, const std::string& path) = 0;
	virtual void InitSoundSystem() = 0;
};

class SdlSoundSystem final : public SoundSystem
{
public:
	SdlSoundSystem();
	virtual ~SdlSoundSystem();

	void AddAudio(std::shared_ptr<AudioClip> audio);
	void InitSoundSystem();
	void play(const sound_id id, const int volume) override;
	void RegisterSound(const sound_id id, const std::string& path);

private:
	std::vector<std::shared_ptr<AudioClip>> m_AudioClips;
	class sdlSoundSystemImpl;
	sdlSoundSystemImpl* m_pImpl;
};

class NullSoundSystem final : public SoundSystem
{
private:
	void InitSoundSystem() override {}
	void play(const sound_id, const int) override {}
	void RegisterSound(const sound_id, const std::string&) {}
};

class ServisLocator final
{
public:
	static SoundSystem& GetSoundSystem()
	{
		return *m_ss_Instance.get();
	}
	static void RegisterSoundSystem(std::shared_ptr<SoundSystem> ss)
	{
		if (ss)
		{
			m_ss_Instance = ss;
		}
	}

private:
	static NullSoundSystem m_ss_Default;
	static std::shared_ptr<SoundSystem> m_ss_Instance;
};

class LogginSoundSystem final : public SoundSystem
{
public:
	LogginSoundSystem(std::shared_ptr<SoundSystem> ss) : m_ss_real(ss) {}
	~LogginSoundSystem() = default;

	void InitSoundSystem() override
	{
		m_ss_real->InitSoundSystem();
		std::cout << "initing sound system" << std::endl;
	}
	void RegisterSound(const sound_id id, const std::string& path) override
	{
		m_ss_real->RegisterSound(id, path);
		std::cout << "registering sound with path: " << path << std::endl;
	}
	void play(const sound_id id, const int volume) override
	{
		m_ss_real->play(id, volume);
		std::cout << "playing " << id << " at volume " << volume << std::endl;
	}

private:
	std::shared_ptr<SoundSystem> m_ss_real;
};