#include "raylib.h"

const int BALL_SIZE = 20;
const int FONT_SIZE = BALL_SIZE * 3;
const int NET_SIZE = BALL_SIZE * 0.75;

const int PADDLE_WIDTH = BALL_SIZE;
const int PADDLE_HEIGHT = BALL_SIZE * 10;
const float PADDLE_SPEED = BALL_SIZE * 10 * 1.5;

const int PADDING = BALL_SIZE;

const int WINDOW_SIZE = BALL_SIZE * 4;

int main(void) {
  InitWindow(16 * WINDOW_SIZE, 9 * WINDOW_SIZE, "Pong");

  SetTargetFPS(60);

  // TODO: use something a bit more random
  float ball_speed_x = BALL_SIZE * 10;
  float ball_speed_y = BALL_SIZE * 10;

  int score_left = 0;
  int score_right = 0;

  int w = GetScreenWidth();
  int h = GetScreenHeight();

  const Vector2 topScreenMiddle = {(float)w / 2, 0};
  const Vector2 bottomScreenMiddle = {(float)w / 2, h};

  int ball_x = (w - BALL_SIZE) / 2;
  int ball_y = (h - BALL_SIZE) / 2;

  int paddle_left_x = PADDING;
  int paddle_left_y = (h - PADDLE_HEIGHT) / 2;

  int paddle_right_x = w - PADDING - PADDLE_WIDTH;
  int paddle_right_y = (h - PADDLE_HEIGHT) / 2;

  while (!WindowShouldClose()) {

    /* DEFINE BALL AND PADDLES */

    Rectangle ball = {ball_x, ball_y, BALL_SIZE, BALL_SIZE};

    Rectangle paddle_left = {paddle_left_x, paddle_left_y, PADDLE_WIDTH,
                             PADDLE_HEIGHT};

    Rectangle paddle_right = {paddle_right_x, paddle_right_y, PADDLE_WIDTH,
                              PADDLE_HEIGHT};

    /* BALL MOVEMENT AND COLLISION */

    if (CheckCollisionRecs(paddle_left, ball) ||
        CheckCollisionRecs(paddle_right, ball)) {
      ball_speed_x *= -1;
    }

    if (ball_y > h - BALL_SIZE || ball_y < 0) {
      ball_speed_y *= -1;
    }

    ball_x += GetFrameTime() * ball_speed_x;
    ball_y += GetFrameTime() * ball_speed_y;

    /* SCORING */
    if (ball_x < 0) {
      score_right++;
      ball_x = (w - BALL_SIZE) / 2;
      ball_y = (h - BALL_SIZE) / 2;
    }

    if (ball_x > w - BALL_SIZE) {
      score_left++;
      ball_x = (w - BALL_SIZE) / 2;
      ball_y = (h - BALL_SIZE) / 2;
    }

    /* PADDLE CONTROLS */

    if (IsKeyDown(KEY_UP) && paddle_right_y > 0) {
      paddle_right_y -= GetFrameTime() * PADDLE_SPEED;
    }
    if (IsKeyDown(KEY_DOWN) && paddle_right_y < h - PADDLE_HEIGHT) {
      paddle_right_y += GetFrameTime() * PADDLE_SPEED;
    }

    if (IsKeyDown(KEY_W) && paddle_left_y > 0) {
      paddle_left_y -= GetFrameTime() * PADDLE_SPEED;
    }

    if (IsKeyDown(KEY_S) && paddle_left_y < h - PADDLE_HEIGHT) {
      paddle_left_y += GetFrameTime() * PADDLE_SPEED;
    }

    BeginDrawing();

    ClearBackground(BLACK);

    /* DRAW BALL AND PADDLES */
    DrawRectangleRec(paddle_left, LIGHTGRAY);
    DrawRectangleRec(paddle_right, LIGHTGRAY);
    DrawRectangleRec(ball, LIGHTGRAY);

    /* DRAW NET */
    DrawLineDashed(topScreenMiddle, bottomScreenMiddle, NET_SIZE, NET_SIZE,
                   LIGHTGRAY);

    /* DRAW SCORE */
    DrawText(TextFormat("%d", score_left), w / 2 - (2 * PADDING + FONT_SIZE),
             2 * PADDING, FONT_SIZE, WHITE);
    DrawText(TextFormat("%d", score_right), w / 2 + PADDING + FONT_SIZE,
             2 * PADDING, FONT_SIZE, WHITE);

    EndDrawing();
  }
  CloseWindow();

  return 0;
}
