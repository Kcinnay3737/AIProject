#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

PointCollision::PointCollision(Actor* Owner, PhysicsComponent* OwnerPhysicsComponent)
{
    _Owner = Owner;
	_OwnerPhysicsComponent = OwnerPhysicsComponent;
}

PointCollision::~PointCollision()
{
}

CollisionData PointCollision::CheckCollisionWithPoint(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithBox(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithSphere(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithLine(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithGrid(const ICollision& OtherCollision) const
{
    return CollisionData();
}

void PointCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawPoint(GetPosition());
}

void PointCollision::SetPositionOffset(const Vector2D<float>& PositionOffset)
{
    _PositionOffset = PositionOffset;
}

Vector2D<float> PointCollision::GetPosition() const
{
	Vector2D<float> CurrPoint = Vector2D<float>(0.0f, 0.0f);

	if (_Owner)
	{
		TransformComponent* CurrTransformComponent = _Owner->GetComponentOfClass<TransformComponent>();
		if (CurrTransformComponent)
		{
			CurrPoint += CurrTransformComponent->GetPosition();
		}
	}
	CurrPoint += _PositionOffset;

	return CurrPoint;
}
