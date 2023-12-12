#include "Enemy/FirstEnemy.h"
#include "Engine.h"
#include "Player/Isaac.h"
#include <cmath>
#include "Door.h"

FirstEnemy::FirstEnemy(const std::string& Name) : AI(Name)
{
}

Actor* FirstEnemy::Clone(const std::string& Name, const Param& Params)
{
	FirstEnemy* NewFirstEnemy = new FirstEnemy(Name);
	return NewFirstEnemy;
}

void FirstEnemy::TakeHit(float Damage)
{
	if (_CurrentHealth <= 0) return;
	_CurrentHealth -= static_cast<int>(Damage);
	Engine::GetAudio()->PlaySound(_EnemyHitSongId);
	if (_CurrentHealth <= 0)
	{
		Door* CurrDoor = Engine::GetWorld()->GetActorOfClass<Door>();
		if (CurrDoor)
		{
			CurrDoor->PopMonsterAlive();
		}
		Engine::GetWorld()->DeleteActorByName(GetName());
	}
}

bool FirstEnemy::Initialise(const Param& Params)
{
	bool bSucces = AI::Initialise(Params);

	_PhysicsComponent = CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"), Params);
	_AnimationComponent = CreateComponentOfClass<AnimationComponent>(std::string("AnimationComponent"), Params);

	return bSucces;
}

void FirstEnemy::Destroy(const Param& Params)
{
	AI::Destroy(Params);
}

void FirstEnemy::BeginPlay()
{
	AI::BeginPlay();

	_EnemyHitSongId = Engine::GetAudio()->LoadSound("EnemyHitSong.mp3");

	Door* CurrDoor = Engine::GetWorld()->GetActorOfClass<Door>();
	if (CurrDoor)
	{
		CurrDoor->AddMonsterAlive();
	}

	Vector2D<int> ScreenSize = Engine::GetGraphics()->GetScreenSize();
	Vector2D<float> FScreenSize = Vector2D<float>(static_cast<float>(ScreenSize.X), static_cast<float>(ScreenSize.Y));

	Vector2D<float> Size = GetSize();
	Vector2D<float> StartPosition = Vector2D<float>(64.0f, 64.0f);
	Vector2D<float> EndPosition = Vector2D<float>(ScreenSize.X - 80.0f - Size.X, ScreenSize.Y - 80.0f - Size.Y);

	float X = (rand() % static_cast<int>(EndPosition.X)) + StartPosition.X;
	float Y = (rand() % static_cast<int>(EndPosition.Y)) + StartPosition.Y;

	Vector2D<float> Position = Vector2D<float>(X, Y);
	SetPosition(Position);

	_Player = Engine::GetWorld()->GetActorOfClass<Isaac>();

	if (_PhysicsComponent)
	{
		_PhysicsComponent->SetCollision(ECollisionType::Box);
		_PhysicsComponent->SetMaxVelocityMagnetude(150.0f);

		_PhysicsComponent->OnCollision.AddFunction(this, &FirstEnemy::OnCollision);
	}

	if (_AnimationComponent)
	{
		_AnimationComponent->LoadTexture(std::string("FirstEnemy.png"));
		_AnimationComponent->SetTileSize(Vector2D<int>(32, 32));

		AnimationData IdleDownAnimation = AnimationData();
		IdleDownAnimation.FrameInterval = 100.0f;
		IdleDownAnimation.StartIndex = 8;
		IdleDownAnimation.EndIndex = 8;
		_AnimationComponent->AddAnimation(std::string("IdleDownAnimation"), IdleDownAnimation);

		AnimationData MoveDownAnimation = AnimationData();
		MoveDownAnimation.FrameInterval = 0.2f;
		MoveDownAnimation.StartIndex = 8;
		MoveDownAnimation.EndIndex = 11;
		_AnimationComponent->AddAnimation(std::string("MoveDownAnimation"), MoveDownAnimation);

		AnimationData IdleUpAnimation = AnimationData();
		IdleUpAnimation.FrameInterval = 100.0f;
		IdleUpAnimation.StartIndex = 4;
		IdleUpAnimation.EndIndex = 4;
		_AnimationComponent->AddAnimation(std::string("IdleUpAnimation"), IdleUpAnimation);

		AnimationData MoveUpAnimation = AnimationData();
		MoveUpAnimation.FrameInterval = 0.2f;
		MoveUpAnimation.StartIndex = 4;
		MoveUpAnimation.EndIndex = 7;
		_AnimationComponent->AddAnimation(std::string("MoveUpAnimation"), MoveUpAnimation);

		AnimationData IdleRightAnimation = AnimationData();
		IdleRightAnimation.FrameInterval = 100.0f;
		IdleRightAnimation.StartIndex = 0;
		IdleRightAnimation.EndIndex = 0;
		_AnimationComponent->AddAnimation(std::string("IdleRightAnimation"), IdleRightAnimation);

		AnimationData MoveRightAnimation = AnimationData();
		MoveRightAnimation.FrameInterval = 0.2f;
		MoveRightAnimation.StartIndex = 0;
		MoveRightAnimation.EndIndex = 3;
		_AnimationComponent->AddAnimation(std::string("MoveRightAnimation"), MoveRightAnimation);

		AnimationData IdleLeftAnimation = AnimationData();
		IdleLeftAnimation.FrameInterval = 100.0f;
		IdleLeftAnimation.StartIndex = 0;
		IdleLeftAnimation.EndIndex = 0;
		IdleLeftAnimation.AnimationFlip.Horizontal = true;
		_AnimationComponent->AddAnimation(std::string("IdleLeftAnimation"), IdleLeftAnimation);

		AnimationData MoveLeftAnimation = AnimationData();
		MoveLeftAnimation.FrameInterval = 0.2f;
		MoveLeftAnimation.StartIndex = 0;
		MoveLeftAnimation.EndIndex = 3;
		MoveLeftAnimation.AnimationFlip.Horizontal = true;
		_AnimationComponent->AddAnimation(std::string("MoveLeftAnimation"), MoveLeftAnimation);

		_AnimationComponent->SetCurrentAnimation(std::string("MoveDownAnimation"));
		_AnimationComponent->SetOffsetSize(Vector2D<float>(40.0f, 40.0f));
		_AnimationComponent->SetOffsetPosition(Vector2D<float>(-20.0f, -20.0f));
	}

	_IAQLearning->Initialize(8, 8, 0.1, 0.1, 1.0, 0.995, 0.1f);

	Vector2D<float> PlayerPosition = _Player->GetPosition() + (_Player->GetSize() / 2);
	Vector2D<float> CurrentPosition = GetPosition() + (GetSize() / 2);

	_LastDistance = CurrentPosition.Distance(PlayerPosition);
}

void FirstEnemy::Update(float DeltaTime)
{
	AI::Update(DeltaTime);

	Vector2D<float> CurrVeloDir = _PhysicsComponent->GetVelocity();
	CurrVeloDir.Normalize();

	if (CurrVeloDir.Magnitude() > 0.0f && CurrVeloDir != _LastVeloDir)
	{
		if (CurrVeloDir.Y > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("MoveDownAnimation"));
		}
		else if (CurrVeloDir.Y < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("MoveUpAnimation"));
		}
		else if (CurrVeloDir.X > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("MoveRightAnimation"));
		}
		else if (CurrVeloDir.X < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("MoveLeftAnimation"));
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

	if (!_bCanAttack)
	{
		_CurrAttackDelay += DeltaTime;
		if (_CurrAttackDelay >= _AttackDelay)
		{
			_bCanAttack = true;
			_CurrAttackDelay = 0.0f;
		}
	}

	Vector2D<float> MidPoint = GetPosition() + GetSize() / 2;
	if (Engine::GetGraphics()->CheckPointIsOutOfScreen(MidPoint))
	{
		Engine::GetWorld()->DeleteActorByName(GetName());
	}
}

int FirstEnemy::GetCurrentState()
{
	Vector2D<float> PlayerPosition = _Player->GetPosition() + (_Player->GetSize() / 2);
	Vector2D<float> CurrentPosition = GetPosition() + (GetSize() / 2);

	Vector2D<float> Dir = (PlayerPosition - CurrentPosition);
	Dir.Normalize();

	Vector2D<float> Right = Vector2D<float>(1.0f, 0.0f);

	float Angle = Vector2D<float>::AngleBetween(Dir, Right);

	if (Angle <= 22.5f)//Right
	{
		return 0;
	}
	else if (Angle > 22.5f && Angle < 67.5f)//Right corner
	{
		float CrossProduct = Vector2D<float>::Cross(Right, Dir);
		if (CrossProduct > 0)//Down
		{
			return 7;
		}
		return 1;
	}
	else if (Angle >= 67.5f && Angle <= 112.5f)//Up/down
	{
		float CrossProduct = Vector2D<float>::Cross(Right, Dir);
		if (CrossProduct > 0)//Down
		{
			return 6;
		}
		return 2;
	}
	else if (Angle > 112.5f && Angle < 157.5f)//Left corner
	{
		float CrossProduct = Vector2D<float>::Cross(Right, Dir);
		if (CrossProduct > 0)//Down
		{
			return 5;
		}
		return 3;
	}
	else if (Angle >= 157.5f)//Left
	{
		return 4;
	}
	return 0;
}

void FirstEnemy::PerformAction(int Action, float DeltaTime)
{
	float MoveSpeed = 150.0f;

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

int FirstEnemy::GetNewState()
{
	return GetCurrentState();
}

double FirstEnemy::GetReward()
{
	double TempReward = _CurrentReward;
	_CurrentReward = 0.0;
	return TempReward;
}

void FirstEnemy::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
	for (const CollisionData& CurrCollisionData : CollisionsData)
	{
		Isaac* CurrIsaac = dynamic_cast<Isaac*>(CurrCollisionData.OtherActor);
		if(!CurrIsaac) continue;
		if (_bCanAttack)
		{
			CurrIsaac->TakeHit(1.0f);
			_bCanAttack = false;
		}
	}
}