#include "UI/IsaacUI.h"
#include "Engine.h"
#include "Player/Isaac.h"

IsaacUI::IsaacUI(const std::string& Name) : Component(Name)
{
}

bool IsaacUI::Initialise(const Param& Params)
{
	bool bSucces = Component::Initialise(Params);

	Isaac* OwnerIsaac = dynamic_cast<Isaac*>(_OwnerActor);
	if (OwnerIsaac)
	{
		OwnerIsaac->OnHealthChanged.AddFunction(this, &IsaacUI::OnHealthChanged);
	}

	return bSucces;
}

void IsaacUI::Draw()
{
	Vector2D<float> CurrHeartPostion = _FirstHeartPosition;

	for (int i = 0; i < _CurrentHealth; i++)
	{
		Engine::GetGraphics()->DrawTexture(_TextureID, Rectangle2D<float>(CurrHeartPostion, _HeartSize));
		CurrHeartPostion.X += _HeartSize.X + _Spacer;
	}
}

void IsaacUI::OnHealthChanged(int CurrHealth)
{
	_CurrentHealth = CurrHealth;
}

void IsaacUI::SetTexture(const std::string& Filepath)
{
	_TextureID = Engine::GetGraphics()->LoadTexture(Filepath.c_str());
}
