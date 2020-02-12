/***************************************
 *                                     *
 * FUNCTION NAME : P_PLACEMENT_HEXAGON *
 *                                     *
 * Author: A. Grosz, B. Lee            *
 * Date: 10 April 2002                 *
 * Version: 1.0                        *
 *                                     *
 * Creates a hexagon of pucks          *
 *                                     *
 * Input: structure of pucks, amount   *
 * Output: none                        *
 ***************************************/ 

void P_PLACEMENT (struct puck *a_puck, int p_tot ) {
  
  int p_tot2;       /* total number of pucks */
  int sub;          /* number subtracted from p_tot2 */
  int ap;           /* apothem */
  int m;            /* puck number */
  int i, x;         /* control variables */
  s_vec c;          /* center vector */
  int left;         /* number of pucks left after making perfect hexagon */
  
  p_tot2 = p_tot;
  c.x = X_SIZE/2;
  c.y = Y_SIZE/2;
  m = 0;
  
  /* test for number of rows possible */
  
  sub = 6;
  p_tot2 = p_tot2 - 1;
  while (p_tot2 >= 0) {
    p_tot2 = p_tot2 - sub;
    sub = sub + 6;
  }
  if (p_tot2 < 0) 
    ap = sub/6 - 2;
  else ap = sub/6 -2;

  /* place center row */
  
  a_puck[m].p.x = c.x;
  a_puck[m].p.y = c.y;
  m++;
  for (i = 1; i <= ap; i++) {
    a_puck[m].p.x = c.x - (i * 2 * P_SIZE);
    a_puck[m].p.y = c.y;
    m++;
    a_puck[m].p.x = c.x + (i * 2 * P_SIZE);
    a_puck[m].p.y = c.y;
    m++;
  }

  /* place center column */
  
  for (i = 1; i <= ap; i++) {
    a_puck[m].p.y = c.y - (i * 2 * P_SIZE);
    a_puck[m].p.x = c.x;
    m++;
    a_puck[m].p.y = c.y + (i * 2 * P_SIZE);
    a_puck[m].p.x = c.x;
    m++;
  }
 
  /* place all other rows */
  
  for (i = 1; i <= ap; i++) {
    for (x = 1; x <= ((ap + i)/2); x++) {
      a_puck[m].p.x = c.x + (x * 2 * P_SIZE);
      a_puck[m].p.y = c.y - (ap + 1 - i);
      m++;
      a_puck[m].p.x = c.x - (x * 2 * P_SIZE);
      a_puck[m].p.y = c.y - (ap + 1 - i);
      m++;
      a_puck[m].p.x = c.x + (x * 2 * P_SIZE);
      a_puck[m].p.y = c.y + (ap + 1 - i);
      m++;
      a_puck[m].p.x = c.x - (x * 2 * P_SIZE);
      a_puck[m].p.y = c.y + (ap + 1 - i);
      m++;
    }
  }

 /* place leftover pucks */
  
  left = p_tot - m;
  x = 1;
  while (left > 0) {
    if (left > 0) {
      a_puck[m].p.x = c.x;
      a_puck[m].p.y = c.y + ap + (x * 2 * P_SIZE);
      m++;
      left--;
    }
    i = 1;
    while ((i <= (ap/2)) && (left > 0)) {
      a_puck[m].p.x = c.x + (i * 2 * P_SIZE);
      a_puck[m].p.y = c.y + ap + (x * 2 * P_SIZE);
      m++;
      left--;
      if ((i <= (ap/2)) && (left > 0)) {
	a_puck[m].p.x = c.x - (i * 2 * P_SIZE);
	a_puck[m].p.y = c.y + ap + (x * 2 * P_SIZE);
	m++;
	left--;
      }
      i++;
    }
    i = 1;
    if (left > 0) {
      a_puck[m].p.x = c.x;
      a_puck[m].p.y = c.y - ap - (x * 2 * P_SIZE);
      m++;
      left--;
    }
    if (left > 0) {
      while ((i <= (ap/2)) && (left > 0)) {
	a_puck[m].p.x = c.x + (i * 2 * P_SIZE);
	a_puck[m].p.y = c.y - ap - (x * 2 * P_SIZE);
	m++;
	left--;
	if ((i <= (ap/2)) && (left > 0)) {
	  a_puck[m].p.x = c.x - (i * 2 * P_SIZE);
	  a_puck[m].p.y = c.y - ap - (x * 2 * P_SIZE);
	  m++;
	  left--;
	}
	i++;
      }
    }
    x++;
  }
}


