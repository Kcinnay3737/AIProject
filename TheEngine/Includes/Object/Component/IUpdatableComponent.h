#pragma once

namespace NPEngine
{
	//Interface class for update the component
	class IUpdatableComponent
	{
		friend class Actor;
	private:
		//Call each frame for update the component
		virtual void Update(float DeltaTime) = 0;
	};
}