#include "Door.h"
#include "Engine.h"
#include "Player/Isaac.h"
#include "Physics/Collision/BoxCollision.h"

void Door::AddMonsterAlive()
{
	_NumberOfMonsterAlive++;
	Close();
}

void Door::PopMonsterAlive()
{
	if (_NumberOfMonsterAlive <= 0) return;
	_NumberOfMonsterAlive--;
	if (_NumberOfMonsterAlive <= 0)
	{
		Open();
	}
}

Door::Door(const std::string& Name) : Actor(Name)
{
}

Actor* Door::Clone(const std::string& Name, const Param& Params)
{
	Door* NewDoor = new Door(Name);
	return NewDoor;
}

bool Door::Initialise(const Param& Params)
{
	bool bSucces = Actor::Initialise(Params);

	_AtlasComponent = CreateComponentOfClass<AtlasComponent>(std::string("AtlasComponent"), Params);
	_PhysicsComponent = CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"), Params);

	auto IT = Params.find(std::string("OpenLevelName"));
	if (IT != Params.end())
	{
		SetOpenLevelName(std::any_cast<std::string>(IT->second));
	}

	return bSucces;
}

void Door::BeginPlay()
{
	Actor::BeginPlay();

	_AtlasComponent->LoadTexture("Door.png");
	_AtlasComponent->SetTileSize(Vector2D<int>(64, 48));
	_AtlasComponent->SetOffsetSize(Vector2D<float>(50.0f, 50.0f));
	_AtlasComponent->SetOffsetPosition(Vector2D<float>(-20.0f, -20.0f));

	_PhysicsComponent->SetCollision(ECollisionType::Box);
	_PhysicsComponent->SetCorrectMovement(false);
	_PhysicsComponent->SetIsPhysicsVolume(false);
	_PhysicsComponent->OnCollision.AddFunction(this, &Door::OnCollision);
	
	BoxCollision* CurrBoxCollision = static_cast<BoxCollision*>(_PhysicsComponent->GetCollision());
	CurrBoxCollision->SetSizeOffset(Vector2D<float>(0.0f, 10.0f));

	Vector2D<int> ScreenSize = Engine::GetGraphics()->GetScreenSize();
	Vector2D<float> FScreenSize = Vector2D<float>(static_cast<float>(ScreenSize.X), static_cast<float>(ScreenSize.Y));

	Vector2D<float> Size = Vector2D<float>(200.0f, 70.0f);
	Vector2D<float> Position = Vector2D<float>((FScreenSize.X / 2.0f) - (Size.X / 2), -10.0f);

	SetSize(Size);
	SetPosition(Position);

	Close();
}

void Door::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
	if (!_bIsOpen) return;
	for (const CollisionData& CurrCollisionData : CollisionsData)
	{
		Isaac* CurrIsaac = dynamic_cast<Isaac*>(CurrCollisionData.OtherActor);
		if(!CurrIsaac) continue;
		OpenLevel();
		break;
	}
}

void Door::OpenLevel()
{
	Engine::GetWorld()->LoadScene(_OpenLevelName);
}

void Door::Close()
{
	_AtlasComponent->SetTileIndex(1);
	_bIsOpen = false;
}

void Door::Open()
{
	_AtlasComponent->SetTileIndex(0);
	_bIsOpen = true;
}