#pragma once

#include "Object/Component/Component.h"
#include "Input/IInput.h"

namespace NPEngine
{
	//Compoennt for control a actor with WASD
	class ControllerComponent : public Component
	{
	private:
		float _MoveSpeed = 200.0f;

	public:
		ControllerComponent(const std::string& Name);
		virtual ~ControllerComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		//Call when WASD is pressed
		void OnMoveKeyPressed(const DataKey& CurrDataKey);

	public:
		//Set the current move speed
		void SetMoveSpeed(float MoveSpeed) { _MoveSpeed = MoveSpeed; }
		//Get the current move speed
		float GetMoveSpeed() const { return _MoveSpeed; }
	};
}