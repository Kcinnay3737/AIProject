#pragma once

#include "Object/Actor/Actor.h"

namespace NPEngine
{
	//Class for a tilemap
	class TileMap : public Actor
	{
	public:
		std::vector<std::vector<std::vector<int>>> _TileMap;

		size_t _TileSetID = 0;

		Vector2D<float> _CellSize = Vector2D<float>(0.0f, 0.0f);
		std::vector<int> _CollisionLayer;

	public:
		TileMap(const std::string& Name);
		virtual ~TileMap() = default;

		virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	protected:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		virtual void BeginPlay() override;

		virtual void Draw() override;

	private:
		//Load a tile set
		void LoadTileSet(const std::string& TileSetPath);
		//Load tile map at the path, use csv file
		void LoadTileMap(const std::vector<std::string>& LayerPath);

		//Return a grid with collide cell
		std::vector<std::vector<bool>> GetCollisionGrid() const;
	};
}