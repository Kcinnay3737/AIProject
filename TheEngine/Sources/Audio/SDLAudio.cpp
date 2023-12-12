#include "Audio/SDLAudio.h"

#include "Engine.h"
#include "Logger/ILogger.h"
#include <SDL_mixer.h>
#include <string>

using namespace NPEngine;

bool SDLAudio::Initialize(const Param& Params)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	return true;
}

void SDLAudio::Shutdown(const Param& Params)
{
	for (auto& Music : _MusicMap)
	{
		Mix_FreeMusic(Music.second);
		Music.second = nullptr;
	}
	_MusicMap.clear();

	for (auto& Sound : _SoundMap)
	{
		Mix_FreeChunk(Sound.second);
		Sound.second = nullptr;
	}
	_SoundMap.clear();

	Mix_CloseAudio();
}

size_t SDLAudio::LoadMusic(const std::string& Filename)
{
	//Get ID
	std::hash<std::string> Hasher;
	size_t MusicId = Hasher(Filename);

	//Load the music
	if (_MusicMap.find(MusicId) == _MusicMap.end())
	{
		std::string FilePath = "./Assets/Audio/Music/";
		FilePath += Filename;
		Mix_Music* Music = Mix_LoadMUS(FilePath.c_str());
		if (Music)
		{
			_MusicMap[MusicId] = Music;
		}
		else
		{
			Engine::GetLogger()->LogMessage("Music not found");
		}
	}

	return MusicId;
}

size_t SDLAudio::LoadSound(const std::string& Filename)
{
	//Get the ID
	std::hash<std::string> Hasher;
	size_t SoundId = Hasher(Filename);

	//Load the sound
	if (_SoundMap.find(SoundId) == _SoundMap.end())
	{
		std::string FilePath = "./Assets/Audio/Sound/";
		FilePath += Filename;
		Mix_Chunk* Sound = Mix_LoadWAV(FilePath.c_str());
		if (Sound)
		{
			_SoundMap[SoundId] = Sound;
		}
		else
		{
			Engine::GetLogger()->LogMessage("Sound effect not found");
		}
	}

	return SoundId;
}

void SDLAudio::PlayMusic(size_t MusicId, int Loop)
{
	//Get the music
	Mix_Music* Music = _MusicMap[MusicId];
	if (Music)
	{
		//Play the music
		if (Mix_PlayMusic(Music, Loop) == -1)
		{
			Engine::GetLogger()->LogMessage("Failed to play music");
		}
	}
	else
	{
		Engine::GetLogger()->LogMessage("Music not found");
	}
}

void SDLAudio::PlaySound(size_t SoundId, int Loop)
{
	//Get the sound
	Mix_Chunk* Sound = _SoundMap[SoundId];
	if (Sound)
	{
		//Play the sound
		if (Mix_PlayChannel(-1, Sound, Loop) == -1)
		{
			Engine::GetLogger()->LogMessage("Failed to play sound");
		}
	}
	else
	{
		Engine::GetLogger()->LogMessage("Sound not found");
	}
}

void SDLAudio::PauseMusic()
{
	Mix_PauseMusic();
}

void SDLAudio::StopMusic()
{
	Mix_HaltMusic();
}

void SDLAudio::ResumeMusic()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void SDLAudio::SetMusicVolume(int Volume)
{
	Volume = std::max(0, std::min(Volume, MIX_MAX_VOLUME));
	Mix_VolumeMusic(Volume);
}

void SDLAudio::SetSoundVolume(size_t SoundId, int Volume)
{
	Mix_Chunk* Sound = _SoundMap[SoundId];
	if (Sound)
	{
		Volume = std::max(0, std::min(Volume, MIX_MAX_VOLUME));
		Mix_VolumeChunk(Sound, Volume);
	}
	else
	{
		Engine::GetLogger()->LogMessage("Sound not found");
	}
}