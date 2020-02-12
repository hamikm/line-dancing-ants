/****************************************
 *                                      *
 *                MAIN                  *
 *                                      *
 * Originally written by:               *
 *   (people who forgot to document     *
 *   their work)                        *
 *                                      *
 * as the driver function of a puck     *
 * clustering simulation                *
 *                                      *
 * Modified by:                         *
 *   Hamik Mukelyan                     *
 *                                      *
 * to the driver function of a search   *
 * and retrieve "chain" simulation      *
 *                                      *
 ****************************************/

main (int argc, char *argv[])
{
  s_robot *a_robot;                      // array of robots
  s_puck *a_puck;                        // array of pucks
  int i, j, k, z;                        // control variables
  int p_tot, r_tot;                      // total number of pucks, robots
  int counter;                           // counter variable
  FILE *p_pos;                           // file for position of pucks
  FILE *r_pos;                           // file for position of robots
  FILE *setting;                         // file to store settings
  FILE *p_posf;                          // file for final puck pos
  FILE *r_posf;                          // file for final robot pos
  float homex, homey;                    // pos of home location
  float r_variance, p_variance;          // variances for gaussian placement function

  if (argc!=9) {
     printf("Arguments are: <# robots> <# pucks> <home x> <home y> <max robot move>\n");
     printf("<puck placement variance> <robot placement variance> <searcher probability>\n");
     exit(-1);
  }

  printf("my robots, they has good grammer\n"); 
  
  set_seed();

  // prepare data files
  r_pos = fopen ("data_files/r_pos.dat","w");
  p_pos = fopen ("data_files/p_pos.dat","w");
  r_posf = fopen ("data_files/r_posf.dat","w");
  p_posf = fopen ("data_files/p_posf.dat","w");
  setting = fopen ("data_files/setting.dat","w");

  // input
  sscanf(argv[1],"%d",&r_tot);
  if(r_tot < 0)
    r_tot = 0;
  sscanf(argv[2],"%d",&p_tot);
  a_robot=(s_robot *)malloc(sizeof(s_robot)*(r_tot+1)); // +1 b/c home loc 0 state robot
  a_puck=(s_puck *)malloc(sizeof(s_puck)*p_tot);
  sscanf(argv[3], "%f", &homex);
  sscanf(argv[4], "%f", &homey);
  sscanf(argv[5], "%f", &R_MOVE_MAX);
  sscanf(argv[6], "%f", &p_variance);
  sscanf(argv[7], "%f", &r_variance);
  sscanf(argv[8], "%f", &SEARCH_PROB);

  if(SEARCH_PROB < 0)
    SEARCH_PROB = 0;
  if(SEARCH_PROB > 1)
    SEARCH_PROB = 1;

  if(R_MOVE_MAX >= .99)
    OUTPUT = 1;
  else
    OUTPUT = (int)(1.0/R_MOVE_MAX);
  ITERATIONS=100000*OUTPUT;

  STRAIGHT_TIME = STRAIGHT_LENGTH/R_MOVE_MAX;

  // create settings file
  fprintf (setting, "%d\n", (ITERATIONS / OUTPUT)); 
  fprintf (setting, "%d\n%d\n", X_SIZE, Y_SIZE);
  fprintf (setting, "%d\n%f\n", r_tot + 1, R_SIZE); // +1 b/c home loc 0 state robot
  fprintf (setting, "%d\n%f\n", p_tot, P_SIZE);
 
  // close settings file
  fclose (setting);

  // initialize pucks
  if(p_tot > 0) {
    P_PLACEMENT (&a_puck[0], p_tot, p_variance, homex, homey);
    a_puck[p_tot-1].next=NULL;
    for (i = 0; i < p_tot-1; i++) {
       a_puck[i].next=&a_puck[i+1];
    }
    for (i = 0; i < p_tot; i++) {
      a_puck[i].p_num=i;
      a_puck[i].being_carried=0;
      a_puck[i].exist = 1;
    }
  }
  else { // the else is to protect against p_tot <= 0
    a_puck = NULL;
  }

  // initialize robots 
  for (i = 0; i < r_tot; i++) {
    a_robot[i].angle=0;
    R_TURN (&a_robot[i]);
    a_robot[i].next=&a_robot[i+1];
    a_robot[i].r_num=i;
  }
  a_robot[r_tot].angle=0;
  R_TURN (&a_robot[r_tot]);
  a_robot[r_tot].r_num=r_tot;
  a_robot[r_tot].next=NULL;
  R_PLACEMENT (&a_robot[1], &a_puck[1], r_tot, p_tot, r_variance, homex, homey);
  a_robot[0].p.x = homex;
  a_robot[0].p.y = homey;
  for (i = 0; i < r_tot + 1; i++) {
    a_robot[i].sdirection = 1;
    a_robot[i].active = 1;
    a_robot[i].state = -1;
    a_robot[i].time = 0; // home rob's attachable changes after one time incrementation
    a_robot[i].pucky = -1; 
    a_robot[i].dist = -1;
    if(ran2(&seed) < SEARCH_PROB)
      a_robot[i].attachable = 0; // searcher
    else
      a_robot[i].attachable = 1; // chain former
  }
  a_robot[0].state = 0;
  a_robot[0].attachable = 1;

  // main loop
  for (i = 0; i < ITERATIONS; i++) {
    // DEBUG
    // printf("--iteration %d--\n", i);

    // move robots
    for (j = 0; j < r_tot + 1; j++) {

      if (a_robot[j].active)
	R_MOVE (&a_robot[j], a_puck, a_robot, i);
    }
    
    if(i%OUTPUT==0) { 

      // output robot positions
      for (j = 0; j < r_tot + 1; j++) { // +1 for home loc robot
        if(!a_robot[j].active)
          fprintf (r_pos, "%c %f %f\n", 'd', a_robot[j].p.x, a_robot[j].p.y); // dead
        else if(a_robot[j].state < 0)
          fprintf (r_pos, "%c %f %f\n", 'n', a_robot[j].p.x, a_robot[j].p.y);
        else // in chain. display with diff color
          fprintf (r_pos, "%c %f %f\n", 'c', a_robot[j].p.x, a_robot[j].p.y);
      }
      fflush(r_pos);
 
      // output puck positions
      for (j = 0; j < p_tot; j++) {
        if(!a_puck[j].exist)
          fprintf (p_pos, "%c %f %f %d\n", 'd', a_puck[j].p.x, a_puck[j].p.y, 1); // doesn't exist
        else
          fprintf (p_pos, "%c %f %f %d\n", 'e', a_puck[j].p.x, a_puck[j].p.y, 1); // exists
      }
      fflush(p_pos);
    }
  }
  
  // output robot positions
  for (j = 0; j < r_tot + 1; j++) {
    fprintf (r_posf, "%f\t%f\n", a_robot[j].p.x, a_robot[j].p.y);
  }

  // output puck positions
  for (j = 0; j < p_tot; j++) {
    fprintf (p_posf, "%f\t%f\n", a_puck[j].p.x, a_puck[j].p.y);
  }

  // close files
  fclose (p_pos);
  fclose (r_pos);
}
