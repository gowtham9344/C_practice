#include <stdio.h>

int main ()
{
	char c;
	while ((c = getchar ()) != EOF && c != '\n')
		printf ("%d ", c);

	return 0;
}
