/**************************************
 *                                    *
 *             P_PLACEMENT            *
 *                                    *
 * Originally written by:             *
 *   Hamik Mukelyan                   *
 *                                    *
 * to return position vectors         *
 * distributed around <homex, homey>  *
 * according to a gaussian           *
 * distribution                      *
 *                                    *
 **************************************/

s_vec POSITION(float variance, float homex, float homey)
{
  s_vec pos;
  float theta = 2 * PI * ran2(&seed);
  float mu = 0; // change mu if you want, but be consistent
  float max; // y-val of rel max
  float y; // randomly selected y in (0,max)
  float x;
  s_vec homevec;
  
  homevec.x=homex;
  homevec.y=homey;

  // find max val of function
  max = 1/(variance*sqrt(2*PI));
  y = ran2(&seed) * max;

  // find x (distance from home loc) using inverse function
  x = mu + sqrt(-2*variance*variance*log(y*variance*sqrt(2*PI))); // log is natural log

  // find cartesian coordinates
  pos.x = x * cos(theta) + homex;
  pos.y = x * sin(theta) + homey;

  if(VEC_MAG(VEC_DIF(pos, homevec)) < 2*(P_SIZE+R_SIZE))
    return POSITION(variance, homex, homey);
  else
    return pos;
}
