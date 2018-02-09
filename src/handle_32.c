/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:29:25 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 21:27:55 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_32(char *ptr, t_data *data)
{
	int							ncmds;
	int							i;
	int							nsects;
	struct load_command			*lc;

	data->bits = 32;
	ncmds = ((struct mach_header *)ptr)->ncmds;
//	if (((struct mach_header *)ptr)->filetype & MH_OBJECT)
//		data->filetype = MH_OBJECT;
	lc = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	nsects = 1;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			parse_segment32((struct segment_command *)lc, &data->tabsections, &nsects);
		if (lc->cmd == LC_SYMTAB)
			parse_symtab32((struct symtab_command *)lc, ptr, data);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
//	hashtab_print(&data->tabsections, sections_print);
	symtab_sort(&data->lstsym, data);
	ft_lstiter(data->lstsym, &print_sym, data);
	hashtab_clean(&data->tabsections, sections_del);
	ft_lstdel(&data->lstsym, sym_del);
}	
