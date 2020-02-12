/********************************
 *                              *
 * Function name: VEC_ADD       *
 *                              *
 * Author: A. Zhang             *
 * Date: 4 April 2002           *
 * Version: 1.0                 *
 *                              *
 * Find sum of vectors          *
 *                              * 
 * Input: vectors               *
 * Output: sum                  *
 ********************************/

s_vec VEC_ADD (s_vec a, s_vec b)
{
  s_vec sum;      /* calculated sum */
  
  sum.x = a.x + b.x;
  sum.y = a.y + b.y;

  return sum;
}
