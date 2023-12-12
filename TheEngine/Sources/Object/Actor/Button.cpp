#include "Object/Actor/Button.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/PhysicsComponent.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Engine.h"

using namespace NPEngine;

Button::Button(const std::string& Name) : Actor(Name)
{
}

bool Button::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	_AtlasComponent = CreateComponentOfClass<AtlasComponent>(std::string("AtlasComponent"), Params);
	_PhysicsComponent = CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"), Params);

	return true;
}

void Button::Destroy(const Param& Params)
{
	Actor::Destroy(Params);

	Engine::GetInput()->OnButtonPressed[EButtonKeys::Mouse_Left].RemoveFunction(this, &Button::OnLeftMousePressed);
	Engine::GetInput()->OnButtonReleased[EButtonKeys::Mouse_Left].RemoveFunction(this, &Button::OnLeftMouseReleased);
}

void Button::BeginPlay()
{
	Actor::BeginPlay();

	Engine::GetInput()->OnButtonPressed[EButtonKeys::Mouse_Left].AddFunction(this, &Button::OnLeftMousePressed);
	Engine::GetInput()->OnButtonReleased[EButtonKeys::Mouse_Left].AddFunction(this, &Button::OnLeftMouseReleased);
}

Actor* Button::Clone(const std::string& Name, const Param& Params)
{
	Button* NewButton = new Button(Name);
	return NewButton;
}

void Button::OnLeftMousePressed(const DataButton& CurrDataKey)
{
	BoxCollision ButtonBoxCollision = BoxCollision(this, nullptr);
	PointCollision MousePointCollision = PointCollision(nullptr, nullptr);

	Vector2D<int> MousePosititionInt = Engine::GetInput()->GetMousePosition();
	Vector2D<float> MousePositionFloat = Vector2D<float>(static_cast<float>(MousePosititionInt.X), static_cast<float>(MousePosititionInt.Y));

	MousePointCollision.SetPositionOffset(MousePositionFloat);

	CollisionData CurrCollisionData = ButtonBoxCollision.CheckCollisionWithPoint(MousePointCollision);

	if (CurrCollisionData.bCollision)
	{
		_bButtonIsPressed = true;
		OnPressedButton();
	}
}

void Button::OnLeftMouseReleased(const DataButton& CurrDataKey)
{
	if (!_bButtonIsPressed) return;
	_bButtonIsPressed = false;

	BoxCollision ButtonBoxCollision = BoxCollision(this, nullptr);
	PointCollision MousePointCollision = PointCollision(nullptr, nullptr);

	Vector2D<int> MousePosititionInt = Engine::GetInput()->GetMousePosition();
	Vector2D<float> MousePositionFloat = Vector2D<float>(static_cast<float>(MousePosititionInt.X), static_cast<float>(MousePosititionInt.Y));

	MousePointCollision.SetPositionOffset(MousePositionFloat);

	CollisionData CurrCollisionData = ButtonBoxCollision.CheckCollisionWithPoint(MousePointCollision);

	if (CurrCollisionData.bCollision)
	{
		OnClicked.Broadcast();
	}

	OnReleasedButton();
}

void Button::OnPressedButton()
{
	_AtlasComponent->SetTileIndex(1);
}

void Button::OnReleasedButton()
{
	_AtlasComponent->SetTileIndex(0);
}
