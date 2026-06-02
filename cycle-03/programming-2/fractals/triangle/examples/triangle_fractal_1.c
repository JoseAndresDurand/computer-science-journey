#include "../turtlec.h"

void triangle(Turtle *t, float length, int depth);

int main() {
  TurtleApp *app = turtleAppCreate(800, 800, "Test Line");
  Turtle *t = turtleAppGetTurtle(app);
  triangle(t, 300.0f, 5);
  return 0;
}

void triangle(Turtle *t, float length, int depth) {
  if (depth == 0)
    return;
  for (int i = 0; i < 3; i++) {
    turtleForward(t, length);
    turtleLeft(t, 120.0f);
  }
  turtleForward(t, length / 2.0);
  turtleLeft(t, 60.0f);
  for (int i = 0; i < 3; i++) {
    turtleForward(t, length / 2.0);
    turtleLeft(t, 120.0f);
  }
  turtleRight(t, 60.0f);
  turtleBackward(t, length / 2.00);
  turtleLeft(t, 60.0f);
  turtleForward(t, length / 2.0);
  turtleRight(t, 60.0f);
  for (int i = 0; i < 3; i++) {
    turtleForward(t, length / 2.0);
    turtleLeft(t, 120.0f);
  }
  triangle(t, length / 2.0, depth - 1);
}
