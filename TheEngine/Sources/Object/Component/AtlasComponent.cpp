#include "Object/Component/AtlasComponent.h"
#include "Engine.h"

using namespace NPEngine;

AtlasComponent::AtlasComponent(const std::string& Name) : SpriteComponent(Name)
{
}

bool AtlasComponent::Initialise(const Param& Params)
{
	SpriteComponent::Initialise(Params);

	auto IT = Params.find("TileSize");
	if (IT != Params.end())
	{
		_TileSize = std::any_cast<Vector2D<int>>(IT->second);
	}

	return true;
}

void AtlasComponent::Draw()
{
	if (!_bDraw) return;

	if (_bTextureIsLoaded)
	{
		Engine::GetGraphics()->DrawTextureTile(_TextureID, Rectangle2D<float>(GetPosition(), GetSize()), _TileSize, _CurrTileIndex, Color::White, 0.0f, _Flip);
	}
}