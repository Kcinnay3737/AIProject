#pragma once

#include "Object/Actor/Actor.h"

using namespace NPEngine;

//Class for background image with music
class Background : public Actor
{
private:
	size_t _MusicSoundId = 0;

public:
	Background(const std::string& Name);
	virtual ~Background() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{}) override;

private:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;

	virtual void BeginPlay() override;
};