#pragma once
#include "shape.h"

class Square : public Shape
{
public:
	Square() = default;

	Square(const Vector2& position, float size = 40, const Color& color = WHITE) :
		Shape(position, size, color)
	{
	}

	// Inherited via Shape
	void update() override;

	void draw() override;

	Type getType() override { return Type::SQUARE; }

protected:
	float rotation_m{ 0 };
};