#pragma once

#include "Logger/ILoggerProvider.h"
#include "Graphics/Color.h"

namespace NPEngine
{
	//Interface for a logger provider
	class ILogger : public ILoggerProvider
	{
	public:
		virtual ~ILogger() = default;

		//Set the current text color
		virtual void SetTextColor(EColor ForegourndColor = EColor::White, EColor BackgroundColor = EColor::Black) = 0;
		
		//Log the message
		virtual void LogMessage(const char* Message, ...) = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;
	};
}