#pragma once

#include "World/Scene/IScene.h"
#include "Utility/Delegate.h"

namespace NPEngine
{
	//Scene provider
	class Scene final : public IScene
	{
	public:
		//Call when the scene is load
		Delegate<void, const Param&> OnLoadScene;

	private:
		//All prototype to spawn on load
		std::map<std::string, unsigned int> _PrototypeToSpawn;

	public:
		virtual ~Scene() = default;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void Load(const Param& Params) override;
	
	public:
		virtual unsigned int GetNumberSpawnPrototype(const char* Name) override;
		virtual void SetNumberSpawnPrototype(const char* Name, unsigned int Number) override;

	};
}