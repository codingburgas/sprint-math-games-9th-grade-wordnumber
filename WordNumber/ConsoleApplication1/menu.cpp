#include "menu.h"
#include "chooseGame.h"
#include "rules.h"

void menu(bool hasInit) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    if (!hasInit) {
        InitWindow(screenWidth, screenHeight, "WordNumber");
    }

    Image logoIcon = LoadImage("../images/logo.png");
    SetWindowIcon(logoIcon);

    Texture2D logo = LoadTexture("../images/logo.png");
    Texture2D menuBg = LoadTexture("../images/menuBackground.png");

    Rectangle startQuizButton = { (screenWidth / 2) - 200, (screenHeight / 2) - 40, 400, 100 };
    Rectangle rulesButton = { (screenWidth / 2) - 200, (screenHeight / 2) + 100, 400, 100 };
    Rectangle exitButton = { (screenWidth / 2) - 200, (screenHeight / 2) + 240, 400, 100 };

    Color btnStart = Color{ 60, 180, 255, 230 };
    Color btnRules = Color{ 120, 255, 120, 230 };
    Color btnExit = Color{ 255, 80, 80, 230 };

    Color btnStartHover = Color{ 90, 200, 255, 255 };
    Color btnRulesHover = Color{ 150, 255, 150, 255 };
    Color btnExitHover = Color{ 255, 120, 120, 255 };

    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(menuBg, 0, 0, RAYWHITE);

        DrawTexture(logo, (screenWidth / 2) - logo.width / 2, 80, RAYWHITE);

        auto drawButton = [&](Rectangle rect, const char* text, Color base, Color hover) {
            bool isHover = CheckCollisionPointRec(mousePosition, rect);
            Color finalColor = isHover ? hover : base;

            DrawRectangleRounded(rect, 0.3f, 12, Fade(finalColor, 0.92f));
            DrawRectangleRoundedLines(rect, 0.3f, 12, 3, Fade(WHITE, 0.85f));

            int textWidth = MeasureText(text, 50);
            DrawText(text, rect.x + (rect.width - textWidth) / 2, rect.y + 28, 50, BLACK);

            return isHover;
            };

        bool hStart = drawButton(startQuizButton, "Start", btnStart, btnStartHover);
        bool hRules = drawButton(rulesButton, "Rules", btnRules, btnRulesHover);
        bool hExit = drawButton(exitButton, "Exit", btnExit, btnExitHover);

        if (hStart && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            chooseGame();
        }
        if (hRules && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            rules();
        }
        if (hExit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
        }

        EndDrawing();
    }
}
