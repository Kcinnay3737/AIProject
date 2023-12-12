#pragma once

#include "Time/ITime.h"

namespace NPEngine
{
	//Time provider with sdl
	class SDLTime final : public ITime
	{
	public:

	private:

	public:
		virtual ~SDLTime() = default;

		float GetDeltaTime() override;
		void SetFramePerSecond(int FramePerSecond) override;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;

		virtual void UpdateDeltaTime() override;
		virtual void UpdateLastFrameStartTime() override;
		virtual void UpdateCurrentFrameStartTime() override;
		virtual void ControlFrameRate() override;

		virtual void InitialiseTime() override;
		virtual void OnStartFrame() override;
		virtual void OnEndFrame() override;
	};
}