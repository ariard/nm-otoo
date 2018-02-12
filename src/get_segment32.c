/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_archi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:19:15 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 21:04:46 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		get_section_text32(struct segment_command *segm,
				char *ptr, t_data *data)
{
	struct section		*sect;
	int					segsects;

	segsects = segm->nsects;
	sect = (void *)segm + sizeof(struct segment_command);
	while (segsects--)
	{
		if (!ft_strcmp("__text", sect->sectname))
			ft_hexdump32(sect, ptr, data, "Contents of (__TEXT,__text) "
				"section");
		if (!ft_strcmp("__data", sect->sectname) && (data->flag &
			OT_DOPT))
			ft_hexdump32(sect, ptr, data, "Contents of (__DATA,__data) "
				"section");
		sect = (void *)sect + sizeof(struct section);
	}
}

void			get_segment32(char *ptr, t_data *data)
{
	int						ncmds;
	int						i;
	struct load_command		*lc;

	if (!(OT_HOPT & data->flag) && !(OT_FOPT & data->flag)
		&& !(OT_AOPT & data->flag))
		ft_printf("%s:\n", data->filename);
	data->bits = 32;
	ncmds = ((struct mach_header *)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			get_section_text32((struct segment_command *)lc, ptr,
				data);
		lc = (void *)lc + lc->cmdsize;
	}
}
