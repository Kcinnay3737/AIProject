#include "Object/Component/SpriteComponent.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

SpriteComponent::SpriteComponent(const std::string& Name) : Component(Name)
{
}

void SpriteComponent::LoadTexture(const std::string& TexturePath)
{
	_TextureID = Engine::GetGraphics()->LoadTexture(TexturePath.c_str());
	_bTextureIsLoaded = true;
}

bool SpriteComponent::Initialise(const Param& Params)
{
	Component::Initialise(Params);

	auto IT = Params.find("TexturePath");
	if (IT != Params.end())
	{
		const std::string& TexturePath = std::any_cast<const std::string&>(IT->second);
		LoadTexture(TexturePath);
	}

	return true;
}

void SpriteComponent::Draw()
{
	if (!_bDraw) return;

	if (_bTextureIsLoaded)
	{
		Engine::GetGraphics()->DrawTexture(_TextureID, Rectangle2D<float>(GetPosition(), GetSize()), Color::White, 0.0f, _Flip);
	}
}

Vector2D<float> SpriteComponent::GetPosition() const
{
	Vector2D<float> Position = Vector2D<float>(0.0f, 0.0f);
	
	if (_OwnerActor)
	{
		TransformComponent* CurrTransformComponent = _OwnerActor->GetComponentOfClass<TransformComponent>();
		if (CurrTransformComponent)
		{
			Position += CurrTransformComponent->GetPosition();
		}
	}
	Position += _OffsetPosition;

	return Position;
}

Vector2D<float> SpriteComponent::GetSize() const
{
	Vector2D<float> Size = Vector2D<float>(0.0f, 0.0f);

	if (_OwnerActor)
	{
		TransformComponent* CurrTransformComponent = _OwnerActor->GetComponentOfClass<TransformComponent>();
		if (CurrTransformComponent)
		{
			Size += CurrTransformComponent->GetSize();
		}
	}
	Size += _OffsetSize;

	return Size;
}
