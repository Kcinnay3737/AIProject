#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

SphereCollision::SphereCollision(Actor* Owner)
{
    _Owner = Owner;
}

SphereCollision::~SphereCollision()
{
}

CollisionData SphereCollision::CheckCollisionWithPoint(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithBox(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithSphere(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithLine(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithGrid(const ICollision& OtherCollision) const
{
    return CollisionData();
}

void SphereCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawCircle(GetPosition(), _Ray);
}

void SphereCollision::SetPositionOffset(const Vector2D<float>& PositionOffset)
{
    _PositionOffset = PositionOffset;
}

Vector2D<float> SphereCollision::GetPosition() const
{
	Vector2D<float> CurrPosition = Vector2D<float>(0.0f, 0.0f);

	if (_Owner)
	{
		TransformComponent* CurrTransformComponent = _Owner->GetComponentOfClass<TransformComponent>();
		if (CurrTransformComponent)
		{
			CurrPosition += CurrTransformComponent->GetPosition();
		}
	}
	CurrPosition += _PositionOffset;

	return CurrPosition;
}
