/**************************************
 *                                    *
 *             P_PLACEMENT            *
 *                                    *
 * Originally written by:             *
 *   A. Grosz                         *
 *   A. Zhang                         *
 *                                    *
 * to randomly place robots in square *
 * with opposite corners at (0,0) and *
 * (100, 100)                         *
 *                                    *
 * Modified by:                       *
 *   Hamik Mukelyan                   *
 *                                    *
 * to place robots around home loc    *
 * via gaussian distribution (pucks   *
 * more dense nearer home loc)        *
 *                                    *
 **************************************/

void R_PLACEMENT (s_robot *a_robot, s_puck *a_puck, int r_tot, int p_tot, float variance, float homex, float homey)
{
  float dist_r_r;            /* dstance between robots */
  float dist_r_p;            /* distance between puck and robots */
  int i, j;                  /* control variables */
  int need_new;              /* 0 if coord free, 1 if coord occupied */

  /* place all robots */
  for (i = 0; i < r_tot; i++) {
    need_new = 1;          
    while (need_new == 1) {
      /* regenerate coordinate */
      a_robot[i].p = POSITION (variance, homex, homey);
      
      /* test new coord with robots */
      j = 0;
      dist_r_r = 3 * R_SIZE;
      if (i > 0) {
	while ((dist_r_r > (2 * R_SIZE + R_SIZE/10.0)) && (j < i)) {
	  dist_r_r = VEC_MAG (VEC_DIF (a_robot[i].p, a_robot[j].p));
	  j++;
	}
      }

      /* okay with robots */
      if (dist_r_r > (2 * R_SIZE + R_SIZE/10.0)) {

	dist_r_p = 3 * R_SIZE + P_SIZE;
	j = 0;
 
	/*test coord with pucks */
	while ((dist_r_p > (2*(R_SIZE + P_SIZE))) && (j < p_tot)) {
	  dist_r_p = VEC_MAG (VEC_DIF (a_robot[i].p, a_puck[j].p));
	  j++;
	}
	
	/* okay with pucks */
	if (dist_r_p > (2*(R_SIZE + P_SIZE))) {
	  /* test passed */
	  need_new = 0;
	}
      }
    }
  }
}
