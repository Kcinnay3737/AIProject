#include "Graphics/Color.h"

using namespace NPEngine;

const Color& Color::Black = Color(RGBA(0, 0, 0, 255));
const Color& Color::Blue = Color(RGBA(0, 0, 255, 255));
const Color& Color::Brown = Color(RGBA(165, 42, 42, 255));
const Color& Color::Cyan = Color(RGBA(0, 255, 255, 255));
const Color& Color::Green = Color(RGBA(0, 255, 0, 255));
const Color& Color::Grey = Color(RGBA(128, 128, 128, 255));
const Color& Color::Magenta = Color(RGBA(255, 0, 255, 255));
const Color& Color::Orange = Color(RGBA(255, 165, 0, 255));
const Color& Color::Purple = Color(RGBA(128, 0, 128, 255));
const Color& Color::Red = Color(RGBA(255, 0, 0, 255));
const Color& Color::White = Color(RGBA(255, 255, 255, 255));
const Color& Color::Yellow = Color(RGBA(255, 255, 0, 255));

RGBA::RGBA(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = A;
}

Color::Color() : Color(RGBA(255, 255, 255, 255))
{
	
}

Color::Color(RGBA rgba)
{
	this->rgba = rgba;
}

Color::Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
	rgba = RGBA(R, G, B, A);
}

Color& Color::operator=(const Color& Other) 
{
	this->rgba = Other.rgba;

	return *this;
}