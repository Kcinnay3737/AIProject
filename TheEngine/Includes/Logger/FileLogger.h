#pragma once

#include "Logger/ILogger.h"
#include <fstream>

namespace NPEngine
{
	//Logger provider for file
	class FileLogger final : public ILogger
	{
	private:
		std::ofstream _File;

	public:
		virtual ~FileLogger() = default;

		virtual void SetTextColor(EColor ForegourndColor = EColor::White, EColor BackgroundColor = EColor::Black) override { };

		virtual void LogMessage(const char* Message, ...) override;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;
	};
}