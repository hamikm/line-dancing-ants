/*************************************
 *                                   *
 *              R_MOVE               *
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to return a pointer to the puck   *
 * with id number num                *
 *                                   *
 *************************************/

s_puck *PUCK(int num, s_puck *all_pucks)
{
  while(all_pucks!=NULL && all_pucks->p_num!=num)
    all_pucks=all_pucks->next;

  if(all_pucks!=NULL && all_pucks->p_num==num && all_pucks->exist)
    return all_pucks;
  return NULL;
}
