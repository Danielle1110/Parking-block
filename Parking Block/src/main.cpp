#include "parkingblock.h"

int main() {
    double startTime = 0.0;
    double endTime = 0.0;


    const int screenWidth = 1400;  
    const int screenHeight = 1050;  
    InitWindow(screenWidth, screenHeight, "Parking Block");
    Texture2D backgroundTexture = LoadTexture("resources/parking.png");
    Texture2D treeTexture = LoadTexture("resources/tree.png");
    std::vector<Texture2D> carTexture = {
        LoadTexture("resources/car_red.png"),
        LoadTexture("resources/car_green.png"),
        LoadTexture("resources/car_pink.png"),
        LoadTexture("resources/car_blue.png"),
        LoadTexture("resources/car_yellow.png"),
        LoadTexture("resources/car_white.png"),
        LoadTexture("resources/car_purple.png")
    };

    const int gridSize = 100;
    const int gridRows = 10;
    const int gridCols = 14;

    
    std::vector<Wall> walls;
    std::vector<Car> cars;
    int level = 1;
    LoadLevel(cars, walls, carTexture, level); 

    SetTargetFPS(60); 

    Car* selectedCar = nullptr;
    bool win = false;
    GameState gameState = MENU;

    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        switch (gameState) {
            case MENU: {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawText("Parking Block", screenWidth / 2 - MeasureText("Parking Block", 40) / 2, 100, 40, BLACK);

                Rectangle startButton = {screenWidth / 2 - 100, 300, 200, 50};
                Rectangle levelSelectButton = {screenWidth / 2 - 100, 400, 200, 50};
                Rectangle exitButton = {screenWidth / 2 - 100, 500, 200, 50};

                DrawRectangleRec(startButton, LIGHTGRAY);
                DrawRectangleRec(levelSelectButton, LIGHTGRAY);
                DrawRectangleRec(exitButton, LIGHTGRAY);

                DrawText("Start Game", startButton.x + 20, startButton.y + 15, 20, BLACK);
                DrawText("Select Level", levelSelectButton.x + 20, levelSelectButton.y + 15, 20, BLACK);
                DrawText("Exit", exitButton.x + 70, exitButton.y + 15, 20, BLACK);

                EndDrawing();

                if (CheckCollisionPointRec(mousePosition, startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    startTime = 0.0;
                    endTime = 0.0;
                    gameState = GAMEPLAY;
                    level = 1;
                    LoadLevel(cars, walls, carTexture, level);
                    startTime = GetTime();
                }
                if (CheckCollisionPointRec(mousePosition, levelSelectButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    gameState = LEVEL_SELECT;
                }
                if (CheckCollisionPointRec(mousePosition, exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    CloseWindow();
                    return 0;
                }
                break;
            }
            case LEVEL_SELECT: {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawText("Select Level", screenWidth / 2 - MeasureText("Select Level", 30) / 2, 50, 30, BLACK);

                int columns = 5;
                int rows = 2;
                int buttonWidth = 100;
                int buttonHeight = 50;
                int xOffset = (screenWidth - columns * buttonWidth) / (columns + 1);
                int yOffset = (screenHeight - rows * buttonHeight) / (rows + 3);

                for (int i = 1; i <= 10; ++i) {
                    int col = (i - 1) % columns;
                    int row = (i - 1) / columns;
                    Rectangle levelButton = {
                        xOffset + col * (buttonWidth + xOffset),
                        100 + yOffset + row * (buttonHeight + yOffset),
                        buttonWidth,
                        buttonHeight
                    };

                    DrawRectangleRec(levelButton, LIGHTGRAY);
                    DrawText(TextFormat("Level %d", i), levelButton.x + 20, levelButton.y + 10, 20, BLACK);

                    if (CheckCollisionPointRec(mousePosition, levelButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        level = i;
                        LoadLevel(cars, walls, carTexture, i);
                        gameState = GAMEPLAY;
                        win = false;
                        startTime = GetTime();
                        endTime = 0.0;
                    }
                }

                EndDrawing();
                break;
            }
            case GAMEPLAY: {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    selectedCar = nullptr;
                    for (auto& car : cars) {
                        if (CheckCollisionPointRec(mousePosition, car.rect)) {
                            selectedCar = &car;
                            break;
                        }
                    }
                }

                if (selectedCar && !win) {
                    Vector2 movement = {0, 0};

                    if (selectedCar->horizontal) {
                        if (IsKeyPressed(KEY_RIGHT)) movement.x = gridSize;
                        if (IsKeyPressed(KEY_LEFT)) movement.x = -gridSize;
                    } else {
                        if (IsKeyPressed(KEY_DOWN)) movement.y = gridSize;
                        if (IsKeyPressed(KEY_UP)) movement.y = -gridSize;
                    }

                    Rectangle newRect = selectedCar->rect;
                    newRect.x += movement.x;
                    newRect.y += movement.y;

                    if (newRect.x >= 0 && newRect.x + newRect.width <= screenWidth &&
                        newRect.y >= 0 && newRect.y + newRect.height <= screenHeight &&
                        !CheckCollisionWithCars(newRect, cars, *selectedCar) &&
                        !CheckCollisionWithWalls(newRect, walls)) {
                        selectedCar->rect = newRect;
                    }

                    if (selectedCar == &cars[0] && 
                        selectedCar->rect.x + selectedCar->rect.width >= 14 * gridSize &&
                        selectedCar->rect.x + selectedCar->rect.width <= 15 * gridSize &&
                        selectedCar->rect.y == 4 * gridSize) {
                        win = true;
                        endTime = GetTime();
                    }
                }

                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(backgroundTexture, 0, 0, WHITE);

                // DrawGrid(gridRows, gridCols, gridSize);

                for (const auto& car : cars) {
                    Rectangle sourceRec = { 0.0f, 0.0f, (float)car.texture.width, (float)car.texture.height };
                    Rectangle destRec = { car.rect.x, car.rect.y, car.rect.width, car.rect.height };
                    Vector2 origin = { 0.0f, 0.0f };
                    DrawTexturePro(car.texture, sourceRec, destRec, origin, 0.0f, WHITE);
                    if (&car == selectedCar) {
                        DrawRectangleLinesEx(car.rect, 3, DARKGRAY);
                    }
                }

                for (const auto& wall : walls) {
                    DrawTexture(treeTexture, wall.rect.x, wall.rect.y, RAYWHITE);
                }


                DrawTargetPosition(gridSize);

                DrawText(TextFormat("Level: %d", level), 10, 10, 30, WHITE);
                DrawText(TextFormat("Use arrows for control"), 10, 40, 30, WHITE);

                double elapsedTime = win ? endTime - startTime : GetTime() - startTime;
                DrawText(TextFormat("Time: %.2f s", elapsedTime), screenWidth - 200, 10, 20, WHITE);

                
                if (win) {
                    DrawText("You Win! Press M to return to the menu.", 325, screenHeight / 2, 40, WHITE);

                    if (level < 10) {
                        DrawText("Press R for the next level.", 325, screenHeight / 2 + 50, 30, WHITE);
                        if (IsKeyPressed(KEY_R)) {
                            level++;
                            win = false;
                            LoadLevel(cars, walls, carTexture, level);
                            startTime = GetTime();
                            endTime = 0.0;
                        }
                    }

                    if (IsKeyPressed(KEY_M)) {
                        gameState = MENU;
                        level = 1;
                        win = false;
                    }
                }

                EndDrawing();
                break;
            }

        }
    }
    for (auto& texture : carTexture) {
        UnloadTexture(texture);
    }
    UnloadTexture(treeTexture);
    UnloadTexture(backgroundTexture);

    CloseWindow();
    return 0;
}