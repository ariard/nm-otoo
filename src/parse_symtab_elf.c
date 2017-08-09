/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:21:29 by ariard            #+#    #+#             */
/*   Updated: 2017/06/09 17:28:59 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_elfsect	g_elfsect[] =
{
	{".bss", 'B'},
	{".rodata", 'R'},
	{".text", 'T'},
	{".data", 'D'},
	{NULL, 0},
};

int		resolve_type(short index, t_hashtab *sections)
{
	char	*key;
	char	type;
	t_list	*elem;
	int	i;

	key = ft_itoa(index);
	type = 0;
	i = -1;
	elem = (hashtab_lookup(sections, key, &sections_match));
	while (g_elfsect[++i].value)
		type = (!ft_strcmp(g_elfsect[i].value,
			((t_section *)elem->content)->sectname)) ? \
			g_elfsect[i].type : type;
	ft_strdel(&key);
	return (type);
}

static int		sym_info_elf(t_sym *sym,
			struct elf64_sym elf_sym, t_data *data)
{
	(void)data;
	DG("index %hd, info %d, section %hd, value %llx, size %llu", 
		elf_sym.st_name, elf_sym.st_info, elf_sym.st_shndx, elf_sym.st_value,
		elf_sym.st_size);
	if (!elf_sym.st_name || !elf_sym.st_value)
		return (1);
	sym->index = elf_sym.st_name;
	sym->value = elf_sym.st_value;
	sym->type = resolve_type(elf_sym.st_shndx, &data->tabsections);
	return (0);
}

void			parse_symtab_elf(char *ptr, 
			struct elf64_shdr *section_header, t_data *data)
{
	struct	elf64_sym *tabsym;
	int	num_sym;
	int	i;
	t_sym	sym;

	tabsym = (struct elf64_sym *)(ptr + section_header->sh_offset);
	num_sym = section_header->sh_size / section_header->sh_entsize;
	i = -1;
	while (++i < num_sym)
	{
		sym_init(&sym);
		if (sym_info_elf(&sym, tabsym[i], data))
			continue;
		ft_lsteadd(&data->lstsym, ft_lstnew(&sym, sizeof(t_sym)));
	}
}
