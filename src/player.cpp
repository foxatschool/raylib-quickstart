#pragma once
#include <raylib.h>

class Player
{
    Player(){}
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector3 collider;
    Color color;
};