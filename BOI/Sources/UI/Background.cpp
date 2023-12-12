#include "UI/Background.h"
#include "Object/Component/SpriteComponent.h"
#include "Engine.h"

Background::Background(const std::string& Name) : Actor(Name)
{
}

bool Background::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	CreateComponentOfClass<SpriteComponent>(std::string("SpriteComponent"), Params);

	return true;
}

void Background::Destroy(const Param& Params)
{
	Actor::Destroy(Params);
	Engine::GetAudio()->StopMusic();
}

void Background::BeginPlay()
{
	Actor::BeginPlay();

	_MusicSoundId = Engine::GetAudio()->LoadMusic(std::string("MenuMusic.mp3"));
	Engine::GetAudio()->PlayMusic(_MusicSoundId);
}


Actor* Background::Clone(const std::string& Name, const Param& Params)
{
	Background* NewBackground = new  Background(Name);
	return NewBackground;
}