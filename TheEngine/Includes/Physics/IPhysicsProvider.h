#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class PhysicsComponent;

	//A interface for physcics provider friend with engine and physcis component
	class IPhysicsProvider : public IServiceProvider
	{
		friend class PhysicsComponent;
		friend class Engine;
	public:
		virtual ~IPhysicsProvider() = default;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override = 0;
		virtual void Shutdown(const Param& Params = Param{}) override = 0;

		//Call each frame for process the physics
		virtual void UpdatePhysics(float DeltaTime) = 0;

		//Add a new physics actor for calcule physics each frame
		virtual void AddPhysicsActor(const std::string& ActorName, PhysicsComponent* PhysicsComponentToAdd) = 0;
		//Remove physics actor with name
		virtual void RemovePhysicsActor(const std::string& Name) = 0;
	};
}