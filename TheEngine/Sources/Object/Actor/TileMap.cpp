#include "Object/Actor/TileMap.h"
#include "Engine.h"
#include "Object/Component/PhysicsComponent.h"
#include "Physics/Collision/GridCollision.h"

#include <fstream>
#include <sstream>

using namespace NPEngine;

TileMap::TileMap(const std::string& Name) : Actor(Name)
{
}

bool TileMap::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"), Params);

	auto IT = Params.find("CollisionLayer");
	if (IT != Params.end())
	{
		_CollisionLayer = std::any_cast<const std::vector<int>&>(IT->second);
	}

	IT = Params.find("LayerPath");
	if (IT != Params.end())
	{
		const std::vector<std::string>& LayerPath = std::any_cast<const std::vector<std::string>&>(IT->second);
		LoadTileMap(LayerPath);
	}

	IT = Params.find("TileSetPath");
	if (IT != Params.end())
	{
		const std::string& TileSetPath = std::any_cast<const std::string&>(IT->second);

		LoadTileSet(TileSetPath);
	}

	IT = Params.find("CellSize");
	if (IT != Params.end())
	{
		_CellSize = std::any_cast<Vector2D<float>>(IT->second);
	}

	return true;
}

void TileMap::Destroy(const Param& Params)
{
	Actor::Destroy(Params);


}

void TileMap::BeginPlay()
{
	Actor::BeginPlay();

	PhysicsComponent* CurrPhysicsComponent = GetComponentOfClass<PhysicsComponent>();
	if (CurrPhysicsComponent)
	{
		CurrPhysicsComponent->SetIsMovable(false);
		CurrPhysicsComponent->SetIsCalculeCollision(false);

		CurrPhysicsComponent->SetCollision(ECollisionType::Grid);
		//CurrPhysicsComponent->SetDrawCollision(true);

		GridCollision* CurrGridCollision = static_cast<GridCollision*>(CurrPhysicsComponent->GetCollision());
		CurrGridCollision->SetCellSize(_CellSize);
		CurrGridCollision->SetGrid(GetCollisionGrid());
	}
}

Actor* TileMap::Clone(const std::string& Name, const Param& Params)
{
	TileMap* CloneActor = new TileMap(Name);
	return CloneActor;
}

void TileMap::Draw()
{
	for (const std::vector<std::vector<int>>& CurrLayer : _TileMap)
	{
		Rectangle2D<float> CurrDrawRectangle = Rectangle2D<float>(Vector2D<float>(0.0f, 0.0f), _CellSize);

		for (const std::vector<int>& CurrRow : CurrLayer)
		{
			CurrDrawRectangle.Position.X = 0;
			for (const int& Cell : CurrRow)
			{
				Vector2D<int> CellSizeInt = Vector2D<int>(static_cast<int>(_CellSize.X), static_cast<int>(_CellSize.Y));
				Engine::GetGraphics()->DrawTextureTile(_TileSetID, CurrDrawRectangle, CellSizeInt, Cell);
				CurrDrawRectangle.Position.X += _CellSize.X;
			}
			CurrDrawRectangle.Position.Y += _CellSize.Y;
		}
	}

	Actor::Draw();
}

void TileMap::LoadTileSet(const std::string& TileSetPath)
{
	_TileSetID = Engine::GetGraphics()->LoadTexture(TileSetPath.c_str());
}

void TileMap::LoadTileMap(const std::vector<std::string>& LayerPath)
{
	for (const std::string& EndPath : LayerPath)
	{
		std::string CurrPath = std::string("./Assets/TileMap/") + EndPath;

		std::ifstream File(CurrPath);
		std::string Line;
		std::vector<std::vector<int>> Layer;

		if (File.is_open()) 
		{
			while (getline(File, Line)) 
			{
				std::vector<int> Row;
				std::stringstream LineStream(Line);
				std::string Cell;

				while (getline(LineStream, Cell, ',')) 
				{
					if (!Cell.empty()) 
					{
						Row.push_back(std::stoi(Cell));
					}
				}

				Layer.push_back(Row);
			}
			_TileMap.push_back(Layer);
			File.close();
		}
	}
}

std::vector<std::vector<bool>> TileMap::GetCollisionGrid() const
{
	if (_TileMap.empty()) return std::vector<std::vector<bool>>();

	std::vector<std::vector<bool>> CollisionGrid(
		_TileMap[0].size(),
		std::vector<bool>(_TileMap[0][0].size(), false)
	);

	for (const int& LayerIndex : _CollisionLayer) 
	{
		if (LayerIndex < _TileMap.size()) 
		{
			for (int Y = 0; Y < _TileMap[LayerIndex].size(); Y++)
			{
				for (int X = 0; X < _TileMap[LayerIndex][Y].size(); X++)
				{
					if (_TileMap[LayerIndex][Y][X] != -1 && !CollisionGrid[Y][X]) 
					{
						CollisionGrid[Y][X] = true;
					}
				}
			}
		}
	}

	return CollisionGrid;
}
