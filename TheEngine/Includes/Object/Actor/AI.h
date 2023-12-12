#pragma once

#include "Object/Actor/Actor.h"
#include "AI/IAIQLearning.h"

namespace NPEngine
{
	class Model;
	//Class for artificial intelligence
	class AI : public Actor
	{
	public:

	protected:
		//QLearning interface
		IAIQLearning* _IAQLearning = nullptr;

	public:
		AI(const std::string& Name);
		virtual ~AI() = default;

		virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	protected:
		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void BeginPlay() override;
		virtual void Update(float DeltaTime) override;

		//AI function
		//Return the current state
		virtual int GetCurrentState();
		//Performe the chosen action
		virtual void PerformAction(int Action, float DeltaTime);
		//Return the state after perform action
		virtual int GetNewState();
		//Return the reward
		virtual double GetReward();
		//----------

	public:
	};
}