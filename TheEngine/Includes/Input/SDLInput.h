#pragma once

#include "Input/IInput.h"
#include "SDL_scancode.h"

namespace NPEngine
{
	//Input provider with SDL
	class SDLInput final : public IInput
	{
	public:

	private:
		const unsigned char* _KeyStates = nullptr;

	public:
		virtual ~SDLInput() = default;

		virtual bool IsKeyDown(EKeyboardKeys Key) override;
		virtual bool IsButtonDown(EButtonKeys Key) override;

		virtual void GetMousePosition(int* x, int* y) override;
		virtual Vector2D<int> GetMousePosition() override;

		SDL_Scancode MapToSDLScancode(EKeyboardKeys Key);
		Uint8 MapToSDLButtonCode(EButtonKeys button);

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;

		virtual void ProcessInput() override;
		virtual void UpdateInputListener(float DeltaTime) override;
	};
}