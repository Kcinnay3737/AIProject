#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include <Windows.h>

#include "Engine.h"

#include "Object/Actor/TileMap.h"
#include "Player/Isaac.h"
#include "UI/ButtonLoadScene.h"
#include "UI/Background.h"
#include "Enemy/FirstEnemy.h"
#include "Enemy/BossEnemy.h"
#include "Enemy/FlyEnemy.h"
#include "Door.h"
#include <ctime> 

using namespace NPEngine;

void InitGameplay(void)
{
	srand((unsigned)time(0));

	Vector2D<int> ScreenSize = Engine::GetGraphics()->GetScreenSize();

	//AI
	FirstEnemy* NewFirstEnemy = new FirstEnemy(std::string("FirstEnemy"));
	Engine::GetInstanceManager()->AddInstance(NewFirstEnemy, 
	{
		{"Size", Vector2D<float>(75.0f, 75.0f)},
		{"DrawDepth", 2}
	});

	BossEnemy* NewBossEnemy = new BossEnemy(std::string("BossEnemy"));
	Engine::GetInstanceManager()->AddInstance(NewBossEnemy,
	{
		{"Size", Vector2D<float>(300.0f, 300.0f)},
		{"DrawDepth", 3}
	});

	FlyEnemy* NewFlyEnemy = new FlyEnemy(std::string("FlyEnemy"));
	Engine::GetInstanceManager()->AddInstance(NewFlyEnemy,
	{
		{"Size", Vector2D<float>(75.0f, 75.0f)},
		{"DrawDepth", 4}
	});

	//Create and Add instance into instance manager
	TileMap* TileMapLevel1 = new TileMap(std::string("TileMapLevel1"));
	Engine::GetInstanceManager()->AddInstance(TileMapLevel1,
	{
		{"Size", Vector2D<float>(0.0f, 0.0f)},
		{"LayerPath", std::vector<std::string> {"MapBOI_Layer1.csv", "MapBOI_Layer2.csv"}},
		{"TileSetPath", std::string("TileSetMapBOI.png")},
		{"CellSize", Vector2D<float>(32.0f, 32.0f)},
		{"CollisionLayer", std::vector<int> {1}}
	});

	Isaac* NewIsaac = new Isaac(std::string("Isaac"));
	Engine::GetInstanceManager()->AddInstance(NewIsaac,
	{
		{"DrawDepth", 2}
	});

	Background* BackgroundMenu = new Background(std::string("BackgroundMenu"));
	Engine::GetInstanceManager()->AddInstance(BackgroundMenu,
	{
		{"Position", Vector2D<float>(0.0f, 0.0f)},
		{"Size", Vector2D<float>(static_cast<float>(ScreenSize.X), static_cast<float>(ScreenSize.Y))},
		{"TexturePath", std::string("BackgroundMenu.png")},
		{"DrawDepth", 0}
	});

	ButtonLoadScene* ButtonMenu = new ButtonLoadScene(std::string("ButtonMenu"));
	Vector2D<float> ButtonMenuSize = Vector2D<float>(300.0f, 100.0f);
	Vector2D<float> ButtonMenuPosition = Vector2D<float>(ScreenSize.X / 2 - ButtonMenuSize.X / 2, (ScreenSize.Y / 2 - ButtonMenuSize.Y / 2) - 200);
	Engine::GetInstanceManager()->AddInstance(ButtonMenu, 
	{
		{"Size", ButtonMenuSize},
		{"Position", ButtonMenuPosition},
		{"TexturePath", std::string("ButtonMenu.png")},
		{"TileSize", Vector2D<int>(48, 16)},
		{"LoadSceneName", std::string("SceneGame1")},
		{"DrawDepth", 1}
	});

	Door* DoorLevel1 = new Door(std::string("DoorLevel1"));
	Engine::GetInstanceManager()->AddInstance(DoorLevel1,
	{
		{"OpenLevelName", std::string("SceneGame2")},
		{"DrawDepth", 1}
	});

	Door* DoorLevel2 = new Door(std::string("DoorLevel2"));
	Engine::GetInstanceManager()->AddInstance(DoorLevel2,
	{
		{"OpenLevelName", std::string("SceneGame3")},
		{"DrawDepth", 1}
	});

	//Create the scene
	Scene* SceneMenu = Engine::GetWorld()->CreateScene(std::string("SceneMenu"));
	if (SceneMenu)
	{
		SceneMenu->SetNumberSpawnPrototype("BackgroundMenu", 1);
		SceneMenu->SetNumberSpawnPrototype("ButtonMenu", 1);
	}

	Scene* SceneGame1 = Engine::GetWorld()->CreateScene(std::string("SceneGame1"));
	if (SceneGame1)
	{
		SceneGame1->SetNumberSpawnPrototype("TileMapLevel1", 1);
		SceneGame1->SetNumberSpawnPrototype("Isaac", 1);
		SceneGame1->SetNumberSpawnPrototype("FirstEnemy", 4);
		SceneGame1->SetNumberSpawnPrototype("DoorLevel1", 1);
	}

	Scene* SceneGame2 = Engine::GetWorld()->CreateScene(std::string("SceneGame2"));
	if (SceneGame2)
	{
		SceneGame2->SetNumberSpawnPrototype("TileMapLevel1", 1);
		SceneGame2->SetNumberSpawnPrototype("Isaac", 1);
		SceneGame2->SetNumberSpawnPrototype("FirstEnemy", 10);
		SceneGame2->SetNumberSpawnPrototype("DoorLevel2", 1);
	}

	Scene* SceneGame3 = Engine::GetWorld()->CreateScene(std::string("SceneGame3"));
	if (SceneGame3)
	{
		SceneGame3->SetNumberSpawnPrototype("TileMapLevel1", 1);
		SceneGame3->SetNumberSpawnPrototype("Isaac", 1);
		SceneGame3->SetNumberSpawnPrototype("BossEnemy", 1);
	}

	//Load first scene
	Engine::GetWorld()->LoadScene(std::string("SceneMenu"));
}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
	Engine TheEngine;
	if (TheEngine.InitEngine("TestGame", 1280, 960))
	{
		InitGameplay();
		TheEngine.Start();
	}

	return 0;
}