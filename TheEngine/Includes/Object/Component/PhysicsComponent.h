#pragma once

#include "Object/Component/Component.h"
#include "Physics/PhysicsEnum.h"
#include "Physics/Collision/CollisionData.h"
#include "Physics/Collision/ICollision.h"
#include "Physics/MovementData.h"
#include <typeindex>
#include <typeinfo>

namespace NPEngine
{
	//A compoenent for calculate the physics
	class PhysicsComponent : public Component, public IDrawableComponent
	{
	public:
		//Call when the component collide
		Delegate<void, const std::vector<CollisionData>&> OnCollision;

	private:
		bool _bDrawCollision = false;
		ECollisionType _CollisionType = ECollisionType::None;

		ICollision* _Collision = nullptr;

		MovementData _MovementData = MovementData();

		float _MaxVelocityMagnetude = 100.0f;

		bool _bIsMovable = true;
		bool _bIsPhysicsVolume = true;
		bool _bCalculeCollision = true;
		bool _bCorrectMovement = true;

		std::unordered_map<std::type_index, bool> _IgnoreActorClass;

	public:
		PhysicsComponent(const std::string& Name);
		virtual ~PhysicsComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		virtual void Draw() override;

		//Correct the velocity with the max speed
		void CorrectMagnetude();

	public:
		//Set if draw the collision or not
		void SetDrawCollision(bool bDrawCollision) { _bDrawCollision = bDrawCollision; }

		//Return the current velocity
		Vector2D<float> GetVelocity();
		//Set the current velocity
		void SetVelocity(const Vector2D<float>& NewVelocity);
		//Add the valu to the current velocity
		void AddVelocity(const Vector2D<float>& VelociyToAdd);
		//Apply the velocity
		void ApplyVelocity(float DeltaTime);

		//Correct the movement with the collision
		void CorrectMovement(const std::vector<CollisionData>& AllCollisionData);

		//Return if the compoennt is movable
		bool GetIsMovable() const { return _bIsMovable; }
		//Set if the component is movable
		void SetIsMovable(bool IsMovable) { _bIsMovable = IsMovable; }

		//Return if the component calcule the collision
		bool GetIsCalculeCollision() const { return _bCalculeCollision; }
		//Set if the component calcule the collision
		void SetIsCalculeCollision(bool bCalculeCollision) { _bCalculeCollision = bCalculeCollision; }

		//Return if the component is a physics volume
		bool GetIsPhysicsVolume() const { return _bIsPhysicsVolume; }
		//Set if the component is a physics volume
		void SetIsPhysicsVolume(bool bIsPhyscicsVolume) { _bIsPhysicsVolume = bIsPhyscicsVolume; }

		//Return if the component need to correct movement 
		bool GetCorrectMovement() const { return _bCorrectMovement; }
		//Set if the component need to correct movement
		void SetCorrectMovement(bool bCorrectMovement) { _bCorrectMovement = bCorrectMovement; }

		//Return all collision with this component 
		std::vector<CollisionData> CheckCollision();

		//Set the collision type
		void SetCollision(const ECollisionType& CollisionType);
		//Return the collision
		ICollision* GetCollision() const;

		//Set the max velocity for this component
		void SetMaxVelocityMagnetude(float MaxVelocityMagnetude) { _MaxVelocityMagnetude = MaxVelocityMagnetude; }
		//Return the max velocity for this component 
		float GetMaxVelocityMagntude() const { return _MaxVelocityMagnetude; }

		//Add actor to ignore during collisiion
		template <typename T>
		void AddIgnoreActorClass();
		//Add actor to ignore during collision
		void AddIgnoreActorClass(std::type_index TypeIndex);
		//Remove ignore actor class to ignore during collision
		template <typename T>
		void RemoveIgnoreActorClass();
		//Remove ignore actor class to ignore during collision
		void RemoveIgnoreActorClass(std::type_index TypeIndex);

		//Return if the param actor is ignore during the collision
		bool GetIgnoreActorClass(Actor* CheckActor);

	};

	template<typename T>
	inline void PhysicsComponent::AddIgnoreActorClass()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		std::type_index TypeIndex(typeid(T));

		_IgnoreActorClass[TypeIndex] = true;
	}

	template<typename T>
	inline void PhysicsComponent::RemoveIgnoreActorClass()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		std::type_index TypeIndex(typeid(T));

		_IgnoreActorClass.erase(TypeIndex);
	}
}