#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#define ROWS 32
#define COLS 40
#define SIZE 20

#define DEAD  0
#define ALIVE 1

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 640;

    int next = 0;
    int cells[ROWS][COLS] = {0};

    InitWindow(screenWidth, screenHeight, "Game Of Life");
    SetTargetFPS(12);

    while (!WindowShouldClose())
    {

        Vector2 mousePos = GetMousePosition();

        if (IsKeyPressed(KEY_L)) next = !next;
 
        // Clear
        if (IsKeyPressed(KEY_C)) memset(cells, 0, sizeof cells);

        // Fps +/-
        if (IsKeyDown(KEY_A)) SetTargetFPS(GetFPS() - 1);
        if (IsKeyDown(KEY_D)) SetTargetFPS(GetFPS() + 1);
        
        // Update cells
        if (next || IsKeyPressed(KEY_N)) {
            int nextCells[ROWS][COLS] = {0};

            memcpy(nextCells, cells, sizeof cells);

            for (int y = 0; y < ROWS; y++) {
                for (int x = 0; x < COLS; x++) {
                    int cell = cells[y][x];

                    // Get neighbours
                    int neighbours = 0; 
                    for (int ny = y - 1; ny <= y + 1; ny++) {
                        for (int nx = x - 1; nx <= x + 1; nx++) {
                            if (ny < 0 || ny > ROWS - 1 || nx < 0 || nx > COLS - 1) continue;
                            if (ny == y && nx == x) continue;
                            if (cells[ny][nx] == ALIVE) neighbours++;
                        }
                    }

                    if (cell == ALIVE && (neighbours < 2 || neighbours > 3)) nextCells[y][x] = DEAD;
                    if (cell == DEAD && neighbours == 3) nextCells[y][x] = ALIVE;
                }
            }

            memcpy(cells, nextCells, sizeof cells);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int x = mousePos.x / SIZE;
            int y = mousePos.y / SIZE;
                 
            // Toggle cell
            cells[y][x] = !cells[y][x];
        }

        BeginDrawing();

            ClearBackground(BLACK);

            // Draw cells
            for (int y = 0; y < ROWS; y++) {
                for (int x = 0; x < COLS; x++) {
                    int cell = cells[y][x];
                    
                    Color gray = {50, 50, 50, 255};

                    if (cell == DEAD) DrawRectangleLines(x * SIZE, y * SIZE, SIZE, SIZE, gray);
                    else DrawRectangle(x * SIZE, y * SIZE, SIZE, SIZE, WHITE);
                }
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}