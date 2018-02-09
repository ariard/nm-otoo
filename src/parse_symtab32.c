/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symtab32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:27:55 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 19:29:17 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		sym_info(t_sym *sym, char *stringtable, struct nlist el,
				t_hashtab *sections)
{
	sym->name = stringtable + el.n_un.n_strx;
	if (N_STAB & el.n_type)
		sym_stab(sym, el.n_type);
	 else
	{
		sym->type = ((N_TYPE & el.n_type) ==  N_UNDF) ? 'U' : sym->type;
		sym->type = ((N_EXT & el.n_type) && (el.n_value) && (!el.n_sect)) ?  'C' : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_ABS) ? 'A' : sym->type;
		sym->type = ((N_TYPE & el.n_type)  == N_SECT) ?  
			sym_resolve(el.n_sect, sections) : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_PBUD) ? 'U' : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_INDR) ? 'I' : sym->type;
		if ((el.n_type & N_PEXT) || !(el.n_type & N_EXT))
			sym->type += 32;
	}
	sym->value = el.n_value;
//	dprintf(3, "[%s] %d\n", sym->name, sym->value);
}

void			parse_symtab32(struct symtab_command *tabsym, char *ptr, t_data *data)
{
	int					i;
	int					nsyms;
	char				*stringtable;
	t_sym				sym;

	stringtable = (void *)ptr + tabsym->stroff;
	nsyms = tabsym->nsyms;
	i = -1;
	while (++i < nsyms)
	{
		sym_init(&sym);
		sym_info(&sym, stringtable, (((struct nlist *)((void *)ptr + tabsym->symoff))[i]),
			&data->tabsections);
		ft_lsteadd(&data->lstsym, ft_lstnew(&sym, sizeof(t_sym)));
	}
}
