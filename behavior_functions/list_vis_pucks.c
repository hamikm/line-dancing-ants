/*************************************
 *                                   *
 *              P_LIST               *
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to return the first element of a  *
 * linked list of visible pucks for  *
 * a particular robot                *
 *                                   *
 *************************************/

s_puck *P_LIST(s_robot *robot, s_puck *all_pucks, int holding)
{
  int i;
  s_puck *head, *temp;

  head = (s_puck *) malloc(sizeof(s_puck));
  temp = (s_puck *) malloc(sizeof(s_puck));

  head->p_num = -1;
  temp->p_num = -1;
  temp->next = temp;

  while(all_pucks != NULL) {
    if(VEC_MAG(VEC_DIF(robot->p, all_pucks->p)) < R_VIEW_DIST && all_pucks->being_carried!=1 
       && (holding==-1 ? 1 : all_pucks->p_num!=holding) && all_pucks->exist) {
      head->p.x = all_pucks->p.x;
      head->p.y = all_pucks->p.y;
      head->p_num = all_pucks->p_num;
      break;
    }
    all_pucks = all_pucks->next;
  }

  if(all_pucks == NULL) {
    head->next = NULL;
    free(temp);
    return head;
  }
  else {
    all_pucks = all_pucks->next;
    head->next = temp;
  }

  while(all_pucks != NULL) {
    if(VEC_MAG(VEC_DIF(robot->p, all_pucks->p)) < R_VIEW_DIST && all_pucks->being_carried!=1
       && (holding==-1 ? 1 : all_pucks->p_num!=holding) && all_pucks->exist) {
      temp = temp->next;
      temp->p.x = all_pucks->p.x;
      temp->p.y = all_pucks->p.y;
      temp->p_num = all_pucks->p_num;
      temp->next = (s_puck *) malloc(sizeof(s_puck));
    }
    all_pucks = all_pucks->next;  
  }

  if(temp->p_num == -1) {
    free(temp);
    head->next = NULL;
  }
  else {
    free(temp->next);
    temp->next = NULL;
  }

  return head;
}
