#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Player(int playerNumber) :
    playerNumber_m {playerNumber}
    {}

    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    float shipHeight;
    float invincibilityTimer;
    float invincibilityDuration;
    bool invincible;
    Rectangle collider;
    Color color;
    int playerNumber_m;

public:
    Player();
    void Update(int screenWidth, int screenHeight);
    void Draw() const;
    void StartInvincibility(float duration = 5.0f);
    void UpdateInvincibility(float deltaTime);
    bool IsInvicible() const;
    Rectangle GetCollider() const;
    Vector2 GetPosition() const;
    Vector2 GetSpeed() const;
    float GetRotation() const;
    void Reset(int screenWidth, int screenHeight);
};

#endif