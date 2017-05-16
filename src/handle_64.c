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
	int			ncmds;
	int			i;
	int			nsects;
	struct mach_header_64	*header;
	struct load_command	*lc;
	struct section_64	*sect;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	i = 0;
//	hashtab_init(data->tabsections, 100, &ft_hash_string);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			parse_symtab((struct symtab_command *)lc, ptr, data);
		if (lc->cmd == LC_SEGMENT_64)
		{
			ft_printf("cmdsize %lld\n", ((struct segment_command_64 *)lc)->cmdsize);
			ft_printf("segname %s\n", ((struct segment_command_64 *)lc)->segname);
			nsects = ((struct segment_command_64 *)lc)->nsects;
			sect = (void *)lc + sizeof(struct segment_command_64);
			while (nsects--)
			{	
				ft_printf("----------\n");
				ft_printf("sectname %s\n", sect->sectname);
				ft_printf("segname %s\n", sect->segname);
				sect = (void *)sect + sizeof(struct section_64);
			}
			ft_printf("\n");
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
//	symtab_resolve
//	symtab_clean
//	symtab_out
	ft_printf("number cmds = %d\n", ncmds);
}
