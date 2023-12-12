#include "Enemy/FlyEnemy.h"
#include <cmath>
#include "Enemy/BossEnemy.h"
#include "Engine.h"
#include "Physics/Collision/BoxCollision.h"
#include "Player/Isaac.h"

FlyEnemy::FlyEnemy(const std::string& Name) : AI(Name)
{
}

Actor* FlyEnemy::Clone(const std::string& Name, const Param& Params)
{
    FlyEnemy* NewFlyEnemie = new FlyEnemy(Name);
    return NewFlyEnemie;
}

void FlyEnemy::TakeHit(float Damage)
{
	if (_CurrentHealth <= 0) return;
	_CurrentHealth -= static_cast<int>(Damage);
	Engine::GetAudio()->PlaySound(_EnemyHitSongId);
	if (_CurrentHealth <= 0)
	{
		Engine::GetWorld()->DeleteActorByName(GetName());
	}
}

bool FlyEnemy::Initialise(const Param& Params)
{
    bool bSucces = AI::Initialise(Params);

    _PhysicsComponent = CreateComponentOfClass<PhysicsComponent>("PhysicsComponent", Params);
    _AnimationComponent = CreateComponentOfClass<AnimationComponent>("AnimationComponent", Params);

    return bSucces;
}

void FlyEnemy::Destroy(const Param& Params)
{
    AI::Destroy(Params);
}

void FlyEnemy::BeginPlay()
{
    AI::BeginPlay();

	_EnemyHitSongId = Engine::GetAudio()->LoadSound("EnemyHitSong.mp3");

	BossEnemy* CurrBossEnemy = Engine::GetWorld()->GetActorOfClass<BossEnemy>();
	Vector2D<float> BossCenterPosition = CurrBossEnemy->GetPosition() + CurrBossEnemy->GetSize() / 2;
	Vector2D<float> SpawnPosition = BossCenterPosition + Vector2D<float>(-GetSize().X / 2, -100.0f);
	SetPosition(SpawnPosition);

	if (_PhysicsComponent)
	{
		_PhysicsComponent->SetCollision(ECollisionType::Box);
		_PhysicsComponent->SetMaxVelocityMagnetude(150.0f);

		_PhysicsComponent->OnCollision.AddFunction(this, &FlyEnemy::OnCollision);

		_PhysicsComponent->AddIgnoreActorClass(typeid(BossEnemy));

		BoxCollision* CurrBoxCollision = static_cast<BoxCollision*>(_PhysicsComponent->GetCollision());
		CurrBoxCollision->SetSizeOffset(Vector2D<float>(-25.0f, -25.0f));
		CurrBoxCollision->SetPositionOffset(Vector2D<float>(15.0f, 10.0f));
	}

	if (_AnimationComponent)
	{
		_AnimationComponent->LoadTexture(std::string("FlyEnemy.png"));
		_AnimationComponent->SetTileSize(Vector2D<int>(32, 32));
		
		AnimationData BaseAnimation = AnimationData();
		BaseAnimation.FrameInterval = 0.1f;
		BaseAnimation.StartIndex = 0;
		BaseAnimation.EndIndex = 1;
		_AnimationComponent->AddAnimation(std::string("BaseAnimation"), BaseAnimation);
		
		_AnimationComponent->SetCurrentAnimation(std::string("BaseAnimation"));
	}

	_IAQLearning->Initialize(8, 8, 0.1, 0.1, 1.0, 0.995, 0.1f);

	_CurrentState = (rand() % 7) + 0;
}

void FlyEnemy::Update(float DeltaTime)
{
    AI::Update(DeltaTime);

	_CurrDelayChangeState += DeltaTime;
	if (_CurrDelayChangeState >= _DelayChangeState)
	{
		_CurrDelayChangeState = 0.0f;
		_CurrentState = (rand() % 7) + 0;
	}

	Vector2D<float> MidPoint = GetPosition() + GetSize() / 2;
	if (Engine::GetGraphics()->CheckPointIsOutOfScreen(MidPoint))
	{
		Engine::GetWorld()->DeleteActorByName(GetName());
	}
}

void FlyEnemy::Draw()
{
	Actor::Draw();
}

int FlyEnemy::GetCurrentState()
{
    return _CurrentState;
}

void FlyEnemy::PerformAction(int Action, float DeltaTime)
{
	float MoveSpeed = 300.0f;

	if (Action == GetCurrentState())
	{
		_CurrentReward += 10.0;
	}

	switch (Action)
	{
	case 0://Right
		_PhysicsComponent->AddVelocity(Vector2D<float>(MoveSpeed, 0.0f));
		break;
	case 1://RightUpCorner
		_PhysicsComponent->AddVelocity(Vector2D<float>(MoveSpeed, -MoveSpeed));
		break;
	case 2://Up
		_PhysicsComponent->AddVelocity(Vector2D<float>(0.0f, -MoveSpeed));
		break;
	case 3://LeftUpCorner
		_PhysicsComponent->AddVelocity(Vector2D<float>(-MoveSpeed, -MoveSpeed));
		break;
	case 4://Left
		_PhysicsComponent->AddVelocity(Vector2D<float>(-MoveSpeed, 0.0f));
		break;
	case 5://LeftDownCorner
		_PhysicsComponent->AddVelocity(Vector2D<float>(-MoveSpeed, MoveSpeed));
		break;
	case 6://Down
		_PhysicsComponent->AddVelocity(Vector2D<float>(0.0f, MoveSpeed));
		break;
	case 7://RightDownCorner
		_PhysicsComponent->AddVelocity(Vector2D<float>(MoveSpeed, MoveSpeed));
		break;
	}
}

int FlyEnemy::GetNewState()
{
	return GetCurrentState();
}

double FlyEnemy::GetReward()
{
	double TempReward = _CurrentReward;
	_CurrentReward = 0.0;
	return TempReward;
}

void FlyEnemy::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
	for (const CollisionData CurrCollisionData : CollisionsData)
	{
		Isaac* CurrIsaac = dynamic_cast<Isaac*>(CurrCollisionData.OtherActor);
		if (CurrIsaac)
		{
			CurrIsaac->TakeHit(3.0f);
			Engine::GetWorld()->DeleteActorByName(GetName());
		}
	}
}
