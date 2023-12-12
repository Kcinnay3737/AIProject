#pragma once

#include "StateMachine/IState.h"
#include "Player/Isaac.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

//State when the player win
class StateIsaacWin : public IState
{
private:
	Isaac* _OwnerIsaac = nullptr;

	float _DelayRestart = 2.0f;
	float _CurrentDelayRestart = 0.0f;

	PhysicsComponent* _PhysicsComponent = nullptr;
	AtlasComponent* _AtlasComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	size_t _PlayerWinSongId = 0;

public:
	StateIsaacWin();
	virtual ~StateIsaacWin() = default;

	virtual void OnEnter(Object* Owner) override;
	virtual void Execute(float DeltaTime, Object* Owner) override;
	virtual void OnExit(Object* Owner) override;

	//Call when the physics component collide
	virtual void OnCollision(const std::vector<CollisionData>& CollisionsData) override;
};