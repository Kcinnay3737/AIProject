#include "UI/ButtonLoadScene.h"
#include "Engine.h"

ButtonLoadScene::ButtonLoadScene(const std::string& Name) : Button(Name)
{

}

bool ButtonLoadScene::Initialise(const Param& Params)
{
	Button::Initialise(Params);

	auto IT = Params.find("LoadSceneName");
	if (IT != Params.end())
	{
		_LoadSceneName = std::any_cast<std::string>(IT->second);
	}

	return true;
}

void ButtonLoadScene::Destroy(const Param& Params)
{
	Button::Destroy(Params);

	OnClicked.RemoveFunction(this, &ButtonLoadScene::LoadScene);
}

void ButtonLoadScene::BeginPlay()
{
	Button::BeginPlay();

	OnClicked.AddFunction(this, &ButtonLoadScene::LoadScene);
}

Actor* ButtonLoadScene::Clone(const std::string& Name, const Param& Params)
{
	ButtonLoadScene* NewButtonLoadScene = new ButtonLoadScene(Name);
	return NewButtonLoadScene;
}

void ButtonLoadScene::LoadScene()
{
	Engine::GetWorld()->LoadScene(_LoadSceneName);
}
