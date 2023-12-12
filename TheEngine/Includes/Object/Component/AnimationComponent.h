#pragma once

#include "Object/Component/AtlasComponent.h"

namespace NPEngine
{
	//Structure for switch animation
	struct AnimationSwitch
	{
	public:
		bool bSwitchAnimation = false;
		std::string SwitchAnimationName = "";
		int SwitchIndex = 0;
	};

	//Structure with all animation data
	struct AnimationData
	{
		friend class AnimationComponent;
	public:
		float FrameInterval = 0.0f;
		int StartIndex = 0;
		int EndIndex = 0;
		bool bLoop = true;

		AnimationSwitch SwitchAnimationData = AnimationSwitch();

		Flip AnimationFlip = Flip();

		Delegate<void, int, const std::string&> AnimationObserver = Delegate<void, int, const std::string&>();

		//Add a new frame to call AnimationObserver
		void AddFrameToCallObserver(int Frame);
		//Remove a frame to call AnimationObeserver 
		void RemoveFrameToCallObserver(int Frame);
		//Clear all frame in FrameToCallObserver dictonary
		void ClearAllFrameToCallObserver();

	private:
		std::unordered_map<int, bool> FrameToCallObserver;
		std::string AnimationName = "";
	};

	//Component class for play a animation
	class AnimationComponent : public AtlasComponent, public IUpdatableComponent
	{
	private:
		AnimationData _BaseAnimationData = AnimationData();

		AnimationData& _CurrentAnimation = _BaseAnimationData;

		std::map<std::string, AnimationData> _Animations;

		float _CurrentFrameTime = 0.0f;

	public:
		AnimationComponent(const std::string& Name);
		virtual ~AnimationComponent() = default;

		//Add a new animation to _Animations
		void AddAnimation(const std::string& AnimationName, AnimationData& NewAnimationData);
		//Remove a animation to _Animation
		void RemoveAnimation(const std::string& AnimationName);

		//Return the animation data at the name
		AnimationData& GetAnimationData(const std::string& AnimationName);
		//Set the current animation with the animationdata at this name
		void SetCurrentAnimation(const std::string AnimationName);

	private:
		void Update(float DeltaTime) override;

	};
}