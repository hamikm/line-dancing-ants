/*******************************
 * Function name: set_seed     *
 *                             *
 * Sets seed for generating    *
 * random numbers              *
 *******************************/

void set_seed ()
{
  time_t *tata, time1;
  struct tm *tt1;
  tata = NULL;
  time1 = time (tata);
  tt1 = gmtime (&time1);
  
  seed = -100 * (tt1->tm_sec + 60 * tt1->tm_min);
}
