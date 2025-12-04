#include "games.h"
#include "raylib.h"
#include <vector>
#include <string>
#include <set>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

static vector<string> loadWords()
{
    vector<string> words;
    ifstream file("hangmanWords.txt");

    if (!file.is_open()) {
        words = { "ERROR", "NOFILE", "WORDS", "POORLY", "GIRLY", "HEADER", "FILES" };
        return words;
    }

    string word;
    while (getline(file, word)) {
        if (!word.empty())
            words.push_back(word);
    }

    return words;
}

static string chooseWord()
{
    static vector<string> words = loadWords();
    if (words.empty()) return "EMPTY";
    srand((unsigned int)time(nullptr));
    return words[rand() % words.size()];
}

void hangman()
{
    string secret = chooseWord();
    set<char> guessed;
    int wrong = 0;

    vector<char> alphabet;
    for (char c = 'A'; c <= 'Z'; c++)
        alphabet.push_back(c);

    bool won = false, lost = false;

    const int layoutWidth = 900;
    const int layoutHeight = 700;

    while (!WindowShouldClose()) {

        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        int ox = (sw - layoutWidth) / 2;
        int oy = (sh - layoutHeight) / 2;

        Color neon = Color{ 0, 255, 180, 255 };
        Color whiteC = WHITE;

        if (!won && !lost) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 m = GetMousePosition();

                for (int i = 0; i < 26; i++) {
                    int bx = ox + 420 + (i % 7) * 60;
                    int by = oy + 150 + (i / 7) * 60;
                    Rectangle r = { (float)bx, (float)by, 50, 50 };

                    if (CheckCollisionPointRec(m, r)) {
                        char letter = alphabet[i];
                        if (!guessed.count(letter)) {
                            guessed.insert(letter);
                            if (secret.find(letter) == string::npos)
                                wrong++;
                        }
                    }
                }
            }
        }

        bool all = true;
        for (char c : secret)
            if (!guessed.count(c))
                all = false;

        if (all) won = true;
        if (wrong >= 6) lost = true;

        BeginDrawing();
        ClearBackground(Color{ 10, 10, 20, 255 });

        DrawText("HANGMAN", ox + 310, oy + 20, 50, neon);

        DrawLine(ox + 50, oy + 500, ox + 200, oy + 500, neon);
        DrawLine(ox + 125, oy + 500, ox + 125, oy + 250, neon);
        DrawLine(ox + 125, oy + 250, ox + 250, oy + 250, neon);
        DrawLine(ox + 250, oy + 250, ox + 250, oy + 300, neon);

        if (wrong > 0) DrawCircle(ox + 250, oy + 320, 20, neon);
        if (wrong > 1) DrawLine(ox + 250, oy + 340, ox + 250, oy + 400, neon);
        if (wrong > 2) DrawLine(ox + 250, oy + 360, ox + 220, oy + 380, neon);
        if (wrong > 3) DrawLine(ox + 250, oy + 360, ox + 280, oy + 380, neon);
        if (wrong > 4) DrawLine(ox + 250, oy + 400, ox + 230, oy + 450, neon);
        if (wrong > 5) DrawLine(ox + 250, oy + 400, ox + 270, oy + 450, neon);

        string shown;
        for (char c : secret)
            shown += guessed.count(c) ? string(1, c) + " " : "_ ";

        DrawText(shown.c_str(), ox + 50, oy + 550, 50, neon);

        for (int i = 0; i < 26; i++) {
            int bx = ox + 420 + (i % 7) * 60;
            int by = oy + 150 + (i / 7) * 60;

            Rectangle r = { (float)bx, (float)by, 50, 50 };
            bool hovered = CheckCollisionPointRec(GetMousePosition(), r);
            bool isGuessed = guessed.count(alphabet[i]) > 0;

            Color border;
            Color fill;

            if (isGuessed) {
                border = Color{ 80, 80, 80, 255 };
                fill = Color{ 20, 20, 20, 255 };
            }
            else {
                border = hovered ? whiteC : neon;
                fill = Color{ 0, 0, 0, 255 };
            }

            DrawRectangleRec(r, fill);
            DrawRectangleLinesEx(r, 3, border);

            char txt[2] = { alphabet[i], 0 };
            DrawText(txt, bx + 17, by + 12, 25, neon);
        }

        if (won) DrawText("YOU WIN! (ESC)", ox + 420, oy + 500, 35, GREEN);
        if (lost) {
            DrawText("YOU LOSE! (ESC)", ox + 420, oy + 500, 35, RED);
            DrawText(("WORD: " + secret).c_str(), ox + 420, oy + 540, 25, neon);
        }

        EndDrawing();
    }
}
