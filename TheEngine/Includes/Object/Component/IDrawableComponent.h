#pragma once

namespace NPEngine
{
	//A interface for draw a component
	class IDrawableComponent
	{
		friend class Actor;
	private:
		//Call each frame for draw the current component
		virtual void Draw() = 0;
	};
}