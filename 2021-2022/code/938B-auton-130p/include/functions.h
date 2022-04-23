using namespace vex;




//This funcrion Does

void clampUp();
void clampDown();
void moveForward(float time, int power);





void turnLeft(float time);
void turnRight(float time);
// void lift(float time, int power);
void clawFront(int direction, float rotations);
void backLift(int direction, float rotations);
void backClaw(int direction, float time);
void pidTurnLeft(double angle, double tolerance);
void pidTurnRight(double angle, double tolerance);
void pidTurn(double angle, double tolerance);
void climb();
void setVelocityAll(int velocityAll);