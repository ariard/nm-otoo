/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:21:29 by ariard            #+#    #+#             */
/*   Updated: 2017/05/19 17:55:22 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		sym_init(t_sym *sym)
{	
	sym->type = 0;
	sym->name = NULL;
	sym->scope = 0;
	sym->sections = 0;
	sym->value = 0;
}

static int		sym_resolve(int num, t_hashtab *tabsections)
{
	char		*key;
	int			type;
	t_list		*elem;

	key = ft_itoa(num);
	type = 0;
	if ((elem = (hashtab_lookup(tabsections, key, &sections_match))))
	{
		type = (ft_strcmp("__data", ((t_section *)elem->content)->sectname) == 0) ?
			'D' : type;
		type = (ft_strcmp("__bss", ((t_section *)elem->content)->sectname) == 0) ?
			'B' : type;
		type = (ft_strcmp("__text", ((t_section *)elem->content)->sectname) == 0) ? 
			'T' : type;
		type = (type == 0) ? 'S' : type;
	}
	ft_strdel(&key);
	return (type);
}	

static void		sym_info(t_sym *sym, char *stringtable, struct nlist_64 el,
				t_hashtab *sections)
{
	sym->name = stringtable + el.n_un.n_strx;
	if (el.n_type & N_STAB)
		sym->type = '-';
	else
	{
		sym->type = ((N_TYPE & el.n_type) ==  N_UNDF) ? 'U' : sym->type;
		sym->type = ((N_EXT & el.n_type) && (el.n_value) && (!el.n_sect)) ?  'C' : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_ABS) ? 'A' : sym->type;
		sym->type = ((N_TYPE & el.n_type)  == N_SECT) ?  
			sym_resolve(el.n_sect, sections) : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_PBUD) ? 'U' : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_INDR) ? 'I' : sym->type;
	}
	if ((el.n_type & N_PEXT) || !(el.n_type & N_EXT))
		sym->type += 32;
	sym->value = el.n_value;
/*	DG(" ");
	DG("%s", sym->name);
	DG("index %.4x", el.n_un.n_strx);
	DG("type %x or %d or %b", el.n_type, el.n_type, el.n_type);
	DG("sect %x", el.n_sect);
	DG("desc %.2x", el.n_desc);
	DG("value %.4x", sym->value); */
}

void			parse_symtab(struct symtab_command *tabsym, char *ptr, t_data *data)
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
		sym_info(&sym, stringtable, (((struct nlist_64 *)((void *)ptr + tabsym->symoff))[i]),
			&data->tabsections);
		ft_lsteadd(&data->lstsym, ft_lstnew(&sym, sizeof(t_sym)));
	}
}
