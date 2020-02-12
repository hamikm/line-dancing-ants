/**************************************
 *                                    *
 * FUNCTION NAME : P_PLACEMENT_LINE   *
 *                                    *
 * Author: B. Lin                     *
 * Date: 13 April 2002                *
 * Version: 1.0                       *
 *                                    *
 * Places pucks in lines              *
 *                                    *
 * Input: structure of pucks, amount  *
 * Output: none                       *
 **************************************/ 

void P_PLACEMENT (s_puck *a_puck, int p_tot)
{
  int i, j;          /* incremental variable */  
  int p_num;         /* The current number of the puck */ 
  int n;             /* Distance variable between each row */ 
  int  rows;         /* number of rows total */ 
  int amount;        /* number of pucks in a row */ 
  s_vec pos;         /* position vector */
 
  /* Initialization */ 
  
  pos.x = 0.10*X_SIZE; 
  pos.y = 0.90*Y_SIZE; 
  p_num = 0;         /*current number of the puck */
  n = 8; 
  amount = (X_SIZE - X_SIZE * 0.2) / (2 * P_SIZE); 
  rows = p_tot / amount;
  for(i = 0; i < rows; i++) {
    for(j = 0; j < amount; j++) {
      a_puck[p_num].p = pos; 
      pos.x += (2 * P_SIZE); 
      p_num++; 
    }
    pos.y -= (n * R_SIZE); 
    pos.x = 0.10 * X_SIZE; 
  }
  /* If there are left over pucks */
  while(p_num < p_tot) {
    a_puck[p_num].p = pos; 
    pos.x += (2 * P_SIZE); 
    p_num++; 
  }
}
