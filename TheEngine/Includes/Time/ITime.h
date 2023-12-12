#pragma once

#include "Time/ITimeProvider.h"

namespace NPEngine
{
	//Interface for time provider
	class ITime : public ITimeProvider
	{
	public:
		virtual ~ITime() = default;
		
		//Return the current delta time
		virtual float GetDeltaTime() = 0;
		//Set desired frame per second
		virtual void SetFramePerSecond(int FramePerSecond) = 0;

	protected:
		long _LastFrameStartTime = 0;
		long _CurrentFrameStartTime = 0;
		float _DeltaTime = 0;
		int _FramesPerSecond = 60;
		long _DesiredFrameDuration = 1000 / 60;

	private:
		//<= 0 for unlimited frame
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		//Update delta time with the current time and the last time
		virtual void UpdateDeltaTime() = 0;
		//Set the last frame value whit the last current value
		virtual void UpdateLastFrameStartTime() = 0;
		//Set the current frame value with the current time
		virtual void UpdateCurrentFrameStartTime() = 0;
		//Wait for keep the frame rate
		virtual void ControlFrameRate() = 0;

		//Initialise time value
		virtual void InitialiseTime() override = 0;
		//Call on start of the frame
		virtual void OnStartFrame() override = 0;
		//Call on end of the frame
		virtual void OnEndFrame() override = 0;

	};
}