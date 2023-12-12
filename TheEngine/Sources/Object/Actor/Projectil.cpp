#include "Object/Actor/Projectil.h"
#include "Object/Component/SpriteComponent.h"
#include "Object/Component/PhysicsComponent.h"
#include <typeindex>
#include <typeinfo>
#include "Engine.h"

using namespace NPEngine;

size_t Projectil::_ProjectilCount = 0;

Projectil::Projectil(const std::string& Name) : Actor(Name)
{

}

Actor* Projectil::Clone(const std::string& Name, const Param& Params)
{
	Projectil* NewProjectil = new Projectil(Name);
	return NewProjectil;
}

bool Projectil::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	_PhysicsComponent = CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"), Params);
	CreateComponentOfClass<SpriteComponent>(std::string("SpriteComponent"), Params);

	auto IT = Params.find("Direction");
	if (IT != Params.end())
	{
		_Direction = std::any_cast<Vector2D<float>>(IT->second);
		_Direction.Normalize();
	}

	IT = Params.find("MoveSpeed");
	if (IT != Params.end())
	{
		_MoveSpeed = std::any_cast<float>(IT->second);
	}

	return true;
}

void Projectil::BeginPlay()
{
	Actor::BeginPlay();

	SpriteComponent* CurrSpriteComponent = GetComponentOfClass<SpriteComponent>();
	if (CurrSpriteComponent)
	{
		CurrSpriteComponent->LoadTexture(std::string("Projectil.png"));
	}

	if (_PhysicsComponent)
	{
		_PhysicsComponent->OnCollision.AddFunction(this, &Projectil::OnHit);

		_PhysicsComponent->SetMaxVelocityMagnetude(_MoveSpeed);

		_PhysicsComponent->SetCollision(ECollisionType::Box);
		//_PhysicsComponent->SetDrawCollision(true);
		_PhysicsComponent->SetIsPhysicsVolume(false);
	}
}

void Projectil::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	if (_PhysicsComponent)
	{
		_PhysicsComponent->SetVelocity(_Direction * _MoveSpeed);
	}
}

void Projectil::OnHit(const std::vector<CollisionData>& CollisionsData)
{
	for (const CollisionData& CurrCollisionData : CollisionsData)
	{
		CurrCollisionData.OtherActor->TakeHit(_Damage);
	}

	Engine::GetWorld()->DeleteActorByName(GetName());
}

void Projectil::SetMoveSpeed(const float& MoveSpeed)
{
	_MoveSpeed = MoveSpeed;
	if (_PhysicsComponent)
	{
		_PhysicsComponent->SetMaxVelocityMagnetude(_MoveSpeed);
	}
}

std::string Projectil::GetNextProjectileName()
{
	std::string Name = "Projectile" + std::to_string(Projectil::_ProjectilCount);
	Projectil::_ProjectilCount++;
	return Name;
}
