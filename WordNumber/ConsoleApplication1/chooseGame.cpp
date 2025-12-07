#include "chooseGame.h"
#include "menu.h"
#include "games.h"
void chooseGame() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    const Rectangle game1Button = { screenWidth / 2 - 450, screenHeight / 2 - 60, 300, 120 };
    const Rectangle game2Button = { screenWidth / 2 + 250, screenHeight / 2 - 60, 300, 120 };
    const Rectangle game3Button = { screenWidth / 2 - 100, screenHeight / 2 + 120, 300, 120 };
    const Rectangle backButton = { screenWidth / 2 + 475, screenHeight / 2 + 280, 300, 120 };

    Texture2D background = LoadTexture("../images/background1.png");
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawText("Welcome to the games menu! From here you can choose what game to play!", GetScreenWidth() / 2 - 875, GetScreenHeight() / 2 - 455, 47, WHITE);
        bool isMouseOverQuiz1 = CheckCollisionPointRec(mousePosition, game1Button);
        DrawRectangleRec(game1Button, isMouseOverQuiz1 ? DARKGRAY : SKYBLUE);
        DrawText("Hangman", screenWidth / 2 - 403, screenHeight / 2 - 30, 50, WHITE);
        if (isMouseOverQuiz1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            hangman();
        }

        bool isMouseOverQuiz2 = CheckCollisionPointRec(mousePosition, game2Button);
        DrawRectangleRec(game2Button, isMouseOverQuiz2 ? DARKGRAY : SKYBLUE);
        DrawText("Math Game", screenWidth / 2 + 275, screenHeight / 2 - 30, 50, WHITE);
        if (isMouseOverQuiz2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startMathGame();
        }

        bool isMouseOverQuiz3 = CheckCollisionPointRec(mousePosition, game3Button);
        DrawRectangleRec(game3Button, isMouseOverQuiz3 ? DARKGRAY : SKYBLUE);
        DrawText("Crossword", screenWidth / 2 - 83, screenHeight / 2 + 150, 50, WHITE);
        if (isMouseOverQuiz3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            crossword();
        }



        bool isMouseOverBack = CheckCollisionPointRec(mousePosition, backButton);
        DrawRectangleRec(backButton, isMouseOverBack ? PINK : RED);
        DrawText("Back", screenWidth / 2 + 550, screenHeight / 2 + 315, 50, WHITE);
        if (isMouseOverBack && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            menu(true);
        }
        EndDrawing();
    }
}