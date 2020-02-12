/**********************************
 *     Function Name:  vec_rot    *
 *                                *
 *  Created by:  S. Kazadi        *
 *  Creation Date:  11 April 2003 *
 *                                *
 *  This function rotates a       *
 *  two dimensional vector by a   *
 *  specified angle (in radians)  *
 *                                *
 **********************************/

s_vec vec_rot(s_vec a,float angle)
{
   s_vec b;
   b.x=a.x*cos(angle)+a.y*sin(angle);
   b.y=-a.x*sin(angle)+a.y*cos(angle);
   return(b);
}
