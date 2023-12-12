#pragma once

namespace NPEngine
{
	//Class for flip texture data
	struct Flip
	{
		Flip(bool Horizontal = false, bool Vertical = false);

		bool Horizontal = false;
		bool Vertical = false;
	};
}