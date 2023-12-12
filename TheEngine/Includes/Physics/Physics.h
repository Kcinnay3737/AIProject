#pragma once

#include "Physics/IPhysics.h"

namespace NPEngine
{
	class PhysicsComponent;

	//Provider for physics
	class Physics : public IPhysics
	{
	public:
		virtual ~Physics() = default;

		virtual std::vector<CollisionData> CheckCollisionWith(const ICollision* Collision) override;

	private:
		std::map<std::string, PhysicsComponent*> _PhysicsActors;

		virtual bool Initialize(const Param& Params = Param{}) override;
		virtual void Shutdown(const Param& Params = Param{}) override;

		virtual void UpdatePhysics(float DeltaTime) override;

		virtual void AddPhysicsActor(const std::string& ActorName, PhysicsComponent* PhysicsComponentToAdd) override;
		virtual void RemovePhysicsActor(const std::string& Name) override;
	};
}