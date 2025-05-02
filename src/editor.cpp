#include "editor.h"
#include "square.h"
#include "circle.h"

Editor::Editor()
{
	shape_m = create(type_m);
}

Editor::~Editor()
{
	clearAll();
	delete shape_m;
}

void Editor::update()
{
	//scale shape
	if (IsKeyDown(KEY_UP))
	{
		size_m += 0.5f;
		size_m = std::min(size_m, 50.0f);
	}
	if (IsKeyDown(KEY_DOWN))
	{
		size_m -= 0.5f;
		size_m = std::max(size_m, 1.0f);
		if (size_m < 0) size_m = 1;
	}

	shape_m->setSize(size_m);

	if (IsKeyPressed(KEY_RIGHT))
	{
		colorIndex_m = ++colorIndex_m % colors_m.size();
		shape_m->setColor(colors_m[colorIndex_m]);
	}

	//Shape select
	if (IsKeyDown(KEY_TAB))
	{
		type_m = static_cast<Shape::Type>((static_cast<int>(type_m) + 1) % static_cast<int>(Shape::Type::NUMSHAPES));
		delete shape_m;
		shape_m = create(type_m);
	}

	//clear screeen
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_BACKSPACE))
	{
		clearAll();
	}

	//input -> update -> draw
	if (IsMouseButtonPressed(0) || IsMouseButtonDown(0) && IsKeyDown(KEY_LEFT_CONTROL))
	{
		//add current shape
		shapes_m.push_back(shape_m);
		//create new shape
		shape_m = create(type_m);
	}


	shape_m->setPosition(GetMousePosition());

	for (auto shape : shapes_m)
	{
		shape->update();
	}

	shape_m->update();
}

void Editor::draw()
{
	for (auto shape : shapes_m)
	{
		shape -> draw();
	}
	shape_m->draw();
}

Shape* Editor::create(Shape::Type type)
{
	Shape* shape = nullptr;

	switch (type)
	{
	case Shape::Type::CIRCLE:
		shape = new Circle(GetMousePosition(), size_m, colors_m[colorIndex_m]);
		break;
	case Shape::Type::SQUARE:
		shape = new Square(GetMousePosition(), size_m, colors_m[colorIndex_m]);
		break;
	default:
		break;

	}

	return shape;
}

void Editor::clearAll()
{
	for (auto shape : shapes_m)
	{
		delete shape;
	}
	shapes_m.clear();
}
