/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_archi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:19:15 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 19:16:29 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	parse_archi(char *ptr, t_data *data)
{
	unsigned int		magic_number;
	const NXArchInfo	*arch;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == FAT_CIGAM)
		handle_fat(ptr, data);
	else
	{
		if (magic_number == MH_MAGIC_64)
			handle_64(ptr, data);
		else if (magic_number == MH_MAGIC)
			handle_32(ptr);
		else
		{
			arch = NXGetArchInfoFromCpuType(ntohl(*((int *)ptr + 1)),
				ntohl(*((int *)ptr + 2)));
			ft_dprintf(2, "%s : Not supported\n", (arch) ? arch->name : "(unknown)");
		}
	}
}

// if single = 64 or 32
//  if fat
//  	read number of archi
//  		print archi	
//  			call 32 and 64
//  			if supported archi
//  				execute	


