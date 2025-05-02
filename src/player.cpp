#pragma once
#include "player.h"
//#include "main.cpp"
#include <cmath>

#define PLAYER_BASE_SIZE 45.0f
#define PLAYER_SPEED 6.0f

Player::Player() {
    shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);
    position = { (2800 / 2) / 2, 1400 / 2 - shipHeight / 2 };
    speed = { 0, 0 };
    acceleration = 0;
    rotation = 0;
    collider = { 0, 0, 12 };
    color = LIGHTGRAY;
    invincible = false;
    invincibilityTimer = 0.0f;
    invincibilityDuration = 5.0f;
}

void Player::Reset(int screenWidth, int screenHeight) {
    position = { (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
    speed = { 0, 0 };
    acceleration = 0;
    rotation = 0;
    collider = { position.x, position.y };
}

void Player::Update(int screenWidth, int screenHeight) {
    // Player logic: speed
    speed.x = sin(rotation * DEG2RAD) * PLAYER_SPEED;
    speed.y = cos(rotation * DEG2RAD) * PLAYER_SPEED;


    // Screen wrapping
    if (position.x > screenWidth + shipHeight) position.x = -shipHeight;
    else if (position.x < -shipHeight) position.x = screenWidth + shipHeight;

    if (position.y > screenHeight + shipHeight) position.y = -shipHeight;
    else if (position.y < -shipHeight) position.y = screenHeight + shipHeight;

    /*
    switch (playerNumber_m)
    {
    case 2:
        // Player logic: rotation
        if (IsKeyDown(KEY_LEFT)) rotation -= .5f;
        if (IsKeyDown(KEY_RIGHT)) rotation += .5f;

        // Player logic: acceleration
        if (IsKeyDown(KEY_UP))
        {
            if (acceleration < 1)acceleration += 0.005f;
        }
        else
        {
            if (acceleration > 0) acceleration -= 0.04f;
            else if (acceleration < 0) acceleration = 0;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            if (acceleration > 0)acceleration -= 0.005f;
            else if (acceleration <= 0)acceleration -= 0.05f;
        }

        break;
    case 1:

        // Player logic: rotation
        if (IsKeyDown(KEY_A)) rotation -= .5f;
        if (IsKeyDown(KEY_D)) rotation += .5f;

        // Player logic: acceleration
        if (IsKeyDown(KEY_W))
        {
            if (acceleration < 1)acceleration += 0.005f;
        }
        else
        {
            if (acceleration > 0) acceleration -= 0.04f;
            else if (acceleration < 0) acceleration = 0;
        }
        if (IsKeyDown(KEY_S))
        {
            if (acceleration > 0)acceleration -= 0.005f;
            else if (acceleration <= 0)acceleration -= 0.05f;
        }

        break;
    default:
        break;
    }
    */
    // Player logic: rotation
        if (IsKeyDown(KEY_A)) rotation -= .5f;
        if (IsKeyDown(KEY_D)) rotation += .5f;

        // Player logic: acceleration
        if (IsKeyDown(KEY_W))
        {
            if (acceleration < 1)acceleration += 0.005f;
        }
        else
        {
            if (acceleration > 0) acceleration -= 0.04f;
            else if (acceleration < 0) acceleration = 0;
        }
        if (IsKeyDown(KEY_S))
        {
            if (acceleration > 0)acceleration -= 0.005f;
            else if (acceleration <= 0)acceleration -= 0.05f;
        }
    
    // logic: movement
    position.x += (speed.x * acceleration);
    position.y -= (speed.y * acceleration);


    // Collider update
    Rectangle collider = {
    position.x - (shipHeight / 2.0f),    // X position (offset to center)
    position.y - (shipHeight / 2.0f),    // Y position (offset to center)
    shipHeight - 0.1f,                   // Width of the collider (adjust scaling as needed)
    shipHeight - 0.1f                    // Height of the collider
    };

}

void Player::Draw() const {

    // Define rectangle size
    Vector2 size = { PLAYER_BASE_SIZE, shipHeight }; // Width, Height

    // Define rectangle origin (center point)
    Vector2 origin = { PLAYER_BASE_SIZE / 2, shipHeight / 2 };

    Rectangle rectangle_m = {position.x, position.y, size.x, size.y};


    // Draw the rotated rectangle
    DrawRectanglePro(
        rectangle_m ,   // Position & size
        origin,               // Rotation origin (center of rectangle)
        rotation,             // Rotation angle (degrees)
        MAROON                // Color
    );
}


Rectangle Player::GetCollider() const {
    return collider;
}

Vector2 Player::GetPosition() const {
    return position;
}

Vector2 Player::GetSpeed() const {
    return speed;
}

float Player::GetRotation() const {
    return rotation;
}



//Adds invincibility to player after they die so then they don't get killed right on respawn
void Player::StartInvincibility(float duration) {
    invincible = true;
    invincibilityTimer = 0.0f;
    invincibilityDuration = duration;
}

void Player::UpdateInvincibility(float deltaTime) {
    if (invincible) {
        invincibilityTimer += deltaTime;
        if (invincibilityTimer >= invincibilityDuration) {
            invincible = false;
            invincibilityTimer = 0.0f;
        }
    }
}

bool Player::IsInvicible() const {
    return invincible;
}