#pragma once
#include "square.h"
#include "raymath.h"

void Square::update()
{

	struct Hitbox
	{
		float x, y;       // Position of the top-left corner
		float width, height; // Dimensions of the hitbox

		// Function to check collision with another hitbox
		bool intersects(const Hitbox& other) const
		{
			return (x < other.x + other.width &&
				x + width > other.x &&
				y < other.y + other.height &&
				y + height > other.y);
		}
	};

}

void Square::draw()
{
	Rectangle r{ position_m.x, position_m.y, size_m, size_m };
	DrawRectanglePro(r, Vector2{ size_m / 2, size_m / 2 }, rotation_m, color_m);
}