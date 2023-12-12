#pragma once

#include "Audio/IAudioProvider.h"

namespace NPEngine
{
	//Interface for audio provider
	class IAudio : public IAudioProvider
	{
	public:
		virtual ~IAudio() = default;
		 
		//Load a music and return the id
		virtual size_t LoadMusic(const std::string& Filename) = 0;
		//Load a sound and return the id
		virtual size_t LoadSound(const std::string& Filename) = 0;

		//Play music with a id
		virtual void PlayMusic(size_t MusicId, int Loop = -1) = 0;
		//Play sound with a id
		virtual void PlaySound(size_t SoundId, int Loop = 0) = 0;

		//Pause the music
		virtual void PauseMusic() = 0;
		//Stop the music
		virtual void StopMusic() = 0;
		//Resume the music
		virtual void ResumeMusic() = 0;

		//Set the music volume
		virtual void SetMusicVolume(int Volume) = 0;
		//Set the sound volume
		virtual void SetSoundVolume(size_t SoundId, int Volume) = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;
	};
}