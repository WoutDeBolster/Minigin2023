
#include "SoundSystem.h"

NullSoundSystem ServisLocator::m_ss_Default;
std::shared_ptr<SoundSystem> ServisLocator::m_ss_Instance = std::make_shared<NullSoundSystem>(m_ss_Default);

class SdlSoundSystem::sdlSoundSystemImpl
{
public:
	sdlSoundSystemImpl() = default;
	virtual ~sdlSoundSystemImpl();

	void InitSoundSystem();
	void play(const sound_id id, const int volume, bool loopSound);
	void PauzeSound(const sound_id id);
	void RegisterSound(const sound_id id, const std::string& path);

private:
	std::vector<std::shared_ptr<AudioClip>> m_AudioClips;
};


//SDL Sound System
SdlSoundSystem::SdlSoundSystem()
{
	m_pImpl = new sdlSoundSystemImpl();
}

SdlSoundSystem::~SdlSoundSystem()
{
	Mix_CloseAudio();
	delete m_pImpl;
}

void SdlSoundSystem::AddAudio(std::shared_ptr<AudioClip> audio)
{
	m_AudioClips.push_back(audio);
}

void SdlSoundSystem::InitSoundSystem()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "coudnt open mixerAudio" << Mix_GetError() << std::endl;
	}
	m_AudioClips.resize(50);
}

void SdlSoundSystem::play(const sound_id id, const int volume, bool loopSound)
{
	auto audioClip = m_AudioClips[id];
	if (audioClip->IsSoundLoaded() == false)
	{
		audioClip->LoadSound();
	}
	audioClip->SetLoop(loopSound);
	audioClip->SetVolume(volume);
	audioClip->PlaySound();
}

void SdlSoundSystem::PauzeSound(const sound_id id)
{
	auto audioClip = m_AudioClips[id];
	audioClip->PauzeSound();
}

void SdlSoundSystem::RegisterSound(const sound_id id, const std::string& path)
{
	auto audioClip = std::make_shared<AudioClip>(path);
	m_AudioClips[id] = audioClip;
}

//SDL sound system IMPl
SdlSoundSystem::sdlSoundSystemImpl::~sdlSoundSystemImpl()
{
	Mix_CloseAudio();
}

void SdlSoundSystem::sdlSoundSystemImpl::InitSoundSystem()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "coudnt open mixerAudio" << Mix_GetError() << std::endl;
	}
	m_AudioClips.resize(50);
}

void SdlSoundSystem::sdlSoundSystemImpl::play(const sound_id id, const int volume, bool loopSound)
{
	auto audioClip = m_AudioClips[id];
	if (audioClip->IsSoundLoaded() == false)
	{
		audioClip->LoadSound();
	}
	audioClip->SetLoop(loopSound);
	audioClip->SetVolume(volume);
	audioClip->PlaySound();
}

void SdlSoundSystem::sdlSoundSystemImpl::PauzeSound(const sound_id id)
{
	auto audioClip = m_AudioClips[id];
	audioClip->PauzeSound();
}

void SdlSoundSystem::sdlSoundSystemImpl::RegisterSound(const sound_id id, const std::string& path)
{
	auto audioClip = std::make_shared<AudioClip>(path);
	m_AudioClips[id] = audioClip;
}
