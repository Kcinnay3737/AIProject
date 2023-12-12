#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class Actor;

	//A class for line collision
	class LineCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Line;

		Actor* _Owner = nullptr;
		PhysicsComponent* _OwnerPhysicsComponent = nullptr;

		Vector2D<float> _StartPointOffset = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _EndPointOffset = Vector2D<float>(0.0f, 0.0f);

	public:
		LineCollision(Actor* Owner);
		virtual ~LineCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const override;

		virtual void DrawCollision() override;

		//Set the offset for the start point
		void SetStartPointOffset(Vector2D<float> StartPointOffset) { _StartPointOffset = StartPointOffset; }
		//Get the offset for the start point
		Vector2D<float> GetStartPointOffset() const { return _StartPointOffset; }
		//Return the start point
		Vector2D<float> GetStartPoint() const;

		//Set offset for the end point
		void SetEndPointOffset(Vector2D<float> EndPointOffset) { _EndPointOffset = EndPointOffset; }
		//Return the offset for the end point
		Vector2D<float> GetEndPointOffset() const { return _EndPointOffset; }
		//Return the end point
		Vector2D<float> GetEndPoint() const;

		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }

		virtual Actor* GetOwner() const override { return _Owner; }
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const  override { return _OwnerPhysicsComponent; }
	};
}