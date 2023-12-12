#pragma once

#include "Utility/Utility.h"
#include "Utility/GameplayStatic.h"

#include "Logger/ILogger.h"
#include "Time/ITime.h"
#include "Graphics/IGraphics.h"
#include "Audio/IAudio.h"
#include "Input/IInput.h"
#include "World/World.h"
#include "World/InstanceManager/IInstanceManager.h"
#include "Physics/IPhysics.h"

namespace NPEngine
{
	//Current engine state
	struct EngineState
	{
	public:
		bool IsInit = false;
		bool IsRunning = false;
	};

	class Engine final 
	{
	public:

	private:
		//The current engine instance
		static Engine* _InstanceEngine;

		//Current engine state
		EngineState _EngineState = EngineState();

		//All provider
		IGraphicsProvider* _GraphicsProvider = nullptr;
		IGraphics* _Graphics = nullptr;
		IInputProvider* _InputProvider = nullptr;
		IInput* _Input = nullptr;
		ITimeProvider* _TimeProvider = nullptr;
		ITime* _Time = nullptr;
		ILoggerProvider* _LoggerProvider = nullptr;
		ILogger* _Logger = nullptr;
		IAudioProvider* _AudioProvider = nullptr;
		IAudio* _Audio = nullptr;
		IServiceProvider* _InstanceManagerProvider = nullptr;
		IInstanceManager* _InstanceManager = nullptr;
		IWorldProvider* _WorldProvider = nullptr;
		World* _World = nullptr;
		IPhysicsProvider* _PhysicsProvider = nullptr;
		IPhysics* _Physics = nullptr;

	public:
		//Call for init engine
		bool InitEngine(const char* Name, int Widht, int Height);
		//Start the engine
		void Start(void);

	private:
		//Call at start of frame
		void StartFrame();

		//Process all the current input
		void ProcessInput();
		//Call after process input
		void PostInput();

		//Update the physics in the world
		void UpdatePhysics(float DeltaTime);

		//Call each frame for update world
		void Update(float DeltaTime);
		//Call each frame after the update
		void PostUpdate();

		//Call each frame for render world
		void Render(void);
		//Call each frame after render
		void PostRender();

		//Call at end of frame
		void EndFrame();

		//Shut down all provider data and the engine
		void Shutdown(void);

	public:
		//Getter, setter
		EngineState& GetEngineState();

		static Engine* GetEngineInstance();

		static IGraphics* GetGraphics();
		static IInput* GetInput();
		static ITime* GetTime();
		static ILogger* GetLogger();
		static IAudio* GetAudio();
		static IInstanceManager* GetInstanceManager();
		static World* GetWorld();
		static IPhysics* GetPhysics();
	};
}