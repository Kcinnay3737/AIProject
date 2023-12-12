#include "World/Scene/Scene.h"
#include "Engine.h"

using namespace NPEngine;

bool Scene::Initialize(const Param& Params)
{
	return true;
}

void Scene::Destroy(const Param& Params)
{
	_PrototypeToSpawn.clear();
}

void Scene::Load(const Param& Params)
{
	for (auto& IT : _PrototypeToSpawn)
	{
		const std::string& Name = IT.first;
		const unsigned int& Number = IT.second;

		for (unsigned int i = 0; i < Number; i++)
		{
			std::string CopyName = Name + std::to_string(i);
			Engine::GetInstanceManager()->SpawnCopyInWorldAt(Name, CopyName);
		}
	}

	OnLoadScene.Broadcast(Params);
}

void Scene::SetNumberSpawnPrototype(const char* Name, unsigned int Number)
{
	_PrototypeToSpawn[Name] = Number;
}

unsigned int Scene::GetNumberSpawnPrototype(const char* Name)
{
	auto IT = _PrototypeToSpawn.find(Name);
	if (IT == _PrototypeToSpawn.end()) return 0;
	return IT->second;
}