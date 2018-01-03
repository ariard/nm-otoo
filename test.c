#include <mach-o/loader.h>
#include <stdio.h>

int	main(void)
{
	struct mach_header	hello;
	printf("size mach-o header : [%d]", sizeof(hello));
}
