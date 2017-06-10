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

void		sym_info_elf(t_sym *sym, struct elf64_sym elf_sym)
{
	sym->type = elf_sym.st_info;
	sym->index = elf_sym.st_name;
	sym->value = elf_sym.st_value;
}

void		parse_symtab_elf(char *ptr, struct elf64_shdr *section_header,
		t_data *data)
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
		sym_info_elf(&sym, tabsym[i]);
		ft_lsteadd(&data->lstsym, ft_lstnew(&sym, sizeof(t_sym)));
	}		
}
