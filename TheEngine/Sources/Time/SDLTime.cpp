#include "Time/SDLTime.h"

#include <time.h>
#include <SDL.h>

using namespace NPEngine;

bool SDLTime::Initialize(const Param& Params)
{
	auto IT = Params.find("FPS");
	int FramePerSecond = IT != Params.end() ? std::any_cast<int>(IT->second) : 60;
	SetFramePerSecond(FramePerSecond);
	return true;
}

void SDLTime::Shutdown(const Param& Params)
{
}

float SDLTime::GetDeltaTime()
{
	if (_DeltaTime > 0.2f) return 0.2f;
	return _DeltaTime;
}

void SDLTime::SetFramePerSecond(int FramePerSecond)
{
	_FramesPerSecond = FramePerSecond;
	if (_FramesPerSecond <= 0) return;
	_DesiredFrameDuration = 1000 / FramePerSecond;
}

void SDLTime::UpdateDeltaTime()
{
	_DeltaTime = (_CurrentFrameStartTime - _LastFrameStartTime) * 0.001f;
}

void SDLTime::UpdateLastFrameStartTime()
{
	_LastFrameStartTime = _CurrentFrameStartTime;
}

void SDLTime::UpdateCurrentFrameStartTime()
{
	_CurrentFrameStartTime = SDL_GetTicks();
}

void SDLTime::ControlFrameRate()
{
	if (_FramesPerSecond <= 0) return;

	long CurrentTime = SDL_GetTicks();

	long CurrentFrameTime = CurrentTime - _CurrentFrameStartTime;

	if (CurrentFrameTime < _DesiredFrameDuration)
	{
		SDL_Delay(_DesiredFrameDuration - CurrentFrameTime);
	}
}

void SDLTime::InitialiseTime()
{
	UpdateCurrentFrameStartTime();
	UpdateLastFrameStartTime();
}

void SDLTime::OnStartFrame()
{
	UpdateCurrentFrameStartTime();
	UpdateDeltaTime();
}

void SDLTime::OnEndFrame()
{
	ControlFrameRate();
	UpdateLastFrameStartTime();
}