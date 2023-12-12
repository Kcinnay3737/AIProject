#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	class Actor;
	
	//A interface for a component on a actor
	class IActorComponent
	{
		friend class Actor;
	public:
		virtual ~IActorComponent() = default;

	private:
		//Call by the actor for initialise the component
		virtual bool Initialise(const Param& Params = Param{}) = 0;
		//Call by the actor for destroy compoennt
		virtual void Destroy(const Param& Params = Param{}) = 0;

		//Set the current compoennt owner
		virtual void SetOwner(Actor* Owner) = 0;
	};
}