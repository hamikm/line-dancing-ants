/*************************************
 *                                   *
 *             CHAIN_ORBIT           *
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to move a robot orbiting up or    *
 * down a chain                      *
 *                                   *
 *************************************/

// orbit dist makes sloppy orbits, might want to orbit around ghost robot (see back of uc merced paper) 

void CHAIN_ORBIT(s_robot *a_robot, s_robot *chain_robot, float *x, float orbit_dist)
{
  double dist;

  if(a_robot->sdirection > 0) { // swing in one direction
    a_robot->angle = ANGLE(a_robot->p, chain_robot->p) - PI/2;
    if((dist=VEC_MAG(VEC_DIF(a_robot->p, chain_robot->p))) < orbit_dist)
      a_robot->angle -= PI/6;
    if(dist > orbit_dist)
      a_robot->angle += PI/6;
  }
  else { // swing in the other direction
    a_robot->angle = ANGLE(a_robot->p, chain_robot->p) + PI/2;
    if((dist=VEC_MAG(VEC_DIF(a_robot->p, chain_robot->p))) < orbit_dist)
      a_robot->angle += PI/6;
    if(dist > orbit_dist)
      a_robot->angle -= PI/6; 
  }
  *x = R_MOVE_MAX;
}
