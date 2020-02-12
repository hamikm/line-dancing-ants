void FREE_LIST (s_puck *head)
{
  s_puck *current;
  
  current=head;
  while (head!=NULL) {
     head = head->next;
     free(current);
     current = head;
  }
}

  
