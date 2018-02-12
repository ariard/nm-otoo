/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 21:59:11 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 20:17:27 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		get_section_text64(struct segment_command_64 *segm,
				char *ptr, t_data *data)
{
	struct section_64	*sect;
	int					segsects;

	segsects = segm->nsects;
	sect = (void *)segm + sizeof(struct segment_command_64);
	while (segsects--)
	{
		if (!ft_strcmp("__text", sect->sectname) && !(data->flag &
			OT_DOPT))
			ft_hexdump64(sect, ptr, data, "Contents of (__TEXT,__text) section");
		if (!ft_strcmp("__data", sect->sectname) && (data->flag &
			OT_DOPT))
			ft_hexdump64(sect, ptr, data, "Contents of (__DATA,__data) section");
		sect = (void *)sect + sizeof(struct section_64);
	}
}

void			get_segment64(char *ptr, t_data *data)
{
	int						ncmds;
	int						i;
	struct load_command		*lc;

	data->bits = 64;
	ncmds = ((struct mach_header_64 *)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			get_section_text64((struct segment_command_64 *)lc, ptr,
				data);
		lc = (void *)lc + lc->cmdsize;
	}
}
