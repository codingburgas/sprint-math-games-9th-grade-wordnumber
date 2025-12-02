#include "menu.h"
#include "game.h"
void menu() {
    InitWindow(800, 600, "Hangman WordNumber)");
    SetTargetFPS(60);

    bool inMenu = true;

    Rectangle playBtn = { 300, 250, 200, 60 };
    Rectangle quitBtn = { 300, 330, 200, 60 };

    while (inMenu && !WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, playBtn)) {
                game();
            }
            if (CheckCollisionPointRec(mouse, quitBtn)) {
                CloseWindow();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("HANGMAN", 260, 120, 60, BLACK);

        DrawRectangleRec(playBtn, LIGHTGRAY);
        DrawRectangleLinesEx(playBtn, 2, BLACK);
        DrawText("PLAY", playBtn.x + 65, playBtn.y + 15, 30, BLACK);

        DrawRectangleRec(quitBtn, LIGHTGRAY);
        DrawRectangleLinesEx(quitBtn, 2, BLACK);
        DrawText("QUIT", quitBtn.x + 65, quitBtn.y + 15, 30, BLACK);

        EndDrawing();
    }
}