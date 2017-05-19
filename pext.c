#include <stdio.h>

int		main(void)
{
	int		a = 0b11111111;
	int		new;

	printf("%d\n", a);
	printf("%d\n", 0x10);
	new = a & 0x10;
	printf("%d\n", new);
	a = 0b11101111;
	new = a & 0x10;
	printf("%d", new);
	return (0);
}
