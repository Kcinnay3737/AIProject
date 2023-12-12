#include "AI/AITBQlearning.h"
#include "Engine.h"

using namespace NPEngine;

AITBQLearning::AITBQLearning(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon, double EpsilonDiscountFactor, float EpsilonUpdateDelay)
{
	_Model = new AIToolbox::MDP::Model(StateSize, ActionSize, DiscountFactor);
	_QLearning = new AIToolbox::MDP::QLearning(StateSize, ActionSize, DiscountFactor, LearningRate);
	_QGreedyPolicy = new AIToolbox::MDP::QGreedyPolicy(_QLearning->getQFunction());
	_EpsilonPolicy = new AIToolbox::MDP::EpsilonPolicy(*_QGreedyPolicy, Epsilon);

	_EpsilonDiscountFactor = EpsilonDiscountFactor;
	_EpsilonUpdateDelay = EpsilonUpdateDelay;
	_CurrentEpsilonRate = 0.0f;
}

AITBQLearning::~AITBQLearning()
{
	delete _Model;
	delete _QLearning;
	delete _QGreedyPolicy;
	delete _EpsilonPolicy;
}

void AITBQLearning::Initialize(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon, double EpsilonDiscountFactor, float EpsilonUpdateDelay)
{
	delete _Model;
	delete _QLearning;
	delete _QGreedyPolicy;
	delete _EpsilonPolicy;

	_Model = new AIToolbox::MDP::Model(StateSize, ActionSize, DiscountFactor);
	_QLearning = new AIToolbox::MDP::QLearning(StateSize, ActionSize, DiscountFactor, LearningRate);
	_QGreedyPolicy = new AIToolbox::MDP::QGreedyPolicy(_QLearning->getQFunction());
	_EpsilonPolicy = new AIToolbox::MDP::EpsilonPolicy(*_QGreedyPolicy, Epsilon);

	_EpsilonDiscountFactor = EpsilonDiscountFactor;
	_EpsilonUpdateDelay = EpsilonUpdateDelay;
	_CurrentEpsilonRate = 0.0f;
}

int AITBQLearning::GetAction(int State) const
{
	return _EpsilonPolicy->sampleAction(State);
}

void AITBQLearning::UpdateQTable(int CurrentState, int Action, double Reward, int NewState)
{
	_QLearning->stepUpdateQ(CurrentState, Action, NewState, Reward);
}

void AITBQLearning::UpdateEpsilon(float DeltaTime)
{
	_CurrentEpsilonRate += DeltaTime;
	if (_CurrentEpsilonRate <= _EpsilonUpdateDelay)
	{
		SetEpsilon(GetEpsilon() * _EpsilonDiscountFactor);
	}
}

void AITBQLearning::SetLearningRate(double LearningRate)
{
	_QLearning->setLearningRate(LearningRate);
}

double AITBQLearning::GetLearningRate() const
{
	return _QLearning->getLearningRate();
}

void AITBQLearning::SetDiscountFactor(double DiscountFactor)
{
	_Model->setDiscount(DiscountFactor);
	_QLearning->setDiscount(DiscountFactor);
}

double AITBQLearning::GetDiscountFactor() const
{
	return _QLearning->getDiscount();
}

void AITBQLearning::SetEpsilon(double Epsilon)
{
	_EpsilonPolicy->setEpsilon(Epsilon);
	_CurrentEpsilonRate = 0.0f;
}

double AITBQLearning::GetEpsilon() const
{
	return _EpsilonPolicy->getEpsilon();
}

void AITBQLearning::SetEpsilonDiscountFactor(double EpsilonDiscountFactor)
{
	_EpsilonDiscountFactor = EpsilonDiscountFactor;
}

double AITBQLearning::GetEpsilonDiscountFactor() const
{
	return _EpsilonDiscountFactor;
}

void AITBQLearning::SetEpsilonUpdateDelay(float EpsilonUpdateDelay)
{
	_EpsilonUpdateDelay = EpsilonUpdateDelay;
}

float AITBQLearning::GetEpsilonUpdateDelay() const
{
	return _EpsilonUpdateDelay;
}
