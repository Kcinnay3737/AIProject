#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	//Scene provider interface friend with world class
	class ISceneProvider
	{
		friend class World;
	public:
		virtual ~ISceneProvider() = default;

	private:
		virtual bool Initialize(const Param& Params = Param{}) = 0;
		virtual void Destroy(const Param& Params = Param{}) = 0;

		//Load all all data in the current scene
		virtual void Load(const Param& Params = Param{}) = 0;
		
	};
}