#include "hangman.h"

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

void hangman() {
    string secret = chooseWord();
    set<char> guessed;
    int wrong = 0;

    vector<char> alphabet;
    for (char c = 'A'; c <= 'Z'; c++)
        alphabet.push_back(c);

    bool won = false, lost = false;

    while (!WindowShouldClose()) {

        if (!won && !lost) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 m = GetMousePosition();
                for (int i = 0; i < 26; i++) {
                    int bx = 420 + (i % 7) * 50;
                    int by = 120 + (i / 7) * 50;
                    Rectangle rec = { (float)bx, (float)by, 40, 40 };

                    if (CheckCollisionPointRec(m, rec)) {
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
        for (char c : secret) {
            if (!guessed.count(c)) {
                all = false;
                break;
            }
        }
        if (all) won = true;
        if (wrong >= 6) lost = true;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawLine(50, 350, 200, 350, BLACK);
        DrawLine(125, 350, 125, 100, BLACK);
        DrawLine(125, 100, 250, 100, BLACK);
        DrawLine(250, 100, 250, 150, BLACK);

        if (wrong > 0) DrawCircle(250, 170, 20, BLACK);
        if (wrong > 1) DrawLine(250, 190, 250, 250, BLACK);
        if (wrong > 2) DrawLine(250, 210, 220, 230, BLACK);
        if (wrong > 3) DrawLine(250, 210, 280, 230, BLACK);
        if (wrong > 4) DrawLine(250, 250, 230, 300, BLACK);
        if (wrong > 5) DrawLine(250, 250, 270, 300, BLACK);

        string shown;
        for (char c : secret)
            shown += guessed.count(c) ? string(1, c) + " " : "_ ";

        DrawText(shown.c_str(), 50, 400, 40, DARKBLUE);

        for (int i = 0; i < 26; i++) {
            int bx = 420 + (i % 7) * 50;
            int by = 120 + (i / 7) * 50;
            Rectangle rec = { (float)bx, (float)by, 40, 40 };

            Color col = guessed.count(alphabet[i]) ? GRAY : LIGHTGRAY;
            DrawRectangleRec(rec, col);
            DrawRectangleLines(bx, by, 40, 40, BLACK);

            char txt[2] = { alphabet[i], 0 };
            DrawText(txt, bx + 12, by + 8, 20, BLACK);
        }

        if (won) DrawText("YOU WIN! (Press ESC)", 420, 450, 30, GREEN);
        if (lost) {
            DrawText("YOU LOSE! (Press ESC)", 420, 450, 30, RED);
            DrawText(("Word: " + secret).c_str(), 420, 490, 25, BLACK);
        }

        EndDrawing();

    }
}