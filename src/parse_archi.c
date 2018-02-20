/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_archi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 19:51:30 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 20:46:37 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	handle_32and64(unsigned int magic_number, char *ptr,
			t_data *data)
{
	const NXArchInfo	*arch;

	if (magic_number == MH_MAGIC_64 && !data->bin && (OT_HOPT & data->flag))
		display_header(ptr, data);
	else if (magic_number == MH_MAGIC && !data->bin && (OT_HOPT & data->flag))
		display_header32(ptr, data);
	else if (magic_number == MH_MAGIC_64)
		(data->bin) ? handle_64(ptr, data) : get_segment64(ptr, data);
	else if (magic_number == MH_MAGIC)
		(data->bin) ? handle_32(ptr, data) : get_segment32(ptr, data);
	else
	{
		MC(ptr + 1);
		MC(ptr + 2);
		arch = NXGetArchInfoFromCpuType(ntohl(*((int *)ptr + 1)),
			ntohl(*((int *)ptr + 2)));
		ft_dprintf(2, " %s %s : %s not supported\n", data->filename,
			(data->bin) ? "nm" : "otool", (arch) ? arch->name : "(unknown)");
		if (arch)
			NXFreeArchInfo(arch);
	}
}

void		parse_archi(char *ptr, t_data *data)
{
	unsigned int		magic_number;
	int					filetype;

	MC(ptr);
	magic_number = *(unsigned int *)ptr;
	filetype = ((struct mach_header *)ptr)->filetype;
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_ar(ptr, data);
	else if (magic_number == FAT_CIGAM)
		handle_fat(ptr, data);
	else if (filetype ^ MH_OBJECT && filetype ^ MH_EXECUTE
		&& filetype ^ MH_DYLIB && filetype ^ MH_FVMLIB
		&& filetype ^ MH_DYLINKER && filetype ^ MH_DYLIB_STUB)
		ft_dprintf(2, "%s : %s isn't a valid object file\n", (data->bin) ?
		"nm" : "otool", data->filename);
	else
		handle_32and64(magic_number, ptr, data);
}
