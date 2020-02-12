#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159

struct vec {
  float x;                              // x component 
  float y;                              // y component 
};

struct robot {
  struct vec p;                         // position of robot 
  int r_num;		                // robot number 
  float angle;                          // angle of robot 
  int time;                             // time robot has moved 
  int sdirection;                       // direction of the spiral 
  int p_carry;                          // number of puck being carried 
  struct robot *next;                   // pointer to next node. 
  char active;                          // ??
  int state;                            // -1 if spiraling, 0 if attaching, > 0 if in chain
  char stop;                            // 1 for stop, 0 for go
};

typedef struct robot s_robot;
typedef struct vec s_vec;

#include "hive/vec_dif.c"
#include "angle_between_robots.c"

int main()
{
  s_robot *rob1 = (s_robot *) malloc(sizeof(s_robot)), *rob2 = (s_robot *) malloc(sizeof(s_robot));

  rob1->p.x = 1;   
  rob1->p.y = -1;   
  rob2->p.x = 0;   
  rob2->p.y = 0;

  printf("angle between robots is %f\n", ANGLE(rob1, rob2));

  return 0;
}
