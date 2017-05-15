/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:28:41 by ariard            #+#    #+#             */
/*   Updated: 2017/05/16 00:39:35 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64(char *ptr, t_data *data)
{ 
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	parse_sections(ptr, &data);
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	i = 0;
	hashtab_init(data->tabsections, 100, &ft_hash_string);
	while (i < ncmds)
	{
		if (lc->cmd = LC_SYMTAB)
			parse
			sym = (struct symtab_command *)lc;
			break;
		

		lc = (void *)lc + lc->cmdsize;
	}
}
