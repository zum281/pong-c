#include "raylib.h"

int main(void) {
  InitWindow(800, 600, "Pong");

  while (!WindowShouldClose()) {
    BeginDrawing();
    Rectangle rec = {0.0, 0.0, 100.0, 100.0};
    Color color = {0xff, 0xff, 0xff, 0xff};

    DrawRectangleRec(rec, color);
    EndDrawing();
  }
  CloseWindow();

  return 0;
}
