/*************************************
 *                                   *
 *             ROB_STATE             *
 *                                   *
 * Originvisy written by:            *
 *   Hamik Mukelyan                  *
 *                                   *
 * to return a pointer to the robot  *
 * in the linked list of robots      *
 * vis_robots which has state st     *
 *                                   *
 *************************************/

s_robot *ROB_STATE(s_robot *vis_robots, int st)
{
  while(vis_robots!=NULL && vis_robots->state!=st)
    vis_robots = vis_robots->next;
  if(vis_robots!=NULL)
    return vis_robots;
  return NULL;
}
