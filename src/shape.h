#pragma once
#include "raylib.h"


class Shape
{
public:
	enum class Type
	{
		CIRCLE,
		SQUARE,
		IMAGE,
		NUMSHAPES
	};

public:
	Shape() = default;

	Shape(const Vector2& position, float size = 20, const Color& color = WHITE) :
		position_m{ position },
		size_m{ size },
		color_m{ color }
	{}

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual Type getType() = 0;

	const Vector2& getPosition() const { return position_m; }
	void setPosition(const Vector2& position) { position_m = position; }
	
	float getSize() const { return size_m; }
	void setSize(float size) { size_m = size; }
	
	const Color& getColor() const { return color_m; }
	void setColor(const Color& color) { color_m = color; }

protected:
	Vector2 position_m{ 0,0 };
	float size_m = 20;
	Color color_m = WHITE;
};