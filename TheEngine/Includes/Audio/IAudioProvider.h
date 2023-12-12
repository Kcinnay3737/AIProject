#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	//Interface audio provider friend with engine class
	class IAudioProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~IAudioProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;
	};
}