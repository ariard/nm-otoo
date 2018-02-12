/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:21:29 by ariard            #+#    #+#             */
/*   Updated: 2018/02/10 22:28:30 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_stabs			g_stabs[]=
{
	{0x20, "GSYM"},
	{0x22, "FNAME"},
	{0x24, "FUN"},
	{0x26, "STSYM"},
	{0x28, "LCSYM"},
	{0x2e, "BNSYM"},
	{0x32, "AST"},
	{0x3c, "OPT"},
	{0x40, "RSYM"},
	{0x44, "SLINE"},
	{0x4e, "ENSYM"},
	{0x60, "SSYM"},
	{0x64, "SO"},
	{0x66, "OSO"},
	{0x80, "LSYM"},
	{0x82, "BINCL"},
	{0x84, "SOL"},
	{0x86, "PARAMS"},
	{0x88, "VERSION"},
	{0x8A, "OLEVEL"},
	{0xa0, "PSYM"},
	{0xa2, "EINCL"},
	{0xa4, "ENTRY"},
	{0xc0, "LBRAC"},
	{0xc2, "EXCL"},
	{0xe0, "RBRAC"},
	{0xe2, "BCOMM"},
	{0xe4, "ECOMM"},
	{0xe8, "ECOML"},
	{0xfe, "LENG"},
	{0x0, "null"},
};

void			sym_init(t_sym *sym)
{
	sym->type = 0;
	sym->name = NULL;
	sym->desc = NULL;
	sym->value = 0;
	sym->index = 0;
	sym->sect = 0;
	sym->debug = 0;
}

int		sym_resolve(int num, t_hashtab *tabsections)
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

static void		sym_stab(t_sym *sym, struct nlist_64 el)
{
	int			i;

	sym->type = '-';
	i = -1;
	while (++i < 29)
		if (g_stabs[i].value == el.n_type)
			break;
	sym->desc = g_stabs[i].entry;
	sym->sect = el.n_sect;
	sym->debug = el.n_desc;
}

static void		sym_info(t_sym *sym, char *stringtable, struct nlist_64 el,
			t_hashtab *sections)
{
	sym->name = stringtable + el.n_un.n_strx;
	if (N_STAB & el.n_type)
		sym_stab(sym, el);
	 else
	{
		sym->type = ((N_TYPE & el.n_type) ==  N_UNDF) ? 'U' : sym->type;
		sym->type = ((N_EXT & el.n_type) && (el.n_value) && (!el.n_sect)) ?  'C' : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_ABS) ? 'A' : sym->type;
		sym->type = ((N_TYPE & el.n_type)  == N_SECT) ?  
			sym_resolve(el.n_sect, sections) : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_PBUD) ? 'U' : sym->type;
		sym->type = ((N_TYPE & el.n_type) == N_INDR) ? 'I' : sym->type;
		if (!(BIT(el.n_type, 0) & N_EXT))
			sym->type += 32;
	}
	sym->value = el.n_value;
//	DG("[%s] %llx\n", sym->name, sym->value);
}

void			sym_del(void *data_ref, size_t size)
{
	t_sym		*sym;

	(void)size;
	sym = (t_sym *)data_ref;
	sym->type = 0;
	sym->name = NULL;
	sym->desc = NULL;
	sym->value = 0;
	sym->index = 0;
	sym->sect = 0;
	sym->debug = 0;
	free(data_ref);
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
