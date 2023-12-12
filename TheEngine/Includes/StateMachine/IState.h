#pragma once

#include "Utility/Utility.h"
#include "Physics/Collision/CollisionData.h"

namespace NPEngine
{
	class Object;

	//Interface for a state in a state machine
	class IState
	{
	public:
		virtual ~IState() = default;

		//Call when state start
		virtual void OnEnter(Object* Owner) = 0;
		//Call each frame when the state is active
		virtual void Execute(float DeltaTime, Object* Owner) = 0;
		//Call when the state exit
		virtual void OnExit(Object* Owner) = 0;

		//Call when the owner of this state collide
		virtual void OnCollision(const std::vector<CollisionData>& CollisionsData) = 0;
	};
}