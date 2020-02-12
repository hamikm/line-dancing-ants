/*************************************
 *                                   *
 *              R_LIST               *
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to return a pointer to the first  *
 * node of a linked list of all the  *
 * robots in a_robot's viewing range *
 *                                   *
 *************************************/

s_robot *R_LIST (s_robot *all_robots, s_robot *robot) 
{
  int i;
  s_robot *head, *temp;

  head = (s_robot *) malloc(sizeof(s_robot));
  temp = (s_robot *) malloc(sizeof(s_robot));

  head->r_num = -1;
  temp->r_num = -1;
  temp->next = temp;

  while(all_robots != NULL) {
    if(VEC_MAG(VEC_DIF(robot->p, all_robots->p)) < R_VIEW_DIST && all_robots != robot) {
      head->state = all_robots->state;
      head->r_num = all_robots->r_num;
      head->p.x = all_robots->p.x;
      head->p.y = all_robots->p.y;
      head->attachable = all_robots->attachable;
      break;
    }
    all_robots = all_robots->next;
  }
  
  if(all_robots == NULL) {
    head->next = NULL;
    free(temp);
    return head;
  }
  else {
    all_robots = all_robots->next;
    head->next = temp;
  }

  while(all_robots != NULL) {
    if(VEC_MAG(VEC_DIF(robot->p, all_robots->p)) < R_VIEW_DIST && all_robots != robot) {
      temp = temp->next;
      temp->state = all_robots->state;
      temp->r_num = all_robots->r_num;
      temp->p.x = all_robots->p.x;
      temp->p.y = all_robots->p.y; 
      temp->attachable = all_robots->attachable;
      temp->next = (s_robot *) malloc(sizeof(s_robot));
    }
    all_robots = all_robots->next;  
  }

  if(temp->r_num == -1) {
    free(temp);
    head->next = NULL;
  }
  else {
    free(temp->next);
    temp->next = NULL;
  }

  return head;
}
