#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class IInputProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~IInputProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) = 0;
		virtual void Shutdown(const Param& Params) = 0;

		virtual void ProcessInput() = 0;
		virtual void UpdateInputListener(float DeltaTime) = 0;
	};
}