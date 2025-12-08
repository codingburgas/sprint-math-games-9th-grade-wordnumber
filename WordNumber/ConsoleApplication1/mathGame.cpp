#include "games.h"
#include "raylib.h"

void NewQuestion(int& a, int& b, int& correct, int answers[4])
{
    a = GetRandomValue(1, 20);
    b = GetRandomValue(1, 20);
    correct = a + b;

    int correctIndex = GetRandomValue(0, 3);

    for (int i = 0; i < 4; i++)
    {
        if (i == correctIndex)
        {
            answers[i] = correct;
        }
        else
        {
            int wrong;
            bool unique;

            do
            {
                wrong = correct + GetRandomValue(-10, 10);
                if (wrong <= 0) wrong = GetRandomValue(1, 40);

                unique = (wrong != correct);
                for (int j = 0; j < i && unique; j++)
                    if (answers[j] == wrong) unique = false;

            } while (!unique);

            answers[i] = wrong;
        }
    }
}

void startMathGame()
{
    int score = 0;
    int questions = 0;

    int a = 0, b = 0, correct = 0;
    int answers[4];

    bool finished = false;
    bool won = false;
    float finishAnimTime = 0.0f;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    Rectangle answerButtons[4];

    float btnWidth = 340.0f;
    float btnHeight = 70.0f;
    float spacing = 15.0f;

    float totalHeight = 4 * btnHeight + 3 * spacing;
    float startY = screenH - totalHeight - 50.0f;
    float btnX = (screenW - btnWidth) / 2.0f;

    for (int i = 0; i < 4; i++)
        answerButtons[i] = { btnX, startY + i * (btnHeight + spacing), btnWidth, btnHeight };

    Color buttonColors[4] = { ORANGE, SKYBLUE, LIME, PINK };

    Rectangle backBtn = { (screenW - 220) / 2.0f - 130.0f, 420.0f, 220.0f, 60.0f };
    Rectangle playAgainBtn = { (screenW - 220) / 2.0f + 130.0f, 420.0f, 220.0f, 60.0f };

    NewQuestion(a, b, correct, answers);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        float dt = GetFrameTime();

        if (finished) finishAnimTime += dt;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (finished)
            {
                if (CheckCollisionPointRec(mouse, backBtn)) return;

                if (CheckCollisionPointRec(mouse, playAgainBtn))
                {
                    score = 0;
                    questions = 0;
                    finished = false;
                    won = false;
                    finishAnimTime = 0.0f;
                    NewQuestion(a, b, correct, answers);
                }
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (CheckCollisionPointRec(mouse, answerButtons[i]))
                    {
                        if (answers[i] == correct) score++;

                        questions++;

                        if (questions >= 10)
                        {
                            finished = true;
                            won = (score >= 5);
                            finishAnimTime = 0.0f;
                        }
                        else
                        {
                            NewQuestion(a, b, correct, answers);
                        }
                    }
                }
            }
        }

        BeginDrawing();

        Color topColor = { 30, 30, 60, 255 };
        Color bottomColor = { 10, 160, 200, 255 };
        DrawRectangleGradientV(0, 0, screenW, screenH, topColor, bottomColor);

        const char* title = "MATH GAMES";
        int titleSize = 60;
        int titleWidth = MeasureText(title, titleSize);
        DrawText(title, (screenW - titleWidth) / 2, 25, titleSize, RAYWHITE);

        if (finished)
        {
            for (int i = 0; i < 40; i++)
            {
                float t = finishAnimTime * 2.0f;
                int radius = GetRandomValue(4, 9);
                int x = (i * 53 + (int)(t * 40)) % screenW;
                int y = (i * 37 + (int)(t * 30)) % screenH;

                Color c = won ? Color{ 180,255,180,120 } : Color{ 255,180,180,120 };
                DrawCircle((float)x, (float)y, (float)radius, c);
            }

            float pulse = 1.0f + 0.1f * (float)std::sin(finishAnimTime * 4.0f);
            int animSize = (int)(40 * pulse);

            const char* mainText = won ? "YOU WIN!" : "TRY AGAIN!";
            int mainWidth = MeasureText(mainText, animSize);
            DrawText(mainText, (screenW - mainWidth) / 2, 150, animSize, won ? LIME : PINK);

            const char* resultText = TextFormat("Your score: %i / 10", score);
            int resultWidth = MeasureText(resultText, 35);
            DrawText(resultText, (screenW - resultWidth) / 2, 220, 35, RAYWHITE);

            const char* subText = won ? "Great job! Keep going!" : "No worries, try again!";
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

        int qCardW = 560;
        int qCardH = 90;

        int qCardX = (screenW - qCardW) / 2;
        int qCardY = screenH / 4;

        Rectangle qCard = { (float)qCardX, (float)qCardY, (float)qCardW, (float)qCardH };

        DrawRectangleRounded(qCard, 0.3f, 10, Fade(BLACK, 0.25f));
        DrawRectangleRoundedLines(qCard, 0.3f, 10, 3, RAYWHITE);

        const char* qText = TextFormat("%i + %i = ?", a, b);
        int qFont = 55;
        int qWidth = MeasureText(qText, qFont);
        DrawText(qText, qCardX + (qCardW - qWidth) / 2, qCardY + 18, qFont, RAYWHITE);

        const char* scoreText = TextFormat("QUESTION %i / 10   |   SCORE: %i", questions + 1, score);
        int sWidth = MeasureText(scoreText, 35);
        DrawText(scoreText, (screenW - sWidth) / 2, qCardY + qCardH + 20, 35, RAYWHITE);

        for (int i = 0; i < 4; i++)
        {
            bool hover = CheckCollisionPointRec(mouse, answerButtons[i]);
            Color fill = hover ? Fade(buttonColors[i], 0.95f) : Fade(buttonColors[i], 0.7f);

            DrawRectangleRounded(answerButtons[i], 0.4f, 10, fill);
            DrawRectangleRoundedLines(answerButtons[i], 0.4f, 10, 2, RAYWHITE);

            const char* ansText = TextFormat("%i", answers[i]);
            int ansW = MeasureText(ansText, 40);

            DrawText(ansText,
                answerButtons[i].x + (answerButtons[i].width - ansW) / 2,
                answerButtons[i].y + 18,
                40, RAYWHITE);
        }

        EndDrawing();
    }
}
