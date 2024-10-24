#ifndef PARKINGBLOCK_H
#define PARKINGBLOCK_H

#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>

struct Car {
    Rectangle rect;
    Texture2D texture;
    bool horizontal;
};

struct Wall {
    Rectangle rect;
    Color color;
};

bool CheckCollisionWithCars(const Rectangle& r, const std::vector<Car>& cars, const Car& currentCar) {
    for (const auto& car : cars) {
        if (&car != &currentCar && CheckCollisionRecs(r, car.rect)) {
            return true;
        }
    }
    return false;
}

bool CheckCollisionWithWalls(const Rectangle& r, const std::vector<Wall>& walls) {
    for (const auto& wall : walls) {
        if (CheckCollisionRecs(r, wall.rect)) {
            bool sideCollision =
                (r.x + r.width == wall.rect.x || wall.rect.x + wall.rect.width == r.x) &&
                r.y < wall.rect.y + wall.rect.height && r.y + r.height > wall.rect.y;

            bool verticalCollision =
                (r.y + r.height == wall.rect.y || wall.rect.y + wall.rect.height == r.y) &&
                r.x < wall.rect.x + wall.rect.width && r.x + r.width > wall.rect.x;

            if (!sideCollision && !verticalCollision) {
                return true;
            }
        }
    }
    return false;
}

// void DrawGrid(int gridRows, int gridCols, int gridSize) {
//     for (int i = 0; i <= gridRows; i++) {
//         DrawLine(0, i * gridSize, gridCols * gridSize, i * gridSize, LIGHTGRAY);
//     }
//     for (int i = 0; i <= gridCols; i++) {
//         DrawLine(i * gridSize, 0, i * gridSize, gridRows * gridSize, LIGHTGRAY);
//     }
// }

void DrawTargetPosition(int gridSize) {
    Rectangle target1 = { 12 * gridSize, 4 * gridSize, gridSize, gridSize };
    Rectangle target2 = { 13 * gridSize, 4 * gridSize, gridSize, gridSize };

    DrawRectangleRec(target1, { 255, 255, 0, 100 });
    DrawRectangleLinesEx(target1, 3, WHITE);
    DrawRectangleRec(target2, { 255, 255, 0, 100 });
    DrawRectangleLinesEx(target2, 3, WHITE);
}

void LoadLevel(std::vector<Car>& cars, std::vector<Wall>& walls, std::vector<Texture2D>& carTexture, int level) {
    cars.clear();
    walls.clear();
    if (level == 1) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},
            {{200, 400, 100, 200}, carTexture[2], false},
            {{200, 300, 200, 100}, carTexture[1], true},
            {{400, 600, 300, 100}, carTexture[3], true},
            {{400, 400, 100, 200}, carTexture[2], false},
            {{700, 400, 100, 400}, carTexture[6], false},
            {{800, 500, 200, 100}, carTexture[1], true},
            {{1200, 400, 100, 200}, carTexture[2], false},
            {{800, 300, 100, 200}, carTexture[2], false}
        }; 
        walls = {
            {{200, 600, 100, 100}, LIGHTGRAY},
            {{400, 300, 100, 100}, LIGHTGRAY},
            {{300, 600, 100, 100}, LIGHTGRAY},
            {{500, 300, 100, 100}, LIGHTGRAY},
            {{600, 300, 100, 100}, LIGHTGRAY},
            {{700, 800, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 2) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{300, 300, 100, 200}, carTexture[2], false},     
            {{700, 200, 100, 400}, carTexture[6], false},     
            {{800, 300, 300, 100}, carTexture[3], true},    
            {{700, 600, 100, 200}, carTexture[2], false},   
            {{300, 500, 200, 100}, carTexture[1], true},    
            {{1100, 300, 100, 200}, carTexture[2], false},
            {{1100, 500, 200, 100}, carTexture[1], true},    
            {{500, 500, 100, 300}, carTexture[4], false},
            {{700, 0, 200, 100}, carTexture[1], true},    
            {{800, 100, 100, 200}, carTexture[2], false},     
            {{300, 200, 200, 100}, carTexture[1], true}      
        };
        walls = {
            {{0, 200, 100, 100}, LIGHTGRAY},
            {{100, 200, 100, 100}, LIGHTGRAY},
            {{200, 200, 100, 100}, LIGHTGRAY},
            {{200, 300, 100, 100}, LIGHTGRAY},
            {{0, 500, 100, 100}, LIGHTGRAY},
            {{100, 500, 100, 100}, LIGHTGRAY},
            {{200, 500, 100, 100}, LIGHTGRAY},
            {{1100, 200, 100, 100}, LIGHTGRAY},
            {{1200, 200, 100, 100}, LIGHTGRAY},
            {{1200, 300, 100, 100}, LIGHTGRAY},
            {{1300, 300, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 3) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{600, 300, 100, 200}, carTexture[2], false},     
            {{500, 400, 100, 200}, carTexture[2], false},     
            {{1100, 300, 300, 100}, carTexture[3], true},    
            {{500, 200, 100, 200}, carTexture[2], false},   
            {{600, 500, 300, 100}, carTexture[3], true},    
            {{1000, 300, 100, 200}, carTexture[2], false},     
            {{900, 500, 200, 100}, carTexture[1], true},
            {{200, 200, 300, 100}, carTexture[3], true},     
            {{200, 400, 100, 200}, carTexture[2], false}  
        };
        walls = {
            {{200, 600, 100, 100}, LIGHTGRAY},
            {{300, 500, 100, 100}, LIGHTGRAY},
            {{300, 600, 100, 100}, LIGHTGRAY},
            {{500, 700, 100, 100}, LIGHTGRAY},
            {{600, 700, 100, 100}, LIGHTGRAY},
            {{500, 0, 100, 100}, LIGHTGRAY},
            {{500, 100, 100, 100}, LIGHTGRAY},
            {{600, 0, 100, 100}, LIGHTGRAY},
            {{500, 100, 100, 100}, LIGHTGRAY},
            {{1000, 200, 100, 100}, LIGHTGRAY},
            {{600, 600, 100, 100}, LIGHTGRAY},
            {{700, 600, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 4) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{1000, 300, 100, 200}, carTexture[2], false},     
            {{300, 300, 100, 200}, carTexture[2], false},     
            {{100, 500, 400, 100}, carTexture[5], true},    
            {{500, 400, 100, 200}, carTexture[2], false},   
            {{500, 600, 200, 100}, carTexture[1], true},    
            {{900, 400, 100, 200}, carTexture[2], false},     
            {{800, 200, 300, 100}, carTexture[3], true},
            {{500, 100, 300, 100}, carTexture[3], true},    
            {{700, 300, 300, 100}, carTexture[3], true},     
            {{600, 200, 100, 200}, carTexture[2], false},     
            {{400, 300, 200, 100}, carTexture[1], true}  
        };
        walls = {
            {{900, 600, 100, 100}, LIGHTGRAY},
            {{1000, 600, 100, 100}, LIGHTGRAY},
            {{200, 200, 100, 100}, LIGHTGRAY},
            {{300, 200, 100, 100}, LIGHTGRAY},
            {{400, 200, 100, 100}, LIGHTGRAY},
            {{200, 300, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 5) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{500, 500, 100, 200}, carTexture[2], false},     
            {{600, 400, 100, 200}, carTexture[2], false},     
            {{600, 300, 200, 100}, carTexture[1], true},    
            {{500, 300, 100, 200}, carTexture[2], false},   
            {{600, 600, 300, 100}, carTexture[3], true},    
            {{900, 400, 100, 300}, carTexture[4], false},     
            {{800, 200, 200, 100}, carTexture[1], true},
            {{100, 300, 300, 100}, carTexture[3], true},    
            {{400, 200, 100, 300}, carTexture[4], false},     
            {{300, 100, 200, 100}, carTexture[1], true},     
            {{700, 0, 100, 300}, carTexture[4], false}  
        };
        walls = {
            {{200, 500, 100, 100}, LIGHTGRAY},
            {{200, 600, 100, 100}, LIGHTGRAY},
            {{300, 600, 100, 100}, LIGHTGRAY},
            {{400, 600, 100, 100}, LIGHTGRAY},
            {{400, 500, 100, 100}, LIGHTGRAY},
            {{800, 300, 100, 100}, LIGHTGRAY},
            {{900, 300, 100, 100}, LIGHTGRAY},
            {{1000, 300, 100, 100}, LIGHTGRAY},
            {{500, 700, 100, 100}, LIGHTGRAY},
            {{600, 700, 100, 100}, LIGHTGRAY},
            {{900, 800, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 6) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{200, 300, 100, 200}, carTexture[2], false},     
            {{100, 200, 300, 100}, carTexture[3], true},     
            {{400, 0, 100, 300}, carTexture[4], false},    
            {{100, 500, 100, 300}, carTexture[4], false},   
            {{200, 600, 300, 100}, carTexture[3], true},    
            {{500, 600, 100, 200}, carTexture[2], false},     
            {{400, 300, 200, 100}, carTexture[1], true},
            {{600, 200, 100, 200}, carTexture[2], false},
            {{500, 500, 300, 100}, carTexture[3], true},
            {{800, 400, 100, 300}, carTexture[4], false},
            {{1000, 300, 100, 200}, carTexture[2], false},
            {{700, 700, 300, 100}, carTexture[3], true},   
            {{1100, 300, 200, 100}, carTexture[1], true},
            {{400, 400, 100, 200}, carTexture[2], false}  
        };
        walls = {
            {{1000, 500, 100, 100}, LIGHTGRAY},
            {{1000, 600, 100, 100}, LIGHTGRAY},
            {{1000, 700, 100, 100}, LIGHTGRAY},
            {{1000, 800, 100, 100}, LIGHTGRAY},
            {{1000, 900, 100, 100}, LIGHTGRAY},
            {{100, 800, 100, 100}, LIGHTGRAY},
            {{200, 800, 100, 100}, LIGHTGRAY},
            {{300, 800, 100, 100}, LIGHTGRAY},
            {{400, 800, 100, 100}, LIGHTGRAY},
            {{500, 800, 100, 100}, LIGHTGRAY},
            {{600, 800, 100, 100}, LIGHTGRAY},
            {{700, 800, 100, 100}, LIGHTGRAY},
            {{800, 800, 100, 100}, LIGHTGRAY},
            {{900, 800, 100, 100}, LIGHTGRAY},
            {{0, 800, 100, 100}, LIGHTGRAY},
            {{100, 900, 100, 100}, LIGHTGRAY},
            {{200, 900, 100, 100}, LIGHTGRAY},
            {{300, 900, 100, 100}, LIGHTGRAY},
            {{400, 900, 100, 100}, LIGHTGRAY},
            {{500, 900, 100, 100}, LIGHTGRAY},
            {{600, 900, 100, 100}, LIGHTGRAY},
            {{700, 900, 100, 100}, LIGHTGRAY},
            {{800, 900, 100, 100}, LIGHTGRAY},
            {{900, 900, 100, 100}, LIGHTGRAY},
            {{0, 900, 100, 100}, LIGHTGRAY},
            {{0, 0, 100, 100}, LIGHTGRAY},
            {{0, 100, 100, 100}, LIGHTGRAY},
            {{0, 200, 100, 100}, LIGHTGRAY},
            {{600, 0, 100, 100}, LIGHTGRAY},
            {{500, 100, 100, 100}, LIGHTGRAY},
            {{600, 100, 100, 100}, LIGHTGRAY},
            {{200, 500, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 7) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{200, 300, 100, 300}, carTexture[4], false},     
            {{300, 100, 100, 300}, carTexture[4], false},     
            {{600, 300, 200, 100}, carTexture[1], true},    
            {{300, 400, 100, 200}, carTexture[2], false},   
            {{0, 100, 300, 100}, carTexture[3], true},    
            {{800, 300, 100, 300}, carTexture[4], false},     
            {{300, 600, 200, 100}, carTexture[1], true},
            {{500, 400, 100, 200}, carTexture[2], false},   
            {{700, 200, 300, 100}, carTexture[3], true},    
            {{600, 600, 300, 100}, carTexture[3], true},
            {{600, 0, 100, 300}, carTexture[4], false},
            {{500, 100, 100, 300}, carTexture[4], false},     
            {{1100, 200, 100, 300}, carTexture[4], false}  
        };
        walls = {
            {{200, 600, 100, 100}, LIGHTGRAY},
            {{200, 700, 100, 100}, LIGHTGRAY},
            {{300, 700, 100, 100}, LIGHTGRAY},
            {{900, 500, 100, 100}, LIGHTGRAY},
            {{1000, 500, 100, 100}, LIGHTGRAY},
            {{1100, 500, 100, 100}, LIGHTGRAY},
            {{1200, 500, 100, 100}, LIGHTGRAY},
            {{1300, 500, 100, 100}, LIGHTGRAY},
            {{900, 600, 100, 100}, LIGHTGRAY},
            {{1000, 600, 100, 100}, LIGHTGRAY},
            {{1100, 600, 100, 100}, LIGHTGRAY},
            {{1200, 600, 100, 100}, LIGHTGRAY},
            {{1300, 600, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 8) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{200, 200, 100, 200}, carTexture[2], false},     
            {{300, 200, 100, 300}, carTexture[4], false},     
            {{400, 300, 300, 100}, carTexture[3], true},    
            {{600, 400, 100, 200}, carTexture[2], false},   
            {{500, 600, 200, 100}, carTexture[1], true},    
            {{700, 500, 300, 100}, carTexture[3], true},     
            {{200, 600, 200, 100}, carTexture[1], true},
            {{700, 600, 100, 200}, carTexture[2], false},
            {{600, 800, 200, 100}, carTexture[1], true},
            {{900, 800, 100, 200}, carTexture[2], false},
            {{800, 700, 300, 100}, carTexture[3], true},
            {{900, 300, 100, 200}, carTexture[2], false}  
        };
        walls = {
            {{0, 0, 100, 100}, LIGHTGRAY},
            {{100, 0, 100, 100}, LIGHTGRAY},
            {{200, 0, 100, 100}, LIGHTGRAY},
            {{300, 0, 100, 100}, LIGHTGRAY},
            {{100, 100, 100, 100}, LIGHTGRAY},
            {{0, 100, 100, 100}, LIGHTGRAY},
            {{200, 100, 100, 100}, LIGHTGRAY},
            {{300, 100, 100, 100}, LIGHTGRAY},
            {{900, 0, 100, 100}, LIGHTGRAY},
            {{1000, 0, 100, 100}, LIGHTGRAY},
            {{1100, 0, 100, 100}, LIGHTGRAY},
            {{1200, 0, 100, 100}, LIGHTGRAY},
            {{1300, 0, 100, 100}, LIGHTGRAY},
            {{900, 100, 100, 100}, LIGHTGRAY},
            {{1000, 100, 100, 100}, LIGHTGRAY},
            {{1100, 100, 100, 100}, LIGHTGRAY},
            {{1200, 100, 100, 100}, LIGHTGRAY},
            {{1300, 100, 100, 100}, LIGHTGRAY},
            {{900, 200, 100, 100}, LIGHTGRAY},
            {{1000, 200, 100, 100}, LIGHTGRAY},
            {{1100, 200, 100, 100}, LIGHTGRAY},
            {{1200, 200, 100, 100}, LIGHTGRAY},
            {{1300, 200, 100, 100}, LIGHTGRAY},
            {{700, 300, 100, 100}, LIGHTGRAY},
            {{100, 500, 100, 100}, LIGHTGRAY},
            {{100, 600, 100, 100}, LIGHTGRAY},
            {{100, 700, 100, 100}, LIGHTGRAY},
            {{100, 800, 100, 100}, LIGHTGRAY},
            {{200, 800, 100, 100}, LIGHTGRAY},
            {{300, 800, 100, 100}, LIGHTGRAY},
            {{400, 800, 100, 100}, LIGHTGRAY},
            {{500, 800, 100, 100}, LIGHTGRAY},
            {{1000, 500, 100, 100}, LIGHTGRAY},
            {{1000, 600, 100, 100}, LIGHTGRAY},
            {{800, 600, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 9) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{200, 300, 100, 200}, carTexture[2], false},     
            {{500, 500, 100, 200}, carTexture[2], false},     
            {{300, 700, 300, 100}, carTexture[3], true},    
            {{600, 300, 100, 200}, carTexture[2], false},   
            {{200, 500, 300, 100}, carTexture[3], true},    
            {{700, 400, 100, 200}, carTexture[2], false},     
            {{400, 300, 200, 100}, carTexture[1], true},
            {{900, 300, 100, 200}, carTexture[2], false},   
            {{900, 200, 400, 100}, carTexture[5], true},    
            {{700, 0, 100, 200}, carTexture[2], false},
            {{800, 100, 400, 100}, carTexture[5], true},
            {{700, 600, 200, 100}, carTexture[1], true},    
            {{900, 500, 300, 100}, carTexture[3], true},     
            {{1100, 300, 100, 200}, carTexture[2], false}  
        };
        walls = {
            {{0, 0, 100, 100}, LIGHTGRAY},
            {{1000, 0, 100, 100}, LIGHTGRAY},
            {{1000, 300, 100, 100}, LIGHTGRAY},
            {{0, 100, 100, 100}, LIGHTGRAY},
            {{0, 200, 100, 100}, LIGHTGRAY},
            {{0, 300, 100, 100}, LIGHTGRAY},
            {{100, 0, 100, 100}, LIGHTGRAY},
            {{100, 100, 100, 100}, LIGHTGRAY},
            {{100, 200, 100, 100}, LIGHTGRAY},
            {{100, 300, 100, 100}, LIGHTGRAY},
            {{0, 500, 100, 100}, LIGHTGRAY},
            {{0, 600, 100, 100}, LIGHTGRAY},
            {{0, 700, 100, 100}, LIGHTGRAY},
            {{0, 800, 100, 100}, LIGHTGRAY},
            {{0, 900, 100, 100}, LIGHTGRAY},
            {{900, 0, 100, 100}, LIGHTGRAY},
            {{800, 0, 100, 100}, LIGHTGRAY},
            {{1100, 0, 100, 100}, LIGHTGRAY},
            {{100, 500, 100, 100}, LIGHTGRAY},
            {{100, 600, 100, 100}, LIGHTGRAY},
            {{100, 700, 100, 100}, LIGHTGRAY},
            {{100, 800, 100, 100}, LIGHTGRAY},
            {{100, 900, 100, 100}, LIGHTGRAY},
            {{200, 700, 100, 100}, LIGHTGRAY},
            {{300, 600, 100, 100}, LIGHTGRAY},
            {{400, 600, 100, 100}, LIGHTGRAY},
            {{300, 300, 100, 100}, LIGHTGRAY},
            {{300, 800, 100, 100}, LIGHTGRAY},
            {{200, 800, 100, 100}, LIGHTGRAY},
            {{400, 800, 100, 100}, LIGHTGRAY},
            {{500, 800, 100, 100}, LIGHTGRAY},
            {{600, 800, 100, 100}, LIGHTGRAY},
            {{700, 800, 100, 100}, LIGHTGRAY},
            {{800, 800, 100, 100}, LIGHTGRAY},
            {{200, 900, 100, 100}, LIGHTGRAY},
            {{300, 900, 100, 100}, LIGHTGRAY},
            {{400, 900, 100, 100}, LIGHTGRAY},
            {{500, 900, 100, 100}, LIGHTGRAY},
            {{600, 900, 100, 100}, LIGHTGRAY},
            {{700, 900, 100, 100}, LIGHTGRAY},
            {{800, 900, 100, 100}, LIGHTGRAY},
            {{900, 800, 100, 100}, LIGHTGRAY},
            {{900, 900, 100, 100}, LIGHTGRAY},
            {{1000, 700, 100, 100}, LIGHTGRAY},
            {{1100, 700, 100, 100}, LIGHTGRAY},
            {{1200, 700, 100, 100}, LIGHTGRAY},
            {{1300, 700, 100, 100}, LIGHTGRAY},
            {{1000, 800, 100, 100}, LIGHTGRAY},
            {{1100, 800, 100, 100}, LIGHTGRAY},
            {{1200, 800, 100, 100}, LIGHTGRAY},
            {{1300, 800, 100, 100}, LIGHTGRAY},
            {{1000, 900, 100, 100}, LIGHTGRAY},
            {{1100, 900, 100, 100}, LIGHTGRAY},
            {{1200, 900, 100, 100}, LIGHTGRAY},
            {{1300, 900, 100, 100}, LIGHTGRAY},
            {{1200, 500, 100, 100}, LIGHTGRAY},
            {{1200, 600, 100, 100}, LIGHTGRAY},
            {{1300, 500, 100, 100}, LIGHTGRAY},
            {{1300, 600, 100, 100}, LIGHTGRAY},
            {{1200, 300, 100, 100}, LIGHTGRAY},
            {{1300, 300, 100, 100}, LIGHTGRAY},
            {{1200, 0, 100, 100}, LIGHTGRAY},
            {{1200, 100, 100, 100}, LIGHTGRAY},
            {{1300, 0, 100, 100}, LIGHTGRAY},
            {{1300, 100, 100, 100}, LIGHTGRAY},
            {{1300, 200, 100, 100}, LIGHTGRAY},
            {{200, 0, 100, 100}, LIGHTGRAY},
            {{300, 0, 100, 100}, LIGHTGRAY},
            {{400, 0, 100, 100}, LIGHTGRAY},
            {{500, 0, 100, 100}, LIGHTGRAY},
            {{600, 0, 100, 100}, LIGHTGRAY},
            {{200, 100, 100, 100}, LIGHTGRAY},
            {{300, 100, 100, 100}, LIGHTGRAY},
            {{400, 100, 100, 100}, LIGHTGRAY},
            {{500, 100, 100, 100}, LIGHTGRAY},
            {{600, 100, 100, 100}, LIGHTGRAY},
            {{200, 200, 100, 100}, LIGHTGRAY},
            {{300, 200, 100, 100}, LIGHTGRAY},
            {{400, 200, 100, 100}, LIGHTGRAY},
            {{500, 200, 100, 100}, LIGHTGRAY},
            {{600, 200, 100, 100}, LIGHTGRAY}
        };
    } else if (level == 10) {
        cars = {
            {{0, 400, 200, 100}, carTexture[0], true},       
            {{1300, 300, 100, 200}, carTexture[2], false},     
            {{900, 200, 200, 100}, carTexture[1], true},     
            {{1100, 200, 300, 100}, carTexture[3], true},    
            {{900, 400, 100, 300}, carTexture[4], false},   
            {{200, 500, 200, 100}, carTexture[1], true},    
            {{900, 700, 100, 200}, carTexture[2], false},     
            {{400, 300, 100, 300}, carTexture[4], false},
            {{600, 600, 200, 100}, carTexture[1], true},
            {{200, 200, 300, 100}, carTexture[3], true},
            {{600, 100, 100, 300}, carTexture[4], false},
            {{700, 400, 100, 200}, carTexture[2], false},
            {{800, 400, 100, 400}, carTexture[6], false},   
            {{700, 100, 300, 100}, carTexture[3], true},
            {{700, 300, 300, 100}, carTexture[3], true},
            {{1100, 300, 100, 200}, carTexture[2], false},
            {{200, 300, 100, 200}, carTexture[2], false}  
        };
        walls = {
            {{500, 200, 100, 100}, LIGHTGRAY},
            {{500, 300, 100, 100}, LIGHTGRAY},
            {{400, 600, 100, 100}, LIGHTGRAY},
            {{400, 700, 100, 100}, LIGHTGRAY},
            {{500, 600, 100, 100}, LIGHTGRAY},
            {{1000, 100, 100, 100}, LIGHTGRAY},
            {{1000, 500, 100, 100}, LIGHTGRAY},
            {{1100, 500, 100, 100}, LIGHTGRAY},
            {{1200, 500, 100, 100}, LIGHTGRAY},
            {{1300, 500, 100, 100}, LIGHTGRAY},
            {{800, 800, 100, 100}, LIGHTGRAY},
            {{800, 900, 100, 100}, LIGHTGRAY},
            {{900, 900, 100, 100}, LIGHTGRAY},
            {{500, 700, 100, 100}, LIGHTGRAY},
            {{600, 800, 100, 100}, LIGHTGRAY},
            {{700, 800, 100, 100}, LIGHTGRAY},
            {{600, 900, 100, 100}, LIGHTGRAY},
            {{700, 900, 100, 100}, LIGHTGRAY},
            {{1000, 800, 100, 100}, LIGHTGRAY},
            {{1000, 900, 100, 100}, LIGHTGRAY}
        };
    }
}

enum GameState {
    MENU,
    GAMEPLAY,
    LEVEL_SELECT
};

#endif // PARKINGBLOCK_H