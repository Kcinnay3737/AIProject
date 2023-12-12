#include "Object/Component/ControllerComponent.h"
#include "Engine.h"
#include "Input/EnumInput.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Actor/Actor.h"

using namespace NPEngine;

ControllerComponent::ControllerComponent(const std::string& Name) : Component(Name)
{
}

bool ControllerComponent::Initialise(const Param& Params)
{
    Component::Initialise(Params);

    Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_W].AddFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);
	Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_A].AddFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);
	Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_S].AddFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);
	Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_D].AddFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);

    return true;
}

void ControllerComponent::Destroy(const Param& Params)
{
    Component::Destroy(Params);

	Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_W].RemoveFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);
	Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_A].RemoveFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);
	Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_S].RemoveFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);
	Engine::GetInput()->OnKeyMaintained[EKeyboardKeys::Key_D].RemoveFunction<ControllerComponent>(this, &ControllerComponent::OnMoveKeyPressed);
}

void ControllerComponent::OnMoveKeyPressed(const DataKey& CurrDataKey)
{
	PhysicsComponent* CurrPhysicsComponent = GetOwner()->GetComponentOfClass<PhysicsComponent>();
	if (!CurrPhysicsComponent) return;

	Vector2D<float> VelocityToAdd = Vector2D<float>(0.0f, 0.0f);

	switch (CurrDataKey.Key)
	{
	case EKeyboardKeys::Key_W:
		VelocityToAdd.Y += -_MoveSpeed;
		break;
	case EKeyboardKeys::Key_A:
		VelocityToAdd.X += -_MoveSpeed;
		break;
	case EKeyboardKeys::Key_S:
		VelocityToAdd.Y += _MoveSpeed;
		break;
	case EKeyboardKeys::Key_D:
		VelocityToAdd.X += _MoveSpeed;
		break;
	}

	CurrPhysicsComponent->AddVelocity(VelocityToAdd);
}