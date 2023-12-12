#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	//Interface for AI using QLearning
	class IAIQLearning
	{
	public:
		virtual ~IAIQLearning() = default;

		// Initialise QLearning parameters
		virtual void Initialize(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon, double EpsilonDiscountFactor, float EpsilonUpdateRate) = 0;

		// Get the best action for a state
		virtual int GetAction(int State) const = 0;

		// Update the QTable with the current state, action, reward, new state
		virtual void UpdateQTable(int CurrentState, int Action, double Reward, int NewState) = 0;
		
		virtual void UpdateEpsilon(float DeltaTime) = 0;

		// Set and get parameters
		virtual void SetLearningRate(double LearningRate) = 0;
		virtual double GetLearningRate() const = 0;
		virtual void SetDiscountFactor(double DiscountFactor) = 0;
		virtual double GetDiscountFactor() const = 0;
		virtual void SetEpsilon(double Epsilon) = 0;
		virtual double GetEpsilon() const = 0;
		virtual void SetEpsilonDiscountFactor(double EpsilonDiscountFactor) = 0;
		virtual double GetEpsilonDiscountFactor() const = 0;
		virtual void SetEpsilonUpdateDelay(float EpsilonUpdateRate) = 0;
		virtual float GetEpsilonUpdateDelay() const = 0;
	};
}