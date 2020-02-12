/********************************
 *                              *
 * Function name: VEC_CRS       *
 *                              *
 * Author: A. Zhang             *
 * Date: 4 April 2002           *
 * Version: 1.0                 *
 *                              *
 * Vector cross product         *
 *                              * 
 * Input: vectors               *
 * Output: cross product        *
 ********************************/

float VEC_CRS (s_vec a, s_vec b)
{
  float product;       /* calculated product */
  
  product = a.x * b.y - a.y * b.x;
  
  return product;
}
