#include "../turtlec.h"

void fractalTree(Turtle *t, float length, int depth, float angle);

int main(void){
  TurtleApp *app = turtleAppCreate(800, 800, "Test Line");
  Turtle *t = turtleAppGetTurtle(app);
  turtleLeft(t, 90.0f);
  fractalTree(t, 100.0f, 10, 60.0f);
 return 0;
}

void fractalTree(Turtle *t, float length, int depth, float angle){
  if(depth == 0)
    return;
  turtleForward(t, length);
  turtleLeft(t, angle);
  fractalTree(t, length*0.7, depth-1, angle);
  turtleRight(t, angle*2);
  fractalTree(t, length*0.7, depth-1, angle);
  turtleLeft(t, angle);
  turtleBackward(t, length);
  if (depth > 5)
    turtleSetColor(t, 120, 70, 20);
  else
    turtleSetColor(t, 0, 200, 0);
}
