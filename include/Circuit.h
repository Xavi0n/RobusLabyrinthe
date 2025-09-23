#ifndef CIRCUIT_H   
#define CIRCUIT_H   

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define LEFT 0
#define RIGHT 1

#define LEFT_COLUMN 1
#define CENTER_COLUMN 2
#define RIGHT_COLUMN 3

// 1 means line present, 0 means no line. Each element of the table represents the edge
// of a 50x50 cm square in the maze.
// The first line of the table represents the start line of the maze, which means maze is flipped in the table vs reality.
unsigned char uctWhereAreLines [11][4] = {
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0}
};

//FUNCTION PROTOTYPES
void vUpdateRobotDirection(unsigned char ucTurnDirection);
void vUpdateRobotPosition();
bool bGetNearbyLines(unsigned char ucRobotDirection, unsigned char ucWhereIsRobotX, unsigned char ucWhereIsRobotY);
bool bDangerCheck ();

#endif