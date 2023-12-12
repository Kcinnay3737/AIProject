#pragma once

#include <queue>
#include "Utility/Utility.h"

namespace NPEngine
{
	//The base class
	class Object
	{
	private:
		static size_t _CurrentID;
		static std::queue<size_t> _IDFree;

		size_t _ID;

	public:
		Object();
		virtual ~Object();

		//Return the ID
		size_t GetID() const { return _ID; }

	private:
		//Generate a new unique ID
		size_t GetNextID();
	};
}