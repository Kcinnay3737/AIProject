#include "Player/StateIsaacWin.h"
#include "Engine.h"

StateIsaacWin::StateIsaacWin()
{
}

void StateIsaacWin::OnEnter(Object* Owner)
{
	_PlayerWinSongId = Engine::GetAudio()->LoadSound(std::string("WinSong.mp3"));
	Engine::GetAudio()->PlaySound(_PlayerWinSongId);

	Engine::GetWorld()->RemoveInPersistenteData(std::string("PlayerHP"));

	_OwnerIsaac = static_cast<Isaac*>(Owner);

	_PhysicsComponent = _OwnerIsaac->GetComponentOfClass<PhysicsComponent>();
	{
		_PhysicsComponent->SetMaxVelocityMagnetude(0.0f);
	}

	_AtlasComponent = _OwnerIsaac->GetComponentOfClass<AtlasComponent>();
	if (_AtlasComponent)
	{
		_AtlasComponent->SetDraw(false);
	}

	_AnimationComponent = _OwnerIsaac->GetComponentOfClass<AnimationComponent>();
	if (_AnimationComponent)
	{
		_AnimationComponent->LoadTexture(std::string("IsaacWin.png"));
		_AnimationComponent->SetTileSize(Vector2D<int>(48, 45));
		_AnimationComponent->SetOffsetPosition(Vector2D<float>(0.0f, -20.0f));
		_AnimationComponent->SetOffsetSize(Vector2D<float>(50.0f, 50.0f));
		_AnimationComponent->SetCurrentAnimation(std::string("WinAnimation"));
	}
}

void StateIsaacWin::Execute(float DeltaTime, Object* Owner)
{
	_CurrentDelayRestart += DeltaTime;
	if (_CurrentDelayRestart >= _DelayRestart)
	{
		Engine::GetWorld()->LoadScene("SceneMenu");
	}
}

void StateIsaacWin::OnExit(Object* Owner)
{
}

void StateIsaacWin::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
}
