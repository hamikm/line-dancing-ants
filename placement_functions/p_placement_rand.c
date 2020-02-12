/**************************************
 *                                    *
 *             P_PLACEMENT            *
 *                                    *
 * Originally written by:             *
 *   A. Zhang                         *
 *                                    *
 * to randomly place pucks in square  *
 * with opposite corners at (0,0) and *
 * (100, 100)                         *
 *                                    *
 * Modified by:                       *
 *   Hamik Mukelyan                   *
 *                                    *
 * to place pucks around home loc     *
 * via gaussian distribution (pucks   *
 * more dense nearer home loc)        *
 *                                    *
 **************************************/

void P_PLACEMENT (s_puck *a_puck, int p_tot, float variance, float homex, float homey)
{
  float dist;             /* distance between pucks */
  int i, j;               /* control variables */
  int need_new;           /* 0 if coord free, 1 if occupied */

  /* place all pucks */
  for (i = 0; i < p_tot; i++) {
    need_new = 1;
    while (need_new == 1) {
      /* regenerate coordinate */
      a_puck[i].p = POSITION (variance, homex, homey);

      /* test new coord */
      j = 0;
      dist = 3 * P_SIZE;
      if (i > 0) {
	while ((dist > (2 * P_SIZE + P_SIZE/10.0)) && (j < i)) {
	  dist = VEC_MAG (VEC_DIF (a_puck[i].p, a_puck[j].p));
	  j++;
	}
      }
      if (dist > (2 * P_SIZE + P_SIZE/10.0)) {
	/* test passed */
	need_new = 0;
      }
    }
  }
}
