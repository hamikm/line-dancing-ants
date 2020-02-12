/********************************
 *                              *
 * Function name: VEC_SCL       *
 *                              *
 * Author: A. Zhang             *
 * Date: 4 April 2002           *
 * Version: 1.0                 *
 *                              *
 * Multiply vector by scalar    *
 *                              * 
 * Input: vector, scalar        *
 * Output: vector               *
 ********************************/

s_vec VEC_SCL (s_vec a, float k)
{
  s_vec b;                /* resulting vector */

  b.x = a.x * k;
  b.y = a.y * k;

  return b;
}
