#include "../turtlec.h"

void triangle(Turtle *t, float length, int depth);

int main() {
  TurtleApp *app = turtleAppCreate(800, 800, "Test Line");
  Turtle *t = turtleAppGetTurtle(app);
  triangle(t, 300.0f, 5);
  return 0;
}

void triangle(Turtle *t, float length, int depth) {
  if (depth == 0) {
    for (int i = 0; i < 3; i++) {
      turtleForward(t, length);
      turtleLeft(t, 120.0f);
    }
    return;
  }
  float half_length = length / 2.0f;
  triangle(t, half_length, depth - 1);

  turtleForward(t, half_length);
  triangle(t, half_length, depth - 1);

  turtleBackward(t, half_length);
  turtleLeft(t, 60.0f);
  turtleForward(t, half_length);
  turtleRight(t, 60.0f);
  triangle(t, half_length, depth - 1);

  turtleLeft(t, 60.0f);
  turtleBackward(t, half_length);
  turtleRight(t, 60.0f);
}
