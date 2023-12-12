#pragma once

#include "Object/Actor/AI.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

class Isaac;

//Enemy spawn by the boss
class FlyEnemy : public AI
{
public:

private:
	PhysicsComponent* _PhysicsComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	Isaac* _Player = nullptr;

	int _CurrentHealth = 2;

	float _DelayChangeState = 1.0f;
	float _CurrDelayChangeState = 0.0f;
	int _CurrentState = 0;

	double _CurrentReward = 0;

	size_t _EnemyHitSongId = 0;

public:
	FlyEnemy(const std::string& Name);
	virtual ~FlyEnemy() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	virtual void TakeHit(float Damage) override;

protected:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;

	//AI function
	virtual int GetCurrentState() override;
	virtual void PerformAction(int Action, float DeltaTime) override;
	virtual int GetNewState() override;
	virtual double GetReward() override;
	//----------

private:
	//Call when physics component collide
	void OnCollision(const std::vector<CollisionData>& CollisionsData);

};