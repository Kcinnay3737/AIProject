#include "Physics/Collision/GridCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

GridCollision::GridCollision(Actor* Owner, PhysicsComponent* OwnerPhysicsComponent)
{
    _OwnerActor = Owner;
    _OwnerPhysicsComponent = OwnerPhysicsComponent;
}

GridCollision::~GridCollision()
{
}

CollisionData GridCollision::CheckCollisionWithPoint(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithBox(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithSphere(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithLine(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithGrid(const ICollision& OtherCollision) const
{
    return CollisionData();
}

//Pas encore implementer
std::vector<Vector2D<int>> GridCollision::GetIndexInRect(const Rectangle2D<float>& Rect) const
{
    //Vector2D<float> StartPosition = Vector2D<float>(0.0f, 0.0f);

    //if (_OwnerActor)
    //{
    //    TransformComponent* CurrTransformComponent = _OwnerActor->GetComponentOfClass<TransformComponent>();
    //    if (CurrTransformComponent)
    //    {
    //        StartPosition += CurrTransformComponent->GetPosition();
    //    }
    //}
    //StartPosition += _PositionOffset;

    return std::vector<Vector2D<int>>();
}

void GridCollision::DrawCollision()
{
    int Y = 0;
    for (std::vector<bool>& Lines : _Grid)
    {
        int X = 0;
        for (bool IsCollide : Lines)
        {
            if (IsCollide)
            {
                BoxCollision CurrBoxCollision = GetBoxCollisionAt(Vector2D<int>(X, Y));
                CurrBoxCollision.DrawCollision();
            }
            X++;
        }
        Y++;
    }
}

BoxCollision GridCollision::GetBoxCollisionAt(Vector2D<int> CellPosition) const
{
    Vector2D<float> Position = _CellSize;
    Position.X *= CellPosition.X;
    Position.Y *= CellPosition.Y;

    Position += _PositionOffset;

    BoxCollision NewBoxCollision = BoxCollision(_OwnerActor, _OwnerPhysicsComponent);

    NewBoxCollision.SetPositionOffset(Position);
    NewBoxCollision.SetSizeOffset(_CellSize);

    return NewBoxCollision;
}
