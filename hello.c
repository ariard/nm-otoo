#include <stdio.h>

int	dix = 10;

extern void SomeFunctions;

int	global;

static int private = 0;

__private_extern__ int y = 0;

int	main(void)
{

	printf("hello world!\n");
	return (0);
}
