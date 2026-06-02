#include <math.h>
#include "../turtlec.h"

void levy(Turtle *t, float length, int depth, float angle);

int main(void){
  TurtleApp *app = turtleAppCreate(800, 800, "Test Line");
  Turtle *t = turtleAppGetTurtle(app);
  levy(t, 100.0f, 10, 45.0f);

 return 0;
}

void levy(Turtle *t, float length, int depth, float angle){
  if(depth==0){
    turtleForward(t, length);
    return;
  }
  turtleLeft(t, angle);
  levy(t, length/sqrt(2), depth-1, angle);
  turtleRight(t, angle*2);
  levy(t, length/sqrt(2), depth-1, angle);
  turtleLeft(t, angle);

  if(depth>4)
    turtleSetColor(t, 30, 50, 60);
  else
    turtleSetColor(t, 120, 45, 20);


if(depth>4)
turtleSetColor(t, 30, 50, 60);
else
turtleSetColor(t, 120, 45, 20);

}
