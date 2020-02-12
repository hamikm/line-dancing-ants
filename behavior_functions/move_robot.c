/*************************************
 *                                   *
 *              R_MOVE               *
 *                                   *
 * Originally written by:            *
 *   A. Lim                          *
 *   M. Chung                        *
 *   B. Lee                          *
 *   A. Zhang                        *
 *   A. Grosz                        *
 *                                   *
 * to move a single robot in a puck  *
 * clustering simulation             *
 *                                   *
 * Modified (a lot) by:              *
 *   Hamik Mukelyan                  *
 *                                   *
 * to move a single robot in a       *
 * search and retrieve "chain"       *
 * simulation                        *
 *                                   *
 *************************************/

/*
Use this algorithm outline to navigate this file (grep or ctrl-f each title). 
Brief descriptions of each part of the algorithm are in parentheses.

START OUTLINE

create linked list of all robots within R_VIEW_MAX radius of robot
  (and initialize misc variables. see comments in code)
create linked list of all pucks within R_VIEW_MAX radius of robot
  (except for any puck that is being carried or does not exist (exist = 0). also initialize misc variables. 
  see comments in code)
don't see robots w/ states >= 0
  (become a -1 robot if you lose the chain, then spiral)
see robots with states >= 0
  seeking highest state or attaching to chain. (state is -1)
    are searcher robot (will never attach to chain. will keep on looking for pucks)
      don't have a puck
        see pucks (seek pucks)
          near enough to pick up puck (pick up puck)
          not near enough to pick up puck (move straight toward puck)
        do not see pucks (orbit around chain at 3/2.0 * C_DIST)
      have a puck (orbit around chain at 2 * C_DIST and deposit when necessary)
    are chain former robot (will attach to chain and ignore puck collection)
      within attaching distance of the robot with the highest vis state
        attach at any angle if the highest state robot is the home loc robot (become first element of chain)
        at end of chain (attach to chain)
      moving toward highest vis state (orbit around chain at C_DIST)
  home loc robot (state is 0. adjust attachable bit so only one chain forms)
  in-chain behavior (state is > 0)
    are driver. highest state robot
      (move perpendicular to chain. move closer to robot below you if you move out too far, and move away from
      robot below you if you move in too close. sif you see a robot trying to attach (a robot with state
      -1 that is designated a chain former with attachable = 1), stop and wait for it to attach)
    are middle robot
      (move to midpoint of line connecting robots with next highest and next lowest states (home robot and state
      2 robot if you are state 1 robot)
don't bump into other robots
  (avoid collisions with robots)
don't bump into pucks
  (avoid collisions with pucks that exist and are not being carried)
execute move
  (reset your position vector p and reset the position vector of the puck that you are carrying, if you are 
  carrying one)
free memory used by this function
  (free memory used used by routines that constructed linked lists of visible robots and pucks. see range_r
  and range_p)
turn
  (if robot and puck collision avoidance behavior asks you to turn, turn!)

END OUTLINE
*/

void R_MOVE (s_robot *a_robot, s_puck *all_pucks, s_robot *all_robots, float iter)
{
  int need_turn;                 // 1 if robot needs to turn
  s_vec v;                       // vector to new location 
  s_vec u;                       // unit vector robots movement 
  s_vec max;                     // vector of maximum displacement 
  s_vec t;                       // test displacement vector 
  s_vec d;                       // distance vector between objects 
  float z;                       // vector cross product 
  float Pd;                      // distance to adjust move by 
  int i;                         // counter 
  s_robot *ptr = all_robots;     // ptr to first elem of linked list of all robots
  float x = 0;                   // dist to move this timestep
  float dum;                     // used for robot-robot and robot-puck collision avoidance
  float xx;                      // also used for collision avoidance
  s_puck *p_ptr = all_pucks;     // points to first element of linked list of all pucks
  float pp_size;                 // collision avoidance variable
 
  // variables declared below and related operations are chain-specific
  s_robot *range_r, *temp_r;     // both ptrs to the robots that this robot can see
  s_robot *home_r;               // home robot
  s_robot *highest;              // robot with highest visible state
  s_robot *second_highest;       // robot with second highest visible state
  s_robot *lowest;               // robot with lowest visible state
  s_robot *second_lowest;        // robot with second lowest visible state
  s_robot *one_up;               // robot with state one greater than state of this robot
  s_robot *one_down;             // robot with state one less than state of this robotd
  s_vec between;                 // pos point midway between robs with states a_robot->state+-1  
  s_vec attach;                  // attach point
  int TEMP = 0;                  // convenient temporary integer
  float dist, theta;             // convenient variables
  char see_attacher = 0;         // boolean type. 1 for see -1 state robot
  s_robot *nearest_chain_r;      // nearest robot that is in chain
  s_robot *nearest_r;            // nearest general robot
  s_puck *range_p, *temp_p;      // ptrs to pucks this robot can see
  s_puck *nearest_p;             // ptr to puck nearest this robot
  int pickup = 0;                // if 1, pick up puck
  int dropoff = 0;               // if 1, drop off puck

  // initialize variables
  need_turn = 0;
  u = VEC_UNT (a_robot->angle);
  v = VEC_SCL (u, x);
  
  // START create linked list of all robots within R_VIEW_MAX radius of robot
  range_r = temp_r = R_LIST(ptr, a_robot);
  if(range_r->r_num==-1) {
    free(range_r);
    range_r = temp_r = NULL;
  }
  highest = HIGHEST_STATE(range_r, 1);
  second_highest = HIGHEST_STATE(range_r, 2);
  lowest = LOWEST_STATE(range_r, 1);
  second_lowest = LOWEST_STATE(range_r, 2);
  home_r = ROB_STATE(range_r, 0);
  nearest_r = nearest_chain_r = highest; // set to anything. changed in loop later if necc.

  while(temp_r!=NULL) {
    if(temp_r->state == -1 && temp_r->attachable == 1)
      see_attacher = 1; // if the end robot sees a robot that can attach to the chain, it does not drive the chain (stops)
    if(VEC_MAG(VEC_DIF(a_robot->p, temp_r->p)) < VEC_MAG(VEC_DIF(a_robot->p,nearest_r->p))) // find nearest gen rob
      nearest_r = temp_r;
    if(temp_r->state >= 0) { // find nearest robot that's in chain
      if(VEC_MAG(VEC_DIF(a_robot->p, temp_r->p)) < VEC_MAG(VEC_DIF(a_robot->p,nearest_chain_r->p)))
        nearest_chain_r = temp_r;
    }
    temp_r = temp_r->next;
  }
  temp_r = range_r;

  // if crashed
  if(nearest_r!=NULL && VEC_MAG(VEC_DIF(a_robot->p, nearest_r->p)) < 2*R_SIZE - 2*ERROR) {
    a_robot->active = 0; printf("i crashed into a robot\n");
  } // END create linked list of all robots within R_VIEW_MAX radius of robot

  // START create linked list of all pucks within R_VIEW_MAX radius of robot
  range_p = temp_p = nearest_p = P_LIST(a_robot, p_ptr, a_robot->pucky);
  if(range_p->p_num==-1) {
    free(range_p);
    range_p = temp_p = nearest_p= NULL;
  }

  while(temp_p!=NULL) {
    if(temp_p->p_num>-1) {
      if(VEC_MAG(VEC_DIF(a_robot->p, temp_p->p)) < VEC_MAG(VEC_DIF(a_robot->p,nearest_p->p))) // find nearest puck
        nearest_p = temp_p;
    }
    temp_p=temp_p->next;
  }
  temp_p = range_p;

  // if crashed
  if(nearest_p!=NULL && VEC_MAG(VEC_DIF(a_robot->p, nearest_p->p)) < (R_SIZE + P_SIZE - 2*ERROR)) {
    a_robot->active = 0; printf("i crashed into a puck\n");
  } // END create linked list of all pucks within R_VIEW_MAX radius of robot

  // START don't see robots w/ states >= 0
  if(a_robot->active && (highest == NULL ? 1 : highest->state == -1)) {
    
    if(a_robot->state > 0) {
      a_robot->state = -1;
    }

    SPIRAL(a_robot, &x);
  } // END don't see robots w/ states >= 0
  
  // START see robots with states >= 0
  if(a_robot->active && (highest != NULL ? highest->state > -1 : 0)) {
    
    // START seeking highest state or attaching to chain. have state -1
    if(a_robot->state == -1) {
      
      // START are searcher robot
      if(a_robot->attachable==0) { // if are searcher robot

        // START don't have a puck
        if(a_robot->pucky==-1) {

          // START see pucks
          if(range_p!=NULL && VEC_MAG(VEC_DIF(a_robot->p, nearest_chain_r->p)) < R_VIEW_DIST) {

            // START near enough to pick up puck
            if(VEC_MAG(VEC_DIF(a_robot->p, nearest_p->p)) < P_SIZE + R_SIZE + .1*R_SIZE) {
              pickup = 1;
            } // END near enough to pick up puck        

            // START not near enough to pick up puck
            else {	  
              a_robot->angle=ANGLE(a_robot->p, nearest_p->p);
              x = R_MOVE_MAX;
            } // END not near enough to pick up puck

          } // END see pucks

          // START do not see pucks
          else {
            CHAIN_ORBIT(a_robot, nearest_chain_r, &x, 3*C_DIST/2.0);
          } // END do not see pucks (looking for them)

        } // END don't have a puck

        // START have a puck
        if(a_robot->pucky!=-1) {
  
          if(a_robot->dist < 0) // set dist to move to center to drop off puck
            a_robot->dist = (2*C_DIST/3.0) * ran2(&seed) + 2.1*R_SIZE;
 
          if(home_r==NULL)
            CHAIN_ORBIT(a_robot, nearest_chain_r, &x, 2 * C_DIST);
          else { // if see home robot
            if(VEC_MAG(VEC_DIF(a_robot->p,home_r->p)) < a_robot->dist) { // if inside collection center, drop off puck
              PUCK(a_robot->pucky, p_ptr)->being_carried = 0;
              PUCK(a_robot->pucky, p_ptr)->exist = 0;
              a_robot->pucky=-1;
              a_robot->dist = -1;           
            }
            else { // else, move towards collection center
              a_robot->angle = ANGLE(a_robot->p, home_r->p);
              x = R_MOVE_MAX;
            }
          }
        } // END have a puck

      } // END are searcher robot
      
      // START are chain former robot
      if(a_robot->attachable==1) {

        // START within attaching distance of the robot with the highest vis state
        if(VEC_MAG(VEC_DIF(a_robot->p, highest->p)) < C_DIST) {
	   
          // START attach at any angle if the highest state robot is the home loc robot
          if(highest == home_r && home_r->attachable == 1) { // create new chain if no other chain exists
    
            a_robot->state = 1;
            x = R_MOVE_MAX;
          } // END attach at any angle if the highest state robot is the home loc robot
	  
          // START at end of chain
          if(highest->state > 0 && second_highest != NULL) {
            if(VEC_MAG(VEC_DIF(a_robot->p, second_highest->p)) < 1.98*C_DIST) { // not near attaching point
              CHAIN_ORBIT(a_robot, highest, &x, C_DIST);
            }
            else { // near enough attaching point
              a_robot->state = highest->state + 1;
            }
          } // END at end of chain

        } // END within attaching distance of the robot with the highest vis state
  
        // START moving toward highest vis state
        else {
          if(nearest_chain_r!=highest) { // swing around "middle" robots nearest_chain_r!=home_r &&
            CHAIN_ORBIT(a_robot, nearest_chain_r, &x, C_DIST);
          }
          else {
            a_robot->angle = ANGLE(a_robot->p, highest->p);
            x = R_MOVE_MAX;
          }
        } // END moving toward highest vis state

      }

    } // END seeking highest state or attaching to chain. have state -1

    // START home loc robot
    if(a_robot->state == 0) {

      if(ROB_STATE(range_r, 1) != NULL) {
        if(a_robot->time == 1) {
          a_robot->attachable = 0; // chain exists
          a_robot->time = 0;
        }
        else
          a_robot->time++;
      }
      else { // chain disappeared
        a_robot->attachable = 1;
        a_robot->time = 0;
      }
    } // END home loc robot
	
    // START in-chain behavior
    if(a_robot->state > 0) {
      
      // START are driver. highest state robot
      if(highest->state < a_robot->state) {

        if(!see_attacher) {
          if((dist=VEC_MAG(VEC_DIF(a_robot->p, highest->p))) > C_DIST + D_ERROR)
            a_robot->angle=ANGLE(a_robot->p, highest->p) - PI/3;
          else if(dist < C_DIST - D_ERROR)
            a_robot->angle=ANGLE(a_robot->p, highest->p) - 2*PI/3;
	  else
            a_robot->angle=ANGLE(a_robot->p, highest->p) - PI/2;
        }
        else {
	  if(VEC_MAG(VEC_DIF(a_robot->p, highest->p)) > C_DIST + D_ERROR)
            a_robot->angle=ANGLE(a_robot->p, highest->p);
          else
            a_robot->angle=ANGLE(a_robot->p, highest->p) - PI;
        }
        x = R_MOVE_MAX/2.0;
      } // END are driver. highest state robot

      // START are middle robot
      if(highest->state > a_robot->state) {

        one_up = ROB_STATE(range_r, a_robot->state + 1);
        one_down = ROB_STATE(range_r, a_robot->state - 1);

        if(one_down!=NULL && one_up!=NULL) {
          between = VEC_ADD(VEC_SCL(VEC_DIF(one_up->p,one_down->p), .5), one_down->p);
          a_robot->angle = ANGLE(a_robot->p, between);
          if(VEC_MAG(VEC_DIF(a_robot->p, between)) < R_MOVE_MAX)
            x = VEC_MAG(VEC_DIF(a_robot->p, between));  
          else
            x = R_MOVE_MAX;
        }
      } // END are "middle" follower robot

    } // END in-chain behavior

  } // END see robots with states >= 0

  // START don't bump into other robots
  while (a_robot->active && ptr != NULL) {
    if (ptr != a_robot) {
      
      // find distance vector between robot and robot 
      d = VEC_DIF (ptr->p, a_robot->p);
      
      // if robot is in front 
      if (VEC_DOT (d,u) >= 0) {
	
	// if robot is too close 
	z = VEC_CRS (d,u);
	if (z<0)
	  z*=-1;
	if (z < (2 * R_SIZE + .1)) { // added .1 to reduce hiccup collisions
	  
	  // adjust distance to move 
	  dum=(2*R_SIZE)*(2*R_SIZE)-z*z;
	  if (dum<0.0001)
	    dum=0;
	  Pd = sqrt (dum);
	  dum=d.x*d.x+d.y*d.y-z*z;
	  if (dum<0.0001)
	    dum=0;
	  xx = sqrt (dum) - Pd;
	  if (xx<x) {
	    need_turn=1;
	    x=xx;
	  }
	}
      }
    }
    ptr=ptr->next;
  } 
  ptr = all_robots; // END don't bump into other robots

  // START don't bump into pucks
  pp_size=P_SIZE;
  
  while (a_robot->active && p_ptr!=NULL && !pickup) {
    if ((a_robot->pucky==-1 ? 1 : a_robot->pucky!=p_ptr->p_num) && p_ptr->exist) {
      
      // find distance vector between robot and puck 
      d = VEC_DIF(p_ptr->p, a_robot->p);
      
      // if puck is in front 
      if (VEC_DOT (d,u) > 0) {
	
	z = VEC_CRS (d, u);

	// if robot is too close 
	if (fabs (z) < (pp_size + R_SIZE + .1)) { // added .1 to reduce hiccup collisions
	  
	  // adjust distance to push puck 
	  dum=pow(pp_size+R_SIZE,2)-pow(z,2);
	  if (dum<0.0001)
	    dum=0;
	  Pd = sqrt (dum);
	  dum=d.x*d.x+d.y*d.y-z*z;
	  if (dum<0.0001)
	    dum=0;
	  xx = sqrt (dum) - Pd;
	  if (xx<x) {
	    need_turn=1;
	    x=xx;
	  }
	}
      }
    }
    p_ptr=p_ptr->next;
  } 
  p_ptr=all_pucks; // END don't bump into pucks

  if(pickup) {
    a_robot->pucky=nearest_p->p_num;
    PUCK(a_robot->pucky, p_ptr)->being_carried=1;
  }

  // START execute move
  if(a_robot->state != 0) {
    a_robot->p = VEC_ADD (a_robot->p,VEC_SCL(u,x));

    if(a_robot->pucky!=-1) { // make the pos of the puck that is being carried the same as the pos of this robot
      PUCK(a_robot->pucky, p_ptr)->p.x = a_robot->p.x; 
      PUCK(a_robot->pucky, p_ptr)->p.y = a_robot->p.y; 
    }
  } // END execute move
 
  // START free memory used by this function
  FREE_ROBOT_LIST(range_r);
  FREE_LIST(range_p); // END free memory used by this function

  if(x>0)
    a_robot->time++;

  // START turn
  if(need_turn == 1 && a_robot->state != 0) {
    R_TURN(a_robot);
    a_robot->time = 0;
    if(ran2(&seed)>0.5) // randomly select left or right spiral
      a_robot->sdirection=1; 
    else
      a_robot->sdirection=-1;
  } // END turn
}
