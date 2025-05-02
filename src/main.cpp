#include "raylib.h"

#include <vector>
#include <math.h>
#include <iostream>
#include "player.h"
#include "shoot.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
#include <random>

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define PLAYER_BASE_SIZE    60.0f
#define PLAYER_SPEED        6.0f
#define PLAYER_MAX_SHOOTS   30
//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 2800;
static const int screenHeight = 1400;

float p1StartPos = (screenWidth / 2) / 2;
float p2StartPos = (screenWidth / 2) + (screenWidth / 2) / 2;

//static const int screenWidth = GetScreenWidth();
//static const int screenHeight = GetScreenHeight();

static bool gameOver = false;
static bool pause = false;
static bool victory = false;

// NOTE: Defined triangle is isosceles with common angles of 70 degrees.
static float shipHeight = 0.0f;

static Player player;
static Shoot shoot[PLAYER_MAX_SHOOTS];


//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    //SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED);
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Tank Game");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables

float getRandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());  // Seed the random number generator
    std::uniform_real_distribution<float> dist(min, max);

    return dist(gen);
}

float randomAngle = getRandomFloat(0.0f, 180.0f);

void InitGame(void)
{
    int posx, posy;
    int velx, vely;
    bool correctRange = false;
    victory = false;
    pause = false;

    shipHeight = (PLAYER_BASE_SIZE / 2);


/*
    Player player1(1);
    Player player2(2);

    // Initialization player
    players[0] = &player1;
    players[1] = &player2;

    players[0]->position = Vector2{ screenWidth / 2, screenHeight/2 - shipHeight / 2 };
    players[1]->position = Vector2{ screenWidth / 2, screenHeight/2 - shipHeight / 2 };

*/
}

// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
{
          
            player.Update(screenWidth, screenHeight);
        }

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

        for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
        {
            if (!shoot[i].IsActive())
            {
                shoot[i].position = Vector2{ (2800 / 2) , 1400 / 2 };
                shoot[i].active = true;
                shoot[i].speed.x = 1.0 * sin(getRandomFloat(0.0f, 360.0) * DEG2RAD) * PLAYER_SPEED;
                shoot[i].speed.y = 1.0 * cos(getRandomFloat(0.0f, 360.0f) * DEG2RAD) * PLAYER_SPEED;
                shoot[i].rotation = getRandomFloat(0.0f, 360.0f);
                break;
            }
        }
        /*
            // Player shoot logic
            if (IsKeyPressed(KEY_SPACE))
            {
                for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
                {
                    if (!shoot[i].IsActive())
                    {
                        shoot[i].position = Vector2{ static_cast<float>(player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight)), static_cast<float>(player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight)) };
                        shoot[i].active = true;
                        shoot[i].speed.x = 1.0 * sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
                        shoot[i].speed.y = 1.0 * cos(player.rotation * DEG2RAD) * PLAYER_SPEED;
                        shoot[i].rotation = player.rotation;
                        break;
                    }

                }
            }
            */

            // Shoot life timer
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if (shoot[i].active) shoot[i].lifeSpan++;
            }

            // Shot logic
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if (shoot[i].active)
                {
                    // Movement
                    shoot[i].position.x += shoot[i].speed.x;
                    shoot[i].position.y -= shoot[i].speed.y;

                    // Collision logic: shot vs walls
                    if (shoot[i].position.x > screenWidth + shoot[i].radius)
                    {
                        shoot[i].active = false;
                        shoot[i].lifeSpan = 0;
                    }
	
                    if (shoot[i].position.y > screenHeight + shoot[i].radius)
	{
                        shoot[i].active = false;
                        shoot[i].lifeSpan = 0;
                    }
                    else if (shoot[i].position.y < 0 - shoot[i].radius)
                    {
                        shoot[i].active = false;
                        shoot[i].lifeSpan = 0;
                    }
	
                    // Life of a shot
                    if (shoot[i].lifeSpan >= 900)
                    {
                        shoot[i].position = Vector2{ 0, 0 };
                        shoot[i].speed = Vector2{ 0, 0 };
                        shoot[i].lifeSpan = 0;
                        shoot[i].active = false;
                    }
                }
            }

            // Collision logic: player vs meteors
            //player.collider = Vector3{ static_cast<float>(player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f)), static_cast<float>(player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f)), 12 };

            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if (CheckCollisionCircles(Vector2{ player.position.x, player.position.y }, player.collider.y, shoot[i].GetPosition(), shoot[i].radius) && shoot[i].active) gameOver = true;
            }

    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
	    {
            InitGame();
            gameOver = false;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
		BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!gameOver)
			{
        player.Draw();


        // Draw shoot
        for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
        {
            shoot[i].Draw();
			}

        if (victory) DrawText("VICTORY", screenWidth / 2 - MeasureText("VICTORY", 20) / 2, screenHeight / 2, 20, LIGHTGRAY);
			
        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", screenWidth / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, screenHeight / 2 - 50, 20, GRAY);
		}

#endif
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
}
		
// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
	}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}
