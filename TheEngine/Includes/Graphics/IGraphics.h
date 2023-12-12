#pragma once

#include "Graphics/IGraphicsProvider.h"
#include "Graphics/Color.h"
#include "Graphics/Flip.h"
#include "Math/Vector2D.h"
#include "Math/Rectangle2D.h"

namespace NPEngine
{
	//Interface for graphics provider
	class IGraphics : public IGraphicsProvider
	{
	protected:
		Color _BackgroundColor = Color();

	public:
		virtual ~IGraphics() = default;

		//Set the background color
		virtual void SetBackgroundColor(const Color& Color) = 0;

		//Set the current draw color
		virtual void SetColor(const Color& Color) = 0;

		//Draw a rectangle
		virtual void DrawRect(const Rectangle2D<float>& Rect, const Color& Color = Color::Blue, bool bFill = false) = 0;
		//Draw a line
		virtual void DrawLine(const Vector2D<float>& Start, const Vector2D<float>& End, const Color& Color = Color::Red) = 0;
		//Draw a point
		virtual void DrawPoint(const Vector2D<float>& Position, const Color& Color = Color::Red) = 0;
		//Draw a circle
		virtual void DrawCircle(const Vector2D<float>& Position, const float Ray, const Color& Color = Color::Red) = 0;

		//Load a texture and return the id
		virtual size_t LoadTexture(const std::string& Filename) = 0;
		//Draw a texture with id
		virtual void DrawTexture(size_t TextureId,
								const Rectangle2D<float>& DrawRect,
								const Color& Color = Color::White,
								float Angle = 0,
								const Flip& Flip = Flip()) = 0;
		//Draw texture tile with id
		virtual void DrawTextureTile(size_t TextureId,
								const Rectangle2D<float>& DrawRect,
								const Vector2D<int>& CellSize,
								const Vector2D<int>& CellPosition,
								const Color& Color = Color::White,
								float Angle = 0,
								const Flip& Flip = Flip()) = 0;
		//Draw texture tile with id in index
		virtual void DrawTextureTile(size_t TextureId,
								const Rectangle2D<float>& DrawRect,
								const Vector2D<int>& CellSize,
								const int& CellIndex,
								const Color& Color = Color::White,
								float Angle = 0,
								const Flip& Flip = Flip()) = 0;
		//Return the current texture size
		virtual void GetTextureSize(size_t TextureId, Vector2D<int>* Size) = 0;

		//Load a font and return the id
		virtual size_t LoadFont(const std::string& Filename, int FontSize) = 0;
		//Draw a text
		virtual void DrawString(size_t FontId, const char* Text, const Vector2D<int>& Location, const Color& Color) = 0;
		//Return the text size
		virtual void GetTextSize(size_t FontId, const char* Text, Vector2D<int>* Size) = 0;

		//Return the screen size
		virtual Vector2D<int> GetScreenSize() const = 0;

		//Return if a point is out of screen
		virtual bool CheckPointIsOutOfScreen(const Vector2D<float>& Point) const = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		//Clear the current render
		virtual void Clear() override = 0;
		//Present the current render
		virtual void Present() override = 0;
	};
}