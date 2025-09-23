#ifndef CIRCUIT_H   
#define CIRCUIT_H   

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Placeholder table for line positions in the maze. Will be updated when maze is mapped.
// 1 means line present, 0 means no line. Each element of the table represents the edge
// of a 50x50 cm square in the maze.
// The first line of the table represents the start line of the maze, which means maze is flipped in the table vs reality.
unsigned char uctWhereAreLines [10][10] = {
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0}
};

unsigned char ucRobotDirection = NORTH;
unsigned char ucWhereIsRobotX = 0;      // Represents the robot's current X position with respect to the table    
unsigned char ucWhereIsRobotY = 0;      // Represents the robot's current Y position with respect to the table
                                        // If the value of a variable is 2, the robot is between edges 2 and 3

//FUNCTION PROTOTYPES
unsigned char ucUpdateRobotDirection(unsigned char ucTurnDirection);

#endif CIRCUIT_H