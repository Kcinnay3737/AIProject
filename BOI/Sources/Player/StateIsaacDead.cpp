#include "Player/StateIsaacDead.h"
#include "Engine.h"

StateIsaacDead::StateIsaacDead()
{
}

void StateIsaacDead::OnEnter(Object* Owner)
{
	_PlayerLossSongId = Engine::GetAudio()->LoadSound(std::string("LossSong.mp3"));
	Engine::GetAudio()->PlaySound(_PlayerLossSongId);

	Engine::GetWorld()->RemoveInPersistenteData(std::string("PlayerHP"));

	_OwnerIsaac = static_cast<Isaac*>(Owner);

	_PhysicsComponent = _OwnerIsaac->GetComponentOfClass<PhysicsComponent>();
	{
		_PhysicsComponent->SetCollision(ECollisionType::None);
		_PhysicsComponent->SetMaxVelocityMagnetude(0.0f);
	}

	_AtlasComponent = _OwnerIsaac->GetComponentOfClass<AtlasComponent>();
	if (_AtlasComponent)
	{
		_AtlasComponent->LoadTexture(std::string("HeadIsaac.png"));
		_AtlasComponent->SetTileSize(Vector2D<int>(32, 32));
		_AtlasComponent->SetTileIndex(0);
		_AtlasComponent->SetOffsetPosition(Vector2D<float>(0.0f, -15.0f));
		_AtlasComponent->SetDraw(false);
	}

	_AnimationComponent = _OwnerIsaac->GetComponentOfClass<AnimationComponent>();
	if (_AnimationComponent)
	{
		_AnimationComponent->LoadTexture(std::string("IsaacDead.png"));
		_AnimationComponent->SetTileSize(Vector2D<int>(48, 48));
		_AnimationComponent->SetOffsetPosition(Vector2D<float>(0.0f, -20.0f));
		_AnimationComponent->SetOffsetSize(Vector2D<float>(50.0f, 50.0f));
		_AnimationComponent->SetCurrentAnimation(std::string("DeadAnimation"));
	}
}

void StateIsaacDead::Execute(float DeltaTime, Object* Owner)
{
	_CurrentDelayRestart += DeltaTime;
	if (_CurrentDelayRestart >= _DelayRestart)
	{
		Engine::GetWorld()->LoadScene("SceneMenu");
	}
}

void StateIsaacDead::OnExit(Object* Owner)
{
}

void StateIsaacDead::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
}
