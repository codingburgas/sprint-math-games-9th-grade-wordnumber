#include "chooseGame.h"
#include "menu.h"
#include "hangman.h"
void chooseGame() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    const Rectangle quiz1Button = { screenWidth / 2 - 450, screenHeight / 2 - 330, 300, 120 };
    const Rectangle quiz2Button = { screenWidth / 2 + 250, screenHeight / 2 - 330, 300, 120 };
    const Rectangle quiz3Button = { screenWidth / 2 - 450, screenHeight / 2 - 110, 300, 120 };
    const Rectangle quiz4Button = { screenWidth / 2 + 250, screenHeight / 2 - 110, 300, 120 };
    const Rectangle quiz5Button = { screenWidth / 2 - 450, screenHeight / 2 + 110, 300, 120 };
    const Rectangle quiz6Button = { screenWidth / 2 + 250, screenHeight / 2 + 110, 300, 120 };
    const Rectangle backButton = { screenWidth / 2 + 475, screenHeight / 2 + 280, 300, 120 };

    Texture2D background = LoadTexture("../images/background1.png");
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawText("Welcome to the games menu! From here you can choose what game to play!", GetScreenWidth() / 2 - 800, GetScreenHeight() / 2 - 455, 50, BLACK);
        bool isMouseOverQuiz1 = CheckCollisionPointRec(mousePosition, quiz1Button);
        DrawRectangleRec(quiz1Button, isMouseOverQuiz1 ? DARKGRAY : SKYBLUE);
        DrawText("Hangman", screenWidth / 2 - 385, screenHeight / 2 - 290, 50, WHITE);
        if (isMouseOverQuiz1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            hangman();
        }

        bool isMouseOverQuiz2 = CheckCollisionPointRec(mousePosition, quiz2Button);
        DrawRectangleRec(quiz2Button, isMouseOverQuiz2 ? DARKGRAY : SKYBLUE);
        DrawText("Game 2", screenWidth / 2 + 315, screenHeight / 2 - 290, 50, WHITE);
        if (isMouseOverQuiz2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ;
        }

        bool isMouseOverQuiz3 = CheckCollisionPointRec(mousePosition, quiz3Button);
        DrawRectangleRec(quiz3Button, isMouseOverQuiz3 ? DARKGRAY : SKYBLUE);
        DrawText("Game 3", screenWidth / 2 - 385, screenHeight / 2 - 70, 50, WHITE);
        if (isMouseOverQuiz3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ;
        }

        bool isMouseOverQuiz4 = CheckCollisionPointRec(mousePosition, quiz4Button);
        DrawRectangleRec(quiz4Button, isMouseOverQuiz4 ? DARKGRAY : SKYBLUE);
        DrawText("Game 4", screenWidth / 2 + 315, screenHeight / 2 - 70, 50, WHITE);
        if (isMouseOverQuiz4 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ;
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