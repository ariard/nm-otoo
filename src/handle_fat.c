/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:30:07 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 20:33:00 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static uint32_t		extract_offset(void *tmp, t_data *data)
{
	if (((struct fat_arch *)tmp)->offset == 0)
	{
		ft_dprintf(2, "%s: %s bad offset in header\n", (data->bin) ?
			"nm" : "otool", data->filename);
		return (0);
	}
	return (ntohl(((struct fat_arch *)tmp)->offset));
}

static void			otool_special(t_data *data)
{
	if (!data->bin)
		data->flag |= OT_FOPT;
}

static void			branch_all(char *ptr, void *tmp, int narchs, t_data *data)
{
	int					i;
	const NXArchInfo	*arch;
	uint32_t			off;

	i = 0;
	while (i++ < narchs)
	{
		arch = NXGetArchInfoFromCpuType(
			ntohl(((struct fat_arch *)tmp)->cputype),
			ntohl(((struct fat_arch *)tmp)->cpusubtype));
		if (narchs > 1)
			ft_printf("\n%s (for %s):\n", data->filename, (arch)
				? arch->name : "unknown");
		else
			ft_printf("%s:\n", data->filename);
		if (arch)
			NXFreeArchInfo(arch);
		if (!(off = extract_offset(tmp, data)))
			return ;
		parse_archi((void *)ptr + off, data);
		MC(tmp = (void *)tmp + sizeof(struct fat_arch));
	}
}

void				handle_fat(char *ptr, t_data *data)
{
	int			i;
	int			narchs;
	void		*tmp;
	uint32_t	off;

	narchs = ntohl(((struct fat_header *)ptr)->nfat_arch);
	MC(tmp = ptr + sizeof(struct fat_header));
	i = -1;
	while (++i < narchs)
	{
		if (!(off = extract_offset(tmp, data)))
			return ;
		if (data->cpu == ntohl(((struct fat_arch *)tmp)->cputype))
			return (parse_archi(ptr + off, data));
		MC(tmp = (void *)tmp + sizeof(struct fat_arch));
	}
	MC(tmp = ptr + sizeof(struct fat_header));
	otool_special(data);
	branch_all(ptr, tmp, narchs, data);
}
