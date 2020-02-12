/********************************
 *                              *
 * Function name: VEC_UNT       *
 *                              *
 * Author: A. Zhang             *
 * Date: 9 April 2002           *
 * Version: 1.0                 *
 *                              *
 * Find unit vector at angle    *
 *                              * 
 * Input: angle                 *
 * Output: unit vector          *
 ********************************/

s_vec VEC_UNT (float angle)
{
  s_vec unit;          /* calculated unit vector */

  unit.x = cos (angle);
  unit.y = sin (angle);

  return unit;
}
