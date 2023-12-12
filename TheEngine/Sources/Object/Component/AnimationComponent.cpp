#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

AnimationComponent::AnimationComponent(const std::string& Name) : AtlasComponent(Name)
{
}

void AnimationComponent::AddAnimation(const std::string& AnimationName, AnimationData& NewAnimationData)
{
	NewAnimationData.AnimationName = AnimationName;
	_Animations[AnimationName] = NewAnimationData;
}

void AnimationComponent::RemoveAnimation(const std::string& AnimationName)
{
	_Animations.erase(AnimationName);
}

AnimationData& AnimationComponent::GetAnimationData(const std::string& AnimationName)
{
	auto IT = _Animations.find(AnimationName);
	if (IT == _Animations.end()) return _BaseAnimationData;
	return IT->second;
}

void AnimationComponent::SetCurrentAnimation(const std::string AnimationName)
{
	auto ITAnimation = _Animations.find(AnimationName);
	if (ITAnimation == _Animations.end()) return;

	_CurrentAnimation = ITAnimation->second;
	_CurrentFrameTime = 0.0f;
	SetTileIndex(_CurrentAnimation.StartIndex);
	SetFlip(_CurrentAnimation.AnimationFlip);

	auto IT = _CurrentAnimation.FrameToCallObserver.find(GetTileIndex());
	if (IT != _CurrentAnimation.FrameToCallObserver.end())
	{
		_CurrentAnimation.AnimationObserver.Broadcast(GetTileIndex(), _CurrentAnimation.AnimationName);
	}
}

void AnimationComponent::Update(float DeltaTime)
{
	if (GetTileIndex() == _CurrentAnimation.EndIndex && !_CurrentAnimation.bLoop) return;

	_CurrentFrameTime += DeltaTime;

	if (_CurrentFrameTime >= _CurrentAnimation.FrameInterval)
	{
		_CurrentFrameTime = 0.0f;

		if (_CurrentAnimation.SwitchAnimationData.bSwitchAnimation && GetTileIndex() == _CurrentAnimation.SwitchAnimationData.SwitchIndex)
		{
			SetCurrentAnimation(_CurrentAnimation.SwitchAnimationData.SwitchAnimationName);
		}
		else
		{
			if (GetTileIndex() >= _CurrentAnimation.EndIndex)
			{
				SetTileIndex(_CurrentAnimation.StartIndex);
			}
			else
			{
				SetTileIndex(GetTileIndex() + 1);
			}

			auto IT = _CurrentAnimation.FrameToCallObserver.find(GetTileIndex());
			if (IT != _CurrentAnimation.FrameToCallObserver.end() && IT->second)
			{
				_CurrentAnimation.AnimationObserver.Broadcast(GetTileIndex(), _CurrentAnimation.AnimationName);
			}
		}
	}
}

//------------------------------------------------------------------

void AnimationData::AddFrameToCallObserver(int Frame)
{
	FrameToCallObserver[Frame] = true;
}

void AnimationData::RemoveFrameToCallObserver(int Frame)
{
	FrameToCallObserver.erase(Frame);
}

void AnimationData::ClearAllFrameToCallObserver()
{
	FrameToCallObserver.clear();
}
