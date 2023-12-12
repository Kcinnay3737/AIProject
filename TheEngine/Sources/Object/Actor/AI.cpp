#include "Object/Actor/AI.h"
#include "AI/AITBQlearning.h"

using namespace NPEngine;

AI::AI(const std::string& Name) : Actor(Name)
{
}

Actor* AI::Clone(const std::string& Name, const Param& Params)
{
	AI* NewAI = new AI(Name);
	return NewAI;
}

bool AI::Initialise(const Param& Params)
{
	bool bSucces = Actor::Initialise(Params);

	_IAQLearning = new AITBQLearning(1, 1, 0.1, 0.1, 0.1, 0.99, 0.1f);

	return bSucces;
}

void AI::Destroy(const Param& Params)
{
	Actor::Destroy(Params);

	delete _IAQLearning;
}

void AI::BeginPlay()
{
	Actor::BeginPlay();

}

void AI::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	//Get the current state
	int CurrentState = GetCurrentState();

	//Get the action
	int Action = _IAQLearning->GetAction(CurrentState);

	//Perform the action
	PerformAction(Action, DeltaTime);

	//Get the new state
	int NewState = GetNewState();

	//Get the reward
	double Reward = GetReward();

	//Update the QTable
	_IAQLearning->UpdateQTable(CurrentState, Action, Reward, NewState);

	//Update epsilon
	_IAQLearning->UpdateEpsilon(DeltaTime);
}

int AI::GetCurrentState()
{
	return 0;
}

void AI::PerformAction(int Action, float DeltaTime)
{
}

int AI::GetNewState()
{
	return 0;
}

double AI::GetReward()
{
	return 0.0;
}
