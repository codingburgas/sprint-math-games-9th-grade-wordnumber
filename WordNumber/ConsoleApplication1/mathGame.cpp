#include "games.h"
#include "raylib.h"

#include <cstdio>

void startMathGame()
{
    int score = 0;
    int questions = 0;

    int a = 0, b = 0;
    char op = '+';
    int correct = 0;

    bool finished = false;

    Rectangle answerButtons[4];
    for (int i = 0; i < 4; i++) {
        answerButtons[i] = { 200.0f, 300.0f + i * 80.0f, 200.0f, 60.0f };
    }

    int buttonValues[4];

    Rectangle backBtn = { 20, 20, 160, 60 };

    auto MakeQuestion = [&]() {

        int operation = GetRandomValue(0, 2);

        if (operation == 0) op = '+';
        if (operation == 1) op = '-';
        if (operation == 2) op = '*';

        if (op == '+') {
            a = GetRandomValue(1, 20);
            b = GetRandomValue(1, 20);
            correct = a + b;
        }
        if (op == '-') {
            a = GetRandomValue(1, 20);
            b = GetRandomValue(1, a);
            correct = a - b;
        }
        if (op == '*') {
            a = GetRandomValue(1, 10);
            b = GetRandomValue(1, 10);
            correct = a * b;
        }

        int correctIndex = GetRandomValue(0, 3);

        for (int i = 0; i < 4; i++) {
            if (i == correctIndex) {
                buttonValues[i] = correct;
            }
            else {
                int wrong = correct + GetRandomValue(-10, 10);
                if (wrong <= 0) wrong = 1 + GetRandomValue(1, 15);
                if (wrong == correct) wrong += 3;
                buttonValues[i] = wrong;
            }
        }
        };

    MakeQuestion();

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();

            if (CheckCollisionPointRec(m, backBtn)) return;

            if (!finished) {
                for (int i = 0; i < 4; i++) {
                    if (CheckCollisionPointRec(m, answerButtons[i])) {

                        if (buttonValues[i] == correct) score++;

                        questions++;

                        if (questions >= 10) {
                            finished = true;
                        }
                        else {
                            MakeQuestion();
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(backBtn, LIGHTGRAY);
        DrawText("BACK", (int)backBtn.x + 25, (int)backBtn.y + 15, 30, BLACK);

        if (finished) {

            DrawText("RESULT:", GetScreenWidth() - 350, 40, 50, DARKBLUE);

            char scoreText[50];
#ifdef _MSC_VER
            sprintf_s(scoreText, "Score: %d/10", score);
#else
            sprintf(scoreText, "Score: %d/10", score);
#endif
            DrawText(scoreText, 200, 200, 60, BLACK);

            if (score >= 6)
                DrawText("Good job!", 200, 300, 50, GREEN);
            else
                DrawText("You need more practice!", 200, 300, 50, RED);

            EndDrawing();
            continue;
        }

        char q[50];
#ifdef _MSC_VER
        sprintf_s(q, "%d %c %d = ?", a, op, b);
#else
        sprintf(q, "%d %c %d = ?", a, op, b);
#endif
        DrawText(q, 200, 150, 60, BLACK);

        for (int i = 0; i < 4; i++) {
            DrawRectangleRec(answerButtons[i], LIGHTGRAY);

            char t[20];
#ifdef _MSC_VER
            sprintf_s(t, "%d", buttonValues[i]);
#else
            sprintf(t, "%d", buttonValues[i]);
#endif
            DrawText(t, answerButtons[i].x + 70, answerButtons[i].y + 10, 40, BLACK);
        }

        char scoreText[40];
#ifdef _MSC_VER
        sprintf_s(scoreText, "Score: %d", score);
#else
        sprintf(scoreText, "Score: %d", score);
#endif
        DrawText(scoreText, GetScreenWidth() - 350, 40, 40, DARKGREEN);

        EndDrawing();
    }
}
