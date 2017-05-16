#include "nm.h"

void		parse_symtab(struct symtab_command *sym, char *ptr, t_data *data)
{
	int			i;
	int			nsyms;
	char			*stringtable;
	struct nlist_64		*array;

	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	nsyms = sym->nsyms;
	i = -1;
	ft_printf("symoff %d\n", sym->symoff);
	while (++i < nsyms)
	{
		ft_printf("%x %s\n", array[i].n_value, stringtable + array[i].n_un.n_strx);
		ft_printf("sect %d\n", array[i].n_sect);
	}
	(void)data;
}

/*	sym_init
	sym_info
		-branch 

*/
