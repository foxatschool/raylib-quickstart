#pragma once
#include <vector>
#include "shape.h"
#include <array>


class Editor
{
public:
	Editor();

	~Editor();

	void update();

	void draw();


private:

	Shape* Editor::create(Shape::Type type);

	void clearAll();


	float size_m = 20;
	Shape::Type type_m = Shape::Type::CIRCLE;

	//Colors
	const std::array<Color, 8> colors_m = { WHITE, GREEN, RED, BLUE,PURPLE, SKYBLUE, MAGENTA, ORANGE };
	int colorIndex_m = 0;
	std::vector<Texture2D> textures_m;
	int textureIndex = 0;
	//Textures

	//Shapes
	Shape* shape_m = nullptr;
	std::vector<Shape*> shapes_m;
};