#pragma once

#include "AI/IAIQLearning.h"
#include "Utility/Utility.h"

#include <AIToolbox/MDP/Algorithms/QLearning.hpp>
#include <AIToolbox/MDP/Model.hpp>
#include <AIToolbox/MDP/Policies/EpsilonPolicy.hpp>
#include <AIToolbox/MDP/Policies/QGreedyPolicy.hpp>
#include <AIToolbox/Seeder.hpp>
#include <fstream>
#include <random>

namespace NPEngine
{
	//Provider for AI using QLearning with AI-Toolbox
	class AITBQLearning : public IAIQLearning
	{
	private:
		AIToolbox::MDP::Model* _Model = nullptr;
		AIToolbox::MDP::QLearning* _QLearning = nullptr;
		AIToolbox::MDP::QGreedyPolicy* _QGreedyPolicy = nullptr;
		AIToolbox::MDP::EpsilonPolicy* _EpsilonPolicy = nullptr;

		double _EpsilonDiscountFactor = 0.0;
		float _EpsilonUpdateDelay = 0.1f;

		float _CurrentEpsilonRate = 0.0f;

	public:
		AITBQLearning(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon, double EpsilonDiscountFactor, float EpsilonUpdateDelay);
		virtual ~AITBQLearning();

		//IAIQLearning interface
		virtual void Initialize(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon, double EpsilonDiscountFactor, float EpsilonUpdateDelay) override;

		virtual int GetAction(int State) const override;

		virtual void UpdateQTable(int CurrentState, int Action, double Reward, int NewState) override;

		virtual void UpdateEpsilon(float DeltaTime) override;

		virtual void SetLearningRate(double LearningRate) override;
		virtual double GetLearningRate() const override;
		virtual void SetDiscountFactor(double DiscountFactor) override;
		virtual double GetDiscountFactor() const override;
		virtual void SetEpsilon(double Epsilon) override;
		virtual double GetEpsilon() const override;
		virtual void SetEpsilonDiscountFactor(double EpsilonDiscountFactor) override;
		virtual double GetEpsilonDiscountFactor() const override;
		virtual void SetEpsilonUpdateDelay(float EpsilonUpdateDelay) override;
		virtual float GetEpsilonUpdateDelay() const override;
		//---------------------
	};
}