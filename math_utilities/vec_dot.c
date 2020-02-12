/********************************
 *                              *
 * Function name: VEC_DOT       *
 *                              *
 * Author: A. Zhang             *
 * Date: 4 April 2002           *
 * Version: 1.0                 *
 *                              *
 * Find vector dot product      *
 *                              * 
 * Input: vectors               *
 * Output: dot product          *
 ********************************/

float VEC_DOT (s_vec a, s_vec b)
{
  float product;      /* calculated product */
  
  product = a.x * b.x + a.y * b.y;
  
  return product;
}
