/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
#include "circle.h"
#include "square.h"
#include "editor.h"

#include "raylib.h"
#include "resource_dir.h"// utility header for SearchAndSetResourceDir
#include <vector>
#include <iostream>

int main ()
{
	const int screen_width = 1280;
	const int screen_height = 800;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	Editor editor;

	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
	
		editor.update();

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);


		// draw some text using the default font
		DrawText("Click", 200,200,20,BLACK);

		DrawTexture(wabbit, 250, 200, BLACK);

		//draw editer
		editor.draw();


#if 0
		// draw our texture to the screen
		float rate = 100.0f;
		float amplitude =1.0f;
		// only do this if mouse was clicked
		if (IsMouseButtonDown(0))
		{
			for (int i = 0; i <= screen_width; i += 10)
			{
				int y = screen_height / 2 + (sinf((GetTime() * 3) + i / 50.0f) * 100);

				//Get the rabits to grow 
				float scale = i + (sinf((GetTime() * rate) + 30 / 50.0f) * amplitude);
				//Have the growing rabits follow the Mouse
				DrawTextureEx(wabbit, (Vector2) { GetMouseX(), GetMouseY() }, 0, scale, ORANGE);


			}

			
		}

#endif
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
