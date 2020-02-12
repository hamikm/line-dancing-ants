/****************************************
 *                                      *
 *             LOWEST_STATE             *
 *                                      *
 * Originally written by:               *
 *   Hamik Mukelyan                     *
 *                                      *
 * to return a pointer to the robot     *
 * with the lowest visible state        *
 *                                      *
 ****************************************/

s_robot *LOWEST_STATE(s_robot *vis_robots, int num) // 1 corresponds to lowest, 2 to second_lowest
{                                          
  s_robot *lowest = vis_robots, *second_lowest = NULL, *temp = vis_robots;

  if(temp == NULL || temp->r_num == -1 || num < 1 || num > 2) // if r_num is -1, there are no
    return NULL;                                              // visible robots

  while(temp != NULL) { // find lowest
    if(temp->state < lowest->state)
      lowest = temp;
    temp = temp->next;
  }
  temp = vis_robots;

  if(num==2 && lowest != NULL) {
    while(temp != NULL) { // find highest and assign to second_lowest
      if(temp->state > lowest->state) {
        second_lowest = temp;
      }
      temp = temp->next;
    }
    temp = vis_robots;
  
    while(temp != NULL && second_lowest!=NULL) { // creep second_lowest (the highest state) down to the actual second lowest
      if(temp->state < second_lowest->state && temp->state > lowest->state) {
        second_lowest = temp;
      }
      temp = temp->next;
    }
  }

  if(num == 1)
    return lowest;
  else
    return second_lowest;
}
