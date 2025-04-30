#pragma once
#include "circle.h"

void Circle::update()
{ 
	//
}

void Circle::draw()
{
	DrawCircleV(position_m, size_m, color_m);
}