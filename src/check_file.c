/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:17:47 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 19:59:14 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char		check_32(struct segment_command *segm, t_data *data)
{
	char	*tmp;

	tmp = data->origin;
	MCS2(segm);
	tmp += segm->fileoff + segm->filesize;
	if (tmp > (data->origin + data->filesize))
	{
		ft_dprintf(2, "%s: %s truncated or malformed object\n", (data->bin) ?
			"nm" : "otool", data->filename);
		return (1);
	}
	return (0);
}

char		check_64(struct segment_command_64 *segm, t_data *data)
{
	char	*tmp;

	tmp = data->origin;
	MCS2(segm);
	tmp += segm->fileoff + segm->filesize;
	if (tmp > (data->origin + data->filesize))
	{
		ft_dprintf(2, "%s: %s truncated or malformed object\n", (data->bin) ?
			"nm" : "otool", data->filename);
		return (1);
	}
	return (0);
}

char		check_sym(struct symtab_command *tab, t_data *data)
{
	char	*tmp;

	tmp = data->origin;
	MCS2(tab);
	tmp += tab->strsize + tab->stroff;
	if (tmp > (data->origin + data->filesize))
	{
		ft_dprintf(2, "%s: %s truncated or malformed object\n", (data->bin) ?
			"nm" : "otool", data->filename);
		return (1);
	}
	return (0);
}
