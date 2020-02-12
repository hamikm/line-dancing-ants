/********************************
 *                              *
 * Function name: VEC_DIF       *
 *                              *
 * Author: A. Zhang             *
 * Date: 4 April 2002           *
 * Version: 1.0                 *
 *                              *
 * Find difference of vectors   *
 *                              * 
 * Input: vectors               *
 * Output: difference           *
 ********************************/

s_vec VEC_DIF (s_vec a, s_vec b)
{
  s_vec dif;      /* calculated difference */
  
  dif.x = a.x - b.x;
  dif.y = a.y - b.y;

  return dif;
}
