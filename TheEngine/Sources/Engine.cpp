#include "Engine.h"

#include "Graphics/SDLGraphics.h"
#include "Input/SDLInput.h"
#include "Time/SDLTime.h"
#include "Audio/SDLAudio.h"
#include "World/InstanceManager/InstanceManager.h"
#include "Physics/Physics.h"

#if _DEBUG
#include "Logger/ConsoleLogger.h"
#else
#include "Logger/FileLogger.h"
#endif

//#include <vld.h>

using namespace NPEngine;

Engine* Engine::_InstanceEngine = nullptr;

//Engine ----------------------------------------------------------------------------

bool Engine::InitEngine(const char* Name, int Width, int Height)
{
	//VLDEnable();

	Param Params;

	//Initialise logger
#if _DEBUG
	_Logger = new ConsoleLogger();
#else
	_Logger = new FileLogger();
#endif
	_LoggerProvider = static_cast<ILoggerProvider*>(_Logger);
	if (!_Logger || !_LoggerProvider || !_LoggerProvider->Initialize(Params))
	{
		return false;
	}
	Params.clear();

	//Initialise time
	_Time = new SDLTime();
	_TimeProvider = static_cast<ITimeProvider*>(_Time);
	if (!_Time || !_TimeProvider || !_TimeProvider->Initialize(Params))
	{
		return false;
	}
	Params.clear();

	//Initialise graphics
	_Graphics = new SDLGraphics();
	_GraphicsProvider = static_cast<IGraphicsProvider*>(_Graphics);
	Params["Name"] = Name;
	Params["Width"] = Width;
	Params["Height"] = Height;
	if (!_Graphics || !_GraphicsProvider || !_GraphicsProvider->Initialize(Params))
	{
		return false;
	}
	_Graphics->SetBackgroundColor(Color::Black);
	Params.clear();

	//Initialise audio
	_Audio = new SDLAudio();
	_AudioProvider = static_cast<IAudioProvider*>(_Audio);
	if (!_Audio || !_AudioProvider || !_AudioProvider->Initialize(Params))
	{
		return false;
	}
	Params.clear();

	//Initialise input
	_Input = new SDLInput();
	_InputProvider = static_cast<IInputProvider*>(_Input);
	if (!_Input || !_InputProvider || !_InputProvider->Initialize(Params))
	{
		return false;
	}
	Params.clear();

	//Initialise physics
	_Physics = new Physics();
	_PhysicsProvider = static_cast<IPhysicsProvider*>(_Physics);
	if (!_Physics || !_PhysicsProvider || !_PhysicsProvider->Initialize(Params))
	{
		return false;
	}
	Params.clear();

	//Initialise Instance Manager
	_InstanceManager = new InstanceManager();
	_InstanceManagerProvider = static_cast<IServiceProvider*>(_InstanceManager);
	if (!_InstanceManager || !_InstanceManagerProvider || !_InstanceManagerProvider->Initialize(Params))
	{
		return false;
	}
	Params.clear();

	//Initialise world
	_World = new World();
	_WorldProvider = static_cast<IWorldProvider*>(_World);
	if (!_World || !_WorldProvider || !_WorldProvider->Initialize(Params))
	{
		return false;
	}
	Params.clear();

	//Initialise the instance
	_InstanceEngine = this;

	GetEngineState().IsInit = true;

	return true;
}

void Engine::Start(void)
{
	if (!GetEngineState().IsInit)
	{
		if (!InitEngine("Unknow title", 800, 600))
		{
			return;
		}
	}

	GetEngineState().IsRunning = true;

	_TimeProvider->InitialiseTime();

	while (GetEngineState().IsRunning)
	{
		_TimeProvider->OnStartFrame();

		StartFrame();

		UpdatePhysics(_Time->GetDeltaTime());

		ProcessInput();
		PostInput();

		Update(_Time->GetDeltaTime());
		PostUpdate();

		Render();
		PostRender();

		EndFrame();

		_TimeProvider->OnEndFrame();
	}

	Shutdown();
}

//-----------------------------------------------------------------------------------

//Flow ------------------------------------------------------------------------------

void Engine::StartFrame()
{
	_WorldProvider->StartFrame();
}

void Engine::ProcessInput()
{
	_InputProvider->ProcessInput();
	

	if (_Input->IsKeyDown(Key_Escape))
	{
		Engine::GetEngineInstance()->GetEngineState().IsRunning = false;
	}
}

void Engine::PostInput()
{
	_InputProvider->UpdateInputListener(_Time->GetDeltaTime());
}

void Engine::UpdatePhysics(float DeltaTime)
{
	_PhysicsProvider->UpdatePhysics(DeltaTime);
}

static Rectangle2D<float> MovableRect = Rectangle2D<float>(Vector2D<float>(0.0f, 0.0f), Vector2D<float>(100.0f, 100.0f));

void Engine::Update(float DeltaTime)
{
	_WorldProvider->Update(DeltaTime);
}

void Engine::PostUpdate()
{
	_WorldProvider->PostUpdate();
}

void Engine::Render(void)
{
	_GraphicsProvider->Clear();

	_WorldProvider->Render();

	_GraphicsProvider->Present();
}

void Engine::PostRender()
{
	_WorldProvider->PostRender();
}

void Engine::EndFrame()
{
	_WorldProvider->EndFrame();
}

void Engine::Shutdown(void)
{
	Param Params;

	//Delete world
	if (_World && _WorldProvider)
	{
		_WorldProvider->Shutdown(Params);
		delete _World;
		_WorldProvider = nullptr;
		_World = nullptr;
	}
	Params.clear();

	//Delete instance manager
	if (_InstanceManager && _InstanceManagerProvider)
	{
		_InstanceManagerProvider->Shutdown(Params);
		delete _InstanceManager;
		_InstanceManager = nullptr;
		_InstanceManagerProvider = nullptr;
	}
	Params.clear();

	//Delete physics
	if (_Physics && _PhysicsProvider)
	{
		_PhysicsProvider->Shutdown(Params);
		delete _Physics;
		_Physics = nullptr;
		_PhysicsProvider = nullptr;
	}

	//Delete input
	if (_Input && _InputProvider)
	{
		_InputProvider->Shutdown(Params);
		delete _Input;
		_InputProvider = nullptr;
		_Input = nullptr;
	}
	Params.clear();

	//Delete audio
	if (_Audio && _AudioProvider)
	{
		_AudioProvider->Shutdown(Params);
		delete _Audio;
		_AudioProvider = nullptr;
		_Audio = nullptr;
	}
	Params.clear();

	//Delete graphics
	if (_Graphics && _GraphicsProvider)
	{
		_GraphicsProvider->Shutdown(Params);
		delete _Graphics;
		_GraphicsProvider = nullptr;
		_Graphics = nullptr;
	}
	Params.clear();

	//Delete time
	if (_Time && _TimeProvider)
	{
		_TimeProvider->Shutdown(Params);
		delete _Time;
		_TimeProvider = nullptr;
		_Input = nullptr;
	}
	Params.clear();

	//Delete logger
	if (_Logger && _LoggerProvider)
	{
		_LoggerProvider->Shutdown(Params);
		delete _Logger;
		_LoggerProvider = nullptr;
		_Logger = nullptr;
	}
	Params.clear();

	//VLDDisable();
}

//-----------------------------------------------------------------------------------

//Getter, Setter

Engine* Engine::GetEngineInstance()
{
	return _InstanceEngine;
}

EngineState& Engine::GetEngineState()
{
	return _EngineState;
}

IGraphics* Engine::GetGraphics()
{
	return GetEngineInstance()->_Graphics;
}

IInput* Engine::GetInput()
{
	return GetEngineInstance()->_Input;
}

ITime* Engine::GetTime()
{
	return GetEngineInstance()->_Time;
}

ILogger* Engine::GetLogger()
{
	return GetEngineInstance()->_Logger;
}

IAudio* Engine::GetAudio()
{
	return GetEngineInstance()->_Audio;
}

IInstanceManager* Engine::GetInstanceManager()
{
	return GetEngineInstance()->_InstanceManager;
}

World* Engine::GetWorld()
{
	return GetEngineInstance()->_World;
}

IPhysics* Engine::GetPhysics()
{
	return GetEngineInstance()->_Physics;
}
