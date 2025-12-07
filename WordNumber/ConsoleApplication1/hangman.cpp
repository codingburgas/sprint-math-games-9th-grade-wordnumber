#include "games.h"

vector<string> words = {
    "TREE", "RIVER", "MOUNTAIN", "FOREST", "SUNLIGHT", "OCEAN", "RAINBOW",
    "STONE", "BREEZE", "THUNDER", "MEADOW", "VALLEY", "HURRICANE",

    "PENCIL", "NOTEBOOK", "TEACHER", "CLASSROOM", "STUDENT", "MARKER", "BACKPACK",
    "ERASER", "CHALK", "HOMEWORK", "SCIENCE", "HISTORY", "GEOGRAPHY",

    "CAT", "DOG", "HORSE", "MONKEY", "EAGLE", "DOLPHIN", "PENGUIN",
    "TIGER", "LION", "GIRAFFE", "FROG", "WOLF", "SNAKE", "RABBIT",

    "APPLE", "BREAD", "BUTTER", "BANANA", "PIZZA", "CHOCOLATE", "ORANGE",
    "BURGER", "PASTA", "CHEESE", "SALAD", "COOKIE", "SANDWICH",

    "WINDOW", "TABLE", "LAMP", "PHONE", "BOTTLE", "SCISSORS", "UMBRELLA",
    "CHAIR", "PILLOW", "BLANKET", "KEYBOARD", "HEADPHONES", "BACKPACK",

    "AIRPORT", "VILLAGE", "MARKET", "HARBOR", "DESERT", "ISLAND", "CASTLE",
    "STATION", "COUNTRY", "CITY", "TUNNEL", "BRIDGE", "TEMPLE",

    "ASTEROID", "TELESCOPE", "DISCOVERY", "ARCHITECTURE", "ADVENTURE",
    "HARMONIZE", "BLUEPRINT", "GALAXY", "INVENTION", "JOURNEY",

    "COMPUTER", "PROGRAM", "KEYBOARD", "HANGMAN", "LIBRARY", "FUNCTION",
    "VARIABLE", "ALGORITHM", "NETWORK", "DATABASE", "OPERATOR",

    "CANDLE", "FLOWER", "GARDEN", "ROCKET", "PLANET", "YACHT",
    "FACTORY", "THEATER", "MUSEUM", "HOSPITAL", "MARKETPLACE",

    "SUNSET", "SUNRISE", "CLOUD", "WEATHER", "CLIMATE", "LIGHTNING",
    "TORNADO", "EARTHQUAKE", "WILDFIRE", "TSUNAMI"
};

string chooseWord() {
    srand(time(nullptr));
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
