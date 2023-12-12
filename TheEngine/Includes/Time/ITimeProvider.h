#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	//Interface for time provider friend with engine class
	class ITimeProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~ITimeProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) = 0;
		virtual void Shutdown(const Param& Params) = 0;

		//Initialise time value
		virtual void InitialiseTime() = 0;
		//Call on start of the frame
		virtual void OnStartFrame() = 0;
		//Call on end of the frame
		virtual void OnEndFrame() = 0;
	};
}