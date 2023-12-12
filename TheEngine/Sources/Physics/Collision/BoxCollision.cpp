#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Actor/Actor.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Component/PhysicsComponent.h"
#include "Engine.h"

using namespace NPEngine;

BoxCollision::BoxCollision(Actor* Owner, PhysicsComponent* OwnerPhysicsComponent)
{
    _OwnerActor = Owner;
    _OwnerPhysicsComponent = OwnerPhysicsComponent;
}

BoxCollision::~BoxCollision()
{
}

CollisionData BoxCollision::CheckCollisionWithPoint(const ICollision& OtherCollision) const
{
    if (OtherCollision.GetCollisionType() != ECollisionType::Point) return CollisionData();
    const PointCollision& OtherPointCollision = static_cast<const PointCollision&>(OtherCollision);

	if (_OwnerPhysicsComponent)
	{
		if (_OwnerPhysicsComponent->GetIgnoreActorClass(OtherCollision.GetOwner())) return CollisionData();
	}

    CollisionData CurrentCollisionData = CollisionData();

	Vector2D<float> Position = GetPosition();
	Vector2D<float> Size = GetSize();

    Vector2D<float> OtherPoint = OtherPointCollision.GetPosition();

    //Check if collide
	if (OtherPoint.X >= Position.X &&
		OtherPoint.X <= Position.X + Size.X &&
		OtherPoint.Y >= Position.Y &&
		OtherPoint.Y <= Position.Y + Size.Y)
	{
		CurrentCollisionData.bCollision = true;
		CurrentCollisionData.OtherActor = OtherCollision.GetOwner();

        //Calcule correction
        if (_OwnerPhysicsComponent && _OwnerPhysicsComponent->GetIsPhysicsVolume() && OtherCollision.GetOwnerPhysicsComponent() && OtherCollision.GetOwnerPhysicsComponent()->GetIsPhysicsVolume())
        {
			Vector2D<float> Center = Position + (Size / 2);

			float DirectionX = (OtherPoint.X < Center.X) ? -1.0f : 1.0f;
			float DirectionY = (OtherPoint.Y < Center.Y) ? -1.0f : 1.0f;

			float OverlapX = std::max(0.0f, std::abs(Center.X - OtherPoint.X) - Size.X / 2.0f);
			float OverlapY = std::max(0.0f, std::abs(Center.Y - OtherPoint.Y) - Size.Y / 2.0f);

			CurrentCollisionData.MovementCorrection.X += OverlapX * DirectionX;
			CurrentCollisionData.MovementCorrection.Y += OverlapY * DirectionY;
        }
	}

    return CurrentCollisionData;
}

CollisionData BoxCollision::CheckCollisionWithBox(const ICollision& OtherCollision) const
{
    if (OtherCollision.GetCollisionType() != ECollisionType::Box) return CollisionData();
    const BoxCollision& OtherBoxCollision = static_cast<const BoxCollision&>(OtherCollision);

    if (_OwnerPhysicsComponent)
    {
        if (_OwnerPhysicsComponent->GetIgnoreActorClass(OtherCollision.GetOwner())) return CollisionData();
    }

    CollisionData CurrentCollisionData = CollisionData();

	Vector2D<float> Position = GetPosition();
	Vector2D<float> Size = GetSize();

    Vector2D<float> OtherPosition = OtherBoxCollision.GetPosition();
    Vector2D<float> OtherSize = OtherBoxCollision.GetSize();

    //Check collision
    if (Position.X < OtherPosition.X + OtherSize.X &&
        Position.X + Size.X > OtherPosition.X &&
        Position.Y < OtherPosition.Y + OtherSize.Y &&
        Position.Y + Size.Y > OtherPosition.Y)
    {
        CurrentCollisionData.bCollision = true;
        CurrentCollisionData.OtherActor = OtherCollision.GetOwner();

        //Calcule correction
        if (_OwnerPhysicsComponent && _OwnerPhysicsComponent->GetIsPhysicsVolume() && OtherCollision.GetOwnerPhysicsComponent() && OtherCollision.GetOwnerPhysicsComponent()->GetIsPhysicsVolume())
        {
			//Movement correction calcule
			Vector2D<float> Center = Position + (Size / 2);
			Vector2D<float> OtherCenter = OtherPosition + (OtherSize / 2);

			float DistanceX = Center.X - OtherCenter.X;
			float DistanceY = Center.Y - OtherCenter.Y;

			float OverlapX = Size.X / 2 + OtherSize.X / 2 - std::abs(DistanceX);
			float OverlapY = Size.Y / 2 + OtherSize.Y / 2 - std::abs(DistanceY);

			if (OverlapX < OverlapY)
			{
				CurrentCollisionData.MovementCorrection.X += OverlapX * (DistanceX > 0 ? 1 : -1);
			}
			else
			{
				CurrentCollisionData.MovementCorrection.Y += OverlapY * (DistanceY > 0 ? 1 : -1);
			}
        }
    }

    return CurrentCollisionData;
}

CollisionData BoxCollision::CheckCollisionWithSphere(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData BoxCollision::CheckCollisionWithLine(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData BoxCollision::CheckCollisionWithGrid(const ICollision& OtherCollision) const
{
	if (OtherCollision.GetCollisionType() != ECollisionType::Grid) return CollisionData();
	const GridCollision& OtherGridCollision = static_cast<const GridCollision&>(OtherCollision);

	if (_OwnerPhysicsComponent)
	{
		if (_OwnerPhysicsComponent->GetIgnoreActorClass(OtherCollision.GetOwner())) return CollisionData();
	}

	CollisionData CurrentCollisionData = CollisionData();

	Vector2D<float> Position = GetPosition();
	Vector2D<float> Size = GetSize();

    const std::vector<std::vector<bool>>& OtherGrid = OtherGridCollision.GetGrid();

    int Y = 0;
    for (const std::vector<bool>& Line : OtherGrid)
    {
        int X = 0;
        for (const bool& Cell : Line)
        {
            if (Cell)
            {
                BoxCollision OtherBoxCollision = OtherGridCollision.GetBoxCollisionAt(Vector2D<int>(X, Y));
                CollisionData CellCollisionData = this->CheckCollisionWithBox(OtherBoxCollision);
                if (CellCollisionData.bCollision)
                {
                    CurrentCollisionData.bCollision = true;
                    CurrentCollisionData.OtherActor = OtherCollision.GetOwner();

					if (std::abs(CellCollisionData.MovementCorrection.X) > std::abs(CurrentCollisionData.MovementCorrection.X))
					{
                        CurrentCollisionData.MovementCorrection.X = CellCollisionData.MovementCorrection.X;
					}

					if (std::abs(CellCollisionData.MovementCorrection.Y) > std::abs(CurrentCollisionData.MovementCorrection.Y))
					{
                        CurrentCollisionData.MovementCorrection.Y = CellCollisionData.MovementCorrection.Y;
					}
                }
            }
            X++;
        }
        X = 0;
        Y++;
    }

    return CurrentCollisionData;
}

void BoxCollision::DrawCollision()
{
    Rectangle2D<float> CurrRectangle = Rectangle2D<float>(GetPosition(), GetSize());

    Engine::GetGraphics()->DrawRect(CurrRectangle);
}

Vector2D<float> BoxCollision::GetPosition() const
{
    Vector2D<float> CurrPosition = Vector2D<float>(0.0f, 0.0f);

    if (_OwnerActor)
    {
        TransformComponent* CurrTransformComponent = _OwnerActor->GetComponentOfClass<TransformComponent>();
        if (CurrTransformComponent)
        {
            CurrPosition += CurrTransformComponent->GetPosition();
        }
    }
    CurrPosition += _PositionOffset;

    return CurrPosition;
}

Vector2D<float> BoxCollision::GetSize() const
{
	Vector2D<float> CurrSize = Vector2D<float>(0.0f, 0.0f);

	if (_OwnerActor)
	{
		TransformComponent* CurrTransformComponent = _OwnerActor->GetComponentOfClass<TransformComponent>();
		if (CurrTransformComponent)
		{
			CurrSize += CurrTransformComponent->GetSize();
		}
	}
	CurrSize += _SizeOffset;

	return CurrSize;
}