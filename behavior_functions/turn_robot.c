/*****************************
 *                           *
 * Function Name: R_TURN     * 
 *                           * 
 * Author: A. Lim, A. Zhang  *
 * Date: 6 April 2002        *
 * Version: 1.0              *
 *                           *
 * Turns a single robot      *
 *                           *
 * Input: array of robots,   *
 *        current robot      *
 * Output: none              * 
 *****************************/

void R_TURN (s_robot *a_robot)
{
  a_robot->angle = 2 * PI * ran2 (&seed);
}


