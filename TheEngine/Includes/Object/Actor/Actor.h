#pragma once

#include "Object/Object.h"
#include "Object/Actor/IActorWorld.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

namespace NPEngine
{
	class Component;
	class IUpdatableComponent;
	class IDrawableComponent;
	class TransformComponent;

	//Data for new component to add
	struct DataComponentToAdd
	{
	public:
		Component* CurrentComponent = nullptr;
		std::type_index TypeIndex = std::type_index(typeid(void));
		Param Params = Param{};
	};

	//Data for compoennt to delete
	struct DataComponentToDelete
	{
	public:
		std::string ComponentName = "";
		Param Params = Param{};
	};

	//Class with draw and update function, can have components
	class Actor : public Object, public IActorWorld
	{
	private:
		unsigned char _DrawDepth = 0;

		std::string _Name;

	protected:
		TransformComponent* _TransformComponent = nullptr;

	public:
		Actor(const std::string& Name);
		virtual ~Actor() = default;

		//Create a new actor with the same value
		virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

		//Component
		//Add compoennt to this actor
		void AddComponent(Component* Component, const Param& Params = Param{});
		//Delete compoennt at this name
		void DeleteComponentByName(const std::string& Name, const Param& Params = Param{});
		//Create a component with a class
		template <typename T>
		T* CreateComponentOfClass(const std::string& Name, const Param& Params = Param{});
		//---------

		//Take a hit
		virtual void TakeHit(float Damage) {};

	protected:
		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		//Call when the frame start
		virtual void BeginPlay() override;
		//Call each frame
		virtual void Update(float DeltaTime) override;
		//Call each frame for Draw 
		virtual void Draw() override;

	private:
		std::map<std::string, Component*> _Components;
		std::unordered_map<std::type_index, std::vector<Component*>> _ClassComponents;

		std::map<std::string, IUpdatableComponent*> _UpdatableComponent;
		std::map<std::string, IDrawableComponent*> _DrawableComponent;

		std::vector<DataComponentToAdd> _ComponentToAdd;
		std::vector<DataComponentToDelete> _ComponentToDelete;

		//Create all compoennt to add
		virtual void OnCreateComponent() override final;
		//Delete all compoennt to delete
		virtual void OnDeleteComponent() override final;
		
	public:
		//return the current name
		std::string GetName() const { return _Name; }

		virtual void SetDrawDepth(unsigned char DrawDepth) override;
		virtual unsigned char GetDrawDepth() const override { return _DrawDepth; }

		//Component
		Component* GetComponentByName(const std::string& Name) const;
		template <typename T> 
		T* GetComponentOfClass() const;
		template <typename T>
		std::vector<T*> GetAllComponentOfClass() const;
		//---------

		void SetPosition(const Vector2D<float>& Position);
		Vector2D<float> GetPosition() const;
		void SetSize(const Vector2D<float>& Size);
		Vector2D<float> GetSize() const;

	};

	template<typename T>
	inline T* Actor::CreateComponentOfClass(const std::string& Name, const Param& Params)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		T* NewComponent = new T(Name);
		if (!NewComponent) return nullptr;

		AddComponent(NewComponent, Params);
		return NewComponent;
	}

	template<typename T>
	inline T* Actor::GetComponentOfClass() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		std::type_index TypeIndex(typeid(T));
		auto IT = _ClassComponents.find(TypeIndex);

		if (IT != _ClassComponents.end() && !IT->second.empty())
		{
			T* ComponentOfClass = dynamic_cast<T*>(IT->second[0]);
			if (ComponentOfClass) return ComponentOfClass;
		}

		for (auto& IT : _ClassComponents)
		{
			for (Component* BaseComponent : IT.second)
			{
				T* DerivedComponent = dynamic_cast<T*>(BaseComponent);
				if (DerivedComponent) return DerivedComponent;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetAllComponentOfClass() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		std::vector<T*> ComponentsOfClass;

		for (auto& IT : _ClassComponents)
		{
			for (Component* BaseComponent : IT->second)
			{
				T* DerivedComponent = dynamic_cast<T*>(BaseComponent);
				if (!DerivedComponent) break;
				ComponentsOfClass.push_back(DerivedComponent);
			}
		}

		return ComponentsOfClass;
	}
}