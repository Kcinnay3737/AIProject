#pragma once

#include "StateMachine/IState.h"
#include "Player/Isaac.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

//State when the player is dead
class StateIsaacDead: public IState
{
private:
	Isaac* _OwnerIsaac = nullptr;

	PhysicsComponent* _PhysicsComponent = nullptr;
	AtlasComponent* _AtlasComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	float _DelayRestart = 2.0f;
	float _CurrentDelayRestart = 0.0f;

	size_t _PlayerLossSongId = 0;
public:
	StateIsaacDead();
	virtual ~StateIsaacDead() = default;

	virtual void OnEnter(Object* Owner) override;
	virtual void Execute(float DeltaTime, Object* Owner) override;
	virtual void OnExit(Object* Owner) override;

	//Call when the physics collide
	virtual void OnCollision(const std::vector<CollisionData>& CollisionsData) override;
};