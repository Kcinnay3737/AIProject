#include "Object/Actor/Actor.h"
#include "Engine.h"
#include "Object/Component/Component.h"
#include "Object/Component/TransformComponent.h"

using namespace NPEngine;

Actor::Actor(const std::string& Name) : Object()
{
	_Name = Name;
}

//Flow ----------------------------------------------------

bool Actor::Initialise(const Param& Params)
{
	_TransformComponent = CreateComponentOfClass<TransformComponent>(std::string("Transform"), Params);

	auto IT = Params.find(std::string("DrawDepth"));
	if (IT != Params.end())
	{
		int DrawDepth = std::any_cast<int>(IT->second);
		SetDrawDepth(DrawDepth);
	}

	return true;
}

void Actor::Destroy(const Param& Params)
{
	_ClassComponents.clear();

	_UpdatableComponent.clear();
	_DrawableComponent.clear();

	_ComponentToDelete.clear();

	for (DataComponentToAdd& DataComponent : _ComponentToAdd)
	{
		Component* CurrComponent = DataComponent.CurrentComponent;
		if (!CurrComponent) continue;

		IActorComponent* ActorComponent = static_cast<IActorComponent*>(CurrComponent);
		if (ActorComponent)
		{
			ActorComponent->Destroy(Params);
		}

		delete CurrComponent;
	}
	_ComponentToAdd.clear();

	for (auto& IT : _Components)
	{
		Component* CurrComponent = IT.second;
		if (!CurrComponent) continue;

		IActorComponent* ActorComponent = static_cast<IActorComponent*>(CurrComponent);
		if (ActorComponent)
		{
			ActorComponent->Destroy(Params);
		}

		delete ActorComponent;
	}
	_Components.clear();
}

void Actor::BeginPlay()
{
}

void Actor::Update(float DeltaTime)
{
	for (auto& Value : _UpdatableComponent)
	{
		IUpdatableComponent* CurrComponent = Value.second;
		if (!CurrComponent) continue;
		CurrComponent->Update(DeltaTime);
	}
}

void Actor::Draw()
{
	for (auto& Value : _DrawableComponent)
	{
		IDrawableComponent* CurrComponent = Value.second;
		if (!CurrComponent) continue;
		CurrComponent->Draw();
	}
}

//---------------------------------------------------------

//Component -----------------------------------------------

void Actor::AddComponent(Component* Component, const Param& Params)
{
	if (!Component) return;

	std::type_index TypeIndex(typeid(*Component));

	DataComponentToAdd CurrDataComponentToAdd = DataComponentToAdd();
	CurrDataComponentToAdd.CurrentComponent = Component;
	CurrDataComponentToAdd.TypeIndex = TypeIndex;
	CurrDataComponentToAdd.Params = Params;
	_ComponentToAdd.push_back(CurrDataComponentToAdd);

	Engine::GetWorld()->AddActorToCallCreateComponent(GetName());
}

void Actor::DeleteComponentByName(const std::string& Name, const Param& Params)
{
	DataComponentToDelete DataActor = DataComponentToDelete();
	DataActor.ComponentName = Name;
	DataActor.Params = Params;
	_ComponentToDelete.push_back(DataActor);

	Engine::GetWorld()->AddActorToCallDeleteComponent(Name);
}

void Actor::OnCreateComponent()
{
	for (DataComponentToAdd& DataComponent : _ComponentToAdd)
	{
		Component* NewComponent = DataComponent.CurrentComponent;

		if (!NewComponent) continue;

		std::string NewComponentName = NewComponent->GetName();
		IActorComponent* ActorComponent = static_cast<IActorComponent*>(NewComponent);

		//Check if an compoennt already has this name
		Component* CheckComponent = GetComponentByName(NewComponentName);
		if (CheckComponent)
		{
			Engine::GetLogger()->LogMessage("A component already has this name");
			if (ActorComponent)
			{
				ActorComponent->Destroy();
			}
			delete NewComponent;
			continue;
		}

		if (ActorComponent)
		{
			ActorComponent->SetOwner(this);
			if (!ActorComponent->Initialise(DataComponent.Params))
			{
				Engine::GetLogger()->LogMessage("Initialise failed");
				ActorComponent->Destroy();
				delete NewComponent;
				continue;
			}
		}

		IUpdatableComponent* UpdatableComponent = dynamic_cast<IUpdatableComponent*>(NewComponent);
		if (UpdatableComponent)
		{
			_UpdatableComponent[NewComponentName] = UpdatableComponent;
		}

		IDrawableComponent* DrawableComponent = dynamic_cast<IDrawableComponent*>(NewComponent);
		if (DrawableComponent)
		{
			_DrawableComponent[NewComponentName] = DrawableComponent;
		}
		
		_Components[NewComponentName] = NewComponent;
		_ClassComponents[DataComponent.TypeIndex].push_back(NewComponent);
	}
	_ComponentToAdd.clear();
}

void Actor::OnDeleteComponent()
{
	for (DataComponentToDelete& DataComponent : _ComponentToDelete)
	{
		auto ComponentIT = _Components.find(DataComponent.ComponentName);
		if (ComponentIT == _Components.end()) continue;

		Component* ComponentToRemove = ComponentIT->second;

		std::type_index TypeIndex(typeid(*ComponentToRemove));

		auto ClassComponentIT = _ClassComponents.find(TypeIndex);
		if (ClassComponentIT != _ClassComponents.end())
		{
			std::vector<Component*>& ComponentVector = ClassComponentIT->second;
			auto NewEnd = std::remove(ComponentVector.begin(), ComponentVector.end(), ComponentToRemove);
			ComponentVector.erase(NewEnd, ComponentVector.end());
		}

		_Components.erase(ComponentIT);
		_UpdatableComponent.erase(DataComponent.ComponentName);
		_DrawableComponent.erase(DataComponent.ComponentName);

		IActorComponent* ActorComponent = static_cast<IActorComponent*>(ComponentToRemove);
		if (ActorComponent)
		{
			ActorComponent->Destroy(DataComponent.Params);
		}

		delete ComponentToRemove;
	}
	_ComponentToDelete.clear();
}

//---------------------------------------------------------

Actor* Actor::Clone(const std::string& Name, const Param& Params)
{
	Actor* CloneActor = new Actor(Name);
	return CloneActor;
}

void Actor::SetDrawDepth(unsigned char DrawDepth)
{
	_DrawDepth = DrawDepth;

	Engine::GetWorld()->ResetDrawOrder();
}

//Getter, setter -----------------------------------------

Component* Actor::GetComponentByName(const std::string& Name) const
{
	auto IT = _Components.find(Name);
	if (IT == _Components.end()) return nullptr;
	return IT->second;
}

void Actor::SetPosition(const Vector2D<float>& Position)
{
	if (!_TransformComponent) return;
	_TransformComponent->SetPosition(Position);
}

Vector2D<float> Actor::GetPosition() const
{
	if (!_TransformComponent) return Vector2D<float>(0.0f, 0.0f);
	return _TransformComponent->GetPosition();
}

void Actor::SetSize(const Vector2D<float>& Size)
{
	if (!_TransformComponent) return;
	_TransformComponent->SetSize(Size);
}

Vector2D<float> Actor::GetSize() const
{
	if (!_TransformComponent) return Vector2D<float>(0.0f, 0.0f);
	return _TransformComponent->GetSize();
}
