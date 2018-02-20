/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:29:25 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 20:46:17 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_32(char *ptr, t_data *data)
{
	int					ncmds;
	int					i;
	int					nsects;
	struct load_command	*lc;

	data->bits = 32;
	ncmds = ((struct mach_header *)ptr)->ncmds;
	MC(lc = (void *)ptr + sizeof(struct mach_header));
	i = -1;
	nsects = 1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			parse_segment32((struct segment_command *)lc,
			&data->tabsections, &nsects, data);
		if (lc->cmd == LC_SYMTAB)
			parse_symtab32((struct symtab_command *)lc,
			ptr, data);
		MBC(lc = (void *)lc + lc->cmdsize);
	}
	symtab_sort(&data->lstsym, data);
	ft_lstiter(data->lstsym, &print_sym, data);
	hashtab_clean(&data->tabsections, sections_del);
	ft_lstdel(&data->lstsym, sym_del);
}
