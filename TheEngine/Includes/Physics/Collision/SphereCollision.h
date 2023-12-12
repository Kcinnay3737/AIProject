#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class Actor;

	//A class for a sphere collision
	class SphereCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Sphere;

		Actor* _Owner = nullptr;
		PhysicsComponent* _OwnerPhysicsComponent = nullptr;

		Vector2D<float> _PositionOffset = Vector2D<float>(0.0f, 0.0f);
		float _Ray = 0.0f;

	public:
		SphereCollision(Actor* Owner);
		virtual ~SphereCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const override;

		virtual void DrawCollision() override;

		//Set the current position offset
		void SetPositionOffset(const Vector2D<float>& PositionOffset);
		//Return the current position offset
		Vector2D<float> GetPositionOffset() const { return _PositionOffset; }
		//Return the current position
		Vector2D<float> GetPosition() const;

		//Set the current ray value
		void SetRay(float Ray) { _Ray = Ray; }
		//return the current ray value
		float GetRay() const { return _Ray; }

		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }

		virtual Actor* GetOwner() const override { return _Owner; }
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const  override { return _OwnerPhysicsComponent; }
	};
}