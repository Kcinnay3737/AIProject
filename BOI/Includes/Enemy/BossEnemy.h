#pragma once

#include "Object/Actor/AI.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

class Isaac;

//Enum for all boss state
enum EBossState : uint8_t
{
	Thinking = 0,
	Jumping = 1,
	Vomiting = 2
};

//The last enemy in the game
class BossEnemy : public AI
{
public:

private:
	static int CurrentNumberOfFlyEnemySpawn;

	PhysicsComponent* _PhysicsComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	Isaac* _Player = nullptr;

	int _CurrentHealth = 40;

	EBossState _CurrentBossState = EBossState::Thinking;

	double _CurrentReward = 0.0;

	Vector2D<float> _JumpDesiredPosition = Vector2D<float>(0.0f, 0.0f);

	bool _bIsCurrentlyLanding = false;

	float _AttackDelay = 2.0f;
	float _CurrentAttackDelay = 0.0f;
	float _bCanAttack = true;
	float _BossDamage = 2.0f;

	float _BossMoveSpeed = 275.0f;

	size_t _EnemyHitSongId = 0;
	size_t _SpawnFlySongId = 0;

public:
	BossEnemy(const std::string& Name);
	virtual ~BossEnemy() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	virtual void TakeHit(float Damage) override;

protected:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;

	//AI function
	virtual int GetCurrentState() override;
	virtual void PerformAction(int Action, float DeltaTime) override;
	virtual int GetNewState() override;
	virtual double GetReward() override;
	//----------

private:
	//Call when the physics component collide
	void OnCollision(const std::vector<CollisionData>& CollisionsData);

	//AI action function
	void Jump(const Vector2D<float> JumpLocation);
	void Land();
	void Vomit();

	void UpdateJump(float DeltaTime);;

	void SpawnFly();

	//Call by the animation
	void AnimationListener(int FrameIndex, const std::string& AnimationName);

};