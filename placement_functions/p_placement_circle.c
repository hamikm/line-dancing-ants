/***************************************
 *                                     *
 * Function name: RANDOM_PUCK_POSITION *
 *                                     *
 * Author: B. Lin                      *
 *                                     *
 * Date: 6  May, 2002                  *
 * Revision: 1                         *
 *                                     *
 * Place pucks in concentric circles   *                                  
 *                                     *
 * Input: puck array                   *
 *        and puck total               *
 * Output: none                        *
 ***************************************/

void P_PLACEMENT (s_puck *a_puck, int p_tot)
{ 
  int temp; /* number of pucks in a concentric circle */ 
  int p_count; /* current puck number */  
  int circle; /* temporary variable */ 
  int dist; /* distance between adjacent concentric circle */ 
  float theta; /* angle of concentric circle */  
  float angle; /* amount of degree to increase theta by */ 
  float b,z; /* stores x and y position of first puck */ 

  /* Initialization */ 
  a_puck[0].p.x= 0.50*X_SIZE;                                                  
  a_puck[0].p.y= 0.50*Y_SIZE;  
  a_puck[0].c_num=0;  

  temp=6; 
  theta=0; 
  p_count=1; 
  dist = 2* P_SIZE; 

  
  b=a_puck[0].p.x;                                                              
  z=a_puck[0].p.y;

  /* Placing Pucks in Concentric Circles */ 
  
  /* If there are still pucks to be placed */ 
  while(p_count<p_tot)
    {
      circle = temp; 
      angle= (2*PI)/temp;
      /* While there is enough pucks to be placed in circle */ 
      while(circle >= 1)
	{
	  a_puck[p_count].p.x = cos(theta)*dist+b; 
	  a_puck[p_count].p.y= sin(theta)*dist+z; 
	  a_puck[p_count].c_num=p_count;
	  theta+=angle;
	  circle--; 
	  p_count++; 
	}
      /* Reset value and increase distance */ 
      temp+=6; 
      theta=0; 
      dist+= 2*P_SIZE; 
    }
}

  



