#include "Object/Component/PhysicsComponent.h"
#include "Engine.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/GridCollision.h"

using namespace NPEngine;

PhysicsComponent::PhysicsComponent(const std::string& Name) : Component(Name)
{

}

bool PhysicsComponent::Initialise(const Param& Params)
{
	bool Success = Component::Initialise(Params);

	auto IT = Params.find("IgnoreActor");
	if (IT != Params.end())
	{
		const std::vector<std::type_index>& IgnoreActorClass = std::any_cast<const std::vector<std::type_index>&>(IT->second);
		for (const std::type_index& TypeIndex : IgnoreActorClass)
		{
			AddIgnoreActorClass(TypeIndex);
		}
	}

	IPhysics* Physics = Engine::GetPhysics();
	if (Physics)
	{
		IPhysicsProvider* PhysicsProvider = static_cast<IPhysicsProvider*>(Physics);
		if (PhysicsProvider)
		{
			TransformComponent* CurrTransformComponent = GetOwner()->GetComponentOfClass<TransformComponent>();
			if (CurrTransformComponent)
			{
				PhysicsProvider->AddPhysicsActor(GetOwner()->GetName(), this);
			}
			else
			{
				Success = false;
			}
		}
		else
		{
			Success = false;
		}
	}
	else
	{
		Success = false;
	}

	return Success;
}

void PhysicsComponent::Destroy(const Param& Params)
{
	Component::Destroy(Params);

	IPhysics* Physics = Engine::GetPhysics();
	if (Physics)
	{
		IPhysicsProvider* PhysicsProvider = static_cast<IPhysicsProvider*>(Physics);
		if (PhysicsProvider)
		{
			PhysicsProvider->RemovePhysicsActor(GetOwner()->GetName());
		}
	}

	if (_Collision != nullptr)
	{
		delete _Collision;
	}
}

void PhysicsComponent::Draw()
{
	if (_Collision && _bDrawCollision)
	{
		_Collision->DrawCollision();
	}
}

void PhysicsComponent::CorrectMagnetude()
{
	if (GetVelocity().Magnitude() > _MaxVelocityMagnetude)
	{
		_MovementData.Velocity.Normalize();
		_MovementData.Velocity = _MovementData.Velocity * _MaxVelocityMagnetude;
	}
}

Vector2D<float> PhysicsComponent::GetVelocity()
{
	return _MovementData.Velocity;
}

void PhysicsComponent::SetVelocity(const Vector2D<float>& NewVelocity)
{
	_MovementData.Velocity = NewVelocity;
	CorrectMagnetude();
}

void PhysicsComponent::AddVelocity(const Vector2D<float>& VelociyToAdd)
{
	_MovementData.Velocity += VelociyToAdd;
	CorrectMagnetude();
}

void PhysicsComponent::ApplyVelocity(float DeltaTime)
{
	if (!_bIsMovable) return;

	if (DeltaTime > 0.5f)
	{
		DeltaTime = 0.5f;
	}

	TransformComponent* CurrTransformComponent = GetOwner()->GetComponentOfClass<TransformComponent>();
	if (CurrTransformComponent)
	{
		CurrTransformComponent->AddPositionOffset(GetVelocity() * DeltaTime);
	}

	SetVelocity(Vector2D<float>(0.0f, 0.0f));
}

std::vector<CollisionData> PhysicsComponent::CheckCollision()
{
	std::vector<CollisionData> CollisionsData = Engine::GetPhysics()->CheckCollisionWith(GetCollision());

	if (!CollisionsData.empty())
	{
		OnCollision.Broadcast(CollisionsData);
	}
	
	return CollisionsData;
}

void PhysicsComponent::CorrectMovement(const std::vector<CollisionData>& AllCollisionData)
{
	if (!_bCorrectMovement) return;

	Vector2D<float> CurrentCorrectionMovement = Vector2D<float>(0.0f, 0.0f);

	for (const CollisionData& CurrCollisionData : AllCollisionData)
	{
		if (std::abs(CurrCollisionData.MovementCorrection.X) > std::abs(CurrentCorrectionMovement.X))
		{
			CurrentCorrectionMovement.X = CurrCollisionData.MovementCorrection.X;
		}

		if (std::abs(CurrCollisionData.MovementCorrection.Y) > std::abs(CurrentCorrectionMovement.Y))
		{
			CurrentCorrectionMovement.Y = CurrCollisionData.MovementCorrection.Y;
		}
	}

	TransformComponent* CurrTransformComponent = GetOwner()->GetComponentOfClass<TransformComponent>();
	if (CurrTransformComponent)
	{
		CurrTransformComponent->AddPositionOffset(CurrentCorrectionMovement);
	}
}

void PhysicsComponent::SetCollision(const ECollisionType& CollisionType)
{
	if (_Collision != nullptr)
	{
		delete _Collision;
	}

	_CollisionType = CollisionType;

	switch (_CollisionType)
	{
	case ECollisionType::None:
		_Collision = nullptr;
		break;
	case ECollisionType::Point:
		_Collision = new PointCollision(GetOwner(), this);
		break;
	case ECollisionType::Line:
		_Collision = new LineCollision(GetOwner());
		break;
	case ECollisionType::Box:
		_Collision = new BoxCollision(GetOwner(), this);
		break;
	case ECollisionType::Sphere:
		_Collision = new SphereCollision(GetOwner());
		break;
	case ECollisionType::Grid:
		_Collision = new GridCollision(GetOwner(), this);
		break;
	default:
		_Collision = nullptr;
		break;
	}
}

ICollision* PhysicsComponent::GetCollision() const
{
	return _Collision;
}

void PhysicsComponent::AddIgnoreActorClass(std::type_index TypeIndex)
{
	_IgnoreActorClass[TypeIndex] = true;
}

void PhysicsComponent::RemoveIgnoreActorClass(std::type_index TypeIndex)
{
	_IgnoreActorClass.erase(TypeIndex);
}

bool PhysicsComponent::GetIgnoreActorClass(Actor* CheckActor)
{
	if (!CheckActor) return false;

	std::type_index TypeIndex(typeid(*CheckActor));

	auto IT = _IgnoreActorClass.find(TypeIndex);
	if (IT == _IgnoreActorClass.end()) return false;

	return true;
}
