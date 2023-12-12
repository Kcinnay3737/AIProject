#pragma once

#include "StateMachine/IState.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/AnimationComponent.h"
#include "Player/Isaac.h"

using namespace NPEngine;

//State active when the player is alive
class StateIsaacAlive : public IState
{
private:
	Isaac* _OwnerIsaac = nullptr;

	PhysicsComponent* _PhysicsComponent = nullptr;
	AtlasComponent* _AtlasComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	Vector2D<float> _LastVeloDir = Vector2D<float>(0.0f, 1.0f);

	Vector2D<float> _ShootDirection = Vector2D<float>(0.0f, 0.0f);

	float _ShootDelay = 0.3f;
	float _CurrShootDelay = 0.0f;

	size_t _ShootSoundId = 0;

public:
	StateIsaacAlive();
	virtual ~StateIsaacAlive() = default;

	virtual void OnEnter(Object* Owner) override;
	virtual void Execute(float DeltaTime, Object* Owner) override;
	virtual void OnExit(Object* Owner) override;

	//
	virtual void OnCollision(const std::vector<CollisionData>& CollisionsData) override;

private:
	//Update the player shoot
	void UpdateShoot(float DeltaTime);
	//Update the body animation with the velocity
	void UpdateBodyAnimation();
	//Update the head with the velo or the shoot
	void UpdateHeadAtlas();
};