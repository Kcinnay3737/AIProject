#pragma once

#include "World/IWorldProvider.h"

namespace NPEngine
{
	class Scene;
	class Actor;

	//Interface for world provider
	class IWorld : public IWorldProvider
	{
	public:
		virtual ~IWorld() = default;

		//Load a new scene at Name
		virtual void LoadScene(const std::string& Name, const Param& Params = Param{}) = 0;
		//Create a new scene with Name
		virtual Scene* CreateScene(const std::string& Name, const Param& Params = Param{}) = 0;
		//Delete the scene at Name
		virtual void DeleteScene(const std::string& Name, const Param& Params = Param{}) = 0;

		//Add Actor in the world
		virtual void AddActor(Actor* Actor, const Param& Params = Param{}) = 0;
		//Delete actor in world at Name
		virtual void DeleteActorByName(const std::string& Name, const Param& Params = Param{}) = 0;
		//Return actor in world at Name
		virtual Actor* GetActorByName(const std::string& Name) = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		//Unload all data in the world
		virtual void UnloadWorld() = 0;

		//Unload all data in the current scene
		virtual void UnloadScene() = 0;
		//Load all data on the new scene
		virtual void OnLoadScene() = 0;

		virtual void StartFrame() override = 0;

		virtual void Update(float DeltaTime) override = 0;
		virtual void PostUpdate() override = 0;

		virtual void Render() override = 0;
		virtual void PostRender() override = 0;

		virtual void EndFrame() override = 0;

		//Delete all actor to delete
		virtual void OnDeleteActor() = 0;
		//Add all actor to add
		virtual void OnCreateActor() = 0;

	public:
		//Return the scene at Name
		virtual Scene* GetSceneByName(const std::string& Name) = 0;
	};
}