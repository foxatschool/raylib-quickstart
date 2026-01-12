#pragma once
#include "image.h"

void ImageShape::update()
{ }

void ImageShape::draw()
{
	DrawTextureEx(texture_m, position_m, 0, (int)size_m, color_m);

	Rectangle src{ 0, 0, texture_m.width, texture_m.height };
	Rectangle dest{ position_m.x, position_m.y, size_m, size_m };
	
	DrawTexturePro(texture_m, src, dest, Vector2{ size_m / 2, size_m / 2 }, 0, color_m);
}


