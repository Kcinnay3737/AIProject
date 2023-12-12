#pragma once

#include <cstdint>

namespace NPEngine
{
	//Enum with all color
	enum EColor : uint8_t
	{
		Black = 0,
		Blue = 1,
		Brown = 2,
		Cyan = 3,
		Green = 4,
		Grey = 5,
		Magenta = 6,
		Orange = 7,
		Purple = 8,
		Red = 9,
		White = 10,
		Yellow = 11
	};

	//Struct with R, G, B, A
	struct RGBA
	{
	public:
		RGBA() = default;
		RGBA(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

		unsigned char R = 255;
		unsigned char G = 255;
		unsigned char B = 255;
		unsigned char A = 255;
	};

	class Color
	{
	public:
		Color();
		Color(RGBA rgba);
		Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

		//Static color
		static const Color& Black;
		static const Color& Blue;
		static const Color& Brown;
		static const Color& Cyan;
		static const Color& Green;
		static const Color& Grey;
		static const Color& Magenta;
		static const Color& Orange;
		static const Color& Purple;
		static const Color& Red;
		static const Color& White;
		static const Color& Yellow;

		RGBA rgba;

		Color& operator = (const Color& Other);
	};
}