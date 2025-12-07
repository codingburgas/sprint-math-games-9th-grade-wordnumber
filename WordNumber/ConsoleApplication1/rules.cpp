#include "chooseGame.h"
#include "menu.h"
#include "raylib.h"
#include <cmath>
void DrawRoundedRectangle(Rectangle rec, float radius, Color color)
{
    if (radius <= 0.0f)
    {
        DrawRectangleRec(rec, color);
        return;
    }

    if (radius > rec.width / 2.0f) radius = rec.width / 2.0f;
    if (radius > rec.height / 2.0f) radius = rec.height / 2.0f;
    Rectangle centerH{ rec.x + radius, rec.y, rec.width - 2.0f * radius, rec.height };
    Rectangle centerV{ rec.x, rec.y + radius, rec.width, rec.height - 2.0f * radius };

    DrawRectangleRec(centerH, color);
    DrawRectangleRec(centerV, color);
    Vector2 c1{ rec.x + radius,             rec.y + radius };
    Vector2 c2{ rec.x + rec.width - radius, rec.y + radius };
    Vector2 c3{ rec.x + radius,            rec.y + rec.height - radius };
    Vector2 c4{ rec.x + rec.width - radius, rec.y + rec.height - radius };

    DrawCircleV(c1, radius, color);
    DrawCircleV(c2, radius, color);
    DrawCircleV(c3, radius, color);
    DrawCircleV(c4, radius, color);
}
void DrawRoundedRectangleLines(Rectangle rec, float radius, float thick, Color color)
{
    if (thick <= 0.0f) return;

    if (radius <= 0.0f)
    {
        DrawRectangleLinesEx(rec, thick, color);
        return;
    }

    if (radius > rec.width / 2.0f) radius = rec.width / 2.0f;
    if (radius > rec.height / 2.0f) radius = rec.height / 2.0f;

    int steps = (int)thick;

    for (int i = 0; i < steps; i++)
    {
        Rectangle r{
            rec.x + (float)i,
            rec.y + (float)i,
            rec.width - 2.0f * (float)i,
            rec.height - 2.0f * (float)i
        };

        float rad = radius - (float)i;
        if (rad < 0.0f) rad = 0.0f;
        DrawLine(
            (int)(r.x + rad), (int)r.y,
            (int)(r.x + r.width - rad), (int)r.y,
            color
        );
        DrawLine(
            (int)(r.x + rad), (int)(r.y + r.height),
            (int)(r.x + r.width - rad), (int)(r.y + r.height),
            color
        );
        DrawLine(
            (int)r.x, (int)(r.y + rad),
            (int)r.x, (int)(r.y + r.height - rad),
            color
        );
        DrawLine(
            (int)(r.x + r.width), (int)(r.y + rad),
            (int)(r.x + r.width), (int)(r.y + r.height - rad),
            color
        );

        Vector2 c1{ r.x + rad,             r.y + rad };
        Vector2 c2{ r.x + r.width - rad,   r.y + rad };
        Vector2 c3{ r.x + rad,             r.y + r.height - rad };
        Vector2 c4{ r.x + r.width - rad,   r.y + r.height - rad };

        DrawCircleLines((int)c1.x, (int)c1.y, rad, color);
        DrawCircleLines((int)c2.x, (int)c2.y, rad, color);
        DrawCircleLines((int)c3.x, (int)c3.y, rad, color);
        DrawCircleLines((int)c4.x, (int)c4.y, rad, color);
    }
}
void rules()
{
    const int screenW = GetScreenWidth();
    const int screenH = GetScreenHeight();

    Rectangle panel{
        screenW / 2.0f - 400.0f,
        screenH / 2.0f - 250.0f,
        800.0f,
        500.0f
    };

    Rectangle toGame{
        panel.x + panel.width - 210.0f,
        panel.y + panel.height - 70.0f,
        180.0f,
        50.0f
    };

    while (!WindowShouldClose())
    {
        SetExitKey(KEY_ESCAPE);

        float t = (float)GetTime();
        Vector2 mouse = GetMousePosition();
        bool hoverStart = CheckCollisionPointRec(mouse, toGame);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleGradientV(
            0, 0, screenW, screenH,
            Color{ 10, 10, 30, 255 },
            Color{ 5, 0, 40, 255 }
        );

        float planetY = screenH / 2.0f + 30.0f + sinf(t * 0.7f) * 10.0f;
        DrawCircleGradient(
            (int)(panel.x - 80.0f),
            (int)planetY,
            160.0f,
            Color{ 50, 200, 255, 255 },
            Color{ 10, 30, 80, 255 }
        );
        DrawCircleLines(
            (int)(panel.x - 80.0f),
            (int)planetY,
            170.0f,
            Color{ 0, 255, 180, 120 }
        );

        Color neon = Color{ 0, 255, 200, 255 };
        Color panelFill = Color{ 10, 10, 25, 230 };

        DrawRoundedRectangle(panel, 24.0f, panelFill);
        DrawRoundedRectangleLines(panel, 24.0f, 3.0f, neon);
        const char* title = "WordNumber RULES";
        int titleFontSize = 40;
        int titleWidth = MeasureText(title, titleFontSize);
        DrawText(
            title,
            (int)(panel.x + (panel.width - (float)titleWidth) / 2.0f),
            (int)(panel.y + 20),
            titleFontSize,
            neon
        );
        int textSize = 22;
        int textX = (int)panel.x + 60;
        int textY = (int)panel.y + 90;
        int lineGap = 35;

        DrawText("Welcome to our space quiz!", textX, textY, textSize, RAYWHITE);
        DrawText("Travel through the solar system and", textX, textY + lineGap, textSize, RAYWHITE);
        DrawText("answer questions to earn points.", textX, textY + 2 * lineGap, textSize, RAYWHITE);
        DrawText("Use the mouse to choose an answer,", textX, textY + 3 * lineGap, textSize, RAYWHITE);
        DrawText("then press ENTER to go to the next.", textX, textY + 4 * lineGap, textSize, RAYWHITE);
        DrawText("Try to finish with the highest score!", textX, textY + 5 * lineGap, textSize, RAYWHITE);

        for (int i = 0; i < 5; i++)
        {
            DrawCircle(textX - 20, textY + i * lineGap + 10, 5, neon);
        }
        Color startFill = hoverStart ? Color{ 0, 200, 160, 255 } : Color{ 0, 140, 120, 255 };
        Color startBorder = Color{ 0, 255, 200, 255 };

        DrawRoundedRectangle(toGame, 18.0f, startFill);
        DrawRoundedRectangleLines(toGame, 18.0f, 2.0f, startBorder);

        const char* startText = "CHOOSE GAME";
        int startFontSize = 24;
        int startTextWidth = MeasureText(startText, startFontSize);
        DrawText(
            startText,
            (int)(toGame.x + (toGame.width - (float)startTextWidth) / 2.0f),
            (int)(toGame.y + 10),
            startFontSize,
            RAYWHITE
        );

        DrawText("Press ESC to go back",
            (int)(panel.x + 20),
            (int)(panel.y + panel.height - 40),
            18,
            GRAY);

        EndDrawing();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverStart)
            chooseGame();
    }
}
