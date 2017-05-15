#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

struct 	s_type
{
	int	match;
	char	*symbole;
};

typedef struct s_type		t_type; 

struct	s_subtype
{
	int	subtype;
	char	*symbole;
};

typedef struct s_subtype	t_subtype;
static	t_type		g_machosym[] =
{
	{0xe0, "stab"},
	{0x10, "limited global scope"},
	{0xe, "y"},
	{0x01, "external symbol"},
	{0, "null"}
};

static 	t_subtype	g_machsubtype[] =
{
	{0x0, "U"},
	{0x2, "A"},
	{0xe, "S"},
	{0xc, "pbud"},
	{0xa, "I"},
	{0, "null"},
};

void		print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int			i;
	int			j;
	int			k;
	char			*symbole;
	char			*stringtable;
	struct	nlist_64 	*array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	printf("symoff %d\n", symoff);
	printf("stroff %d\n", stroff);
	for (i = 0; i < nsyms; ++i)
	{	
		j = 0;
		while (g_machosym[j].match)
		{
			if (g_machosym[j].match & array[i].n_type)
			{
				symbole = g_machosym[j].symbole;
				if (symbole[0] == 'y')
				{	
					k = 0;
					while (g_machsub[k].subtype)
					{
						if (g_machsub[k].match & array[i].n_type)
						{
							symbole = g_machsub[k].symbole;
							break;
						}
						k++;
					}
				}
				break;
			}
			j++;
		}
		printf("%s  %s\n", symbole, stringtable + array[i].n_un.n_strx);
		printf("%llx\n", array[i].n_value);
	}
}

void		handle_64(char *ptr)
{
	int			ncmds;
	int			i;
	struct mach_header_64	*header;
	struct load_command	*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			printf("%d symbols have been found\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void *) lc + lc->cmdsize;
	}	
}

void		nm(char *ptr)
{
	int	magic_number;
	
	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
}

int		main(int ac, char **av)
{
	int		fd;
	char		*ptr;
	struct stat	buf;

	if (ac != 2)
	{
		fprintf(stderr, "Please give me an arg\n");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}	
	return (EXIT_SUCCESS);
}
