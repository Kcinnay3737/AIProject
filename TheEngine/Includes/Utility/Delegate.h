#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <cstddef>

namespace NPEngine
{
	//Class for containing functions and casting them
	template<typename ReturnType, typename... Args>
	class Delegate
	{
	private:
		//Return the id for a function in a instance object
		template<typename T>
		size_t GetHash(T* Instance, ReturnType(T::* Method)(Args...))
		{
			std::hash<std::uintptr_t> PtrHasher;

			std::uintptr_t InstancePtr = reinterpret_cast<std::uintptr_t>(Instance);
			size_t InstanceHash = PtrHasher(InstancePtr);

			std::uintptr_t MethodPtr = reinterpret_cast<std::uintptr_t&>(Method);
			size_t MethodHash = PtrHasher(MethodPtr);

			return InstanceHash ^ (MethodHash << 1);
		}

		//return the id for a function
		size_t GetHash(ReturnType(*Method)(Args...))
		{
			std::hash<ReturnType(*)(Args...)> Hasher;
			return Hasher(Method);
		}

		//Dictionary id/function
		std::unordered_map<size_t, std::function<ReturnType(Args...)>> Functions;

	public:
		//Add a new instance function in the function dictionary
		template<typename T>
		void AddFunction(T* Instance, ReturnType(T::* Method)(Args...)) 
		{
			size_t Key = GetHash<T>(Instance, Method);
			Functions[Key] = [Instance, Method](Args... args) -> ReturnType 
			{
				return (Instance->*Method)(args...);
			};
		}

		//Add a new function in the function dictionary
		void AddFunction(ReturnType(*Function)(Args...)) 
		{
			size_t Key = GetHash(Function);
			Functions[Key] = Function;
		}

		//Remove instance function in the function dictionary
		template<typename T>
		void RemoveFunction(T* Instance, ReturnType(T::* Method)(Args...)) 
		{
			size_t Key = GetHash<T>(Instance, Method);
			Functions.erase(Key);
		}

		//Remove function in the function dictionary
		void RemoveFunction(ReturnType(*Function)(Args...)) 
		{
			size_t Key = GetHash(Function);
			Functions.erase(Key);
		}

		//Broadcast all function with return value
		std::vector<ReturnType> BroadcastResult(Args... args)
		{
			std::vector<ReturnType> Results;
			Results.reserve(Functions.size());
			for (auto& [Key, Function] : Functions)
			{
				if (Function != nullptr)
				{
					try
					{
						Results.push_back(Function(args...));
					}
					catch (...)
					{
						
					}
				}
			}
			return Results;
		}

		//Broadcast all function without return value
		void Broadcast(Args... args)
		{
			for (auto& [Key, Function] : Functions)
			{
				if (Function != nullptr)
				{
					try
					{
						Function(args...);
					}
					catch (...)
					{

					}
				}
			}
		}
	};
}