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
    Vector2 c3{ rec.x + radius,             rec.y + rec.height - radius };
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

        Vector2 c1{ r.x + rad,           r.y + rad };
        Vector2 c2{ r.x + r.width - rad, r.y + rad };
        Vector2 c3{ r.x + rad,           r.y + r.height - rad };
        Vector2 c4{ r.x + r.width - rad, r.y + r.height - rad };

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
        screenW / 2.0f - 500.0f,
        screenH / 2.0f - 280.0f,
        1000.0f,
        560.0f
    };

    Rectangle toGame{
        panel.x + panel.width - 230.0f,
        panel.y + panel.height - 80.0f,
        200.0f,
        55.0f
    };

    const char* ruleLines[5] = {
        "Welcome to our space quiz adventure!",
        "Travel through the system and answer questions.",
        "Use the mouse to choose the correct answer.",
        "Press ENTER to move to the next challenge.",
        "Try to finish with the highest score!"
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
            Color{ 5, 5, 25, 255 },
            Color{ 2, 0, 40, 255 }
        );

        for (int i = 0; i < 90; i++)
        {
            int sx = (i * 71 + (int)(t * 40)) % screenW;
            int sy = (i * 47 + (int)(t * 30)) % screenH;
            Color starCol = (i % 9 == 0) ? Color{ 120, 200, 255, 180 } : Color{ 180, 180, 220, 120 };
            DrawPixel(sx, sy, starCol);
        }

        float planetY = screenH / 2.0f + 40.0f + sinf(t * 0.7f) * 12.0f;
        DrawCircleGradient(
            (int)(panel.x - 90.0f),
            (int)planetY,
            170.0f,
            Color{ 50, 200, 255, 255 },
            Color{ 10, 30, 80, 255 }
        );
        DrawCircleLines(
            (int)(panel.x - 90.0f),
            (int)planetY,
            182.0f,
            Color{ 0, 255, 180, 120 }
        );

        Rectangle panelShadow{
            panel.x + 8.0f,
            panel.y + 10.0f,
            panel.width,
            panel.height
        };
        DrawRoundedRectangle(panelShadow, 26.0f, Color{ 0, 0, 0, 120 });

        Color neon = Color{ 0, 255, 200, 255 };
        Color panelFill = Color{ 10, 10, 28, 235 };

        DrawRoundedRectangle(panel, 26.0f, panelFill);
        DrawRoundedRectangleLines(panel, 26.0f, 3.0f, neon);

        const char* title = "WordNumber RULES";
        int titleFontSize = 42;
        int titleWidth = MeasureText(title, titleFontSize);
        DrawText(
            title,
            (int)(panel.x + (panel.width - (float)titleWidth) / 2.0f),
            (int)(panel.y + 20),
            titleFontSize,
            neon
        );

        int subtitleFont = 22;
        const char* subtitle = "Learn the rules using these flashcards:";
        int subtitleWidth = MeasureText(subtitle, subtitleFont);
        DrawText(
            subtitle,
            (int)(panel.x + (panel.width - (float)subtitleWidth) / 2.0f),
            (int)(panel.y + 70),
            subtitleFont,
            Color{ 180, 220, 255, 255 }
        );

        int cardCount = 5;
        float cardWidth = panel.width - 120.0f;
        float cardHeight = 70.0f;
        float startY = panel.y + 110.0f;
        float cardGap = 12.0f;

        for (int i = 0; i < cardCount; i++)
        {
            float cx = panel.x + 60.0f;
            float cy = startY + i * (cardHeight + cardGap);

            Rectangle cardRec{
                cx,
                cy,
                cardWidth,
                cardHeight
            };

            Color cardFill = Color{ 18, 20, 45, 235 };
            Color cardBorder = Color{ 70, 200, 255, 220 };

            DrawRoundedRectangle(cardRec, 16.0f, cardFill);
            DrawRoundedRectangleLines(cardRec, 16.0f, 2.0f, cardBorder);

            Vector2 bulletPos{
                cardRec.x + 26.0f,
                cardRec.y + cardRec.height / 2.0f
            };
            DrawCircleV(bulletPos, 6.0f, neon);
            DrawCircleLines((int)bulletPos.x, (int)bulletPos.y, 8.0f, Color{ 0, 255, 200, 120 });

            int ruleFontSize = 22;
            int textX = (int)(cardRec.x + 50.0f);
            int textY = (int)(cardRec.y + (cardRec.height - ruleFontSize) / 2.0f);

            DrawText(ruleLines[i], textX, textY, ruleFontSize, RAYWHITE);
        }

        Color startFill = hoverStart ? Color{ 0, 210, 170, 255 } : Color{ 0, 150, 130, 255 };
        Color startBorder = Color{ 0, 255, 220, 255 };

        DrawRoundedRectangle(toGame, 20.0f, startFill);
        DrawRoundedRectangleLines(toGame, 20.0f, 2.0f, startBorder);

        const char* startText = "CHOOSE GAME";
        int startFontSize = 24;
        int startTextWidth = MeasureText(startText, startFontSize);
        DrawText(
            startText,
            (int)(toGame.x + (toGame.width - (float)startTextWidth) / 2.0f),
            (int)(toGame.y + 14),
            startFontSize,
            RAYWHITE
        );

        const char* escText = "Press ESC to go back to the menu";
        int escFont = 18;
        int escW = MeasureText(escText, escFont);
        DrawText(
            escText,
            (int)(panel.x + (panel.width - escW) / 2.0f),
            (int)(panel.y + panel.height - 40),
            escFont,
            GRAY
        );

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverStart)
            chooseGame();
    }
}
