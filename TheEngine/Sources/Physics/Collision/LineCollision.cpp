#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

LineCollision::LineCollision(Actor* Owner)
{
    _Owner = Owner;
}

LineCollision::~LineCollision()
{
}

CollisionData LineCollision::CheckCollisionWithPoint(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithBox(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithSphere(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithLine(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithGrid(const ICollision& OtherCollision) const
{
    return CollisionData();
}

void LineCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawLine(GetStartPoint(), GetEndPoint());
}

Vector2D<float> LineCollision::GetStartPoint() const
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
    CurrPoint += _StartPointOffset;

    return CurrPoint;
}

Vector2D<float> LineCollision::GetEndPoint() const
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
	CurrPoint += _EndPointOffset;

	return CurrPoint;
}