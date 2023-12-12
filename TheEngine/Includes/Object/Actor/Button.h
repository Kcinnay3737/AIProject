#pragma once

#include "Object/Actor/Actor.h"
#include "Input/IInput.h"

namespace NPEngine
{
	class AtlasComponent;
	class PhysicsComponent;

	class Button : public Actor
	{
	public:
		//Call when the button is cliched
		Delegate<void> OnClicked;

	protected:
		AtlasComponent* _AtlasComponent = nullptr;
		PhysicsComponent* _PhysicsComponent = nullptr;

		bool _bButtonIsPressed = false;

	public:
		Button(const std::string& Name);
		virtual ~Button() = default;

		virtual Actor* Clone(const std::string& Name, const Param& Params = Param{}) override;

	protected:
		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;
		virtual void BeginPlay() override;

	private:
		//Call when the left mouse is pressed
		void OnLeftMousePressed(const DataButton& CurrDataKey);
		//Call when the left mouse is re;eaded
		void OnLeftMouseReleased(const DataButton& CurrDataKey);

		//Call when the button is pressed
		virtual void OnPressedButton();
		//Call when the button is released
		virtual void OnReleasedButton();

	public:
		
	};
}