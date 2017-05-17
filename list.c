#include <mach-o/nlist.h>
#include <stdio.h>

int		main(void)
{
	printf("%lu\n", sizeof(struct nlist_64));
	return (0);
}
