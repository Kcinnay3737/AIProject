#pragma once

#include "Physics/IPhysicsProvider.h"
#include "Physics/Collision/CollisionData.h"

namespace NPEngine
{
	class ICollision;

	//A interface for a physics provider
	class IPhysics : public IPhysicsProvider
	{
	public:
		virtual ~IPhysics() = default;

		//return all collision with the parameters collision
		virtual std::vector<CollisionData> CheckCollisionWith(const ICollision* Collision) = 0;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override = 0;
		virtual void Shutdown(const Param& Params = Param{}) override = 0;

		//Call each frame for process the physics
		virtual void UpdatePhysics(float DeltaTime) override = 0;

		//Add a new physics actor for calcule physics each frame
		virtual void AddPhysicsActor(const std::string& ActorName, PhysicsComponent* PhysicsComponentToAdd) override = 0;
		//Remove physics actor with name
		virtual void RemovePhysicsActor(const std::string& Name) override = 0;
	};
}