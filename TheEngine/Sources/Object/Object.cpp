#include "Object/Object.h"
#include "Engine.h"

using namespace NPEngine;

size_t Object::_CurrentID = 0;
std::queue<size_t> Object::_IDFree = std::queue<size_t>();

Object::Object()
{
	_ID = GetNextID();

	World* CurrWorld = Engine::GetWorld();
	if (CurrWorld)
	{
		IObjectManager* ObjectManager = static_cast<IObjectManager*>(CurrWorld);
		if (ObjectManager)
		{
			ObjectManager->AddObject(_ID, this);
		}
	}
}

Object::~Object()
{
	World* CurrWorld = Engine::GetWorld();
	if (CurrWorld)
	{
		IObjectManager* ObjectManager = static_cast<IObjectManager*>(CurrWorld);
		if (ObjectManager)
		{
			ObjectManager->RemoveId(_ID);
		}
	}

	Object::_IDFree.push(_ID);
}

size_t Object::GetNextID()
{
	if (!Object::_IDFree.empty())
	{
		size_t RecycledID = Object::_IDFree.front();
		Object::_IDFree.pop();
		return RecycledID;
	}

	return Object::_CurrentID++;
}