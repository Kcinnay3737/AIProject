#pragma once

#include "Object/Component/Component.h"

using namespace NPEngine;

//UI component for the player
class IsaacUI : public Component, public IDrawableComponent
{
private:
	int _CurrentHealth = 5;
	
	size_t _TextureID = 0;
	Vector2D<float> _FirstHeartPosition = Vector2D<float>(50.0f, 50.0f);
	Vector2D<float> _HeartSize = Vector2D<float>(50.0f, 50.0f);
	float _Spacer = 10.f;

public:
	IsaacUI(const std::string& Name);
	virtual ~IsaacUI() = default;

private:
	virtual bool Initialise(const Param& Params = Param{}) override;

	virtual void Draw() override;

	//Call when the player health change
	void OnHealthChanged(int CurrHealth);

public:
	void SetTexture(const std::string& Filepath);
};