#include <stdio.h>
#include <string.h>

int a = 10;

void	foobar(void)
{
	char	*dix = "dix";
	
	strlen(dix);
}

void	foo(void)
{
	printf("foo");
}

void	bar(void)
{
	printf("bar");
}
	
int	main(void)
{
	char	*a;

	a = "hello world\n";

	printf("%s\n", a);
	return (0);
}
