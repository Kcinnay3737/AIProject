#pragma once

#include "Object/Component/SpriteComponent.h"

namespace NPEngine
{
	//Componet for draw tile in a texture
	class AtlasComponent : public SpriteComponent
	{
	protected:
		Vector2D<int> _TileSize = Vector2D<int>(32, 32);
		int _CurrTileIndex = 0;

	public:
		AtlasComponent(const std::string& Name);
		virtual ~AtlasComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;

		virtual void Draw() override;
		
	public:
		//Set the tile size
		void SetTileSize(Vector2D<int> TileSize) { _TileSize = TileSize; }
		//Return the tile size
		Vector2D<int> GetTileSize() const { return _TileSize; }

		//Set the tile index to draw
		void SetTileIndex(int TileIndex) { _CurrTileIndex = TileIndex; }
		//Get the current tile index
		int GetTileIndex() const { return _CurrTileIndex; }
	};
}