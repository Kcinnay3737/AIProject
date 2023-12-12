#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	//A interface for a actor in world
	class IActorWorld
	{
		friend class World;
		friend class InstanceManager;
	public:
		virtual ~IActorWorld() = default;

		//Set the draw depth
		virtual void SetDrawDepth(unsigned char DrawDepth) = 0;
		//Return the draw depth
		virtual unsigned char GetDrawDepth() const = 0;

	private:
		virtual bool Initialise(const Param& Params = Param{}) = 0;
		virtual void Destroy(const Param& Params = Param{}) = 0;

		//Call in start on first frame
		virtual void BeginPlay() = 0;

		//Call each frame
		virtual void Update(float dt) = 0;
		
		//Call each frame for draw
		virtual void Draw() = 0;

		//Create all component to add
		virtual void OnCreateComponent() = 0;
		//Delete all component to delete
		virtual void OnDeleteComponent() = 0;
	};
}