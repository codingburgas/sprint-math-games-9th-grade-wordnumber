#include "games.h"

void crossword()
{
    const int rows = 7;
    const int cols = 5;

    const char* words[rows] = { "APPLE", "BREAD", "CANDY", "DATES", "ELDER", "FISHY", "GHOST" };

    const char* hints[rows] = {
        "A common fruit, usually red or green",
        "Food made from flour, baked until brown",
        "Sweet treat, often comes in chocolate",
        "Dried fruit from a sweet palm tree",
        "An older person, also called senior",
        "Aquatic animal, often in a pond or sea",
        "Spooky entity, appears in stories"
    };

    char secret[rows + 1] = { 0 };
    for (int i = 0; i < rows; i++) secret[i] = words[i][0];

    char display[rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            display[i][j] = ' ';

    int curRow = 0, curCol = 0;

    while (!WindowShouldClose()) {
        int key = GetKeyPressed();

        if (key >= 'A' && key <= 'Z') {
            display[curRow][curCol] = (char)key;

            if (curCol < cols - 1) curCol++;
            else if (curRow < rows - 1) {
                curCol = 0;
                curRow++;
            }
        }

        if (key == KEY_BACKSPACE) {
            display[curRow][curCol] = ' ';
            if (curCol > 0) curCol--;
            else if (curRow > 0) {
                curRow--;
                curCol = cols - 1;
            }
        }

        if (key == KEY_RIGHT) curCol = (curCol + 1) % cols;
        if (key == KEY_LEFT)  curCol = (curCol - 1 + cols) % cols;
        if (key == KEY_DOWN)  curRow = (curRow + 1) % rows;
        if (key == KEY_UP)    curRow = (curRow - 1 + rows) % rows;

        bool allCorrect = true;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (words[i][j] != display[i][j])
                    allCorrect = false;

        bool secretCorrect = true;
        for (int i = 0; i < rows; i++)
            if (display[i][0] != secret[i])
                secretCorrect = false;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Elementary Crossword", 180, 20, 30, DARKBLUE);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int x = 100 + j * 60;
                int y = 100 + i * 60;
                Color bg = (i == curRow && j == curCol) ? SKYBLUE : LIGHTGRAY;
                DrawRectangle(x, y, 50, 50, bg);
                DrawRectangleLines(x, y, 50, 50, BLACK);

                if (display[i][j] != ' ') {
                    Color col = (display[i][j] == words[i][j]) ? GREEN : RED;
                    char letter[2] = { display[i][j], '\0' };
                    DrawText(letter, x + 15, y + 10, 30, col);
                }
            }

            DrawText(hints[i], 100 + cols * 60 + 20, 100 + i * 60 + 10, 20, DARKGRAY);
        }

        if (secretCorrect)
            DrawText("Secret word solved!", 400, 500, 25, BLUE);

        if (allCorrect)
            DrawText("You solved all words!", 250, 550, 30, GREEN);

        EndDrawing();
    }
}
