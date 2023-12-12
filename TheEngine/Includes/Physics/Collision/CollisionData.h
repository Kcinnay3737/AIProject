#pragma once

#include "Math/Vector2D.h"

namespace NPEngine
{
	class Actor;

	//The data for a collision
	struct CollisionData
	{
	public:
		bool bCollision = false;
		Actor* OtherActor = nullptr;
		Vector2D<float> MovementCorrection = Vector2D<float>(0.0f, 0.0f);
	};
}