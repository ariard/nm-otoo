/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 21:13:59 by ariard            #+#    #+#             */
/*   Updated: 2018/02/13 21:43:41 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	sanitize(void *ptr, size_t size, t_data *data)
{
	if (!ptr)
	{
		ft_dprintf(2, "%s : file corrupted", (data->bin) ? "nm" : "otool");
		exit(1);
	}
	if ((char *)ptr < data->origin || (char *)ptr + size > data->origin
		+ data->filesize)
	{
		ft_dprintf(2, "%s : %s corrupted", data->filename,
			(data->bin) ? "nm" : "otool");
		exit(1);
	}
}
