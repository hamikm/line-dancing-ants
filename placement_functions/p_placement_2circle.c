/***************************************
 *                                     *
 * Function name: RANDOM_PUCK_POSITION *
 *                                     *
 * Author: B. Lin                      *
 *                                     *
 * Date: 15  May, 2002                 *
 * Revision: 0                         *
 *                                     *
 * Place pucks in concentric circles   *                                  
 *                                     *
 * Input: puck array                   *
 *        and puck total               *
 * Output: none                        *
 ***************************************/

void P_PLACEMENT(s_puck *a_puck, int p_tot)
{ 
  int temp, p_count, circle;
  int dist; 
  float theta, angle; 
  float b,z; 
  float perc= 0.50; 
  int clust1; 
  a_puck[0].p.x= 0.20*X_SIZE;                                                  
  a_puck[0].p.y= 0.50*Y_SIZE;  
  a_puck[0].c_num=0;  
  
  temp=6; 
  theta=0; 
  p_count=1; 
  dist = 2* P_SIZE; 
  
  clust1=p_tot*perc; 
  b=a_puck[0].p.x;                                                              
  z=a_puck[0].p.y;
  printf("%d \n", clust1);
  while(p_count< clust1)
    {
      circle = temp; 
      angle= (2*PI)/temp;
      while(circle >= 1 && p_count<clust1)
	{
	  a_puck[p_count].p.x = cos(theta)*dist+b; 
	  a_puck[p_count].p.y= sin(theta)*dist+z; 
	  a_puck[p_count].c_num=p_count;
	  theta+=angle;
	  circle--; 
	  p_count++; 
	}
       
      temp+=6; 
      theta=0; 
      dist+= 2*P_SIZE; 
    } 
  /* REINITIALIZATION */ 
  temp=6; 
  theta=0;  
  dist = 2* P_SIZE; 
  a_puck[p_count-1].p.x=0.80*X_SIZE; 
  a_puck[p_count-1].p.y=0.50*Y_SIZE; 
  
  b=a_puck[p_count-1].p.x;                                                             
  z=a_puck[p_count-1].p.y;
  /* SAME AS THE WHILE LOOP ABOVE */ 
  while(p_count<p_tot)
    {
      circle = temp; 
      angle= (2*PI)/temp;
      while(circle >= 1)
	{
	  a_puck[p_count].p.x = cos(theta)*dist+b; 
	  a_puck[p_count].p.y= sin(theta)*dist+z; 
	  a_puck[p_count].c_num=p_count;
	  theta+=angle;
	  circle--; 
	  p_count++; 
	}
      temp+=6; 
      theta=0; 
      dist+= 2*P_SIZE; 
    }
}

