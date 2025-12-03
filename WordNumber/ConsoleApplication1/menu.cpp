#include "menu.h" 
#include "game.h" 
#include "rules.h"

void menu() {
	const int screenWidth = 1920; 
	const int screenHeight = 1080; 


	InitWindow(screenWidth, screenHeight, "WordNumber");
	Image logoIcon = LoadImage("../images/logo.png");
	SetWindowIcon(logoIcon);
	Vector2 mousePosition = GetMousePosition();
	Texture2D logo = LoadTexture("../images/logo.png");
	Texture2D menuBg = LoadTexture("../images/menuBackground.png");
	const Rectangle startQuizButton = { (screenWidth / 2)-110, (screenHeight / 2) - 60, 270, 100 };
	const Rectangle rulesButton = { (screenWidth / 2)-110, (screenHeight / 2) + 110, 270, 100 };
	const Rectangle exitButton = { (screenWidth / 2)-110, (screenHeight / 2) + 280, 270, 100 };

	while (!WindowShouldClose()) {

		mousePosition = GetMousePosition();

		BeginDrawing();
		DrawTexture(menuBg, 0, 0, RAYWHITE);
		DrawTexture(logo, (screenWidth / 2) - 850, (screenHeight / 2) - 440,RAYWHITE);
		bool isMouseOverStart = CheckCollisionPointRec(mousePosition, startQuizButton);
		DrawRectangleRec(startQuizButton, (isMouseOverStart ? SKYBLUE : BLUE));
		DrawText("Start", screenWidth / 2 -50, screenHeight / 2 - 30, 50, BLACK);

		if (isMouseOverStart && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			game();
		}

		bool isMouseOverRules = CheckCollisionPointRec(mousePosition, rulesButton);
		DrawRectangleRec(rulesButton, (isMouseOverRules ? GREEN : LIME));
		DrawText("Rules", screenWidth / 2 -50, screenHeight / 2 +135, 50, BLACK);

		if (isMouseOverRules && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			rules();
		}


		bool isMouseOverExit = CheckCollisionPointRec(mousePosition, exitButton);
		DrawRectangleRec(exitButton, (isMouseOverExit ? PINK : RED));
		DrawText("Exit", screenWidth / 2-25, screenHeight / 2 + 305, 50, BLACK);

		if (isMouseOverExit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			CloseWindow();
		}

		ClearBackground(DARKBLUE);

		EndDrawing();
	}
}