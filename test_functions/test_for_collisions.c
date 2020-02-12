/*************************************
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *   Robert Lee                      *
 *                                   *
 * to see if robots overlap. will be *
 * used in the future to see if      *
 * pucks in clusters overlap         *
 *                                   *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define R_SIZE 1.0 // radius of robot
#define E 0.02     // margin of error for dist tests

struct vec {
  float x;
  float y;
};

typedef struct vec s_vec;

int main()
{
  float rx, ry, px, py, temp2 = 0;
  int r_tot, p_tot, i=0, j, k = 0, num_iterations = 0, cont = 1;
  long temp = 0;
  FILE *settings = fopen("setting.dat", "r"),
       *r_pos = fopen("r_pos.dat", "r"),
       *p_pos = fopen("p_pos.dat", "r");
  s_vec *r_all, *rtemp, *p_all, *ptemp;
  char bogus, str[100];

  // get # of robots and allocate enough space for an s_vec array of length # robots
  while(i++ < 4)
    fscanf(settings, "%d", &temp);
  r_all = rtemp = (s_vec *) malloc(sizeof(s_vec) * (r_tot = temp));

  // jump over float in setting.dat
  fscanf(settings, "%f", &temp2);

  // get # of pucks and allocate enough space for an s_vec array of length # pucks
  fscanf(settings, "%d", &temp);
  p_all = ptemp = (s_vec *) malloc(sizeof(s_vec) * (p_tot = temp));

  // go through r_pos one timestep at a time. compare the positions
  // of each robot with every other robot. if the positions are ever closer than
  // 2 * R_SIZE, output warning
  k=0;
  while(1) {
 
    printf("timestep: %d\n", k++);

    for(i = 0; i<r_tot;i++) { // get all positions from one timestep
      fscanf(r_pos, "%s", str);

      fscanf(r_pos, "%s", str);
      sscanf(str, "%f", &r_all->x);

      fscanf(r_pos, "%s", str);
      sscanf(str, "%f", &r_all->y);
      
      r_all++;
    }
    r_all = rtemp;
    cont = 1;

    // check each robot againt every other to see if too close
    for(i = 0; i<r_tot; i++) {
      for(j = i + 1; j<r_tot; j++) {

        // too close defined as dist between robots < 2*R_SIZE
        if((temp2=sqrt(pow((r_all+i)->x-(r_all+j)->x,2) + 
          pow((r_all+i)->y-(r_all+j)->y,2))) < 2 * R_SIZE - E)
          printf("  uh oh: (%.2f, %.2f) and (%.2f, %.2f) are %f units apart\n", 
                 (r_all+i)->x, (r_all+i)->y, (r_all+j)->x, (r_all+j)->y, temp2);
      }
    }

    // DEBUG
    // printf("waiting to go on to next timestep. enter float when ready... ");
    // scanf("%f", &temp2);

    // add check for EOF here. can you believe i'd type all this and not add the check myself?
  }
  
  return 0;  
}
