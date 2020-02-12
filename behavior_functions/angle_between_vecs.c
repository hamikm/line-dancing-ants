/*************************************
 *                                   *
 *               ANGLE               *
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to return the angle between two   *
 * 2-vectors relative the first      *
 * argument                          *
 *                                   *
 *************************************/

float ANGLE(s_vec s1, s_vec s2)
{
  float angle; // angle between rob1 and rob2 relative rob1
  s_vec *diff; // vector between rob1 and rob2 relative rob1

  diff = (s_vec *) malloc(sizeof(s_vec));
  *diff = VEC_DIF(s1, s2);

  if(diff->x < 0) {
    if(diff->y > 0) {
      angle = atan(diff->y / diff->x) + 2 * PI;
    }
    if(diff->y < 0) {
      angle = atan(diff->y / diff->x); 
    }
    if(diff->y == 0) {
      angle = 0;
    }
  }
  else if(diff->x > 0) {
    if(diff->y > 0) {
      angle = atan(diff->y / diff->x) + PI;
    }
    if(diff->y < 0) {
      angle = atan(diff->y / diff->x) + PI;
    }
    if(diff->y == 0) {
      angle = PI;
    }
  }
  else {
    if(diff->y > 0) {
      angle = 3 * PI / 2;
    }
    if(diff->y < 0) {
      angle = PI / 2;
    }
  }

  free(diff);

  return angle;
}
