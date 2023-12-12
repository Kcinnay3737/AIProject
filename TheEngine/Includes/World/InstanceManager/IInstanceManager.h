#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class Actor;

	//Value for an instantiable actor
	struct InstanceActor
	{
		Actor* ActorInstance = nullptr;
		Param InitialiseParams = Param{};
		Param DestroyParams = Param{};
		Param CloneParam = Param{};
	};

	//Interface for a instance manager for spawn copy of prototype
	class IInstanceManager : public IServiceProvider
	{
	public:
		virtual ~IInstanceManager() = default;

		//Add a new instance
		virtual void AddInstance(Actor* ActorInstance, const Param& InitialiseParams = Param{}, const Param& DestroyParams = Param{}, const Param& CloneParams = Param{}) = 0;
		//Delete instance at key
		virtual void DeleteInstanceAt(std::string Name) = 0;
		//Get instance at key
		virtual InstanceActor& GetInstanceAt(std::string Name) = 0;
		//Create a new copy of prototype at Name and copy it with copy name
		virtual Actor* GetCopyAt(std::string Name, std::string CopyName) = 0;
		//Create a copy and spawn this copy in the world
		virtual Actor* SpawnCopyInWorldAt(std::string Name, std::string CopyName) = 0;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override = 0;
		virtual void Shutdown(const Param& Params = Param{}) override = 0;
	};
}