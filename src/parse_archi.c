/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_archi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:19:15 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 21:28:28 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	parse_archi(char *ptr, t_data *data)
{
	unsigned int		magic_number;
	const NXArchInfo	*arch;
	int					filetype;

	magic_number = *(unsigned int *)ptr;
	filetype = ((struct mach_header *)ptr)->filetype;
	if (filetype ^ MH_OBJECT && filetype ^ MH_EXECUTE && filetype ^ MH_DYLIB)
		ft_dprintf(2, "nm : %s isn't a valid object file", data->filename);
	else if (magic_number == FAT_CIGAM)
		handle_fat(ptr, data);
	else
	{
		if (magic_number == MH_MAGIC_64)
			handle_64(ptr, data);
		else if (magic_number == MH_MAGIC)
			handle_32(ptr, data);
		else
		{
			arch = NXGetArchInfoFromCpuType(ntohl(*((int *)ptr + 1)),
				ntohl(*((int *)ptr + 2)));
			ft_dprintf(2, "%s : Not supported\n", (arch) ? arch->name : "(unknown)");
		}
	}
}
