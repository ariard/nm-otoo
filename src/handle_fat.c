/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:30:07 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 20:26:41 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

long int	sysarchi_extract(int ncmds, void *tmp, t_data *data)
{
	int		i;

	i = 0;
	DG("%d", data->cpu);
	while (i++ < ncmds)
	{
		DG("%d", ntohl(((struct fat_arch *)tmp)->cputype));
		if (data->cpu == ntohl(((struct fat_arch *)tmp)->cputype))
			return (ntohl(((struct fat_arch *)tmp)->offset));
		tmp = (void *)tmp + sizeof(struct fat_arch);
	}
	return (0);
}

void		handle_fat(char *ptr, t_data *data)
{
	int					ncmds;
	const NXArchInfo	*arch;
	void				*tmp;
	long int				i;

	(void)data;
	ncmds = ntohl(((struct fat_header *)ptr)->nfat_arch);
	tmp = ptr + sizeof(struct fat_header);
	if ((i = sysarchi_extract(ncmds, tmp, data)))
		return (parse_archi((void *)ptr + i, data));
	i = 0;
	DG("print all archi");
	while (i++ < ncmds)
	{	
		arch = NXGetArchInfoFromCpuType(ntohl(((struct fat_arch *)tmp)->cputype),
			ntohl(((struct fat_arch *)tmp)->cpusubtype));
		ft_printf("\n%s (for %s):\n", data->filename, (arch) ? arch->name : "unknown");
	 	parse_archi((void *)ptr + ntohl(((struct fat_arch *)tmp)->offset), data);
		tmp = (void *)tmp + sizeof(struct fat_arch);
	}
}

//		j = -1;
//		cputype = (((struct fat_arch *)tmp)->cputype);
//		ft_printf("	cputype %d\n", ntohl(cputype));
//		while (g_cpu[++j].cputype)
//			if (!(g_cpu[j].endianf(cputype) ^ g_cpu[j].cputype))
//				break;	
//		ft_printf("cputype %d\n", g_cpu[j].endianf(cputype));
//		ft_printf("	offset %d\n", ntohl(((struct fat_arch *)tmp)->offset));
