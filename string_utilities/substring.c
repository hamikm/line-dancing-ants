/* str indexed 0..n-1, n = number of chars in string
   x <= y and x,y >= 0 and x,y < strlen(str) 
     returns x..y-1
   otherwise
     returns pointer to null character
   
   author: hamik mukelyan */

#include <string.h>
#include <stdlib.h>

char *substring(char *str, int x, int y)
{
	int i;
	char *sub = (char *)malloc(sizeof(char) * (y - x + 1)), *temp = sub;

	printf("str = %s\n", str);

	if(x > y || x < 0 || y < 0 || x >= (i = strlen(str)) || y >= i) {
		*sub = 0;
		return sub;
	}	
	i = 0;
	while(i++ < x)
		str++;
	for(i = 0; i < y - x + 1; i++)
		*sub++ = *str++;

	return temp;
}
