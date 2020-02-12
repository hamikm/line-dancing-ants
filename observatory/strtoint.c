/* returns integer equivalent of str
   author: hamik mukelyan */

int strtoint(char *str)
{
	char *temp = str;
	int sum = 0, counter = 1;

	while(*++temp >= '0' && *temp <= '9')
		counter*=10;

	while(counter > 0) {
		sum+=counter*(*str++ - '0');
		counter/=10;	
	}

	return sum;		
}
