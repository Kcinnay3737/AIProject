#include "Enemy/BossEnemy.h"
#include "Engine.h"
#include "Player/Isaac.h"
#include <cmath>
#include "Physics/Collision/BoxCollision.h"
#include "Enemy/FlyEnemy.h"

int BossEnemy::CurrentNumberOfFlyEnemySpawn = 0;

BossEnemy::BossEnemy(const std::string& Name) : AI(Name)
{
}

bool BossEnemy::Initialise(const Param& Params)
{
    bool bSucces = AI::Initialise(Params);

    _PhysicsComponent = CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"));
    _AnimationComponent = CreateComponentOfClass<AnimationComponent>(std::string("AnimationComponent"));

    return bSucces;
}

void BossEnemy::Destroy(const Param& Params)
{
    AI::Destroy(Params);
}

void BossEnemy::BeginPlay()
{
    AI::BeginPlay();

	_EnemyHitSongId = Engine::GetAudio()->LoadSound("EnemyHitSong.mp3");
	_SpawnFlySongId = Engine::GetAudio()->LoadSound("SpawnFlySong.mp3");

	Vector2D<int> ScreenSize = Engine::GetGraphics()->GetScreenSize();
	Vector2D<float> FScreenSize = Vector2D<float>(static_cast<float>(ScreenSize.X), static_cast<float>(ScreenSize.Y));

	Vector2D<float> Size = GetSize();

	Vector2D<float> Position = Vector2D<float>((FScreenSize.X / 2) - (Size.X / 2), 64.0f);
	SetPosition(Position);

	_Player = Engine::GetWorld()->GetActorOfClass<Isaac>();

	if (_PhysicsComponent)
	{
		_PhysicsComponent->SetCollision(ECollisionType::Box);
		_PhysicsComponent->SetMaxVelocityMagnetude(_BossMoveSpeed);
		_PhysicsComponent->SetIsPhysicsVolume(false);

		_PhysicsComponent->OnCollision.AddFunction(this, &BossEnemy::OnCollision);

		BoxCollision* CurrBoxCollision = static_cast<BoxCollision*>(_PhysicsComponent->GetCollision());
		CurrBoxCollision->SetSizeOffset(Vector2D<float>(-30.0f, -50.0f));
		CurrBoxCollision->SetPositionOffset(Vector2D<float>(15.0f, 40.0f));

		_PhysicsComponent->AddIgnoreActorClass(typeid(FlyEnemy));
	}

	if (_AnimationComponent)
	{
		_AnimationComponent->LoadTexture(std::string("bossEnemy.png"));
		_AnimationComponent->SetTileSize(Vector2D<int>(80, 96));

		AnimationData IdleAnimation = AnimationData();
		IdleAnimation.FrameInterval = 0.0f;
		IdleAnimation.StartIndex = 0;
		IdleAnimation.EndIndex = 0;
		IdleAnimation.bLoop = false;
		IdleAnimation.AddFrameToCallObserver(0);
		IdleAnimation.AnimationObserver.AddFunction(this, &BossEnemy::AnimationListener);
		_AnimationComponent->AddAnimation(std::string("IdleAnimation"), IdleAnimation);

		AnimationData StartJumpAnimation = AnimationData();
		StartJumpAnimation.FrameInterval = 0.2f;
		StartJumpAnimation.StartIndex = 1;
		StartJumpAnimation.EndIndex = 5;
		StartJumpAnimation.SwitchAnimationData.bSwitchAnimation = true;
		StartJumpAnimation.SwitchAnimationData.SwitchIndex = 5;
		StartJumpAnimation.SwitchAnimationData.SwitchAnimationName = std::string("JumpLoopAnimation");
		_AnimationComponent->AddAnimation(std::string("StartJumpAnimation"), StartJumpAnimation);

		AnimationData JumpLoopAnimation = AnimationData();
		JumpLoopAnimation.FrameInterval = 0.2f;
		JumpLoopAnimation.StartIndex = 2;
		JumpLoopAnimation.EndIndex = 5;
		_AnimationComponent->AddAnimation(std::string("JumpLoopAnimation"), JumpLoopAnimation);

		AnimationData LandAnimation = AnimationData();
		LandAnimation.FrameInterval = 0.2f;
		LandAnimation.StartIndex = 7;
		LandAnimation.EndIndex = 8;
		LandAnimation.SwitchAnimationData.bSwitchAnimation = true;
		LandAnimation.SwitchAnimationData.SwitchIndex = 8;
		LandAnimation.SwitchAnimationData.SwitchAnimationName = std::string("IdleAnimation");
		_AnimationComponent->AddAnimation(std::string("LandAnimation"), LandAnimation);

		AnimationData VomitAnimation = AnimationData();
		VomitAnimation.FrameInterval = 0.2f;
		VomitAnimation.StartIndex = 8;
		VomitAnimation.EndIndex = 9;
		VomitAnimation.SwitchAnimationData.bSwitchAnimation = true;
		VomitAnimation.SwitchAnimationData.SwitchIndex = 9;
		VomitAnimation.SwitchAnimationData.SwitchAnimationName = std::string("IdleAnimation");
		VomitAnimation.AddFrameToCallObserver(9);
		VomitAnimation.AnimationObserver.AddFunction(this, &BossEnemy::AnimationListener);
		_AnimationComponent->AddAnimation(std::string("VomitAnimation"), VomitAnimation);

		_AnimationComponent->SetCurrentAnimation(std::string("IdleAnimation"));
	}

	_IAQLearning->Initialize(2, 3, 0.1, 0.4, 1.0, 0.999, 0.1f);
}

void BossEnemy::Update(float DeltaTime)
{
    AI::Update(DeltaTime);

	if (_CurrentBossState == Jumping)
	{
		UpdateJump(DeltaTime);
	}

	if (!_bCanAttack)
	{
		_CurrentAttackDelay += DeltaTime;
		if (_CurrentAttackDelay >= _AttackDelay)
		{
			_CurrentAttackDelay = 0.0f;
			_bCanAttack = true;
		}
	}
}

Actor* BossEnemy::Clone(const std::string& Name, const Param& Params)
{
    BossEnemy* NewBossEnemy = new BossEnemy(Name);
	return NewBossEnemy;
}

void BossEnemy::TakeHit(float Damage)
{
	if (_CurrentHealth <= 0) return;
	_CurrentHealth -= static_cast<int>(Damage);
	Engine::GetAudio()->PlaySound(_EnemyHitSongId);
	if (_CurrentHealth <= 0)
	{
		_Player->SetCurrentState(std::string("Win"));
		Engine::GetWorld()->DeleteActorByName(GetName());

		std::vector<FlyEnemy*> FlyEnemies = Engine::GetWorld()->GetAllActorOfClass<FlyEnemy>();
		for (const FlyEnemy* CurrFlyEnemy : FlyEnemies)
		{
			Engine::GetWorld()->DeleteActorByName(CurrFlyEnemy->GetName());
		}
	}
}

int BossEnemy::GetCurrentState()
{
	if (_CurrentBossState == Thinking)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void BossEnemy::PerformAction(int Action, float DeltaTime)
{
	switch (Action)
	{
	case 0:
		if (_CurrentReward == Jumping)
		{
			_CurrentReward -= 10.0;
		}
		break;
	case 1:
		if (_CurrentBossState == Thinking)
		{
			_CurrentReward += 10.0;
			Jump(_Player->GetPosition() + _Player->GetSize() / 2);
		}
		else if (_CurrentBossState == Jumping)
		{
			_CurrentReward += 20.0;
			UpdateJump(DeltaTime);
		}
		else
		{
			_CurrentReward -= 10.0;
		}
		break;
	case 2:
		if (_CurrentBossState == Thinking)
		{
			_CurrentReward += 10.0;
			Vomit();
		}
		else if(_CurrentBossState == Vomiting)
		{
			_CurrentReward += 20.0;
		}
		else
		{
			_CurrentReward -= 10.0;
		}
		break;
	}
}

int BossEnemy::GetNewState()
{
    return GetCurrentState();
}

double BossEnemy::GetReward()
{
	double TempReward = _CurrentReward;
	_CurrentReward = 0.0;
	return TempReward;
}

void BossEnemy::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
	if (!_bCanAttack) return;
	for (const CollisionData& CurrCollisionData : CollisionsData)
	{
		Isaac* CurrIsaac = dynamic_cast<Isaac*>(CurrCollisionData.OtherActor);
		if (CurrIsaac)
		{
			CurrIsaac->TakeHit(_BossDamage);
			_bCanAttack = false;
		}
	}
}

void BossEnemy::Jump(const Vector2D<float> JumpLocation)
{
	if (_CurrentBossState != Thinking) return;
	_CurrentBossState = Jumping;

	_JumpDesiredPosition = JumpLocation;
	_AnimationComponent->SetCurrentAnimation(std::string("StartJumpAnimation"));
}

void BossEnemy::Land()
{
	_bIsCurrentlyLanding = true;
	_AnimationComponent->SetCurrentAnimation(std::string("LandAnimation"));
}

void BossEnemy::Vomit()
{
	if (_CurrentBossState != Thinking) return;
	_CurrentBossState = Vomiting;

	_AnimationComponent->SetCurrentAnimation(std::string("VomitAnimation"));
}

void BossEnemy::UpdateJump(float DeltaTime)
{
	if (_bIsCurrentlyLanding) return;

	Vector2D<float> CurrentMidPosition = GetPosition() + GetSize() / 2;

	Vector2D<float> JumpDir = _JumpDesiredPosition - CurrentMidPosition;
	float JumpDist = JumpDir.Magnitude();
	JumpDir.Normalize();

	if (JumpDist <= (_BossMoveSpeed / 2) * DeltaTime)
	{
		Land();
		return;
	}

	_PhysicsComponent->AddVelocity(JumpDir * _BossMoveSpeed);
}

void BossEnemy::SpawnFly()
{
	Engine::GetAudio()->PlaySound(_SpawnFlySongId);

	Engine::GetInstanceManager()->SpawnCopyInWorldAt(std::string("FlyEnemy"), std::string("FlyEnemyCopy") + std::to_string(BossEnemy::CurrentNumberOfFlyEnemySpawn));
	BossEnemy::CurrentNumberOfFlyEnemySpawn++;
}

void BossEnemy::AnimationListener(int FrameIndex, const std::string& AnimationName)
{
	if (AnimationName == std::string("IdleAnimation"))
	{
		_CurrentBossState = Thinking;
		_bIsCurrentlyLanding = false;
	}
	else if (AnimationName == std::string("VomitAnimation"))
	{
		SpawnFly();
	}
}
