#include "Player/Isaac.h"
#include "Engine.h"
#include "Object/Component/ControllerComponent.h"
#include "Object/Actor/Projectil.h"
#include <typeindex>
#include <typeinfo>
#include "UI/IsaacUI.h"
#include "Player/StateIsaacAlive.h"
#include "Player/StateIsaacDead.h"
#include "Player/StateIsaacWin.h"

Isaac::Isaac(const std::string& Name) : Actor(Name)
{

}

bool Isaac::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"), Params);
	CreateComponentOfClass<ControllerComponent>(std::string("ControllerComponent"), Params);
	CreateComponentOfClass<AtlasComponent>(std::string("AtlasComponent"), Params);
	CreateComponentOfClass<AnimationComponent>(std::string("AnimationComponent"), Params);

	_IsaacUI = CreateComponentOfClass<IsaacUI>(std::string("IssacUIComponent"));
	_IsaacUI->SetTexture(std::string("Heart.png"));

	return true;
}

void Isaac::Destroy(const Param& Params)
{
	Actor::Destroy(Params);

	for (auto IT : _AllState)
	{
		delete IT.second;
	}
	_AllState.clear();
}

void Isaac::BeginPlay()
{
	Actor::BeginPlay();

	if (Engine::GetWorld()->PersistenteDataContain(std::string("PlayerHP")))
	{
		_CurrHP = std::any_cast<int>(Engine::GetWorld()->GetInPersistenteData(std::string("PlayerHP")));
	}

	Vector2D<int> ScreenSize = Engine::GetGraphics()->GetScreenSize();
	Vector2D<float> FScreenSize = Vector2D<float>(static_cast<float>(ScreenSize.X), static_cast<float>(ScreenSize.Y));

	Vector2D<float> Size = GetSize();
	Vector2D<float> Position = Vector2D<float>((ScreenSize.X / 2) - (Size.X / 2), ScreenSize.Y - 164.0f);
	SetPosition(Position);

	_PlayerHitSongId = Engine::GetAudio()->LoadSound(std::string("PlayerHit.mp3"));

	_AllState["Alive"] = new StateIsaacAlive();
	_AllState["Dead"] = new StateIsaacDead();
	_AllState["Win"] = new StateIsaacWin();
	SetCurrentState(std::string("Alive"));

	_PhysicsComponent = GetComponentOfClass<PhysicsComponent>();
	if (_PhysicsComponent)
	{
		_PhysicsComponent->OnCollision.AddFunction(this, &Isaac::OnCollision);
	}

	ControllerComponent* CurrControllerComponent = GetComponentOfClass<ControllerComponent>();
	if (CurrControllerComponent)
	{
		CurrControllerComponent->SetMoveSpeed(200.0f);
	}

	_AtlasComponent = GetComponentOfClass<AtlasComponent>();

	_AnimationComponent = GetComponentOfClass<AnimationComponent>();
	if (_AnimationComponent)
	{
		AnimationData IdleDownAnimation = AnimationData();
		IdleDownAnimation.FrameInterval = 100.0f;
		IdleDownAnimation.StartIndex = 0;
		IdleDownAnimation.EndIndex = 0;
		_AnimationComponent->AddAnimation(std::string("IdleDownAnimation"), IdleDownAnimation);

		AnimationData WalkDownAnimation = AnimationData();
		WalkDownAnimation.FrameInterval = 0.1f;
		WalkDownAnimation.StartIndex = 0;
		WalkDownAnimation.EndIndex = 9;
		_AnimationComponent->AddAnimation(std::string("WalkDownAnimation"), WalkDownAnimation);

		AnimationData IdleUpAnimation = AnimationData();
		IdleUpAnimation.FrameInterval = 100.0f;
		IdleUpAnimation.StartIndex = 0;
		IdleUpAnimation.EndIndex = 0;
		_AnimationComponent->AddAnimation(std::string("IdleUpAnimation"), IdleUpAnimation);

		AnimationData WalkUpAnimation = AnimationData();
		WalkUpAnimation.FrameInterval = 0.1f;
		WalkUpAnimation.StartIndex = 0;
		WalkUpAnimation.EndIndex = 9;
		_AnimationComponent->AddAnimation(std::string("WalkUpAnimation"), WalkUpAnimation);

		AnimationData IdleRightAnimation = AnimationData();
		IdleRightAnimation.FrameInterval = 100.0f;
		IdleRightAnimation.StartIndex = 10;
		IdleRightAnimation.EndIndex = 10;
		_AnimationComponent->AddAnimation(std::string("IdleRightAnimation"), IdleRightAnimation);

		AnimationData WalkRightAnimation = AnimationData();
		WalkRightAnimation.FrameInterval = 0.1f;
		WalkRightAnimation.StartIndex = 10;
		WalkRightAnimation.EndIndex = 19;
		_AnimationComponent->AddAnimation(std::string("WalkRightAnimation"), WalkRightAnimation);

		AnimationData IdleLeftAnimation = AnimationData();
		IdleLeftAnimation.FrameInterval = 100.0f;
		IdleLeftAnimation.StartIndex = 10;
		IdleLeftAnimation.EndIndex = 10;
		IdleLeftAnimation.AnimationFlip = Flip(true, false);
		_AnimationComponent->AddAnimation(std::string("IdleLeftAnimation"), IdleLeftAnimation);

		AnimationData WalkLeftAnimation = AnimationData();
		WalkLeftAnimation.FrameInterval = 0.1f;
		WalkLeftAnimation.StartIndex = 10;
		WalkLeftAnimation.EndIndex = 19;
		WalkLeftAnimation.AnimationFlip = Flip(true, false);
		_AnimationComponent->AddAnimation(std::string("WalkLeftAnimation"), WalkLeftAnimation);

		AnimationData DeadAnimation = AnimationData();
		DeadAnimation.FrameInterval = 0.3f;
		DeadAnimation.StartIndex = 0;
		DeadAnimation.EndIndex = 2;
		DeadAnimation.bLoop = false;
		_AnimationComponent->AddAnimation(std::string("DeadAnimation"), DeadAnimation);

		AnimationData WinAnimation = AnimationData();
		WinAnimation.FrameInterval = 0.3f;
		WinAnimation.StartIndex = 0;
		WinAnimation.EndIndex = 1;
		WinAnimation.bLoop = false;
		_AnimationComponent->AddAnimation(std::string("WinAnimation"), WinAnimation);
	}

	OnHealthChanged.Broadcast(_CurrHP);
}

void Isaac::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	_CurrentState->Execute(DeltaTime, this);
}

void Isaac::Dead()
{
	SetCurrentState(std::string("Dead"));
	OnLose.Broadcast();
}

void Isaac::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
	if (_CurrentState)
	{
		_CurrentState->OnCollision(CollisionsData);
	}
}

void Isaac::SetCurrentState(const std::string& State)
{
	if (_CurrentState)
	{
		_CurrentState->OnExit(this);
	}
	_CurrentState = _AllState[State];
	_CurrentState->OnEnter(this);
}

Actor* Isaac::Clone(const std::string& Name, const Param& Params)
{
	Isaac* CopyIsaac = new Isaac(Name);
	return CopyIsaac;
}

void Isaac::TakeHit(float Damage)
{
	if (_CurrHP <= 0) return;

	Engine::GetAudio()->PlaySound(_PlayerHitSongId);

	_CurrHP -= static_cast<int>(Damage);
	Engine::GetWorld()->AddInPersistenteData(std::string("PlayerHP"), _CurrHP);
	OnHealthChanged.Broadcast(_CurrHP);

	if (_CurrHP <= 0)
	{
		Dead();
	}
}
