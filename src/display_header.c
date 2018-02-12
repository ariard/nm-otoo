/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:20:21 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 19:16:08 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		display_header(char *ptr, t_data *data)
{
	struct mach_header_64	*h;
	int						caps;
	int						sub;

	(void)data;
	h = (struct mach_header_64 *)ptr;
	caps = htonl(h->cpusubtype & CPU_SUBTYPE_LIB64);
	sub = h->cpusubtype ^ CPU_SUBTYPE_LIB64;
	ft_printf("Mach header\n");
	ft_printf("      magic cputype cpusubtype  caps    filetype ncmds "
			"sizeofcmds      flags\n");
	ft_printf(" %#x %8d %10d  0x%02x    %8d %5d %10d 0x%08x\n", h->magic,
			h->cputype, sub, caps, h->filetype, h->ncmds, h->sizeofcmds,
			h->flags);
}

void		display_header32(char *ptr, t_data *data)
{
	struct mach_header		*h;
	int						caps;
	int						sub;

	(void)data;
	h = (struct mach_header *)ptr;
	caps = htonl(h->cpusubtype & CPU_SUBTYPE_MASK);
	sub = h->cpusubtype;
	ft_printf("Mach header\n");
	ft_printf("      magic cputype cpusubtype  caps    filetype ncmds "
			"sizeofcmds      flags\n");
	ft_printf("%#x %8d %10d  0x%02x    %8d %5d %10d 0x%08x\n", h->magic,
			h->cputype, sub, caps, h->filetype, h->ncmds, h->sizeofcmds,
			h->flags);
}
