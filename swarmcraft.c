/****************************************
 *                                      *
 *              SwarmCraft              *
 *            Chain Expansion           *
 *                                      *
 * ------------------------------------ *
 *                                      *
 * Originally written by:               *
 *   Amos Zhang                         *
 *   Anthony Lim                        *
 *   Michael Chung                      *
 *   Andrea Grosz                       *
 *   Brian Lee                          *
 *   Brian Lin                          *
 *   Ryan Cho                           *
 *   James Wigglesworth                 *
 *   Bryan Tseng                        *
 *   Dashiell Vitullo                   *
 *   Michael Wang                       *
 *   Sanza Kazadi                       *
 *   (and others who forgot to document *
 *   their work)                        *
 *                                      *
 * as a puck clustering simulation      *
 *                                      *
 * Modified by:                         *
 *   Hamik Mukelyan                     *
 *                                      *
 * to a search and retrieve "chain"     *
 * simulation. See PROGRESS file for    * 
 * all changes                          *
 *                                      *
 * ------------------------------------ *
 *                                      *
 * Naming conventions:                  *
 *                                      *
 * s_... - structure                    *
 * a_... - array                        *
 * p_... - puck related                 *
 * r_... - robot related                *
 * vec_... - vector related             *
 * c_... - cluster related              *
 *                                      *
 * functions names/constants            *
 * are upper case, all else             *
 * lower case                           *
 *                                      *
 ****************************************/

// general includes
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// definition of constants
#define PI 3.14159265358979323846264338 // pi
#define ET 2.71828182845904523536028747 // e
#define ERROR 0.05                      // grep for uses

// definition of constants of simulation
#define X_SIZE 100                      // length of arena 
#define Y_SIZE 100                      // width of arena 
#define P_SIZE 0.5                      // radius of puck 
#define R_SIZE 1.0                      // radius of robot 

// definition of function specific constants
#define R_PUSH_MAX 3                    // maximum dist robot can push puck 
#define P_SPACE 1.05                    // average space between pucks 
#define E 0.0                           // epsilon constant ?? 
#define A 1                             // alpha constant ??
#define P 0                             // phi constant ??
#define R_VIEW_DIST 20                  // robot viewing radius ?? 
#define R_VIEW_ANGLE PI                 // 1/2 robot viewing angle. several functions assume R_VIEW_ANGLE is PI
#define D_ERROR 1                       // grep this constant to see where it is used
#define A_ERROR PI/6                    // use grep to find out how it's used
#define C_DIST 8                        // dist between adj robots in chain. C_DIST should be > 2*R_SIZE and < R_VIEW_MAX
#define STRAIGHT_LENGTH 20              // dist to travel in straight line after spiral collision

// struct defs
struct vec {
  float x;                              // x component 
  float y;                              // y component 
};

struct puck {
  struct vec p;                         // position of puck
  char exist;                           // 1 is not collected, 0 if collected
  int p_num;                            // puck number 
  struct puck *next;                    // next pointer 
  char being_carried;                   // 0 if waiting to be carried, 1 if being carried
};

struct robot {
  struct vec p;                         // position of robot 
  int r_num;		                // robot number 
  float angle;                          // angle of robot 
  int time;                             // convenient time variable 
  int sdirection;                       // direction of the spiral 
  int pucky;                            // p_num of puck being held, -1 for none
  struct robot *next;                   // pointer to next node. 
  char active;                          // 1 if active
  int state;                            // -1 if spiraling, 0 if attaching, > 0 if in chain
  float dist;                           // distance from perimeter of collection zone to collection center to drop off puck at
  char attachable;                      // rob attaches as state 1 only when home rob's attachable = 1. also,
                                        // rob attaches to chain only when its attachable = 1
};

typedef struct vec s_vec;
typedef struct puck s_puck;
typedef struct robot s_robot;

// misc variables
long seed;                              // seed for ran2 function. initialized in main
float R_MOVE_MAX;                       // maximum distance robot can move 
int OUTPUT;                             // iterations to skip between outputs
int STRAIGHT_TIME;                      // #timesteps to travel in straight line after spiral collision
long ITERATIONS;                        // total iterations
float SEARCH_PROB;                      // probability 0<=p<=1 that a robot will never attach to the 
                                        // chain (continue to search for pucks) 

// sim includes
#include "misc_utilities/sign.c"

#include "math_utilities/seed.c"
#include "math_utilities/sqr.c"
#include "math_utilities/rand2.c"
#include "math_utilities/vec_add.c"
#include "math_utilities/vec_dif.c"
#include "math_utilities/vec_dot.c"
#include "math_utilities/vec_rot.c"
#include "math_utilities/vec_crs.c"
#include "math_utilities/vec_mag.c"
#include "math_utilities/vec_unt.c"
#include "math_utilities/vec_scl.c"
#include "math_utilities/gaussian_position.c"

#include "string_utilities/strtoint.c"

#include "placement_functions/r_placement_rand.c"
#include "placement_functions/p_placement_rand.c"

#include "memory_utilities/free_puck_list.c"
#include "memory_utilities/free_robot_list.c"

#include "behavior_functions/puck_with_num.c"
#include "behavior_functions/list_vis_pucks.c"
#include "behavior_functions/robot_with_specific_state.c"
#include "behavior_functions/turn_robot.c"
#include "behavior_functions/list_vis_robots.c"
#include "behavior_functions/lowest_vis_state.c"
#include "behavior_functions/angle_between_vecs.c"
#include "behavior_functions/highest_vis_state_robots.c"
#include "behavior_functions/spiral.c"
#include "behavior_functions/chain_angle.c"
#include "behavior_functions/move_robot.c"

#include "main.c"
