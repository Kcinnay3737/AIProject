#pragma once

#include "Utility/Utility.h"
#include "Physics/Collision/CollisionData.h"
#include "Physics/PhysicsEnum.h"

namespace NPEngine
{
	class Actor;
	class PhysicsComponent;

	//A interface class for collision
	class ICollision
	{
	public:
		virtual ~ICollision() = default;

		//Return collision data with point collision in parameters
		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const = 0;
		//Return collision data with box collision in parameters
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const = 0;
		//Return collision data with sphere collision in parameters
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const = 0;
		//Return collision data with line collision in parametersv
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const = 0;
		//Return collision data with grid collision in parameters
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const = 0;

		//Draw current collision
		virtual void DrawCollision() = 0;

		//Return the current collision type
		virtual ECollisionType GetCollisionType() const = 0;

		//Return the collision owner
		virtual Actor* GetOwner() const = 0;
		//Return the physics component owner
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const = 0;
	};
}