/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:30:07 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 19:34:03 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

//void		handle_fat(char *ptr)
//{
//	int			ncmds;
//	void			*tmp;
//	int			i;
//
//	ncmds = ntohl(((struct fat_header *)ptr)->nfat_arch);
//	tmp = ptr + sizeof(struct fat_header);
//	i = 0;
//	// fix cputype + cpusubtype story
//	while (i++ < ncmds)
//	{	
//		DG("%p\n", tmp);
//		DG("%d\n", tmp - (void *)ptr);
//		ft_printf("architecture %d\n", i);
//		ft_printf("	cputype %d\n", ntohl(((struct fat_arch *)tmp)->cputype));		
//		ft_printf("	cputype %d\n", (((struct fat_arch *)tmp)->cputype));		
//		ft_printf("	cpusubtype %d\n", ntohl(((struct fat_arch *)tmp)->cpusubtype));
//		ft_printf("	cpusubtype %d\n", (((struct fat_arch *)tmp)->cpusubtype));
//		//capabilities ?
//		ft_printf("	offset %d\n", ntohl(((struct fat_arch *)tmp)->offset));
//		ft_printf("	size %d\n", ntohl(((struct fat_arch *)tmp)->size));
//		ft_printf("	align %d\n", ntohl(((struct fat_arch *)tmp)->align));
//		tmp = (void *)tmp + sizeof(struct fat_arch);
//	}
//}

//		ft_printf("architecture %d\n", i);
//		j = -1;
//		cputype = (((struct fat_arch *)tmp)->cputype);
//		ft_printf("	cputype %d\n", ntohl(cputype));
//		while (g_cpu[++j].cputype)
//			if (!(g_cpu[j].endianf(cputype) ^ g_cpu[j].cputype))
//				break;	
//		ft_printf("cputype %d\n", g_cpu[j].endianf(cputype));
