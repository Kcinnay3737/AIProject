#include "World/InstanceManager/InstanceManager.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

bool InstanceManager::Initialize(const Param& Params)
{
    return true;
}

void InstanceManager::Shutdown(const Param& Params)
{
	for (auto& IT : _Instances)
	{
		InstanceActor& CurrInstanceActor = IT.second;

		Actor* CurrActor = CurrInstanceActor.ActorInstance;
		if (!CurrActor) continue;

		IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
		if (ActorWorld)
		{
			ActorWorld->Destroy(CurrInstanceActor.DestroyParams);
		}

		delete CurrActor;
	}
	_Instances.clear();
}

void InstanceManager::AddInstance(Actor* ActorInstance, const Param& InitialiseParams, const Param& DestroyParams, const Param& CloneParams)
{
	if (!ActorInstance) return;

	const std::string& InstanceName = ActorInstance->GetName();

	auto IT = _Instances.find(InstanceName);
	if (IT != _Instances.end())
	{
		Engine::GetLogger()->LogMessage("An instance already has this name");
		return;
	}

	InstanceActor CurrInstanceActor = InstanceActor();
	CurrInstanceActor.ActorInstance = ActorInstance;
	CurrInstanceActor.InitialiseParams = InitialiseParams;
	CurrInstanceActor.DestroyParams = DestroyParams;
	CurrInstanceActor.CloneParam = CloneParams;

	_Instances[InstanceName] = CurrInstanceActor;
}

void InstanceManager::DeleteInstanceAt(std::string Name)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return;

	InstanceActor CurrInstanceActor = IT->second;

	Actor* CurrActor = CurrInstanceActor.ActorInstance;

	_Instances.erase(IT);

	if (!CurrActor) return;

	IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
	if (ActorWorld)
	{
		ActorWorld->Destroy(CurrInstanceActor.DestroyParams);
	}

	delete CurrActor;
}

InstanceActor& InstanceManager::GetInstanceAt(std::string Name)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return _BaseInstanceActor;
	return IT->second;
}

Actor* InstanceManager::GetCopyAt(std::string Name, std::string CopyName)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return nullptr;

	InstanceActor& CurrInstanceActor = IT->second;

	Actor* Instance = CurrInstanceActor.ActorInstance;
	Actor* CopyInstance = Instance->Clone(CopyName, CurrInstanceActor.CloneParam);
	return CopyInstance;
}

Actor* InstanceManager::SpawnCopyInWorldAt(std::string Name, std::string CopyName)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return nullptr;

	InstanceActor& CurrInstanceActor = IT->second;

	Actor* Instance = CurrInstanceActor.ActorInstance;
	Actor* CopyInstance = Instance->Clone(CopyName, CurrInstanceActor.CloneParam);

	Engine::GetWorld()->AddActor(CopyInstance, CurrInstanceActor.InitialiseParams);

	return CopyInstance;
}
