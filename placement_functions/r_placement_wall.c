/**************************************
 *                                    *
 * FUNCTION NAME : R_PLACEMENT_RAND   *
 *                                    *
 * Author: S. Kazadi                  *
 * Date: 19 June 2003                 *
 * Version: 1.0                       *
 *                                    *
 * Places pucks randomly              *
 *                                    *
 * Input: structure of pucks, amount  *
 *        structure of robots, amount *
 * Output: none                       *
 **************************************/

void R_PLACEMENT (s_robot *a_robot, s_puck *a_puck, int r_tot, int p_tot)
{
  float dist_r_r;            /* dstance between robots */
  float dist_r_p;            /* distance between puck and robots */
  int i, j;                  /* control variables */
  int need_new;              /* 0 if coord free, 1 if coord occupied */
  float first_pos=-50.0;    /* the position of the first robot in the wall */

  /* place all robots */
  for (i = 0; i < r_tot; i++) {
    if (i>-99) {
      need_new = 1;          
      a_robot[i].active=1;
      while (need_new == 1) {
	/* regenerate coordinate */
	a_robot[i].p = RANDOM_POSITION (X_SIZE, Y_SIZE, R_SIZE);
	a_robot[i].p.x+=60;
	/* test new coord with robots */
	j = 0;
	dist_r_r = 3 * R_SIZE;
	if (i > 0) {
	  while ((dist_r_r > (2 * R_SIZE - ERROR)) && (j < i)) {
	    dist_r_r = VEC_MAG (VEC_DIF (a_robot[i].p, a_robot[j].p));
	    j++;
	  }
	}
	
	/* okay with robots */
	if (dist_r_r > (2 * R_SIZE - ERROR)) {
	  
	  dist_r_p = 3 * (R_SIZE + P_SIZE);
	  j = 0;
	  
	  /*test coord with pucks */
	  while ((dist_r_p > (R_SIZE + P_SIZE - ERROR)) && (j < p_tot)) {
	    dist_r_p = VEC_MAG (VEC_DIF (a_robot[i].p, a_puck[j].p));
	    j++;
	  }
	  
	  /* okay with pucks */
	  if (dist_r_p > (R_SIZE + P_SIZE - ERROR)) {
	    /* test passed */
	    need_new = 0;
	  }
	}
      }
    }
    else
    {
      a_robot[i].p.x=-440;
      a_robot[i].p.y=first_pos;
      first_pos+=2*R_SIZE;
    }
  }
}
