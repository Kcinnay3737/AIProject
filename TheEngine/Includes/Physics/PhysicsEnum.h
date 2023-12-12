#pragma once

#include <cstdint>

//Collision type enum
enum ECollisionType : uint8_t
{
	None = 0,
	Point = 1,
	Line = 2,
	Box = 3,
	Sphere = 4,
	Grid = 5
};