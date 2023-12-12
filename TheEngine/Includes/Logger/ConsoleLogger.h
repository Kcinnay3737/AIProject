#pragma once

#include "Logger/ILogger.h"
#include <concrt.h>

namespace NPEngine
{
	//Logger provider for consol
	class ConsoleLogger final : public ILogger
	{
	private:
		HANDLE _HConsole = HANDLE();

	public:
		virtual ~ConsoleLogger() = default;

		virtual void SetTextColor(EColor ForegourndColor, EColor BackgroundColor) override;

		virtual void LogMessage(const char* Message, ...) override;

		//Return the good color with corresponding to enum
		uint8_t MapToForegroundColor(EColor Color);
		//Return the good color with corresponding to enum
		uint8_t MapToBackgroundColor(EColor Color);

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;

	};
}