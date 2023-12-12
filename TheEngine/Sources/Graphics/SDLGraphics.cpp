#include "Graphics/SDLGraphics.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Engine.h"
#include "Logger/ILogger.h"
#include <string>
#include <SDL_ttf.h>

using namespace NPEngine;

bool SDLGraphics::Initialize(const Param& Params)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	//Init window
	auto IT = Params.find("Name");
	const char* WindowName = IT != Params.end() ? std::any_cast<const char*>(IT->second) : "DefaultName";
	IT = Params.find("Width");
	int WindowWidth = IT != Params.end() ? std::any_cast<int>(IT->second) : 800;
	IT = Params.find("Height");
	int WindowHeight = IT != Params.end() ? std::any_cast<int>(IT->second) : 600;
	int X = SDL_WINDOWPOS_CENTERED;
	int Y = SDL_WINDOWPOS_CENTERED;
	Uint32 WindowFlag = SDL_WINDOW_TOOLTIP;
	_Window = SDL_CreateWindow(WindowName, X, Y, WindowWidth, WindowHeight, WindowFlag);
	if (!_Window)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	//Init renderer
	Uint32 RenderFlags = SDL_RENDERER_ACCELERATED;
	_Renderer = SDL_CreateRenderer(_Window, -1, RenderFlags);
	if (!_Renderer)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		Engine::GetLogger()->LogMessage(TTF_GetError());
		return false;
	}

	return true;
}

void SDLGraphics::Shutdown(const Param& Params)
{
	for (auto& Texture : _TextureMap)
	{
		SDL_DestroyTexture(Texture.second);
		Texture.second = nullptr;
	}
	_TextureMap.clear();

	for (auto& Font : _FontMap)
	{
		TTF_CloseFont(Font.second);
		Font.second = nullptr;
	}
	_FontMap.clear();

	SDL_DestroyRenderer(_Renderer);
	_Renderer = nullptr;
	SDL_DestroyWindow(_Window);
	_Window = nullptr;
	TTF_Quit();
	SDL_Quit();
}

void SDLGraphics::SetBackgroundColor(const Color& Color)
{
	_BackgroundColor = Color;
}

void SDLGraphics::SetColor(const Color& Color)
{
	SDL_SetRenderDrawColor(_Renderer, Color.rgba.R, Color.rgba.G, Color.rgba.B, Color.rgba.A);
}

void SDLGraphics::DrawRect(const Rectangle2D<float>& Rect, const Color& Color, bool bFill)
{
	SetColor(Color);

	SDL_FRect SDLRect = { 0.0f };
	SDLRect.x = Rect.Position.X;
	SDLRect.y = Rect.Position.Y;
	SDLRect.w = Rect.Size.X;
	SDLRect.h = Rect.Size.Y;

	if (bFill)
	{
		SDL_RenderFillRectF(_Renderer, &SDLRect);
	}
	else
	{
		SDL_RenderDrawRectF(_Renderer, &SDLRect);
	}
}

void SDLGraphics::DrawLine(const Vector2D<float>& Start, const Vector2D<float>& End, const Color& Color)
{
	SetColor(Color);

	SDL_RenderDrawLineF(_Renderer, Start.X, Start.Y, End.X, End.Y);
}

void SDLGraphics::DrawPoint(const Vector2D<float>& Position, const Color& Color)
{
	SetColor(Color);

	SDL_RenderDrawPointF(_Renderer, Position.X, Position.Y);
}

void SDLGraphics::DrawCircle(const Vector2D<float>& Position, const float Ray, const Color& Color)
{
	SetColor(Color);

	const int Resolution = 360;

	for (int i = 0; i < Resolution; i++)
	{
		float Angle = static_cast<float>(i) / static_cast<float>(Resolution) * (2.0f * static_cast<float>(M_PI));
		float X = Position.X + Ray * cos(Angle);
		float Y = Position.Y + Ray * sin(Angle);

		SDL_RenderDrawPointF(_Renderer, X, Y);
	}
}

void SDLGraphics::DrawTexture(size_t TextureId, const Rectangle2D<float>& DrawRect, const Color& Color, float Angle, const Flip& Flip)
{
	//Get the texture
	SDL_Texture* Texture = _TextureMap[TextureId];
	if (!Texture) return;

	//Set flip
	SDL_RendererFlip SDLFlip = SDL_FLIP_NONE;
	if (Flip.Horizontal && Flip.Vertical)
	{
		SDLFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}
	else if (Flip.Horizontal)
	{
		SDLFlip = SDL_FLIP_HORIZONTAL;
	}
	else if (Flip.Vertical)
	{
		SDLFlip = SDL_FLIP_VERTICAL;
	}

	//Set the color
	SDL_SetTextureColorMod(Texture, Color.rgba.R, Color.rgba.G, Color.rgba.B);
	SDL_SetTextureAlphaMod(Texture, Color.rgba.A);

	//Set the screen rect
	SDL_FRect SDLScreenRect = { 0.0f };
	SDLScreenRect.x = DrawRect.Position.X;
	SDLScreenRect.y = DrawRect.Position.Y;
	SDLScreenRect.w = DrawRect.Size.X;
	SDLScreenRect.h = DrawRect.Size.Y;

	//Set the texture rect
	Rectangle2D<int> TextureRect = Rectangle2D<int>(Vector2D<int>(0, 0), Vector2D<int>(0, 0));
	GetTextureSize(TextureId, &TextureRect.Size);

	SDL_Rect SDLTextureRect = { 0 };
	SDLTextureRect.x = TextureRect.Position.X;
	SDLTextureRect.y = TextureRect.Position.Y;
	SDLTextureRect.w = TextureRect.Size.X;
	SDLTextureRect.h = TextureRect.Size.Y;

	//Draw the texture
	SDL_RenderCopyExF(_Renderer, Texture, &SDLTextureRect, &SDLScreenRect, Angle, nullptr, SDLFlip);
}

void SDLGraphics::DrawTextureTile(size_t TextureId, const Rectangle2D<float>& DrawRect, const Vector2D<int>& CellSize, const Vector2D<int>& CellPosition, const Color& Color, float Angle, const Flip& Flip)
{
	//Get the texture
	SDL_Texture* Texture = _TextureMap[TextureId];
	if (!Texture) return;

	//Set the texture flip
	SDL_RendererFlip SDLFlip = SDL_FLIP_NONE;
	if (Flip.Horizontal && Flip.Vertical)
	{
		SDLFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}
	else if (Flip.Horizontal)
	{
		SDLFlip = SDL_FLIP_HORIZONTAL;
	}
	else if (Flip.Vertical)
	{
		SDLFlip = SDL_FLIP_VERTICAL;
	}

	//Set the color
	SDL_SetTextureColorMod(Texture, Color.rgba.R, Color.rgba.G, Color.rgba.B);
	SDL_SetTextureAlphaMod(Texture, Color.rgba.A);

	//Set the screen rect
	SDL_FRect SDLScreenRect = { 0.0f };
	SDLScreenRect.x = DrawRect.Position.X;
	SDLScreenRect.y = DrawRect.Position.Y;
	SDLScreenRect.w = DrawRect.Size.X;
	SDLScreenRect.h = DrawRect.Size.Y;

	Rectangle2D<int> TextureRect = Rectangle2D<int>(Vector2D<int>(CellSize.X * CellPosition.X, CellSize.Y * CellPosition.Y), Vector2D<int>(CellSize.X, CellSize.Y));

	SDL_Rect SDLTextureRect = { 0 };
	SDLTextureRect.x = TextureRect.Position.X;
	SDLTextureRect.y = TextureRect.Position.Y;
	SDLTextureRect.w = TextureRect.Size.X;
	SDLTextureRect.h = TextureRect.Size.Y;

	//Draw the texture
	SDL_RenderCopyExF(_Renderer, Texture, &SDLTextureRect, &SDLScreenRect, Angle, nullptr, SDLFlip);
}

void SDLGraphics::DrawTextureTile(size_t TextureId, const Rectangle2D<float>& DrawRect, const Vector2D<int>& CellSize, const int& CellIndex, const Color& Color, float Angle, const Flip& Flip)
{
	//Get the texture
	SDL_Texture* Texture = _TextureMap[TextureId];
	if (!Texture) return;

	// Calculate the number of cells per row in the texture
	int CellsPerRow;
	Vector2D<int> TextureSize;
	GetTextureSize(TextureId, &TextureSize);
	CellsPerRow = TextureSize.X / CellSize.X;

	// Convert the CellIndex to X and Y coordinates
	Vector2D<int> CellPosition;
	CellPosition.X = (CellIndex % CellsPerRow) * CellSize.X;
	CellPosition.Y = (CellIndex / CellsPerRow) * CellSize.Y;

	//Set the texture flip
	SDL_RendererFlip SDLFlip = SDL_FLIP_NONE;
	if (Flip.Horizontal && Flip.Vertical)
	{
		SDLFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}
	else if (Flip.Horizontal)
	{
		SDLFlip = SDL_FLIP_HORIZONTAL;
	}
	else if (Flip.Vertical)
	{
		SDLFlip = SDL_FLIP_VERTICAL;
	}

	//Set the color
	SDL_SetTextureColorMod(Texture, Color.rgba.R, Color.rgba.G, Color.rgba.B);
	SDL_SetTextureAlphaMod(Texture, Color.rgba.A);

	//Set the screen rect
	SDL_FRect SDLScreenRect = { 0.0f };
	SDLScreenRect.x = DrawRect.Position.X;
	SDLScreenRect.y = DrawRect.Position.Y;
	SDLScreenRect.w = DrawRect.Size.X;
	SDLScreenRect.h = DrawRect.Size.Y;

	// Define the texture rect
	SDL_Rect SDLTextureRect = { CellPosition.X, CellPosition.Y, CellSize.X, CellSize.Y };

	//Draw the texture
	SDL_RenderCopyExF(_Renderer, Texture, &SDLTextureRect, &SDLScreenRect, Angle, nullptr, SDLFlip);
}

void SDLGraphics::GetTextureSize(size_t TextureId, Vector2D<int>* Size)
{
	SDL_Texture* Texture = _TextureMap[TextureId];
	if (!Texture) return;

	SDL_QueryTexture(Texture, NULL, NULL, &Size->X, &Size->Y);
}

size_t SDLGraphics::LoadFont(const std::string& Filename, int FontSize)
{
	//Get ID
	std::hash<std::string> Hasher;
	size_t FontId = Hasher(Filename);

	//Load font
	if (_FontMap.find(FontId) == _FontMap.end())
	{
		std::string FilePath = "./Assets/Font/";
		FilePath += Filename;

		TTF_Font* Font = TTF_OpenFont(FilePath.c_str(), FontSize);
		if (Font)
		{
			_FontMap[FontId] = Font;
		}
		else
		{
			Engine::GetLogger()->LogMessage(TTF_GetError());
		}
	}

	return FontId;
}

void SDLGraphics::DrawString(size_t FontId, const char* Text, const Vector2D<int>& Location, const Color& Color)
{
	//Get the font
	TTF_Font* Font = _FontMap[FontId];
	if (!Font) return;

	//Set the color
	SDL_Color SDLColor = SDL_Color();
	SDLColor.r = Color.rgba.R;
	SDLColor.g = Color.rgba.G;
	SDLColor.b = Color.rgba.B;
	SDLColor.a = Color.rgba.A;

	//Create surface contain the text with font and color
	SDL_Surface* Surface = TTF_RenderText_Solid(Font, Text, SDLColor);
	//Create texture with the surface
	SDL_Texture* TextureBuffer = SDL_CreateTextureFromSurface(_Renderer, Surface);

	//Get the render text size
	Vector2D<int> FontSize;
	GetTextSize(FontId, Text, &FontSize);

	//Set the screen rect
	SDL_Rect SDLRect = SDL_Rect();
	SDLRect.x = Location.X;
	SDLRect.y = Location.Y;
	SDLRect.w = FontSize.X;
	SDLRect.h = FontSize.Y;

	//Draw font
	SDL_RenderCopy(_Renderer, TextureBuffer, nullptr, &SDLRect);
	SDL_FreeSurface(Surface);
	SDL_DestroyTexture(TextureBuffer);
}

void SDLGraphics::GetTextSize(size_t FontId, const char* Text, Vector2D<int>* Size)
{
	TTF_Font* Font = _FontMap[FontId];
	if (!Font) return;

	int Width = 0;
	int Height = 0;
	if (TTF_SizeText(Font, Text, &Width, &Height) != 0) return;

	Size->X = Width;
	Size->Y = Height;
}

Vector2D<int> SDLGraphics::GetScreenSize() const
{
	Vector2D<int> ScreenSize = Vector2D<int>(0, 0);

	SDL_GetWindowSize(_Window, &ScreenSize.X, &ScreenSize.Y);

	return ScreenSize;
}

bool SDLGraphics::CheckPointIsOutOfScreen(const Vector2D<float>& Point) const
{
	Vector2D<int> ScreenSize = GetScreenSize();
	Vector2D<float> FScreenSize = Vector2D<float>(static_cast<float>(ScreenSize.X), static_cast<float>(ScreenSize.Y));

	if (Point.X < 0 || Point.Y < 0 || Point.X > FScreenSize.X || Point.Y > FScreenSize.Y)
	{
		return true;
	}
	return false;
}

void SDLGraphics::Clear()
{
	SDL_SetRenderDrawColor(_Renderer, _BackgroundColor.rgba.R, _BackgroundColor.rgba.G, _BackgroundColor.rgba.B, _BackgroundColor.rgba.A);
	SDL_RenderClear(_Renderer);
}

void SDLGraphics::Present()
{
	SDL_RenderPresent(_Renderer);
}

size_t SDLGraphics::LoadTexture(const std::string& Filename)
{
	//Get the ID
	std::hash<std::string> Hasher;
	size_t TextureId = Hasher(Filename);

	//Load the texture
	if (_TextureMap.find(TextureId) == _TextureMap.end())
	{
		std::string FilePath = "./Assets/Texture/";
		FilePath += Filename;
		SDL_Texture* Texture = IMG_LoadTexture(_Renderer, FilePath.c_str());
		if (Texture)
		{
			_TextureMap[TextureId] = Texture;
		}
		else
		{
			Engine::GetLogger()->LogMessage("Texture not found");
		}
	}

	return TextureId;
}