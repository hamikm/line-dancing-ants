/*************************************
 *                                   *
 *           HIGHEST_STATE           *
 *                                   *
 * Originally written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to return a pointer to the        *
 * (visible) robot with the highest  * 
 * state or second highest state     *
 *                                   *
 *************************************/

// notes 
// vis_robots is a linked list of all robots within R_VIEW_DIST units of a particular robot
// if num == 1, will return highest visible state. if num == 2, second highest

s_robot *HIGHEST_STATE(s_robot *vis_robots, int num)
{                                          
  s_robot *highest = vis_robots, *second_highest = NULL, *temp = vis_robots;

  if(temp == NULL || temp->r_num == -1 || num < 1 || num > 2) // if r_num is -1, there are no
    return NULL;                                              // visible robots

  while(temp != NULL) { // r_num can only be -1 if temp points to the first
                        // element of the linked list
    if(temp->state > highest->state)
      highest = temp;
    temp = temp->next;
  }
  temp = vis_robots;

  while(temp != NULL && second_highest == NULL) { // r_num only -1 if temp points to the first
                                                  // element of the linked list
    if(temp->state < highest->state) {
      second_highest = temp;
    }
    temp = temp->next;
  }
  temp = vis_robots;
  while(temp != NULL && second_highest != NULL) { // r_num can only be -1 if temp points to the first
                              // element of the linked list
    if(temp->state > second_highest->state && temp->state < highest->state) {
      second_highest = temp;
    }
    temp = temp->next;
  }

  if(num == 1)
    return highest;
  else
    return second_highest;
}
