#pragma once

#include "Object/Component/Component.h"
#include "Graphics/Flip.h"

namespace NPEngine
{
	//A component for draw a texture
	class SpriteComponent : public Component, public IDrawableComponent
	{
	protected:
		size_t _TextureID = -1;

		Vector2D<float> _OffsetPosition = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _OffsetSize = Vector2D<float>(0.0f, 0.0f);

		bool _bTextureIsLoaded = false;

		Flip _Flip = Flip();

		bool _bDraw = true;

	public:
		SpriteComponent(const std::string& Name);
		virtual ~SpriteComponent() = default;

		//Load the texture at the texture path
		void LoadTexture(const std::string& TexturePath);

	protected:
		virtual bool Initialise(const Param& Params = Param{}) override;

	private:
		virtual void Draw() override;

	public:
		//Set offset position for this component 
		void SetOffsetPosition(const Vector2D<float>& OffsetPosition) { _OffsetPosition = OffsetPosition; }
		//Return the offset position
		Vector2D<float> GetOffsetPosition() const { return _OffsetPosition; }
		//Return the component position
		Vector2D<float> GetPosition() const;

		//Set the offset for the size for this component
		void SetOffsetSize(const Vector2D<float>& Size) { _OffsetSize = Size; }
		//Return the offset for the size
		Vector2D<float> GetOffsetSize() const { return _OffsetSize; }
		//Return the component size
		Vector2D<float> GetSize() const;

		//Set the flip data
		void SetFlip(Flip NewFlip) { _Flip = NewFlip; }
		//Return the flip data
		Flip GetFlip() const { return _Flip; }

		//Set if draw the texture
		void SetDraw(bool bDraw) { _bDraw = bDraw; }
	};
}