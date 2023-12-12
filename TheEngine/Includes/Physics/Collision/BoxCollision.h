#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class Actor;
	class PhysicsComponent;

	//A collision class dor the box
	class BoxCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Box;

		Actor* _OwnerActor = nullptr;
		PhysicsComponent* _OwnerPhysicsComponent = nullptr;

		Vector2D<float> _PositionOffset = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _SizeOffset = Vector2D<float>(0.0f, 0.0f);

	public:
		BoxCollision(Actor* Owner, PhysicsComponent* OwnerPhysicsComponent);
		virtual ~BoxCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const override;

		virtual void DrawCollision() override;

		//Set the position offset
		void SetPositionOffset(Vector2D<float> PositionOffset) { _PositionOffset = PositionOffset; }
		//Get the position offset
		Vector2D<float> GetPositionOffset() const { return _PositionOffset; }
		//Return the position
		Vector2D<float> GetPosition() const;

		//Set the size offset
		void SetSizeOffset(Vector2D<float> SizeOffset) { _SizeOffset = SizeOffset; }
		//Return the size offset
		Vector2D<float> GetSizeOffset() const { return _SizeOffset; }
		//Return the size
		Vector2D<float> GetSize() const;

		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }

		virtual Actor* GetOwner() const override { return _OwnerActor; }
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const  override { return _OwnerPhysicsComponent; }
	};
}