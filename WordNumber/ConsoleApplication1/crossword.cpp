#define _CRT_SECURE_NO_WARNINGS
#include "games.h"
#include "raylib.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#define WORD_LEN 6
#define HINT_LEN 200

struct Entry {
    char word[WORD_LEN];
    char hint[HINT_LEN];
};

void crossword() {
    const int rows = 7;
    const int cols = 5;

    Entry entries[] = {
        {"APPLE", "A common fruit, usually red or green"},
        {"BREAD", "Food made from flour, baked until brown"},
        {"CANDY", "Sweet treat made with sugar"},
        {"LEMON", "Yellow sour fruit"},
        {"MOUSE", "Small animal, likes cheese"},
        {"GHOST", "Spooky entity in stories"},
        {"HONEY", "Sweet food made by bees"},
        {"JUICE", "Drink made from fruits"},
        {"FISHY", "Animal that swims"},
        {"DATES", "Dried fruit from palm tree"},
        {"ELDER", "Older person or senior"},
        {"CLOCK", "Device that shows time"},
        {"PLANT", "A green living organism"},
        {"SMILE", "A happy face expression"},
        {"SUGAR", "Sweet white crystals"},
        {"LIGHT", "Makes things bright"},
        {"MAGIC", "Something mysterious"},
        {"STONE", "Hard piece of rock"},
        {"BOARD", "Flat wooden panel"},
        {"WATER", "Liquid you drink"}
    };

    int entryCount = sizeof(entries) / sizeof(entries[0]);

    const char* words[rows];
    const char* hints[rows];

    char secret[rows + 1];
    char display[rows][cols];
    bool jokerUsed[rows];

    int curRow = 0, curCol = 0;
    int activeRow = 0;

    enum GameState { PLAYING, FINISHED };
    GameState gameState = PLAYING;

    float finishAnimTime = 0.0f;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    Rectangle backBtn = { (screenW - 220) / 2.0f - 130.0f, 420.0f, 220.0f, 60.0f };
    Rectangle playAgainBtn = { (screenW - 220) / 2.0f + 130.0f, 420.0f, 220.0f, 60.0f };

    auto initGame = [&]() {
        int idx[200];
        for (int i = 0; i < entryCount; i++) idx[i] = i;

        for (int i = entryCount - 1; i > 0; i--) {
            int j = GetRandomValue(0, i);
            int t = idx[i];
            idx[i] = idx[j];
            idx[j] = t;
        }

        for (int i = 0; i < rows; i++) {
            words[i] = entries[idx[i]].word;
            hints[i] = entries[idx[i]].hint;
        }

        for (int i = 0; i < rows; i++) secret[i] = words[i][0];
        secret[rows] = '\0';

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) display[i][j] = ' ';
            jokerUsed[i] = false;
        }

        curRow = 0;
        curCol = 0;
        activeRow = 0;
        gameState = PLAYING;
        finishAnimTime = 0.0f;
        };

    initGame();

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        float dt = GetFrameTime();

        if (gameState == FINISHED) finishAnimTime += dt;

        int key = GetKeyPressed();

        if (gameState == PLAYING) {
            if (key >= KEY_A && key <= KEY_Z) {
                char c = 'A' + (key - KEY_A);
                display[activeRow][curCol] = c;
                if (curCol < cols - 1) curCol++;
            }

            if (key == KEY_BACKSPACE) {
                if (display[activeRow][curCol] == ' ') {
                    if (curCol > 0) curCol--;
                }
                display[activeRow][curCol] = ' ';
            }

            if (key == KEY_RIGHT && curCol < cols - 1) curCol++;
            if (key == KEY_LEFT && curCol > 0)        curCol--;

            if (key == KEY_J && !jokerUsed[activeRow]) {
                for (int j = 0; j < cols; j++) {
                    if (display[activeRow][j] != words[activeRow][j]) {
                        display[activeRow][j] = words[activeRow][j];
                        curCol = (j < cols - 1) ? j + 1 : j;
                        jokerUsed[activeRow] = true;
                        break;
                    }
                }
            }

            bool currentCorrect = true;
            for (int j = 0; j < cols; j++)
                if (display[activeRow][j] != words[activeRow][j]) currentCorrect = false;

            if (currentCorrect && activeRow < rows - 1) {
                activeRow++;
                curRow = activeRow;
                curCol = 0;
            }

            bool allCorrect = true;
            for (int i = 0; i < rows && allCorrect; i++)
                for (int j = 0; j < cols; j++)
                    if (display[i][j] != words[i][j]) allCorrect = false;

            if (allCorrect) gameState = FINISHED;

            curRow = activeRow;
        }
        else if (gameState == FINISHED) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, backBtn)) return;
                if (CheckCollisionPointRec(mouse, playAgainBtn)) {
                    initGame();
                    continue;
                }
            }
        }

        bool secretCorrect = true;
        for (int i = 0; i < rows; i++)
            if (display[i][0] != secret[i]) secretCorrect = false;

        BeginDrawing();

        Color topColor = { 30, 30, 60, 255 };
        Color bottomColor = { 10, 160, 200, 255 };
        DrawRectangleGradientV(0, 0, screenW, screenH, topColor, bottomColor);

        const char* title = "WORD GAMES";
        int titleSize = 60;
        int titleWidth = MeasureText(title, titleSize);
        DrawText(title, (screenW - titleWidth) / 2, 25, titleSize, RAYWHITE);

        if (gameState == FINISHED) {
            for (int i = 0; i < 40; i++) {
                float t = finishAnimTime * 2.0f;
                int radius = GetRandomValue(4, 9);
                int x = (i * 53 + (int)(t * 40)) % screenW;
                int y = (i * 37 + (int)(t * 30)) % screenH;
                Color c = Color{ 180, 255, 180, 120 };
                DrawCircle((float)x, (float)y, (float)radius, c);
            }

            float pulse = 1.0f + 0.1f * (float)std::sin(finishAnimTime * 4.0f);
            int animSize = (int)(40 * pulse);

            const char* mainText = "CROSSWORD DONE! ";
            int mainWidth2 = MeasureText(mainText, animSize);
            DrawText(mainText, (screenW - mainWidth2) / 2, 150, animSize, LIME);

            const char* resultText = TextFormat("You solved %i / %i words", rows, rows);
            int resultWidth = MeasureText(resultText, 35);
            DrawText(resultText, (screenW - resultWidth) / 2, 220, 35, RAYWHITE);

            const char* subText = "Great job! Want to play again?";
            int subW = MeasureText(subText, 28);
            DrawText(subText, (screenW - subW) / 2, 270, 28, RAYWHITE);

            bool backHover = CheckCollisionPointRec(mouse, backBtn);
            DrawRectangleRounded(backBtn, 0.3f, 8, backHover ? Fade(ORANGE, 0.95f) : Fade(ORANGE, 0.7f));
            DrawRectangleRoundedLines(backBtn, 0.3f, 8, 2, RAYWHITE);
            DrawText("BACK",
                backBtn.x + (backBtn.width - MeasureText("BACK", 30)) / 2,
                backBtn.y + 15, 30, RAYWHITE);

            bool playHover = CheckCollisionPointRec(mouse, playAgainBtn);
            DrawRectangleRounded(playAgainBtn, 0.3f, 8, playHover ? Fade(SKYBLUE, 0.95f) : Fade(SKYBLUE, 0.7f));
            DrawRectangleRoundedLines(playAgainBtn, 0.3f, 8, 2, RAYWHITE);
            DrawText("PLAY AGAIN",
                playAgainBtn.x + (playAgainBtn.width - MeasureText("PLAY AGAIN", 30)) / 2,
                playAgainBtn.y + 15, 30, RAYWHITE);

            EndDrawing();
            continue;
        }

        int gridCell = 72;
        int gridW = cols * gridCell;
        int gridH = rows * gridCell;

        int cardPaddingX = 520;
        int cardPaddingY = 180;

        int cardW = gridW + cardPaddingX;
        int cardH = gridH + cardPaddingY;

        if (cardW > screenW - 40) cardW = screenW - 40;
        if (cardH > screenH - 80) cardH = screenH - 80;

        int cardX = (screenW - cardW) / 2;
        int cardY = screenH / 2 - cardH / 2 + 40;
        Rectangle card = { (float)cardX, (float)cardY, (float)cardW, (float)cardH };

        DrawRectangleRounded(card, 0.08f, 12, Fade(BLACK, 0.35f));
        DrawRectangleRoundedLines(card, 0.08f, 12, 3, RAYWHITE);

        int gridX = cardX + 40;
        int gridY = cardY + (cardH - gridH) / 2;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int x = gridX + j * gridCell;
                int y = gridY + i * gridCell;

                float cellSize = (float)gridCell - 6.0f;
                Rectangle cell = { (float)x, (float)y, cellSize, cellSize };

                Color bg = (i == activeRow && j == curCol) ? SKYBLUE : LIGHTGRAY;
                DrawRectangleRounded(cell, 0.25f, 4, Fade(bg, 0.95f));
                DrawRectangleRoundedLines(cell, 0.25f, 4, 2, BLACK);

                if (display[i][j] != ' ') {
                    Color col = (display[i][j] == words[i][j]) ? GREEN : RED;
                    char letter[2] = { display[i][j], '\0' };
                    int fontSize = 40;
                    int tw = MeasureText(letter, fontSize);
                    DrawText(letter,
                        x + (int)((cellSize - tw) / 2),
                        y + (int)((cellSize - fontSize) / 2),
                        fontSize, col);
                }
            }
        }

        int hintFontSize = 22;
        int hintX = gridX + gridW + 40;
        int hintYLabel = gridY - 40;

        DrawText("Hints:", hintX, hintYLabel, 30, RAYWHITE);

        for (int i = 0; i < rows; i++) {
            float rowCenterY = (float)(gridY + i * gridCell + gridCell / 2);
            int textY = (int)(rowCenterY - hintFontSize / 2);
            Color c = (i == activeRow) ? YELLOW : RAYWHITE;
            DrawText(TextFormat("%i) %s", i + 1, hints[i]), hintX, textY, hintFontSize, c);
        }

        const char* info1 = "Type letters with the keyboard.";
        const char* info2 = "Solve each word in order. Press J for a joker.";
        int infoY = cardY - 50;
        int info1W = MeasureText(info1, 22);
        int info2W = MeasureText(info2, 22);
        DrawText(info1, (screenW - info1W) / 2, infoY, 22, RAYWHITE);
        DrawText(info2, (screenW - info2W) / 2, infoY + 24, 22, RAYWHITE);
        EndDrawing();
    }
}
