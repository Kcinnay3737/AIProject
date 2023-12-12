#pragma once

#include "Object/Actor/Button.h"

using namespace NPEngine;

//Button for load a scene
class ButtonLoadScene : public Button
{
private:
	std::string _LoadSceneName = "";

public:
	ButtonLoadScene(const std::string& Name);
	virtual ~ButtonLoadScene() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{}) override;

private:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;
	virtual void BeginPlay() override;

	//Lead the current button scene
	void LoadScene();

public:
	void SetLoadSceneName(const std::string& Name) { _LoadSceneName = Name; }

};