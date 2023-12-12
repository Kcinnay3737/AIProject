#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	//Base interface for a service provider
	class IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~IServiceProvider() = default;

	private:
		//Call for initialize the service
		virtual bool Initialize(const Param& Params = Param{}) = 0;
		//Call for shutdown the service
		virtual void Shutdown(const Param& Params = Param{}) = 0;
	};
}