#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	//World interface friend with engine class
	class IWorldProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~IWorldProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		//Call at start of frame
		virtual void StartFrame() = 0;

		//Call each frame for update all actor
		virtual void Update(float DeltaTime) = 0;
		//Call each frame after update
		virtual void PostUpdate() = 0;

		//Call each frame for render all actor
		virtual void Render() = 0;
		//Call after render
		virtual void PostRender() = 0;

		//Call at end of frame
		virtual void EndFrame() = 0;
	};
}