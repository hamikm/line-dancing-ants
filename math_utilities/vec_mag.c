/********************************
 *                              *
 * Function: VEC_MAG            *
 *                              *
 * Author: A. Zhang             *
 * Date: 4 April 2002           *
 * Version: 1.0                 *
 *                              *
 * Find magnitude of vector     *
 *                              *
 * Input: vector                *
 * Output: magnitude            *
 ********************************/

float VEC_MAG(s_vec v)
{
  float mag;        /* calculated magnitude */

  mag = sqrt (v.x * v.x + v.y * v.y);

  return mag;
}
