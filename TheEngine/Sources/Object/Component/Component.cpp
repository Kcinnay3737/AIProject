#include "Object/Component/Component.h"

using namespace NPEngine;

Component::Component(const std::string& Name) : Object()
{
	_Name = Name;
}

bool Component::Initialise(const Param& Params)
{
	return true;
}

void Component::Destroy(const Param& Params)
{
}

void Component::SetOwner(Actor* Owner)
{
	_OwnerActor = Owner;
}
