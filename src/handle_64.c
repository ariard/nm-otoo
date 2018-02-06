/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:28:41 by ariard            #+#    #+#             */
/*   Updated: 2018/02/06 18:09:46 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64(char *ptr, t_data *data)
{ 
	int							ncmds;
	int							i;
	int							nsects;
	struct load_command			*lc;

	ncmds = ((struct mach_header_64 *)ptr)->ncmds;
	if (((struct mach_header_64 *)ptr)->filetype & MH_OBJECT)
		data->filetype = MH_OBJECT;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	nsects = 1;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			parse_symtab((struct symtab_command *)lc, ptr, data);
		if (lc->cmd == LC_SEGMENT_64)
			parse_sections((struct segment_command_64 *)lc, &data->tabsections, &nsects);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
//	hashtab_print(&data->tabsections, sections_print);	
	symtab_sort(&data->lstsym, data);
	ft_lstiter(data->lstsym, &print_sym, data);
}
