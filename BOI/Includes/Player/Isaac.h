#pragma once

#include "Object/Actor/Actor.h"
#include "StateMachine/IState.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/AnimationComponent.h"

class IsaacUI;

using namespace NPEngine;

class Isaac : public Actor
{
public:
	//Call when the current health change
	Delegate<void, int> OnHealthChanged;
	//Call when the game is lost
	Delegate<void> OnLose;
	//Call when the game is won
	Delegate<void> OnWin;

private:
	PhysicsComponent* _PhysicsComponent = nullptr;
	AtlasComponent* _AtlasComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;
	IsaacUI* _IsaacUI = nullptr;

	//Current health
	int _CurrHP = 10;

	IState* _CurrentState = nullptr;
	std::map<std::string, IState*> _AllState;

	size_t _PlayerHitSongId = 0;

public:
	Isaac(const std::string& Name);

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{}) override;

	virtual void TakeHit(float Damage) override;

private:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;
	virtual void BeginPlay() override;

	virtual void Update(float DeltaTime) override;

	void Dead();

	//Call when the phyiscs component collide
	void OnCollision(const std::vector<CollisionData>& CollisionsData);

public:
	void SetCurrentState(const std::string& State);
};