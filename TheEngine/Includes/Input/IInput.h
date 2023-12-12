#pragma once

#include "Input/IInputProvider.h"
#include "Utility/Delegate.h"
#include "Input/EnumInput.h"

namespace NPEngine
{
	//Struct for current key state
	struct DataKey
	{
	public:
		EKeyboardKeys Key = EKeyboardKeys::Key_None;
		float TimePressed = 0.0f;
		bool bIsPressed = false;
	};

	//Struct for current button state
	struct DataButton
	{
	public:
		EButtonKeys Key = EButtonKeys::Mouse_None;
		float TimePressed = 0.0f;
		bool bIsPressed = false;
	};

	//Interface for a input provider
	class IInput : public IInputProvider
	{
	public:
		//Key delegate
		std::map<EKeyboardKeys, Delegate<void, const DataKey&>> OnKeyPressed;
		std::map<EKeyboardKeys, Delegate<void, const DataKey&>> OnKeyMaintained;
		std::map<EKeyboardKeys, Delegate<void, const DataKey&>> OnKeyReleased;

		//Button delegate
		std::map<EButtonKeys, Delegate<void, const DataButton&>> OnButtonPressed;
		std::map<EButtonKeys, Delegate<void, const DataButton&>> OnButtonMaintained;
		std::map<EButtonKeys, Delegate<void, const DataButton&>> OnButtonReleased;

	protected:
		//Key state dict
		std::map<EKeyboardKeys, DataKey> _DataKey;
		//Button state dict
		std::map<EButtonKeys, DataButton> _DataButton;

	public:
		virtual ~IInput() = default;

		//Return true if the button is down
		virtual bool IsKeyDown(EKeyboardKeys Key) = 0;
		//Return true if the button is down
		virtual bool IsButtonDown(EButtonKeys Key) = 0;

		//Return the current mouse position
		virtual void GetMousePosition(int* X, int* Y) = 0;
		//Return the current mouse position
		virtual Vector2D<int> GetMousePosition() = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		//Process the current input
		virtual void ProcessInput() override = 0;
		//Update current input listener state and call it
		virtual void UpdateInputListener(float DeltaTime) override = 0;
	};
}