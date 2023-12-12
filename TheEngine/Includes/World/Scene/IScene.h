#pragma once

#include "World/Scene/ISceneProvider.h"


namespace NPEngine
{
	//Insterface for scene provider
	class IScene : public ISceneProvider
	{
	public:


	public:
		virtual ~IScene() = default;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Destroy(const Param& Params) override = 0;

		//Load the current scene value in the world
		virtual void Load(const Param& Params) override = 0;

	public:
		//Set the number of prototype to spawn at key Name
		virtual void SetNumberSpawnPrototype(const char* Name, unsigned int Number) = 0;
		//Return the number of prototype to spawn at key name
		virtual unsigned int GetNumberSpawnPrototype(const char* Name) = 0;
		
	};
}