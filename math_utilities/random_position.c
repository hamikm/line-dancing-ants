/**********************************
 *                                *
 * Function: RANDOM_POSITION      *
 *                                *
 * Author: A. Zhang               *
 * Date: 4 April 2002             *
 * Version: 1.1                   *
 *                                *
 * Return a random position       *
 *                                *
 * Input: arena size, object size *
 * Output: position               *
 *                                *
 **********************************/

s_vec RANDOM_POSITION (float x_size, float y_size, float obj_size)
{
  s_vec pos;        /* calculated position */

  /* randomly generate a position */
  pos.x = (x_size - 2 * obj_size) * ran2 (&seed) + obj_size;
  pos.y = (y_size - 2 * obj_size) * ran2 (&seed) + obj_size;

  return pos;
}

/**********************************
 *                                *
 * CHANGES                        *
 *                                *
 * 1.1 - added object size        *
 *                                *
 **********************************/


