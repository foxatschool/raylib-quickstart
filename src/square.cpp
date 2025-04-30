#pragma once
#include "square.h"
#include "raymath.h"

void Square::update()
{
	//
}

void Square::draw()
{
	
	DrawRectangleV(position_m, Vector2{size_m/2, size_m/2}, color_m);
}