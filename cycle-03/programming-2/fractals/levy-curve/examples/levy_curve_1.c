#include "../turtlec.h"
#include <math.h>

void levy(Turtle *t, float length, int depth, float angle);

int main(void) {
  TurtleApp *app = turtleAppCreate(800, 800, "Test Line");
  Turtle *t = turtleAppGetTurtle(app);
  levy(t, 100.0f, 10, 45.0f);

  return 0;
}

void levy(Turtle *t, float length, int depth, float angle) {
  if (depth == 0) {
    turtleForward(t, length);
    return;
  }
  turtleLeft(t, angle);
  levy(t, length / sqrt(2), depth - 1, angle);
  turtleRight(t, angle * 2);
  levy(t, length / sqrt(2), depth - 1, angle);
  turtleLeft(t, angle);

  if (depth >= 1 && depth <= 2)
    turtleSetColor(t, 255, 0, 0);
  if (depth >= 3 && depth <= 5)
    turtleSetColor(t, 255, 255, 0);
  if (depth > 5)
    turtleSetColor(t, 0, 255, 255);
}
