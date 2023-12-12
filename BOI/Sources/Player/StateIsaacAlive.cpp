#include "Player/StateIsaacAlive.h"
#include "Engine.h"
#include "Object/Actor/Projectil.h"
#include "Enemy/FirstEnemy.h"

StateIsaacAlive::StateIsaacAlive()
{
}

void StateIsaacAlive::OnEnter(Object* Owner)
{
	_ShootSoundId = Engine::GetAudio()->LoadSound(std::string("ShootSong.mp3"));

	_OwnerIsaac = static_cast<Isaac*>(Owner);

	_CurrShootDelay = _ShootDelay;

	_PhysicsComponent = _OwnerIsaac->GetComponentOfClass<PhysicsComponent>();
	{
		_PhysicsComponent->SetCollision(ECollisionType::Box);
		_PhysicsComponent->SetMaxVelocityMagnetude(200.0f);
	}

	_AtlasComponent = _OwnerIsaac->GetComponentOfClass<AtlasComponent>();
	if (_AtlasComponent)
	{
		_AtlasComponent->LoadTexture(std::string("HeadIsaac.png"));
		_AtlasComponent->SetTileSize(Vector2D<int>(32, 32));
		_AtlasComponent->SetTileIndex(0);
		_AtlasComponent->SetOffsetPosition(Vector2D<float>(0.0f, -15.0f));
		_AtlasComponent->SetDraw(true);
	}

	_AnimationComponent = _OwnerIsaac->GetComponentOfClass<AnimationComponent>();
	if (_AnimationComponent)
	{
		_AnimationComponent->LoadTexture(std::string("BodyIsaac.png"));
		_AnimationComponent->SetTileSize(Vector2D<int>(32, 32));
		_AnimationComponent->SetOffsetPosition(Vector2D<float>(2.0f, 25.0f));
		_AnimationComponent->SetOffsetSize(Vector2D<float>(0.0f, 0.0f));
		_AnimationComponent->SetCurrentAnimation(std::string("IdleDownAnimation"));
	}
}

void StateIsaacAlive::Execute(float DeltaTime, Object* Owner)
{
	UpdateShoot(DeltaTime);
	UpdateBodyAnimation();
	UpdateHeadAtlas();
}

void StateIsaacAlive::OnExit(Object* Owner)
{

}

void StateIsaacAlive::OnCollision(const std::vector<CollisionData>& CollisionsData)
{

}

void StateIsaacAlive::UpdateShoot(float DeltaTime)
{
	_ShootDirection = Vector2D<float>(0.0f, 0.0f);

	if (Engine::GetInput()->IsKeyDown(Key_UpArrow))
	{
		_ShootDirection.Y -= 1.0f;
	}
	if (Engine::GetInput()->IsKeyDown(Key_DownArrow))
	{
		_ShootDirection.Y += 1.0f;
	}
	if (Engine::GetInput()->IsKeyDown(Key_LeftArrow))
	{
		_ShootDirection.X -= 1.0f;
	}
	if (Engine::GetInput()->IsKeyDown(Key_RightArrow))
	{
		_ShootDirection.X += 1.0f;
	}

	if (_ShootDirection.X != 0.0f && _ShootDirection.Y != 0.0f)
	{
		_ShootDirection.X = 0;
	}

	_ShootDirection.Normalize();

	_CurrShootDelay += DeltaTime;

	if (_ShootDirection.Magnitude() > 0 && _CurrShootDelay >= _ShootDelay)
	{
		_CurrShootDelay = 0;
		Vector2D<float> ProjectilSize = Vector2D<float>(20.0f, 20.0f);
		Vector2D<float> ProjectilPosition = _OwnerIsaac->GetPosition() + ((_OwnerIsaac->GetSize() / 2) - (ProjectilSize / 2));

		Projectil* NewProjectil = Engine::GetWorld()->CreateActorOfClass<Projectil>(Projectil::GetNextProjectileName(), {
			{"DrawDepth", _OwnerIsaac->GetDrawDepth() + 1},
			{"Position", ProjectilPosition},
			{"Size", ProjectilSize},
			{"IgnoreActor", std::vector<std::type_index>{typeid(*_OwnerIsaac)}}
			});
		NewProjectil->SetMoveSpeed(1000.0f);
		NewProjectil->SetDirection(_ShootDirection);

		Engine::GetAudio()->PlaySound(_ShootSoundId);
	}
}

void StateIsaacAlive::UpdateBodyAnimation()
{
	Vector2D<float> CurrVeloDir = Vector2D<float>(0.0f, 0.0f);

	if (_PhysicsComponent)
	{
		CurrVeloDir = _PhysicsComponent->GetVelocity();
		CurrVeloDir.Normalize();
	}

	float ShootMagnetude = _ShootDirection.Magnitude();

	if (CurrVeloDir.Magnitude() > 0.0f && CurrVeloDir != _LastVeloDir)
	{
		if (CurrVeloDir.Y > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkDownAnimation"));
		}
		else if (CurrVeloDir.Y < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkUpAnimation"));
		}
		else if (CurrVeloDir.X > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkRightAnimation"));
		}
		else if (CurrVeloDir.X < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkLeftAnimation"));
		}
	}
	else if (_LastVeloDir.Magnitude() > 0.0f && CurrVeloDir.Magnitude() == 0.0f)
	{
		if (_LastVeloDir.Y > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleDownAnimation"));
		}
		else if (_LastVeloDir.Y < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleUpAnimation"));
		}
		else if (_LastVeloDir.X > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleRightAnimation"));
		}
		else if (_LastVeloDir.X < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleLeftAnimation"));
		}
	}

	_LastVeloDir = CurrVeloDir;
}

void StateIsaacAlive::UpdateHeadAtlas()
{
	if (_ShootDirection.Magnitude() > 0)
	{
		if (_ShootDirection.Y > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(0);
		}
		else if (_ShootDirection.Y < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(4);
		}
		else if (_ShootDirection.X > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(2);
		}
		else if (_ShootDirection.X < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(true, false));
			_AtlasComponent->SetTileIndex(2);
		}
	}
	else if (_LastVeloDir.Magnitude() > 0)
	{
		if (_LastVeloDir.Y > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(0);
		}
		else if (_LastVeloDir.Y < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(4);
		}
		else if (_LastVeloDir.X > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(2);
		}
		else if (_LastVeloDir.X < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(true, false));
			_AtlasComponent->SetTileIndex(2);
		}
	}
}
