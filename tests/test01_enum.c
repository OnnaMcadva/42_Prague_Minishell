#include <stdio.h>

enum yourmama {
	NO,
	YES,
	WHO_KNOWS = 42,
};

int main()
{
	enum yourmama	mama;
	int				i;

	printf ("%d\n", YES); // prints 1

	mama = NO;
	printf ("%d\n", mama); // prints 0

	i = WHO_KNOWS;
	printf ("%d\n", i); // prints 42

}
