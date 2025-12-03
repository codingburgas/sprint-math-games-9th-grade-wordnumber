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

void startMathGame() {

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
            sprintf_s(scoreText, "Score: %d/10", score);
            DrawText(scoreText, 200, 200, 60, BLACK);

            if (score >= 6)
                DrawText("Good job!", 200, 300, 50, GREEN);
            else
                DrawText("You need more practice!", 200, 300, 50, RED);

            EndDrawing();
            continue;
        }

        char q[50];
        sprintf_s(q, "%d %c %d = ?", a, op, b);
        DrawText(q, 200, 150, 60, BLACK);

        for (int i = 0; i < 4; i++) {
            DrawRectangleRec(answerButtons[i], LIGHTGRAY);

            char t[20];
            sprintf_s(t, "%d", buttonValues[i]);
            DrawText(t, answerButtons[i].x + 70, answerButtons[i].y + 10, 40, BLACK);
        }

        char scoreText[40];
        sprintf_s(scoreText, "Score: %d", score);
        DrawText(scoreText, GetScreenWidth() - 350, 40, 40, DARKGREEN);

        EndDrawing();
    }
}




void crossword() {
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

