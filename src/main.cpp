﻿#include <cstdlib>

#include "raylib.h"

#include "config.h"

#include "Board/Board.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // ===== INIT =====

    Board board;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // ===== UPDATE =====


        // ===== DRAW =====
        BeginDrawing();


        board.Draw();

            ClearBackground(WHITE);


        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...


    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
