#include "Physics/Physics.h"
#include "Object/Actor/Actor.h"
#include "Object/Component/PhysicsComponent.h"
#include "Physics/Collision/ICollision.h"

using namespace NPEngine;

bool Physics::Initialize(const Param& Params)
{
    return true;
}

void Physics::Shutdown(const Param& Params)
{
}

void Physics::UpdatePhysics(float DeltaTime)
{
    std::map<PhysicsComponent*, std::vector<CollisionData>> MapCurrentCollision;

    for (auto& IT : _PhysicsActors)
    {
        PhysicsComponent* CurrPhysicsComponent = IT.second;
        if(!CurrPhysicsComponent) continue;

		CurrPhysicsComponent->ApplyVelocity(DeltaTime);

        if (CurrPhysicsComponent->GetIsCalculeCollision())
        {
            std::vector<CollisionData> CurrCollisionsData = CurrPhysicsComponent->CheckCollision();
            MapCurrentCollision[CurrPhysicsComponent] = CurrCollisionsData;
        }
    }

    for (auto& IT : MapCurrentCollision)
    {
		PhysicsComponent* CurrPhysicsComponent = IT.first;
		if (!CurrPhysicsComponent) continue;
        CurrPhysicsComponent->CorrectMovement(IT.second);
    }
}

void Physics::AddPhysicsActor(const std::string& ActorName, PhysicsComponent* PhysicsComponentToAdd)
{
    if (!PhysicsComponentToAdd) return;

    _PhysicsActors[ActorName] = PhysicsComponentToAdd;
}

void Physics::RemovePhysicsActor(const std::string& Name)
{
    _PhysicsActors.erase(Name);
}

std::vector<CollisionData> Physics::CheckCollisionWith(const ICollision* Collision)
{
    std::vector<CollisionData> CollisionsData;

    if (!Collision) return CollisionsData;

    for (auto& IT : _PhysicsActors)
    {
        const PhysicsComponent* OtherPhysicsComponent = IT.second;
        const ICollision* OtherCollision = OtherPhysicsComponent->GetCollision();
        if(!OtherCollision || OtherCollision == Collision) continue;
        
        CollisionData CurrCollisionData = CollisionData();

        switch (OtherCollision->GetCollisionType())
        {
        case ECollisionType::Box:
            CurrCollisionData = Collision->CheckCollisionWithBox(*OtherCollision);
            break;
        case ECollisionType::Grid:
            CurrCollisionData = Collision->CheckCollisionWithGrid(*OtherCollision);
            break;
        case ECollisionType::Line:
            CurrCollisionData = Collision->CheckCollisionWithLine(*OtherCollision);
            break;
        case ECollisionType::Point:
            CurrCollisionData = Collision->CheckCollisionWithPoint(*OtherCollision);
            break;
        case ECollisionType::Sphere:
            CurrCollisionData = Collision->CheckCollisionWithSphere(*OtherCollision);
            break;
        case ECollisionType::None:
            break;
        }

        if (CurrCollisionData.bCollision)
        {
            CollisionsData.push_back(CurrCollisionData);
        }
    }
    
    return CollisionsData;
}
