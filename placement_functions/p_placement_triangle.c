/*************************************
 * FUNCTION: P_PLACEMENT_TRIANGLE    *
 *                                   *
 * Author: B. Lee, M. Chung          *
 * Date: 10 April 2002               *
 * Version: 1.0                      *
 *                                   *
 * Creates a triangle of pucks       *
 *                                   *
 * Input: structure of pucks, amount *
 * Output: none                      *
 *************************************/


void P_PLACEMENT (s_puck *a_puck, int p_tot)
{ 
  int i, j, m;           /* control variables */
  s_vec p_i;             /* initial position */
  
  /* initialize */
  m = 0;
  p_i.x = 25;
  p_i.y = 25;
  
  for (i = 0; i <= sqrt (2 * p_tot); i++) {
    for (j = 0; j <= i; j ++) {
      /* puck placement */
      a_puck[m].p.x = i * 2 * P_SIZE + p_i.x;
      a_puck[m].p.y = j * 2 * P_SIZE + p_i.y;
      m++;
    }
  }
}







