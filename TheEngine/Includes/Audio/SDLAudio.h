#pragma once

#include "Audio/IAudio.h"
#include <unordered_map>

struct _Mix_Music;
struct Mix_Chunk;

namespace NPEngine
{
	//Provider audio with SDL
	class SDLAudio final : public IAudio
	{
	private:
		std::unordered_map<size_t, _Mix_Music*> _MusicMap;
		std::unordered_map<size_t, Mix_Chunk*> _SoundMap;

	public:
		virtual ~SDLAudio() = default;

		virtual size_t LoadMusic(const std::string& Filename) override;
		virtual size_t LoadSound(const std::string& Filename) override;

		virtual void PlayMusic(size_t MusicId, int Loop) override;
		virtual void PlaySound(size_t SoundId, int Loop) override;

		virtual void PauseMusic() override;
		virtual void StopMusic() override;
		virtual void ResumeMusic() override;

		virtual void SetMusicVolume(int Volume) override;
		virtual void SetSoundVolume(size_t SoundId, int Volume) override;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;
	};
}