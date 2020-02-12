/*************************************
 *                                   *
 *               SPIRAL              *
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to spiral a robot                 *
 *                                   *
 *************************************/

void SPIRAL(s_robot *a_robot, float *x)
{
  if(a_robot->time >= STRAIGHT_TIME) {
    if(a_robot->sdirection > 0)
      a_robot->angle += R_MOVE_MAX*PI/(2*sqrt(1+a_robot->angle*a_robot->angle));
    else
      a_robot->angle -= R_MOVE_MAX*PI/(2*sqrt(1+a_robot->angle*a_robot->angle));
  }
  *x = R_MOVE_MAX;
}
