#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	//Logger provider interface friend with engine
	class ILoggerProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~ILoggerProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) = 0;
		virtual void Shutdown(const Param& Params) = 0;
	};
}