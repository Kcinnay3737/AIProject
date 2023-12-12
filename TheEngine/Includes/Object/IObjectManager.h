#pragma once

namespace NPEngine
{
	class Object;

	//A interface for manage object
	class IObjectManager
	{
		friend class Object;
	public:
		//Return the current object at this ID
		virtual Object* GetObject(size_t ID) = 0;

	private:
		//Add an object with ID
		virtual void AddObject(size_t ID, Object* NewObject) = 0;
		//Remove the object at the ID
		virtual void RemoveId(size_t ID) = 0;
	};
}