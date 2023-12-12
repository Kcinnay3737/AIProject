#pragma once

#include "Object/Actor/Actor.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/PhysicsComponent.h"

using namespace NPEngine;

//A door for change scene when all enemies is dead
class Door : public Actor
{
private:
	AtlasComponent* _AtlasComponent = nullptr;
	PhysicsComponent* _PhysicsComponent = nullptr;

	bool _bIsOpen = false;

	std::string _OpenLevelName = "";

	int _NumberOfMonsterAlive = 0;

public:
	Door(const std::string& Name);
	virtual ~Door() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	//Close the door
	void Close();
	//Open the door
	void Open();

	//Add monster alive to kill for open the door
	void AddMonsterAlive();
	//Pop a monster, when the number of monster is 0 the door open
	void PopMonsterAlive();

private:
	virtual bool Initialise(const Param& Params) override;

	virtual void BeginPlay() override;

	//Called when the physics component collide
	void OnCollision(const std::vector<CollisionData>& CollisionsData);

	//Open the level
	void OpenLevel();

public:
	void SetOpenLevelName(const std::string& LevelName) { _OpenLevelName = LevelName; }
};