/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:28:41 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 19:10:44 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64(char *ptr, t_data *data)
{
	int					ncmds;
	int					i;
	int					nsects;
	struct load_command	*lc;

	data->bits = 64;
	ncmds = ((struct mach_header_64 *)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	i = -1;
	nsects = 1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			parse_segment64((struct segment_command_64 *)lc,
			&data->tabsections, &nsects);
		if (lc->cmd == LC_SYMTAB)
			parse_symtab((struct symtab_command *)lc, ptr, data);
		lc = (void *)lc + lc->cmdsize;
	}
	symtab_sort(&data->lstsym, data);
	ft_lstiter(data->lstsym, &print_sym, data);
	hashtab_clean(&data->tabsections, sections_del);
	ft_lstdel(&data->lstsym, sym_del);
}
