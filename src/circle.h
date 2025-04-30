#pragma once
#include "shape.h"

class Circle : public Shape
{
public:
	Circle() = default;

	Circle(const Vector2& position, float size = 20, const Color& color = WHITE):
		Shape(position, size, color)
	{ }



	// Inherited via Shape
	void update() override;
	
	void draw() override;

	Type getType() override { return Type::CIRCLE; }
};